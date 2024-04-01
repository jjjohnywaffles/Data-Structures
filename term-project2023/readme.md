# CSPB 2270 – Data Structures - Term Project
#
# This program recreates a classic word game called hangman where the goal of the game
# is to guess a random word before the drawing of a man is completed. 
# This program requires the build folder included within this program alongside a .txt
# file which holds the random words the program is able to pick from. 
# In order to compile the program, navigate to the "build" folder by typing the following into console:
# 1) cd term-project-jjjohnywaffles
# 2) cd build
# 3) cmake ..
# 4) make
# Once these steps are completed, a new executable is created called run_app_1.
# You are able to run the program by executing the command, ./run_app_1
# As long as the WordList.txt file is also within the build folder, the program will work. 
# 
# The data structure I have decided to use for this program are vectors. While there are some small uses of arrays, vectors are the primary data structure used.
# I have decided to utilize vectors since they are used to store and manipulate data in a flexible and efficient manner. 
# Specifically, the program uses vectors to store the word list, the blank letters, the score list, and the list of previously used letters.
# Using vectors for storing these various lists allows the program to easily access and manipulate the words in the list. 
# Utilizing a vector instead of an array allows for the list to be easily resized and modified without having to create a new array or deal with memory allocation issues.
# Along with this, using vectors for storing the blank letters allows for the program to easily track the letters that have been correctly guessed by the user. 
# This allows for vectors to be resized as needed based on the length of the word being guessed.
