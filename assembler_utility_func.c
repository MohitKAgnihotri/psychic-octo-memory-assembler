#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "assembler_language.h"
#include "assembler_utility_func.h"

int skip_spaces(char* line, int last_position)
{
    while (line[last_position] == ' ' || line[last_position] == '\t')
        last_position++;
    return last_position;
}

int line_is_empty(char* line)
{
    int i;
    i = skip_spaces(line, 0);
    return (line[i] == '\n' || line[i] == EOF);
}

int is_current_word_empty(char* word)
{
    return strlen(word) == 0 ? 1 : 0;
}

int right_symbol_identation(char* line)
{
    return !(line[0] == ' ' || line[0] == '\t');
}

int is_alphanumeric(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (!isalnum(str[i]))
            return FALSE;
        i++;
    }
    return TRUE;
}

int strcmp_lower(char* word1, char* word2)
{
    int i = 0;
    char word1_lower[MAX_STRING_SIZE];
    while (word1[i] != '\0')
    {
        word1_lower[i] = tolower(word1[i]);
        i++;
    }
    word1_lower[i] = '\0';
    return strcmp(word1_lower, word2);
}

int convert_dec_to_another_base(int number,int base){
    if(number == 0 || base==10)
        return number;
    return (number % base) + 10*convert_dec_to_another_base(number / base, base);
}

void convert_dec_to_x_bit_binary(int num, int bits, char* result)
{
    int i = bits - 1;
    int binary_num = convert_dec_to_another_base(num, 2);

    result[i] = '\0';
    i--;
    do
    {
        result[i] = binary_num % 10 == 0 ? '0' : '1';
        binary_num = binary_num / 10;
        i--;
    } while (binary_num);

    for (; i >= 0; i--)
    { /* pad with zeros */
        result[i] = '0';
    }
    /* perform 2's complement if it's a negative number */
    if (num < 0)
    {
        int i = bits - 2;
        int first_one_encountered = 0;
        for (; i >= 0; i--)
        {
            if (first_one_encountered == 0)
            {
                if (result[i] == '1')
                {
                    first_one_encountered = 1;
                    continue;
                }
            }
            else
            {
                result[i] = result[i] == '1' ? '0' : '1';
            }
        }
    }
}

void convert_ascii_value_to_10_bit_binary(char c, char* result)
{
    char array[9] = {0};
    convert_dec_to_x_bit_binary(c, 9, array);
    reverse_cpy(result,array,8);
}

void combine_filename_with_new_file_extension(char * filename, char * output_filename, char * extension)
{
    char * filename_prefix;
    char extension_filename[MAX_FILE_NAME_SIZE];
    char copy_of_filename[MAX_FILE_NAME_SIZE];
    strcpy(copy_of_filename, filename);
    filename_prefix = strtok(copy_of_filename, ".");
    strcpy(extension_filename, filename_prefix);
    strcat(extension_filename, extension);
    strcpy(output_filename, extension_filename);
}

void add_line_to_file(FILE * fp, char * val, int address)
{
    fprintf(fp, "%s    %.4d\n", val, address);
}


void reverse_cpy(char *restrict dst, const char *restrict src, size_t n)
{
    size_t i;
    for (i=0; i < n; ++i)
        dst[n-1-i] = src[i];

}

int * convert_to_hex(char * string)
{
    int *hex_val = malloc(sizeof(int) * 4);
    if (!hex_val)
        return NULL;
    else
    {
        for (int i = 0; i < 8; i++)
        {
            hex_val[0] = hex_val[0]  + ((string[i] - '0') << i);
            hex_val[1] = hex_val[1]  + ((string[i+8] - '0') << i);
            hex_val[2] = hex_val[2]  + ((string[i+16] - '0') << i);
            hex_val[3] = hex_val[3]  + ((string[i+24] - '0') << i);
        }
    }
    return hex_val;
}
