#ifndef _HELPSTRINGSOPERATIONS_H
#define _HELPSTRINGSOPERATIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <ctype.h>


void splitToWords(std::string str, std::vector<std::string> & vec);
std::string getFirstWord(std::string str);




void splitToWords(std::string str, std::vector<std::string> & vec){
  std::string word = "";
  for (char c : str) {
    if (c == ' '){
       if(word != " " && word != ""){
         vec.push_back(word);
       }
       word = "";
    }
    else {
       word = word + c;
    }
  }
  if(word != " " && word != ""){
    vec.push_back(word);
  }
}

std::string getFirstWord(std::string str){
  std::string word = "";
  char c;
  int i = 0;

  do {
    c = str[i];
    ++i;
  } while (isspace(c));

  do {
    word = word + c;
    c = str[i];
    ++i;
  } while (!isspace(c) && c != '\0');
  return word;
}


#endif
