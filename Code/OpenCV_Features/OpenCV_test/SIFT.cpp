#include "SIFT.h"

SIFT1::SIFT1()
{
}

void SIFT1::FeatureMatching(Mat img1, Mat img2)
{
	// 特徴点抽出
	Ptr<FeatureDetector> detector = xfeatures2d::SIFT::create();
	vector<KeyPoint> keypoint1, keypoint2;
	detector->detect(img1, keypoint1);
	detector->detect(img2, keypoint2);

	imshow("img1", img1);
	imshow("img2", img2);

	// 特徴記述
	Ptr<DescriptorExtractor> extractor = ORB::create();
	Mat descriptor1, descriptor2;
	extractor->compute(img1, keypoint1, descriptor1);
	//extractor->compute(img2, keypoint2, descriptor2);
	//imshow("descriptor1", descriptor1);
	//imshow("descriptor2", descriptor2);

	//// マッチング
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
	//vector<DMatch> dmatch;

	//if (true)
	//{
	//	// クロスチェックする場合
	//	std::vector<cv::DMatch> match12, match21;
	//	matcher->match(descriptor1, descriptor2, match12);
	//	matcher->match(descriptor2, descriptor1, match21);
	//	for (size_t i = 0; i < match12.size(); i++)
	//	{
	//		cv::DMatch forward = match12[i];
	//		cv::DMatch backward = match21[forward.trainIdx];
	//		if (backward.trainIdx == forward.queryIdx)
	//			dmatch.push_back(forward);
	//	}
	//}
	//else
	//{
	//	matcher->match(descriptor1, descriptor2, dmatch);
	//}

	// //マッチング結果の表示
	//Mat out;
	//drawMatches(img1, keypoint1, img2, keypoint2, dmatch, out);
	//imshow("matching", out);
	while (cv::waitKey(1) == -1);
}
