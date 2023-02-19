/** ***************************************************************************
 * @file:   DFA.cpp
 * @author: Zach Gassner & Justin Blechel
 * @date:   16 February 2023
 * @desc:   This file contains the implementation of a class called DFA
 *  A deterministic finite automaton (DFA) M
 *  is defined by a 5-tuple M = <Q, Σ, δ, q₀, F>
 *      - Q: finite set of states
 *      – Σ: finite alphabet
 *      – δ: transition function δ:QxΣ->Q
 *      – q₀∈Q: start state
 *      – F⊆Q: set of accepting states
 *
 *****************************************************************************/

#include "DFA.hpp"
#include <cmath>     // for std::pow
#include <algorithm> // for std::reverse

/** ***************************************************************************
 * DFA constructor - initialize count and construct delta function
 *****************************************************************************/
DFA::DFA() {
    delta.resize(1366, std::vector<int>(4));
    // vector that stores the count of strings accepted of length n,
    // initialized at n = 0, so count[0] through count[1364] = 1
    // since they're all accepting states, and count[1365] = 0 since it's dead state
    count.resize(1366);
    fill(count.begin(), count.end()-1, 1);

    // transitions for each state depending on which letter is next
    for (int i = 0; i < delta.size(); i++)
        for (int j = 0; j < delta[i].size(); j++)
            delta[i][j] = next_state(decode(i), char(j + 97));
}

/** ***************************************************************************
 * DFA destructor - set to default
 *****************************************************************************/
DFA::~DFA() = default;


/** ***************************************************************************
 * map state buffers to integers from 0 to 1365
 * @param  state: string to encode
 * @pre    character exists in alphabet
 * @post   letter encoded, integer returned
 *****************************************************************************/
int DFA::encode(const std::string& state) {
    double intState = 0;
    int exponent = int(state.size()-1);

    for (auto &symbol: state)
        intState += (symbol - 96) * std::pow(4, exponent--);

    return int(intState);
}


/** ***************************************************************************
 * decode a base-4 encoded string
 * @param  state: integer to decode
 * @pre    string has been encoded
 * @post   integer decoded, string returned
 *****************************************************************************/
std::string DFA::decode(int state) {
    std::string strState;

    while (state > 0) {
        // 96 is ascii for ` but 1 more is a, 2 more b, 3 more c 
        char c = (state % 4) + 96;
        // if letter is d it wants to print ` since 4 % 4 = 0 so 96 + 0 = 96
        // so just make char = 100 which is ascii for 'd', and
        // state-- bc state/=4 will be off by 1 in this case
        if (c == 96) {
            c = 100;
            state--;
        }

        strState += c;
        state /= 4;
    }

    std::reverse(strState.begin(), strState.end());
    return strState;
}


/** ***************************************************************************
 * map a string to a positive integer using base-4 encoding
 * @param  s: string to encode
 * @pre    letters exists in alphabet
 * @post   return next state
 *****************************************************************************/
// takes a state and an input as param, returns next state
int DFA::next_state(const std::string& currentState, char input) {
    std::string nextState = currentState + input;

    // dead state will always stay in dead state
    if (encode(currentState) == 1365)
        return 1365;

    // will always transition to an accepting state
    if (currentState.size() < 5)
        return encode(nextState);

    return contains_every_letter(nextState) ?
        encode(nextState.substr(1, nextState.size() - 1)) : 1365;
}


/** ***************************************************************************
 * check if all four letters a, b, c and d occur at least once in a string
 * @param  str: string to check
 * @pre    letters exist in alphabet
 * @post   return true if all letters occur once, else return false
 *****************************************************************************/
bool DFA::contains_every_letter(const std::string& str) {
    bool A=false, B=false, C=false, D=false;

    for (char symbol : str) {
        if (symbol == 'a') A = true;
        else if (symbol == 'b') B = true;
        else if (symbol == 'c') C = true;
        else if (symbol == 'd') D = true;
    }

    return (A && B && C && D);
}


/** ***************************************************************************
 * compute the number of strings of length n accepted by M
 * @param  n: number of strings of length n
 * @pre    1 <= n <= 300
 * @post   return number of strings
 *****************************************************************************/
// calculate number of strings of length n accepted by the DFA
BigUnsigned DFA::num_strings_accepted(int n) {
    for (int k = 0; k < n; k++) {
        std::vector<BigUnsigned> previous = count;
        for (int i = 0; i < count.size(); i++) {
            BigUnsigned nextCount;
            for (int j = 0; j < 4; j++) {
                int t_state = delta[i][j];
                nextCount += previous[t_state];
            }
            count[i] = nextCount;
        }
    }

    // count from state 0, the starting state
    return count[0];
}
