#include <Hexacrypt.h>
#include <Rand64.h>
#include <Hash8.h>

using namespace std;

//Only the 95 text characters are allowed
static const string allChars = " !\"#$\%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
static const int CHAR_COUNT = allChars.length();


//How much garbage to include
#define GARBAGE 10


//Filter out any illegal characters
//===================================
//  Returns the filtered string
string filter(string input) {

	string retStr = "";
	size_t i;
	char c;

	for (i = 0; i < input.length(); i++) {
		c = input[i];
		if (c >= 32 && c <= 126) {retStr+=c;}
	}

	return retStr;
}



//Perform a Pseudo XOR on string input and using
//  a seeded Rand64 object
void pseudoXOR(string &input, Rand64 &rand) {

	string pxor;
	size_t i, index, strlen = allChars.length();	
	
	for (i = 0; i < input.length(); i++) {
		pxor = rand.shuffleString(allChars);
		index = pxor.find_first_of(input[i]);
		input[i]=pxor[(strlen - 1) - index];
	}
}



//Completely reverse all of the characters in the string
//=======================================================
//  Modifies the input string...
void reverseStr(string &str)
{
    int n = str.length();
 
    // Swap character starting from two
    // corners
    for (int i=0; i<n/2; i++)
       swap(str[i], str[n-i-1]);
}


//Add random garbage onto the front of the string
//=======================================================
//  Requires the seed for adding the count of how much garbage was added
void addGarbage(string &input, Rand64 &rand, unsigned long &seed) {

    int front, back, i;
    string count_string;    //Used to encode the garbage added

    front = rand.next(GARBAGE+1);
    for (i = 0; i < front; i++) {
        input.insert(0,&allChars[rand.next(CHAR_COUNT)], 1);
    }

    back = rand.next(GARBAGE);
    for (i = 0; i < back; i++) {
        input+=allChars[rand.next(CHAR_COUNT)];
    }    

    rand.reseed(seed);
    count_string = rand.shuffleString(allChars);
    input+=count_string[front];
    input+=count_string[back];
}



//Removes the garbage from the string
//====================================
//   Throws error upon failure
void removeGarbage(string &input, Rand64 &rand) {

    int front, back;
    string count_string = rand.shuffleString(allChars);
    size_t index = input.length();
    
    //Extract
    front = count_string.find_first_of(input[index - 2]);
    back = count_string.find_first_of(input[index - 1]);

    //Test for error
    if (front < 1 || front > GARBAGE || back < 1 || back > GARBAGE) {
        throw "Invalid input!";
    }

    //We gucci. Remove the characters
    input = input.substr(front);
    input = input.substr(0,(input.length() - back) - 2);
}




//Encrypt with the Hexacrypt Algorithn
//======================================
//  Returns the encrypted string
Php::Value Hexacrypt_Encrypt(Php::Parameters &params) {

	string plaintext, key;
	Rand64 rand;
    unsigned long seed;
    char checksum;

	//Cast to string
	plaintext = filter(params[0].stringValue());
	key = filter(params[1].stringValue());	
    seed = Hash8<unsigned long>(key);

	rand.reseed(seed);
	pseudoXOR(plaintext,rand);
	reverseStr(plaintext);
    rand.randomSeed();
    addGarbage(plaintext,rand, seed);

    //Also add a small checksum
    checksum = allChars[Hash8<unsigned char>(key+plaintext) % CHAR_COUNT];
    plaintext.insert(0,&checksum,1);

    rand.reseed(seed);
    pseudoXOR(plaintext,rand);

	return plaintext;
}




//Decrypt with the Hexacrypt Algorithm
//========================================
//  Returns false upon failure
Php::Value Hexacrypt_Decrypt(Php::Parameters &params) {

	string ciphertext, key;
	Rand64 rand;
    unsigned long seed;
    char checksum;

	//Cast to string
	ciphertext = filter(params[0].stringValue());
	key = filter(params[1].stringValue());	
    seed = Hash8<unsigned long>(key); 

	rand.reseed(seed);
    pseudoXOR(ciphertext, rand);

    //Validate checksum
    checksum = allChars[
        
        //Remove first character, as this is NOT part of the checksum
        Hash8<unsigned char>(key+ciphertext.substr(1,ciphertext.length() - 1)) % CHAR_COUNT
    ];   
    if (checksum != ciphertext[0]) {
        return false;
    }
    ciphertext = ciphertext.substr(1,ciphertext.length() - 1);


    //Test for error in garbage
    rand.reseed(seed);
    try {
        removeGarbage(ciphertext, rand);
    } catch (const char* msg) {
        //Php::warning << "Invalid Hexacrypt string. Unable to decrypt." << endl;
        return false;
    }

	reverseStr(ciphertext);
    rand.reseed(seed);
	pseudoXOR(ciphertext,rand);
    
	return ciphertext;
}
