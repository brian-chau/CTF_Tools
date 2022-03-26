# How to use:

* build.sh:

Generates the binary file itself from the assembly code. 

I included an assembly file from [my other repository containing assembly code](https://github.com/brian-chau/c_asm_sendfile_fcntl)


* asm2shell.sh

Generates the byte string that can be piped into another binary application to make it do something. 

I use this for learning CTF.


* str2LEhex.sh

Converts a string to a little-endian hex string.

Good for generating assembly with a string in it.

Usage: ./str2LEhex.sh <string>
