; Simplest .asm program without segment fault (returns something)
; Refer syscall: https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/syscalls/
; to exit - call syscall 60 (in rax register) - passing random number - ex. 255 - (passing as an arg0 param) into rdi register.

global _start
_start:
    mov rax, 60
    mov rdi, 255
    syscall
