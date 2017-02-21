#include "frmMain.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace System;
using namespace System::Windows::Forms;


[STAThread]
int main(int argc, char** argv)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Thesis::frmMain form;
	Application::Run(%form);
	return 0;
}

System::Void Thesis::frmMain::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}
