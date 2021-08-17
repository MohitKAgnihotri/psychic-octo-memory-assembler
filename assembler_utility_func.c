#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "assembler_language.h"
#include "assembler_utility_func.h"

/* skip_spaces -
receives: line and last position.
returns the last postion where no empty spaces or \t are found. */
int skip_spaces(char* line, int last_position)
{
    while (line[last_position] == ' ' || line[last_position] == '\t')
        last_position++;
    return last_position;
}

/* line_is_empty -
   receives: the line to parse.
   returns true is the line is empty, or false if not. */
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

/* right_symbol_identation -
	receives: the line to parse.
	returns true of it starts with an empty place. */
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

/* Converts a decimal number to any other base. */
int convert_dec_to_another_base(int number,int base){
    if(number == 0 || base==10)
        return number;
    return (number % base) + 10*convert_dec_to_another_base(number / base, base);
}

/* Converts a decimal number to a binary number with padded zeroes up to x bits.
* When calling the function array of chars sized number of bits + 1 (for '\0') should be provided (char * result) */
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

/* Coverts an alphabetic char into its binary value using 10 bits (with zero padding)
* When calling the function array of chars sized number of bits + 1 (for '\0') should be provided (char * result) */
void convert_ascii_value_to_10_bit_binary(char c, char* result)
{
    convert_dec_to_x_bit_binary(c, 11, result);
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

void add_line_to_file_ext(FILE * fp, char * column_a, int column_b)
{
    fprintf(fp, "%s    %.4d\n", column_a, column_b);
}
