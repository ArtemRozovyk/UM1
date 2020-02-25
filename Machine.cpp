//
// Created by human on 25/02/2020.
//

#include <iostream>
#include <utility>
#include "Machine.h"
typedef unsigned char u8;

void Machine::exec() {
    unsigned int curr;

    while(!stop){
        curr=(*mem[0])[pc++];
        std::cout << " curr " <<(curr>>28&0b1111) << std::endl ;
        //doOperation(curr);
        if(pc==(*mem[0]).size()){
            std::cout << " end of the tape";
            break;
        }
    }
}

void Machine::init(std::vector<unsigned int> * vector ) {
    this->mem.push_back(vector);
}

void Machine::doOperation(unsigned int curr) {
    u8 op=(u8)(curr>>28u&0b1111u);
    u8 C=(u8)(curr&0b111u);
    u8 B=(u8)(curr>>3u&0b111u);
    u8 A=(u8)(curr>>6u&0b111u);


    printf("%d %d %d %d \n",op,A,B,C);


}
