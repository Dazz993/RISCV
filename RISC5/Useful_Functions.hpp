//
// Created by lenovo on 2019/7/4.
//

#ifndef RISC5_USEFUL_FUNCTIONS_HPP
#define RISC5_USEFUL_FUNCTIONS_HPP

int Change_Into_16(char *, bool);
int get_16_num(char);

int Change_Into_16(char *tmp, bool op){
    int ret = 0;
    int base = 1;
    if(!op){
        ret += get_16_num(tmp[8]);
        for(int i = 7; i >= 1; i--){
            base *= 16;
            ret += get_16_num(tmp[i]) * base;
        }
    } else {
        ret = get_16_num(tmp[0]) * 16 + get_16_num(tmp[1]);
    }
    return ret;
}

int get_16_num(char ch){
    int ret;
    if(ch >= '0' && ch <= '9'){
        ret = ch - '0';
    } else if (ch >= 'A' && ch <= 'F'){
        ret = 10 + ch - 'A';
    }
    return ret;
}

#endif //RISC5_USEFUL_FUNCTIONS_HPP
