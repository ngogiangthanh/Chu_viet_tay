#include "Extent.h"

Extent::Extent()
{
}

//Chuyển từ định dạng mat sang bitmap
Bitmap^ Extent::ConvertMatToBitmap(Mat matToConvert)
{
	return gcnew Bitmap(matToConvert.cols, matToConvert.rows, 4 * matToConvert.rows, Imaging::PixelFormat::Format24bppRgb, IntPtr(matToConvert.data));
}

// Chuyển từ định dạng bitmap sang mat
Mat Extent::BitmapToMat(Bitmap^ bitmap)
{
	IplImage* tmp;

	Imaging::BitmapData^ bmData = bitmap->LockBits(Rectangle(0, 0, bitmap->Width, bitmap->Height), Imaging::ImageLockMode::ReadWrite, bitmap->PixelFormat);
	if (bitmap->PixelFormat == Imaging::PixelFormat::Format8bppIndexed)
	{
		tmp = cvCreateImage(cvSize(bitmap->Width, bitmap->Height), IPL_DEPTH_8U, 1);
		tmp->imageData = (char*)bmData->Scan0.ToPointer();
	}

	else if (bitmap->PixelFormat == Imaging::PixelFormat::Format24bppRgb)
	{
		tmp = cvCreateImage(cvSize(bitmap->Width, bitmap->Height), IPL_DEPTH_8U, 3);
		tmp->imageData = (char*)bmData->Scan0.ToPointer();
	}

	bitmap->UnlockBits(bmData);

	return cvarrToMat(tmp);
}

// Ép kiểu System::String sang std::string
void Extent::MarshalString(System::String^ s, string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

vector<string>& Extent::split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		if (!item.empty())
			elems.push_back(item);
	}
	return elems;
}

vector<string> Extent::split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void Extent::LoadImage(PictureBox^ pb, Mat icon)
{
	Graphics^ graphics = pb->CreateGraphics();
	IntPtr ptr(icon.ptr());
	Bitmap^ b = gcnew Bitmap(icon.cols, icon.rows, icon.step, Imaging::PixelFormat::Format24bppRgb, ptr);
	RectangleF rect(0, 0, pb->Width, pb->Height);
	graphics->DrawImage(b, rect);
}

void Extent::showImage(string path)
{
	//Mo file hinh bang chuong trinh mac dinh cua windows
	string run = "start " + path;
	const char * executeStr = run.c_str();
	system(executeStr);
	executeStr = run.c_str();
}
