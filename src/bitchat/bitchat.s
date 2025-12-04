.intel_syntax noprefix

.global _input
.global _printName

.global input

.section .data

prompt: .asciz "You: "
response: .asciz "BitChat: "

.section .bss

input: .skip 0x1000

.section .text

/* prompts input and moves into reserved space 
// returns number of characters read in rax */
_input:

  // sys_write; prompt user input
  mov rax, 0x1
  mov rdi, 0x1
  lea rsi, [rip + prompt]
  mov rdx, 0x5
  syscall

  // sys_read; move input to input; save bytes read to rbx 
  xor eax, eax
  xor edi, edi
  lea rsi, [rip + input]
  mov rdx, 0x1000
  syscall
  mov rbx, rax

  // add null terminator
  add rsi, rax
  mov BYTE PTR [rsi], 0

  // sys_ioctl; flush buffer
  mov rax, 0x10
  mov rsi, 0x540B 
  xor edx, edx
  syscall

  mov rax, rbx
  dec rax
  ret

/* prefixes output from BitChat by saying 'Bitchat: '
// returns characters printed in rax */
_printName:

  // sys_write; prefix output with 'BitChat: '

  mov rax, 0x1
  mov rdi, 0x1
  lea rsi, [rip + response]
  mov rdx, 0x9
  syscall

  ret
