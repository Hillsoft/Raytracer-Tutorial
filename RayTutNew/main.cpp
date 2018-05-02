#include <QtCore/QCoreApplication>

#include "image.h"
#include "camera.h"
#include "shape.h"

void rayTrace(Image& image, Camera* camera, Shape* scene)
{
	for (int x = 0; x < image.getWidth(); x++)
	{
		for (int y = 0; y < image.getHeight(); y++)
		{
			Vector2 screenCoord((2.0f*x) / image.getWidth() - 1.0f,
				(-2.0f*y) / image.getHeight() + 1.0f);
			Ray ray = camera->makeRay(screenCoord);

			Color* curPixel = image.getPixel(x, y);

			Intersection intersection(ray);
			if (scene->intersect(intersection))
			{
				*curPixel = intersection.color;
			}
			else
			{
				*curPixel = Color(0.0f);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	// QCoreApplication a(argc, argv);

	int width = 1920;
	int height = 1080;

	Image image(width, height);
	PerspectiveCamera camera(Point(-5.0f, 1.0f, 0.0f),
		Vector(0.0f, 1.0f, 0.0f), Vector(), 25.0f * PI / 180.0f,
		(float)width / (float)height);

	ShapeSet scene;

	Plane floor(Point(0.0f, 0.0f, 0.0f), Vector(),
		Color(0.5f, 1.0f, 0.5f));
	scene.addShape(&floor);

	Sphere sphere(Point(0.0f, 1.0f, 0.0f), 1.0f,
		Color(0.5f, 0.5f, 1.0f));
	scene.addShape(&sphere);

	rayTrace(image, &camera, &scene);

	image.saveImage("out.png");

	// return a.exec();
}
