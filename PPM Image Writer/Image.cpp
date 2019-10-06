#include <iostream>
#include <fstream>
#include <string>

#include "Image.h"
#include "ppm_format.h"

using namespace std;

namespace imaging {

	math::Vec3<float> * const Image::getRawDataPtr() {
		return buffer;
	}

	math::Vec3<float> Image::getPixel(unsigned int x, unsigned int y) const {
		if (x >= Image::getWidth() || y >= Image::getHeight() || x < 0 || y < 0) {
			return math::Vec3<float>(0.0f, 0.0f, 0.0f);
		}
		else {
			return math::Vec3<float>(buffer[y*width + x][0], buffer[y*width + x][1], buffer[y*width + x][2]); //return the pixel
		}
	}

	void Image::setPixel(unsigned int x, unsigned int y, math::Vec3<float> & value) {
		if ((x < width) && (y < height) && x >= 0 && y >= 0) {
			buffer[y*width + x][0] = value[0]; //set red
			buffer[y*width + x][1] = value[1]; //set green
			buffer[y*width + x][2] = value[2]; //set blue
		}
		else {
			cerr << "Cannot set pixel - Out of bounds." << endl;
		}
	}

	void Image::setData(const math::Vec3<float> * data_ptr) {
		int size = width*height;
		if (size != 0) {
			buffer = new math::Vec3<float>[size];
			for (int i = 0; i < size; i++) {
				buffer[i] = data_ptr[i]; //set data
			}
		}
		else {
			cerr << "Cannot set data - Width or height is equal to 0." << endl;
		}
	}

	Image::Image() : Array<math::Vec3<float>>(0, 0) {}

	Image::Image(unsigned int width, unsigned int height) : Array(width, height) {}

	Image::Image(unsigned int width, unsigned int height, const math::Vec3<float> * data_ptr) : Array<math::Vec3<float>>(width, height) {
		setData(data_ptr);
	}

	Image::Image(const Image &src) : Array<math::Vec3<float>>(src.width, src.height) {
		int size = src.width * src.height;
		setData(src.buffer);
	}

	Image::~Image() {
		if (buffer != nullptr) {
			delete[] buffer;
			buffer = nullptr;
		}
	}

	bool Image::operator << (std::string filename) {
		Image* img = ReadPPM(filename.c_str()); //call ReadPPM
		if (!img) {
			return false;
		}
		else {
			width = img->getWidth(); //set width
			height = img->getHeight(); //set height
			buffer = img->getRawDataPtr(); //set data
			return true;
		}
	}

	bool Image::operator >> (std::string filename) {
		Image * img = new Image(width, height, buffer); //create the image
		return WritePPM(*img, filename.c_str()); //call WritePPM
	}
}