/** ***************************************************************************
 * @file:   DFA.cpp
 * @author: Zach Gassner & Justin Blechel
 * @date:   16 February 2023
 * @remark: This file contains the implementation of a class called DFA
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
 *
 *****************************************************************************/
template<typename T>
DFA<T>::DFA() {
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
 *
 *****************************************************************************/
template<typename T>
DFA<T>::~DFA() = default;


/** ***************************************************************************
 * map state buffers to integers from 0 to 1365
 * @param  state: string to encode
 * @pre    character exists in alphabet
 * @post   letter encoded, integer returned
 *
 *****************************************************************************/
template<typename T>
int DFA<T>::encode(const std::string& state) {
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
 *
 *****************************************************************************/
template<typename T>
std::string DFA<T>::decode(int state) {
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
 * accept as parameters a state buffer and input
 *  and return the next state buffer
 * @param  currentState: the current state buffer
 * @param  input: the input to be added to the state buffer
 * @pre    currentState.size <= 5
 * @post   return next state
 *
 *****************************************************************************/
template<typename T>
int DFA<T>::next_state(const std::string& currentState, T input) {
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
 * check if all letters of an alphabet occur at least once in a string
 * @param  str: string to check
 * @pre    letters exist in alphabet
 * @post   return true if all letters occur at least once, else return false
 *
 *****************************************************************************/
template<typename T>
bool DFA<T>::contains_every_letter(const std::string& str) {
    int flag = 1; // count of unique symbols

    std::string temp = str;
    std::sort(temp.begin(), temp.end());

    // loop through the sorted string and count unique symbols
    for (int i = 1; i < temp.size(); ++i)
        if (temp[i] > temp[i-1]) flag++;

    // if the count of unique symbols is equal to the size of the alphabet,
    // return true, else return false
    return flag == alphabet.size();
}


/** ***************************************************************************
 * compute the number of strings of length n accepted by M
 * @remark: Keep track of the previous count to get the next count
 *  count(q, j) = (count(transitions[q][a]), j - 1) +
 *                (count(transitions[q][b]), j - 1) +
 *                (count(transitions[q][c]), j - 1) +
 *                (count(transitions[q][d]), j - 1)
 *
 * @param:  n: number of strings of length n
 * @pre:    1 <= n <= 300
 * @post:   return number of strings accepted of length n
 *
 *****************************************************************************/
template<typename T>
BigUnsigned DFA<T>::num_strings_accepted(int n) {
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

template class DFA<char>;