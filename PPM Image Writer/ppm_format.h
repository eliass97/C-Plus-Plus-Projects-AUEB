#ifndef _PPM
#define _PPM

#include "Image.h"

namespace imaging {

	Image * ReadPPM(const char * filename);

	bool WritePPM(Image & image, const char * filename);
}
#endif