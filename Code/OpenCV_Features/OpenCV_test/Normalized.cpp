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
	AST /= new_order;
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

void Normalized::BaseLineDetection(Mat src, int& upperBaseLine, int& lowerBaseLine)
{
	int size = src.rows;
	vector<int> vertical_projection;
	int count;
	int peak_line = 0;
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


}

void Normalized::SkewDetectionUsesCentreOfMass(int upper_part_1, int lower_part_1, int upper_part_2, int lower_part_2)
{
	vector<cv::Point> pts;
	pts.push_back(cv::Point(0, upper_part_1));
	pts.push_back(cv::Point(this->word.cols, upper_part_2));
	pts.push_back(cv::Point(this->word.cols, lower_part_2));
	pts.push_back(cv::Point(0, lower_part_1));

	MatModifies matMod;
	Mat word_removed_baseline = matMod.cut(this->word, pts);
	//cv::Rect crop(0, this->upperBaseLine, this->word.cols, this->lowerBaseLine-this->upperBaseLine);
	// = this->word.clone();

	//imwrite("D:/word_removed_baseline.jpg", word_removed_baseline);
	int x_CoM_left, x_CoM_right;
	int y_CoM_left, y_CoM_right;
	x_CoM_left = this->xCentroid(0, 0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	x_CoM_right = this->xCentroid(word_removed_baseline.cols / 2, 0, word_removed_baseline.cols, word_removed_baseline.rows);
	y_CoM_left = this->yCentroid(0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	y_CoM_right = this->yCentroid(word_removed_baseline.cols / 2, word_removed_baseline.cols, word_removed_baseline.rows);
	float slope = float (y_CoM_right - y_CoM_left)/(x_CoM_right - x_CoM_left);
	//float slope = -10;
	float theta =  atan(slope) * 180 / M_PI;

	//cout << "left (x, y) = (" << x_CoM_left << ", "<< y_CoM_left << ")"<< endl;
	//cout << "right (x, y) = (" << x_CoM_right << ", " << y_CoM_right << ")" << endl;
	//cout << "slope = " << slope << endl;
	//cout << "theta = " << theta << endl;

	cv::Point2f ptCp(0, 0);
	cv::Mat M = cv::getRotationMatrix2D(ptCp, theta, 1);
	cv::warpAffine(word, word, M, word.size(), INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255)); //Nearest is too rough, 
	
	//imshow("Rotate", word);
	//imwrite("D:/Rotate.jpg", word);
}


void Normalized::SkewDetectionUsesCentreOfMass(int upper, int lower)
{
	cv::Rect crop(0, upper, this->word.cols, lower);
	Mat word_removed_baseline = this->word.clone();

	//imwrite("D:/word_removed_baseline.jpg", word_removed_baseline);
	int x_CoM_left, x_CoM_right;
	int y_CoM_left, y_CoM_right;
	x_CoM_left = this->xCentroid(0, 0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	x_CoM_right = this->xCentroid(word_removed_baseline.cols / 2, 0, word_removed_baseline.cols, word_removed_baseline.rows);
	y_CoM_left = this->yCentroid(0, word_removed_baseline.cols / 2, word_removed_baseline.rows);
	y_CoM_right = this->yCentroid(word_removed_baseline.cols / 2, word_removed_baseline.cols, word_removed_baseline.rows);
	float slope = float(y_CoM_right - y_CoM_left) / (x_CoM_right - x_CoM_left);
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
}

int Normalized::xCentroid(int x_start, int y_start, int NC, int NR)
{
	int xCentroid;
	int n = 0;
	int sum = 0;
	for (int i = x_start; i < NC; i++)
	{
		for (int j = y_start; j < NR; j++)
		{
			Scalar intensity = this->word.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
			{
				sum += i;
				n++;
			}
		}
	}
	xCentroid = round(sum / n);
	return xCentroid;
}

int Normalized::yCentroid(int x_start, int NC, int NR)
{
	int yCentroid;
	int n = 0;
	int sum = 0;
	for (int i = x_start; i < NC; i++)
	{
		for (int j = 0; j < NR; j++)
		{
			Scalar intensity = this->word.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD_INK)
			{
				sum += j;
				n++;
			}

		}
	}
	yCentroid = round(sum / n);
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