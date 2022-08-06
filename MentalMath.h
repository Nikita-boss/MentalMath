#ifndef MENTALMATH_H
#define MENTALMATH_H
#include <vector>
#include <random>
#include <string>
#include <tuple>

class MentalMath {
    private:
        int length;
        int difficulty;
        std::string mode;
        std::mt19937 rng;
        std::vector<double> first{};
        std::vector<double> second{};
        std::vector<double> answer{};
        std::vector<double> myanswer;
        std::vector<char> sign;
        std::tuple<int,int> result();
        void save_result(std::tuple<int,int> output, long time_taken);
        void set_mixed(std::mt19937 rng);
        void set_multiply_11(std::mt19937 rng);
        void set_addition(std::mt19937 rng);
        void set_subtraction(std::mt19937 rng);
        void set_multiplication(std::mt19937 rng);
        void set_decimal_mixed(std::mt19937 rng);
        void set_approximation(std::mt19937 rng);
        void read_from_screen_noChoice(int length);
        void read_from_screen_Choice(int length, int start, std::mt19937 rng);

    public:
        MentalMath(int i=1, int j=1, int k=1);
        ~MentalMath() {};
        void test();
};

#endif