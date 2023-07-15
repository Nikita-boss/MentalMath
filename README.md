# Objective
During the preparation for quant interviews I came across various versions of the applications which test your mental arithmetic abilities but none of them had all the features that I required. Therefore, I decided to create my own.

# Description
Application has three input paraments: mode, length, difficulty.
1. Mode - test various arithmetic operations
  1 - mixed
  2 - multiplication by 11 
  3 - addition
  4 - subtraction
  5 - 2 digit multiplication
  6 - mixed decimal
2. Length - number of questions in the test
  1 - 10 questions
  2 - 80 questions
3. Difficulty
  1 - easy
  2 - hard

# Running 
Make the executable file using the makefile. Run the code with the arguments of your choice.
E.g. ./Main 6 2 2 - for an ultimate test

# Result
After the test is complete the user is able to see which questions were answered incorrectly and key performance indicators such as time per question, overall time, etc. The result of the test is saved in the text file in code directory with main metrics.

# Future improvement
Impement Fractions as one of the modes.
