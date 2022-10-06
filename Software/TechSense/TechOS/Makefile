default:
	arm-none-eabi-as -o ./Objects/start.o ./Kernel/start.s -g
	arm-none-eabi-gcc -c -o ./Objects/main.o ./Kernel/main.c -I ./libs
	arm-none-eabi-gcc -T linker.ld -o techOS.elf ./Objects/start.o ./Objects/main.o -ffreestanding -O2 -nostdlib -lgcc
	arm-none-eabi-objcopy techOS.elf -O binary techOS.img