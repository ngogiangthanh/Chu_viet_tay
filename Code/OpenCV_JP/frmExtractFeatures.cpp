#include "frmExtractFeatures.h"
#include "Projection.h"
#include "Word_lp.h"
#include "Word_Up.h"
#include "Word_Profile.h"

const vector<string> explode(const string& s, const char& c);

System::Void OpenCV_JP::frmExtractFeatures::btnOpenInput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Thesis\\Chu_viet_tay\\Experiments\\Clustering";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		this->lbInput->Text = folderBrowserDialog->SelectedPath;
		tbAlert->Text = tbAlert->Text + "\r\nChoose input: " + folderBrowserDialog->SelectedPath;
	}
}

System::Void OpenCV_JP::frmExtractFeatures::btnOpenOutput_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog->SelectedPath = "D:\\Thesis\\Chu_viet_tay\\Experiments\\Clustering";
	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		this->lbOutput->Text = folderBrowserDialog->SelectedPath;
		tbAlert->Text = tbAlert->Text + "\r\nChoose output: " + folderBrowserDialog->SelectedPath;
	}
}

System::Void OpenCV_JP::frmExtractFeatures::btnExtract_Click(System::Object ^ sender, System::EventArgs ^ e)
{
		Extent* extent = new Extent();

		string input_path_image;
		string output_path_image;
		extent->MarshalString(lbInput->Text, input_path_image);
		extent->MarshalString(lbOutput->Text, output_path_image);

	if (cbPp->Checked) {

		ofstream extracting_pp_file;
		extracting_pp_file.open(output_path_image+"\\projection_profiles.txt");

		for (auto i = fs::recursive_directory_iterator(input_path_image);
			i != fs::recursive_directory_iterator();
			++i) {
			ostringstream oss;
			oss << *i;
			string str = oss.str();

			vector<string> v{ explode(str, '\\') };
			vector<string> v1{ explode(v.back(), '.') };
			string extension = v1.back();
			if (extension == "jpg" | extension == "JPG" | extension == "png" | extension == "PNG" | extension == "BMP" | extension == "bmp")
			{
			 //cout << "str " << str << endl;
			 Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

			 Projection projection_profile(img_org);
			 projection_profile.cal_pp();
			 projection_profile.draw_pp();
			 float *pp = 0;
			 int size_pp = projection_profile.get_pp(pp);
			 string line = str + " ";
			 for (int i = 0; i < size_pp; i++) {

				 std::ostringstream ss;
				 ss << pp[i];
				 std::string s(ss.str());
				 if (i < size_pp - 1)
					 line = line + s + " ";
				 else if (i == size_pp - 1)
					 line = line + s;
			 }
			 extracting_pp_file << line + "\n";
			}
		}
		extracting_pp_file.close();

		tbAlert->Text = "\r\nRunning extracting projection profiles...";

	}
	if (cbupw->Checked) {
		ofstream extracting_wup_file;
		extracting_wup_file.open(output_path_image + "\\word_upper_profiles.txt");

		for (auto i = fs::recursive_directory_iterator(input_path_image);
			i != fs::recursive_directory_iterator();
			++i) {
			ostringstream oss;
			oss << *i;
			string str = oss.str();

			vector<string> v{ explode(str, '\\') };
			vector<string> v1{ explode(v.back(), '.') };
			string extension = v1.back();
			if (extension == "jpg" | extension == "JPG" | extension == "png" | extension == "PNG" | extension == "BMP" | extension == "bmp")
			{
				//cout << "str " << str << endl;
				Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

				Word_Up word_up(img_org);
				word_up.cal_up();
				word_up.interpolated_value();
				word_up.draw_up();

				float *wup = 0;
				int size_wup = word_up.get_up(wup);
				string line = str + " ";
				for (int i = 0; i < size_wup; i++) {

					std::ostringstream ss;
					ss << wup[i];
					std::string s(ss.str());
					if (i < size_wup - 1)
						line = line + s + " ";
					else if (i == size_wup - 1)
						line = line + s;
				}
				extracting_wup_file << line + "\n";
			}
		}
		extracting_wup_file.close();
		tbAlert->Text =  "\r\nRunning extracting upper word...";

	}
	if (cblw->Checked) {
		ofstream extracting_wlp_file;
		extracting_wlp_file.open(output_path_image + "\\word_lower_profiles.txt");

		for (auto i = fs::recursive_directory_iterator(input_path_image);
			i != fs::recursive_directory_iterator();
			++i) {
			ostringstream oss;
			oss << *i;
			string str = oss.str();

			vector<string> v{ explode(str, '\\') };
			vector<string> v1{ explode(v.back(), '.') };
			string extension = v1.back();
			if (extension == "jpg" | extension == "JPG" | extension == "png" | extension == "PNG" | extension == "BMP" | extension == "bmp")
			{
				//cout << "str " << str << endl;
				Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

				Word_lp word_lp(img_org);
				word_lp.cal_lp();
				word_lp.interpolated_value();
				word_lp.draw_lp();
				float* lwp = 0;
				int size_lwp = word_lp.get_lp(lwp);

				string line = str + " ";
				for (int i = 0; i < size_lwp; i++) {

					std::ostringstream ss;
					ss << lwp[i];
					std::string s(ss.str());
					if (i < size_lwp - 1)
						line = line + s + " ";
					else if (i == size_lwp - 1)
						line = line + s;
				}
				extracting_wlp_file << line + "\n";
			}
		}
		extracting_wlp_file.close();
		tbAlert->Text =  "\r\nRunning extracting lower word...";
	}

	if (cblw->Checked & cbupw->Checked) {
		ofstream extracting_wp_file;
		extracting_wp_file.open(output_path_image + "\\word_profiles.txt");

		for (auto i = fs::recursive_directory_iterator(input_path_image);
			i != fs::recursive_directory_iterator();
			++i) {
			ostringstream oss;
			oss << *i;
			string str = oss.str();

			vector<string> v{ explode(str, '\\') };
			vector<string> v1{ explode(v.back(), '.') };
			string extension = v1.back();
			if (extension == "jpg" | extension == "JPG" | extension == "png" | extension == "PNG" | extension == "BMP" | extension == "bmp")
			{
				//cout << "str " << str << endl;
				Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

				Word_Up word_up(img_org);
				word_up.cal_up();
				word_up.interpolated_value();
				word_up.draw_up();
				float* wup = 0;
				int size_wup = word_up.get_up(wup);

				Word_lp word_lp(img_org);
				word_lp.cal_lp();
				word_lp.interpolated_value();
				word_lp.draw_lp();
				float* lwp = 0;
				int size_lwp = word_lp.get_lp(lwp);

				float *wpp = 0;
				Word_Profile word_pp(wup, lwp, size_lwp);
				word_pp.combined(wpp);
				//word_pp.draw_wp();

				string line = str + " ";
				for (int i = 0; i < size_wup; i++) {

					std::ostringstream ss;
					ss << wpp[i];
					std::string s(ss.str());
					if (i < size_wup - 1)
						line = line + s + " ";
					else if (i == size_wup - 1)
						line = line + s;
				}
				extracting_wp_file << line + "\n";
			}
		}
		extracting_wp_file.close();
		tbAlert->Text = "\r\nRunning extracting word profile...";
	}
}

const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}