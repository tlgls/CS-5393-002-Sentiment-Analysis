#include "DSString.h"


using namespace std;

/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 *
 * Note that c-strings don's store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable. 
 * DDO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */  

DSString::DSString() : data(nullptr), len(0) {}

DSString::DSString(const char *cstr) {
    if (cstr) {
        len = 0;
        while (cstr[len] != '\0') len++;
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            data[i] = cstr[i]; 
        }
        data[len] = '\0';
    } else {
        data = nullptr;
        len = 0;
    }
}

DSString::DSString(const DSString &other) : len(other.len) {
    data = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        data[i] = other.data[i];
    }
    data[len] = '\0';
}

DSString &DSString::operator=(const DSString &other) {
    if (this == &other) return *this;

    delete[] data;
    len = other.len;
    data = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        data[i] = other.data[i];
    }
    data[len] = '\0';
    return *this;
}

DSString::~DSString() {
    delete[] data;
}

size_t DSString::length() const {
    return len;
}

char &DSString::operator[](size_t index) {
    if (index >= len) throw out_of_range("Index out of range");
    return data[index];
}

char &DSString::operator[](size_t index) const {
    if (index >= len) throw out_of_range("Index out of range");
    return data[index];
}

DSString DSString::operator+(const DSString &other) const {
    DSString result;
    result.len = len + other.len;
    result.data = new char[result.len + 1];
    
    for (size_t i = 0; i < len; ++i) {
        result.data[i] = data[i];
    }
    for (size_t i = 0; i < other.len; ++i) {
        result.data[len + i] = other.data[i];
    }
    result.data[result.len] = '\0';
    return result;
}

bool DSString::operator==(const DSString &other) const {
    if (len != other.len) return false;
    for (size_t i = 0; i < len; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

bool DSString::operator<(const DSString &other) const {
    size_t minLen = (len < other.len) ? len : other.len;
    for (size_t i = 0; i < minLen; ++i) {
        if (data[i] < other.data[i]) return true;
        if (data[i] > other.data[i]) return false;
    }
    return len < other.len;
}

DSString DSString::substring(size_t start, size_t numChars) const {
    if (start >= len) throw out_of_range("Start index out of range");
    size_t end = (start + numChars < len) ? start + numChars : len;
    DSString subStr;
    subStr.len = end - start;
    subStr.data = new char[subStr.len + 1];
    
    for (size_t i = 0; i < subStr.len; ++i) {
        subStr.data[i] = data[start + i];
    }
    subStr.data[subStr.len] = '\0';
    return subStr;
}

DSString DSString::toLower() const {
    DSString lowerStr(*this);
    for (size_t i = 0; i < len; ++i) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            lowerStr.data[i] = data[i] + ('a' - 'A');
        }
    }
    return lowerStr;
}

const char *DSString::c_str() const {
    return data;
}

ostream &operator<<(ostream &out, const DSString &str) {
    if (str.data) out << str.data;
    return out;
}

vector<DSString> DSString::tokenize(DSString delimiter) {
    vector<DSString> tokens;
    size_t start = 0, end = 0;
    
    while (end <= len) {
        if (end == len || data[end] == delimiter.data[0]) {
            if (end > start) {
                tokens.push_back(substring(start, end - start));
            }
            start = end + 1;
        }
        ++end;
    }
    return tokens;
}

istream &getline(istream &in, DSString &str) {
    string temp;
    getline(in, temp);
    str = DSString(temp.c_str());
    return in;
}

istream &getline(istream &in, DSString &str, char delimiter) {
    string temp;
    getline(in, temp, delimiter);
    str = DSString(temp.c_str());
    return in;
}


