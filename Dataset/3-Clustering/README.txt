Số lượng unigram-từ: 2693 từ, gồm 1303 từ (author_1) và 1390 từ (author_2)
Số lượng mẫu: 80 mẫu
Mục đích:
	Tập dữ liệu sử dụng cho các quá trình:
		- Chuẩn hóa nghiêng và đường gạch (normalization):
				+ Sử dụng Module chuẩn hóa từ
				+ Sử dụng chức năng chọn ngẫu nhiên 100 mẫu từ [vào 4 dataset] trong tập lớn này
				+ Thêm nghiêng, đường gạch và chuẩn hóa
		- Gom cụm dữ liệu (Clustering)
				+ Cách lựa chọn theo các chiến lược trình bày trong báo cáo
				+ Sử dụng cho Module trích chọn đặc trưng
		- Thực nghiệm tốc độ tính toán
				+ Sử dụng Module FastDTW và NN_LB_Improved
				+ Cách sử dụng lựa chọn 1 từ trong toàn bộ 2693 từ, thực hiện tính toán cặp đôi so với 2692 từ còn lại. Thực hiện với toàn bộ 2693 từ. Như vậy ta được tổng số lần tính toán DTW là 7,249,556 DTW. Với cách thức cắt tỉa Lemire thì, chỉ thực hiện khoảng 1/2-1/5 tổng số lần này.

Lưu ý: Em thực hiện lưu các từ theo mẫu, mẫu thuộc author_1 hoặc author_2. Ví dụ: từ "anh.jpg" thuộc thư mục "anh" của "author_1", nhằm mục đích khai thác tên thư mục để tính giá trị Entroypy tự động (thủ thuật để tính giá trị entropy nhanh và đơn giản hơn). Sự lưu trữ này là khách quan và không ảnh hưởng đến quá trình gom cụm dữ liệu.