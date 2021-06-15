#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificaNumero(char *horario) {
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

int validaHorario(char *horario)
{
  const char substring[2] = ":";

  if (strstr(horario, substring) == NULL)
  {
    printf("ERRO: Utilize o delimitador ':' para definir as horas .\n");
    return 0;
  }

  if (!verificaNumero(horario))
  {
    printf("ERRO: O horário informado não é numérico. \n");
    return 0;
  }

  int i = 0;
  long tempo[2];
  const char delimitador[2] = ":";
  char *token = strtok(horario, delimitador);

  while (token != NULL)
  {
    tempo[i++] = strtol(token, NULL, 10);
    token = strtok(NULL, delimitador);
  }

  if (tempo[0]>23)
  {
    printf("ERRO: A hora não pode ser maior que 24. \n");
    return 0;
  }

  if (tempo[1]>60)
  {
    printf("ERRO: Os minutos não podem ser maiores que 60. \n");
    return 0;
  }

  return 1;
}

int calculaIntervaloMinutos(char *entrada, char *saida)
{
  int i = 0;
  int tempoEntrada[2];
  int tempoSaida[2];
  int minutosEntrada = 0; 
  int minutosSaida = 0;
  int intervalo = 0;
  const char delimitador[2] = ":";
  char *tokenEntrada = strtok(entrada, delimitador);
  char *tokenSaida = strtok(saida, delimitador);

  while (tokenEntrada != NULL)
  {
    tempoEntrada[i++] = strtol(tokenEntrada, NULL, 10);
    tokenEntrada = strtok(NULL, delimitador);
  }

  while (tokenSaida != NULL)
  {
    tempoSaida[i++] = strtol(tokenSaida, NULL, 10);
    tokenSaida = strtok(NULL, delimitador);
  }

  if (tempoEntrada[0] < 8)
  {
    printf("ERRO: A entrada só é permitida a partir das 7h");
    return 0;
  }

  if (tempoSaida[0] > 4 && tempoSaida[0] < 7)
  {
    printf("ERRO: A saída é permitida até as 4h");
    return 0;
  }

  minutosEntrada = (tempoEntrada[0]*60)+tempoEntrada[0];
  minutosSaida = (tempoSaida[0]*60)+tempoSaida[0];

  if (minutosSaida > minutosEntrada)
  {
    intervalo = minutosSaida - minutosEntrada;
  }

  return intervalo;
}

int calculaPreco(int *minutos_considerados)
{
  float total = 0.00;
  int horas, minutos;
  int intervalo = minutos_considerados;

  if (minutos_considerados < 61)
  {
    total = 8.00;
  }
  else if (minutos_considerados < 181)
  {
    horas = intervalo / 60;
    total = 5.00 * horas;
  }

  printf("valor a ser pago -> R$ %d", total);
  return 1;
}

int main()
{
  char entrada[80];
  char saida[80];
  int entradaValidada, saidaValidada;
  int minutos_considerados;

  while (!entradaValidada)
  {
    printf("Horário de entrada -> ");
    gets(entrada);
    entradaValidada = validaHorario(entrada);
  }

  while (!saidaValidada)
  {
    printf("Horário de saída -> ");
    gets(saida);
    saidaValidada = validaHorario(saida);
  }

  if (entradaValidada && saidaValidada)
  {
    minutos_considerados = calculaIntervaloMinutos(entrada, saida);
    calculaPreco(minutos_considerados);
  }

  return(0);
}
