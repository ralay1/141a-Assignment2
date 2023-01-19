//
//  String.hpp
//  Assignment3
//
//  Created by rick gessner on 1/29/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include <iostream>
#include "BufferManager.hpp"
#include "Searchable.hpp"
#include "Sortable.hpp"

//It's up to you to decide the how the string and buffermanager
//will work together -- IS_A vs HAS-A.

namespace ECE141 {


    template<typename T=char, size_t aPresize=32>
    class String {
    public:

        //add rest of the OCF methods...
        String(const String &aString);
        String(const char* aBuffer);

        String& operator=(const String &aCopy);
        //add version to assign from const char*

        size_t size() const {return length;}

        //mutation methods...
        T& operator[](size_t pos);

        String  operator+(const String &aString);
        //add method to add const char*
        //add method to support "hello"+theStringObject

        String& operator+=(const String &aString);
        //add method to append const char*

        String& insert(size_t anIndex, const String &aStr, size_t aStrIndex,
                       size_t aStrCount);
        //add method to insert const char*

        String& insert(size_t anIndex, T aChar);

        String& replace(size_t anIndex, size_t aMaxCopyLen, const String &aString);
        //add method to replace const char*

        String& erase(size_t anIndex, size_t aCount);

        //Comparision methods...
        int compare( const String& aString ) const;
        //add method to add compare const char*

        bool operator==(const String &aString) const {return true;}
        bool operator!=(const String &aString) const {return !(*this==aString);}
        bool operator<(const String &aString) const {return false;}
        bool operator<=(const String &aString) const {return false;}
        bool operator>(const String &aString) const {return false;}
        bool operator>=(const String &aString) const {return false;}
        //Add version(s) to support const char*...

        //Search...
        int find( const String &aString, size_t anIndex = 0 );

        friend std::ostream& operator << (std::ostream &anOut, const String &aStr);
        friend std::istream& operator >> (std::istream &anOut,  String &aString);

        

    protected:
        size_t length;
    };

} //end namespace

#endif /* String_hpp */
