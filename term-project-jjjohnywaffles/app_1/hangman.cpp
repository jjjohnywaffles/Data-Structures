//Author: Jonathan Hu
//Program plays a simple game of hangman selecting a random word and produces a small graphic based on the game state.
//Time Spent: 35 Hours

#include "hangman.h"
using namespace std;

void playGame() {
    const int MAX_LIST = 200;
    const int MAX_SIZE = 200;
    const string WORD_LIST_FILE = "WordList.txt";
    vector<string> words(MAX_SIZE);

    // Open the word list file
    ifstream inputFile(WORD_LIST_FILE);
    if (!inputFile) {
        // Handle the case where the file could not be opened.
        cout << "Incorrect file.\n";
        return;
    }

    // Read in the word list
    readWord(MAX_LIST, inputFile, words);

    // Seed the random number generator with the current time
    srand(time(0));

    // Starts the game
    vector<char> blankLetters(MAX_SIZE);
    vector<int> scoreList(MAX_LIST);
    vector<string> wordsList(MAX_LIST);

    int tryIndex = 0;
    char option;

    do {
        mainMenu();

        //Choose a random word from the list
        int wordIndex = letters(words, blankLetters, MAX_LIST);

        //Play the game and get the score
        int gameScore = guessLetters(words, blankLetters, wordIndex);

        //Ask the user if they want to play again
        cout << "\nDo you want to play again (Input Y or N)?";
        cin >> option;

        //Add the word and score to the lists
        wordsList[tryIndex] = words[wordIndex];
        scoreList[tryIndex] = gameScore;
        tryIndex++;
        
    } while (option == 'y' || option == 'Y');

    // Close the word list file
    inputFile.close();
}


//main menu with options
void mainMenu() {
    char ch;
    cout << "\nWelcome to Hangman!\n" << endl;
    cout << "Press Y to Start the Game\n";
    cout << "Press I for Instructions\n";
    cout << "Press Q to Quit\n";
    cout << "\nEnter your choice: ";
    cin >> ch;
    switch (ch) {
        case 'y':
        case 'Y':
            break;
        case 'i':
        case 'I':
            showInstructions();
            //show menu again after displaying instructions
            mainMenu(); 
            break;
        case 'q':
        case 'Q':
            exit(0);
        default:
            cout << "\nInvalid choice. Try again.\n";
            //show menu again after invalid input
            mainMenu();    
    }
    cout<<endl;
}

// display instructions
void showInstructions() {
    cout << "\nInstructions:\n";
    cout << "1. A word will be chosen randomly from the list.\n";
    cout << "2. You have to guess the word by entering one letter at a time.\n";
    cout << "3. You have 7 chances to guess the word. If you fail to guess the word in 7 attempts, you lose.\n";
    cout << "4. Good Luck!\n";
}

//Generates a random word
int letters(const vector<string> &words, vector<char> &blank_letter, const int MAX_LIST) {
    int random_word = rand() % MAX_LIST; // select a random number between 0 and MAX_LIST-1
    for (int blanks = 0; blanks < words[random_word].length(); blanks++){
        blank_letter[blanks] = '_'; // initialize the blank_letter vector with underscores
        cout << blank_letter[blanks] << " "; // display the underscores on the screen
    }
    cout<<endl;
    return random_word; // return the index of the selected word
}

//reads the input file
void readWord(const int MAX_LIST, ifstream &inputFile, vector<string> &words){
    int i = 0;
    while (i < MAX_LIST && getline(inputFile, words[i])) {
        i++;
    }
}

//prints out previously used letters
void gameState(const vector<char>& used_letters) {
    if (!used_letters.empty()) {
        cout << "\n\nPreviously used letters: ";
        for (const char& letter : used_letters) {
            cout << letter << " ";
        }
        cout << endl;
    }
}

// This function takes in a vector of words, a vector of blank letters,
// and a reference to the current word index, and returns a rounded score.
int guessLetters(const vector<string>& words, vector<char>& blank_letter, int& word_index){

    // Initialize variables
    char letter;
    int i = 0;
    int wrong_choice = 0;
    int score = 0, rounded_score = 0;
    const int MAX_GUESS = 26;
    vector<char> used_letters;

    // Loop until the maximum number of guesses is reached
    while (i < MAX_GUESS) {

        // Prompt the user for a letter
        cout << "\n\nEnter your letter: ";
        cin >> letter;

        // Add the user's letter to the used_letters vector
        used_letters.push_back(letter);

        // Call the gameState function to update the game state
        gameState(used_letters);

        // Initialize variables for searching the word for the guessed letter
        int search_letter = 0;
        int count_letter = 0;
        bool found_letter = false;

        // Loop through each letter of the word to check if it matches the guessed letter
        while (search_letter < words[word_index].length()) {

            // If the letter has already been guessed, tell the user and do nothing
            if (blank_letter[search_letter] == letter) {
                cout << "You already guessed that letter!";
            }

            // If the letter matches the guessed letter, replace the blank with the letter
            // and set found_letter to true
            if (words[word_index][search_letter] == letter) {
                blank_letter[search_letter] = letter;
                found_letter = true;
                score++;
            }
            search_letter++;
        }

        // Increment the guess counter
        i++;

        // Count the number of letters that have been found
        int j = 0;
        while (j < words[word_index].length()) {
            if (blank_letter[j] != '_')
                count_letter++;
            j++;
        }

        // Display the current state of the word
        int k = 0;
        while (k < words[word_index].length()) {
            cout << blank_letter[k] << " ";
            k++;
        }
        cout<<endl;
        // If the guessed letter was not found, increment the wrong_choice counter
        if (!found_letter) {
            cout << "\n\nWrong letter!\n";
            wrong_choice++;
        }
        // Call the hangmanFigure function to display the current state of the hangman figure
        int check = hangmanFigure(wrong_choice, words, word_index);
        rounded_score = 0;

        // If all the letters have been found and the hangman figure is complete,
        // the user wins the game
        if (count_letter == words[word_index].length() && check == 0) {
            cout << "\nCongrats! You've Guessed the Correct Word!";
            if (wrong_choice == 0) {
                cout << "\nNo Mistakes! Congrats!";
            }
            break;
        }
        // If the hangman figure is complete, the user loses the game
        else if (check == -1) {
            break;
        }
    }
    // Return the rounded score
    return rounded_score;
}

//show visual gamestate
int hangmanFigure(int wrong_choice, const vector<string>& words, int word_index)
{
    if (wrong_choice == 0) {
        cout << "--------" << endl;
        cout << "|      |" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|-------" << endl;
    } else if (wrong_choice == 1) {
        cout << "--------" << endl;
        cout << "|      |" << endl;
        cout << "|      O" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|-------" << endl;
    } else if (wrong_choice == 2) {
        cout << "--------" << endl;
        cout << "|      |" << endl;
        cout << "|      O" << endl;
        cout << "|      |" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|-------" << endl;
    } else if (wrong_choice == 3) {
        cout << "--------" << endl;
        cout << "|      |" << endl;
        cout << "|      O" << endl;
        cout << "|     /|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|-------" << endl;
    } else if (wrong_choice == 4) {
        cout << "--------" << endl;
        cout << "|      |" << endl;
        cout << "|      O" << endl;
        cout << "|     /|\\" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|-------" << endl;
    } else if (wrong_choice == 5) {
        cout << "--------" << endl;
        cout << "|      |" << endl;
        cout << "|      O" << endl;
        cout << "|     /|\\" << endl;
        cout << "|     /" << endl;
        cout << "|" << endl;
        cout << "|-------" << endl;
    } else if (wrong_choice == 6) {
        cout << "--------" << endl;
        cout << "|      |" << endl;
        cout << "|      O" << endl;
        cout << "|     /|\\" << endl;
        cout << "|     / \\" << endl;
        cout << "|" << endl;
        cout << "|-------" << endl;
        cout << "\n\nGAME OVER!";
        cout << "\nYour word was " << words[word_index];
        return -1;
    }
    return 0;
}