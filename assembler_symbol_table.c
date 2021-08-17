
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "assembler_language.h"
#include "assembler_symbol_table.h"

symbol_line *symbol_head;
symbol_line *symbol_tail;

void assembler_symbol_table_init()
{
    // For now this is an empty function
}

symbol_line * get_symbol_line_from_symbol_table(char * symbol)
{
    symbol_line * sl = symbol_head;
    while (sl) {
        if (strcmp(sl->symbol, symbol) == 0) {
            return sl;
        }
        sl = sl->next;
    }
    fprintf(stderr, "ERROR: Operand %s is not defined in symbol table (line %d)\n", symbol);
    return NULL;
}

/* increase_DC_symbol_address_by_IC_offset -
   The function goes over the symbols table and adds to each entry of type DATA the IC offset. */
void increase_DC_symbol_address_by_IC_offset(const int *IC)
{
    symbol_line *temp;

    if(!symbol_head)
        return;

    temp = symbol_head;

    while(temp) {
        if (temp->symbol_type == DATA)
            temp->address += *IC;

        temp = temp->next;
    }

    return;
}

/* add_to_symbol_table -
 receives: the last line in the symbols table, the current symbol to be added, the address where it's going to be allocated (DC or 0 if it's extern),
 1 if the symbol is extern / 0 if not, the symbol type (from enum: NONE, DATA, CODE). The function allocates a new node
 of type symbol_line to the symbols table. */
void add_to_symbol_table(char* current_symbol, int address, int is_extern, int symbol_type)
{
    symbol_line* new_symbol = (symbol_line*)malloc(sizeof(symbol_line));

    if (!new_symbol)
    {
        fprintf(stderr, "Memory allocation for new symbol failed!");
        exit(1);
    }

    strcpy(new_symbol->symbol,current_symbol); /* NTS: make sure that the current symbol gets '\0'. strcpy
							copies the '\0' as well) */

    new_symbol->address = address;
    new_symbol->is_extern = is_extern;
    new_symbol->symbol_type = symbol_type;

    if(!symbol_head) {
        symbol_head = new_symbol;
        symbol_tail = symbol_head;
    }
    else {
        symbol_tail->next = new_symbol;
        symbol_tail = symbol_tail->next;
    }

    symbol_tail->next = NULL;

    return;

}

/* symbol_exists -
 receives: the head of the symbols table, the current symbol. The function searches within the list if the symbol already exists.
 returns: 1 if already exists, 0 if not. */
int assembler_symbol_exists(char *current_symbol)
{
    symbol_line *temp = symbol_head;

    while (temp)
    {
        if (strcmp(temp->symbol, current_symbol) == 0)
            return TRUE;

        else
            temp = temp->next;

    }
    return FALSE;
}
