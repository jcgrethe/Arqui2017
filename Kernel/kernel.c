#include "include/types.h"
#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <interruptions.h>
#include <KeyboardDriver.h>
#include "include/videoDriver.h"
#include "include/mouseDriver.h"
#include "include/system_calls.h"

extern byte text;
extern byte rodata;
extern byte data;
extern byte bss;
extern byte endOfKernelBinary;
extern byte endOfKernel;

static const qword PageSize = 0x1000;
extern unsigned int read();

static void * const shell = (void*)0x400000;
static void * const holaMundo = (void*)0x500000;
static void * const blobsWarModule = (void*)0x600000;


typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, qword bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * getStackBase() {
	return (void*)(
		(qword)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(qword)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary() {
	

	void * moduleAddresses[] = {
		shell,
		holaMundo,
		blobsWarModule,
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	
	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main() {
	
	cli();
	set_up_mouse();	
	set_up_IDT();
	set_up_system_calls();
	sti();

	uint8_t apagar = 0;
	char opcion='0';
	while(1){
		int i = 0;
		clear();
		menu();
		while((opcion = getBuffer()) == EOF || i<1) {
			i++;
		}
		
		switch(opcion) {
			case '1':
				((EntryPoint)shell)();
				break;

			case '2':
				((EntryPoint)holaMundo)();
				break;

			case '3':
				((EntryPoint)blobsWarModule)();
				break;
		}							
	}

	return 0;
}
