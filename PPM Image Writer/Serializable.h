#ifndef _SERIALIZABLE_
#define _SERIALIZABLE_

#include <iostream>
#include <string>

class Serializable {

public:

	virtual bool operator << (std::string filename) = 0;

	virtual bool operator >> (std::string filename) = 0;
};
#endif