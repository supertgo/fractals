#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* allow_only_f_math_sings(char* input) {
  char* result;
  unsigned int i = 0;
  unsigned int not_allowed_char_length = 0; 
  unsigned int input_length = strlen(input);
  
  for (i = 0; i < input_length; i++) {
    if (input[i] != 'F' && input[i] != '+' && input[i] != '-') {
      not_allowed_char_length++;
    }
  }

  result = (char*)malloc(input_length - not_allowed_char_length  + 1);

  if (result == NULL) {
    printf("Ocorreu um erro durante a alocação de memória da string para "
           "mostrar o resultado");
    return NULL;
  }

  unsigned j = 0;
  for (i = 0; i < input_length; i++) {
    if (input[i] == 'F' ||  input[i] == '+' || input[i] == '-') {
      result[j] = input[i];
      j++;
    }
  }

  result[j] = '\0';
  return result;
}

char* replace_characters(const char* input, const char** characters,
                         const char** replacements,
                         unsigned int num_replacements) {
  char* result;
  unsigned int i, j;
  unsigned long int result_length = strlen(input);
  const char* match;
  
  for (i = 0; input[i] != '\0'; i++) {
    int match_found = 0;
    for (j = 0; j < num_replacements; j++) {
      match = strstr(&input[i], characters[j]);
      if (match == &input[i]) {
        result_length += strlen(replacements[j]);
        i += strlen(characters[j]) - 1;
        match_found = 1;
        break;
      }
    }
    if (!match_found) {
      result_length++;
    }
  }
  printf("%ld length\n", result_length);

  result = (char*)malloc(result_length + 1);

  if (result == NULL) {
    printf("Ocorreu um erro durante a alocação de memória da string para "
           "mostrar o resultado");
    return NULL;
  }

  i = 0;
  while (*input) {
    int match_found = 0;
    for (j = 0; j < num_replacements; j++) {
      match = strstr(input, characters[j]);
      if (match == input) {
        strcpy(&result[i], replacements[j]);
        i += strlen(replacements[j]);
        input += strlen(characters[j]);
        match_found = 1;
        break;
      }
    }
    if (!match_found) {
      result[i++] = *input++;
    }
  }

  result[i] = '\0';
  return result;
}

int main() {
  int iterator;
  char axiom[] = "XYY";
  char *str;
  char *t = axiom;
  const char *characters[] = {"X", "Y"};
  const char *replecements[] = {"-FY-X", "Y+XF+"};

  printf("Defina a quantidade de itreações: ");
  scanf("%d", &iterator);

  for (int i = 0; i < iterator; i++) {
    str = replace_characters(t, characters, replecements, 2);
    t = str;
  }

  char *allowed = allow_only_f_math_sings(str);
  printf("%s\n", str);
  printf("%s", allowed);

  return 0;
}
