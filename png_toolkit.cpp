#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include "stb_image_write.h"
#include "png_toolkit.h"

typedef enum
{
	a,
	b,
	c,
} RED;
png_toolkit::png_toolkit()
{
}

png_toolkit::~png_toolkit()
{
    stbi_image_free(imgData.pixels);
}

bool png_toolkit::load( const std::string &pictureName )
{
    imgData.pixels = stbi_load(pictureName.c_str(), &imgData.w, &imgData.h, &imgData.compPerPixel, 0);
    return imgData.pixels != nullptr;
}

bool png_toolkit::save( const std::string &pictureName )
{
    return stbi_write_png(pictureName.c_str(),
                   imgData.w, imgData.h,
                   imgData.compPerPixel,
                          imgData.pixels, 0) != 0;
}


image_data png_toolkit::getPixelData( void ) const
{
    return imgData;
}
void png_toolkit::goRed(void)
{
	int const height = imgData.h / 2;
	for (int i = height; i < imgData.h; i++)
		for (int j = 0; j < imgData.w; j++)
		{
			imgData.pixels[imgData.compPerPixel * (i * imgData.w + j)] = (255);
			imgData.pixels[imgData.compPerPixel * (i * imgData.w + j) + 1] = 0;
			imgData.pixels[imgData.compPerPixel * (i * imgData.w + j) + 2] = 0;
		}
}