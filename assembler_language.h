
#ifndef PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H
#define PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H

#define NUM_OF_SAVED_WORDS 64


typedef enum instruction_type
{
  ins_type_R,
  ins_type_I,
  ins_type_J,
  }instruction_type_t;

typedef enum operand_type
{
  opr_type_collector,
  opr_type_immediate,
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
typedef struct registers {
  char register_name[4];
  char register_val[5];
} registers;

#endif //PSYCHIC_OCTO_MEMORY_ASSEMBLER__ASSEMBLER_LANGUAGE_H
