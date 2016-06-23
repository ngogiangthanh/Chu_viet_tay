#include "Segmentation.h"

Segmentation::Segmentation(Mat src)
{
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
	int M = 5;
	long index = 0;

	//Tính MAF từng cột với bộ chập M phần tử
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		for (int j = 0; j < this->height; j++) {

			index = i * this->height + j;
			float avg_val = 0;
			//Tổng của M phần tử
			for (int z = 0; z < M; z++)
			{
				avg_val += (j + z < this->height) ? this->elements[index + z].getIntensity() : 0;
			}//for z

			//Làm tròn số nguyên
			avg_val = round(avg_val /= M);
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
		int j = 0;
		y_valley = -1;

		while (j < this->height) {
			for (; j < (j + this->heigh_of_line / 2) & j < (this->height - 3); j++) {
				index = i * this->height + j;
				int j_cur = this->elements[index].getIntensity();
				int j_1 = this->elements[index + 1].getIntensity();
				int j_2 = this->elements[index + 2].getIntensity();
				int j_3 = this->elements[index + 3].getIntensity();
				//Dòng bình thường
				if ((y_valley == -1 | (j - y_valley) > this->heigh_of_line*0.75) & 
					(j_cur <= 1) & 
					(j_1 + j_2 + j_3 >= 6) & 
					(j_1 <= j_2 & j_2 <= j_3) & 
					(j_1 > 0 & j_2 > 0 & j_3 > 0)) {
					cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(50, 0, 0));
					y_valley = j;
					this->elements[index].setValley(true);
					//
					if (this->isPunctuationMarkValley(y_valley, i)) {
						this->elements[index].setPunctuationMarks(true);
						cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(200, 0, 0));
					}
					break;
				}
				//Dong dau tien
				else if (j == 0 & 
					j_cur != 0 & 
					(j_1 + j_2 + j_3 >= 6) & 
					(j_1 > 0 & j_2 > 0 & j_3 > 0)) {
					cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(50, 0, 0));
					y_valley = j;
					this->elements[index].setValley(true);
					//
					if (this->isPunctuationMarkValley(y_valley, i)) {
						this->elements[index].setPunctuationMarks(true);
						cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(200, 0, 0));
					}
					break;
				}
				//Dòng bất bình thường
				else if ((y_valley == -1 | (j - y_valley) > this->heigh_of_line*0.75) & 
					j_cur <= 5 & 
					(j_1 + j_2 + j_3 >= 21) & 
					(j_1 <= j_2 & j_2 <= j_3) & 
					(j_1 > 0 & j_2 > 0 & j_3 > 0)) {
					cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(50, 0, 0));
					y_valley = j;
					this->elements[index].setValley(true);
					//
					if (this->isPunctuationMarkValley(y_valley, i)) {
						this->elements[index].setPunctuationMarks(true);
						cv::line(this->dist, cv::Point(i*width_size, j), cv::Point((i + 1)*width_size, j), Scalar(200, 0, 0));
					}
					break;
				}
			}//for j - 3
			j += this->heigh_of_line / 2;
		}//while j
	}//for i
}

void Segmentation::connectValley()
{
	long index = 0;
	long idxNext = 0;
	long idxConnect = 0;
	for (int i = 0; i < NUMBER_OF_COLUMNS - 1; i++)
	{
		for (int j = 0; j < this->height; j++) {
			index = i * this->height + j;
			if (this->elements[index].isValley() & this->standardDeviation(index, i + 1) & !this->elements[index].isDoneNext()) {
				idxConnect = this->elements[index].getIdxConnect();
				if (!this->elements[idxConnect].isDonePre()) {
					cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point((i + 1)*width_size, this->elements[index].getY()), Scalar(127, 0, 0));
					cv::line(this->src, cv::Point((i + 1)*width_size, this->elements[index].getY()), cv::Point(this->elements[idxConnect].getX(), this->elements[idxConnect].getY()), Scalar(127, 0, 0));
					this->elements[index].setDoneNext(true);
					this->elements[idxConnect].setDonePre(true);
				}
			}
		}
	}//for i

	bool isEnough = false;
	int count = 0;
	for (int u = 0; u < 5; u++) {
		for (int i = 0; i < NUMBER_OF_COLUMNS - 1; i++)
		{
			//cout << "So connect trong lan " << u << "la " << count << endl;
			count = 0;
			for (int j = 0; j < this->height; j++) {
				index = i * this->height + j;
				if (this->elements[index].isValley() &
					this->elements[index].isDonePre() &
					!this->elements[index].isDoneNext()) {
					//cout << "begin X,Y=" << this->elements[index].getX() << ", " << this->elements[index].getY() << endl;
					for (int z = i + 1; z < NUMBER_OF_COLUMNS; z++) {
						for (int k = 0; k < this->height; k++) {
							idxNext = z * this->height + k;
							if (abs(k - j) <= this->heigh_of_line*(0.4 + (float)u / 10) & this->elements[idxNext].isValley() &
								this->elements[idxNext].isDoneNext() &
								!this->elements[idxNext].isDonePre()) {

								cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point((z)*width_size, this->elements[index].getY()), Scalar(127, 0, 0));
								cv::line(this->src, cv::Point((z)*width_size, this->elements[index].getY()), cv::Point(this->elements[idxNext].getX(), this->elements[idxNext].getY()), Scalar(127, 0, 0));
								this->elements[index].setDoneNext(true);
								this->elements[idxNext].setDonePre(true);
								isEnough = true;
								count++;
								break;
							}
						}
						if (isEnough) {
							isEnough = false;
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
				cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point(0, this->elements[index].getY()), Scalar(127, 0, 0));
			}
			else if (this->elements[index].isValley() &
				this->elements[index].isDonePre() &
				!this->elements[index].isDoneNext()) {
				cv::line(this->src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point(this->width, this->elements[index].getY()), Scalar(127, 0, 0));
			}
		}
	}

}

bool Segmentation::standardDeviation(long idx, int id_w_i_plus)
{
	//Trung bình khoảng cách
	double current_distance = 0;
	double min_distance = this->getHeight();
	long index = 0;
	long idxConnect = 0;

	//int current_y = this->elements[idx].getY();

	for (int i = 0; i < this->height; i++)
	{
		index = id_w_i_plus * this->height + i;

		if (this->elements[index].isValley() & this->elements[index].isPunctuationMarks()) {
			current_distance = this->distance(this->elements[index].getX(),
				this->elements[index].getY(),
				this->elements[idx].getX(),
				this->elements[idx].getY());
			if (min_distance > current_distance) {
				min_distance = current_distance;
				idxConnect = index;
			}
		}
	}
	if (min_distance < this->height) {
		this->elements[idx].setIdxConnect(idxConnect);
		this->elements[idx].setMinDistance(min_distance);
		return (min_distance <= this->heigh_of_line*0.9);
	}

	current_distance = 0;
	min_distance = this->getHeight();
	index = 0;
	idxConnect = 0;

	for (int i = 0; i < this->height; i++)
	{
		index = id_w_i_plus * this->height + i;

		if (this->elements[index].isValley()) {
			current_distance = this->distance(this->elements[index].getX(),
				this->elements[index].getY(),
				this->elements[idx].getX(),
				this->elements[idx].getY());
			if (min_distance > current_distance) {
				min_distance = current_distance;
				idxConnect = index;
			}
		}
	}
	this->elements[idx].setIdxConnect(idxConnect);
	this->elements[idx].setMinDistance(min_distance);
	return (min_distance <= this->heigh_of_line*0.6);
}

double Segmentation::distance(int x1, int y1, int x2, int y2)
{
	return abs(y1 - y2);//a half of Manhattan
}

bool Segmentation::isPunctuationMarkValley(int y, int w)
{
	int MAX_VARIABILITY = this->heigh_of_line / 4;
	int total = MAX_VARIABILITY*(MAX_VARIABILITY + 1) / 2;
	int max_behind = total * 3;
	int current_total = 0;
	long index;
	int current_variability = 0;
	int next_val = this->elements[w * this->height + y].getIntensity();
	current_total = next_val;
	for (int j = y + 1; j < this->height; j++) {
		index = w * this->height + j;
		if (next_val > this->elements[index].getIntensity()) {
			if (current_variability <= MAX_VARIABILITY & current_total <= total) {
				current_total = 0;
				for (int i = j; i < this->height & i < j + this->heigh_of_line; i++) {
					index = w * this->height + i;
					current_total += this->elements[index].getIntensity();
				}
				if (current_total > max_behind)
					return true;
				else return false;
			}
		}
		else {
			next_val = this->elements[index].getIntensity();
			current_total += next_val;
			current_variability++;

		}

		if (current_variability > MAX_VARIABILITY) {
			//cout << "current_variability " << current_variability << endl;
			return false;
		}
	}
	return false;
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
