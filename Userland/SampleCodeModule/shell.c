#include "include/stdio.h"
#include "types.h"

void initShell() {

  clearScreen();
  printf("Shell: ");

  char c;

  while(1) {
    if ((c = getc()) != EOF) {
      printf(c);
    }
    //Wait for inputs
  }

}