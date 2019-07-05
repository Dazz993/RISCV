//
// Created by lenovo on 2019/7/3.
//
#ifndef INSTRUCTION
#define INSTRUCTION

#include "Memory.hpp"
#include <iostream>
enum OPERTOR {
    LUI, AUIPC, JAL,
//  0    1      2

    JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB,
//  3     4    5    6    7    8     9     10

    LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI,
//  11  12  13   14  15  16  17    18    19     20    21   22   23

    SLLI, SRLI, SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR,
//  24    25    26    27   28   29   30   31   32    33   34   35

    AND
//  36
};

char oper[37][8]={
        "LUI", "AUIPC", "JAL",
//  0    1      2

        "JALR", "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU", "LB",
//  3     4    5    6    7    8     9     10

        "LH", "LW", "LBU", "LHU", "SB", "SH", "SW", "ADDI", "SLTI", "SLTIU", "XORI", "ORI", "ANDI",
//  11  12  13   14  15  16  17    18    19     20    21   22   23

        "SLLI", "SRLI", "SRAI", "ADD", "SUB", "SLL", "SLT", "SLTU", "XOR", "SRL", "SRA", "OR",
//  24    25    26    27   28   29   30   31   32    33   34   35

        "AND"
//  36
};

class Instruction {
public:
    OPERTOR op;
    int inst, opcode;
    int rd, rs1, rs2;
    int pc;
    int imm, Val_rs1, Val_rs2, Val_Ex, Val_Ma, Val_pc;

    Instruction();

    void init();

    void IF();

    void ID();

    void EX();

    void MA();

    void WB();

    void get_rd();

    void get_rs1();

    void get_rs2();

    void get_imm_I();

    void get_imm_S();

    void get_imm_B();

    void get_imm_U();

    void get_imm_J();

    void run();

    int signedExtend(int data, int bits) {
        if (data & (1 << bits))
            data |= 0xffffffff >> bits << bits;
        return data;
    }

    void show_information_for_debug();
    
    void show_change_rd_with_ex_for_debug();

    void show_change_rd_with_ma_for_debug();

    void show_change_ma_for_debug();
};

void Instruction::show_information_for_debug(){
//    std::cout<<"after ID: pc:"<<std::hex<<pc<<std::dec<<"  op:"<<oper[op]<<"  rs1:"<<rs1<<"  rs2:"<<rs2<<"  imm:"<<std::hex<<imm<<"  inst:"<<inst<<std::endl;
};

void Instruction::show_change_rd_with_ex_for_debug(){
//    std::cout<<"change RD  "<<std::dec<<rd<<" : "<<Val_Ex<<std::endl;
}

void Instruction::show_change_rd_with_ma_for_debug(){
//    std::cout<<"change RD "<<std::dec<<rd<<" : "<<Val_Ma<<std::endl;
}

void Instruction::show_change_ma_for_debug(){
//    std::cout<<"change MA"<<std::dec<<rd<<" : "<<Val_Ma<<std::endl;
}


Instruction::Instruction() {
    op = LUI;
    inst = opcode = rd = rs1 = rs2 = imm = pc = Val_rs1 = Val_rs2 = Val_Ex = Val_Ma = Val_pc = 0;
}

void Instruction::get_rd() {
    rd = (inst >> 7) & 0x1F;
//    if(rd == 0) std::cout<<"no.0 register!\n";
}

void Instruction::get_rs1() {
    rs1 = (inst >> 15) & 0x1F;
    Val_rs1 = r[rs1];
}

void Instruction::get_rs2() {
    rs2 = (inst >> 20) & 0x1F;
    Val_rs2 = r[rs2];
}

void Instruction::get_imm_I() {
    imm = inst >> 20;
}

void Instruction::get_imm_S() {
    imm = ((inst >> 7) & 0x1F) + ((inst >> 25) << 5);
}

void Instruction::get_imm_B() {
    imm = (((inst >> 8) & 0xF) << 1) + (((inst >> 25) & 0x3F) << 5)
          + (((inst >> 7) & 0x1) << 11) + ((inst >> 31) << 12);
}

void Instruction::get_imm_U() {
    imm = (inst >> 12) << 12;
}

void Instruction::get_imm_J() {
    imm = (((inst >> 21) & 0x3FF) << 1) + (((inst >> 20) & 0x1) << 11)
          + (((inst >> 12) & 0xFF) << 12) + ((inst >> 31)<< 20);
}

void Instruction::init() {
    inst = 0;
    rd = rs1 = rs2 = imm = 0;
    Val_pc = pc;
}

void Instruction::IF() {
    inst = int((unsigned char)memory.mem[pc]) + int((unsigned char)memory.mem[pc + 1] << 8) + int((unsigned char)memory.mem[pc + 2] << 16) +
           int((unsigned char)memory.mem[pc + 3] << 24);
    pc += 4;
}

void Instruction::ID() {
    opcode = inst & 0x7F;
    switch (opcode) {
        case 55 :
            op = LUI;
            get_imm_U();
            get_rd();
            break;
        case 23 :
            op = AUIPC;
            get_imm_U();
            get_rd();
            break;
        case 111:
            op = JAL;
            get_imm_J();
            get_rd();
            break;
        case 103:
            op = JALR;
            get_imm_I();
            get_rs1();
            get_rd();
            break;
        case 99: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = BEQ;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    break;
                case 1:
                    op = BNE;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    break;
                case 4:
                    op = BLT;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    break;
                case 5:
                    op = BGE;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    break;
                case 6:
                    op = BLTU;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    break;
                case 7:
                    op = BGEU;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    break;
            }
            break;
        }
        case 3: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = LB;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 1:
                    op = LH;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 2:
                    op = LW;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 4:
                    op = LBU;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 6:
                    op = LHU;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
            }
            break;
        }
        case 35: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = SB;
                    get_rs1();
                    get_rs2();
                    get_imm_S();
                    break;
                case 1:
                    op = SH;
                    get_rs1();
                    get_rs2();
                    get_imm_S();
                    break;
                case 2:
                    op = SW;
                    get_rs1();
                    get_rs2();
                    get_imm_S();
                    break;
            }
            break;
        }
        case 19: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = ADDI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 2:
                    op = SLTI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 3:
                    op = SLTIU;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 4:
                    op = XORI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 6:
                    op = ORI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 7:
                    op = ANDI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 1:
                    op = SLLI;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 5: {
                    int option3 = (inst >> 25) & 0x7F;
                    switch (option3) {
                        case 0 :
                            op = SRLI;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        case 32:
                            op = SRAI;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                    }
                    break;
                }
            }
            break;
        }
        case 51: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0: {
                    int option3 = (inst >> 25) & 0x7F;
                    switch (option3) {
                        case 0 :
                            op = ADD;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        case 32:
                            op = SUB;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                    }
                    break;
                }
                case 1:
                    op = SLL;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 2:
                    op = SLT;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 3:
                    op = SLTU;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 4:
                    op = XOR;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 5: {
                    int option3 = (inst >> 25) & 0x7F;
                    switch (option3) {
                        case 0 :
                            op = SRL;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        case 32:
                            op = SRA;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                    }
                    break;
                }
                case 6:
                    op = OR;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 7:
                    op = AND;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
            }
            break;
        }
    }
    show_information_for_debug();
}

void Instruction::EX() {
    switch (op) {
        case LUI: { //I-type, U-immediate
            Val_Ex = imm;
            break;
        }
        case AUIPC: { //I-type, U-immediate
            Val_Ex = Val_pc + imm;
            break;
        }
        case JAL: { //U-type, J-immediate
            Val_Ex = Val_pc + 4;
            Val_pc = Val_pc + imm;
            break;
        }
        case JALR: { //I-type, I-immediate
            Val_Ex = Val_pc + 4;
            Val_pc = (Val_rs1 + imm) & 0xfffffffe;
            break;
        }
        case BEQ: { //S-type, B-immediate
            Val_pc = (Val_rs1 == Val_rs2) ? Val_pc + imm : Val_pc + 4;
            break;
        }
        case BNE: { //S-type, B-immediate
            Val_pc = (Val_rs1 != Val_rs2) ? Val_pc + imm : Val_pc + 4;
            break;
        }
        case BLT: { //S-type, B-immediate
            Val_pc = (Val_rs1 < Val_rs2) ? Val_pc + imm : Val_pc + 4;
            break;
        }
        case BGE: { //S-type, B-immediate
            Val_pc = (Val_rs1 >= Val_rs2) ? Val_pc + imm : Val_pc + 4;
            break;
        }
        case BLTU: { //S-type, B-immediate
            Val_pc = ((unsigned int)(Val_rs1) < (unsigned int)(Val_rs2)) ? Val_pc + imm : Val_pc + 4;
            break;
        }
        case BGEU: { //S-type, B-immediate
            Val_pc = ((unsigned int)(Val_rs1) >= (unsigned int)(Val_rs2)) ? Val_pc + imm : Val_pc + 4;
            break;
        }
        case LB: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LH: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LW: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LBU: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LHU: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SB: { //S-type, S-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SH: { //S-type, S-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SW: { //S-type, S-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case ADDI: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SLTI: { //I-type, I-immediate
            if (Val_rs1 < imm)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case SLTIU: { //I-type, I-immediate
            if ((unsigned int) Val_rs1 < (unsigned int)imm)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case XORI: { //I-type, I-immediate
            Val_Ex = Val_rs1 ^ imm;
            break;
        }
        case ORI: { //I-type, I-immediate
            Val_Ex = Val_rs1 | imm;
            break;
        }
        case ANDI: { //I-type, I-immediate
            Val_Ex = Val_rs1 & imm;
            break;
        }
        case SLLI: { //R-type
            Val_Ex = (unsigned int) Val_rs1 << (unsigned int)rs2;
            break;
        }
        case SRLI: { //I-type
            Val_Ex = (unsigned int) Val_rs1 >> (unsigned int)rs2;
            break;
        }
        case SRAI: { //I-type
            Val_Ex = Val_rs1 >> (unsigned int)rs2;
            break;
        }
        case ADD: { //R-type
            Val_Ex = Val_rs1 + Val_rs2;
            break;
        }
        case SUB: { //R-type
            Val_Ex = Val_rs1 - Val_rs2;
            break;
        }
        case SLL: { //R-type
            Val_Ex = (unsigned int)Val_rs1 << (unsigned int)(Val_rs2 & 0x1f);
            break;
        }
        case SRL: { //R-type
            Val_Ex = (unsigned int) Val_rs1 >> (unsigned int)(Val_rs2 & 0x1f);
            break;
        }
        case SRA: { //R-type
            Val_Ex = Val_rs1 << (unsigned int)(Val_rs2 & 0x1f);
            break;
        }
        case SLT: { //R-type
            if (Val_rs1 < Val_rs2)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case SLTU: { //R-type
            if ((unsigned int) Val_rs1 < (unsigned int) Val_rs2)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case XOR: { //R-type
            Val_Ex = Val_rs1 ^ Val_rs2;
            break;
        }
        case OR: { //R-type
            Val_Ex = Val_rs1 | Val_rs2;
            break;
        }
        case AND: { //R-type
            Val_Ex = Val_rs1 & Val_rs2;
            break;
        }
    }
}

void Instruction::MA() {
    switch (op) {
        case LUI:
        case AUIPC:
        case JAL:
        case JALR:
        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU:
        case ADDI:
        case SLTI:
        case SLTIU:
        case XORI:
        case ORI:
        case ANDI:
        case SLLI:
        case SRLI:
        case SRAI:
        case ADD:
        case SUB:
        case SLL:
        case SRL:
        case SRA:
        case SLT:
        case SLTU:
        case XOR:
        case OR:
        case AND: {
            break;
        }

        case LB: {
            Val_Ma = int(memory.mem[Val_Ex]);
            break;
        }
        case LH: {
            Val_Ma = (unsigned char)memory.mem[Val_Ex] + int(memory.mem[Val_Ex + 1] << 8);
            break;
        }
        case LW: {
            Val_Ma = int((unsigned char)memory.mem[Val_Ex]) + int((unsigned char)memory.mem[Val_Ex + 1] << 8) +
                     int((unsigned char)memory.mem[Val_Ex + 2] << 16) + int(memory.mem[Val_Ex + 3] << 24);
            break;
        }
        case LBU: {
            Val_Ma = int((unsigned char)memory.mem[Val_Ex]);
            break;
        }
        case LHU: {
            Val_Ma = int((unsigned char)memory.mem[Val_Ex]) + int((unsigned char)memory.mem[Val_Ex + 1] << 8);
            break;
        }
        case SB: {
            memory.mem[Val_Ex] = Val_rs2 & 255;

            memory.judge_end(Val_Ex);
            break;
        }
        case SH: {
            memory.mem[Val_Ex] = Val_rs2 & 255;
            memory.mem[Val_Ex + 1] = (Val_rs2 >> 8) & 255;

            memory.judge_end(Val_Ex);
            memory.judge_end(Val_Ex + 1);
            break;
        }
        case SW: {
            memory.mem[Val_Ex] = Val_rs2 & 255 ;
            memory.mem[Val_Ex + 1] = (Val_rs2 >> 8) & 255;
            memory.mem[Val_Ex + 2] = (Val_rs2 >> 16) & 255;
            memory.mem[Val_Ex + 3] = (Val_rs2 >> 24) & 255;

            memory.judge_end(Val_Ex);
            memory.judge_end(Val_Ex + 1);
            memory.judge_end(Val_Ex + 2);
            memory.judge_end(Val_Ex + 3);
            break;
        }

    }
}

void Instruction::WB() {
    switch (op) {

        //only change r[rd] by ex
        case LUI:
        case AUIPC:
        case ADDI:
        case SLTI:
        case SLTIU:
        case XORI:
        case ORI:
        case ANDI:
        case SLLI:
        case SRLI:
        case SRAI:
        case ADD:
        case SUB:
        case SLL:
        case SRL:
        case SRA:
        case SLT:
        case SLTU:
        case XOR:
        case OR:
        case AND: {
            if(rd != 0) {
                r[rd] = Val_Ex;
                show_change_rd_with_ex_for_debug();
            }
            break;
        }

            //only change pc by ex
        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU: {
            pc = Val_pc;
            break;
        }

            //change r[rd] and pc by ex
        case JAL:
        case JALR: {
            if(rd != 0) {
                r[rd] = Val_Ex;
                show_change_rd_with_ex_for_debug();
            }
            pc = Val_pc;
            break;
        }

            //change r[rd] by ma
        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU: {
            if(rd != 0) {
                r[rd] = Val_Ma;
                show_change_rd_with_ma_for_debug();
            }
            break;
        }

            //not change register
        case SB:
        case SH:
        case SW: {
            break;
        }
    }
}

void Instruction::run() {
    init();
    IF();
    ID();
    EX();
    MA();
    WB();
}

#endif