#include <stdio.h>
#include "assembler_line_parser.h"
#include "assembler_error.h"
#include "assembler_language.h"
#include "assembler_first_pass.h"

#define LINE_LENGTH 256

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

    }

}
