#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    std::string& curr,
    const std::string& fixed,
    string floatingLeft,
    const std::set<std::string>& dict,
    set<string>& result,
    int index,
    int blanksLeft);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> result;
    string curr = in;

    int blanksLeft = 0;
    for(int i = 0; i < (int)in.size();i++){
        if(in[i] == '-'){
            blanksLeft++;
        }
    }

    wordleHelper(curr, in, floating, dict, result, 0, blanksLeft);

    return result;


}

// Define any helper functions here

void wordleHelper(
    std::string& curr,
    const std::string& fixed,
    string floatingLeft,
    const std::set<std::string>& dict,
    set<string>& result,
    int index , 
    int blanksLeft)
{

    //full word formed
    if(index == (int)curr.size()){
        if(floatingLeft.empty() && dict.find(curr) != dict.end()){
            result.insert(curr);
        }
        return;
    }

        /**
        //check if floating letters are in the word
        bool valid = true;

        for(int i=0; i < (int)floating.size(); i++){
           char c = floating[i];
           bool inWord = false;
           for(int j = 0; j < curr.size(); j++){
                if(curr[j] == c){
                    inWord = true;
                    break;
                }
           }

            if(!inWord){
                valid = false;
                break;
            }           
        }

        //check if in dict
        if(valid && dict.find(curr) != dict.end()){
            result.insert(curr);
        }
        return;
    }
    **/

    //if current letter is fixed
    if(fixed[index] != '-'){
        curr[index] = fixed[index];
        wordleHelper(curr, fixed, floatingLeft, dict, result, index+1, blanksLeft);
        return;
    }
    
    //position is blnak, try letters
    for(char c = 'a'; c <= 'z'; c++){
        bool isFloating = false;
        int floatIdx = -1;

        //check if c is a floating letter
        for(int i = 0; i < (int)floatingLeft.size(); i++){
            if(floatingLeft[i] == c){
                isFloating = true;
                floatIdx = i;
                break;
            }
        }
        if(isFloating){
            //use floating letter in this spot
            string newFloating = floatingLeft;
            newFloating.erase(newFloating.begin() + floatIdx);

            curr[index] = c;
            wordleHelper(curr, fixed, newFloating, dict, result, index+1, blanksLeft-1);
        }
        else{
            //use a non floating letter; make sure remaing spots left for floating letters
            int remainingSpots = blanksLeft - 1;
            if(remainingSpots < (int)floatingLeft.size()){
                //not enough space to fit floating
                continue;
            }
            curr[index] = c;
            wordleHelper(curr, fixed, floatingLeft, dict, result, index+1, remainingSpots);
        }

    }
    curr[index] = '-';


}
