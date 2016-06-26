#pragma once

#include <iostream>
#include <sstream>

#ifndef PI
#define PI 3.14159265359
#endif

template <typename T> std::string& to_string(T& x)
{
	std::ostringstream s;
	s << x;
	return s.str();
}