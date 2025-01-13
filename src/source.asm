; Check if you have >= 18 years
IN                      ; 0x00
STA 0x0A                ; 0x01

LDI 18                  ; 0x02
SUB 0x0A                ; 0x03

; if 18 - input > 0
JGZ 0x07                ; 0x04
; if 18 - input == 0
JEZ 0x0A                ; 0x05
; else
JMP 0x0A                ; 0x06

LDI 0                   ; 0x07
OUT                     ; 0x08
JMP 0x0C                ; 0x09

LDI 1                   ; 0x0A
OUT                     ; 0x0B

HLT                     ; 0x0C
