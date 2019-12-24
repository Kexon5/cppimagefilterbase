#pragma once
#include "png_toolkit.h"
#include "rectangleArea.h"
#include "filters.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class manager_filters {
public:
	static manager_filters& instance();
	void init(string configName);
	void initFilters();
	filter* getFilter(string nameFilter);
	void run(int argc, char* argv[]);
private:
	image_data imgData;
	vector<pair<string, rectangle_area>> taskList;
	map<string, filter*> dict;
};
