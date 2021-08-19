
#ifndef _ASSEMBLER_UTILITY_FUNC_H_
#define _ASSEMBLER_UTILITY_FUNC_H_

int skip_spaces(char* line, int last_position);
int line_is_empty(char* line);
int is_current_word_empty(char* word);
int is_alphanumeric(char* str);
int strcmp_lower(char* word1, char* word2);
int right_symbol_identation(char* line);
void convert_ascii_value_to_10_bit_binary(char c, char* result);
void convert_dec_to_x_bit_binary(int num, int bits, char* result);
int convert_dec_to_another_base(int number,int base);
void combine_filename_with_new_file_extension(char * filename, char * output_filename, char * extension);
void add_line_to_file(FILE * fp, char * val, int add);
void reverse_cpy(char *restrict dst, const char *restrict src, size_t n);
int * convert_to_hex(char * string);
#endif //_ASSEMBLER_UTILITY_FUNC_H_
