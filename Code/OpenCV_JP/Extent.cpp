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

void Extent::ReplaceStringInPlace(std::string & subject, const std::string & search, const std::string & replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}