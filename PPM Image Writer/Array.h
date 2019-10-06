#ifndef _ARRAY_
#define _ARRAY_

namespace math {

	template <typename T>
	class Array {

	protected:

		T * buffer;
		unsigned int width, height;			

	public:

		unsigned int getWidth() const {
			return width;
		}      

		unsigned int getHeight() const {
			return height;
		}

		void * const getRawDataPtr();

		void resize(unsigned int new_width, unsigned int new_height);

		Array(unsigned int w, unsigned int h);

		Array(const Array<T> & source);
		
		T & operator () (int x, int y);                      
		
		const T & operator () (int x, int y) const;

		Array & operator = (const Array<T> & source);

		bool operator == (const Array<T> & right) const;
		
		virtual ~Array();
	};
}
#include "Array.hpp"
#endif