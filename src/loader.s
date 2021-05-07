global loader           	 ; making entry point visible to linker
global inb
global init_pic
global dbg_is_kbd_ready
global dbg_kbd_get_scancode
extern _start

;;  setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0	               ; align loaded modules on page boundaries
MEMINFO     equ  1<<1	               ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002	       ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)       ; checksum required

section .text
        align 4

MultiBootHeader:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

	;;  reserve initial kernel stack space
	STACKSIZE equ 0x4000     ; that's 16k.

loader:
	mov esp, stack+STACKSIZE ; set up the stack
	push eax		 ; pass Multiboot magic number
	push ebx		 ; pass Multiboot info structure
	call _start              ; call kernel proper
	cli

hang:
	hlt			 ; halt machine should kernel return
	jmp   hang


; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;        [esp    ] The return address
io_read:
        mov dx, [esp + 4]
        in  al, dx
        ret

print_str:
        mov ecx, 0x00
        mov byte [0xb8000], 0
        mov byte [0xb8002], ':'
.loop:
        mov dl, cl              ; store the count
        sar dl, 1               ; divide the counter by two for debug display
        add dl, 48              ; add 48 to the count to get an int char
        mov byte [0xb8000], dl  ; push the int char to videoram[0]

        lodsb                   ; load a single byte from the address in eax
        cmp al, 0               ; see if the current byte is '\0'
        jz  .done               ; if it is return
        mov byte [0xb8004 + ecx], al ; print the byte
        add ecx, 2                   ; increment by two to skip over the color byte
        jmp .loop                    ; continue
.done:
        ret


dbg_is_kbd_ready:
        in al, 0x64
        test al, 1
        jz .false
.true:
        mov eax, 0x01
        jmp .end
.false:
        mov eax, 0x00
.end:
        ret

dbg_kbd_get_scancode:
        in al, 0x60
        ret

debug:
        mov  ecx, 0xb8000
.loop:
        in al, 0x64
        test al, 1
        jz .loop
.have_key:
        in al, 0x60
        mov [ecx], al
        add ecx, 2
        jmp .loop



init_pic:
        mov bl, 10
        mov si, message
        call print_str

        ;; call debug

        in ax, 0x21
        or ax, (1 << 6)
        out 0x21, ax
        ;; apply a mask that lets us only see the keyboard
        ;; out 0x21, 0xfd
        ret

section .bss
	align 4
stack:
	resb STACKSIZE	; reserve 16k stack on a doubleword boundary

section .data
message:  db "Initializing pic...", 0
