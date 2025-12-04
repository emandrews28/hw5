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
bool test(const std::string& temp, const std::set<std::string>& dict);
void placeFloat(int index, std::string& temp, std::string remainder, const std::set<std::string>& dict, std::set<std::string>& words);
void fill(int index, std::string& temp, const std::set<std::string>& dict, std::set<std::string>& words);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> words;
    std::string temp = in;
    placeFloat(0, temp, floating, dict, words);
    return words;
}

// Define any helper functions here
void placeFloat(int index, std::string& temp, std::string remainder, const std::set<std::string>& dict, std::set<std::string>& words)
{
  if(index == temp.size()) {
    if(remainder.empty()) {
      fill(0, temp, dict, words);
    }
    return;
  }
  if(temp[index] != '-') {
    placeFloat(index+1, temp, remainder, dict, words);
    return;
  }

  int dashes = 0;
  for(int i=index; i < temp.size(); i++) {
    if(temp[i] == '-') {
      dashes++;
    }
  }
  if(remainder.size() > dashes) {
    return;
  }

  if(remainder.size() < dashes) {
    placeFloat(index+1, temp, remainder, dict, words);
  }

  for(int i=0; i < remainder.size(); i++) {
    temp[index] = remainder[i];
    std::string recurseRemain = remainder;
    recurseRemain.erase(i, 1);
    placeFloat(index+1, temp, recurseRemain, dict, words);  
  }
  temp[index] = '-';
}

void fill(int index, std::string& temp, const std::set<std::string>& dict, std::set<std::string>& words)
{
  if(index == temp.size()) {
    if(test(temp, dict)) {
      words.insert(temp);
    }
    return;
  }
  if(temp[index] != '-') {
    index++;
    fill(index, temp, dict, words);
    return;
  }

  for(int i=0; i < 26; i++) {
    temp[index] = 'a' + i;
    fill(index+1, temp, dict, words);
  }
  temp[index] = '-';
}


bool test(const std::string& temp, const std::set<std::string>& dict) {
  return dict.find(temp) != dict.end();
}
