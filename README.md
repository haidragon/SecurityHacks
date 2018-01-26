Note that the programs are structured to have consistent runtime stack. Using gdb (gdb target1; break foo; run test; info frame;), it is possible to extract the return address of any functions.

sploit1

The function 'foo' performs a strcpy from input (argv) to a 96 byte buffer. We provided an input that contained the shellcode in the first 45 bytes. The return address of 'lab_main' was found to be 0x2021fe88, and the address of the buffer was found to be 0x2021fe10. The difference is 120 bytes. Therefore, we used a 125 byte buffer to slot the return address of buf at bytes 120-123 so that it would overwrite the 'lab_main' return address.

sploit2

The function 'foo' performs a byte-by-byte copy of input (argv) into a 256 byte buffer. The number of bytes copied is limited by len, which has a maximum value of 272. This prevents a direct buffer overflow of the return address (284 bytes are required). Fortunately, after performing stack inspection, it was found that the order of variables on the stack is based on the order of initialization (and not based on order of declaration). We overrode the value of len to 283 so that it would allow us to overwrite the value of the return address of 'foo'.
