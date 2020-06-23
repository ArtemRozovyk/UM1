//
// Created by human on 25/02/2020.
//

#ifndef UM1_MACHINE_H
#define UM1_MACHINE_H

#include <vector>
#include <unordered_map>
#include <list>
#include <thread>



struct table {
    uint32_t * plates;
    uint32_t size;
};

class Machine2 {

    int pc=0;
    uint32_t reg [8] = {};
    std::unordered_map<uint32_t, struct table *> mem;
    std::list<uint32_t> recylcedIds;
    uint32_t index=1;
    void doOperation(uint32_t curr);
    bool stop=false;
    int counter=0;
    struct table * a [][0];
public:
    void exec();
    void init(uint32_t* vector, uint32_t initsize );
};

#endif //UM1_MACHINE_H
