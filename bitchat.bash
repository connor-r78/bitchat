ARCH=$(uname -m)

if [[ "$ARCH" == x86_64 ]]; then
  as src/bitchat/bitchat.x64.s -o bitchat.o
  as src/bitchat/printing.x64.s -o printing.o
elif [[ "$ARCH" == arm64 ]]; then
  as src/bitchat/bitchat.arm64.s -o bitchat.o
  gcc -c src/bitchat/printing_s.c -o printing.o
else
  exit 1
fi

gcc -Os -Wall -Wextra src/bitchat/bitchat.c src/utils/utils.c bitchat.o printing.o -o bitchat.out -lm
./bitchat.out
