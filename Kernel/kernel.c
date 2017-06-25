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
static void * const blobsWar = (void*)0x600000;


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
		blobsWar,
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

	/*
	while(1) {
		int k = 0;
		while(k < 1000*1000*20) {
			k++;
		}
		
	}
	*/

	/* Execute UserLand, sampleCodeModule */
	//printStringHex(((EntryPoint)sampleCodeModuleAddress)());

	uint8_t apagar = 0;
	char opcion[20];

	clear();
	while(1){

		//printString("Elegir la opcion deseada:      1-Shell      2-Blobs War      0-Apagar");

		int i = 0;
		while((opcion[i] = getBuffer()) != EOF && opcion[i] != '\n') {
			i++;
		}

		if(opcion[0] == '1')
			((EntryPoint)shell)();
		else {
			if(opcion[0] == '2')
				((EntryPoint)holaMundo)();
			else{
				if(opcion[0] == '0')
					apagar = 1;
				else
					printString("Opcion incorrecta");
			}
		}
	}

	return 0;
}
