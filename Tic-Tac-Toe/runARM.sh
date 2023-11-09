# Assemble ARM boot.s file
arm-linux-gnueabi-as boot.s -o boot.o

# Compile ARM kernel.c file
arm-linux-gnueabi-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

arm-linux-gnueabi-gcc -c utils.c -o utils.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

arm-linux-gnueabi-gcc -c box.c -o box.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

arm-linux-gnueabi-gcc -c tic_tac_toe.c -o tic_tac_toe.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# Link the object files for ARM architecture
arm-linux-gnueabi-ld -T linker.ld boot.o kernel.o utils.o box.o tic_tac_toe.o -o TicTacToe.elf -z noexecstack

# Check TicTacToe.elf file here if required for the specific ARM format

# Convert ELF to ARM binary
arm-linux-gnueabi-objcopy -O binary TicTacToe.elf TicTacToe.bin

# Create an ARM bootable image
mkdir -p isodir/boot/grub
cp TicTacToe.bin isodir/boot/TicTacToe.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o TicTacToe.iso isodir

# Run it in QEMU for ARM (adjust the command according to your system and architecture)
# qemu-system-arm -M versatilepb -m 128M -nographic -no-reboot -serial /dev/null -monitor telnet:127.0.0.1:1235,server -kernel TicTacToe.bin
qemu-system-arm -M versatilepb -m 256M -nographic -no-reboot -serial /dev/null -kernel TicTacToe.bin
