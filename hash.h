#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
			//variables 
			//array with all the substring (can be 5 max). 
			unsigned long long values[5] = {0}; 

			HASH_INDEX_T hash = 0; 

			//Calculate number of substrings. Round up.
			double numSubstrings = std::ceil(k.size()) / 6;
			//Process last group of 6
			int startIndex = k.size();
			// If string length is multiple of 6, set starting index to 6
			// if (startIndex == 0) {
			// 		startIndex = 6;
			// }
			int power = 1; //multiply to 36 without pow 
			int index = 4; //start at back of the values array 
			int result = 0; 

			//first for loop, go through the substrings 
			for(int i=0; i < numSubstrings; i++) {
				startIndex = k.size() - 1 - (6*i); 
				if(startIndex < 0) {
					break; 
				}
				//second for loop go through the values of the substrings, back to front
				for(int j = startIndex; j >= startIndex-5; j--) {
					//lower the character if upper case 
						if(j < 0) {
							break; 
						}
						char character = tolower(k[j]); 
						//convert letter to digit 
						int value = letterDigitToNumber(character);
						//update result 
						result = value*power; 
						//std::cout << "index" << k[j] << std::endl; 
						//std::cout << "result " << result << std::endl; 
						//multiply by 36, update power 
						power*=36;
						//increment the 
            values[index]+= result;
						//std::cout << "values " << values[index] << std::endl;

				}
				//std::cout << values[index] << std::endl; 
				power = 1; 
				index--; 
			}	
			for(int i=0; i < 5; i++) {
				hash += rValues[i] * values[i]; 
			}
			return hash; 

    }





    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {

			if (letter >= 'a' && letter <= 'z') {
        return letter - 'a';
			}

    	else if (letter >= '0' && letter <= '9') {
        return letter - '0' + 26;
			}
    	else {
        return 0; // Default value if the character is not a letter or digit
			}
		}



    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
