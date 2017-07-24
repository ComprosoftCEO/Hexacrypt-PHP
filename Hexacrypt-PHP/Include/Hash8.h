#ifndef HASH_8_HEADER
#define HASH_8_HEADER

#include <iostream>
#include <Rand64.h>

//Simple hash function that can output in
//   variable formats:
//
//Valid instantiations are:
//===================================
//	-char 	/ unsigned char
//	-short	/ unsigned short
//	-int	/ unsigned int
//	-long	/ unsigned long
//
//Other types will NOT link properly when run
template<class type>
extern type Hash8(std::string input);

#endif
