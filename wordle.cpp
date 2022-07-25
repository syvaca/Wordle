// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordMaker(std::string input, std::string floating, const std::set<std::string>& dict, std::set<std::string>& result, std::set<int> index, unsigned int n);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> result;
    std::set<int> index; //holds the indexes that need to be filled 


    for(unsigned int i = 0; i < in.size(); i++) {
        if(!isalpha(in[i])) {
            index.insert(i);
        }
    }

    wordMaker(in, floating, dict, result, index, 0);

    return result;

}

// Define any helper functions here
void wordMaker(
    std::string input,
    std::string floating, 
    const std::set<std::string>& dict,
    std::set<std::string>& result,
    std::set<int> index,
    unsigned int n) //n is the index we are working on
{

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    while((index.find(n) == index.end()) && (n < input.size())) { //gets the next index that needs to be filled
        n++;
    }

    if(n == input.size()) { //whole word is filled
        if(dict.find(input) != dict.end() && floating.empty()) {
            result.insert(input);
        } 
        return;
    }

    index.erase(n);

    for(unsigned int i = 0; i < floating.size(); i++) { //fill first with float
        input[n] = floating[i];

        string float_copy = floating; 
        float_copy.erase(float_copy.begin()+i);

        wordMaker(input, float_copy, dict, result, index, n+1); //recurse with floating removed
    }

    if(floating.size() > index.size()) {
        return;
    }
                    
    for(unsigned int i = 0; i < alphabet.size(); i++) { //fill second with alphabet
        input[n] = alphabet[i];
        wordMaker(input, floating, dict, result, index, n+1);
    }
}
