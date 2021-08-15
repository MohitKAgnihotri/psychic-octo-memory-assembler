
#ifndef PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H
#define PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H

#define NUM_OF_SAVED_WORDS 64
#define MAX_STRING_SIZE 80
#define MAX_SYMBOL_SIZE 31
#define MAX_OPCODE_SIZE 5
#define MAX_OPERAND_TYPE_SIZE 3
#define MAX_DATA_ARR_SIZE 10
#define MAX_DIGITS_SIZE 5

#define MAX_IMMEDIATE_OPR_VAL (32767)
#define MIN_IMMEDIATE_OPR_VAL (-32768)

enum boolean
{
    FALSE, TRUE
};
enum guidance
{
    EXTERN, ENTRY, NUM, STRING
};

typedef enum instruction_type
{
    ins_type_R,
    ins_type_I,
    ins_type_J,
} instruction_type_t;

typedef enum operand_type
{
  opr_type_collector,
  opr_type_immediate,
  opr_type_direct,
}operand_type_t;

/* struct for holding an opcode and it's binary value */
typedef struct opcodes {
  char* opcode;
  char opcode_binary[6];
  char func_binary[5];
  int qty_of_supported_operands;
    int source_operand_types[5];
    int destination_operand_types[5];
} opcodes;

/* struct for holding a register and it's binary value */
typedef struct registers
{
    char register_name[4];
    char register_val[5];
} registers;

typedef struct sentence
{
    int is_action; /* 1 if it's an action sentence, 0 if it's a guidance sentence */
    int is_store_command; /* 1 if it's .data/.string./.mat, 0 if it's extern or entry */
    int guidance_command; /* enum: EXTERN / ENTRY / NUM (=DATA)  / STRING / MAT */
    int is_symbol;
    char symbol[MAX_SYMBOL_SIZE];
    char opcode[MAX_OPCODE_SIZE];
    int num_of_operands; /* 0 if no operands, 1 if destiantion, 2 if if both destination and source*/
    int source_operand_a_type;
    int source_operand_b_type;
    char dest_operand_type;
    char operand_1[MAX_SYMBOL_SIZE]; /* for variables, registers, matrixes */
    char operand_2[MAX_SYMBOL_SIZE]; /* for variables, registers, matrixes */
    char operand_3[MAX_SYMBOL_SIZE]; /* for variables, registers, matrixes */
    int immediate_operand_a; /* when we have "#" */
    int immediate_operand_b; /* when we have "#" */
    int immediate_operand_c; /* when we have "#" */
    char string[MAX_STRING_SIZE]; /* if guidance_command  = .string, check for it's value in this field */
    int data_arr[MAX_DATA_ARR_SIZE]; /* if guidance command = .data, check for the values in this array */
    int data_arr_num_of_params; /* how many numbers to take from data_arr */
    struct sentence* next;
} sentence;

#endif //PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H
