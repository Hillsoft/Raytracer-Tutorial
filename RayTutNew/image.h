#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "color.h"

class Image
{
protected:
	int width, height;
	Color* data;

public:
	Image(int width, int height);

	virtual ~Image();
	
	int getWidth() const;
	int getHeight() const;

	Color* getPixel(int x, int y);

	void saveImage(std::string filename,
		float exposure = 1.0f, float gamma = 2.2f) const;
};

#endif
