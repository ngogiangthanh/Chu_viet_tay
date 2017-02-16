#include "Normalized.h"


Normalized::Normalized(Mat word)
{
	this->word = word.clone();
}

void Normalized::MeasurementOfAverageStrokeThickness()
{

	int size = this->word.cols*this->word.rows;
	int* val = new int[size];
	int sum = 0;
	int order = 0;
	int ast = 0;

	for (int i = 0; i < this->word.cols; i++)
	{
		for (int j = 0; j < this->word.rows; j++)
		{
			Scalar intensity = this->word.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
				sum++;
			else {
				if (sum != 0 & sum < this->word.rows / 2) {
					//them vao mang
					val[order++] = sum;
					ast += sum;
				}
				sum = 0;
			}
		}

		if (sum != 0 & sum < this->word.rows / 2) {
			//them vao mang
			val[order++] = sum;
			ast += sum;
		}
		sum = 0;
	}
	ast /= order;
	//cout << "average stroke thickness = " << ast << endl;

	int new_order = 0;
	for (int i = 0; i < order; i++) {
		if (ast > val[i]) {
			//cout << val[i] << endl;
			AST += val[i];
			new_order++;
		}
	}
	AST /= new_order == 0 ? 1 : new_order;
	//cout << " new ast = " << AST << endl;
	delete[] val;
}

void Normalized::StraightLineRemoval()
{
	int sum = 0;
	int sum_rows = 0;

	for (int j = 0; j < this->word.rows; j++)
	{
		for (int i = 0; i < this->word.cols; i++)
		{
			Scalar intensity = this->word.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
				sum++;
			else {
				if (sum != 0 & sum > this->word.cols / 2) {
					for (int k = i - sum; k <= i; k++) {
						sum_rows = 0;
						for (int l = j; l < this->word.rows; l++) {
							intensity = this->word.at<uchar>(l, k);
							if (intensity[0] <= THRESHOLD_INK)
								sum_rows++;
							else {
								if (sum_rows != 0 & sum_rows <= AST)
									cv::line(this->word, cv::Point(k, j - 1), cv::Point(k, l), Scalar(255, 255, 255));
								sum_rows = 0;
								break;
							}
						}
					}
				}					
				sum = 0;
			}
		}
		if (sum != 0 & sum > this->word.cols / 2) {
			for (int k = this->word.cols - sum; k < this->word.cols; k++) {
				sum_rows = 0;
				for (int l = j; l < this->word.rows; l++) {
					Scalar intensity = this->word.at<uchar>(l, k);
					if (intensity[0] <= THRESHOLD_INK)
						sum_rows++;
					else {
						if (sum_rows != 0 & sum_rows <= AST)
							cv::line(this->word, cv::Point(k, j - 1), cv::Point(k, l), Scalar(255, 255, 255));
						sum_rows = 0;
						break;
					}
				}
			}
		}		
			sum = 0;
	}

	//imshow("straighline", this->word);
	///imwrite("D:/straighline.jpg", this->word);
}

void Normalized::BaseLineDetection(Mat &src, int& upperBaseLine, int& lowerBaseLine)
{
	int size = src.rows;
	vector<int> vertical_projection;
	int count;
	peak_line = 0;
	int max_value = 0;
	int average_number = 0;
	//tinh vertical_projection
	for (int j = 0; j < src.rows; j++) {
		count = 0;
		for (int i = 0; i < src.cols; i++) {
			Scalar intensity = src.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK) {
				count++;
			}
		}//end for j
		average_number += count;
		vertical_projection.push_back(count);
	}

	//Tính MAF từng cột với bộ chập M phần tử
	//Mat pp =  Mat(src.rows, src.cols, CV_8UC3, Scalar(255, 255, 255));
	//cvtColor(pp, pp, COLOR_BGR2GRAY);
	//for (int i = 0; i < size; i++) {
	//		float avg_val = 0;
	//		//Tổng của M phần tử
	//		for (int z = 0; z < 5; z++)
	//			avg_val += (i + z < size) ? vertical_projection.at(i + z) : 0;
	//		 //Làm tròn số nguyên
	//		avg_val = round(avg_val /= 3);
	//		vertical_projection.at(i) = avg_val;
	//		if (avg_val != 0)
	//			cv::line(pp, cv::Point(0, i), cv::Point(avg_val, i), Scalar(0, 0, 0));
	//}//for i

	//Tim peak_line
	auto biggest = std::max_element(std::begin(vertical_projection), std::end(vertical_projection));
	average_number /= size;
	peak_line = std::distance(std::begin(vertical_projection), biggest);
	max_value = *biggest;
	auto min_prior = std::min_element(vertical_projection.begin(), vertical_projection.begin() + peak_line);
	upperBaseLine = 0;
	lowerBaseLine = size;
	//tìm upperBaseline
	for (vector<int>::size_type k = *min_prior; k != peak_line; k++) {
		if (vertical_projection.at(k) >= average_number) {
			//baseline
			upperBaseLine = k;
			break;
		}
	}


	//Tim lowerBaseLine
	int size_pp = vertical_projection.size();
	int min = max_value;
	int minPixY = size_pp;
	for (vector<int>::size_type k = peak_line; k != size_pp; k++) {
		if (vertical_projection.at(k) < min) {
			min = vertical_projection.at(k);
			minPixY = k;
		}
	}

	int avgPixY = minPixY;
	for (int i = minPixY; i-- > peak_line; ) {
		if (vertical_projection.at(i) >= average_number) {
			//baseline
			lowerBaseLine = i;
			//avgPixY = i;
			break;
		}
	}

	/*if ((minPixY - avgPixY) < (avgPixY - upperBaseLine)) {
		lowerBaseLine = minPixY;
	}
	else {
		lowerBaseLine = avgPixY;
	}*/
	//cout << "upperBaseLine = " << upperBaseLine << endl;
	//cout << "lowerBaseLine = " << lowerBaseLine << endl;

	//cv::line(src, cv::Point(0, this->upperBaseLine), cv::Point(src.cols, this->upperBaseLine), Scalar(128, 128, 128));
	//cv::line(src, cv::Point(0, this->lowerBaseLine), cv::Point(src.cols, this->lowerBaseLine), Scalar(128, 128, 128));
	//imshow("Baseline ", src);
	//imwrite("D:/Baseline.jpg", src);

	//cout << "Max element is " << max_value
	//	<< " at position " << peak_line << std::endl;
	//cout << "Min element before peak line is " << *min_prior
	//	<< " at position " << std::distance(std::begin(vertical_projection), min_prior) << std::endl;
	//cout << "Min element after peak line is " << min
	//	<< " at position " << minPixY << std::endl;
	//cout << "average_number = " << average_number << endl;

	//src = pp;
}

Mat Normalized::SkewDetectionUsesCentreOfMass(int upper_part_1, int lower_part_1, int upper_part_2, int lower_part_2)
{
	vector<cv::Point> pts;
	pts.push_back(cv::Point(0, upper_part_1));
	//pts.push_back(cv::Point(this->word.cols/2, upper_part_1));
	//pts.push_back(cv::Point(this->word.cols / 2, upper_part_2));
	pts.push_back(cv::Point(this->word.cols, upper_part_2));
	pts.push_back(cv::Point(this->word.cols, lower_part_2));
	//pts.push_back(cv::Point(this->word.cols / 2, lower_part_2));
	//pts.push_back(cv::Point(this->word.cols / 2, lower_part_1));
	pts.push_back(cv::Point(0, lower_part_1));

	MatModifies matMod;

	Mat word_removed_baseline = matMod.cut(this->word, pts);

	//cv::Rect crop(0, this->upperBaseLine, this->word.cols, this->lowerBaseLine-this->upperBaseLine);
	// = this->word.clone();

	//imwrite("D:/word_removed_baseline.jpg", word_removed_baseline);
	int x_CoM_left, x_CoM_right;
	int y_CoM_left, y_CoM_right; 
	cv::line(word_removed_baseline, cv::Point(word_removed_baseline.cols / 2, 0), cv::Point(word_removed_baseline.cols / 2, word_removed_baseline.rows), Scalar(128, 128, 128));

	x_CoM_left = this->xCentroid(word_removed_baseline, 0, 0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	x_CoM_right = this->xCentroid(word_removed_baseline, word_removed_baseline.cols / 2, 0, word_removed_baseline.cols, word_removed_baseline.rows) + word_removed_baseline.cols / 2;
	y_CoM_left = this->yCentroid(word_removed_baseline, 0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	y_CoM_right = this->yCentroid(word_removed_baseline, word_removed_baseline.cols / 2, word_removed_baseline.cols, word_removed_baseline.rows);
	float slope = float (y_CoM_right - y_CoM_left)/(x_CoM_right - x_CoM_left);
	//float slope = -10;
	cv::line(word_removed_baseline, cv::Point(x_CoM_left, y_CoM_left), cv::Point(x_CoM_right, y_CoM_right), Scalar(128, 128, 128));
	float theta =  atan(slope) * 180 / M_PI;

	//cout << "left (x, y) = (" << x_CoM_left << ", "<< y_CoM_left << ")"<< endl;
	//cout << "right (x, y) = (" << x_CoM_right << ", " << y_CoM_right << ")" << endl;
	//cout << "slope = " << slope << endl;
	//cout << "theta = " << theta << endl;

	// get rotation matrix for rotating the image around its center
	//cv::Point2f ptCp(0, 0);
	cv::Point2f center(word.cols / 2.0, word.rows / 2.0);
	//cv::Mat M = cv::getRotationMatrix2D(ptCp, theta, 1);
	cv::Mat rot = cv::getRotationMatrix2D(center, theta, 1.0);
	// determine bounding rectangle
	cv::Rect bbox = cv::RotatedRect(center, word.size(), theta).boundingRect();
	// adjust transformation matrix
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

	//cv::Mat dst;
	//cv::warpAffine(src, dst, rot, bbox.size());


	//Mat word_skewed =  Mat(word.rows+10, word.cols+10, CV_8UC3, Scalar(255, 255, 255));
	//cvtColor(word_skewed, word_skewed, COLOR_BGR2GRAY);
	cv::warpAffine(word, word, rot, bbox.size(), INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255)); //Nearest is too rough, 
	//word = word_skewed.clone();
	//imshow("Rotate", word);
	//imwrite("D:/Rotate.jpg", word);
	return word_removed_baseline;
}


Mat Normalized::SkewDetectionUsesCentreOfMass(int upper, int lower)
{
	cout << "upper = " << upper << endl;
	cout << "lower = " << lower << endl;

	cv::Rect crop(0, upper, this->word.cols, lower - upper);
	Mat word_removed_baseline = this->word(crop).clone();
	//Mat word_removed_baseline = this->word.clone();

	//imwrite("D:/word_removed_baseline.jpg", word_removed_baseline);

	int x_CoM_left, x_CoM_right;
	int y_CoM_left, y_CoM_right;
	cv::line(word_removed_baseline, cv::Point(word_removed_baseline.cols / 2, 0), cv::Point(word_removed_baseline.cols / 2, word_removed_baseline.rows), Scalar(128, 128, 128));
	x_CoM_left = this->xCentroid(word_removed_baseline, 0, 0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	x_CoM_right = this->xCentroid(word_removed_baseline, word_removed_baseline.cols / 2, 0, word_removed_baseline.cols, word_removed_baseline.rows) + word_removed_baseline.cols / 2;
	y_CoM_left = this->yCentroid(word_removed_baseline, 0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	y_CoM_right = this->yCentroid(word_removed_baseline, word_removed_baseline.cols / 2, word_removed_baseline.cols, word_removed_baseline.rows);
	float slope = float(y_CoM_right - y_CoM_left) / (x_CoM_right - x_CoM_left);
	cv::line(word_removed_baseline, cv::Point(x_CoM_left, y_CoM_left), cv::Point(x_CoM_right, y_CoM_right), Scalar(128, 128, 128));
	//float slope = -10;
	float theta = atan(slope) * 180 / M_PI;

	//cout << "left (x, y) = (" << x_CoM_left << ", "<< y_CoM_left << ")"<< endl;
	//cout << "right (x, y) = (" << x_CoM_right << ", " << y_CoM_right << ")" << endl;
	//cout << "slope = " << slope << endl;
	//cout << "theta = " << theta << endl;

	cv::Point2f ptCp(0, 0);
	cv::Mat M = cv::getRotationMatrix2D(ptCp, theta, 1);
	cv::warpAffine(word, word, M, word.size(), INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255)); //Nearest is too rough, 

																											  //imshow("Rotate", word);
																											  //imwrite("D:/Rotate.jpg", word);

	return word_removed_baseline;
}

int Normalized::xCentroid(Mat mat,int x_start, int y_start, int NC, int NR)
{
	int xCentroid;
	int n = 0;
	int sum = 0;
	for (int i = x_start; i < NC; i++)
	{
		for (int j = y_start; j < NR; j++)
		{
			Scalar intensity = mat.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
			{
				sum += i - x_start;
				n++;
			}
		}
	}
	xCentroid = (n == 0) ? sum : round(sum / n);
	return xCentroid;
}

int Normalized::yCentroid(Mat mat, int x_start, int NC, int NR)
{
	int yCentroid;
	int n = 0;
	int sum = 0;
	for (int i = x_start; i < NC; i++)
	{
		for (int j = 0; j < NR; j++)
		{
			Scalar intensity = mat.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
			{
				sum += j;
				n++;
			}

		}
	}
	yCentroid = (n == 0) ? sum : round(sum / n);
	return yCentroid;
}

void Normalized::setWord(Mat word)
{
	this->word = word.clone();
}

Mat Normalized::getWord()
{
	return this->word;
}