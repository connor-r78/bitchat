gcc -Os -Wall -Werror -Wextra ../src/bitchat/bitchat.c ../src/utils/utils.c dog.c -o dog.out -lm
./dog.out

rm *.out
