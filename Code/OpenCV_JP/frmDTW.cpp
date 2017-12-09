#include "frmDTW.h"
#include "md5.h"
#include "Entropy.h"
#include "Clustering.h"
#include "FastDTW.h"

using namespace System;
using namespace System::IO;

const vector<string> explode(const string& s, const char& c);
const void to_str(System::String^ s, string& os);

System::Void OpenCV_JP::frmDTW::btnCreate_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog->InitialDirectory = "D:\\Dataset\\4-Features";
	openFileDialog->FilterIndex = 2;
	openFileDialog->RestoreDirectory = true;

	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		this->lbPath->Text = openFileDialog->FileName;
	}
}

System::Void OpenCV_JP::frmDTW::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ fileName = this->lbPath->Text;
	vector<Clustering> v_Clustering;

	try
	{
		Console::WriteLine("trying to open file {0}...", fileName);
		StreamReader^ din = File::OpenText(fileName);

		String^ str;
		while ((str = din->ReadLine()) != nullptr)
		{
			string str1;
			to_str(str, str1);
			vector<string> v{ explode(str1, ' ') };
			string cluster_num = v.back();
			string path_img = v[0];

			cv::Mat img_org = cv::imread(path_img, CV_LOAD_IMAGE_GRAYSCALE);
			std::string savePath = "D:\\Dataset\\4-Features\\Clustering\\rs\\" +cluster_num+"\\";

			mkdir(savePath.c_str());

			cout << " " << savePath << endl;

			savePath += "/" +  md5(path_img) + ".jpg";
			cv::imwrite(savePath, img_org);
		}
	}
	catch (Exception^ e)
	{
		if (dynamic_cast<FileNotFoundException^>(e))
			Console::WriteLine("file '{0}' not found", fileName);
		else
			Console::WriteLine("problem reading file '{0}'", fileName);
	}
}

System::Void OpenCV_JP::frmDTW::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ fileName = this->lbPath->Text;

	vector<Clustering> v_Clustering;
	int N = 0;

	try
	{
		Console::WriteLine("trying to open file {0}...", fileName);
		StreamReader^ din = File::OpenText(fileName);

		String^ str;
		while ((str = din->ReadLine()) != nullptr)
		{
			string str1;
			to_str(str, str1);
			vector<string> v{ explode(str1, ' ') };
			string cluster_num = v.back();
			string path_img = v[0];

			vector<string> v1{ explode(str1, '\\') };

			int size = v_Clustering.size();
			bool isExist = false;

			for (int i = 0; i < size; i++) {
				if (v_Clustering[i].getClusterName() == cluster_num) {
					v_Clustering[i].addCluster(v1[v1.size() - 2]);
					isExist = true;
				}
			}
			if (!isExist) {
				Clustering clustering(cluster_num);
				clustering.addCluster(v1[v1.size() - 2]);
				v_Clustering.push_back(clustering);
			}

			N++;
		}
	}
	catch (Exception^ e)
	{
		if (dynamic_cast<FileNotFoundException^>(e))
			Console::WriteLine("file '{0}' not found", fileName);
		else
			Console::WriteLine("problem reading file '{0}'", fileName);
	}


	ofstream entropy_file;
	entropy_file.open("D:\\entropy.txt");


	int size = v_Clustering.size();

	double entropy = 0;
	int counttest = 0;

	for (int i = 0; i < size; i++) {
		Entropy entr;
		entr.setN(N);
		vector<Cluster> v_Cluster = v_Clustering[i].getClusters();
		int size_v_cluster = v_Cluster.size();

		for (int j = 0; j < size_v_cluster; j++) {
			entr.addNi(v_Cluster[j].getTimes());
			entr.addColumn(v_Cluster[j].getTimes());
		}

		entropy += entr.getEntropy();
		counttest += entr.getNi();
	}

	cout << "counttest= " << counttest << endl;
	cout << "Entropy= " << entropy << endl;

	for (int i = 0; i < size; i++) {

		string line = "";

		line = v_Clustering[i].getClusterName();
		line += "	" + v_Clustering[i].printClusterChild();
		entropy_file << line + "\n";
	}

	entropy_file.close();
}

System::Void OpenCV_JP::frmDTW::button3_Click(System::Object ^ sender, System::EventArgs ^ e)
{

	backgroundWorkerFastDTW->RunWorkerAsync();

}

System::Void OpenCV_JP::frmDTW::button4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	backgroundWorkerLBImproved->RunWorkerAsync();
}

System::Void OpenCV_JP::frmDTW::backgroundWorkerFastDTW_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	String^ fileName = this->lbPath->Text;
	try
	{
		clock_t begin = clock();
		Console::WriteLine("trying to open file {0}...", fileName);
		StreamReader^ din = File::OpenText(fileName);

		String^ str;

		vector<vector<double>> candidates;

		while ((str = din->ReadLine()) != nullptr)
		{
			string str1;
			to_str(str, str1);
			vector<string> v{ explode(str1, ' ') };
			vector<double> candidate;

			int size = v.size();
			for (int i = 0; i < size; i++) {
				candidate.push_back(stod(v[i]));
			}

			candidates.push_back(candidate);
		}

		int size_feature = candidates.size();
		vector<double> target;
		int compare = size_feature;
		double bestsofar = 10000000;
		long counting = 0;
		for (int k = 0; k < compare; k++) {
			fastdtw *_dtw;
			bestsofar = 10000000;
			//Set target
			target = candidates[k];
			_dtw = new fastdtw(target.size(), target.size() / 10);
			//Get candidate;
			for (int j = 0; j < size_feature; j++) {
				if (j != k) {
					vector<double> candidate = candidates[j];

					double newbest = _dtw->fastdynamic(target, candidate);
					counting++;
					if (newbest < bestsofar) {
						//cout << " we found (L1 norm) ["<< k <<"] = " << newbest << endl;
						bestsofar = newbest;
					}
				}
			}
			target.clear();
		}

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "Total DTW comparsion = " << counting << endl;
		cout << "FastDTW completed! [" << elapsed_secs << " seconds]" << endl;
	}
	catch (Exception^ e)
	{
		if (dynamic_cast<FileNotFoundException^>(e))
			Console::WriteLine("file '{0}' not found", fileName);
		else
			Console::WriteLine("problem reading file '{0}'", fileName);
	}
}

System::Void OpenCV_JP::frmDTW::backgroundWorkerLBImproved_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{

	String^ fileName = this->lbPath->Text;
	try
	{
		clock_t begin = clock();
		Console::WriteLine("trying to open file {0}...", fileName);
		StreamReader^ din = File::OpenText(fileName);

		String^ str;

		vector<vector<double>> candidates;


		while ((str = din->ReadLine()) != nullptr)
		{
			string str1;
			to_str(str, str1);
			vector<string> v{ explode(str1, ' ') };
			vector<double> candidate;

			int size = v.size();
			for (int i = 0; i < size; i++) {
				candidate.push_back(stod(v[i]));
			}

			candidates.push_back(candidate);
		}

		int size_feature = candidates.size();
		int compare = size_feature;
		long counting = 0;
		vector<double> target;
		double bestsofar = 10000000;

		for (int k = 0; k < compare; k++) {
			LB_Improved *filter;
			bestsofar = 10000000;
			//Set target
			target = candidates[k];

			filter = new LB_Improved(target, target.size() / 10);

			bestsofar = filter->getLowestCost();
			//Get candidate;
			for (int j = 0; j < size_feature; j++) {
				if (j != k) {
					vector<double> candidate = candidates[j];

					double newbest = filter->test(candidate);
					if (newbest < bestsofar) {
						//std::cout << " we found a new nearest neighbor, distance (L1 norm) = " << newbest << std::endl;
						//cout << "Times calla dtw " << filter->getNumberOfDTW() << endl;
						bestsofar = newbest;
					}
				}
			}
			counting += filter->getNumberOfDTW();
			target.clear();
		}

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "Total DTW comparsion = " << counting << endl;
		cout << "LB Improved completed! [" << elapsed_secs << " seconds]" << endl;
	}
	catch (Exception^ e)
	{
		if (dynamic_cast<FileNotFoundException^>(e))
			Console::WriteLine("file '{0}' not found", fileName);
		else
			Console::WriteLine("problem reading file '{0}'", fileName);
	}
}

const void to_str(System::String^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}