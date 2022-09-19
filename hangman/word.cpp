//
// Created by Grant on 11/10/2020.
//
#include <iostream>
#include "word.h"
using namespace std;

//returns true if the letter has already been guessed, or is invalid
int Word::checkGuess(string guess){
    int check = 0;
    if(guess.size() > 1){
        return 1;
    }
    for(auto i : guessed){
        if(i == guess){
            return 1;
        }
    }
    for(int i = 0; i < 26; i++){
        if(alphabet.find(guess) == string::npos){
            return 1;
        }
    }
    return check;
}

int Word::isWon(int wordSize){
    if(totCorrect >= wordSize){
        return 1;
    }

    return 0;
}

int Word::isLost(int numGuess){
    if(totGuess >= numGuess) {
        return 1;
    }

    return 0;
}