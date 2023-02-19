/** ***************************************************************************
 * @assignment: Project 1
 * @file:   Project1.cpp
 * @author: Zach Gassner & Justin Blechel
 * @date:   Revised: 18 February 2023
 * @desc:   main procedure and test cases
 * @remark: The goal of the project is to compute the number of strings w
 * of length n over {a, b, c, d} with the following property:
 *  In any substring of length 6 of w, all three letters a, b, c and d
 *  occur at least once.
 *  By definition, all strings of length less than 6 are in L
 *
 *****************************************************************************/


#include "DFA.hpp"
#include <iostream>
#include <fstream>


void writeTestcases();

/** ***************************************************************************
 * write test cases to the file 'testcases.txt'
 * compute the number of strings of length n accepted
 * where 1 <= n <= 300 for all n cases
 *****************************************************************************/
void writeTestcases() {
    std::ofstream testcases;
    testcases.open("testcases.txt");
    testcases << "n:\tnumber of strings of length n accepted" << std::endl;
    for (int i = 1; i <= 300; ++i) {
        DFA<char> dfa;
        testcases << i << ":\t" << dfa.num_strings_accepted(i) << std::endl;
    }
    testcases.close();
}

/** ***************************************************************************
 * main procedure controls input, DFA, and printing
 * When run, the program asks the user to enter an integer n,
 * If the user enters -1, the program stops.
 * Else it solves the problem for the user input.
 * This dialog is in a loop and repeats testing until the user enters -1.
 *****************************************************************************/
int main() {
    std::cout << "Program to compute the number of strings w "
                 "of length n over {a, b, c, d} with the following property:\n"
                 "In any substring of length 6 of w, "
                 "all three letters a, b, c and d occur at least once.\n\n";
    int n = 0;

    // dialog loop
    while (n != -1) {

        std::cout << "Enter an integer 'n' from 1-300 (-1 to terminate): ";
        std::cin >> n;

        // The range of n will be between 1 and 300
        if (n < 1 || n > 300) {
            std::cout << "Error: integer 'n' is out of range" <<std::endl;
            continue;
        }

        DFA<char> dfa; // construct DFA M

        // print the number of strings of length n accepted by the DFA M
        std::cout << dfa.num_strings_accepted(n) << std::endl;

    }

    //writeTestcases();

    return 0;
}
