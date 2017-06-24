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

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

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
		sampleCodeModuleAddress,
		sampleDataModuleAddress
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

	((EntryPoint)sampleCodeModuleAddress)();

	return 0;
}
