#include <iostream>
#include <string>
#include <fstream>

#include "Image.h"
#include "ppm_format.h"
#include "Color.h"

using namespace std;

namespace imaging {

	Image * ReadPPM(const char *filename) {

		std::ifstream reader;
		std::string header;
		int width, height, rgb_comp_color;
		reader.open(filename, std::ios::binary); //Open file
		if (!reader.is_open()) { //Check if it's open
			throw("Failed to open the file.");
		}
		else {
			reader >> header; //Read header
			if (header.compare("P6") != 0) { //Check if its P6
				throw("Failed to read the file. Header must be P6.");
			}
			else {
				reader >> width >> height >> rgb_comp_color; //Read width, height and rgb_comp_color
				if (rgb_comp_color > 255) { //Check if bit depth is less or equal to 255
					throw("Failed to read the file. Color value must not be larger than 255.");
				}
				else { //If everything is fine so far
					    reader.ignore(1); //Ignore the whitespace after rgb_comp_color
						component_t *data = new component_t[3 * height*width]; //Color data of each pixel of the image
						char c[3]; //Character
						for (int i = 0; i < 3 * width*height; i = i +3) {
							reader.read(c, 3);
							data[i] = unsigned char(c[0]) / 255.0f; //Put the red value
							data[i + 1] = unsigned char(c[1]) / 255.0f; //Put the green value
							data[i + 2] = unsigned char(c[2]) / 255.0f; //Put the blue value
						}
						reader.close(); //Close reader
						Image* img = new Image(width, height, data); //Create image with the specific width, height and data
						delete[] data;
						return img; //Return the image
					}
				}
			}
		}
	}