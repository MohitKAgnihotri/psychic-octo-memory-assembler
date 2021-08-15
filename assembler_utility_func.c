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