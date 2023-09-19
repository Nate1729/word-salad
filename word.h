#ifndef WORD_H
#define WORD_H

#include <stdlib.h>

typedef enum WordPosition {BEGINNING, MIDDLE, END, NOWHERE } WordPosition;

WordPosition find_word_position(char previous_char, char current_char);

typedef struct Word_t {
  size_t len_max;
  size_t len;
  char *ptr;
} Word;

/* Create a word on the stack. Requires person to define an array
 * in the large scope and pass the reference here, and also give the
 * length of the array.
 */
Word word_create_on_stack(char *array_ptr, size_t array_len);
int word_add_letter(Word *word, char new_letter);
void word_clear(Word *word);
void word_permute(Word *word);
void word_print(Word *word);

#endif
