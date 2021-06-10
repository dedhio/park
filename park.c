#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificarNumero(char *horario) {
  int i;

  for (i = 0; horario[i] != '\0'; i++)
  {
    if (horario[i] != ':' && !isdigit(horario[i]))
    {
      return 0;
    }
  }

  return 1;
}

int verificarHorario(char *horario)
{
  const char substring[2] = ":";

  if (strstr(horario, substring) != NULL)
  {
    return 0;
  }

  if (verificarNumero(horario))
  {
    printf("São numéricos.\n");
  }
  else
  {
    printf("Não são numéricos.\n");
    return 0;
  }

  int i = 0;
  long tempo[2];
  const char delimitador[2] = ":";
  char *token = strtok(horario, delimitador);

  // Alimenta o vetor de inteiros
  while (token != NULL)
  {
    tempo[i++] = strtol(token, NULL, 10);
    token = strtok(NULL, delimitador);
  }

  // Realize suas validações. Se alguma não for atingida, retorne '0'

  printf("Horas: %d\n", tempo[0]);
  printf("Minutos: %d\n", tempo[1]);

  // Caso contrário, retorne '1'

  return 1;
}

int main()
{
  char entrada[80];
  char saida[80];

  printf("Horário de entrada -> ");
  gets(entrada);
  printf("%d\n", verificarHorario(entrada));

  printf("Horário de saída -> ");
  gets(saida);
  printf("%d\n", verificarHorario(saida));

  return(0);
}
