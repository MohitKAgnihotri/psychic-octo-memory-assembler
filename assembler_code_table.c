
#include "assembler_data_table.h"

memory_word *code_tail;
memory_word *code_head;

void add_item_to_code_list(memory_word * item) { /* Code list is a linked list of memory words */
    if (!code_head) { /* First element in linked list */
        code_head = code_tail = item;
    }
    else {
        code_tail->next = item;
        code_tail = item;
    }
}
