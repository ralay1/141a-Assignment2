
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
    BufferManager() {}    //finish me
    BufferManager(const BufferManager &aCopy) {} //finish me
    BufferManager(const char *aBuffer) {}
            
    //---- other ocf methods ---
    
    //---- add BufferManager methods...
    
    friend std::ostream& operator<<(std::ostream& aStream,
                                    const BufferManager& aVar) {
      return aStream;
    }
  };

}

#endif /* BufferManager_h */