//
// Created by human on 27/02/2020.
//

#include "Machine2.h"
//
// Created by human on 25/02/2020.
//

#include <iostream>
#include <utility>
#include <thread>
#include <cstring>
#include<algorithm>
#include<iterator>
typedef  unsigned  char u8;
//  std::map<std::string, int> m;use
void Machine2::exec() {
    uint32_t curr;
    /*for (int i =0;i<14;i++){
        opcount[i]=0;
    }*/
    while(!stop&&pc!=mem[0]->size){
        curr=mem[0]->plates[pc++];
        u8 op=(curr>>28u&0b1111u);
        u8 C=(curr&0b111u);
        u8 B=(curr>>3u&0b111u);
        u8 A=(curr>>6u&0b111u);
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
                reg[A]=mem[reg[B]]->plates[reg[C]];
                break;
            case 2 :
                mem[reg[A]]->plates[reg[B]]=reg[C];
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
                reg[A]=~(reg[B]&reg[C]);
                break;
            case 7 :
                stop=true;
                break;
            case 8 ://
                if(!recylcedIds.empty()){
                    uint32_t id = recylcedIds.front();
                    mem[id]=(new table {new uint32_t[reg[C]]{},reg[C]});
                    reg[B]=id;
                    recylcedIds.remove(id);
                }else{
                    //printf(" %d %d %d \n",A,B,C);
                    mem[index]=(new table {new uint32_t[reg[C]]{},reg[C]});
                    //std::memset(mem[index],0,sizeof(uint32_t)*reg[C]);
                    reg[B]=index;
                    index++;
                }

                break;
            case 9 :
                delete mem[reg[C]];
                mem.erase(reg[C]);
                //ça ralentit considerablement...
                //recylcedIds.push_back(reg[C]);
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
                memcpy(mem[0]->plates,mem[reg[B]]->plates,sizeof(uint32_t)*mem[reg[B]]->size);
                //sizes[0]=sizes[reg[B]];
                mem[0]->size=reg[B];
                pc=reg[C];
                break;
            case 13 :
                reg[(curr>>25u&0b111u)]=curr&0x01ffffffu;
                break;
        }
    }
    if(pc==mem[0]->size){
        std::cout << " end of the tape";
    }

}

void Machine2::init(uint32_t *vector, uint32_t initsize) {
    this->mem[0]= new table {vector,initsize};
}

void Machine2::doOperation(uint32_t curr) {


}


