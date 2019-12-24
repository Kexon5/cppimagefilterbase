#include "filters.h"

void filter::setFilter(image_data& img, rectangle_area& filter_area) {
	prepareImg(img, filter_area);
	image_data imgCopy;
	imgCopy.h = img.h;
	imgCopy.w = img.w;
	imgCopy.compPerPixel = img.compPerPixel;
	int img_size = img.w * img.h * img.compPerPixel;
	imgCopy.pixels = new stbi_uc[img_size];
	memcpy(imgCopy.pixels, img.pixels, img_size);
	int const imgSize = img.h * img.w * img.compPerPixel;
	for (int i = filter_area.y0; i < filter_area.y1; i++)
		for (int j = filter_area.x0; j < filter_area.x1; j++) 
			applyFeatureFilter(img, imgCopy, filter_area, i, j);
	delete[] imgCopy.pixels;
}

void monochrome_filter::applyFeatureFilter(image_data& img, image_data& img_copy, rectangle_area& filter_area, int i, int j) {
	int indPix = img.compPerPixel * (i * img.w + j);
	int const redPart = img.pixels[indPix];
	int const greenPart = img.pixels[indPix + 1];
	int const bluePart = img.pixels[indPix + 2];
	int const mono = (3 * redPart + 6 * greenPart + bluePart) / 10;
	img.pixels[indPix] = mono;
	img.pixels[indPix + 1] = mono;
	img.pixels[indPix + 2] = mono;
}

void red_filter::applyFeatureFilter(image_data& img, image_data& img_copy, rectangle_area& filter_area, int i, int j) {
	int indPix = img.compPerPixel * (i * img.w + j);
	img.pixels[indPix] = 255;
	img.pixels[indPix + 1] = 0;
	img.pixels[indPix + 2] = 0;
}

void threshold_filter::prepareImg(image_data& img, rectangle_area& filter_area) {
	filter* mc_f = new monochrome_filter();
	mc_f->setFilter(img, filter_area);
}

void threshold_filter::applyFeatureFilter(image_data& img, image_data& img_copy, rectangle_area& filter_area, int i, int j) {
	int indPix = img.compPerPixel * (i * img.w + j);
	rectangle_area nowMatrix(j - size_matrix / 2, i - size_matrix / 2, j + size_matrix / 2, i + size_matrix / 2);
	int median = 0;
	secondary_function::getMedian(img_copy, filter_area, nowMatrix, &median);
	if (img.pixels[indPix] < median) {
		img.pixels[indPix] = 0;
		img.pixels[indPix + 1] = 0;
		img.pixels[indPix + 2] = 0;
	}
}

void blur_filter::applyFeatureFilter(image_data& img, image_data& img_copy, rectangle_area& filter_area, int i, int j) {
	int indPix = img.compPerPixel * (i * img.w + j);
	rectangle_area nowMatrix(j - size_matrix / 2, i - size_matrix / 2, j + size_matrix / 2, i + size_matrix / 2);
	int newValue[3];
	secondary_function::getCoreValue(img_copy, filter_area, nowMatrix, newValue, secondary_function::nameGetCoreValue9);
	img.pixels[indPix] = newValue[0];
	img.pixels[indPix + 1] = newValue[1];
	img.pixels[indPix + 2] = newValue[2];
}

void edge_filter::prepareImg(image_data& img, rectangle_area& filter_area) {
	filter* mc_f = new monochrome_filter();
	mc_f->setFilter(img, filter_area);
}

void edge_filter::applyFeatureFilter(image_data& img, image_data& img_copy, rectangle_area& filter_area, int i, int j) {
	int indPix = img.compPerPixel * (i * img.w + j);
	rectangle_area nowMatrix(j - size_matrix / 2, i - size_matrix / 2, j + size_matrix / 2, i + size_matrix / 2);
	int newValue;
	secondary_function::getCoreValue(img_copy, filter_area, nowMatrix, &newValue, secondary_function::nameGetCoreValueClump);
	img.pixels[indPix] = newValue;
	img.pixels[indPix + 1] = newValue;
	img.pixels[indPix + 2] = newValue;
}