#include "Segmentation.h"

Segmentation::Segmentation(Mat src)
{
	this->obstructing = new Obstructing();
	this->src = src.clone();
}

void Segmentation::normalized(Mat& anhGoc)
{
	//Khởi tạo size(width, height) gốc
	this->height = this->src.rows;
	this->width = this->src.cols;
	//Chuẩn hóa lại size cho phù hợp
	if (this->width % NUMBER_OF_COLUMNS != 0) {
		//Size chuẩn hóa (theo chiều width) += số cột - width % số cột
		this->width += NUMBER_OF_COLUMNS - this->width % NUMBER_OF_COLUMNS;
		//gọi hàm resize hình
		resize(this->src, this->src, cv::Size(this->width, this->height));
		resize(anhGoc, anhGoc, cv::Size(this->width, this->height));
	}

	//In ra cmd
	cout << "Kich thuoc goc [" << this->width << ", " << this->height << "]" << endl;
	cout << "Kich thuoc phu hop [" << this->width << ", " << this->height << "]" << endl;
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

	cout << "Hoan tat --> Khoi tao horizontal valleys" << endl;
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

	cout << "Hoan tat --> Moving Average Filter cac dinh voi n = " << this->kernelMAF << endl;
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

	cout << "Hoan tat --> Tim kiem thung lung" << endl;

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
					//cv::line(temp_src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point((i + 1)*width_size, this->elements[index].getY()), Scalar(220, 0, 0));
					//cv::line(temp_src, cv::Point((i + 1)*width_size, this->elements[index].getY()), cv::Point(this->elements[idxConnect].getX(), this->elements[idxConnect].getY()), Scalar(220, 0, 0));
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

								//cv::line(temp_src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point((z)*width_size, this->elements[index].getY()), Scalar(220, 0, 0));
								//cv::line(temp_src, cv::Point((z)*width_size, this->elements[index].getY()), cv::Point(this->elements[idxNext].getX(), this->elements[idxNext].getY()), Scalar(220, 0, 0));
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
				//cv::line(temp_src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point(0, this->elements[index].getY()), Scalar(220, 0, 0));
			}
			else if (this->elements[index].isValley() &
				this->elements[index].isDonePre() &
				!this->elements[index].isDoneNext()) {
				this->elements[index].setIterator(true);
				//cv::line(temp_src, cv::Point((i)*width_size, this->elements[index].getY()), cv::Point(this->width, this->elements[index].getY()), Scalar(220, 0, 0));
			}
		}
	}
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
	MatModifies matModifies;

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
					//cout << "==== first " << 0 << ", " << this->elements[index].getY() << " =====" << endl;//nho xóa
				}
				else {
					line.push_back(cv::Point(this->elements[index].getX(), this->elements[index].getY()));
					//cout << "line = " << ln << "| X,Y= " << this->elements[index].getX() << ", " << this->elements[index].getY() << endl; //nho xoa
				}
				if (this->elements[idx].isHasCorner())
					line.push_back(this->elements[index].getCorner());

				this->elements[index].setIterator(false);

				while (this->elements[idx].isIterator() & this->elements[idx].isDonePre()) {
					line.push_back(cv::Point(this->elements[idx].getX(), this->elements[idx].getY()));
					//cout << "==== test " << this->elements[idx].getX() << ", " << this->elements[idx].getY() << " =====" << endl;//nho xoa
					if (!this->elements[idx].isDoneNext()) {
						line.push_back(cv::Point(this->width, this->elements[idx].getY()));
						//cout << "==== end " << this->width<< ", " << this->elements[idx].getY() << " =====" << endl;//nho xoa
						break;
					}
					else {
						if (this->elements[idx].isHasCorner()) {
							line.push_back(this->elements[idx].getCorner());
							//cout << "line = " << ln << "| X,Y= " << this->elements[idx].getCorner().x << ", " << this->elements[idx].getCorner().y << endl;//nho xoa
						}
					}

					this->elements[idx].setIterator(false);
					idx = this->elements[idx].getIdxConnect();
				}
				//cout << endl;
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
		return a.size() < MIN_POINTS;
	}), lines.end());

	// Tiến hành kiếm tra kẻ có cắt chữ
	int s = (int)lines.size();
	for (vector<int>::size_type m = 0; m != s; m++) {

		vector<cv::Point> el_pre;
		vector<cv::Point> el_next;
		vector<cv::Point> el = lines.at(m);
		vector<cv::Point> el_temp = lines.at(m);

		if (m != 0) {
			el_pre = lines.at(m - 1);
		}
		if (m < s - 1) {
			el_next = lines.at(m + 1);
		}

		int s_el = (int)el.size();

		//cout << "Before el size is " << s_el << endl;
		cv::Point min(0, 0), max(0, 0);
		for (vector<int>::size_type k = 0; k != s_el - 1; k++) {
			int y_pre_valley = matModifies.getValleyY(el_pre, el.at(k).x);
			int y_next_valley = matModifies.getValleyY(el_next, el.at(k).x);

			vector<cv::Point> path_hit;
			if ((min.x != 0 & min.y != 0 & max.x != 0 & max.y != 0) & el.at(k).x >= min.x & el.at(k).x <= max.x) {
				//
				for (std::vector<cv::Point>::iterator it = el_temp.begin(); it != el_temp.end(); ++it) {
					if (it->x == el.at(k).x & it->y == el.at(k).y) {
						it->x = max.x;
					}
				}
				continue;
			}
			else {
				int flag = matModifies.addPts(this->src, el.at(k), el.at(k + 1), this->heigh_of_line, (y_pre_valley >= 0) ? y_pre_valley : 0, (y_next_valley >= 0) ? y_next_valley : this->src.rows - 1, path_hit);

				if (path_hit.size() > 0) {

					min = path_hit.at(0);
					max = path_hit.at(path_hit.size() - 1);

					matModifies.insert(el_temp, path_hit, flag);
				}
			}
		}
		lines.at(m) = el_temp;
		//cout << "After el size is " << lines.at(m).size() << endl << endl;
	}

	//Concat two vectors and cut image
	int numline = 1;
	this->setLineResult(this->word_result);
	for (vector<int>::size_type m = 0; m != s; m++) {
		vector<cv::Point> el = lines.at(m);
		int s_el = (int)el.size();
		for (vector<int>::size_type k = 0; k != s_el - 1; k++) {
			cv::line(this->line_result, cv::Point(el.at(k).x, el.at(k).y), cv::Point(el.at(k + 1).x, el.at(k + 1).y), Scalar(128, 128, 128));
		}
	}
	string pathSaving = (PATH + this->getName());
	mkdir((pathSaving).c_str());
	mkdir((pathSaving + "//words//").c_str());
	mkdir((pathSaving + "//lines//").c_str());
	string savePath;
	int x_min_word, y_min_word, x_max_word, y_max_word;
	int y_min_cut = this->src.rows;

	for (vector<int>::size_type m = 0; m != s - 1; m++) {
		vector<cv::Point> el = lines.at(m);
		std::reverse(el.begin(), el.end());
		//
		vector<cv::Point> pts;
		pts.insert(pts.end(), lines.at(m + 1).begin(), lines.at(m + 1).end());
		pts.insert(pts.end(), el.begin(), el.end());

		Mat rs = matModifies.cut(this->src, pts, y_min_cut);
		Mat rs_reflect = matModifies.cut(this->word_result, pts, y_min_cut);
		vector<Word_Element> words = this->getWords(rs);
		Mat word;
		int word_size = words.size();
		int word_number = 1;
		for (vector<Word_Element>::size_type k = 0; k != word_size - 1; k++) {
			int x = words.at(k).getX_Middle_Coordinate();
			int x_next = words.at(k + 1).getX_Middle_Coordinate();
			Mat word = matModifies.cropImage(rs, x, 0, x_next, rs.rows);
			Mat word_reflect = matModifies.cropImage(rs_reflect, x, 0, x_next, rs.rows);
			matModifies.findMinMax(word, x_min_word, y_min_word, x_max_word, y_max_word);
			word_reflect = matModifies.cropImage(word_reflect, x_min_word, y_min_word, x_max_word, y_max_word);

			cv::rectangle(this->word_result,
				cv::Point(x + x_min_word, y_min_cut + y_min_word),
				cv::Point(x + x_max_word, y_min_cut + y_max_word),
				cv::Scalar(128, 128, 128));

			//resize(word, word, cv::Size(100, 100 * word.rows / word.cols), 0, 0);
			savePath = pathSaving + "//words//" + std::to_string(x + x_min_word) + "_" + std::to_string(y_min_cut + y_min_word) + "_" + std::to_string(x + x_max_word) + "_" + std::to_string(y_min_cut + y_max_word) + ".jpg";
			imwrite(savePath, word_reflect);
			word_number++;
		}

		savePath = pathSaving + "//lines//" + std::to_string(numline) + ".jpg";
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
			rs = matModifies.cut(this->src, pts, y_min_cut);
			rs_reflect = matModifies.cut(this->word_result, pts, y_min_cut);
			words = this->getWords(rs);
			word_size = words.size();
			word_number = 1;
			for (vector<Word_Element>::size_type k = 0; k != word_size - 1; k++) {
				int x = words.at(k).getX_Middle_Coordinate();
				int x_next = words.at(k + 1).getX_Middle_Coordinate();
				//cv::line(rs, cv::Point(x, 0), cv::Point(x, rs.rows), Scalar(128, 128, 128));
				Mat word = matModifies.cropImage(rs, x, 0, x_next, rs.rows);
				Mat word_reflect = matModifies.cropImage(rs_reflect, x, 0, x_next, rs.rows);
				matModifies.findMinMax(word, x_min_word, y_min_word, x_max_word, y_max_word);
				word_reflect = matModifies.cropImage(word_reflect, x_min_word, y_min_word, x_max_word, y_max_word);

				cv::rectangle(this->word_result,
					cv::Point(x + x_min_word, y_min_cut + y_min_word),
					cv::Point(x + x_max_word, y_min_cut + y_max_word),
					cv::Scalar(128, 128, 128));

				//resize(word, word, cv::Size(100, 100*word.rows /word.cols), 0, 0);

				savePath = pathSaving + "//words//" + std::to_string(x + x_min_word) + "_" + std::to_string(y_min_cut + y_min_word) + "_" + std::to_string(x + x_max_word) + "_" + std::to_string(y_min_cut + y_max_word) + ".jpg";
				imwrite(savePath, word_reflect);
				word_number++;
			}

				savePath = pathSaving + "//lines//" + std::to_string(numline) + ".jpg";
				imwrite(savePath, rs);
		}
	}
	cout << "Hoan tat --> Ket noi va cat noi dung trong van ban" << endl;
}

vector<Word_Element> Segmentation::getWords(Mat line)
{
	vector<Word_Element> words;
	vector<X_Element> X_projection;
	Scalar intensity;
	int count = 0;
	long average_val = 0;
	//Step 1: Calculating X-projection
	//cout << "Step 1: Calculating X-projection" << endl;
	for (int i = 0; i < line.cols; i++) {
		count = 0;
		for (int j = 0; j < line.rows; j++) {
			intensity = line.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD)
				count++;
		}//end for j
		X_projection.push_back(X_Element(count, i));
	}//end for i
	 //Step 1': Moving Average Filter X_Projection
	 //cout << "Step 1': Moving Average Filter X_Projection" << endl;
	int X_size = X_projection.size();
	int middle_Kernel = this->kernelMAF / 2;
	int MAF_val = 0;
	for (vector<X_Element>::size_type k = 0; k != X_size; k++) {
		MAF_val = 0;
		int max = 0;
		for (int m = -middle_Kernel; m <= middle_Kernel; m++) {
			if (m + k < X_size & m + k >= 0) {
				if (X_projection.at(m + k).getCurr_Val() != 0) {
					if (max < X_projection.at(m + k).getCurr_Val()) max = X_projection.at(m + k).getCurr_Val();
					MAF_val += X_projection.at(m + k).getCurr_Val();
				}
			}
		}
		
		MAF_val /= this->kernelMAF;
		average_val += MAF_val;
		X_Element x_element = X_projection.at(k);
		x_element.setMAF_Val(MAF_val);
		X_projection.at(k) = x_element;
	}
	//cout << "average_val = " << average_val << endl;
	//cout << "X_size = " << X_size << endl;
	average_val /= X_size;
	//cout << "average_val = " << average_val << endl;
	//Step 1'': Removing the first and end blank
	//cout << "Step 1'': Removing the first and end blank -start" << endl;
	average_val = 5;
	//cout << "average_val = " << average_val << endl;
	//cout << "before - start = " << X_projection.size() << endl;
	vector<X_Element>::iterator begin = X_projection.begin();
	vector<X_Element>::iterator end = X_projection.end();
	bool stop = false;
	for (vector<X_Element>::iterator it = begin; it != end - middle_Kernel; ++it) {
		if (it->getMAF_Val() >= average_val) {
			stop = false;
			for (int m = 1; m <= middle_Kernel; m++) {
				if (it->getMAF_Val() > (it + m)->getMAF_Val()) {
					stop = true;
					break;
				}
			}

			if (!stop) {
				X_projection.erase(begin, it);
				break;
			}
		}
	}
	//cout << "after - start = " << X_projection.size() << endl;

	//cout << "Step 1'': Removing the first and end blank -end" << endl;
	begin = X_projection.begin();
	end = X_projection.end();
	//cout << "before - end = " << X_projection.size() << endl;
	stop = false;
	for (vector<X_Element>::iterator it = end - 1; it != begin + middle_Kernel; --it) {
		if (it->getMAF_Val() >= average_val) {
			stop = false;
			for (int m = 1; m <= middle_Kernel; m++) {
				if (it->getMAF_Val() >= (it - m)->getMAF_Val()) {
					stop = true;
					break;
				}
			}

			if (!stop) {
				X_projection.erase(it, end);
				break;
			}
		}
	}
	//cout << "after - end = " << X_projection.size() << endl;
	//Step 2: Count blank in X_projection
	//cout << "Step 2: Count blank in X_projection" << endl;
	
	//Step 3:
	int avg_blank = 4;
	X_size = X_projection.size();
	count = 0;
	bool start = false;
	int x_begin = -1;
	int x_end = -1;
	words.push_back(Word_Element((begin)->getX_Coordinate(), (begin)->getX_Coordinate()));
	for (vector<X_Element>::size_type k = 0; k != X_size - middle_Kernel; k++) {
		X_Element x_element = X_projection.at(k);
		if (x_element.getMAF_Val() < average_val) {
			count++;
			start = true;
			x_begin = x_element.getX_Coordinate();
		}
		else if (start && x_element.getMAF_Val() >= average_val) {
			start = false;
			x_end = x_element.getX_Coordinate();
			if (count >= avg_blank) {
				Word_Element element(x_begin, x_end);
				words.push_back(element);
			}
			x_begin = -1;
			x_end = -1;
			count = 0;
		}
	}
	words.push_back(Word_Element((end - 1)->getX_Coordinate(), (end - 1)->getX_Coordinate()));

	//Step 4: Return vector words blank
	return words;
}

void Segmentation::setSrc(Mat src)
{
	this->src = src.clone();
}

void Segmentation::setDist(Mat dist)
{
	this->dist = dist.clone();
}

void Segmentation::setName(string name)
{
	this->name = name;
}

void Segmentation::setLineResult(Mat lines)
{
	this->line_result = lines.clone();
}

void Segmentation::setWordResult(Mat words)
{
	this->word_result = words.clone();
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

Mat Segmentation::getLineResult()
{
	return this->line_result;
}

Mat Segmentation::getWordResult()
{
	return this->word_result;
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

string Segmentation::getName()
{
	return this->name;
}

Mat Segmentation::wordCleaning(Mat word)
{
	Mat word_cleaning = word.clone();
	//word cleaning
	vector<X_Element> v_his;
	vector<Y_Element> h_his;
	int max_x = 0;
	int max_x_locate = 0;
	int max_y = 0;
	int max_y_locate = 0;
	Scalar intensity;
	int count = 0;
	for (int i = 0; i < word_cleaning.cols; i++) {
		count = 0;
		for (int j = 0; j < word_cleaning.rows; j++) {
			intensity = word_cleaning.at<uchar>(j, i);
			if (intensity[0] <= THRESHOLD)
				count++;
		}//end for j

		if (count > max_x) {
			max_x = count;
			max_x_locate = i;
		}

		v_his.push_back(X_Element(count, i));
	}//end for i

	for (int i = 0; i < word_cleaning.rows; i++) {
		count = 0;
		for (int j = 0; j < word_cleaning.cols; j++) {
			intensity = word_cleaning.at<uchar>(i, j);
			if (intensity[0] <= THRESHOLD)
				count++;
		}//end for j
		if (count > max_y) {
			max_y = count;
			max_y_locate = i;
		}
		h_his.push_back(Y_Element(count, i));
	}//end for i

	//Khử nhiễu v_his


	//Khử nhiễu h_his


	return word_cleaning;
}
