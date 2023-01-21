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
        BufferManager() {}    //finish me - default constructor
        BufferManager(const BufferManager &aCopy) {} //finish me - copy constructor
        BufferManager(size_t aSize){} //finish me - constructor with predefined size

        //---- Add other ocf methods ---

        //---- Basic methods you must implement. Add more if you need to...
        size_t getCapacity() const;
        T*     getBuffer() const;
        size_t willExpand(size_t aNewSize, size_t anOffset=0);
        size_t willCompact(size_t aNewSize, size_t anOffset=0);

    };

}

#endif /* BufferManager_h */
