#include <stdio.h>
#include <string.h>
#include "assembler_line_parser.h"
#include "assembler_error.h"
#include "assembler_language.h"
#include "assembler_symbol_table.h"
#include "assembler_data_table.h"
#include "assembler_first_pass.h"

#define LINE_LENGTH 256

int IC = 100;
int DC = 0;

sentence* sentence_head;
sentence* sentence_tail;

/* increase_IC_according_sentence -
   receives: the current sentence (the line after it was parsed) and checks for source and destination operands.
   The function increases IC according the number of memory words each type of operand requires. */
void increase_IC_according_sentence(sentence* curr, int* IC)
{
    // ALl instruction are coded in 32 bits. Thus we need to increase the instruction count by 4
    *IC += 4;
}

int assembler_execute_first_pass(char* filename)
{
    char line[LINE_LENGTH] = { 0 };

    int line_number = 0;

    sentence* current_sentence = NULL;
    int syntax_error = FALSE;

    FILE* fd = fopen(filename, "r");
    if (!fd)
    {
        printf("ERROR: Failed to open file %s\n", filename);
        return ASSEMBLER_INCORRECT_FILENAME;
    }

    while (fgets(line, LINE_LENGTH, fd))
    {
        line_number++;
        if (line[0] == ';')
        {
            continue;
        }

        current_sentence = assembler_parse_sentence(line, line_number, &syntax_error);
        if (current_sentence == NULL) /* if line is empty parse_sentence returns null */
        {
            continue;
        }

        if (current_sentence->is_store_command == TRUE)
        {
            if (current_sentence->is_symbol)
            {
                if (!assembler_symbol_exists(current_sentence->symbol))
                {
                    add_to_symbol_table(current_sentence->symbol, DC, 0, DATA);
                }
                else
                {
                    fprintf(stderr, "Error in line %d - symbol %s already exists in symbols table\n", line_number, current_sentence
                        ->symbol);
                }
            }
            /* adding into data table. DC is increased: */
            add_to_data_table(current_sentence, &DC);
        }
        else
        {
            if (current_sentence->guidance_command == EXTERN)
            {
                add_to_symbol_table(current_sentence->symbol, -999, 1, NONE);
            }
            else
            {
                if (current_sentence->is_symbol == 1)
                {
                    if (!assembler_symbol_exists(current_sentence->symbol))
                    {
                        add_to_symbol_table(current_sentence->symbol, IC, 0, CODE);
                    }
                    else
                    {
                        fprintf(stderr, "Error in line %d - symbol %s already exists in symbols table\n", line_number, current_sentence
                            ->symbol);
                        syntax_error = TRUE;
                    }
                }

                /* analyzing sentence so IC is increased by the number of memory words the action sentence takes */
                if (current_sentence->is_action)
                    increase_IC_according_sentence(current_sentence, &IC);
            }
        }

        if (sentence_head == NULL)
        {
            sentence_head = current_sentence;
            sentence_tail = sentence_head;
        }
        else
        {
            sentence_tail->next = current_sentence;
            sentence_tail = sentence_tail->next;
        }
    }


    /* updating the DC address of each entry in symbol_table with the IC offset, only when 													the symbol is of DATA type */
    increase_DC_symbol_address_by_IC_offset(&IC);
    return syntax_error;

}
