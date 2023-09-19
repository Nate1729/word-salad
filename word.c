#include <stdio.h>

#include "word.h"

/* Determine if an `char` is an ascii character
 *
 * Returns:
 *  0 - Not an ASCII number
 *  1 - Uppercase
 *  2 - Lowercase
 */
int is_acii_letter(char c) {
  /* Upper case letters range from 65-90
   * Lower case letters range from 97-122
   */
  if (64 < c && c < 91) {
    return 1;
  }
  if (96 < c && c < 123) {
    return 2;
  }

  return 0;
}

WordPosition find_word_position(char previous_char, char current_char) {
  if (is_acii_letter(previous_char)) {
    if (is_acii_letter(current_char)) {
      return MIDDLE;
    } else {
      return END;
    }
  }
  if (is_acii_letter(current_char)) {
    return BEGINNING;
  }
  return NOWHERE;
}

/* Create a word on the stack. Requires person to define an array
 * in the large scope and pass the reference here, and also give the
 * length of the array.
 */
Word word_create_on_stack(char *array_ptr, size_t array_len) {
  return (Word){.len = 0, .ptr = array_ptr, .len_max = array_len};
}

int word_add_letter(Word *word, char new_letter) {
  if (word->len_max == word->len) {
    fprintf(stderr, "Error! Exceeded maximum word size of %lu!\n",
            word->len_max);
    return -1;
  }

  if (new_letter == '\0') {
    fprintf(stderr, "Error! You can't append the null character!\n");
    return -1;
  }

  word->ptr[word->len] = new_letter;
  word->len += 1;
  return 0;
}

void word_clear(Word *word) {
  int i;
  for (i = 0; i < word->len_max; i++) {
    word->ptr[i] = 0;
  }

  word->len = 0;
}

void word_permute(Word *word) {
  if (word->len == 1 || word->len == 2) {
    return;
  }

  /* Using the Fisher-Yates shuffle */
  int i, new_index;
  char c;

  for (i = 1; i < word->len; i++) {
    c = word->ptr[i];
    new_index = rand() % (word->len - (i)) + i;
    word->ptr[i] = word->ptr[new_index];
    word->ptr[new_index] = c;
  }
}

void word_print(Word *word) {
  int i;
  for (i=0; i<word->len; i++) {
    printf("%c", word->ptr[i]);
  }
}
