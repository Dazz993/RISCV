#include <iostream>
#include "Instruction.hpp"

void debug(){

}
int main() {
    Instruction inst;
    memory.Load_Memory();

//    int cnt = 0;

    while(memory.end == 0){
        inst.run();

        //////////////////////////debeg//////////////////////////
//        std::cout<<std::dec<<"after run: cnt:"<<++cnt<<"  pc:"<<inst.pc<<"  op:"<<inst.op<<std::endl;
//        std::cout<<"------"<<std::endl;
//        for(int i = 0; i < 32; i++) std::cout<<r[i]<<"  ";
//        std::cout<<std::endl;
//        std::cout<<"--------------------------"<<std::endl;
//        if(cnt > 200)break;
    }
    std::cout<<((r[10] & 0xff) % 253);
    return 0;
}
