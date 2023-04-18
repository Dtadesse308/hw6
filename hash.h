#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <algorithm>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash
{
    HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261, 261934300};
    MyStringHash(bool debug = true)
    {
        if (false == debug)
        {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const
    {
        // Add your code here

       unsigned long long Pof36[6] = {1,36, 1296, 46656, 1679616, 60466176};
        std::vector <unsigned long long> w  ;

       

        // generate w[i]
        HASH_INDEX_T sum = 0;
        for (int i = 0; i < (int)k.size(); i++)      // go through the word
        { 

            if ((k.size() - i) >= 6)
            {
                for (int j = 0; j < 6; j++)
                {
                    sum += Pof36[j] * letterDigitToNumber(k[k.size() - 1 - j - i]);
                }
                w.push_back(sum);
                sum = 0;
                i += 5;
            }

            else
            {

                for (int p = 0; p < (int)k.size() - i; p++)
                {
                    sum += Pof36[p] * (letterDigitToNumber(k[k.size() - 1 - i - p]));
                }
                w.push_back(sum);
                i += k.size() - i;
            }
        }

        //generate h(k)   
        unsigned long long h = 0;
       // reverse(w.begin(), w.end());     
        for (int i = w.size()-1; i >= 0; i --){          
            h += (w[i] * rValues[5-1-i]);
     
        }

        return h;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        char x = (char)tolower(letter);
        HASH_INDEX_T num;
        if ((x >= 'a') && (x <= 'z'))
        { // if letter is an character
            num = x - 97;
        }
        else
        { // if letter is a number
            num = letter - 22;
        }

        return num;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for (int i{0}; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
