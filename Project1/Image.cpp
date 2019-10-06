#include <iostream>

#include "Image.h"
#include "Color.h"

using namespace std;

namespace imaging {

	component_t * Image::getRawDataPtr() { //Getters(buffer)
		return buffer;
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const { //Getters(pixel)
		if (x >= width || y >= height || x < 0 || y < 0) {
			return Color(0.0f, 0.0f, 0.0f); //If its outside the image return black
		}
		else {
			return Color(buffer[3 * (y*width + x)], buffer[3 * (y*width + x) + 1], buffer[3 * (y*width + x) + 2]); //If its inside the image return buffer color
		}
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color & value) { //Setters(pixel)
		if ((x < width) && (y < height) && x >= 0 && y >= 0) { //If it's inside the image set the color at buffer
			buffer[3 * (y*width + x)] = value[0];
			buffer[3 * (y*width + x) + 1] = value[1];
			buffer[3 * (y*width + x) + 2] = value[2];
		}
		else { //If it's ouside the image return warning
			cout << "Cannot set pixel - Out of bounds." << endl;
		}
	}

	void Image::setData(const component_t * & data_ptr) { //Setters(data)
		int size = 3 * width*height; //Buffer's size
		if (size != 0) { //If width and height aren't equal to 0
			buffer = new component_t[size]; //Create buffer with the wanted size
			for (int i = 0; i < size; i++) {
				buffer[i] = data_ptr[i]; //Save the wanted data
			}
		}
		else { //If width or height is equal to 0
			cout << "Cannot set data - Width or height is equal to 0." << endl;
		}
	}

	void Image::resize(unsigned int new_width, unsigned int new_height) {
		unsigned int i, j;
		if ((new_width <= 0 || new_height <= 0) || (new_width == width || new_height == height)) { //If the new width or height is negative or zero
			cout << "Cannot resize - Maybe negative or zero value has been given to new width or height. Maybe new width or new height is equal to the previous ones." << endl;
		}
		else { //If else
			component_t * temp = new component_t[width*height * 3]; //Temporary buffer
			for (unsigned int i = 0; i < new_height; i++) {
				for (unsigned int j = 0; j < 3 * new_width; j++) {
					if (i >= height || j >= 3 * width) {
						temp[3 * i*new_width + j] = 0.0f; //Set the pixel to black
					}
					else {
						temp[3 * i*new_width + j] = buffer[3 * i*width + j]; //Pixel pixel from buffer
					}
				}
			}
			delete[] buffer;
			buffer = temp; //Copy pixels from temporary to buffer
			delete[] temp;
			width = new_width; //Change width
			height = new_height; //Change height
		}
	}

	Image::Image() : width(0), height(0), buffer(0) {} //Simple constructor

	Image::Image(unsigned int width, unsigned int height) { //Constructor with w+h inputs
		this->width = width;
		this->height = height;
	}

	Image::Image(unsigned int width, unsigned int height, const component_t * data_ptr) { //Constructor with w+h+d inputs
		this->width = width;
		this->height = height;
		setData(data_ptr);
	}

	Image::Image(const Image &src){ //Constructor with Image input
		this->width = src.width;
		this->height = src.height;
		int size = 3 * width*height; //Buffer's size
		if (size != 0) { //If width and height aren't equal to 0
			buffer = new component_t[size]; //Create buffer with the wanted size
			for (int i = 0; i < size; i++) {
				buffer[i] = src.buffer[i]; //Save the wanted data
			}
		}
		else { //If width or height is equal to 0
			cout << "Cannot set data - Width or height is equal to 0." << endl;
		}
		
	} 

	Image::~Image() { //Destructor
		delete[] buffer;
	}

	Image & Image::operator = (const Image & right) { //Operator
		Image left = Image(right);
		return left;
	}
}