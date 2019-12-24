#include "rectangleArea.h"


rectangle_area::rectangle_area(vector<string>& coefInStr) {
	y0 = stoi(coefInStr[1]);
	x0 = stoi(coefInStr[2]);
	y1 = stoi(coefInStr[3]);
	x1 = stoi(coefInStr[4]);
}

void rectangle_area::transformArea(int width, int height) {
	y0 = (y0 != 0) ? height / y0 : 0;
	x0 = (x0 != 0) ? width / x0 : 0;
	y1 = (y1 != 0) ? height / y1 : 0;
	x1 = (x1 != 0) ? width / x1 : 0;
}