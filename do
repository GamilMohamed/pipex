clear
make
make clean
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./pipex /dev/stdin "cat" "cat" "ls" /dev/stdout
bat in out