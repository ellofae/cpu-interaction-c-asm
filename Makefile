x86_build:
	nasm -f elf32 src/asm86/cpuid_call_x86.asm
	nasm -f elf32 src/asm86/cpuid_supported_x86.asm
	nasm -f elf32 src/asm86/segment_registers_x86.asm
	gcc -m32 src/*.c src/asm86/*.o -o main

x86_64_build:
	nasm -f elf64 src/asm86_64/cpuid_call_x86_64.asm
	nasm -f elf64 src/asm86_64/cpuid_supported_x86_64.asm
	nasm -f elf64 src/asm86_64/segment_registers_x86_64.asm
	gcc -m64 src/*.c src/asm86_64/*.o -o main 

clear:
	rm src/asm*/*.o