//
// Created by human on 25/02/2020.
//

#ifndef UM1_MACHINE_H
#define UM1_MACHINE_H

#include <vector>

class Machine {
    int pc;
    unsigned int reg [8] ;
    std::vector<std::vector<unsigned int> *> mem;
    void doOperation(unsigned int curr);
    bool stop=false;
public:
    void exec();
    void init(std::vector<unsigned int>* vector );
};

#endif //UM1_MACHINE_H
