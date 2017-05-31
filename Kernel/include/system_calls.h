#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

void set_up_system_calls();

void irq80Handler(void);

void interruption_set_handler(int, qword);

#endif