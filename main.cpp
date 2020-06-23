
#include <iostream>
#include <fstream>
#include <vector>
#include "Machine.h"

using namespace std;
typedef unsigned char u8;

uint32_t* charVectToInt(char * chrs,int len){
    uint32_t b=0;
    uint32_t num;
    auto * plates=new uint32_t[len];
    for(int j = 0; j<len-4;j+=4){
        num = 0;
        for ( int i = 0; i != 4; ++i) {
            num |= (u8)chrs[j+i] << (24 - i * 8);    // += could have also been used
        }
        plates[b++]=num;
    }
    return plates;
}

int main() {
    uint32_t * plates=nullptr;
    int length=0;

    //ifstream is ("../codex.umz", std::ifstream::binary);
    ifstream is ("../sandmark.umz", std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        length = is.tellg();
        length++;
        is.seekg (0, is.beg);
        char * buffer = new char [length];
        is.read (buffer,length);
        plates=charVectToInt(buffer,length);
        is.close();
        delete[] buffer;
    }
    Machine m;
    m.init(plates,length);
    m.exec();
    return 0;
}

