#pragma once
#ifndef Element_H
#define Element_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Element {
private:
	unsigned int x;
	unsigned int y;
	unsigned int intensity;
	unsigned int order;
	long idxConnect;
	bool valley;
	bool top;
	bool doneNext;
	bool donePre;
	bool punctuationMarks;
	bool iterator;
	double minDistance;
	cv::Point corner;

public:
	Element();
	Element(unsigned int, unsigned int, unsigned int);
	unsigned int getX();
	unsigned int getY();
	unsigned int getOrder();
	unsigned int getIntensity();
	double getMinDistance();
	cv::Point getCorner();
	long getIdxConnect();
	bool isValley();
	bool isTop();
	bool isDoneNext();
	bool isDonePre();
	bool isPunctuationMarks();
	bool isIterator();
	void setX(unsigned int);
	void setY(unsigned int);
	void setOrder(unsigned int);
	void setIdxConnect(long);
	void setTop(bool top);
	void setIntensity(unsigned int);
	void setValley(bool);
	void setDoneNext(bool);
	void setDonePre(bool);
	void setMinDistance(double);
	void setPunctuationMarks(bool);
	void setIterator(bool);
	void setCorner(cv::Point);
	bool isHasCorner();
};

#endif
