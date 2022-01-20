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

//---------------------------------

//If this won't compile, your Buffer Managerclass may not be ready.
//If this crashes, check how your Buffer Managerwrites to a stream.
bool doOCFTests() {
    ECE141::BufferManager<char> the_buffer("hello world");
    ECE141::BufferManager<char> the_buffer2("");
    ECE141::BufferManager<char> the_buffer3(the_buffer);
    
    if (!(the_buffer.getLength() == 11)) {
        return false;
    }
    
    if (!(the_buffer2.getLength() == 0)) {
        return false;
    }
    
    if (!(the_buffer3.getLength() == 11)) {
        return false;
    }
    
    the_buffer2 = the_buffer3;
    if (!(the_buffer2.getLength() == 11)) {
        return false;
    }
    
    if (strcmp(the_buffer.getBuffer(), "hello world") != 0) {
        return false;
    }
    
    ECE141::BufferManager<char> the_buffer4;
    the_buffer4 = "abcd";
    if (!(the_buffer4.getLength() == 4)) {
        return false;
    }
    
    return true;
}

bool doExpandTests() {
    ECE141::BufferManager<char> the_buffer4("abcd");
    
    the_buffer4.append("efgh");
    if (!(the_buffer4.getLength() == 8)) {
        return false;
    }
    if (strcmp(the_buffer4.getBuffer(), "abcdefgh") != 0) {
        return false;
    }
    
    the_buffer4.insert(2, "ijkl");
    if (!(the_buffer4.getLength() == 12)) {
        return false;
    }
    if (strcmp(the_buffer4.getBuffer(), "abijklcdefgh") != 0) {
        return false;
    }
    
    the_buffer4.insert(4, "xyz", 2);
    if (!(the_buffer4.getLength() == 14)) {
        return false;
    }
    if (strcmp(the_buffer4.getBuffer(), "abijxyklcdefgh") != 0) {
        return false;
    }
    return true;
}


bool doContractTests() {
    ECE141::BufferManager<char> the_buffer4("hello world");
    
    the_buffer4.erase(4, 4);
    std::cout << the_buffer4 << std::endl;
    if (!(the_buffer4.getLength() == 7)) {
        return false;
    }
    if (strcmp(the_buffer4.getBuffer(), "hellrld") != 0) {
        return false;
    }
    
    ECE141::BufferManager<char> the_buffer5("hello world");
    the_buffer4.erase(0, 20);
    std::cout << the_buffer4 << std::endl;
    if (!(the_buffer4.getLength() == 0)) {
        return false;
    }
    if (strcmp(the_buffer4.getBuffer(), "") != 0) {
        return false;
    }
    
    return true;
}



//-----------------------------------

int main(int argc, const char * argv[]) {
    static const char* kMsgs[]={"FAIL","PASS"};
    if(argc>1) {
        std::string temp(argv[1]);
        
        if("compile"==temp) {
            std::cout << temp << " test " << kMsgs[true] << "\n";
            return 0;
        }
        else if("ocf"==temp) {
            std::cout << temp << " test " << kMsgs[doOCFTests()] << "\n";
        }
        else if("expand"==temp) {
            std::cout << temp << " test " << kMsgs[doExpandTests()] << "\n";
        }
        else if("contract"==temp) {
            std::cout << temp << " test " << kMsgs[doContractTests()] << "\n";
        }
    }
    
    
    return 0;
}
