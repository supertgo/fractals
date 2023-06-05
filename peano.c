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
  unsigned long int result_length = 0;
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

char **create_rule_array(const char *ruleX, const char *ruleY) {
  char **rules = malloc(2 * sizeof(char *));
  rules[0] = malloc(strlen(ruleX) + 1);
  rules[1] = malloc(strlen(ruleY) + 1);
  strcpy(rules[0], ruleX);
  strcpy(rules[1], ruleY);
  return rules;
}

int main() {
  int iterator = 4, angle, number;
  char axiom[100], *str, ruleX[100], ruleY[100], *result;
  const char *characters[] = {"X", "Y"};
  char **replacements;

  printf("Defina número do fractal correspondente: ");
  scanf("%d", &number);

  printf("Defina o axioma: ");
  scanf("%s", axiom);

  printf("\nDefina o angulo: ");
  scanf("%d", &angle);

  printf("\nDefina a regra do X: ");
  scanf("%s", ruleX);

  printf("\nDefina a regra do Y: ");
  scanf("%s", ruleY);

  char *t = axiom;
  replacements = create_rule_array(ruleX, ruleY);

  FILE *file = fopen("thiagor-peano-saida.txt", "w");
 
  if (file == NULL) {
    printf("Erro ao abrir o arquivo thiagor-peano-saida.txt\n");
    return 1;
  }

  fprintf(file, "Numero do fractal correspondente: %d\n", number);
  fprintf(file, "Axioma: %s\n", axiom);
  fprintf(file, "Angulo dado em graus: %d\n", angle);
  fprintf(file, "Regra do X -> %s\n", ruleX);
  fprintf(file, "Regra do Y -> %s\n", ruleY);
  fprintf(file, "%s\n", "---------------------------------------------------------------------------------");

  for (int i = 0; i < iterator; i++) {
    str = replace_characters(t, characters, (const char **)replacements, 2);
    result = allow_only_f_math_sings(str);
    fprintf(file, "Sequência de caracteres do %dº estágio: %s\n", i + 1, result);
    fprintf(file, "%s\n", "---------------------------------------------------------------------------------");
    t = str;
  }
  
  for (int i = 0; i < 2; i++) {
    free((void *)replacements[i]);
  }

  free(replacements);

  return 0;
}

