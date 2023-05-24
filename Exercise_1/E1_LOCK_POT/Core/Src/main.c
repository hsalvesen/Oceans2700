#include "main.h"

int main(void)
{
	Init_Peripherals();

	run_safecracker();

	while (1) {}
}
