echo Enter assembly code file to compile:
read assembly_filename
elf_filename="$(echo $assembly_filename | sed 's/.s//g')";
gcc -masm=intel -nostdlib -static $assembly_filename -o $elf_filename
