#include "frmNormalization.h"
#include <opencv2/opencv.hpp>
#include <iomanip>
#include "Test.h"
#include "MatModifies.h"
#include "Normalized.h"
#define DATASET_SIZE 100
#define SKEW_MIN 7
#define SKEW_MAX 12

const Mat addSkewAndLine(Mat, bool);
const Mat addLine(Mat mat);
const vector<string> explode(const string& s, const char& c);
const void readDatabase(vector<Test>& database);
const void makeDataset(vector<Test>& dataset, vector<Test> database);
const void writeAndClearData(vector<Test>& dataset, string output_path);

System::Void OpenCV_JP::frmNormalization::btnCreateDS1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	srand(time(NULL));
	Extent* extent = new Extent();
	string output_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_1", output_path);
	vector<Test> database;
	readDatabase(database);

	vector<Test> dataset1;
	makeDataset(dataset1, database);

	writeAndClearData(dataset1, output_path);
	database.clear();
}

System::Void OpenCV_JP::frmNormalization::btnCreateDS2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	srand(time(NULL));
	Extent* extent = new Extent();
	string output_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_2", output_path);
	vector<Test> database;
	readDatabase(database);

	vector<Test> dataset2;
	makeDataset(dataset2, database);

	int dataset2_size = dataset2.size();
	for (int i = 0; i < dataset2_size; i++) {
		Test el = dataset2[i];
		Mat image_skewed = addSkewAndLine(el.getImage(), false);
		dataset2[i].setImage(image_skewed);
	}

	writeAndClearData(dataset2, output_path);
	database.clear();
}

System::Void OpenCV_JP::frmNormalization::btnCreateDS3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	srand(time(NULL));
	Extent* extent = new Extent();
	string output_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_3", output_path);
	vector<Test> database;
	readDatabase(database);

	vector<Test> dataset3;
	makeDataset(dataset3, database);

	int dataset3_size = dataset3.size();
	for (int i = 0; i < dataset3_size; i++) {
		Test el = dataset3[i];
		Mat image_skewed = addSkewAndLine(el.getImage(), true);
		dataset3[i].setImage(image_skewed);
	}

	writeAndClearData(dataset3, output_path);
	database.clear();
}

System::Void OpenCV_JP::frmNormalization::btnNormDS1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	clock_t begin = clock();

	Extent* extent = new Extent();
	string input_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_1", input_path);

	for (auto i = fs::recursive_directory_iterator(input_path);
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
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
			Normalized normalized(img_org);

			normalized.MeasurementOfAverageStrokeThickness();
			int upper, lower;
			normalized.BaseLineDetection(normalized.getWord(), upper, lower);
			Mat center = normalized.SkewDetectionUsesCentreOfMass(upper, lower);


			//saving
			vector<string> arrPath = extent->split(str, '\\');
			std::string savePath = "D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_1_result\\" + arrPath.back();
			imwrite(savePath, normalized.getWord());
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	MessageBox::Show(L"Chuẩn hóa Dataset 1 thành công!!! [" + elapsed_secs + " giây]");
}

System::Void OpenCV_JP::frmNormalization::btnNormDS2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	clock_t begin = clock();

	Extent* extent = new Extent();
	string input_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_2", input_path);

	for (auto i = fs::recursive_directory_iterator(input_path);
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
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
			Normalized normalized(img_org);

			normalized.MeasurementOfAverageStrokeThickness();
			int upper, lower;
			normalized.BaseLineDetection(normalized.getWord(), upper, lower);
			Mat center = normalized.SkewDetectionUsesCentreOfMass(upper, lower);


			//saving
			vector<string> arrPath = extent->split(str, '\\');
			std::string savePath = "D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_2_result\\" + arrPath.back();
			imwrite(savePath, normalized.getWord());
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	MessageBox::Show(L"Chuẩn hóa Dataset 2 thành công!!! [" + elapsed_secs + " giây]");
}

System::Void OpenCV_JP::frmNormalization::btnNormDS3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	clock_t begin = clock();

	Extent* extent = new Extent();
	string input_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_3", input_path);

	for (auto i = fs::recursive_directory_iterator(input_path);
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
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
			Normalized normalized(img_org);

			normalized.MeasurementOfAverageStrokeThickness();
			normalized.StraightLineRemoval();
			normalized.MeasurementOfAverageStrokeThickness();
			int upper, lower;
			normalized.BaseLineDetection(normalized.getWord(), upper, lower);
			normalized.UnderlineRemoval();
			Mat center = normalized.SkewDetectionUsesCentreOfMass(upper, lower);

			normalized.MeasurementOfAverageStrokeThickness();
			normalized.StraightLineRemoval();
			normalized.MeasurementOfAverageStrokeThickness();
			normalized.BaseLineDetection(normalized.getWord(), upper, lower);
			normalized.UnderlineRemoval();

			//saving
			vector<string> arrPath = extent->split(str, '\\');
			std::string savePath = "D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_3_result\\" + arrPath.back();
			imwrite(savePath, normalized.getWord());
		}
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	MessageBox::Show(L"Chuẩn hóa Dataset 3 thành công!!! [" + elapsed_secs + " giây]");
}

System::Void OpenCV_JP::frmNormalization::btnCreateDS4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	srand(time(NULL));
	Extent* extent = new Extent();
	string output_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_4", output_path);
	vector<Test> database;
	readDatabase(database);

	vector<Test> dataset4;
	makeDataset(dataset4, database);

	int dataset4_size = dataset4.size();
	for (int i = 0; i < dataset4_size; i++) {
		Test el = dataset4[i];
		Mat image_skewed = addLine(el.getImage());
		dataset4[i].setImage(image_skewed);
	}

	writeAndClearData(dataset4, output_path);
	database.clear();
}

System::Void OpenCV_JP::frmNormalization::btnNormDS4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	clock_t begin = clock();

	Extent* extent = new Extent();
	string input_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_4", input_path);

	for (auto i = fs::recursive_directory_iterator(input_path);
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
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
			Normalized normalized(img_org);

			normalized.MeasurementOfAverageStrokeThickness();
			normalized.StraightLineRemoval();
			normalized.MeasurementOfAverageStrokeThickness();
			int upper, lower;
			normalized.BaseLineDetection(normalized.getWord(), upper, lower);
			normalized.UnderlineRemoval();
			Mat center = normalized.SkewDetectionUsesCentreOfMass(upper, lower);


			//saving
			vector<string> arrPath = extent->split(str, '\\');
			std::string savePath = "D:\\Thesis\\Chu_viet_tay\\Experiments\\Normalized\\Dataset_4_result\\" + arrPath.back();
			imwrite(savePath, normalized.getWord());
		}
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	MessageBox::Show(L"Chuẩn hóa Dataset 4 thành công!!! [" + elapsed_secs + " giây]");
}

const Mat addLine(Mat mat) {
	cv::Size size = mat.size();
	cv::line(mat, cv::Point(0, size.height / 2), cv::Point(size.width, size.height / 2), cv::Scalar(0, 0, 0), 4);
	return mat;
}

const Mat addSkewAndLine(Mat mat, bool addLine) {
	if (addLine) {
		cv::Size size = mat.size();
		cv::line(mat, cv::Point(0, size.height / 2), cv::Point(size.width,size.height /2), cv::Scalar(0, 0, 0), 4);
	}

	Mat mat1 = Mat(cv::Size(mat.size().width + 100, mat.size().height + 100), CV_8UC1, Scalar(255, 255, 255));;
	Mat rs = mat1.clone();
	mat.copyTo(mat1(cv::Rect(mat.size().width / 2, 50, mat.cols, mat.rows)));

	int theta = rand() % SKEW_MAX + SKEW_MIN;
	int dir = rand() % 2;
	if (dir == 1) {
		theta = -theta;
	}
	cv::Point2f ptCp(0, 0);
	cv::Mat M = cv::getRotationMatrix2D(ptCp, theta, 1);
	cv::warpAffine(mat1, rs, M, mat1.size(), INTER_CUBIC, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));

	MatModifies matModifies;
	int x_min_word, y_min_word, x_max_word, y_max_word;
	matModifies.findMinMax(rs, x_min_word, y_min_word, x_max_word, y_max_word);
	rs = matModifies.cropImage(rs, x_min_word, y_min_word, x_max_word, y_max_word);
		return rs;
}
const void readDatabase(vector<Test>& database) {
	Extent* extent = new Extent();
	string input_path;
	extent->MarshalString("D:\\Thesis\\Chu_viet_tay\\Experiments\\Clustering\\data_normal", input_path);

	for (auto i = fs::recursive_directory_iterator(input_path);
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
			Mat img_org = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
			Test el(str);
			el.setImage(img_org);
			database.push_back(el);
		}
	}
}


const void makeDataset(vector<Test>& dataset, vector<Test> database) {
	int loop = 0;
	int size_database = database.size();
	while (loop < DATASET_SIZE) {

		int idx = rand() % size_database;
		Test el = database[idx];
		if (!el.isChecked()) {
			dataset.push_back(el);

			el.setCheck(true);
			database[idx] = el;
			loop++;
		}
	}
}


const void writeAndClearData(vector<Test>& dataset, string output_path) {
	for (int j = 0; j < DATASET_SIZE; j++)
	imwrite(output_path + "\\" + dataset[j].getPathMd5() + ".jpg", dataset[j].getImage());

	dataset.clear();
}