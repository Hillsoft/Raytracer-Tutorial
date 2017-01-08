#include "image.h"

#include <fstream>
#include <QtGui\QImage>

Image::Image(int width, int height)
	: width(width), height(height)
{
	data = new float[width * height];
}

Image::~Image()
{
	delete[] data;
}

int Image::getWidth() const
{
	return width;
}

int Image::getHeight() const
{
	return height;
}

float* Image::getPixel(int x, int y)
{
	return data + (x + y * width);
}

void Image::saveImage(std::string filename) const
{
	uchar* imgData = new uchar[width * height];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			imgData[x + y * width] = (uchar)(data[x + y * width] * 255.0f);
		}
	}

	QImage img(imgData, width, height, QImage::Format_Grayscale8);
	img.save(QString(filename.c_str()));

	delete[] imgData;
}
