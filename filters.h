#pragma once
#include "png_toolkit.h"
#include "rectangleArea.h"
#include "secondary_functions.h"
class filter {
public:
	void setFilter(image_data& img, rectangle_area& filter_area);
	virtual void prepareImg(image_data& img, rectangle_area& filter_area) = 0;
	virtual void applyFeatureFilter(image_data& img,  rectangle_area& filter_area, int i, int j) = 0;
};
class monochrome_filter: public filter {
public:
	void prepareImg(image_data& img, rectangle_area& filter_area) {};
	void applyFeatureFilter(image_data& img, rectangle_area& filter_area, int i, int j);
};

class red_filter : public filter {
public:
	void prepareImg(image_data& img, rectangle_area& filter_area) {};
	void applyFeatureFilter(image_data& img, rectangle_area& filter_area, int i, int j);
};
class threshold_filter : public filter {
public:
	threshold_filter(int size = 5) : size_matrix(size) {};
	void prepareImg(image_data& img, rectangle_area& filter_area);
	void applyFeatureFilter(image_data& img, rectangle_area& filter_area, int i, int j);
private:
	int size_matrix;
};
class blur_filter : public filter {
public:
	blur_filter(int size = 3) : size_matrix(size) {};
	void prepareImg(image_data& img, rectangle_area& filter_area) {};
	void applyFeatureFilter(image_data& img, rectangle_area& filter_area, int i, int j);
private:
	int size_matrix;
};
class edge_filter : public filter {
public:
	edge_filter(int size = 3) : size_matrix(size) {};
	void prepareImg(image_data& img, rectangle_area& filter_area);
	void applyFeatureFilter(image_data& img, rectangle_area& filter_area, int i, int j);
private:
	int size_matrix;
};