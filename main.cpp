//
//  main.cpp
//  Assignment2
//
//

#include <iostream>
#include <sstream>
#include <string>
#include "Testable.hpp"
#include "BufferManager.hpp"
#include "MemTrack.hpp"

//---------------------------------

//If this won't compile, your Buffer Managerclass may not be ready.
//If this crashes, check how your Buffer Managerwrites to a stream.
bool doOCFTests(std::ostream &anOutput) {

  MemTrack::list.enable(true);

  {
    ECE141::BufferManager<char> theBuf1(100);
    ECE141::BufferManager<char> theBuf2(theBuf1);

    if(100<theBuf1.getCapacity()) {
      anOutput << "ctor copy failed\n";
      return false;
    }
    
    if(theBuf1.getCapacity()!=theBuf2.getCapacity()) {
      anOutput << "ctor copy failed\n";
      return false;
    }
  }
  
  if(MemTrack::list.leaked()) {
    MemTrack::list.empty(anOutput, "oops, you leaked!");
  }

  return true;
}

bool doExpandTests(std::ostream &anOutput) {

  ECE141::BufferManager<char> theBuf1;
  theBuf1.willExpand(100);
  if(100<theBuf1.getCapacity()) {
    anOutput << "expand failed\n";
  }
  theBuf1.willExpand(200);
  if(200<theBuf1.getCapacity()) {
    anOutput << "expand failed\n";
  }
  return true;
}


bool doCompactTests(std::ostream &anOutput) {
  ECE141::BufferManager<char> theBuf1(100);
  if(100<theBuf1.getCapacity()) {
    anOutput << "expand failed\n";
  }
  theBuf1.willCompact(50);
  if(50<theBuf1.getCapacity()) {
    anOutput << "expand failed\n";
  }
  return true;
}

//-----------------------------------

int main(int argc, const char * argv[]) {
  
    static const char* kMsgs[]={"FAIL","PASS"};
    if(argc>1) {
        std::string temp(argv[1]);
        std::stringstream theOutput;
      

        if("compile"==temp) {
            std::cout << temp << " test " << kMsgs[true] << "\n";
        }
        else if("ocf"==temp) {
            std::cout << temp << " test " << kMsgs[doOCFTests(theOutput)] << "\n";
        }
        else if("expand"==temp) {
          std::cout << temp << " test " << kMsgs[doExpandTests(theOutput)] << "\n";
        }
        else if("compact"==temp) {
            std::cout << temp << " test " << kMsgs[doCompactTests(theOutput)] << "\n";
        }

        std::cout << theOutput.str() << "\n";
    }
        
    return 0;
}

