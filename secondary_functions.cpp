#include "secondary_functions.h"

void secondary_function::getMedian(image_data& img, rectangle_area& filter_area, rectangle_area& now_area, int* new_value) {
	vector<stbi_uc> nowElements;
	int indPix;
	 rectangle_area const active_area = getArea(filter_area, now_area);
	for (int i = active_area.y0; i <= active_area.y1; i++) {
		for (int j = active_area.x0; j <= active_area.x1; j++) {
			indPix = img.compPerPixel * (i * img.w + j);
			nowElements.push_back(img.pixels[indPix]);
		}
	}
	sort(nowElements.begin(), nowElements.end());
	new_value[0] = nowElements[nowElements.size() / 2];
}

int secondary_function::clump(int num) {
	if (num >= 0 && num <= 255)
		return num;
	else if (num < 0)
		return 0;
	else
		return 255;
}

rectangle_area secondary_function::getArea(rectangle_area& filter_area, rectangle_area& now_area) {
	int y0 = (filter_area.y0 > now_area.y0) ? filter_area.y0 : now_area.y0;
	int y1 = (filter_area.y1 - 1> now_area.y1) ? now_area.y1 : filter_area.y1 - 1;
	int x0 = (filter_area.x0 > now_area.x0) ? filter_area.x0 : now_area.x0;
	int x1 = (filter_area.x1 - 1> now_area.x1) ? now_area.x1 : filter_area.x1 - 1;
	return rectangle_area(x0, y0, x1, y1);
}

void secondary_function::getCoreValue(image_data& img, rectangle_area& filter_area, rectangle_area& now_area, int* new_value, enum NameFunction name) {
	rectangle_area const active_area = getArea(filter_area, now_area);
	int sizeNowArea = (now_area.y1 - now_area.y0) * (now_area.y1 - now_area.y0), sizeValue = 0;
	if (name == nameGetCoreValue9)
		sizeValue = 3;
	else
		sizeValue = 1;
	int indPix, indForWeight9 = sizeValue * sizeValue;
	for (int i = 0; i < sizeValue; i++)
		new_value[i] = 0;

	for (int i = active_area.y0; i <= active_area.y1; i++) {
		for (int j = active_area.x0; j <= active_area.x1; j++) {
			indPix = img.compPerPixel * (i * img.w + j);
			if (sizeValue == 1) {
				if ((now_area.y1 + now_area.y0) / 2 == i && (now_area.x1 + now_area.x0) / 2 == j)
					new_value[0] += 9 * img.pixels[indPix];
				else
					new_value[0] -= img.pixels[indPix];
			}
			else {
				new_value[0] += img.pixels[indPix];
				new_value[1] += img.pixels[indPix + 1];
				new_value[2] += img.pixels[indPix + 2];
			}
		}
	}
	if (sizeValue == 3)
		for (int i = 0; i < sizeValue; i++)
			new_value[i] /= 9;
	else
		new_value[0] = clump(new_value[0]);
}