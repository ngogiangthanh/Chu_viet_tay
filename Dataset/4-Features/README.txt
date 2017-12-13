Mô tả: Các đầu vào và kết quả thu được từ quá trình gom cụm và kiểm chứng tốc độ tính toán

Mục đích:
	- Kiểm chứng tốc độ tính toán: chọn 500 - 1000 - 1500 - 2693 từ từ tập dữ liệu (dataset), đã rút trích đặc trưng và chuẩn hóa về độ dài. Dựa vào Module gom cụm dữ liệu [R-Studio]
	- Gom cụm: chọn lần lượt chọn k = 10 - 20 - 40 - 80 mẫu từ author_1 và author_2, chạy gom cụm trên Module gom cụm dữ liệu.
		+ File input: author_X_kAB_projection_profiles.txt hoặc author_X_kAB_word_profiles.txt [trong đó X là tác giả, AB là số k]
		+ File output:
				projection_profiles_clustering_dtw.txt => Kết quả gom cụm dựa trên giải thuật DTW với đặc trưng Projection profiles
				projection_profiles_clustering_euclid.txt => Kết quả gom cụm dựa trên giải thuật EDM với đặc trưng Projection profiles
				word_profiles_clustering_dtw.txt => Kết quả gom cụm dựa trên giải thuật DTW với đặc trưng Word profiles
				word_profiles_clustering_euclid.txt => Kết quả gom cụm dựa trên giải thuật EDM với đặc trưng Word profiles
				projection_profiles_centroids_dtw.txt => Danh sách các trọng số của mẫu, việc gom cụm bằng DTW với đặc trưng Projection profiles
				projection_profiles_centroids_euclid.txt => Danh sách các trọng số của mẫu, việc gom cụm bằng EDM với đặc trưng Projection profiles
				word_profiles_centroids_dtw.txt => Danh sách các trọng số của mẫu, việc gom cụm bằng DTW với đặc trưng Word profiles
				word_profiles_centroids_euclid.txt => Danh sách các trọng số của mẫu, việc gom cụm bằng EDM với đặc trưng Word profiles