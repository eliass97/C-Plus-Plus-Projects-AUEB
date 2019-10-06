#ifndef _IMAGE
#define _IMAGE

#include "Array.h"
#include "Serializable.h"
#include "Vec3.h"

namespace imaging {

	class Image : public math::Array<math::Vec3<float>>, public Serializable {

	public:

		math::Vec3<float> * const getRawDataPtr();

		math::Vec3<float> getPixel(unsigned int x, unsigned int y) const;

		void setPixel(unsigned int x, unsigned int y, math::Vec3<float> & value);

		void setData(const math::Vec3<float> * data_ptr);

		Image();

		Image(unsigned int width, unsigned int height);

		Image(unsigned int width, unsigned int height, const math::Vec3<float> * data_ptr);

		Image(const Image &src);

		~Image();

		virtual bool operator << (std::string filename);

		virtual bool operator >> (std::string filename);
	};
}
#endif