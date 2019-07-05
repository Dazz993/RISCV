//
// Created by lenovo on 2019/7/4.
//

#ifndef RISC5_MEMORY_HPP
#define RISC5_MEMORY_HPP

#include "Useful_Functions.hpp"

const int MAXSIZE_OF_MEMORY = 4194304 + 7;

class Memory {
public:
    char mem[MAXSIZE_OF_MEMORY];
    bool end = 0;

    Memory() { for (int i = 0; i < MAXSIZE_OF_MEMORY; i++) mem[i] = '\0'; }

    void Load_Memory() {
        char tmp[15];
        int point = 0;
//        int count = 0;

        while (~scanf("%s", tmp)) {
            if (tmp[0] == '@') {
                point = Change_Into_16(tmp, 0);
            } else if(tmp[0] == '?') {
                return;
            } else {
                mem[point++] = Change_Into_16(tmp, 1);
            }

            for (int i = 0; i < 15; i++) tmp[i] = 0;
//        count++;
//        if(count == 100) break;
        }
    }

    void judge_end(int pos){
        if(pos == 0x30004) end = 1;
    }
};

Memory memory;
int r[32];


#endif //RISC5_MEMORY_HPP
