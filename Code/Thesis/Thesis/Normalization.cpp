#include "Normalization.h"


Normalization::Normalization(Mat word)
{
	this->word = word.clone();
}

void Normalization::MeasurementOfAverageStrokeThickness()
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

void Normalization::StraightLineRemoval()
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

void Normalization::BaseLineDetection(Mat &src, int& upperBaseLine, int& lowerBaseLine)
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

Mat Normalization::SkewDetectionUsesCentreOfMass(int upper_part_1, int lower_part_1, int upper_part_2, int lower_part_2)
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
	float slope = float(y_CoM_right - y_CoM_left) / (x_CoM_right - x_CoM_left);
	//float slope = -10;
	cv::line(word_removed_baseline, cv::Point(x_CoM_left, y_CoM_left), cv::Point(x_CoM_right, y_CoM_right), Scalar(128, 128, 128));
	float theta = atan(slope) * 180 / M_PI;

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


Mat Normalization::SkewDetectionUsesCentreOfMass(int upper, int lower)
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

int Normalization::xCentroid(Mat mat, int x_start, int y_start, int NC, int NR)
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

int Normalization::yCentroid(Mat mat, int x_start, int NC, int NR)
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

void Normalization::setWord(Mat word)
{
	this->word = word.clone();
}

Mat Normalization::getWord()
{
	return this->word;
}

void Normalization::hough_transform(Mat& im, Mat& orig, double* skew)
{
	double max_r = sqrt(pow(.5*im.cols, 2) + pow(.5*im.rows, 2));
	int angleBins = 180;
	Mat acc = Mat::zeros(Size(2 * max_r, angleBins), CV_32SC1);
	int cenx = im.cols / 2;
	int ceny = im.rows / 2;
	for (int x = 1; x<im.cols - 1; x++)
	{
		for (int y = 1; y<im.rows - 1; y++)
		{
			if (im.at<uchar>(y, x) == 255)
			{
				for (int t = 0; t<angleBins; t++)
				{
					double r = (x - cenx)*cos((double)t / angleBins*CV_PI) + (y - ceny)*sin((double)t / angleBins*CV_PI);
					r += max_r;
					acc.at<int>(t, int(r))++;
				}
			}
		}
	}
	Mat thresh;
	normalize(acc, acc, 255, 0, NORM_MINMAX);
	convertScaleAbs(acc, acc);
	/*debug
	Mat cmap;
	applyColorMap(acc,cmap,COLORMAP_JET);
	imshow("cmap",cmap);
	imshow("acc",acc);*/

	Point maxLoc;
	minMaxLoc(acc, 0, 0, 0, &maxLoc);
	double theta = (double)maxLoc.y / angleBins*CV_PI;
	double rho = maxLoc.x - max_r;
	if (abs(sin(theta))<0.000001)//check vertical
	{
		//when vertical, line equation becomes
		//x = rho
		double m = -cos(theta) / sin(theta);
		Point2d p1 = Point2d(rho + im.cols / 2, 0);
		Point2d p2 = Point2d(rho + im.cols / 2, im.rows);
		line(orig, p1, p2, Scalar(0, 0, 255), 1);
		*skew = 90;
		cout << "skew angle " << " 90" << endl;
	}
	else
	{
		//convert normal form back to slope intercept form
		//y = mx + b
		double m = -cos(theta) / sin(theta);
		double b = rho / sin(theta) + im.rows / 2. - m*im.cols / 2.;
		Point2d p1 = Point2d(0, b);
		Point2d p2 = Point2d(im.cols, im.cols*m + b);
		line(orig, p1, p2, Scalar(0, 0, 255), 1);
		double skewangle;
		skewangle = p1.x - p2.x>0 ? (atan2(p1.y - p2.y, p1.x - p2.x)*180. / CV_PI) : (atan2(p2.y - p1.y, p2.x - p1.x)*180. / CV_PI);
		*skew = skewangle;
		cout << "skew angle " << skewangle << endl;
	}
}

Mat Normalization::preprocess1(Mat& im)
{
	Mat ret = Mat::zeros(im.size(), CV_32SC1);

	for (int x = 1; x<im.cols - 1; x++)
	{
		for (int y = 1; y<im.rows - 1; y++)
		{

			int gy = (im.at<uchar>(y - 1, x + 1) - im.at<uchar>(y - 1, x - 1))
				+ 2 * (im.at<uchar>(y, x + 1) - im.at<uchar>(y, x - 1))
				+ (im.at<uchar>(y + 1, x + 1) - im.at<uchar>(y + 1, x - 1));
			int gx = (im.at<uchar>(y + 1, x - 1) - im.at<uchar>(y - 1, x - 1))
				+ 2 * (im.at<uchar>(y + 1, x) - im.at<uchar>(y - 1, x))
				+ (im.at<uchar>(y + 1, x + 1) - im.at<uchar>(y - 1, x + 1));
			int g2 = (gy*gy + gx*gx);
			ret.at<int>(y, x) = g2;
		}
	}
	normalize(ret, ret, 255, 0, NORM_MINMAX);
	ret.convertTo(ret, CV_8UC1);
	threshold(ret, ret, 50, 255, THRESH_BINARY);
	return ret;
}

Mat Normalization::preprocess2(Mat& im)
{
	// 1) assume white on black and does local thresholding
	// 2) only allow voting top is white and buttom is black(buttom text line)
	Mat thresh;
	//thresh=255-im;
	thresh = im.clone();
	adaptiveThreshold(thresh, thresh, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, -2);
	/*int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_8UC1;
	cv::Laplacian(thresh, thresh, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);*/

	Mat ret = Mat::zeros(im.size(), CV_8UC1);
	for (int x = 1; x<thresh.cols - 1; x++)
	{
		for (int y = 1; y<thresh.rows - 1; y++)
		{
			bool toprowblack = thresh.at<uchar>(y - 1, x) == 0 || thresh.at<uchar>(y - 1, x - 1) == 0 || thresh.at<uchar>(y - 1, x + 1) == 0;
			bool belowrowblack = thresh.at<uchar>(y + 1, x) == 0 || thresh.at<uchar>(y + 1, x - 1) == 0 || thresh.at<uchar>(y + 1, x + 1) == 0;

			uchar pix = thresh.at<uchar>(y, x);
			if ((!toprowblack && pix == 255 && belowrowblack))
			{
				ret.at<uchar>(y, x) = 255;
			}
		}
	}
	return ret;
}
Mat Normalization::rot(Mat& im, double thetaRad)
{
	cv::Mat rotated;
	double rskew = thetaRad* CV_PI / 180;
	double nw = abs(sin(thetaRad))*im.rows + abs(cos(thetaRad))*im.cols;
	double nh = abs(cos(thetaRad))*im.rows + abs(sin(thetaRad))*im.cols;
	cv::Mat rot_mat = cv::getRotationMatrix2D(Point2d(nw*.5, nh*.5), thetaRad * 180 / CV_PI, 1);
	Mat pos = Mat::zeros(Size(1, 3), CV_64FC1);
	pos.at<double>(0) = (nw - im.cols)*.5;
	pos.at<double>(1) = (nh - im.rows)*.5;
	Mat res = rot_mat*pos;
	rot_mat.at<double>(0, 2) += res.at<double>(0);
	rot_mat.at<double>(1, 2) += res.at<double>(1);
	cv::warpAffine(im, rotated, rot_mat, Size(nw, nh), INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
	return rotated;
}

Mat Normalization::Skeleton(Mat img)
{
	Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
	int morph_element = MORPH_CLOSE;
	int operation = MORPH_RECT;
	int morph_size = 1;
	Mat element = getStructuringElement(operation, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

	// Apply the specified morphology operation
	morphologyEx(img, skel, morph_element, element);

	return skel;
}
