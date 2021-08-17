
#ifndef PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H
#define PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H

#define NUM_OF_SAVED_WORDS 64
#define MAX_STRING_SIZE 80
#define MAX_SYMBOL_SIZE 128
#define MAX_REGISTER_SIZE 6
#define MAX_OPCODE_SIZE 5
#define MAX_OPERAND_TYPE_SIZE 3
#define MAX_DATA_ARR_SIZE 10
#define MAX_DIGITS_SIZE 10
#define MAX_FILE_NAME_SIZE 256

#define MAX_IMMEDIATE_OPR_VAL (32767)
#define MIN_IMMEDIATE_OPR_VAL (-32768)

typedef enum boolean
{
    FALSE,
    TRUE
}boolean_t;

typedef enum guidance
{
    EXTERN,
    ENTRY,
    NUM_1,
    NUM_2,
    NUM_4,
    STRING
}guidance_t;

typedef enum symbol_type
{
    NONE,
    DATA,
    CODE
}symbol_type_t;

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
    int opcode_binary;
    int func_binary;
    instruction_type_t instruction_type;
    int qty_of_supported_operands;
} opcodes;

/* struct for holding a register and it's binary value */
typedef struct registers
{
    char register_name[4];
    char register_val[5];
} registers;

/* struct for holding the IC \ DC (code memory word address \ data memory word address), an array of 10 bits (in chars), and a pointer to the next struct of the same type */
typedef struct memory_word {
    int address;
    char bits[32]; /* there are 11 places so '\0' can be added */
    struct memory_word *next;
} memory_word;

typedef struct sentence
{
    int is_action; /* 1 if it's an action sentence, 0 if it's a guidance sentence */
    int is_store_command; /* 1 if it's .data/.string./.mat, 0 if it's extern or entry */
    guidance_t guidance_command; /* enum: EXTERN / ENTRY / NUM (=DATA)  / STRING / MAT */
    int is_symbol;
    char symbol[MAX_SYMBOL_SIZE];
    char opcode[MAX_OPCODE_SIZE];
    int num_of_operands; /* 0 if no operands, 1 if destiantion, 2 if if both destination and source*/
    int operand_a_type;
    int operand_b_type;
    int operand_c_type;
    char operand_a_val[MAX_REGISTER_SIZE]; /* for variables, registers, matrixes */
    char operand_b_val[MAX_REGISTER_SIZE]; /* for variables, registers, matrixes */
    char operand_c_val[MAX_REGISTER_SIZE]; /* for variables, registers, matrixes */
    int operand_a; /* when we have "#" */
    int operand_b; /* when we have "#" */
    int operand_c; /* when we have "#" */
    char string[MAX_STRING_SIZE]; /* if guidance_command  = .string, check for it's value in this field */
    int data_arr[MAX_DATA_ARR_SIZE]; /* if guidance command = .data, check for the values in this array */
    int data_arr_num_of_params; /* how many numbers to take from data_arr */
    struct sentence* next;
} sentence;

memory_word * create_new_memory_word( void );

#endif //PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H
