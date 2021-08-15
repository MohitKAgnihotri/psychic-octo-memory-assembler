
#ifndef _ASSEMBLER_UTILITY_FUNC_H_
#define _ASSEMBLER_UTILITY_FUNC_H_

int skip_spaces(char* line, int last_position);
int line_is_empty(char* line);
int is_current_word_empty(char* word);
int is_alphanumeric(char* str);
int strcmp_lower(char* word1, char* word2);
int right_symbol_identation(char* line);

#endif //_ASSEMBLER_UTILITY_FUNC_H_
