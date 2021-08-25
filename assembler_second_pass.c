#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include "assembler_language.h"
#include "assembler_utility_func.h"
#include "assembler_data_table.h"
#include "assembler_symbol_table.h"
#include "assembler_code_table.h"
#include "assembler_second_pass.h"

#define OBJECT_FILE_EXTENSION ".ob"
#define EXTERN_FILE_EXTENSION ".ext"
#define ENTRY_FILE_EXTENSION ".ent"
#define CODE_TABLE_START_ADDRESS 100

int ic_second_pass;
int is_error_found;
static int line_number;

int keep_ext_file = 0;
int keep_ent_file = 0;

extern int DC;

FILE* object_filename_fp = NULL;
FILE* extern_filename_fp = NULL;
FILE* intern_filename_fp = NULL;

extern sentence* sentence_head;
extern sentence* sentence_tail;

extern memory_word* code_tail;
extern memory_word* code_head;

extern memory_word* data_tail;
extern memory_word* data_head;

extern opcodes opcodes_table[];
extern int opcode_table_length;

extern registers registers_table[];
extern int registers_table_length;

void encode_instruction_R1(sentence* curr, memory_word* word)
{
    int j = 0;
    /* 3 operands are expected */
    if (curr->operand_type[0] == opr_type_collector)
    {
        for ( j= 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[0]) == 0)
            {
                memcpy(&word->bits[21], registers_table[j].register_val, 5);
                break;
            }
        }
    }
    if (curr->operand_type[1] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[1]) == 0)
            {
                memcpy(&word->bits[16], registers_table[j].register_val, 5);
                break;
            }
        }
    }

    if (curr->operand_type[2] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[2]) == 0)
            {
                memcpy(&word->bits[11], registers_table[j].register_val, 5);
                break;
            }
        }
    }
}

void encode_instruction_R2(sentence* curr, memory_word* word)
{
    int j = 0;
    /* 2 operands are expected */
    if (curr->operand_type[0] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[0]) == 0)
            {
                memcpy(&word->bits[21], registers_table[j].register_val, 5);
                break;
            }
        }
    }

    if (curr->operand_type[1] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[1]) == 0)
            {
                memcpy(&word->bits[11], registers_table[j].register_val, 5);
                break;
            }
        }
    }

    /* Set rd to  all zeros */
    memcpy(&word->bits[16], "00000", 5);
}

void encode_instruction_I1(sentence* curr, memory_word* word)
{
    int j = 0;
    /*3 operands are expected */
    if (curr->operand_type[0] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[0]) == 0)
            {
                memcpy(&word->bits[21], registers_table[j].register_val, 5);
                break;
            }
        }
    }

    if (curr->operand_type[2] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[2]) == 0)
            {
                memcpy(&word->bits[16], registers_table[j].register_val, 5);
                break;
            }
        }
    }

    if (curr->operand_type[1] == opr_type_immediate)
    {
        char array_func[17] = { 0 };
        convert_dec_to_x_bit_binary(curr->operand[1], 17, array_func);
        reverse_cpy(&word->bits[0], array_func, 16);
    }
}

void encode_instruction_I2(sentence* curr, memory_word* word)
{
    int j = 0;
    /* 3 operands are expected */
    if (curr->operand_type[0] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[0]) == 0)
            {
                memcpy(&word->bits[21], registers_table[j].register_val, 5);
                break;
            }
        }
    }

    if (curr->operand_type[1] == opr_type_collector)
    {
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[1]) == 0)
            {
                memcpy(&word->bits[16], registers_table[j].register_val, 5);
                break;
            }
        }
    }

    if (curr->operand_type[2] == opr_type_direct)
    {
        symbol_line* sl = get_symbol_line_from_symbol_table(curr->operand_val[2]);
        if (sl && sl->is_extern)
        {
            sl->address = ic_second_pass;
            keep_ext_file = 1;
            add_line_to_file(extern_filename_fp, sl->symbol, ic_second_pass);
        }
        else
        {
            char array_func[17] = { 0 };
            convert_dec_to_x_bit_binary(sl->address - ic_second_pass, 17, array_func);
            reverse_cpy(&word->bits[0], array_func, 16);
        }
    }
}

void encode_instruction_J1_J2(sentence* curr, memory_word* word)
{
    int j = 0;
    symbol_line* sl = NULL;
    /* 3 operands are expected */
    if (curr->operand_type[0] == opr_type_collector)
    {
        word->bits[25] = '1';
        for (j = 0; j < registers_table_length; j++)
        {
            if (strcmp(registers_table[j].register_name, curr->operand_val[0]) == 0)
            {
                memcpy(&word->bits[0], registers_table[j].register_val, 5);
                memcpy(&word->bits[5], "00000000000000000000000000", 21);
                break;
            }
        }
    }
    else if (curr->operand_type[0] == opr_type_direct)
    {
        word->bits[25] = '0';
        sl = get_symbol_line_from_symbol_table(curr->operand_val[0]);
        if (sl)
        {
            if (sl->is_extern)
            {
                sl->address = ic_second_pass;
                keep_ext_file = 1;
                add_line_to_file(extern_filename_fp, sl->symbol, ic_second_pass);
                memcpy(&word->bits[0], "00000000000000000000000000", 26);
            }
            else
            {
                char array_func[26] = { 0 };
                convert_dec_to_x_bit_binary(sl->address, 26, array_func);
                reverse_cpy(&word->bits[0], array_func, 25);
            }
        }
        else
        {
            fprintf(stderr, "ERROR: Second PASS Can't Continue.. Exiting \n");
            exit(-1);
        }
    }
}

void encode_instruction_S(sentence* curr, memory_word* word)
{
    memcpy(&word->bits[0], "000000000000000000000000000", 27);
}

/* Encode instruction sentence into code table */
void encode_instruction(sentence* curr)
{
    int i;
    memory_word* new_memory_word = create_new_memory_word();
    new_memory_word->address = ic_second_pass;
    for (i = 0; i < opcode_table_length; i++)
    {
        if (strcmp(opcodes_table[i].opcode, curr->opcode) == 0)
        {
            char array_func[6] = { 0 };
            char array[7] = { 0 };
            convert_dec_to_x_bit_binary(opcodes_table[i].opcode_binary, 7, array);
            reverse_cpy(&new_memory_word->bits[26], array, 6);
            if (opcodes_table[i].instruction_type == ins_type_R_1)
            {
                encode_instruction_R1(curr, new_memory_word);
                convert_dec_to_x_bit_binary(opcodes_table[i].func_binary, 6, array_func);
                reverse_cpy(&new_memory_word->bits[6], array_func, 5);
                memcpy(&new_memory_word->bits[0], "000000", 6);
                break;
            }
            else if (opcodes_table[i].instruction_type == ins_type_R_2)
            {
                encode_instruction_R2(curr, new_memory_word);
                convert_dec_to_x_bit_binary(opcodes_table[i].func_binary, 6, array_func);
                reverse_cpy(&new_memory_word->bits[6], array_func, 5);
                memcpy(&new_memory_word->bits[0], "000000", 6);
                break;
            }
            else if (opcodes_table[i].instruction_type == ins_type_I_1)
            {
                encode_instruction_I1(curr, new_memory_word);
            }
            else if (opcodes_table[i].instruction_type == ins_type_I_2)
            {
                encode_instruction_I2(curr, new_memory_word);
            }
            else if (opcodes_table[i].instruction_type == ins_type_J_1)
            {
                encode_instruction_J1_J2(curr, new_memory_word);
            }
            else if (opcodes_table[i].instruction_type == ins_type_J_2)
            {
                encode_instruction_J1_J2(curr, new_memory_word);
            }
            else if (opcodes_table[i].instruction_type == ins_type_S)
            {
                encode_instruction_S(curr, new_memory_word);
            }
            else
            {
                assert(1);
            }
            break;
        }
    }
    add_item_to_code_list(new_memory_word);
    ic_second_pass += 4;
}

int assembler_execute_second_pass(char* filename)
{
    char input_filename[MAX_FILE_NAME_SIZE] = { 0 };
    char object_filename[MAX_FILE_NAME_SIZE] = { 0 };
    char extern_filename[MAX_FILE_NAME_SIZE] = { 0 };
    char intern_filename[MAX_FILE_NAME_SIZE] = { 0 };

    memory_word* current_memory_word = NULL;
    memory_word* curr_data_head = NULL;
    char* buffer = NULL;
    int index = 0;
    int max_bytes_to_print = 0;

    sentence* current_sentence = sentence_head;

    ic_second_pass = CODE_TABLE_START_ADDRESS;
    is_error_found = 0;
    line_number = 1;

    strcpy(input_filename, filename);
    combine_filename_with_new_file_extension(input_filename, object_filename, OBJECT_FILE_EXTENSION);
    combine_filename_with_new_file_extension(input_filename, extern_filename, EXTERN_FILE_EXTENSION);
    combine_filename_with_new_file_extension(input_filename, intern_filename, ENTRY_FILE_EXTENSION);

    object_filename_fp = fopen(object_filename, "w+");
    assert(object_filename_fp);
    extern_filename_fp = fopen(extern_filename, "w+");
    assert(extern_filename_fp);
    intern_filename_fp = fopen(intern_filename, "w+");
    assert(intern_filename_fp);


    /* Second pass - actual encoding of the code table */
    while (current_sentence)
    {
        if (current_sentence->is_action == 0)
        { /* is guidance sentence */
            if (current_sentence->guidance_command == ENTRY)
            {
                symbol_line* sl = get_symbol_line_from_symbol_table(current_sentence->symbol);
                if (!sl)
                {
                    break;
                }
                keep_ent_file = 1;
                add_line_to_file(intern_filename_fp, sl->symbol, sl->address);
            }
        }
        else
        {  /* is instruction sentence */
            encode_instruction(current_sentence);
        }

        line_number++;
        current_sentence = current_sentence->next;
        if (is_error_found)
        {
            fprintf(stderr, "ERROR: Errors found in second pass. Output files will not be created.\n");
            fclose(intern_filename_fp);
            fclose(extern_filename_fp);
            fclose(object_filename_fp);
            return 0;
        }
    }

    fprintf(object_filename_fp, "%d %d \n", ic_second_pass - 100, DC);
    current_memory_word = code_head;
    while (current_memory_word)
    {
        int* test = convert_to_hex(current_memory_word->bits);
        fprintf(object_filename_fp, "%.4d %.2X %.2X %.2X %.2X \n", current_memory_word
            ->address, test[0], test[1], test[2], test[3]);
        current_memory_word = current_memory_word->next;
    }

    /*Add Data to the binary image*/
    curr_data_head = data_head;

    buffer = malloc(sizeof(char) * DC * 8);
    index = 0;
    while (curr_data_head)
    {
        memcpy(&buffer[index * 8], curr_data_head->bits, curr_data_head->number_of_valid_bytes * 8);
        index += curr_data_head->number_of_valid_bytes;
        curr_data_head = curr_data_head->next;
    }

    index = 0;
    max_bytes_to_print = DC;
    while (index < (DC * 8))
    {
        int* test = convert_to_hex(&buffer[index]);
        if (max_bytes_to_print > 4)
        {
            fprintf(object_filename_fp, "%.4d %.2X %.2X %.2X %.2X \n", ic_second_pass, test[0], test[1], test[2], test[3]);
            max_bytes_to_print -= 4;
        }
        else if (max_bytes_to_print == 3)
        {
            fprintf(object_filename_fp, "%.4d %.2X %.2X %.2X \n", ic_second_pass, test[0], test[1], test[2]);
            max_bytes_to_print -= 3;
        }
        else if (max_bytes_to_print == 2)
        {
            fprintf(object_filename_fp, "%.4d %.2X %.2X \n", ic_second_pass, test[0], test[1]);
            max_bytes_to_print -= 2;
        }
        else if (max_bytes_to_print == 1)
        {
            fprintf(object_filename_fp, "%.4d %.2X \n", ic_second_pass, test[0]);
            max_bytes_to_print -= 1;
        }
        ic_second_pass += 4;
        index += 32;
    }

    fclose(intern_filename_fp);
    fclose(extern_filename_fp);
    fclose(object_filename_fp);

    if (!keep_ext_file)
    {
        remove(extern_filename);
    }
    if (!keep_ent_file)
    {
        remove(intern_filename);
    }
    return 0;
}
