# Project 1

The goal of this project is to compute the number of strings w of length n over {a, b, c, d}
with the following property: In any substring of length 6 of w, all three letters a, b, c and d occur at least once.

The idea is to create a DFA M for the language:
L = {w | in any substring of length 6 of w, all the letters a, b, c and d occur}.
By definition, all strings of length less than 6 are in L.

## Description

* Interface and implementation of DFA M for the language L
* Algorithm to compute the number of strings of length n accepted by a DFA M

## Getting Started

### Executing program

* Execute program
```
cd <working directory>
make
./Project1.x
```
