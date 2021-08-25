#include "assembler_language.h"
#ifndef PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LINE_PARSER_H
#define PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LINE_PARSER_H

sentence* assembler_parse_sentence(char* line, int line_number, int* syntax_errors);

#endif
