//
// Created by human on 25/02/2020.
//

#include <iostream>
#include <utility>
#include <thread>
#include <stdio.h>

#include <cstring>
#include<algorithm>
#include<iterator>
#include "Machine.h"
typedef  unsigned  char u8;
//  std::map<std::string, int> m;use
void Machine::exec() {
    uint32_t curr;
    /*for (int i =0;i<14;i++){
        opcount[i]=0;
    }*/
    while(!stop&&pc!=a[0]->size){
        curr=a[0]->plates[pc++];
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
        //printf("%d ",recylcedIds.size());

        switch (op){
            case 0 :
                if(reg[C] != 0)
                    reg[A]=reg[B];
                break;
            case 1 :
                reg[A]=a[reg[B]]->plates[reg[C]];
                break;
            case 2 :
                a[reg[A]]->plates[reg[B]]=reg[C];
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
                    a[id]=new table {new uint32_t[reg[C]]{},reg[C]};
                    //printf("%d -id- %d, \n",id,reg[C]);

                    reg[B]=id;
                    recylcedIds.pop_front();
                }else{
                    //printf(" %d %d %d \n",A,B,C);
                    a[index]=new table {new uint32_t[reg[C]]{},reg[C]};
                    //std::memset(mem[index],0,sizeof(uint32_t)*reg[C]);
                    //printf("%d -index- %d, \n",index,reg[C]);

                    reg[B]=index;
                    index++;
                }

                break;
            case 9 :
                delete a[reg[C]];
                //a[reg[C]]= nullptr;
                //mem.erase(reg[C]);
                //ça ralentit considerablement...
                recylcedIds.push_back(reg[C]);
                break;
            case 10 :
                //verif 0...255
                if(reg[C]<0||reg[C]>255){
                    puts("Printing bad value");
                    return;
                }
                if(reg[C]=='L'){
                    counter++;
                }
                printf("%c",(char)reg[C]);
                break;
            case 11 :
                /* getchar example : typewriter */
                    uint8_t c;
                    c=getchar();
                    if(c==EOF){
                        reg[C]=0xffffffff;
                    }else{
                        reg[C]=(uint8_t )c;
                    }

                break;
            case 12 :
                memcpy(a[0]->plates,a[reg[B]]->plates,sizeof(uint32_t)*a[reg[B]]->size);
                //sizes[0]=sizes[reg[B]];
                a[0]->size=reg[B];
                pc=reg[C];
                break;
            case 13 :
                reg[(curr>>25u&0b111u)]=curr&0x01ffffffu;
                break;
        }
    }
    if(pc==a[0]->size){
        std::cout << " end of the tape";
    }

}

void Machine::init(uint32_t *vector, uint32_t initsize) {
    this->a[0]= new table {vector,initsize};
    //printf("%d",a[0]->plates[0]);

}

void Machine::doOperation(uint32_t curr) {


}


