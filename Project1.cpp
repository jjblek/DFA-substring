/** ***************************************************************************
 * @assignment: Project 1
 * @remark The goal of the project is to compute the number of strings w
 * of length n over {a, b, c, d} with the following property:
 *  In any substring of length 6 of w, all three letters a, b, c and d
 *  occur at least once.
 * By definition, all strings of length less than 6 are in L
 *
 * @author Zach Gassner & Justin Blechel
 * @file   Project1.cpp
 * @date   Revised February 2, 2023
 *
 *****************************************************************************/


#include "DFA.hpp"
#include <iostream>

/** ***************************************************************************
 * main procedure controls input, DFA, and printing
 * When run, the program asks the user to enter an integer n,
 * If the user enters -1, the program stops.
 * Else it solves the problem for the user input.
 * This dialog is in a loop and repeats testing until the user enters -1.
 *****************************************************************************/

int main() {
    std::cout << "Program to compute the number of strings w of length n over {a, b, c, d} with the following property:\n"
                 "In any substring of length 6 of w, all three letters a, b, c and d occur at least once.\n\n";
    int n = 0;

    while (n != -1) {

        std::cout << "Enter an integer n from 1-300 (-1 to terminate): ";
        std::cin >> n;



        // The range of n will be between 1 and 300.
        if (n < 1 || n > 300) {
            std::cout << "Error: n out of range" <<std::endl;
            continue;
        }
        DFA dfa;
        std::cout << dfa.num_strings_accepted(n) << std::endl;
        n = 0;
    }

    return 0;
}
