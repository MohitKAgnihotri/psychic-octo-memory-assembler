#include "assembler_language.h"

opcodes opcodes_table[] = {
    { "add", "000000", "00001", 2, {} , {}},
    { "sub", "000000", "00010", 2, {} , {}},
    { "and", "000000", "00011", 2, {} , {}},
    { "or", "000000", "00100", 2, {} , {}},
    { "nor", "000000", "00101", 2, {} , {}},
    { "move", "000001", "00001", 2, {} , {}},
    { "mvhi", "000001", "00010", 2, {} , {}},
    { "mvlo", "000001", "00011", 2, {} , {}},
    { "addi", "001010", "00000", 1, {} , {}},
    { "subi", "001011", "00000", 1, {} , {}},
    { "andi", "001100", "00000", 1, {} , {}},
    { "ori", "001101", "00000", 1, {} , {}},
    { "nori", "001110", "00000", 1, {} , {}},
    { "bne", "001111", "00000", 1, {} , {}},
    { "beq", "010000", "00000", 1, {} , {}},
    { "blt", "010001", "00000", 1, {} , {}},
    { "bgt", "010010", "00000", 1, {} , {}},
    { "lb", "010011", "00000", 1, {} , {}},
    { "sb", "010100", "00000", 1, {} , {}},
    { "lw", "010101", "00000", 1, {} , {}},
    { "sw", "010110", "00000", 1, {} , {}},
    { "lh","010111", "00000", 1, {} , {}},
    { "sh", "011000", "00000", 1, {} , {}},
    { "jmp", "011110", "00000",1, {} , {}},
    { "la", "011111", "00000",1, {} , {}},
    { "call", "100000", "00000",1, {} , {}},
    { "stop", "111111", "00000", 0, {} , {}},
    };

registers registers_table[] = {
    {"$0", "00001"},
    {"$1", "00001"},
    {"$2", "00010"},
    {"$3", "00011"},
    {"$4", "00100"},
    {"$5", "00101"},
    {"$6", "00110"},
    {"$7", "00111"},
    {"$8", "01000"},
    {"$9", "01001"},
    {"$10", "01010"},
    {"$11", "01011"},
    {"$12", "01100"},
    {"$13", "01101"},
    {"$14", "01110"},
    {"$15", "01111"},
    {"$16", "10000"},
    {"$17", "10001"},
    {"$18", "10010"},
    {"$19", "10011"},
    {"$20", "10100"},
    {"$21", "10101"},
    {"$22", "10110"},
    {"$23", "10111"},
    {"$24", "11000"},
    {"$25", "11001"},
    {"$26", "11010"},
    {"$27", "11011"},
    {"$28", "11100"},
    {"$29", "11101"},
    {"$30", "11110"},
    {"$31", "11111"}
};

int registers_table_length = sizeof(registers_table)/sizeof(registers_table[0]);

char *saved_languages_words[NUM_OF_SAVED_WORDS] = {".extern", ".entry", ".data", ".mat", ".string",
                                                   "add", "sub", "and", "or", "nor", "move", "mvhi",
                                                   "mvlo", "addi", "subi", "andi", "ori", "nori", "bne",
                                                   "beq", "blt", "bgt", "lb", "sb", "lw", "sw",
                                                   "lh", "sh", "jmp", "la", "call", "stop", "$0",
                                                   "$1", "$2", "$3", "$4", "$5", "$6",
                                                   "$7", "$8", "$9", "$10", "$11", "$12",
                                                   "$13", "$14", "$15", "$16", "$17", "$18",
                                                   "$19", "$20", "$21", "$22", "$23", "$24",
                                                   "$25", "$26", "$27", "$28", "$29", "$30", "$31"};




