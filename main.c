#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "word.h"


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
