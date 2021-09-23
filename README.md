# lmc-emu
Little Man Computer emulator

#### Available instructions:
* IN - Input from user
* OUT - Output to user
* ADD - Add memory content to accumulator
* SUB - Subtract memory content from accumulator
* LDI - Load immediate number to accumulator
* LDA - Load to accumulator content from memory
* STA - Store content from accumulator to memory
* JMP - Unconditional jump to given address
* JEZ - Jump if accumulator equals to zero
* JGZ - Jump if accumulator greater than zero
* HLT - Halt program

#### Example (A + B program):
```
; A + B
IN
STA 0x0A

IN
ADD 0x0A

OUT
HLT
```
