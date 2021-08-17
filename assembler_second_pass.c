#include <string.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <assert.h>
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

FILE *object_filename_fp = NULL;
FILE *extern_filename_fp = NULL;
FILE *intern_filename_fp = NULL;


extern sentence *sentence_head;
extern sentence * sentence_tail;

extern opcodes opcodes_table[];
extern int opcode_table_length;

extern registers registers_table[];
extern int registers_table_length;

/* Encode instruction sentence into code table */
void encode_instruction(sentence * curr)
{
    int i;
    memory_word * new_memory_word = create_new_memory_word();
    new_memory_word->address = ic_second_pass;
    for(i = 0; i < opcode_table_length; i++)
    {
        if (strcmp(opcodes_table[i].opcode, curr->opcode) == 0)
        {
            convert_dec_to_x_bit_binary(opcodes_table[i].opcode_binary, 6, &new_memory_word->bits[26]);
            if (opcodes_table[i].instruction_type == ins_type_R)
            {
                assert(curr->operand_a_type == opr_type_collector);
                for(int j = 0; j < registers_table_length; j++)
                {
                    if (strcmp(registers_table[j].register_name, curr->operand_a_val) == 0)
                    {
                        strncat(new_memory_word->bits,registers_table[i].register_val,5);
                        break;
                    }
                }
                assert(curr->operand_b_type == opr_type_collector);;
                for(int j = 0; j < registers_table_length; j++)
                {
                    if (strcmp(registers_table[j].register_name, curr->operand_b_val) == 0)
                    {
                        strncat(new_memory_word->bits,registers_table[i].register_val,5);
                        break;
                    }
                }
                assert(curr->operand_c_type == opr_type_collector);
                for(int j = 0; j < registers_table_length; j++)
                {
                    if (strcmp(registers_table[j].register_name, curr->operand_c_val) == 0)
                    {
                        strncat(new_memory_word->bits,registers_table[i].register_val,5);
                        break;
                    }
                }
                strncat(new_memory_word->bits, opcodes_table[i].func_binary,5);
                strncat(new_memory_word->bits, "000000",6);
            }
            else if (opcodes_table[i].instruction_type == ins_type_I)
            {
                assert(curr->operand_a_type == opr_type_collector);
                for(int j = 0; j < registers_table_length; j++)
                {
                    if (strcmp(registers_table[j].register_name, curr->operand_a_val) == 0)
                    {
                        strncat(new_memory_word->bits,registers_table[i].register_val,5);
                        break;
                    }
                }
                assert(curr->operand_b_type == opr_type_collector);;
                for(int j = 0; j < registers_table_length; j++)
                {
                    if (strcmp(registers_table[j].register_name, curr->operand_b_val) == 0)
                    {
                        strncat(new_memory_word->bits,registers_table[i].register_val,5);
                        break;
                    }
                }
                assert(curr->operand_c_type == opr_type_immediate || curr->operand_c_type == opr_type_direct);
                {
                    if (curr->operand_c_type == opr_type_immediate)
                    {
                        char arr[6];
                        convert_dec_to_x_bit_binary(curr->operand_c, 5, arr);
                        strncat(new_memory_word->bits, arr, 6);
                    }
                    else if (curr->operand_c_type == opr_type_direct)
                    {
                        symbol_line * sl = get_symbol_line_from_symbol_table(curr->operand_c_val);
                        if (!sl) {
                            break;
                        }
                        if(sl->is_extern)
                        {
                            add_line_to_file_ext(intern_filename_fp, sl->symbol, curr->);
                        }
                    }
                }
            }
            else if (opcodes_table[i].instruction_type == ins_type_J)
            {
                assert(curr->operand_a_type == opr_type_collector);
                for(int j = 0; j < registers_table_length; j++)
                {
                    if (strcmp(registers_table[j].register_name, curr->operand_a_val) == 0)
                    {
                        strncat(new_memory_word->bits,registers_table[i].register_val,5);
                        break;
                    }
                }
                assert(curr->operand_c_type == opr_type_immediate);
                {
                    char arr[25];
                    convert_dec_to_x_bit_binary( curr->operand_c, 6, arr);
                    strncat(new_memory_word->bits, arr, 25);
                }
            }
            else
            {
                // error condition
                assert(1);
            }
        }
    }
    add_item_to_code_list(new_memory_word);
    ic_second_pass +=4;
}

int assembler_execute_second_pass(char *filename)
{
    char input_filename[MAX_FILE_NAME_SIZE] = {0};
    char object_filename[MAX_FILE_NAME_SIZE] = {0};
    char extern_filename[MAX_FILE_NAME_SIZE] = {0};
    char intern_filename[MAX_FILE_NAME_SIZE] = {0};

    sentence * current_sentence = sentence_head;

    ic_second_pass = CODE_TABLE_START_ADDRESS;
    is_error_found = 0;
    line_number = 1;

    strcpy(input_filename, filename);
    combine_filename_with_new_file_extension(input_filename, object_filename, OBJECT_FILE_EXTENSION);
    combine_filename_with_new_file_extension(input_filename, extern_filename, EXTERN_FILE_EXTENSION);
    combine_filename_with_new_file_extension(input_filename, intern_filename, ENTRY_FILE_EXTENSION);

    object_filename_fp = fopen(object_filename,"w+");
    assert(object_filename_fp);
    extern_filename_fp = fopen(extern_filename,"w+");
    assert(extern_filename_fp);
    intern_filename_fp = fopen(intern_filename,"w+");
    assert(intern_filename_fp);


    /* Second pass - actual encoding of the code table */
    while(current_sentence)
    {
        if(current_sentence->is_action == 0)
        { /* is guidance sentence */
            if (current_sentence->guidance_command == ENTRY)
            {
                symbol_line * sl = get_symbol_line_from_symbol_table(current_sentence->symbol);
                if (!sl) {
                    break;
                }
                add_line_to_file_ext(intern_filename_fp, sl->symbol, sl->address);
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

#if 0
        append_data_table_into_end_of_code_table(data_head);
        create_object_file();
        close_second_pass_output_files();
        free_second_pass_data_structs_linked_lists();
#endif

    }
    fclose(intern_filename_fp);
    fclose(extern_filename_fp);
    fclose(object_filename_fp);
}
