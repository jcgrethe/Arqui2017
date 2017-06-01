#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <interruptions.h>
#include <KeyboardDriver.h>
#include "include/videoDriver.h"
#include "include/types.h"
#include "include/system_calls.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;
extern unsigned int readk();

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * getStackBase() {
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary() {
	char buffer[10];

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	
	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main() {	
	set_up_IDT();
	set_up_system_calls();

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
