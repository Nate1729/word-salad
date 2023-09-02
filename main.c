#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

typedef enum WordPosition_t { BEGINNING, MIDDLE, END, NOWHERE } WordPosition;

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

typedef struct Word_t {
  size_t len_max;
  size_t len;
  char *ptr;
} Word;

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

void process_file(const char *file_name) {
  FILE *f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file!\n");
    return;
  }

  char prev_c, curr_c, word_arr[20];
  size_t word_count = 0;

  Word word = word_create_on_stack(word_arr, 20);

  prev_c = ' ';
  curr_c = fgetc(f);
  while (curr_c != EOF) {
    switch (find_word_position(prev_c, curr_c)) {
    case BEGINNING:
      word_count += 1;
      word_add_letter(&word, curr_c);
      break;
    case MIDDLE:
      word_add_letter(&word, curr_c);
      break;
    case END:
      word_permute(&word);
      word_print(&word);
      word_clear(&word);
      printf("%c", curr_c);
      break;
    case NOWHERE:
      printf("%c", curr_c);
      break;
    }
    /* Loop Stuff */
    prev_c = curr_c;
    curr_c = fgetc(f);
  }

  printf("%lu words transformed.\n", word_count);

  if (fclose(f)) {
    fprintf(stderr, "Error closing file \"%s\"\n", file_name);
  }
}

int main(int argc, char **argv) {

  if (argc == 1) {
    printf("Too few arguments, you need to pass a file name.\n");
  } else if (argc == 2) {
    srand(time(NULL)); /* Seed random number generation */
    process_file(argv[1]);
  }

  return 0;
}
