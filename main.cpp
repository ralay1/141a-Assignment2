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

//-----------------------------------

int main(int argc, const char * argv[]) {
    static const char* kMsgs[]={"FAIL","PASS"};
    if(argc>1) {
        std::string temp(argv[1]);
        std::stringstream theOutput;
        BufferManagerAutoTests bufferManagerTest;
        StringAutoTests stringTest;


        srand(static_cast<uint32_t>(time(NULL)));

        if("compile"==temp) {
            std::cout << temp << " test " << kMsgs[true] << "\n";
        }
        else if("BufferOCF" == temp) {
            std::cout<< temp << " test " << kMsgs[bufferManagerTest("OCFTest",theOutput)] << "\n";
        }
        else if("OCF"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("OCFTest", theOutput)] << "\n";
        }
        else if("Expand"==temp) {
            std::cout << temp << " test " << kMsgs[bufferManagerTest("ExpandTest",theOutput)] << "\n";
        }
        else if("Compact"==temp) {
            std::cout << temp << " test " << kMsgs[bufferManagerTest("CompactTest",theOutput)] << "\n";
        }
        else if("Insert"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("InsertTest",theOutput)] << "\n";
        }
        else if("Append"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("AppendTest",theOutput)] << "\n";
        }
        else if("Replace"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("ReplaceTest",theOutput)] << "\n";
        }
        else if("Erase"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("EraseTest",theOutput)] << "\n";
        }
        else if("Search"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("SearchTest",theOutput)] << "\n";
        }
        else if("Compare"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("CompareTest",theOutput)] << "\n";
        }
        else if("Speed"==temp) {
            std::cout << temp << " test " << kMsgs[stringTest("SpeedTest",theOutput)] << "\n";
        }
        else if("All"==temp) {
            stringTest.runTests();
            bufferManagerTest.runTests();
        }
        else{
            std::cout<<"Unknown test " << temp << "\n";
            return 1;
        }
        std::cout << theOutput.str() << "\n";
    }
    return 0;
}