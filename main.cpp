//
//  main.cpp
//  Assignment2
//
//

#include <iostream>
#include <sstream>
#include <string>
#include "autotest.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <memory>

//-----------------------------------

int main(int argc, const char * argv[]) {
    static const char* kMsgs[]={"FAIL","PASS"};
    if(argc>1) {
        std::string temp(argv[1]);
        std::stringstream theOutput;

        srand(static_cast<uint32_t>(time(NULL)));

        if("compile"==temp) {
            std::cout << temp << " test " << kMsgs[true] << "\n";
        }
        else if("BufferOCF" == temp) {
            std::cout<< temp << " test " << kMsgs[doBufferManagerOCFTests(theOutput)] << "\n";
        }
        else if("OCF"==temp) {
            std::cout << temp << " test " << kMsgs[doOCFTests(theOutput)] << "\n";
        }
        else if("expand"==temp) {
            std::cout << temp << " test " << kMsgs[doBufferManagerExpandTests(theOutput)] << "\n";
        }
        else if("compact"==temp) {
            std::cout << temp << " test " << kMsgs[doBufferManagerCompactTests(theOutput)] << "\n";
        }
        else if("insert"==temp) {
            std::cout << temp << " test " << kMsgs[doInsertTests(theOutput)] << "\n";
        }
        else if("append"==temp) {
            std::cout << temp << " test " << kMsgs[doAppendTests(theOutput)] << "\n";
        }
        else if("replace"==temp) {
            std::cout << temp << " test " << kMsgs[doReplaceTests(theOutput)] << "\n";
        }
        else if("erase"==temp) {
            std::cout << temp << " test " << kMsgs[doEraseTests(theOutput)] << "\n";
        }
        else if("search"==temp) {
            std::cout << temp << " test " << kMsgs[doSearchTests(theOutput)] << "\n";
        }
        else if("compare"==temp) {
            std::cout << temp << " test " << kMsgs[doCompareTests(theOutput)] << "\n";
        }
        else if("speed"==temp) {
            std::cout << temp << " test " << kMsgs[doSpeedTest(theOutput)] << "\n";
        }
        else if("all"==temp) {
            std::cout<< temp << " test Buffer Manager OCF" << kMsgs[doBufferManagerOCFTests(theOutput)] << "\n";
            std::cout<< temp << " test OCF" << kMsgs[doOCFTests(theOutput)] << "\n";
            std::cout<< temp << " test expand" << kMsgs[doBufferManagerExpandTests(theOutput)] << "\n";
            std::cout<< temp << " test compact" << kMsgs[doBufferManagerCompactTests(theOutput)] << "\n";
            std::cout<< temp << " test insert" << kMsgs[doInsertTests(theOutput)] << "\n";
            std::cout<< temp << " test append" << kMsgs[doAppendTests(theOutput)] << "\n";
            std::cout<< temp << " test replace" << kMsgs[doReplaceTests(theOutput)] << "\n";
            std::cout<< temp << " test erase" << kMsgs[doEraseTests(theOutput)] << "\n";
            std::cout<< temp << " test search" << kMsgs[doSearchTests(theOutput)] << "\n";
            std::cout<< temp << " test compare" << kMsgs[doCompareTests(theOutput)] << "\n";
            std::cout<< temp << " test speed" << kMsgs[doSpeedTest(theOutput)] << "\n";
        }
        std::cout << theOutput.str() << "\n";
    }
    return 0;
}