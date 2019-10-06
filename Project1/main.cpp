#include <iostream>
#include <string>

#include "Image.h"
#include "Color.h"
#include "ppm_format.h"

using namespace std;

	int main(int argc, char *argv[]) {

		string filename;
		if (argc <= 2) { //If the file has not been given by cmd
			cout << "File name of the image to load: ";
			cin >> filename;
			cout << endl;
		}
		else { //If the file has been given by cmd
			filename = argv[1]; //Save what was typed at cmd and use it as filename
		}
		imaging::Image* img = imaging::ReadPPM(filename.c_str()); //ReadPPM
		if (img == nullptr) { //If it failed to create img
			cout << "Unable to allocate memory." << endl;
			return -1;
		}
		else { //If everything is ok
			unsigned int width = img->getWidth(); //Width
			unsigned int height = img->getHeight(); //Height
			cout << "Image dimensions are:" << width << "X" << height << endl; //Print width X height
			double AvRed = 0.0;
			double AvGreen = 0.0;
			double AvBlue = 0.0;
			imaging::component_t * data = img->getRawDataPtr(); //Create data
			int size = 3 * width*height; //data size
			for (int i = 0; i < size; i=i+3) {
				AvRed = data[i] + AvRed; //Sum red
				AvGreen = data[i + 1] + AvGreen; //Sum green
				AvBlue = data[i + 2] + AvBlue; //Sum blue
			}
			cout << "The average color of the image is (" << AvRed / (width*height) << "," << AvGreen / (width*height) << "," << AvBlue / (width*height) << ")" << endl; //Print Average colors
			delete img;
			system("pause");
			return 0;
		}
	}