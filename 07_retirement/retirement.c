#include<stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculation(int startAge,
                 int months, double balance, retire_info info) {
  for (int i = 0; i < months; i++) {
    int age = (i + startAge) / 12;
    int month = (startAge + i) % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    double increase = balance * info.rate_of_return;
    balance = balance + increase + info.contribution;
  }
  return balance;
}

void retirement(int startAge,
                double initial,
                retire_info working,
                retire_info retired) {
  double balance = initial;
  balance = calculation(startAge, working.months, balance, working);
  startAge += working.months;
  calculation(startAge, retired.months, balance, retired);
}

int main(void){
  retire_info working;
  working.contribution = 1000;
  working.months = 489;
  working.rate_of_return = 0.045/12;

  retire_info retired;
  retired.contribution = -4000;
  retired.months = 384;
  retired.rate_of_return = 0.01/12;

  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
