#include <iostream>
#include <fstream>
#include <string>

#include "ppm_format.h"

using namespace std;

int main(int argc, char *argv[]) {

	string filename;
	if (argc < 2) {
		cout << "File name of the image to load: ";
		cin >> filename;
		cout << endl;
	}
	else {
		filename = argv[1];
	}
	imaging::Image *img = new imaging::Image();
	bool alert1 = *img << filename;
	if (img == nullptr || alert1 == false) {
		cerr << "Unable to allocate memory." << endl;
		system("pause");
	}
	else {
		unsigned int width = img->getWidth();
		unsigned int height = img->getHeight();
		cout << "Image dimensions are:" << width << "X" << height << endl;
		double AvRed = 0.0;
		double AvGreen = 0.0;
		double AvBlue = 0.0;
		math::Vec3<float> * data = img->getRawDataPtr();
		int size = width*height;
		for (int i = 0; i < size; i++) {
			AvRed = data[i][0] + AvRed;
			AvGreen = data[i][1] + AvGreen;
			AvBlue = data[i][2] + AvBlue;
		}
		cout << "The average color of the image is (" << AvRed / (width*height) << "," << AvGreen / (width*height) << "," << AvBlue / (width*height) << ")" << endl;
		if (argc < 3) {
			cout << "File name to write image: ";
			cin >> filename;
			cout << endl;
		}
		else {
			filename = argv[2];
		}
		bool alert2 = *img >> filename;
		if (alert2 == true) {
			cout << "Image written to " << filename << endl;
		}
		else {
			cerr << "Failed to write file!" << endl;
		}
		delete img;
		system("pause");
	}
	return 0;
}