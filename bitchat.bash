as src/bitchat/bitchat.s -o bitchat.o
gcc -g -Wall -Wextra src/bitchat/bitchat.c bitchat.o -o bitchat.bin -lm
./bitchat.bin
