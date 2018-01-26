Note that the programs are structured to have consistent runtime stack. Using gdb (gdb target1; break foo; run test; info frame;), it is possible to extract the return address of any functions.

sploit1

The function 'foo' performs a strcpy from input (argv) to a 96 byte buffer. We provided an input that contained the shellcode in the first 45 bytes. The return address of 'lab_main' was found to be 0x2021fe88, and the address of the buffer was found to be 0x2021fe10. The difference is 120 bytes. Therefore, we used a 125 byte buffer to slot the return address of buf at bytes 120-123 so that it would overwrite the 'lab_main' return address.
