#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>

/**************************************
 Get a token from a string originally
 written by Peter Wilson
**************************************/
std::string getToken(std::string &s, std::string::iterator &i);
std::string lookAtToken(std::string &s, std::string::iterator i);

#endif
