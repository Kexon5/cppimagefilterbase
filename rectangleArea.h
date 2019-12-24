#pragma once
#include <vector>
#include <string>
using namespace std;
class rectangle_area {
public:
	rectangle_area(int x0 = 0, int y0 = 0, int x1 = 0, int y1 = 0) : x0(x0), y0(y0), x1(x1), y1(y1) {};
	rectangle_area(vector<string>& coefInStr);
	void transformArea(int width, int height);

	int x0, y0, x1, y1;
};