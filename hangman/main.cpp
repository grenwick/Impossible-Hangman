#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "word.h"
using namespace std;

int main() {
    //int end is used at the end of the do while loop to see if the user wants to play again
    int end;
    //below used to store number of guesses as well as size of word, max word size, etc
    int numGuess;
    int wordLength;
    int maxWordSize = 0;
    string seeWord;
    //vectors below used to store individual letters of a word
    Word guess;
    vector<char> fillIn;
    vector<char> inCorr = {};
    do {
        cout << "\n";
        guess.letters = {};
        //declares ifstream and checks that file is open
        ifstream readWord("dictionary.txt");
        if (readWord.fail()) {
            cout << "Could not open file, closing";
            return -1;
        }
        //below reads all words into a vector of words, and finds the length of the largest word
        vector<string> words;
        while (!readWord.fail()) {
            string word;
            readWord >> word;
            if (word.size() > maxWordSize)
                maxWordSize = word.size();
            words.push_back(word);
        }
        //below asks the user for the length of the word that they want to guess, only continues if the input is valid
        vector<string> newWords = {};
        do {
            cout << "How long of a word would you like to guess?";
            cin >> wordLength;
            while (wordLength <= 0 || wordLength > maxWordSize) { // gets rid of wordsizes without any possible words
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a valid word length" << endl;
                cin >> wordLength;
            }
            //below adds all words that match the desired size to a new vector, also checks if the size of the vector is 0, prompts the user to reenter the desired length
            for (const auto &currWord : words) {
                if (currWord.size() == wordLength) {
                    newWords.push_back(currWord);
                }
            }
            if (newWords.size() == 0) {
                cout << "No words of selected size, please choose another size\n";

            }else{
                break;
            }
        }while(true);

        cout << "You are guessing a word of " << wordLength << " letters\n";
        //below asks how many guesses the player wants
        cout << "How many guesses would you like to play with?\n";
        cin >> numGuess;
        while (numGuess <= 0) {
            cin.clear();
            cin.ignore(10000 , '\n');
            cout << "Please enter a valid amount of guesses\n";
            cin >> numGuess;
        }
        //below asks the user if they would like to see the amount of possible words remaining
        cout << "Would you like to see the amount of possible words?\n"
                "Enter 1 for yes, or anything else for no";
        cin >> seeWord;
        if (seeWord == "1") {
            cout << "Remaining words mode selected";
        }
        //below hides the game options to make the player unaware of the true nature of the game
        for(int i = 0; i < 15; i++){
            cout << endl;
        }
        //below declares instance of hangman game, with necessary variables
        Word game;
        game.totGuess = 0;
        game.totCorrect = 0;
        string letter;
        //below holds a vector of chars that represents the word to be guessed
        vector<char> unknown;
        for (int i = 0; i < wordLength; i++) {
            unknown.push_back('_');
        }
        while (true) {
            //below prompts guesses
            cout << endl;
            for (auto i : unknown) {
                cout << i;
            }
            cout << "\nGuess a letter";
            cin >> letter;
            //below makes sure that the guess is unique/valid, if not prompts the user to guess again
            while (game.checkGuess(letter) == true) {
                cout << "\nPlease make a unique/valid guess\n";
                cout << "You have already guessed these letters: ";
                for (auto i : game.guessed) {
                    cout << i;
                }
                cout << endl << endl << "Enter a unique/valid guess";
                cin >> letter;
            }
            //below adds guess to vector of guesses, then sorts that vector
            game.guessed.push_back(letter);
            sort(game.guessed.begin(), game.guessed.end());
            cout << "You have already guessed these letters: ";
            for (auto i : game.guessed) {
                cout << i;
            }
            cout << endl;
            //below makes families according to the guessed letter
            //also declares vector of chars to compare with guess
            map<string, vector<string> > families;
            for (auto & newWord : newWords) {
                string currWord = newWord;
                for (int j = 0; j < wordLength; j++) {//converts each part of the word into binary, based on whether the letter is present or not at that location, allowing for the families to be easily identified
                    if (currWord.at(j) == letter.at(0)) {
                        currWord.at(j) = '1';
                    } else {
                        currWord.at(j) = '0';
                    }
                }
                families[currWord].push_back(newWord);
            }
            //below finds which family has the largest amount of words in it
            int maxWords = 0;
            string wordReplacer;
            for (auto i : families) {
                if (i.second.size() > maxWords) {
                    maxWords = i.second.size();
                    newWords = i.second;
                    wordReplacer = i.first;
                }
            }
            if (seeWord == "1") {
                cout << "Words in chosen family: " << maxWords;
            }
            cout << endl;
            //below checks if the unknown word should be updated, as well as if the guess was correct
            int wasCorr = 0;
            for (int i = 0; i < unknown.size(); i++) {
                if (wordReplacer.at(i) == '1') {
                    unknown.at(i) = letter.at(0);
                    game.totCorrect++;
                    wasCorr++;
                }
            }
            if (wasCorr != 0) {
                cout << "Good Guess!";
            } else {
                game.totGuess++;
                cout << "Sorry, that letter wasn't in the word\n"
                        "Number of guesses remaining: " << (numGuess - game.totGuess) << "\n";
            }
            //below exits if the game is over
            if (game.isWon(wordLength)) {
                cout << " Good Job! You won\n"
                        "The word was " << newWords.at(0);
                break;
            }
            if (game.isLost(numGuess)) {
                cout << " You lost\n"
                        "The correct word was: " << newWords.at(0);
                break;
            }
        }
        cout << endl <<"Would you like to play again? Enter 1 if yes, and anything else for no";
        cin >> end;
    }while (end == 1);
    return 69;
}
