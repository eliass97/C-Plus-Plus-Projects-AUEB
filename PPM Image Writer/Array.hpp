#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

#include <iostream>
#include "Array.h"

namespace math {

	template <typename T>
	void * const Array<T>::getRawDataPtr() {
		return buffer;
	}

	template <typename T>
	void Array<T>::resize(unsigned int new_width, unsigned int new_height) {
		unsigned int i, j;
		if ((new_width <= 0 || new_height <= 0) || (new_width == width || new_height == height)) {
			cerr << "Cannot resize - Maybe negative or zero value has been given to new width or height.\n Maybe new width or new height is equal to the previous ones." << endl;
		}
		else {
			math::Vec3<float> * temp = new math::Vec3<float>[width*height]; //temporary data array
			for (unsigned int i = 0; i < new_height; i++) {
				for (unsigned int j = 0; j < new_width; j++) {
					if (i >= height || j >= width) {
						temp[i*new_width + j] = 0.0f; //set black
					}
					else {
						temp[i*new_width + j] = buffer[i*width + j]; //copy pixel
					}
				}
			}
			delete[] buffer;
			buffer = temp; //copy back pixel
			delete[] temp;
			width = new_width; //set width
			height = new_height; //set height
		}
	}

	template <typename T>
	Array<T>::Array(unsigned int w, unsigned int h) {
		width = w;
		height = h;
	}

	template <typename T>
	Array<T>::Array(const Array<T> & source) : width(source.getWidth()), height(source.getHeight()) {
		memcpy(buffer, source, sizeof(source));
	}

	template <typename T>
	Array<T>::~Array() {
		if (buffer != nullptr) {
			delete[] buffer;
			buffer = nullptr;
		}
	}

	template <typename T>
	T & Array<T>::operator () (int x, int y) {
		if ((x < width) && (y < height) && x >= 0 && y >= 0) {
			return buffer[y*width + x]; //return the pixel
		}
		else {
			cerr << "Cannot set pixel - Out of bounds." << endl;
			return buffer[0];
		}
	}

	template <typename T>
	const T & Array<T>::operator () (int x, int y) const {
		if ((x < width) && (y < height) && x >= 0 && y >= 0) {
			return buffer[y*width + x]; //return the pixel
		}
		else {
			cerr << "Cannot set pixel - Out of bounds." << endl;
			return buffer[0];
		}
	}

	template <typename T>
	Array<T> & Array<T>::operator = (const Array<T> & source) {
		width = source.getWidth(); //set the width
		height = source.getHeight(); //set the height
		Array<Vec3<T>> temp = source.getRawDataPtr(); //get the pixels
		for (unsigned i = 0; i < width*height; i++) {
			buffer[i] = temp[i]; //set the pixels
		}
		delete[] temp;
		return *this;
	}

	template <typename T>
	bool Array<T>::operator == (const Array<T> & right) const {
		bool same = true;
		if (getWidth() != right.getWidth() || getHeight() != right.getHeight()) { //if the size doesn't match
			same = false;
		}
		else {
			Array<Vec3<T>> temp = right.getRawDataPtr(); //temporary array
			for (int i = 0; i < width*height; i++) {
				if (buffer[i] != temp[i]) { //if the pixel doesn't match
					same = false;
					break;
				}
			}
			delete[] temp;
		}
		return same;
	}
};
#endif