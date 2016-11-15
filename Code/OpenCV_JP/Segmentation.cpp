#include "Segmentation.h"

Segmentation::Segmentation(Mat src)
{
	this->obstructing = new Obstructing();
	this->src = src.clone();
}

void Segmentation::normalized()
{
	//Khởi tạo size(width, height) gốc
	cv::Size s = this->src.size();
	this->height = s.height;
	this->width = s.width;
	//Chuẩn hóa lại size cho phù hợp
	if (this->width % NUMBER_OF_COLUMNS != 0) {
		//Size chuẩn hóa (theo chiều width) += số cột - width % số cột
		this->width += NUMBER_OF_COLUMNS - this->width % NUMBER_OF_COLUMNS;
		//gọi hàm resize hình
		resize(this->src, this->src, cv::Size(this->width, this->height), 0, 0);
	}

	//In ra cmd
	cout << "Orginal size [" << this->width << ", " << this->height << "]" << endl;
	cout << "Normalized size [" << this->width << ", " << this->height << "]" << endl;
}

void Segmentation::init()
{
	//Khởi tạo độ lớn của mảng cấu trúc dữ liệu
	this->elements = new Element[NUMBER_OF_COLUMNS*this->height];

	//Khởi tạo một ảnh dist màu trắng dạng màu mức xám - đây là ảnh dùng để lưu y-projection của toàn bộ trang văn bản
	this->dist = Mat(this->height, this->width, CV_8UC3, Scalar(255, 255, 255));
	cvtColor(this->dist, this->dist, COLOR_BGR2GRAY);

	//Thực hiện đếm số lượng điểm ảnh trên ảnh gốc src vào mapping qua ảnh kết quả dist
	this->width_size = this->width / NUMBER_OF_COLUMNS;
	int current_group = 0;
	int row = 0;
	int col = 0;
	int count = 0;
	long index = 0;

	//Duyệt và lần lượt đếm
	for (int i = 0; i < this->height; i++)
	{
		row = i;
		col = 0;
		current_group = 0;

		for (int j = 0; j < this->width; j++)
		{
			Scalar intensity = this->src.at<uchar>(i, j);
			if (intensity[0] <= THRESHOLDING) {
				this->dist.at<uchar>(row, col) = 0;
				col++;
				count++;
			}//if

			if (((j + 1) % width_size) == 0) {
				index = current_group * this->height + i;
				this->elements[index].setOrder(current_group);
				this->elements[index].setX((j + 1) - width_size);
				this->elements[index].setY(i);
				this->elements[index].setIntensity(count);

				current_group++;
				col = current_group * width_size;
				count = 0;
			}//if
		}//for j
	}//for i
}

void Segmentation::movingAverageFilter()
{
	//Khởi tạo lại giá trị dist và các biến có liên quan
	this->dist = Mat(this->height, this->width, CV_8UC3, Scalar(255, 255, 255));
	cvtColor(this->dist, this->dist, COLOR_BGR2GRAY);
	long index = 0;

	//Tính MAF từng cột với bộ chập M phần tử
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		for (int j = 0; j < this->height; j++) {

			index = i * this->height + j;
			float avg_val = 0;
			//Tổng của M phần tử
			for (int z = 0; z < this->kernelMAF; z++)
			{
				avg_val += (j + z < this->height) ? this->elements[index + z].getIntensity() : 0;
			}//for z

			 //Làm tròn số nguyên
			avg_val = round(avg_val /= this->kernelMAF);
			this->elements[index].setIntensity(avg_val);
			if (avg_val != 0) {
				cv::line(this->dist, cv::Point(i*width_size, j), cv::Point(i*width_size + avg_val, j), Scalar(0, 0, 0));
			}//if
		}//for j
	}//for i
}

void Segmentation::findValley()
{
	long index = 0;
	int y_valley = -1;
	//
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		y_valley = -1;
		for (int j = 0; j < this->height; j++) {
			index = i * this->height + j;
			int j_cur = this->elements[index].getIntensity();
			int j_1 = (j + 1 < this->height) ? this->elements[index + 1].getIntensity() : 0;
			int j_2 = (j + 2 < this->height) ? this->elements[index + 2].getIntensity() : 0;
			int j_3 = (j + 3 < this->height) ? this->elements[index + 3].getIntensity() : 0;
			//Dòng bình thường
			if ((j_cur <= 2) &
				(j_1 + j_2 + j_3 >= 6) &
				(j_1 <= j_2 & j_2 <= j_3) &
				(j_1 >= 1 & j_2 >= 2 & j_3 >= 3) &
				(y_valley == -1 | (j - y_valley) >= this->heigh_of_line)) {
				y_valley = j;
				this->elements[index].setValley(true);
				//
				if (this->isPunctuationMarkValley(y_valley, i)) {
					this->elements[index].setPunctuationMarks(true);
				}
			}
			//Dong dau tien
			else if (j == 0 &
				j_cur != 0 &
				(j_1 + j_2 + j_3 >= 6) &
				(j_1 >= 1 & j_2 >= 2 & j_3 >= 3)) {
				y_valley = j;
				this->elements[index].setValley(true);
				//
				if (this->isPunctuationMarkValley(y_valley, i)) {
					this->elements[index].setPunctuationMarks(true);
				}
			}
			//Dòng bất bình thường
			else if (j_cur <= 4 &
				(j_1 + j_2 + j_3 >= 12) &
				(j_1 <= j_2 & j_2 <= j_3) &
				(j_1 >= 3 & j_2 >= 4 & j_3 >= 5) &
				(y_valley == -1 | (j - y_valley) >= this->heigh_of_line)) {
				y_valley = j;
				this->elements[index].setValley(true);
				//
				if (this->isPunctuationMarkValley(y_valley, i)) {
					this->elements[index].setPunctuationMarks(true);
				}
			}
		}//for j
	}//for i

	this->drawValleys();
}

void Segmentation::connectValley()
{
	long index = 0;
	long idxNext = 0;
	long idxConnect = 0;

	//
	for (int i = 0; i < NUMBER_OF_COLUMNS - 1; i++)
	{
		for (int j = 0; j < this->height; j++) {
			index = i * this->height + j;

			if (this->elements[index].isValley() & this->setConnect(index, i + 1) & !this->elements[index].isDoneNext()) {
				idxConnect = this->elements[index].getIdxConnect();
				if (!this->elements[idxConnect].isDonePre()) {
					//	cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point((i + 1)*width_size, this->elements[index].getY()), Scalar(220, 0, 0));
					//	cv::line(this->src, cv::Point((i + 1)*width_size, this->elements[index].getY()), cv::Point(this->elements[idxConnect].getX(), this->elements[idxConnect].getY()), Scalar(220, 0, 0));
					this->elements[index].setCorner(cv::Point((i + 1)*width_size, this->elements[index].getY()));
					this->elements[index].setDoneNext(true);
					this->elements[index].setIterator(true);
					this->elements[idxConnect].setDonePre(true);
				}//if
				else {
					this->elements[index].setIdxConnect(-1);
				}
			}//if
		}
	}//for i

	bool isConnected = false;
	int count = 0;
	int loop = 5;
	for (int u = 0; u < loop; u++) {
		for (int i = 0; i < NUMBER_OF_COLUMNS - 1; i++)
		{
			count = 0;
			for (int j = 0; j < this->height; j++) {
				index = i * this->height + j;
				if (this->elements[index].isValley() &
					this->elements[index].isDonePre() &
					!this->elements[index].isDoneNext()) {

					for (int z = i + 1; z < NUMBER_OF_COLUMNS; z++) {
						for (int k = 0; k < this->height; k++) {
							idxNext = z * this->height + k;
							if (abs(k - j) <= this->heigh_of_line*(MIN_PROBABILITY + (float)u / 10) &
								this->elements[idxNext].isValley() &
								this->elements[idxNext].isDoneNext() &
								!this->elements[idxNext].isDonePre()) {

								//	cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point((z)*width_size, this->elements[index].getY()), Scalar(220, 0, 0));
								////	cv::line(this->src, cv::Point((z)*width_size, this->elements[index].getY()), cv::Point(this->elements[idxNext].getX(), this->elements[idxNext].getY()), Scalar(220, 0, 0));
								this->elements[index].setCorner(cv::Point((z)*width_size, this->elements[index].getY()));
								this->elements[index].setDoneNext(true);
								this->elements[index].setIdxConnect(idxNext);
								this->elements[index].setIterator(true);
								this->elements[idxNext].setDonePre(true);
								isConnected = true;
								count++;
								break;
							}//if
						}
						if (isConnected) {
							isConnected = false;
							break;
						}
					}

				}
			}
		}
	}

	//Ke cac duong con lai
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (int j = 0; j < this->height; j++) {
			index = i * this->height + j;
			if (this->elements[index].isValley() &
				!this->elements[index].isDonePre() &
				this->elements[index].isDoneNext()) {
				this->elements[index].setIterator(true);
				//	cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point(0, this->elements[index].getY()), Scalar(220, 0, 0));
			}
			else if (this->elements[index].isValley() &
				this->elements[index].isDonePre() &
				!this->elements[index].isDoneNext()) {
				this->elements[index].setIterator(true);
				//	cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point(this->width, this->elements[index].getY()), Scalar(220, 0, 0));
			}
		}
	}

	this->drawConnects();
}

bool Segmentation::setConnect(long idx, int id_w_i_plus)
{
	//Trung bình khoảng cách
	double currDistance = 0;
	double MD2NV = this->getHeight();//Minimum Distance to Normal Valley
	long index = 0;
	long idxConnect = 0;

	//
	for (int i = 0; i < this->height; i++)
	{
		index = id_w_i_plus * this->height + i;

		if (this->elements[index].isValley()) {
			currDistance = this->distance(this->elements[index].getY(), this->elements[idx].getY());
			if (MD2NV > currDistance) {
				MD2NV = currDistance;
				idxConnect = index;
			}
		}
	}//for i

	if (MD2NV <= this->heigh_of_line * ((this->elements[idxConnect].isPunctuationMarks() | this->elements[idx].isPunctuationMarks()) ? MAX_PROBABILITY : AVG_PROBABILITY)) {
		this->elements[idx].setIdxConnect(idxConnect);
		this->elements[idx].setMinDistance(MD2NV);
		return true;
	}
	return false;
}

double Segmentation::distance(int y1, int y2)
{
	return abs(y1 - y2);//a half of Manhattan
}

bool Segmentation::isPunctuationMarkValley(int y, int w)
{
	int ASCENDERS_HEIGHT = this->heigh_of_line / 4;
	int MAX_THRESHOLD_NOPs = ASCENDERS_HEIGHT*((ASCENDERS_HEIGHT + 1) / 2); //NOPs = Number Of Pixels
	int MIN_THRESHOLD = MAX_THRESHOLD_NOPs * 2;
	int countNOPs = 0;
	long index;
	int counter = 0;
	int currIntensity = this->elements[w * this->height + y].getIntensity();
	countNOPs = currIntensity;

	//
	for (int j = y + 1; j < this->height; j++) {
		index = w * this->height + j;

		if (currIntensity > this->elements[index].getIntensity()) {
			if (counter <= ASCENDERS_HEIGHT & countNOPs <= MAX_THRESHOLD_NOPs) {
				countNOPs = 0;
				//count NOPs after ASCENDERS
				for (int i = j; i < this->height & i < j + (this->heigh_of_line * AVG_PROBABILITY); i++) {
					index = w * this->height + i;
					countNOPs += this->elements[index].getIntensity();
				}//for i

				if (countNOPs > MIN_THRESHOLD)
					return true;
				else
					return false;
			}//end if counter <= ASCENDERS_HEIGHT & countNOPs <= MAX_THRESHOLD_NOPs
			else {
				return false;
			}
		}//end if
		else if (currIntensity < this->elements[index].getIntensity()) {
			currIntensity = this->elements[index].getIntensity();
			countNOPs += currIntensity;
			counter++;
		}//end else if
	}//for j
	return false;
}

void Segmentation::drawValleys()
{
	long index = 0;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i * this->height + j;
			if (this->elements[index].isValley()) {
				if (this->elements[index].isPunctuationMarks()) {
					cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(220, 0, 0));
				}
				else {
					cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(0, 0, 0));
				}
			}//if
		}//for j
	}//for i
}

void Segmentation::drawConnects()
{
	//init
	long index = 0;
	int ln = 0;
	int x_max = 0;
	int y_max = 0;
	int x_min = this->width;
	int y_min = this->height;
	vector<vector<cv::Point>> lines;
	DrawDecision drawDecision;
	ShortestPath shortest(this->src);
	MatModifies matModifies;
	//Obstructing obstructing;
	//obstructing.setSrc(this->src);

	//Iterator
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		for (int j = 0; j < this->height; j++) {
			index = i * this->height + j;
			long idx = this->elements[index].getIdxConnect();
			//
			if (idx != -1 & this->elements[index].isIterator() &
				this->elements[index].isDoneNext()) {
				vector<cv::Point> line;

				if (!this->elements[index].isDonePre()) {
					line.push_back(cv::Point(0, this->elements[index].getY()));
					cout << "==== first " << 0 << ", " << this->elements[index].getY() << " =====" << endl;
				}
				else {
					line.push_back(cv::Point(this->elements[index].getX(), this->elements[index].getY()));
					cout << "line = " << ln << "| X,Y= " << this->elements[index].getX() << ", " << this->elements[index].getY() << endl;
				}
				line.push_back(this->elements[index].getCorner());

				this->elements[index].setIterator(false);

				while (this->elements[idx].isIterator() & this->elements[idx].isDonePre()) {
					line.push_back(cv::Point(this->elements[idx].getX(), this->elements[idx].getY()));
					if (!this->elements[idx].isDoneNext()) {
						line.push_back(cv::Point(this->width, this->elements[idx].getY()));
						cout << "==== end " << this->width << ", " << this->elements[idx].getY() << " =====" << endl;
					}
					else {
						line.push_back(this->elements[idx].getCorner());
						cout << "line = " << ln << "| X,Y= " << this->elements[idx].getX() << ", " << this->elements[idx].getY() << endl;
					}

					this->elements[idx].setIterator(false);
					idx = this->elements[idx].getIdxConnect();
				}
				cout << endl;
				ln++;

				lines.push_back(line);
			}//if
		}//for j
	}//for i

	 //Sort by first element in vector
	std::sort(lines.begin(), lines.end(),
		[](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
		return a[0].y < b[0].y;
	});

	//Erase vector<cv::Point> has less than 5 elements
	lines.erase(std::remove_if(
		lines.begin(), lines.end(),
		[](std::vector<cv::Point>& a) {
		return a.size() < 5;
	}), lines.end());
	// Tiến hành kiếm tra kẻ có cắt chữ
	int s = (int)lines.size();
	for (vector<int>::size_type m = 0; m != s; m++) {
		vector<cv::Point> el = lines.at(m);
		int s_el = (int)el.size();
		for (vector<int>::size_type k = 0; k != s_el - 1; k++) {
			matModifies.addPts(this->src, el.at(k), el.at(k + 1), this->heigh_of_line);
		}
	}


	//Concat two vectors and cut image
	int numline = 1;

	for (vector<int>::size_type m = 0; m != s - 1; m++) {
		vector<cv::Point> el = lines.at(m);
		std::reverse(el.begin(), el.end());
		vector<cv::Point> pts;
		pts.insert(pts.end(), lines.at(m + 1).begin(), lines.at(m + 1).end());
		pts.insert(pts.end(), el.begin(), el.end());

		Mat rs = matModifies.cut(src, pts);

		string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line" + std::to_string(numline) + ".jpg";
		imwrite(savePath, rs);
		numline++;

		if (m + 1 == s - 1) {
			pts.clear();
			vector<cv::Point> end_line;
			end_line.push_back(cv::Point(this->width, this->height));
			end_line.push_back(cv::Point(0, this->height));
			el = lines.at(m + 1);

			pts.insert(pts.end(), el.begin(), el.end());
			pts.insert(pts.end(), end_line.begin(), end_line.end());
			Mat rs = matModifies.cut(src, pts);

			string savePath = "D:/Thesis/Chu_viet_tay/Outputs/Obstructing/line" + std::to_string(numline) + ".jpg";
			imwrite(savePath, rs);
		}
	}
}

void Segmentation::setSrc(Mat src)
{
	this->src = src.clone();
}

void Segmentation::setDist(Mat dist)
{
	this->dist = dist.clone();
}

void Segmentation::setHeight(unsigned int height)
{
	this->height = height;
}

void Segmentation::setWidth(unsigned int width)
{
	this->width = width;
}

void Segmentation::setHeighOfLine(int heigh_of_line)
{
	this->heigh_of_line = heigh_of_line;
}

void Segmentation::setKernelMAF(int kernelMAF)
{
	this->kernelMAF = kernelMAF;
}

Mat Segmentation::getSrc()
{
	return this->src;
}

Mat Segmentation::getDist()
{
	return this->dist;
}

unsigned int Segmentation::getHeight()
{
	return this->height;
}

unsigned int Segmentation::getWidth()
{
	return this->width;
}

int Segmentation::getHeighOfLine()
{
	return this->heigh_of_line;
}

int Segmentation::getKernelMAF()
{
	return this->kernelMAF;
}