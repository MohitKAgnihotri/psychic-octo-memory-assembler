#include <malloc.h>
#include <string.h>
#include "assembler_language.h"

opcodes opcodes_table[] = {
    { "add", 0, 1, ins_type_R,3},
    { "sub", 0, 2, ins_type_R,3},
    { "and", 0, 3, ins_type_R,3},
    { "or", 0, 4, ins_type_R,3},
    { "nor", 0, 5, ins_type_R,3},
    { "move", 1, 1, ins_type_R,3},
    { "mvhi", 1, 2, ins_type_R,3},
    { "mvlo", 1, 3, ins_type_R,3},
    { "addi", 10, 0, ins_type_I, 3},
    { "subi", 11, 0, ins_type_I, 3},
    { "andi", 12, 0, ins_type_I, 3},
    { "ori", 13, 0, ins_type_I, 3},
    { "nori", 14, 0, ins_type_I, 3},
    { "bne", 15, 0, ins_type_I, 3},
    { "beq", 16, 0, ins_type_I, 3},
    { "blt", 17, 0, ins_type_I, 3},
    { "bgt", 18, 0, ins_type_I, 3},
    { "lb", 19, 0, ins_type_I, 3},
    { "sb", 20, 0,ins_type_I, 3},
    { "lw", 21, 0, ins_type_I, 3},
    { "sw", 22, 0, ins_type_I, 3},
    { "lh", 23, 0, ins_type_I, 3},
    { "sh", 24, 0, ins_type_I, 3},
    { "jmp", 30, 0, ins_type_J, 2},
    { "la", 31, 0, ins_type_J, 2},
    { "call", 32, 0, ins_type_J, 2},
    { "stop", 63, 0, ins_type_J, 0},
};

int opcode_table_length = sizeof(opcodes_table) / sizeof(opcodes_table[0]);

registers registers_table[] = {
    { "$0", "00001" },
    { "$1", "00001" },
    { "$2", "00010" },
    { "$3", "00011" },
    { "$4", "00100" },
    { "$5", "00101" },
    { "$6", "00110" },
    { "$7", "00111" },
    { "$8", "01000" },
    { "$9", "01001" },
    { "$10", "01010" },
    { "$11", "01011" },
    { "$12", "01100" },
    { "$13", "01101" },
    { "$14", "01110" },
    { "$15", "01111" },
    { "$16", "10000" },
    { "$17", "10001" },
    { "$18", "10010" },
    { "$19", "10011" },
    { "$20", "10100" },
    { "$21", "10101" },
    { "$22", "10110" },
    { "$23", "10111" },
    { "$24", "11000" },
    { "$25", "11001" },
    { "$26", "11010" },
    { "$27", "11011" },
    { "$28", "11100" },
    { "$29", "11101" },
    { "$30", "11110" },
    { "$31", "11111" }
};

int registers_table_length = sizeof(registers_table) / sizeof(registers_table[0]);

char* saved_languages_words[] = { ".extern", ".entry", ".db",".dh",".dw", ".asciz",
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

memory_word * create_new_memory_word( void)
{
    memory_word * new_memory_word = (memory_word*)malloc(sizeof(memory_word));
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




