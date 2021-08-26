
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "assembler_language.h"
#include "assembler_symbol_table.h"

symbol_line* symbol_head;
symbol_line* symbol_tail;

void assembler_symbol_table_init()
{

}

symbol_line* get_symbol_line_from_symbol_table(char* symbol)
{
    symbol_line* sl = symbol_head;
    while (sl)
    {
        if (strcmp(sl->symbol, symbol) == 0)
        {
            return sl;
        }
        sl = sl->next;
    }
    fprintf(stderr, "ERROR: Operand %s is not defined in symbol table\n", symbol);
    return NULL;
}

void increase_DC_symbol_address_by_IC_offset(const int* IC)
{
    symbol_line* temp;

    if (!symbol_head)
        return;

    temp = symbol_head;

    while (temp)
    {
        if (temp->symbol_type == DATA)
            temp->address += *IC;

        temp = temp->next;
    }

    return;
}

void add_to_symbol_table(char* current_symbol, int address, int is_extern, int symbol_type)
{
    symbol_line* new_symbol = (symbol_line*)malloc(sizeof(symbol_line));

    if (!new_symbol)
    {
        fprintf(stderr, "Memory allocation for new symbol failed!");
        exit(1);
    }

    strcpy(new_symbol->symbol, current_symbol); /* NTS: make sure that the current symbol gets '\0'. strcpy
							copies the '\0' as well) */

    new_symbol->address = address;
    new_symbol->is_extern = is_extern;
    new_symbol->symbol_type = symbol_type;

    if (!symbol_head)
    {
        symbol_head = new_symbol;
        symbol_tail = symbol_head;
    }
    else
    {
        symbol_tail->next = new_symbol;
        symbol_tail = symbol_tail->next;
    }

    symbol_tail->next = NULL;

    return;

}

int assembler_symbol_exists(char* current_symbol)
{
    symbol_line* temp = symbol_head;

    while (temp)
    {
        if (strcmp(temp->symbol, current_symbol) == 0)
            return TRUE;

        else
            temp = temp->next;

    }
    return FALSE;
}

void free_symbol_list( void ) {
    symbol_line* item = NULL;
    while(symbol_head)
    {
        item = symbol_head;
        symbol_head = symbol_head->next;
        free(item);
    }
    symbol_head = NULL;
    symbol_tail = NULL;
}
