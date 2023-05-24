#include "main.h"

int main(void)
{
	init_peripherals();

	run_security_module();

	while (1) {}
}
