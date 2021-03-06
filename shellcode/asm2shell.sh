echo Enter assembly code file to compile:
read assembly_filename

elf_filename="$(echo $assembly_filename | sed 's/.s//g')";
raw_filename="$(echo $assembly_filename | sed 's/.s/-raw/g')";
gcc -masm=intel -nostdlib -static $assembly_filename -o $elf_filename;
objcopy --dump-section .text=$raw_filename $elf_filename;

# Optional: Display it to the screen
# cat $raw_filename | od -vt x1 | awk '{$1="";print}' | tr -d '\n' | sed 's/ /\\x/g';

# Optional: Send it to another binary application to exploit a vulnerability
# ( cat $raw_filename; cat ) | /path/to/target/binary/file

# Optional: Clean up after yourself
# rm $raw_filename
# rm $elf_filename
echo ""
