#pragma once
#include <vector>
#include <algorithm>
#include "png_toolkit.h"
#include "rectangleArea.h"
using namespace std;
class secondary_function {
public:
	enum NameFunction {
		nameGetCoreValueClump,
		nameGetCoreValue9,
		countFunc
	};
	static void getMedian(image_data& img, rectangle_area& filter_area, rectangle_area& now_area, int* new_value);
	static void getCoreValue(image_data& img, rectangle_area& filter_area, rectangle_area& now_area, int* new_value, enum NameFunction name);
private:
	static int clump(int num);
	static rectangle_area getArea(rectangle_area& filter_area, rectangle_area& now_area);
};