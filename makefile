CFLAGS=-g -std=c11 -pedantic -Wall -Werror -Wextra
queue: PriorityQueue.o
run:  
  ./queue
clean:
  rm -rf PriorityQueue.o queue
