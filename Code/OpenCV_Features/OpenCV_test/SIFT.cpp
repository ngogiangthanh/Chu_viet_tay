#include "SIFT.h"

SIFT::SIFT()
{
}

void SIFT::FeatureMatching(Mat img1, Mat img2, bool crossCheck)
{
	// Feature point extraction
	Ptr<FeatureDetector> detector = xfeatures2d::SIFT::create();
	vector<KeyPoint> keypoint1, keypoint2;
	detector->detect(img1, keypoint1);
	detector->detect(img2, keypoint2);

	// Feature description
	/*
		The current implementation supports the following types of a descriptor extractor:
		"BRISK" – BRISK
		"ORB" – ORB
	*/
	//Ptr<DescriptorExtractor> extractor = ORB::create();
	Ptr<DescriptorExtractor> extractor = BRISK::create();
	Mat descriptor1, descriptor2;
	extractor->compute(img1, keypoint1, descriptor1);
	extractor->compute(img2, keypoint2, descriptor2);

	//Matching alorigthm
	/*
	Descriptor matcher type. Now the following matcher types are supported:
		BruteForce (it uses L2 )
		BruteForce-L1
		BruteForce-Hamming
		BruteForce-Hamming(2)
		FlannBased
	*/
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
	//BFMatcher matcher1(NORM_L2);
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-L1");
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming(2)");
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");//unsupported format or combination formats
	vector<DMatch> dmatch;
	//vector<vector<DMatch> > dmatch;

	if (crossCheck)
	{
		 //cross check
		vector<DMatch> match12, match21;
		matcher->match(descriptor1, descriptor2, match12);
		matcher->match(descriptor2, descriptor1, match21);
		for (size_t i = 0; i < match12.size(); i++)
		{
			DMatch forward = match12[i];
			DMatch backward = match21[forward.trainIdx];
			if (backward.trainIdx == forward.queryIdx)
				dmatch.push_back(forward);
		}
	}
	else
	{
		matcher->match(descriptor1, descriptor2, dmatch);
		//matcher1.knnMatch(descriptor1, descriptor2, dmatch, 4);
	}


	 //show matching
	Mat out;
	drawMatches(img1, keypoint1, img2, keypoint2, dmatch, out);
	imshow("matching", out);
	imwrite("D://result_matching.png", out);
	while (waitKey(1) == -1);
}
