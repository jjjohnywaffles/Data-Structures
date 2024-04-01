#ifndef HANGMAN_H
#define HANGMAN_H

#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

void mainMenu();
void readWord(const int, std::ifstream&, std::vector<std::string>&);
int letters(const std::vector<std::string>&, std::vector<char>&, const int);
int hangmanFigure(int, const std::vector<std::string>&, int);
int guessLetters(const std::vector<std::string>&, std::vector<char>&, int&);
void gameState(const std::vector<char>&);
void showInstructions();
void playGame();

#endif
