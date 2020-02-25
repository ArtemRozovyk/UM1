
#include <iostream>
#include <fstream>
#include <vector>
#include "Machine.h"

using namespace std;
typedef unsigned char u8;



vector<unsigned int> charVectToInt(vector<u8> cv){
    uint32_t num;
    vector<uint32_t> plates;
    for(int j = 0; j<cv.size()-4;j+=4){
        num = 0;
        for ( int i = 0; i != 4; ++i) {
            num |= (u8)cv[j+i] << (24 - i * 8);    // += could have also been used
        }
        plates.push_back(num);
    }
    return plates;
}

vector<unsigned int> charVectToInt(char * chrs,int len){
    uint32_t num;
    vector<uint32_t> plates;
    for(int j = 0; j<len-4;j+=4){
        num = 0;
        for ( int i = 0; i != 4; ++i) {
            num |= (u8)chrs[j+i] << (24 - i * 8);    // += could have also been used
        }
        plates.push_back(num);
    }
    return plates;
}

int main() {
    vector<uint32_t> plates;
    ifstream is ("../sandmark.umz", std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        length++;
        is.seekg (0, is.beg);
        char * buffer = new char [length];
        is.read (buffer,length);
        plates=charVectToInt(buffer,length);
        is.close();
        delete[] buffer;
    }
    Machine m;
    m.init(&plates);
    m.exec();


    return 0;
}



/*

    if(!infile.is_open()){
        puts("error");
    }

    u8 cr;
    while(infile.read ((char*)&cr, sizeof(cr)))
    {
        vi.push_back(cr);
    }
    vector<uint32_t> plates=charVectToInt(vi);
    //printf("%x",plates[0]);
    infile.close();
    for (auto c : plates){
        std::cout<<" c "<< c << std::endl;
    }
    Machine m;
    //m.init(&plates);
    //m.exec();*/

