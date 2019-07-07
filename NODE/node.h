#pragma once
class node
{
public:
	node();
	node(int NodeIndex,double x, double y,double z);
	~node();
	double x;
	double y;
	int NodeIndex;
	double z;
};

