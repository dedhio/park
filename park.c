#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int verificaNumero(char *horario) {
  int i;

  for (i = 0; horario[i] != '\0'; i++)
  {
    if (horario[i] != ':' && horario[i] != 10 && !isdigit(horario[i]))
    {
      return 0;
    }
  }

  return 1;
}

int validaHorario(char *horario)
{
  const char substring[2] = ":";
  int horas=0, minutos=0;

  if (strstr(horario, substring) == NULL)
  {
    printf("ERRO: Utilize o delimitador ':' para definir as horas .\n");
    return 0;
  }

  printf("%s \n", horario);

  if (!verificaNumero(horario))
  {
    printf("ERRO: O horário informado não é numérico. \n");
    return 0;
  }

  sscanf(horario , "%d:%d" , &horas,&minutos);

  if (horas>23)
  {
    printf("ERRO: A hora não pode ser maior que 24. \n");
    return 0;
  }

  if (minutos>60)
  {
    printf("ERRO: Os minutos não podem ser maiores que 60. \n");
    return 0;
  }

  return 1;
}

int calculaPermanencia(char *entrada, char *saida)
{
  int i = 0;
  int horas_entrada, horas_saida, minutos_entrada, minutos_saida;
  int horas_consideradas = 0;
  int intervalo_entrada, intervalo_saida;
  int intervalo = 0;

  sscanf(entrada , "%d:%d" , &horas_entrada,&minutos_entrada);
  sscanf(saida , "%d:%d" , &horas_saida,&minutos_saida);

  if (horas_entrada < 7)
  {
    printf("ERRO: A entrada só é permitida a partir das 7h");
    return 0;
  }

  if (horas_saida > 4 && horas_saida < 7)
  {
    printf("ERRO: A saída é permitida até as 4h");
    return 0;
  }

  intervalo_entrada = (horas_entrada*60)+minutos_entrada;
  intervalo_saida = (horas_saida*60)+minutos_saida;

  if (intervalo_saida > intervalo_entrada)
  {
    intervalo = intervalo_saida - intervalo_entrada;
  }

  printf("Intervalo em minutos -> %d \n", intervalo);

  horas_consideradas = intervalo / 60;
  if ((intervalo % 60) > 5)
  {
    horas_consideradas++;
  } 
  return horas_consideradas;
}

int calculaPreco(int horas_consideradas)
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
      total = total + (horas_consideradas * 3.50);
    }
  }

  printf("\nValor a ser pago -> R$ %.2f \n", total);
  return 1;
}

int main()
{
  char entrada[80];
  char saida[80];
  int entrada_validada = 0;
  int saida_validada = 0;
  int horas_consideradas;

  while (!entrada_validada)
  {
    printf("Horário de entrada -> ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada_validada = validaHorario(entrada);
  }

  while (!saida_validada)
  {
    printf("Horário de saída -> ");
    fgets(saida, sizeof(saida), stdin);
    saida_validada = validaHorario(saida);
  }

  if (entrada_validada && saida_validada)
  {
    horas_consideradas = calculaPermanencia(entrada, saida);
    printf("Horas consideradas -> %d \n", horas_consideradas);
    calculaPreco(horas_consideradas);
  }

  return(0);
}
