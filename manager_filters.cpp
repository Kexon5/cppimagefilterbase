#include "manager_filters.h"
manager_filters& manager_filters::instance() {
	static manager_filters instance;
	return instance;
}
void manager_filters::init(string configName) {
	ifstream fIn(configName);
	string s;
	if (!fIn.is_open())
		throw "Can't open file!";
	while (getline(fIn, s)) {
		vector<string> lexem;
		stringstream ss(s);
		string item;
		while (getline(ss, item, ' ')) {
			lexem.push_back(item);
		}
		if (lexem.size() == 5) {
			try {
				rectangle_area param(lexem);
				taskList.push_back(make_pair(lexem[0], param));
			}
			catch (invalid_argument & e) {
				throw "Error in config file";
			}
		}
	}
	initFilters();
	fIn.close();
}
void manager_filters::initFilters() {
	dict["Red"] = new red_filter();
	dict["Threshold"] = new threshold_filter();
	dict["Blur"] = new blur_filter();
	dict["Edge"] = new edge_filter();
}
filter* manager_filters::getFilter(string name) {
	if (dict.find(name) != dict.end())
		return dict.find(name)->second;
	else
		throw "Not valid filter";
}
void manager_filters::run(int argc, char* argv[]) {
	png_toolkit studTool;
	studTool.load(argv[2]);
	imgData = studTool.getPixelData();
	init(argv[1]);
	for (auto item : taskList) {
		item.second.transformArea(imgData.w, imgData.h);
		getFilter(item.first)->setFilter(imgData, item.second);
	}
	studTool.save(argv[3]);
}