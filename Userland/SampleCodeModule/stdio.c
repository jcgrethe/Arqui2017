#include "./types.h"
#include "include/stdio.h"
#include "include/string.h"
#include <stdarg.h>
extern void int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

static char * mal=0x20000000000;


int abs(int a){
	if(a>=0)
		return a;
	return -a;
}


void free(void * x){
	return;
}

void * malloc(int size){
	for(int x=0;x<size;x++)
		mal[x]=0;
	void * ret= mal;
	mal+=size+1;
	return ret;
}



//https://www.tutorialspoint.com/cprogramming/c_variable_arguments.htm y ayuda de augusto
void printf(const char * str,...){
	char num[12];
	va_list arguments;
	va_start ( arguments,str);
	int length=strlen(str);
	int state=0;
	for(int x=0;x<length;x++){
		if(state==0){
			if(str[x]!= '%')
				putchar(str[x]);
			else
				state=1;
		}else{
			switch(str[x]){
				case 'd':
					intostr(va_arg ( arguments, int),num);
					int index=0;
					while(num[index]!=0)
						putchar(num[index++]);
					state=0;
					break;
				case 'c':
					putchar((char)(va_arg(arguments,int)));
					state=0;
					break;
				case 's':
					printf(va_arg(arguments, char*));
					state = 0;
					break;
				default:	
					putchar('%');
					putchar(str[x]);
					state=0;
					break;
			}
		}

	}	
	va_end(arguments);


}


void clearScreen() {
	int80(2, 1, 0, 0, 0, 0);
}

void putchar(const char c) {
	int80(1, 1, &c, 1, 0, 0);
}

char getchar() {
	char a[2];
	int80(3,0,a,2,0,0);
	if(a[0] == 0 ) return EOF;
	return a[0];
}

void backspace() {
	char c='\b';
	int80(1, 0 , &c, 1 ,0, 0);
}

void newLine(){
	char c='\n';
	int80(1, 0 , &c, 1 ,0, 0);
}


void intostr(int num,char * ret){
	int dig=0;
	char aux;
	if(num!=0){
		if(num<0){
			num=-num;
			ret[0]='-';
			dig++;
		}
		while(num!=0){
			ret[dig]=(num%10)+'0';
			num=num/10;
			dig++;
		}
		for(int x=0;x<dig/2;x++){
			aux=ret[x];
			ret[x]=ret[dig-x-1];
			ret[dig-x-1]=aux;
		}
		ret[dig]=0;
	}else{
		ret[0]='0';
	}	
}

void time(char* m,char* h,char* d,char* mo,char* y) {
	int80(4, m, h, d, mo, y);
}

int changeFontColor(char* color) {
	if(strcmp(color, "blue")) {
		int80(5, 1, 0, 0, 0, 0);
	} else if(strcmp(color, "red")) {
		int80(5, 4, 0, 0, 0, 0);
	} else if(strcmp(color, "violet")) {
		int80(5, 5, 0, 0, 0, 0);
	} else if(strcmp(color, "yellow")) {
		int80(5, 0xE, 0, 0, 0, 0);
	} else if(strcmp(color, "white")) {
		int80(5, 0xF, 0, 0, 0, 0);
	} else {
		return 1;
	}
	return 0;
}


int sscanf(char format [90],char str[90], ...){

		va_list args;
		va_start( args, format );

		int* a;
		int mult;
		int n=0;
		char strnum[10];
		char* character;

		while(*format!='\0'){
			if(*format!='%'){
				if((*format) != (*str)){
					return n;
				} else{
					format++;
					str++;
				}
			}else{
				switch(*(++format)){
					case '%':
						if(*str != '%') return n;
						else str++;
						break;
					case 'd':
					case 'i':
						a=va_arg(args, int);
						*a=*str-'0';
						str++;
						n++;
						break;
					case 'c':
						character = va_arg(args, char*);
						*character = *str++;
						n++;
						break;
					case 's':
						character = va_arg(args,char*);
						char temp;
						while( (temp = *str) != '\0'){
							*character = *str;
							character++;
							str++;
						}
						n++;

				}
				++format;
			}
		}
		return n;
	}


int scanf(const char* format,...){
	va_list args;
	va_start( args, format );

	int n=0;

	char* str = readLine();
    char* character;


	while(*format!='\0'){
		if(*format!='%'){
            if((*format) != (*str)){
                return n;
            } else{
                format++;
                str++;
            }
		}else{
			switch(*(++format)){
				case '%':
                    if(*str != '%') return n;
                    else str++;
                    break;
				case 'd':
				case 'i':
                    str = readInt(str, va_arg(args,int));
					n++;
					break;
				case 'c':
                    character = va_arg(args, char*);
                    *character = *str++;
                    n++;
                    break;
				case 's':
                    character = va_arg(args,char*);
                    char temp;
                    while( (temp = *str) != '\0'){
                        *character = *str;
                        character++;
                        str++;
                    }
                    n++;
			}
			++format;
		}
	}

	return n;
}

char* readLine() {
    int bufferIndex = 0;
    char *buff = malloc(80 + 1);

    int c ;

    while ((c = getchar()) != '\n') {
        if(c == '\b'){
            if (bufferIndex != 0) {
                bufferIndex--;
                putchar('\b');
            }
        }
        else if(c != -1){
            if (bufferIndex <= 80) {
                buff[bufferIndex++] = c;
            }
            putchar(c);
        }

    }
    buff[bufferIndex] = '\0';
    return buff;
}

char* readInt(char* string, int* num){
    *num = 0;
	boolean sign=1;

    if(*string == '-'){
		if (isNum(*(string + 1))) {
			sign = -1;
			*num = (*(string + 1) - '0') * sign;
			string++;
			string++;
		} else {
			return string;

		}
	}

	int c;

    while (isNum(c = *string)){
        *num = (*num)*10+(c-'0')*sign;
        string++;
    }
    return string;
}


int isNum(char c){
	return (c >= '0' && c <= '9');
}

