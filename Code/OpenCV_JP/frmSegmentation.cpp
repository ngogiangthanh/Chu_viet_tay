#include "frmSegmentation.h"

System::Void OpenCV_JP::frmSegmentation::btnSegSave_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void OpenCV_JP::frmSegmentation::btnOpenOutput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Output_Seg\\";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		this->lbOutput->Text = folderBrowserDialog->SelectedPath;
	}
}

System::Void OpenCV_JP::frmSegmentation::btnSegSetMAF_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void OpenCV_JP::frmSegmentation::btnSegResetMAF_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->cbbSegMAF->SelectedIndex = 2;
}

System::Void OpenCV_JP::frmSegmentation::btnSegSetHeighOfLine_Click(System::Object ^ sender, System::EventArgs ^ e)
{
}

System::Void OpenCV_JP::frmSegmentation::btnSegResetHeighOfLine_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->trbSegHeighOfLine->Value = 40;
	this->lbSegValHeigh->Text = "40";
}

System::Void OpenCV_JP::frmSegmentation::btnKhoiTao_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void OpenCV_JP::frmSegmentation::btnMAFSeg_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void OpenCV_JP::frmSegmentation::btnFindValley_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void OpenCV_JP::frmSegmentation::btnSegConnectValley_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void OpenCV_JP::frmSegmentation::btnOpenInput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Output_Pre\\";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		this->lbInput->Text = folderBrowserDialog->SelectedPath;
	}
}

System::Void OpenCV_JP::frmSegmentation::trbSegHeighOfLine_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	std::string model(std::to_string(trbSegHeighOfLine->Value));
	System::String^ val = gcnew System::String(model.c_str());
	lbSegValHeigh->Text = val;
}
