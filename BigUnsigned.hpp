/** ***************************************************************************
 * Assignment: Exercise 4                                                    *
 * Original Author: Ace Programmer                                           *
 * Date: 28 September 2022                                                   *
 * Modified by: EPIC Analysts                                                *
 * Date: October 2022                                                        *
 * Description: This file contains the description of a class called         *
 *      BigUnsigned.                                                         *
 *                                                                           *
 *****************************************************************************/


#ifndef INC_454_P1_BIGUNSIGNED_HPP
#define INC_454_P1_BIGUNSIGNED_HPP


#include <iostream>

/** ***************************************************************************
 *
 * Class name: BigUnsigned
 * Description: This class is designed to hold unsigned (positive) integer
 * 	values that are too large for the standard C++ unsigned data types.
 *
 *****************************************************************************/

class BigUnsigned
{
public:
    BigUnsigned();
    ~BigUnsigned();
    BigUnsigned(const BigUnsigned &other);
    BigUnsigned(const std::string &str);
    size_t length() const;
    BigUnsigned &operator = (const BigUnsigned &other);
    BigUnsigned operator + (const BigUnsigned &other) const;
    friend std::ostream &operator << (std::ostream &outs, const BigUnsigned &BU);
    friend std::istream &operator >> (std::istream &ins, BigUnsigned &BU);

    BigUnsigned(unsigned V);
    bool operator == (const BigUnsigned &other) const;
    bool operator < (const BigUnsigned &other) const;
    BigUnsigned operator += (const BigUnsigned &other);
    BigUnsigned operator * (const BigUnsigned &other) const;

private:
    size_t size;
    unsigned char *value;
};


#endif //INC_454_P1_BIGUNSIGNED_HPP
