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

int calculaPermanencia(char *entrada, char *saida)
{
  int i = 0;
  int tempo_entrada[2];
  int tempo_saida[2];
  int horas_consideradas = 0;
  int minutos_entrada, minutos_saida;
  int intervalo = 0;
  const char delimitador[2] = ":";
  char *tokenEntrada = strtok(entrada, delimitador);
  char *tokenSaida = strtok(saida, delimitador);

  printf("Foi 1");

  while (tokenEntrada != NULL)
  {
    tempo_entrada[i++] = strtol(tokenEntrada, NULL, 10);
    tokenEntrada = strtok(NULL, delimitador);
  }

  while (tokenSaida != NULL)
  {
    tempo_saida[i++] = strtol(tokenSaida, NULL, 10);
    tokenSaida = strtok(NULL, delimitador);
  }

  if (tempo_entrada[0] < 7)
  {
    printf("ERRO: A entrada só é permitida a partir das 7h");
    return 0;
  }

  if (tempo_saida[0] > 4 && tempo_saida[0] < 7)
  {
    printf("ERRO: A saída é permitida até as 4h");
    return 0;
  }

  minutos_entrada = (tempo_entrada[0]*60)+tempo_entrada[0];
  minutos_saida = (tempo_saida[0]*60)+tempo_saida[0];

  if (minutos_saida > minutos_entrada)
  {
    intervalo = minutos_saida - minutos_entrada;
  }

  horas_consideradas = intervalo / 60;
  if ((intervalo % 60) > 5)
  {
    horas_consideradas++;
  } 
  printf("Foi 2");
  return horas_consideradas;
}

int calculaPreco(int *horas_consideradas)
{
  float total = 0.00;
  int horas, minutos;

  if (horas_consideradas > 0)
  {
    if (horas_consideradas < 2)
    {
      total = total + 8.00;
    }
    if (horas_consideradas < 3 ) 
    {
      total = total + 5.00;
    }
    if (horas_consideradas < 4 ) 
    {
      total = total + 5.00;
    }
    if (horas_consideradas > 4 ) 
    {
      total = total + (*horas_consideradas * 3.50);
    }
  }

  printf("valor a ser pago -> R$ %d", total);
  return 1;
}

int main()
{
  char entrada[80];
  char saida[80];
  int entrada_validada, saida_validada;
  int horas_consideradas;

  do
  {
    printf("Horário de entrada -> ");
    gets(entrada);
    entrada_validada = validaHorario(entrada);
  } while (!entrada_validada);

  do
  {
    printf("Horário de saída -> ");
    gets(saida);
    saida_validada = validaHorario(saida);
  } while (!saida_validada);

  printf("Foi 3");

  if (entrada_validada && saida_validada)
  {
    horas_consideradas = calculaPermanencia(entrada, saida);
    calculaPreco(horas_consideradas);
  }

  return(0);
}
