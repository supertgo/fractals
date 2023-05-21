
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char axiom[100], *str, rule[100];
  const char *characters[] = {"F"};
  const char **replacements;

  printf("Defina o axioma: ");
  scanf("%s", axiom);

  printf("\nDefina a regra: ");
  scanf("%s", rule);

  printf("\nDefina a quantidade de iterações: ");
  scanf("%d", &iterator);

  char *t = axiom;

  replacements = malloc(sizeof(const char*));
  *replacements = malloc(strlen(rule) + 1);
  strcpy((char*)*replacements, rule);

  for (int i = 0; i < iterator; i++) {
    str = replace_characters(t, characters, replacements, 1);
    printf("%s\n", str);
    t = str;
  }

  free((char*)*replacements);
  free(replacements);


  return 0;
}
