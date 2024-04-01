#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Possible word struct
struct PossibleWord {
    string word;
};

// Answer struct
struct Answer {
    string word;
};

// Gamestate struct
struct Gamestate {
    string displayWord;
    vector<char> incorrectLetters;
};

// Hangman class
class Hangman {
private:
    PossibleWord possibleWords[5] = {"hello", "world", "programming", "computer", "algorithm"};
    Answer answer;
    Gamestate gamestate;
    void initializeGame();
    bool letterIsCorrect(char letter);
    void updateUserInputs(char letter);
    bool isGameOver();
public:
    Hangman();
    void play();
};

// Constructor
Hangman::Hangman() {
    srand(time(NULL)); // initialize random seed
}

// Public member function to play the game
void Hangman::play() {
    initializeGame();
    cout << "Welcome to Hangman!" << endl;
    while (!isGameOver()) {
        // Print current state of game
        cout << "Incorrect letters: ";
        for (char letter : gamestate.incorrectLetters) {
            cout << letter << " ";
        }
        cout << endl << gamestate.displayWord << endl;
        // Ask user for input
        char letter;
        cout << "Enter a letter: ";
        cin >> letter;
        // Check if letter is correct
        bool correct = letterIsCorrect(letter);
        if (correct) {
            updateUserInputs(letter);
            cout << "Correct!" << endl;
        } else {
            gamestate.incorrectLetters.push_back(letter);
            cout << "Incorrect." << endl;
        }
    }
    if (gamestate.displayWord == answer.word) {
        cout << "You win!" << endl;
    } else {
        cout << "You lose! The word was: " << answer.word << endl;
    }
}

// Private member function to initialize the game
void Hangman::initializeGame() {
    // Select random word from possibleWords
    int index = rand() % 5;
    answer.word = possibleWords[index].word;
    // Initialize displayWord with underscores
    for (int i = 0; i < answer.word.length(); i++) {
        gamestate.displayWord += "_";
    }
    // Clear incorrectLetters
    gamestate.incorrectLetters.clear();
}

// Private member function to check if a letter is correct
bool Hangman::letterIsCorrect(char letter) {
    for (int i = 0; i < answer.word.length(); i++) {
        if (answer.word[i] == letter) {
            return true;
        }
    }
    return false;
}

// Private member function to update user inputs
void Hangman::updateUserInputs(char letter) {
    for (int i = 0; i < answer.word.length(); i++) {
        if (answer.word[i] == letter) {
            gamestate.displayWord[i] = letter;
        }
    }
}

// Private member function to check if the game is over
bool Hangman::isGameOver() {
    if (gamestate.incorrectLetters.size() == 6) {
        return true; // game over, player lost
    }
    if (gamestate.displayWord == answer.word) {
        return true; // game over, player won
    }
    return false; // game not over yet
}

// Main function
int main() {
    Hangman* game = new Hangman();
    game->play();
    delete game;
    return 0;
}