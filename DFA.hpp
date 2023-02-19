/** ***************************************************************************
 * @file:   DFA.hpp
 * @author: Zach Gassner & Justin Blechel
 * @date:   Revised, 18 February 2023
 * @desc:   This file contains the interface of a class called DFA
 * @remark: A DFA (deterministic finite automaton) 'M' is defined by a 5-tuple:
 *     M = <Q, Σ, δ, q₀, F>
 *      - Q: finite set of states
 *      – Σ: finite alphabet
 *      – δ: transition function δ:QxΣ->Q
 *      – q₀∈Q: start state
 *      – F⊆Q: set of accepting states
 *
 *  This class interfaces a DFA 'M' for the Language 'L':
 *      L={ w | in any substring of length 6 of w,
 *          all the letters a, b, c and d occur }
 *  in order to compute the number of strings of length n accepted by M,
 *  using an efficient counting algorithm
 *
 *  @todo accept alphabets of varying size and symbol composition
 *
 *****************************************************************************/

#ifndef INC_454_P1_DFA_HPP
#define INC_454_P1_DFA_HPP


#include "BigUnsigned.hpp"
#include <vector>
#include <set>
template<typename T>
class DFA {
public:
    explicit DFA();
    ~DFA();
    bool contains_every_letter(const std::string& str);
    BigUnsigned num_strings_accepted(int n);
private:
    int next_state(const std::string& currentState, T input);
    int encode(const std::string& state);
    static std::string decode(int state);

    // Σ(SIGMA): a finite alphabet represented as an array of length M that contains the input symbols
    std::set<T> alphabet {'a', 'b', 'c', 'd'};

    // δ: transition function delta is a 2D vector of size N and M
    std::vector<std::vector<int>> delta;


    std::vector<BigUnsigned> count;

};


#endif //INC_454_P1_DFA_HPP
