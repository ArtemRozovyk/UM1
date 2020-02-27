//
// Created by human on 25/02/2020.
//

#include <iostream>
#include <utility>
#include <thread>
#include <cstring>
#include<algorithm>
#include<iterator>
#include "Machine.h"
typedef  unsigned  char u8;
//  std::map<std::string, int> m;use
void Machine::exec() {
    uint32_t curr;
    for (int i =0;i<14;i++){
        opcount[i]=0;
    }
    while(!stop){
        curr=(mem[0])[pc++];
        doOperation(curr);
        if(pc==sizes[0]){
            std::cout << " end of the tape";
            break;
        }
    }

    printf(" count: %d",counter);
}

void Machine::init(uint32_t *vector, uint32_t initsize) {
    this->mem[0]=vector;
    this->sizes[0]=initsize;
}

void Machine::doOperation(uint32_t curr) {
    u8 op=(curr>>28&0b1111);
    u8 C=(u8)(curr&0b111u);
    u8 B=(u8)(curr>>3u&0b111u);
    u8 A=(u8)(curr>>6u&0b111u);
    //printf("%d\n",  counter++);
/*
    opcount[op]++;
    counter++;
    if (counter>90000000){
        for(auto c : opcount){
            printf("%d - %d, \n",c.first,c.second);
        }
    }
    */
    switch (op){
        case 0 :
            if(reg[C] != 0)
                reg[A]=reg[B];
            break;
        case 1 :
            reg[A]=mem[reg[B]][reg[C]];
            break;
        case 2 :
            mem[reg[A]][reg[B]]=reg[C];
            break;
        case 3 :
            reg[A]=reg[B]+reg[C];
            break;
        case 4 :
            reg[A]=reg[B]*reg[C];
            break;
        case 5 :
            reg[A]=reg[B] /reg[C];
            break;
        case 6 :
            reg[A]=~reg[B]|~reg[C];
            break;
        case 7 :
            stop=true;
            break;
        case 8 ://

            if(!recylcedIds.empty()){
                uint32_t id = recylcedIds.front();
                mem[id]=( new uint32_t[reg[C]]{});
                reg[B]=id;
                recylcedIds.pop_front();
            }else{
            //printf(" %d %d %d \n",A,B,C);

            mem[index]=(new uint32_t[reg[C]]{});
            sizes[index]=reg[C];
                //std::memset(mem[index],0,sizeof(uint32_t)*reg[C]);
            reg[B]=index;
            index++;
            }

            break;
        case 9 :
            delete mem[index];
            mem.erase(index);
            //recylcedIds.push_back(index);
            break;
        case 10 :
            //verif 0...255
            if(reg[C]<0||reg[C]>255){
                puts("Printing bad value");
                return;
            }
            printf("%c",(char)reg[C]);
            break;
        case 11 :
            //TODO
            break;
        case 12 :

            memcpy(mem[0],mem[reg[B]],sizeof(uint32_t)*sizes[reg[B]]);
            sizes[0]=sizes[reg[B]];
            pc=reg[C];
            break;
        case 13 :
            reg[(u8)(curr>>25u&0b111u)]=curr&0x01ffffffu;
            break;
    }


}


