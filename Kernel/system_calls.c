#include "include/types.h"
#include "include/interruptions.h"
#include "include/KeyboardDriver.h"
#include "include/videoDriver.h"
#include "include/getTime.h"

typedef qword (*sys)(qword rsi, qword rdx, qword rcx, qword r8, qword r9);

static sys sysCalls[10]; //Change this number to the total of the system calls

qword sys_clear(qword rsi, qword rdx, qword rcx, qword r8, qword r9) {
    clear(); //Change this function to something we program
    return 0;
}

qword sys_write(qword file, qword buffer, qword size, qword r8, qword r9) {

    char* charbuffer=(char*)buffer;
    while(size--) {
      printChar(*charbuffer++); //Change this function to something we program
    }

  return 1;
}

qword sys_read(qword file, qword buffer, qword size, qword r8, qword r9) {
    readAllBuffer((char*) buffer, (int) size);
    return 1;
}
qword sys_time(qword min, qword hour, qword day, qword month, qword year) {
    char *m = (char *) min;
    char *h = (char *) hour;
    char *d = (char *) day;
    char *mo = (char *) month;
    char *y = (char *) year;
    binaryTime();
    *m = getMin();
    *h = getHour();
    *d = getDay();
    *mo = getMonth();
    *y = getYear();
    return 1;
}


void set_up_system_calls(){
 
  sysCalls[1] = &sys_write;
  sysCalls[2] = &sys_clear;
  sysCalls[3] = &sys_read;
  sysCalls[4] = &sys_time;
 
  interruption_set_handler(0x80, (qword)&irq80Handler); //Softwrae interrupts starts after 0x80
}


void syscallHandler(qword rdi,qword rsi, qword rdx, qword rcx, qword r8, qword r9) {

    if(rdi < 0 || rdi >= 10) { //Change this number to the total of the system calls
        //DO NOTHING
        return;
    }
    sysCalls[rdi](rsi,rdx,rcx,r8,r9);
}