#pragma once

// #include "iconv.h"
#include <string>
#include <vector>
#include <codecvt>
#include <locale>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdexcept>


using namespace std;

float stringToFloat(const string &s);

// create a simple debugger class to print messages to make it easier to debug
class Debugger {
public:
    static void print(const string &message) {
        cout << message << endl;
    }
};

// string convertEncoding(const string &input, const char *fromEncoding, const char *toEncoding);