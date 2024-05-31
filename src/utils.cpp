#include "utils.hpp"

/* string convertEncoding(const string& input, const char* fromEncoding, const char* toEncoding) {
    iconv_t cd = iconv_open(toEncoding, fromEncoding);
    if (cd == (iconv_t)-1) {
        cerr << "Error: iconv_open failed" << endl;
        return input; // Return input unchanged on failure
    }

    size_t inSize = input.size();
    size_t outSize = inSize * 2; // Allocate enough space for UTF-8
    const char* inBuf = const_cast<char*>(input.c_str());
    char* outBuf = new char[outSize];
    char* outPtr = outBuf;

    memset(outBuf, 0, outSize);

    const char* inBufPtr = inBuf;

    if (iconv(cd, &inBufPtr, &inSize, &outPtr, &outSize) == (size_t)-1) {
        cerr << "Error: iconv failed" << endl;
        iconv_close(cd);
        delete[] outBuf;
        return input; // Return input unchanged on failure
    }

    string result(outBuf);
    iconv_close(cd);
    delete[] outBuf;

    return result;
} */

float stringToFloat(const string& s) {
    istringstream iss(s);
    float f;
    iss >> f;
    return f;
}