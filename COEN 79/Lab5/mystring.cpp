//Austin Johnson
//Lab 5
//

#include <iostream>
#include <cassert>
#include <string.h>
#include "mystring.h"
#include <cctype>                                                       

using namespace std;

namespace coen79_lab5 {
    
    //Assigns the appropriate values to member variables
    string::string(const char str[]) {
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }

    //Assigns the appropriate values to member variables
    string::string(char c) {
        current_length = 1;
        allocated = 2;
        characters = new char[2];
        characters[0] = c;
        characters[1] = '\0';
    }

    //Assigns the appropriate values to member variables
    string::string(const string& source) {
        current_length = source.current_length;
        allocated = source.allocated;
        characters = new char[source.current_length];
        strncpy(characters, source.characters, source.current_length);
    }

    //deletes characters and set member variables to 0
    string::~string() {
        current_length = 0;
        allocated = 0;
        delete[] characters;
    }

    //makes space for new addend. Uses strncat to add the string to the end
    void string::operator+=(const string& addend) {
        current_length = current_length + addend.current_length;        
        allocated = current_length + 1;                                 
        reserve(allocated);                                             
        strncat(characters, addend.characters, addend.current_length);  
    }

    //makes space for new addend. Uses strncat to add the char[] to the end
    void string::operator+=(const char addend[]) {
        current_length = current_length + strlen(addend);               
        allocated = current_length + 1;                                 
        reserve(allocated);                                             
        strncat(characters, addend, strlen(addend));
    }

    //makes space for new addend. Uses [] operator to add addend and \0.
    void string::operator+=(char addend) {
        int sumlength = current_length + 1;
        allocated = sumlength + 1;
        reserve(allocated);
        characters[current_length] = addend;
        current_length = sumlength;
        characters[current_length] = '\0';
    }

    //copies the values of characters into a larger array and sets character to that value
    void string::reserve(size_t n) {
        char* temp = new char[n];
        strncpy(temp, characters, current_length);
        allocated = n;
        delete[] characters;
        characters = temp;
    }

    //assigns the values of source to the string and returns *this
    string& string::operator =(const string& source) {
        this->dlt(0, current_length);
        if (current_length != source.current_length) {
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    //inserts a string at characters[position]
    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());
        int sumlength = source.current_length + current_length;
        if (allocated < sumlength)
            reserve(sumlength);
        int i;
        for (i = length(); i > position; i--)
            characters[i] = characters[i - 1];
        for (i = 0; i < source.length(); i++)
            characters[position + i] = source.characters[i];
        current_length = sumlength;
    }

    //deletes a num amount of characters at index position
    void string::dlt(unsigned int position, unsigned int num) {
        assert((position + num) <= length());                         
        for (int i = position; i < length(); i++)                     
            characters[i] = characters[i + num];                      
        current_length = current_length - num;
    }

    //replaces the character at position with c
    void string::replace(char c, unsigned int position) {
        assert(position < length());
        characters[position] = c;
    }

    //replaces characters at indices (position,position+source.length) with source.characters
    void string::replace(const string& source, unsigned int position) {
        assert((position + source.length()) <= length());
        int i;
        for (i = 0; i < source.length(); i++) {
            characters[i + position] = source.characters[i];
        }
    }

    //returns the char at index position
    char string::operator [ ](size_t position) const {
        assert(position < length());
        return characters[position];
    }

    //returns the first index where c appears
    int string::search(char c) const {
        int i;
        for (i = 0; i < current_length; i++)
            if (characters[i] == c)
                return i;
        return -1;
    }

    //returns the first index where substring appears
    int string::search(const string& substring) const {
        char* temp = strstr(characters, substring.characters);
        if (temp != NULL)
            return temp[0] - characters[0];
        return -1;
    }

    //returns the number of times c appears in the string
    unsigned int string::count(char c) const {
        int count = 0, i;
        for (i = 0; i < current_length; i++)
            if (characters[i] == c)
                count++;
        return count;
    }

    //returns s1 + s2
    string operator +(const string& s1, const string& s2) {
        string temp;
        temp += s1;
        temp += s2;
        return temp;
    }

    //returns s1 + addend
    string operator +(const string& s1, const char addend[]) {
        string temp;
        temp += s1;
        temp += addend;
        return temp;
    }

    //stores the input into input and returns it
    std::istream& operator >> (std::istream& ins, string& target) {
        char* buffer = new char[100];                                   
        while (ins && isspace(ins.peek()))                              
            ins.ignore();                                               
        ins >> buffer;                                                  
        target = string(buffer);                                        
        return ins;                                                     
    }

    //outputrs the char array
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.characters;                                      
        return outs;                                                    
    }


    //Friend funtions
    //uses appropriate string functions for each of the boolean expressions
    bool operator ==(const string& s1, const string& s2)                
    {
        return (strcmp(s1.characters, s2.characters) == 0);
    }

    bool operator !=(const string& s1, const string& s2)                
    {
        return (strcmp(s1.characters, s2.characters) != 0);
    }

    bool operator > (const string& s1, const string& s2)                
    {
        return (strcmp(s1.characters, s2.characters) > 0);
    }

    bool operator < (const string& s1, const string& s2)                
    {
        return (strcmp(s1.characters, s2.characters) < 0);
    }

    bool operator >=(const string& s1, const string& s2)                
    {
        return ((s1 > s2) || (s1 == s2));
    }                          

    bool operator <=(const string& s1, const string& s2)                
    {
        return ((s1 < s2) || (s1 == s2));
    }
}

