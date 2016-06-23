#pragma once
#ifndef Element_H
#define Element_H

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
	double minDistance;

public:
	Element();
	Element(unsigned int, unsigned int, unsigned int);
	unsigned int getX();
	unsigned int getY();
	unsigned int getOrder();
	unsigned int getIntensity();
	double getMinDistance();
	long getIdxConnect();
	bool isValley();
	bool isTop();
	bool isDoneNext();
	bool isDonePre();
	bool isPunctuationMarks();
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
};

#endif
