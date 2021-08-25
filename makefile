edit : assembler.o assembler_language.o assembler_first_pass.o assembler_second_pass.o assembler_error.o assembler_line_parser.o assembler_utility_func.o assembler_symbol_table.o assembler_data_table.o assembler_code_table.o
	cc -o assembler assembler.o assembler_language.o assembler_first_pass.o assembler_second_pass.o assembler_error.o assembler_line_parser.o assembler_utility_func.o assembler_symbol_table.o assembler_data_table.o assembler_code_table.o

assembler.o : assembler.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler.c
assembler_language.o : assembler_language.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_language.c
assembler_first_pass.o : assembler_first_pass.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_first_pass.c
assembler_second_pass.o : assembler_second_pass.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_second_pass.c
assembler_error.o : assembler_error.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_error.c
assembler_line_parser.o : assembler_line_parser.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_line_parser.c
assembler_utility_func.o : assembler_utility_func.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_utility_func.c
assembler_symbol_table.o : assembler_symbol_table.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_symbol_table.c

assembler_data_table.o : assembler_data_table.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_data_table.c

assembler_code_table.o : assembler_code_table.c assembler_language.h assembler.h assembler_first_pass.h  assembler_second_pass.h assembler_error.h  assembler_line_parser.h assembler_utility_func.h  assembler_symbol_table.h  assembler_data_table.h  assembler_code_table.h
	cc -c assembler_code_table.c

clean :
	rm *.o assembler
