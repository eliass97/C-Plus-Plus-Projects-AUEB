#include <iostream>
#include <string>
#include <fstream>

#include "ppm_format.h"

using namespace std;

namespace imaging {

	Image * ReadPPM(const char *filename) {

		ifstream reader;
		string header;
		int width, height, rgb_comp_color;
		reader.open(filename, std::ios::binary); //open the reader
		if (!reader.is_open()) {
			cerr << "Failed to open the file." << endl;
			return 0;
		}
		else {
			reader >> header; //store header
			if (header.compare("P6") != 0) {
				cerr << "Failed to read the file. Header must be P6." << endl;
				return 0;
			}
			else {
				reader >> width >> height >> rgb_comp_color; //store width, height and rgb
				if (rgb_comp_color > 255) {
					cerr << "Failed to read the file. Color value must not be larger than 255." << endl;
					return 0;
				}
				else {
					reader.ignore(1);
					math::Vec3<float> * data = new math::Vec3<float>[height*width]; //create data array
					char c[3];
					for (int i = 0; i < width*height; i++) {
						reader.read(c, 3); //read the 3 characters
						data[i][0] = unsigned char(c[0]) / 255.0f; //store red
						data[i][1] = unsigned char(c[1]) / 255.0f; //store green
						data[i][2] = unsigned char(c[2]) / 255.0f; //store blue
					}
					reader.close();
					Image * img = new Image(width, height, data); //create the image
					delete[] data; //delete the array
					return img; //return the image
				}
			}
		}
	}

	bool WritePPM(Image & image, const char * filename) {
		std::ofstream writer;
		writer.open(filename, std::ios::binary); //open the writer
		if (writer.fail()) {
			return false; //if it failed to open the file then return false
		}
		else {
			math::Vec3<float> * dataWrite = image.getRawDataPtr(); //create data array
			writer << "P6" << "\n" << image.getWidth() << " " << image.getHeight() << "\n" << "255" << "\n"; //write the header,width,height and rgb
			for (unsigned int i = 0; i < image.getWidth()*image.getHeight(); i++) {
				writer << (char)(dataWrite[i][0] * 255.0f) << (char)(dataWrite[i][1] * 255.0f) << (char)(dataWrite[i][2] * 255.0f); //write the data
			}
			delete[] dataWrite; //delete the array
			return true; //return true
		}
	}
}