#include "frmMain.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
int main(int argc, char** argv){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	

	OpenCV_JP::frmMain main;
	Application::Run(%main);
}

System::Void OpenCV_JP::frmMain::btnPre_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!frmPreprocessing::instance) {
		frmPreprocessing^ pre = gcnew frmPreprocessing();
		pre->Show();
		frmPreprocessing::instance = true;
	}
}

System::Void OpenCV_JP::frmMain::btnSeg_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!frmSegmentation::instance) {
		frmSegmentation^ seg = gcnew frmSegmentation();
		seg->Show();
		frmSegmentation::instance = true;
	}
}

System::Void OpenCV_JP::frmMain::btnNormal_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!frmNormalization::instance) {
		frmNormalization^ normal = gcnew frmNormalization();
		normal->Show();
		frmNormalization::instance = true;
	}
}

System::Void OpenCV_JP::frmMain::btnExtract_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!frmExtractFeatures::instance) {
		frmExtractFeatures^ extract = gcnew frmExtractFeatures();
		extract->Show();
		frmExtractFeatures::instance = true;
	}
}

System::Void OpenCV_JP::frmMain::btnDTW_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!frmDTW::instance) {
		frmDTW^ dtw = gcnew frmDTW();
		dtw->Show();
		frmDTW::instance = true;
	}
}
