#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AXIOM "F-F++F-F"

char *replace_every_f_for_axiom(char *input, char *new_word) {
  char old_word[] = "F";
  char *result;
  int i, ocurrences_of_old_word = 0;
  int new_word_length = strlen(new_word);
  int old_word_length = 1;

  for (i = 0; input[i] != '\0'; i++) {
    if (strstr(&input[i], old_word) == &input[i]) {
      ocurrences_of_old_word++;
      i += old_word_length - 1;
    }
  }

  result = (char *)malloc(
      i + ocurrences_of_old_word * (new_word_length - old_word_length) + 1);

  i = 0;
  while (*input) {
    if (strstr(input, old_word) == input) {
      strcpy(&result[i], new_word);
      i += new_word_length;
      input += old_word_length;
    } else {
      result[i++] = *input++;
    }
  }

  result[i] = '\0';
  return result;
}

int main() {
  char axiom[] = "F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++"
                 "F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-"
                 "F-F++F-F++F-F++F-F-F-F++F-F";
  char *str;
  char *t = axiom;

  for (int i = 0; i < 1; i++) {
    str = replace_every_f_for_axiom(AXIOM, t);
    t = str;
  }

  printf("%s", str);

  return 0;
}

