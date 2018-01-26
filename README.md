Note that the programs are structured to have consistent runtime stack. Using gdb (gdb target1; break foo; run test; info frame;), it is possible to extract the return address of any functions.

sploit1

The function 'foo' performs a strcpy from input (argv) to a 96 byte buffer. We provided an input that contained the shellcode in the first 45 bytes. The return address of 'lab_main' was found to be 0x2021fe88, and the address of the buffer was found to be 0x2021fe10. The difference is 120 bytes. Therefore, we used a 125 byte buffer to slot the return address of buf at bytes 120-123 so that it would overwrite the 'lab_main' return address.

sploit2

The function 'foo' performs a byte-by-byte copy of input (argv) into a 256 byte buffer. The number of bytes copied is limited by len, which has a maximum value of 272. This prevents a direct buffer overflow of the return address (284 bytes are required). Fortunately, after performing stack inspection, it was found that the order of variables on the stack is based on the order of initialization (and not based on order of declaration). We overrode the value of len to 283 so that it would allow us to overwrite the value of the return address of 'foo'.
Another issue encountered here was that we could only input 2 argv arguments into 'lab_main'. The input needed to have 2 null-terminators, which required the use of envp pointers to continue where the argv input buffer left off.

sploit3

The function 'foo' calls upon 'bar' to copy over up to 88 byte from the input (argv) into a 64 byte buffer. The difficulty lies in pointer arithmetic. The function 'bar' increments the location of the buffer pointer by strlen(buf) which is of length 4. This means that the input would have to have -4 byte offset in addition to the distance between the address of buf and the return address of 'bar'.

sploit4

This was similar to sploit2. The local variables 'len' and 'i' are on the stack. On the iterations that copy 'i' value, the bytes needed to match what was currently in the value. On the iterations that copy the 'len' value, the bytes needed to be updated so that there was enough iteration to reach the return address of 'foo'.
