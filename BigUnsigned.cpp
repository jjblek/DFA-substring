/** ***************************************************************************
 * Assignment: Exercise 4
 * Original Author: Ace Programmer
 * Date: 28 September 2022
 * Modified by: Zach Gassner
 * Date: 4 November 2022
 * Description: This file contains the implementation of the methods of a
 *      class called BigUnsigned. Values are store using the little-endian
 *      paradigm.  A little-endian system stores the least-significant byte
 *      at the smallest address.
 *
*****************************************************************************/

#include "BigUnsigned.hpp"
#include <sstream>
#include <string> // for operator * overload
#include <vector> // for operator * overload


/** ***************************************************************************
 *
 * Function name: BigUnsigned
 * Input parameters: None
 * Returned result: None
 * Description: This is the default constructor. It will initialize a new
 *		BigUnsigned object to 0
 *
 *****************************************************************************/

BigUnsigned::BigUnsigned() {
    size = 1;
    value = new unsigned char[size];
    value[0] = 0;
}

/** ***************************************************************************
 *
 * Function name: ~BigUnsigned
 * Input parameters: None
 * Returned result: None
 * Description: This is the destructor. It will clean up the memory
 *		allocated to a BigUnsigned object when the object goes out
 *		of scope.
 *
 *****************************************************************************/

BigUnsigned::~BigUnsigned() {
    delete [] value;
}

/** ***************************************************************************
 *
 * Function name: BigUnsigned
 * Input parameters: An existing object that will be copied.
 * Returned result: None
 * Description: This is the copy constructor. It will initialize a new
 *		BigUnsigned object as a copy of an existing BigUnsigned
 *		object.
 *
 *****************************************************************************/

BigUnsigned::BigUnsigned(const BigUnsigned &other) {
    size = other.size;
    value = new unsigned char [size];
    for (int i = 0; i < size; i++)
        value[i] = other.value[i];
}

/** ***************************************************************************
 *
 * Function name: BigUnsigned
 * Input parameters: A string containing an unsigned nummeric value.
 * Returned result: None
 * Description: This is an additional constructor that will initialize a new
 *		BigUnsigned object by converting a string parmeter to a
 *		BigUnsigned value.
 *
 *****************************************************************************/

BigUnsigned::BigUnsigned(const std::string &str) {
    std::string temp;
    int i = 0;
    // ignore leading white space
    while (isspace (str[i]))
        i++;
    // ignore leading zeros
    while (str[i] == '0')
        i++;
    // collect digits from the input string
    while (isdigit (str[i]))
        temp += str[i++];
    // if not digits have been collected set the string to "0"
    if (temp.length() == 0)
        temp = "0";
    // determine the number of digits in the string
    size = temp.length();
    // create a dynamic arry to hold the object's value
    value = new unsigned char [size];
    // copy the digits from the string to the dynamic array.
    int j = 0;
    for (int i = temp.length()-1; i >= 0; i--)
        value[j++] = temp[i] - '0';
}

/** ***************************************************************************
 *
 * Function name: length
 * Input parameters: None
 * Returned result: An unsigned integer value
 * Description: This function will return a count of the number of
 *		significant digits in an existing BigUnsigned object.
 *
 *****************************************************************************/

size_t BigUnsigned::length() const {
    return size;
}

/** ***************************************************************************
 *
 * Function name: operator =
 * Input parameters: An existing object that will be copied.
 * Returned result: The object that has been modified by this operator.
 * Description: This is the assignment operator. It will reinitialize an
 *		existing BigUnsigned object as a copy of an existing
 *		BigUnsigned object.
 *
 *****************************************************************************/

BigUnsigned &BigUnsigned::operator = (const BigUnsigned &other) {
    if (this == & other)
        return * this;
    size = other.size;
    delete [] value;
    this->value = new unsigned char [size];
    for (int i = 0; i < size; i++)
        value[i] = other.value[i];
    return * this;
}

/** ***************************************************************************
 *
 * Function name: opperator +
 * Input parameters: An existing BigUnsigned opject.
 * Returned result: A new BigUnsigned object containing the result of the
 *		addition operation.
 * Description: This function will add the value in the BigUnsigned object
 *		passed as a parameter to the value in the BigUnsigned object
 *		referred to as "*this". The sum will be stored in a new
 *		BigUnsigned object.
 *
 *****************************************************************************/

BigUnsigned BigUnsigned::operator + (const BigUnsigned &other) const {
    BigUnsigned sum;
    delete [] sum.value;
    sum.size = (size > other.size ? size : other.size);
    sum.value = new unsigned char [sum.size];
    int carry = 0;
    int p = 0;
    while (p < size && p < other.size) {
        int s = carry + value[p] + other.value[p];
        sum.value[p] = s % 10;
        carry = s / 10;
        p++;
    }

    while (p < size) {
        int s = carry + value[p];
        sum.value[p] = s % 10;
        carry = s / 10;
        p++;
    }

    while (p < other.size) {
        int s = carry + other.value[p];
        sum.value[p] = s % 10;
        carry = s / 10;
        p++;
    }

    if (carry != 0) {
        BigUnsigned temp = sum;
        delete [] sum.value;
        sum.size++;
        sum.value = new unsigned char [sum.size];
        for (int i = 0; i < sum.size - 1; i++)
            sum.value[i] = temp.value[i];
        sum.value[sum.size - 1] = carry;
    }

    return sum;
}

/** ***************************************************************************
 *
 * Function name: operator <<
 * Input parameters: An output stream and the BigUnsigned object to be
 *		written to the output stream.
 * Returned result: The modified output stream.
 * Description: This is the insertion function. It will write the value
 *		stored in the passed BigUnsigned object to the ostream
 *		as indicated b ythe current iomanipulator settings.
 *
 *****************************************************************************/

std::ostream &operator << (std::ostream &outs, const BigUnsigned &BU) {
    std::stringstream ss;
    for (int i = BU.size-1; i >= 0; i--)
        ss << int(BU.value[i]);
    outs << ss.str();
    return outs;
}

/** ***************************************************************************
 *
 * Function name: operator >>
 * Input parameters: An input stream and the BigUnsigned object to be
 *		read into from the output stream.
 * Returned result: The modified inout stream.
 * Description: This is the extraction function. It will remove characters
 *		that conform to the definition of a BigUnsigned value from
 *		the input stream. It will bypass leading white space and
 *		not store leading zeros in the BigUnsigned object passed
 *		to it.
 *
 *****************************************************************************/

std::istream &operator >> (std::istream &ins, BigUnsigned &BU) {
    std::string value;
    bool zeroFound = false;
    while (isspace (ins.peek()))
        ins.get();
    while (ins.peek() == '0') {
        ins.get();
        zeroFound = true;
    }
    while (isdigit (ins.peek())) {
        char c = ins.get();
        value += c;
    }
    if (value.length() == 0) {
        value = "0";
        if (!zeroFound)
            ins.setstate (std::ios::failbit);
    }
    BU = BigUnsigned (value);
    return ins;
}

/** ***************************************************************************
 *
 * Function name: BigUnsigned
 * Input parameters: An unsigned number
 * Returned result: None
 * Description: This is the unsigned constructor. It will initialize a new
 *              BigUnsigned object to V.
 *
 *****************************************************************************/

BigUnsigned::BigUnsigned (unsigned V) {
    std::string str = std::to_string(V);
    size = str.size();
    value = new unsigned char[size];
    int j = size - 1;
    for (int i = 0; i < size; i++) {
        value[j] = str[i] - '0';
        j--;
    }
}

/** ***************************************************************************
 *
 * Function name: operator ==
 * Input parameters: BigUnsigned object to be compared with.
 * Returned result: True or false.
 * Description: This is the equality operator. It returns true if both
 *              object's values are equal.
 *
 *****************************************************************************/

bool BigUnsigned::operator == (const BigUnsigned &other) const {
    if (size != other.size)
        return false;

    for (int i = 0; i < size; i++)
        if (value[i] != other.value[i])
            return false;

    return true;
}

/** ***************************************************************************
 *
 * Function name: operator <
 * Input parameters: BigUnsigned object to be compared with.
 * Returned result: True or false.
 * Description: This is the less than operator. It returns true if the
 *              number on the left is smaller than the number on right, and
 *			    returns false if the number on the left is greater than or
 *              equal to the number on the right.
 *
 *****************************************************************************/

bool BigUnsigned::operator < (const BigUnsigned &other) const {
    if (size > other.size)
        return false;

    if (size < other.size)
        return true;

    for (int i = size - 1; i >= 0; i--) {
        if (value[i] > other.value[i])
            return false;

        if (value[i] < other.value[i])
            return true;
    }

    return false;
}

/** ***************************************************************************
 *
 * Function name: operator +=
 * Input parameters: BigUnsigned object to be added.
 * Returned result: The object will be modified.
 * Description: This is the += operator. It will the add two objects and
 *              modify the object on the left.
 *
 *****************************************************************************/

BigUnsigned BigUnsigned::operator += (const BigUnsigned &other) {
    BigUnsigned temp = *this + other;
    *this = temp;
    return *this;
}

/** ***************************************************************************
 *
 * Function name: operator *
 * Input parameters: BigUnsigned object to be multiplied.
 * Returned result: A BigUnsigned object that is the product.
 * Description: This is the multiplication operation. It multiplies the two
 *              BigUnsigned objects and returns a new BigUnsigned object.
 *
 *****************************************************************************/

BigUnsigned BigUnsigned::operator * (const BigUnsigned &other) const {
    // strings to hold the numbers to be multiplied
    std::string bigger;
    std::string smaller;

    // BU objects to hold *this and other
    BigUnsigned biggerBU;
    BigUnsigned smallerBU;

    // breaking down the mulitplication into
    // numbers to add after parts of the multiplication
    // has been completed
    //
    // vector to hold numbers to be added after partial
    // multiplication has been done
    std::vector<std::string> numbersToAdd;

    // so we know which number is bigger
    if (*this < other) {
        smallerBU = *this;
        biggerBU = other;
    }
    else {
        smallerBU = other;
        biggerBU = *this;
    }

    // copying the numbers to be muliplied into strings
    for (int i = biggerBU.size - 1; i >= 0; i--)
        bigger += std::to_string(biggerBU.value[i]);

    // copying the numbers to be muliplied into strings
    for (int i = smallerBU.size - 1; i >= 0; i--)
        smaller += std::to_string(smallerBU.value[i]);

    // bool to help concat zero's when needed
    bool addZero = false;

    // accessing each element of bigger number
    for (int i = bigger.size() - 1; i >= 0; i--) {
        int carry = 0;
        int zerosToAdd = 0;

        // string to hold each number to be added
        std::string numberToAdd;

        // finding out how many zeros to concat based on how many iterations
        if (i <= bigger.size() - 2 && addZero)
            zerosToAdd = bigger.size() - i - 1;

        // concat zero(s)
        for (int k = 0; k < zerosToAdd; k++)
            numberToAdd += '0';

        // accessing each element of smaller number
        for (int j = smaller.size() - 1; j >= 0; j--) {
            int tempProduct;
            int big = int(bigger[i] - '0');
            int small = int(smaller[j] - '0');

            // multiplying and adding the carry
            tempProduct = carry + (big * small);

            // concat the value
            numberToAdd += std::to_string(tempProduct % 10);

            carry = tempProduct / 10;
        }

        // concat the carry value
        if (carry != 0)
            numberToAdd += std::to_string(carry);

        // reversing the numberToAdd so it's in the correct order
        std::string reverse;
        for (int i = numberToAdd.size() - 1; i >= 0; i--)
            reverse += numberToAdd[i];

        // numbers to be added after each iteration
        numbersToAdd.push_back(reverse);

        // bool set to true after first iteration
        // so zero's get added
        addZero = true;
    }

    BigUnsigned product;

    // adding all the numbers to add which is the product
    for (auto & i : numbersToAdd) {
        BigUnsigned temp(i);
        product += temp;
    }

    return product;
}


