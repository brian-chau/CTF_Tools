echo "Binary name: "
read bin_name
gdb ./$bin_name -x intel_disassembly_flavor.gdb
