as src/bitchat/bitchat.s -o bitchat.o
as src/bitchat/printing.s -o printing.o
gcc -g -Wall -Wextra src/bitchat/bitchat.c bitchat.o printing.o -o bitchat.out -lm
./bitchat.out
