#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double compound_earned(double startAmount, double contributeAmount, double rate) {
  return startAmount * (1 + rate / 12) + contributeAmount;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int working_months = 0;
  int retire_months = 0;
  while (working_months < working.months) {
    int year = startAge / 12;
    int month = startAge % 12;
    printf("Age %3d month %2d you have $%.2f\n", year, month, initial);
    initial = compound_earned(initial, working.contribution, working.rate_of_return);
    startAge++;
    working_months++;
  }

  while (retire_months < retired.months) {
    int year = startAge / 12;
    int month = startAge % 12;
    printf("Age %3d month %2d you have $%.2f\n", year, month, initial);
    initial = compound_earned(initial, retired.contribution, retired.rate_of_return);
    startAge++;
    retire_months++;
  }
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;

  retire_info retire;
  retire.months = 384;
  retire.contribution = -4000;
  retire.rate_of_return = 0.01;

  retirement(327, 21345, working, retire);
  return 0;
}
