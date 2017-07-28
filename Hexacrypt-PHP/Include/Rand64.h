#ifndef RAND64_HEADER
#define RAND64_HEADER

#include <iostream>

#define ORDER	  32
#define ARR_MASK  31
#define BIT_MASK  63

#define MULTIPLER		6364136223846793005
#define INCREMENT		1442695040888963407

class Rand64 {

	private:
		unsigned long arr[ORDER];
		unsigned char pos;
		static Rand64 seeder;

	public:
		Rand64();
		Rand64(unsigned long);

		void reseed(unsigned long);
		void randomSeed();	

		unsigned long next();
		unsigned long next(unsigned long max);

		std::string shuffleString(std::string);

};



#endif
