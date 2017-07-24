#include <Rand64.h>
#include <Hash8.h>
#include <time.h>

using namespace std;

//Initialize the static variable
Rand64 Rand64::seeder(time(NULL));


//Create a new random object of a given seed
Rand64::Rand64(unsigned long seed) {
	reseed(seed);
}


//Initialize with a random seed
Rand64::Rand64() {
	randomSeed();
}




//Give it a new seed
void Rand64::reseed(unsigned long seed) {
	
	//Use Linear congruential generator to fill array
	for (int i = 0; i < ORDER; i++) {
		arr[i] = seed;
		seed = (seed*MULTIPLER + INCREMENT);

        //Switch bits
        seed = (seed << 32) | (seed >> 32);
	}
	arr[ORDER] = 0;
}


//Seed the random number generator using a string
/*void Rand64::reseed(string str) {
	unsigned long seed = 0;
	size_t i;

	for (i = 0; i < str.length(); i++) {
		seed+=str[i];
	}

	reseed((unsigned long) seed);
}*/



//Seed using the seeder
void Rand64::randomSeed() {
	reseed(seeder.next());
}



//Get the next random number
unsigned long Rand64::next() {
	int index = arr[ORDER] = (arr[ORDER] + 1) & ARR_MASK;
	arr[index] += (arr[(index + 5) & ARR_MASK] + arr[(index + 17) & ARR_MASK]);
	return arr[index];
}



//Generate a random number
//   0 <= X < MAX
//
//   If Max == 0, don't limit
unsigned long Rand64::next(unsigned long max) {
	return (max == 0) ? next() : next() % max;
}




//Shuffle a string using this random object
string Rand64::shuffleString(string input) {

	string retVal = "";
	size_t strlen;
	unsigned int index;

	while ((strlen = input.length()) > 0) {
		index = next() % strlen;
		retVal += input[index];
		input.erase(index,1);
	}

	return retVal;
}
