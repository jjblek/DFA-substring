/** ***************************************************************************
 * @file:   DFA.hpp
 * @author: Zach Gassner & Justin Blechel
 * @date:   16 February 2023
 * @desc:   This file contains the interface of a class called DFA
 *  A DFA (deterministic finite automaton) 'M' is defined by a 5-tuple:
 *      M = <Q, Σ, δ, q₀, F>
 *      - Q: finite set of states
 *      – Σ: finite alphabet
 *      – δ: transition function δ:QxΣ->Q
 *      – q₀∈Q: start state
 *      – F⊆Q: set of accepting states
 *
 *****************************************************************************/

#ifndef INC_454_P1_DFA_HPP
#define INC_454_P1_DFA_HPP


#include "BigUnsigned.hpp"
#include <vector>

class DFA {
public:
    explicit DFA();
    ~DFA();
    BigUnsigned num_strings_accepted(int n);
private:
    static int next_state(const std::string& currentState, char input);
    static bool contains_every_letter(const std::string& str);
    static int encode(const std::string& state);
    static std::string decode(int state);

    // Σ(SIGMA): a finite alphabet represented as an array of length M that contains the input symbols
    enum alphabet {a, b, c, d};

    // transitions for each state depending on which letter is next
    // δ: transition function delta is a 2D vector of size N and M
    std::vector<std::vector<int>> delta;


    // vectors prev and next of length m where m is the number of states.


    // vector that stores the count of strings accepted of length n,
    // initialized at n = 0, so count[0] through count[1364] = 1
    // since they're all accepting states, and count[1365] = 0 since it's
    // dead state
    std::vector<BigUnsigned> count;

};


#endif //INC_454_P1_DFA_HPP
