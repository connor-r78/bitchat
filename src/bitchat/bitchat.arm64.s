.global input
.global _input
.global _printName

.align 2

.extern _tcflush

/* prompts input and moves into reserved space
// returns number of characters read in x0 */
_input:

  // sys_write; prompt user input
  mov x0, 0x1
  adrp x1, prompt@PAGE
  add x1, x1, prompt@PAGEOFF
  mov x2, 0x5
  mov x16, 0x4
  svc 0x80

  // sys_read; move input to input; save bytes read to x3
  mov x0, 0x0
  adrp x1, input@PAGE
  add x1, x1, input@PAGEOFF
  mov x2, 0x1000
  mov x16, 0x3
  svc 0x80
  mov x3, x0 

  // add null terminator
  add x1, x1, x0
  strb wzr, [x1]

  // tcflush
  mov x0, 0x0
  mov x1, 0x0
  bl _tcflush

  mov x0, x3
  sub x0, x0, 0x1
  ret 

_printName:

  // sys_write; prefix output with 'BitChat: '
  mov x0, 0x1
  adrp x1, response@PAGE
  add x1, x1, response@PAGEOFF
  mov x2, 0x9
  mov x16, 0x4
  svc 0x80 

.data

input: .space 0x1000

prompt: .ascii "You: "
response: .ascii "BitChat: "
