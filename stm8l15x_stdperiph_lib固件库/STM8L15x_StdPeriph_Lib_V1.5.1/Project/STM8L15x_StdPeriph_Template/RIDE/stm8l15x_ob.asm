;This file contains the values to program in the option bytes.
;You can change the values below according to the device datasheet.
;Be careful to respect the complement bytes,
; or the default values of the option bytes will be used.

;See the device datasheet for more information on the meaning of each bit.


cseg at 04800h

db 0AAh ;OPT1
db 000h ;OPT2
db 000h ;OPT3
db 000h ;OPT4
db 000h ;OPT5
db 000h ;OPT6
db 000h ;OPT7
db 000h ;OPT8
db 000h ;OPT9
db 000h ;OPT10
db 001h ;OPT11

end

