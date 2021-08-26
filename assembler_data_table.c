#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "assembler_symbol_table.h"
#include "assembler_data_table.h"
#include "assembler_utility_func.h"
#include "assembler_language.h"

memory_word* data_tail;
memory_word* data_head;

/* add_string_to_data_table -
   receives the sentence after it was parsed and converts each char of the string to it's binary representation for it's ascii value.
  */
void add_string_to_data_table(sentence* curr, int* DC)
{
    int i;
    memory_word* new_memory_word;

    for (i = 0; i < strlen(curr->string); i++)
    {

        new_memory_word = (memory_word*)malloc(sizeof(memory_word));
        if (!new_memory_word)
        {
            fprintf(stderr, "Memory allocation for new memory word failed!");
            exit(1);
        }

        convert_ascii_value_to_10_bit_binary(curr->string[i], new_memory_word->bits);
        new_memory_word->number_of_valid_bytes = 1;
        new_memory_word->address = *DC;

        if (data_tail)
        {
            data_tail->next = new_memory_word;
            data_tail = data_tail->next;
        }
        else
        {
            data_head = new_memory_word;
            data_tail = data_head;
        }
        (*DC)++;
    }

    /* adding '\0' to data table at the end of the string */
    new_memory_word = (memory_word*)malloc(sizeof(memory_word));
    strcpy(new_memory_word->bits, "00000000");
    new_memory_word->address = *DC;
    new_memory_word->number_of_valid_bytes = 1;
    new_memory_word->next = NULL;
    (*DC)++;

    if (data_tail)
    {
        data_tail->next = new_memory_word;
        data_tail = data_tail->next;
    }
    else
    {
        data_head = new_memory_word;
        data_tail = data_head;
    }

    return; /*added_mem_words;*/
}

/* add_num_to_data_table -
   receives the sentence after it was parsed and converts each number of the data_arr of the sentence into it's binary value.
   returns the number of memory words added to the data table. */
void add_num_to_data_table(sentence* curr, int* DC, int num_size)
{
    int i;
    char converted_to_bits[11];
    memory_word* new_memory_word;
    char array[33] = { 0 };

    for (i = 0; i < curr->data_arr_num_of_params; i++)
    {
        memset(converted_to_bits, 0x00, sizeof(converted_to_bits));
        new_memory_word = (memory_word*)malloc(sizeof(memory_word));
        if (!new_memory_word)
        {
            fprintf(stderr, "Memory allocation for new memory word failed!");
            exit(1);
        }
        convert_dec_to_x_bit_binary(curr->data_arr[i], num_size * 8 + 1, array);
        reverse_cpy(new_memory_word->bits, array, num_size * 8);
        new_memory_word->address = *DC;
        new_memory_word->number_of_valid_bytes = num_size;

        if (data_tail)
        {
            data_tail->next = new_memory_word;
            data_tail = data_tail->next;
        }
        else
        {
            data_head = new_memory_word;
            data_tail = data_head;
        }
        *DC += num_size;
    }
    return; /*added_mem_words;*/
}

/* add_to_data_table -
   receives: the current sentence (line after it was parsed) and adds to the data tables the data according it's type.
   Adds to DC the number of entries commited */
void add_to_data_table(sentence* curr, int* DC)
{

    switch (curr->guidance_command)
    {
    case (STRING):
        /* num_of_entries */
        add_string_to_data_table(curr, DC);
        break;
    case (NUM_1):
        /* num_of_entries */
        add_num_to_data_table(curr, DC, 1);
        break;
    case (NUM_2):
        /* num_of_entries */
        add_num_to_data_table(curr, DC, 2);
        break;
    case (NUM_4):
        /* num_of_entries */
        add_num_to_data_table(curr, DC, 4);
        break;

    default:
        return;
    }

    return;

}

void free_data_list( void ) {
    memory_word * item = NULL;
    while(data_head)
    {
        item = data_head;
        data_head = data_head->next;
        free(item);
    }
    data_head = NULL;
    data_tail = NULL;
}
