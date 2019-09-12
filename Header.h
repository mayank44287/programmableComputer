//
//  Header.h
//  Programmable Calculator
//
//  Created by Mayank Raj on 11/28/18.
//  Copyright © 2018 Mayank Raj. All rights reserved.
// this class serves as the reciever part of the command pattern

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <array>
#include <sstream>
#include <vector>


#ifndef Header_h
#define Header_h
using namespace std;


class Reciever{
public:
    vector<string> tokens;
    array<double, 5> currVal;
    string exp;
};
    

#endif /* Header_h */

