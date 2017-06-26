#include "include/timeAndDate.h"
#include "include/stdio.h"

void printTimeAndDate() {
  char min, hour, day, month, year;

  time(&min, &hour, &day, &month, &year);

  char auxMin[3];
  auxMin[2] = 0;
  if (min < 10) {
    auxMin[0] = '0';
    auxMin[1] = min + '0';
  } else {
    auxMin[1] = min%10 + '0';
    auxMin[0] = min/10 + '0';
  }

  char auxHour[3];
  auxHour[2] = 0;
  if (hour < 10) {
    auxHour[0] = '0';
    auxHour[1] = hour + '0';
  } else {
    auxHour[1] = hour%10 + '0';
    auxHour[0] = hour/10 + '0';
  }


  printf("%s:%s - %d/%d/%d", auxHour, auxMin, day, month, year);
  newLine();
}