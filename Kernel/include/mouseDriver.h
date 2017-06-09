#ifndef MOUSE_DRIVER_H
#define MOUSE_DRIVER_H

void set_up_mouse();
byte mRead();
void mWrite(byte);
void mWait(byte);
void mouseHandler();

#endif