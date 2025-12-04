as src/bitchat/bitchat.s -o bitchat.o
as src/bitchat/printing.s -o printing.o
gcc -Os -g -Wall -Wextra src/bitchat/bitchat.c src/utils/utils.c bitchat.o printing.o -o bitchat.out -lm
./bitchat.out
