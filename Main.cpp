#include "MentalMath.h"
#include <iostream>

int main(int argc, char* argv[]) {
    /* param: mode, length, difficulty
        mode:   1 - mixed
                2 - 11 * 
                3 - addition
                4 - subtraction
                5 - 2 digit multiplication
                6 - mixed decimal
        length: 1 - 10 questions
                2 - 80 questions
        difficulty: 1 - easy
                    2 - hard
    */

    (void) argc;
    int mode = atoi(argv[1]);
    int length = atoi(argv[2]);
    int difficulty = atoi(argv[3]);
    MentalMath *m = new MentalMath(mode, length, difficulty);
    m -> test();
    return 0;
}