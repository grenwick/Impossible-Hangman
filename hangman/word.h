//
// Created by Grant on 11/10/2020.
//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
#ifndef FINAL_WORD_H
#define FINAL_WORD_H
class Word {
public:
    string alphabet ="abcdefghijklmnopqrstuvwxyz";
    vector<char> letters;
    int totGuess;
    int totCorrect;
    vector<string> guessed;
    int checkGuess(string guess);
    int isWon(int wordSize);
    int isLost(int numGuess);
};
#endif //FINAL_WORD_H
