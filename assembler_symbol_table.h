
#include "assembler_language.h"

#ifndef _ASSEMBLER_SYMBOL_TABLE_H_
#define _ASSEMBLER_SYMBOL_TABLE_H_

typedef struct symbol_line {
    char symbol[MAX_SYMBOL_SIZE];
    int address;
    int is_extern;
    int symbol_type; /* from enum: NONE, DATA, CODE */
    struct symbol_line *next;
} symbol_line;

void add_to_symbol_table(char* current_symbol, int address, int is_extern, int symbol_type);
int assembler_symbol_exists(char *current_symbol);
void increase_DC_symbol_address_by_IC_offset(const int *IC);
symbol_line * get_symbol_line_from_symbol_table(char * symbol);
void free_symbol_list( void );

#endif
