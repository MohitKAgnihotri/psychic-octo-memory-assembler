#include <malloc.h>
#include <string.h>
#include "assembler_language.h"

opcodes opcodes_table[] = {
    { "add", 0, 1, ins_type_R_1, 3 },
    { "sub", 0, 2, ins_type_R_1, 3 },
    { "and", 0, 3, ins_type_R_1, 3 },
    { "or", 0, 4, ins_type_R_1, 3 },
    { "nor", 0, 5, ins_type_R_1, 3 },
    { "move", 1, 1, ins_type_R_2, 3 },
    { "mvhi", 1, 2, ins_type_R_2, 3 },
    { "mvlo", 1, 3, ins_type_R_2, 3 },
    { "addi", 10, 0, ins_type_I_1, 3 },
    { "subi", 11, 0, ins_type_I_1, 3 },
    { "andi", 12, 0, ins_type_I_1, 3 },
    { "ori", 13, 0, ins_type_I_1, 3 },
    { "nori", 14, 0, ins_type_I_1, 3 },
    { "bne", 15, 0, ins_type_I_2, 3 },
    { "beq", 16, 0, ins_type_I_2, 3 },
    { "blt", 17, 0, ins_type_I_2, 3 },
    { "bgt", 18, 0, ins_type_I_2, 3 },
    { "lb", 19, 0, ins_type_I_1, 3 },
    { "sb", 20, 0, ins_type_I_1, 3 },
    { "lw", 21, 0, ins_type_I_1, 3 },
    { "sw", 22, 0, ins_type_I_1, 3 },
    { "lh", 23, 0, ins_type_I_1, 3 },
    { "sh", 24, 0, ins_type_I_1, 3 },
    { "jmp", 30, 0, ins_type_J_1, 2 },
    { "la", 31, 0, ins_type_J_2, 2 },
    { "call", 32, 0, ins_type_J_2, 2 },
    { "stop", 63, 0, ins_type_S, 0 },
};

int opcode_table_length = sizeof(opcodes_table) / sizeof(opcodes_table[0]);

registers registers_table[] = {
    { "$0", "000000" },
    { "$1", "100000" },
    { "$2", "010000" },
    { "$3", "110000" },
    { "$4", "001000" },
    { "$5", "101000" },
    { "$6", "011000" },
    { "$7", "111000" },
    { "$8", "000100" },
    { "$9", "100100" },
    { "$10", "010010" },
    { "$11", "110100" },
    { "$12", "001100" },
    { "$13", "101100" },
    { "$14", "011100" },
    { "$15", "111100" },
    { "$16", "000010" },
    { "$17", "100010" },
    { "$18", "010010" },
    { "$19", "110010" },
    { "$20", "001010" },
    { "$21", "101010" },
    { "$22", "011010" },
    { "$23", "111010" },
    { "$24", "000110" },
    { "$25", "100110" },
    { "$26", "010110" },
    { "$27", "110110" },
    { "$28", "001110" },
    { "$29", "101110" },
    { "$30", "011110" },
    { "$31", "111110" }
};

int registers_table_length = sizeof(registers_table) / sizeof(registers_table[0]);

char* saved_languages_words[] = { ".extern", ".entry", ".db", ".dh", ".dw", ".asciz",
                                  "add", "sub", "and", "or", "nor", "move", "mvhi",
                                  "mvlo", "addi", "subi", "andi", "ori", "nori", "bne",
                                  "beq", "blt", "bgt", "lb", "sb", "lw", "sw",
                                  "lh", "sh", "jmp", "la", "call", "stop", "$0",
                                  "$1", "$2", "$3", "$4", "$5", "$6",
                                  "$7", "$8", "$9", "$10", "$11", "$12",
                                  "$13", "$14", "$15", "$16", "$17", "$18",
                                  "$19", "$20", "$21", "$22", "$23", "$24",
                                  "$25", "$26", "$27", "$28", "$29", "$30", "$31" };

int saved_languages_words_length = sizeof(saved_languages_words) / sizeof(saved_languages_words[0]);

memory_word* create_new_memory_word(void)
{
    memory_word* new_memory_word = (memory_word*)malloc(sizeof(memory_word));
    if (!new_memory_word)
    {
        fprintf(stderr, "ERROR: Memory allocation failed");
        return NULL;
    }
    new_memory_word->address = 0;
    memset(new_memory_word->bits, 0, 32);
    new_memory_word->next = NULL;

    return new_memory_word;
}




