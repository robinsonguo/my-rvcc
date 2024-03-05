#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "%s: invalid number of arguments\n", argv[0]);
  }

  printf("  .global main\n");
  printf("main:\n");
  printf("  li a0 %d\n", argv[2]);
  printf("  ret\n");

  return 0;
}