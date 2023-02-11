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
#include <map>
//#include "Searchable.hpp"
//#include "Sortable.hpp"

//It's up to you to decide the how the string and buffermanager
//will work together -- IS_A vs HAS-A.

namespace ECE141 {

    enum class Log { JustInsert, JustErase, AppendFront, AppendBack, Normal };
    template<typename T=char, size_t aPresize=32>
    class String : public BufferManager<T> 
    {
    public:

        //add rest of the OCF methods...
        String() {//default ctor 
            BufferManager();
            updateSize();
        }
        String(const String& aString) : BufferManager(aString) {  
            updateSize();
        }
        String(const char* aString) {
            *this = charToString(aString);
            updateSize();
        }
        String(const size_t size) {
            BufferManager((size_t)size);
        }
        ~String() {

        }

        String& operator=(const String& aCopy)
            //add version to assign from const char*
        {
            copyData(aCopy);
            updateSize();
            return *this;
        }
        String& operator=(const char* aCopy)
            //add version to assign from const char*
        {
            *this = charToString(aCopy);
            return *this;
        }

        size_t size() const {return length;}

        String charToString(const char* aCharStar) {
            String temp = String();
            int len = sizeCharStar(aCharStar);
            temp.copyCharData(aCharStar, len);
            temp.updateSize();
            return temp;
        }

        size_t sizeCharStar(const char* aCharStar) {
            size_t count = 0;
            while (aCharStar[count] != '\0') {
                count++;
            }
            return count;
        }

        //mutation methods...
        T& operator[](size_t pos) {
            return getBuffer()[pos];
        }         
        T& operator[](size_t pos) const {
            return getBuffer()[pos];
        }

        size_t updateSize() {
            length = findEndIndex(*this);
            return length;
        }

        String  operator+(const String& aString)
            //add method to support "hello"+theStringObject
        {
            return plus(aString);
        }
        String  operator+(const char* aCharStar)
            //add method to add const char*
        {
            String temp = charToString(aCharStar);
            return *this + temp;
        }
        String plus(const String& moreData) {
            String temp = String();
            int i = 0;
            if (willExpand(moreData.length)) { temp.expand(length + moreData.length); }
            else { temp.expand(length); }
            while (data[i] != '\0') {
                temp.data[i] = data[i];
                i++;
            }
            i = 0;
            while (moreData.data[i] != '\0') {
                temp.data[i+length] = moreData[i]; 
                i++;
            }
            temp.data[length+moreData.length] = '\0';
            temp.updateSize();
            return temp;
        }
        size_t findEndIndex(const String& aString) {
            int i = 0;
            while (aString.data[i] != '\0') {
                i++;
            }
            return i;
        }

        String& operator+=(const String& aString){
            plus(aString);
            updateSize();
            return *this;
        }
        String& operator+=(const char* aString) {
            //add method to append const char*
            String temp = charToString(aString);
            *this += temp;
            return *this;
        }

        String keepPortion(const String& aString, size_t startPos, size_t len) {
            String temp = String(len);
            for (int i = startPos; i < len; i++) {
                temp[i] = aString[i];
            }
            return temp;
        }
        String keepEndPortion(const String& aString, size_t startPos) {
            String temp = String(aString.size()-startPos);
            for (int i = startPos; i < aString.size(); i++) {
                temp[i] = aString[i];
            }
            return temp;
        }
        String& eraseEnd(size_t index) {
            for (int i = index; i < size(); i++) {
                data[i] = NULL;
            }
            return *this;
        }

        String& insert(size_t anIndex, const String& aStr, size_t aStrIndex,
            size_t aStrCount)
        {
            if (willExpand(aStr.size() - aStrCount)) {
                expand(aStr.size() - aStrCount);  
            }
            String lastPortion = keepEndPortion(*this, anIndex);
            String middlePortion = keepPortion(aStr, aStrIndex, aStrCount);
            eraseEnd(aStrIndex);
            *this += middlePortion;
            *this += lastPortion;
            return *this;
        }
        //add method to insert const char*
        String& insert(size_t anIndex, const char* aStr, size_t aStrIndex,
            size_t aStrCount)
        {
            String temp = aStr;
            if (willExpand(temp.size() - aStrCount)) {
                expand(temp.size() - aStrCount);
            }
            String lastPortion = keepEndPortion(*this, anIndex);
            String middlePortion = keepPortion(aStr, aStrIndex, aStrCount);
            eraseEnd(aStrIndex);
            *this += middlePortion;
            *this += lastPortion;
            return *this;
        }
        String& insert(size_t anIndex, T aChar) {
            if (willExpand(1)) {
                expand(1);
            }
            String lastPortion = keepEndPortion(*this, anIndex);
            String middlePortion = aChar;
            eraseEnd(anIndex);
            *this += middlePortion;
            *this += lastPortion;
            return *this;
        }

        Log replaceMap(size_t anIndex, size_t aMaxCopyLen, const String& aString) {
            if (aMaxCopyLen == 0) { return Log::JustInsert; }
            else if (aString.size() == 0) { return Log::JustErase; }
            else if (anIndex == 0 && aMaxCopyLen == 0) { return Log::AppendFront; }
            else if (anIndex == size() - 1 && aMaxCopyLen == 0) { return Log::AppendBack; }
            else
                return Log::Normal;
        }

        String& replace(size_t anIndex, size_t aMaxCopyLen, const String& aString) {
            if (aString.size() - aMaxCopyLen > 0) {
                if (willExpand(aString.size() - aMaxCopyLen)) {
                    expand(aString.size() - aMaxCopyLen);
                }
            }
            if (replaceMap(anIndex, aMaxCopyLen, aString) == Log::JustInsert) {
                insert(anIndex, aString, 0, aString.size());
            }
            else if (replaceMap(anIndex, aMaxCopyLen, aString) == Log::JustErase) {
                erase(anIndex, aMaxCopyLen);
            }
            else if (replaceMap(anIndex, aMaxCopyLen, aString) == Log::AppendFront) {
                insert(0, aString, 0, aString.size());
            }
            else if (replaceMap(anIndex, aMaxCopyLen, aString) == Log::AppendBack) {
                insert(size() - 1, aString, 0, aString.size());
            }
            else
            {
                erase(anIndex, aMaxCopyLen);
                insert(anIndex, aString, 0, aString.size());
            }
            return *this;
        }
        //add method to replace const char*
        String& replace(size_t anIndex, size_t aMaxCopyLen, const char* aString) {
            String temp = aString;
            return replace(anIndex, aMaxCopyLen, aString);
        }

        String& erase(size_t anIndex, size_t aCount) {
            String lastPortion = keepPortion(*this, anIndex, aCount);
            eraseEnd(anIndex);
            *this += lastPortion;
            return *this;
        }
        //Comparision methods...
        int compare(const String& aString) const {
            if (size() > aString.size()) { return 1; }
            else if (size() < aString.size()) { return -1; }
            else {
                for (int i = 0; i < size(); i++) {
                    if (this[i] > aString[i]) { return 1; }
                    else if  (this[i] < aString[i]) { return -1; }
                }
                return 0;
            }
                

        }
        //add method to add compare const char*
        int compare(const char* aString) const {
            String temp = aString;
            compare(temp);
        }

        bool operator==(const String& aString) const {
            if (size() != aString.size()) { return false; }
            for (int i = 0; i < size(); i++) {
                if (this[i] != aString[i]) { return false; }
            }
            return true;
        }
        bool operator!=(const String &aString) const {return !(*this==aString);}
        bool operator<(const String& aString) const {
            if (size() < aString.size()) { return true; }
            else {
                for (int i = 0; i < size(); i++) {
                    if (this[i] < aString[i]) { return true; }
                }
                return false;
            }
        }
        bool operator<=(const String& aString) const { return (*this < aString || *this == aString); }
        bool operator>(const String& aString) const { return !(*this < aString); }
        bool operator>=(const String &aString) const {return (*this > aString || *this == aString);
        }
        //Add version(s) to support const char*...
        bool operator==(const char* aString) { 
            String temp = aString;
            return *this == temp;
        }
        bool operator!=(const char* aString) { return !(*this == aString); }           
        bool operator<(const char* aString) {
            String temp = aString;
            return *this < temp;
        }
        bool operator<=(const char* aString) const { return (*this < aString || *this == aString); }
        bool operator>(const char* aString) const { return !(*this < aString); }
        bool operator>=(const char* aString) const { return (*this > aString || *this == aString); }
            
        
            

        //Search...
        String slice(int leftBound, int rightBound) {
            String temp = String(*this);
            temp.erase(rightBound, temp.size() - temp.size()-1);
            temp.erase(0, leftBound);
            return temp;
        }
        int find(const String& aString, size_t anIndex = 0) {
            int count = 0;
            String comp;
            for (int i = anIndex; i < size() - aString.size(); i++) {
                comp = slice(i, i + aString.size() - 1);
                if (comp == aString) {
                    return i;
                }
            }
            return -1;
        }
        int find(const char* aString, size_t anIndex = 0) {
            String temp = aString;
            return find(temp, anIndex = 0);
        }

        friend std::ostream& operator << (std::ostream &anOut, const String &aStr);
        friend std::istream& operator >> (std::istream &anOut,  String &aString);



    protected:
        size_t length;
    };

} //end namespace

#endif /* String_hpp */
