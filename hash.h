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
        // Add your code here

        unsigned long long w[5]={};
        int b = 1;
        int in = 0;
        HASH_INDEX_T s = 0;
        int weight1 = 4;
        for(int i = k.size()-1; i>=0; i--){
          if(in>5){
            w[weight1]=s;
            b=1;
            s=0;
            weight1 = weight1-1;
            in = 0;
          }
          s+= b * letterDigitToNumber(k[i]);
          b=b*36;
          in++;
        }
        w[weight1]=s;
        return (rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4]);


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

          if(int(letter)>96){
            return int(letter)-97;
          }
          else if(int(letter)>64){
            return int(letter)-65;
          }
          else{
            return int(letter)-48+26;
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
