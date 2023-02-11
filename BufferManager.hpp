//
//  BufferManager.hpp
//  Assignment2
//
//

#ifndef BufferManager_h
#define BufferManager_h
#include <iostream>

namespace ECE141   {


    template <typename T>
    class BufferManager {

    public:
        int arraySize;
        T* data;
    public:
        BufferManager() {
            data = new T[0];
            arraySize = 0;
        }   
        BufferManager(const BufferManager& aCopy) { //finish me - copy constructor
            arraySize = 0;
            copyData(aCopy);
        }
        BufferManager(size_t aSize) { //finish me - constructor with predefined size
            data = new T[aSize+1];
            arraySize = aSize;
        }
        BufferManager(T* values) {
            data = values;
        }
        
        

        //---- Add other ocf methods ---
        BufferManager& operator = (const BufferManager& aCopy) {
            data = aCopy.data;
            return *this;
        }
        BufferManager& setTo(const BufferManager& aCopy) { //not overloaded by string
            data = aCopy.data;
            return *this;
        }
        ~BufferManager() {
            delete[] data;
        }


        //---- Basic methods you must implement. Add more if you need to...
        size_t getCapacity() const {
            return arraySize;
        };
        T* getBuffer() const {
            return data;
        }

        void copyData(const BufferManager& aCopy) {
            if (willExpand(aCopy.getCapacity())) { 
                expand(aCopy.getCapacity()); 
            }
            int i = 0;
            while (aCopy.data[i] != '\0') {
                 data[i] = aCopy.data[i];
                 i++;
            }
            data[getCapacity()] = '\0';
        }

        void copyCharData(const char* aCopy, int length) {
            if (willExpand(length)) { expand(length); }
            int i = 0;
            while (aCopy[i] != '\0') {
                data[i] = aCopy[i];
                i++;
            }
            data[length] = '\0';
        }

        // append to front
        // append to back
        // insert
        // replace
        // remove
        size_t willExpand(size_t aNewSize, size_t anOffset = 0) {
            if (getCapacity() < aNewSize+1) {
                //data = new char[aNewSize+10];
                return 1;
            }
            return 0;
        }
        size_t willCompact(size_t aNewSize, size_t anOffset = 0) {
            if (aNewSize+1 < getCapacity()-10) {
                //data = new char[aNewSize + 10];
                return 1;
            }
            return 0;
        }
        void expand(size_t aNewSize) {
            data = new T[aNewSize + 10];
            arraySize = aNewSize+10;
        }
        void compact(size_t aNewSize) {
            data = new T[aNewSize +1];
        }
        
    };

}

#endif /* BufferManager_h */
