.intel_syntax noprefix

.global _input
.global input

.section .bss

input: .skip 0x1000

.section .text

/* prompts input and moves into reserved space 
// returns number of characters read in rax */
_input:

  // sys_read; move input to input; save bytes read to rbx 
  xor rax, rax
  xor rdi, rdi
  lea rsi, [rip + input]
  mov rdx, 0x1000
  syscall
  mov rbx, rax

  // add null terminator
  add rsi, rax
  mov BYTE PTR [rsi], 0

  // ioctl; flush buffer
  mov rax, 0x10
  mov rsi, 0x540B
  xor rdx, rdx
  syscall

  mov rax, rbx
  dec rax
  ret
