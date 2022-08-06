#include "MentalMath.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>    
#include <fstream>
#include <algorithm>

MentalMath:: MentalMath(int i, int j, int k) {
    length = (j == 1) ? 10:80;
    difficulty = k;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    switch (i) {
        case (1) : mode = "mixed";          set_mixed(rng);         break;
        case (2) : mode = "multiply 11";    set_multiply_11(rng);   break;
        case (3) : mode = "addition";       set_addition(rng);      break;
        case (4) : mode = "subtraction";    set_subtraction(rng);   break;
        case (5) : mode = "multiplication"; set_multiplication(rng);break;
        case (6) : mode = "decimal mixed";  set_decimal_mixed(rng); break; 
        case (7) : mode = "approximation";  set_approximation(rng); break;
        case (8) : mode = "Flow Traders";  
                   this->length = 30; this->difficulty = 1; set_mixed(rng);
                   this->difficulty = 2; set_decimal_mixed(rng);
                   this->length = 15; set_approximation(rng);
                   break;            
    }
}

void MentalMath :: test() {
    std::chrono::system_clock::time_point time1, time2;
    time1 = std::chrono::system_clock::now();
    std::string ans{};
    if (this->mode == "approximation") {
        read_from_screen_Choice(this->length, 0, rng);
    } else if (this->mode == "Flow Traders") {
        read_from_screen_noChoice(60);
        read_from_screen_Choice(15, 60, rng);
    } else {
        read_from_screen_noChoice(this->length);
    }

    time2 = std::chrono::system_clock::now();
    long time_taken = std::chrono::duration_cast<std::chrono::seconds>(time2-time1).count();
    
    std::tuple<int,int> output = result();
    std::cout << "Correct answers: " << std::get<0>(output) << '\n';
    std::cout << "Score: " << std::get<1>(output) << '\n';
    std::cout << "Accuracy: " << std::setprecision(3) << (double) std::get<0>(output)/length * 100 << '%' << '\n';
    std::cout << "Time taken: " << time_taken << " seconds" << '\n'; 
    std::cout << "Average time per question: " << std::setprecision(3) << (double) time_taken / length << " seconds" << '\n';

    save_result(output, time_taken);

}

std::tuple<int,int> MentalMath :: result() {
    int correct{}, score{};

    for (int i{}; i < length; i++) {
        if ((answer[i] - myanswer[i]) <= 0.0001) {
            correct++;
            score++;
        } else {
            if (myanswer[i] == 0) {
                score -= -1;
            } else {
                score -= 2;
            }
            std::cout << "Mistake at " << i+1 << ").";
            std::cout << " Your answer: " << myanswer[i] << '.';
            std::cout << " Correct answer: " << answer[i] << '\n';
        }
    }
    score = (score < 0) ? 0:score;
    return std::make_tuple(correct, score);
}

void MentalMath :: save_result(std::tuple<int,int> output, long time_taken) {
    std::fstream File;
    File.open("result.txt", std::ios::app);
    if (File.is_open()) { 
        File << std::fixed << std::setprecision(1) << (double) std::get<0>(output)/length * 100;
        File << "       " << std::get<1>(output);
        File << "   " << time_taken << "      ";
        File << std::setprecision(1) << (double) time_taken / length;
        File << "   " << mode << '\n';
    }
}

void MentalMath:: set_mixed(std::mt19937 rng) { 
    int upper_limit_add = (this->difficulty == 1) ? 2'000:10'000;
    int upper_limit_subtract = (this->difficulty == 1) ? 2'000:10'000;
    int upper_limit_mult{100}, upper_limit_div{1000};

    std::uniform_real_distribution<double> decider(0, 1);
    std::uniform_int_distribution<int> add(-upper_limit_add, upper_limit_add);
    std::uniform_int_distribution<int> subtract(-upper_limit_subtract, upper_limit_subtract);
    std::uniform_int_distribution<int> multiply(-upper_limit_mult, upper_limit_mult);
    std::uniform_int_distribution<int> divide(1, upper_limit_div);

    int first_number{}, second_number{};
    double temp{};

    for (int i{}; i < this->length; i++) {
        temp = decider(rng);
        if (temp <= 0.25) {

            first_number = add(rng);
            second_number = add(rng);
            first.push_back(first_number);
            second.push_back(second_number);
            answer.push_back(first_number + second_number);
            sign.push_back('+');
       } else if (temp <= 0.5) {
            first_number = subtract(rng);
            second_number = subtract(rng);
            first.push_back(first_number);
            second.push_back(second_number);
            answer.push_back(first_number - second_number);
            sign.push_back('-');
        } else if (temp <= 0.75) {
            // one-fifth are multiplication by 11
            if (temp <= 0.55) {
                first_number = multiply(rng);
                first_number = (first_number == 0) ? multiply(rng):first_number;
                first.push_back(first_number);
                second.push_back(11);
                answer.push_back(first_number * 11);
                sign.push_back('*');
            } else {
                first_number = multiply(rng);
                second_number = multiply(rng);
                first_number = (first_number == 0) ? multiply(rng):first_number;
                second_number = (second_number == 0) ? multiply(rng):second_number;
                first.push_back(first_number);
                second.push_back(second_number);
                answer.push_back(first_number * second_number);
                sign.push_back('*');
            }
       } else {
            first_number = divide(rng);
            second_number = divide(rng);

            if (abs(first_number) < abs(second_number)) {
                std::swap(first_number, second_number); 
            }

            first_number += second_number - first_number % second_number;
            
            first.push_back(first_number);
            second.push_back(second_number);
            answer.push_back(first_number / second_number);
            sign.push_back('/');
        }  
    }
}

void MentalMath:: set_multiply_11(std::mt19937 rng) {
    int upper_limit = (this->difficulty == 1) ? 1'0000:10'000; 
    std::uniform_int_distribution<int> uid(1, upper_limit);
    int first_number{};

    for (int i{}; i < this->length; i++) {
        first_number = uid(rng);
        first.push_back(first_number);
        second.push_back(11);
        sign.push_back('*');
        answer.push_back(first_number * 11);
    }
}

void MentalMath:: set_addition(std::mt19937 rng) {
    int upper_limit = (this->difficulty == 1) ? 2'000:10'000; 
    std::uniform_int_distribution<int> uid(1, upper_limit);
    int first_number{}, second_number{};

    for (int i{}; i < length; i++) {
        first_number = uid(rng);
        first.push_back(first_number);
        second_number = uid(rng);
        second.push_back(second_number);
        answer.push_back(first_number + second_number);
        sign.push_back('+');
    }
}

void MentalMath:: set_subtraction(std::mt19937 rng) {
    int upper_limit = (this->difficulty == 1) ? 2'000:10'000;
    std::uniform_int_distribution<int>uid(1, upper_limit);
    int first_number{}, second_number{};

    for (int i{}; i < length; i++) {
        first_number = uid(rng);
        second_number = uid(rng);
        first.push_back(first_number);
        second.push_back(second_number);
        answer.push_back(first_number - second_number);
        sign.push_back('-');
    }
}

void MentalMath:: set_multiplication(std::mt19937 rng) {
    std::uniform_int_distribution<int>uid(1, 100);
    int first_number{}, second_number{};
    for (int i{}; i < this->length; i++) {
        first_number = uid(rng);
        second_number = uid(rng);
        first.push_back(first_number);
        second.push_back(second_number);
        answer.push_back(first_number * second_number);
        sign.push_back('*');
    }
}

void MentalMath:: set_decimal_mixed(std::mt19937 rng) {
    int upper_limit_add = (this->difficulty == 1) ? 2'000:10'000;
    int upper_limit_subtract = (this->difficulty == 1) ? 2'000:10'000;
    int upper_limit_mult{100}, upper_limit_div{1000};
    std::uniform_int_distribution<int> multiplier(1, 3);
    std::uniform_real_distribution<double> decider(0, 1);
    std::uniform_int_distribution<int> add(-upper_limit_add, upper_limit_add);
    std::uniform_int_distribution<int> subtract(-upper_limit_subtract, upper_limit_subtract);
    std::uniform_int_distribution<int> multiply(-upper_limit_mult, upper_limit_mult);
    std::uniform_int_distribution<int> divide(1, upper_limit_div);

    double first_number, second_number{};
    double decimal{0.001};
    double temp{};

    for (int i{}; i < this->length; i++) {
        temp = decider(rng);
        if (temp <= 0.25) {
            first_number = add(rng) * decimal * pow(10, multiplier(rng));
            second_number = add(rng) * decimal * pow(10, multiplier(rng));
            first.push_back(first_number);
            second.push_back(second_number);
            answer.push_back(first_number + second_number);
            sign.push_back('+');
        } else if(temp <= 0.5) {
            first_number = subtract(rng) * decimal * pow(10, multiplier(rng));
            second_number = subtract(rng) * decimal * pow(10, multiplier(rng));
            first.push_back(first_number);
            second.push_back(second_number);
            answer.push_back(first_number - second_number);
            sign.push_back('-');
        } else if (temp <= 0.75) {
            // one-fifth are multiplication by 11
            if (temp <= 0.55) {
                first_number = multiply(rng) * decimal * pow(10, multiplier(rng));
                first_number = (first_number == 0) ? multiply(rng)*decimal*pow(10,multiplier(rng)):first_number;
                first.push_back(first_number);
                second.push_back(11);
                answer.push_back(first_number * 11);
                sign.push_back('*');
            } else {
                first_number = multiply(rng) * decimal * pow(10, multiplier(rng));
                second_number = multiply(rng) * decimal * pow(10, multiplier(rng));
                first_number = (first_number == 0) ? multiply(rng)*decimal*pow(10,multiplier(rng)):first_number;
                second_number = (second_number == 0) ? multiply(rng)*decimal*pow(10,multiplier(rng)):second_number;
                first.push_back(first_number);
                second.push_back(second_number);
                answer.push_back(first_number * second_number);
                sign.push_back('*');
            }
       } else {
            int tmp_first = divide(rng);
            int tmp_second = divide(rng);

            if (abs(tmp_first) < abs(tmp_second)) {
                std::swap(tmp_first, tmp_second); 
            }

            tmp_first += tmp_second - tmp_first % tmp_second;
            first_number = tmp_first * decimal * pow(10, multiplier(rng));
            second_number = tmp_second * decimal * pow(10, multiplier(rng));
            first.push_back(first_number);
            second.push_back(second_number);
            answer.push_back(first_number / second_number);
            sign.push_back('/');
        }
    }
}

void MentalMath:: set_approximation(std::mt19937 rng) {
    int upper_limit{1'000};
    std::uniform_int_distribution<int>uid(10, upper_limit);
    int first_number{}, second_number{};
    for (int i{}; i < this->length; i++) {
        first_number = uid(rng);
        second_number = uid(rng);
        first.push_back(first_number);
        second.push_back(second_number);
        answer.push_back(first_number * second_number);
        sign.push_back('*');
    }
}

void MentalMath:: read_from_screen_noChoice(int len) {
    std::string ans{};
    for (int i{}; i < len; i++) {
        std::cout << i+1 << ')' << '\n'; 
        std::cout << first[i] << ' ' << sign[i] << ' ' << second[i] << '\n';
        std::cin >> ans;
        this->myanswer.push_back(stod(ans));
        std::cout << '\n';
    } 
}

void MentalMath:: read_from_screen_Choice(int len, int start, std::mt19937 rng) {
    std::string ans{};
    std::uniform_int_distribution<int> choice(0, 2);
    std::vector<double> rows(3, 0);
    std::vector<std::vector<double>> possible_answers(len, rows);
    int first_choice{}, second_choice{};
    int tmp{};
    for (int i{}; i < len; i++) {
        first_choice = this->answer[i+start] + 1'000;
        second_choice = this->answer[i+start] - 1'000;
        possible_answers[i][0] = first_choice;
        possible_answers[i][1] = first_choice;
        possible_answers[i][2] = second_choice;
        tmp = choice(rng);
        possible_answers[i][tmp] = this->answer[i+start];
        if (tmp == 2) {
            possible_answers[i][1] = second_choice;
        }
    }
    for (int i{}; i < len; i++) {
        std::cout << i+1+start << ')' << '\n'; 
        std::cout << first[i+start] << ' ' << sign[i+start] << ' ' << second[i+start] << '\n';
        std::cout << "Possible answers:" << '\n';
        std::cout << "1)  " << possible_answers[i][0] << "  2)  " << possible_answers[i][1] <<
            "  3)  " << possible_answers[i][2] << '\n';
        std::cin >> ans;
        this->myanswer.push_back(possible_answers[i][stoi(ans)-1]);
        std::cout << '\n';
    } 
}
