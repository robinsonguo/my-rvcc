#include <stdio.h>
#include <stdlib.h>

// 处理简单加减运算， 合法输入字符为"0-9+-"
int main(int Argc, char **Argv) {
  // 判断传入程序的参数是否为2个，Argv[0]为程序名称，Argv[1]为传入的第一个参数
  if (Argc != 2) {
    // 异常处理，提示参数数量不对。
    // fprintf，格式化文件输出，往文件内写入字符串
    // stderr，异常文件（Linux一切皆文件），用于往屏幕显示异常信息
    // %s，字符串
    fprintf(stderr, "%s: invalid number of arguments\n", Argv[0]);
    // 程序返回值不为0时，表示存在错误
    return 1;
  }

  // 声明一个全局main段，同时也是程序入口段
  printf("  .globl main\n");
  // main段标签
  printf("main:\n");
  // 获取输入字符串
  char* p = Argv[1];

  // li为addi别名指令，加载一个立即数到寄存器中
  // 传入程序的参数为str类型，因此需要转换为需要integer类型
  // strtol(初始值，剩余值，基数)为“ASCII to long int”
  // 处理第一个数字
  // printf("  li a0, %d\n", strtol(p, &p, 10));

  // movq移动第一个参数的值到第二个参数的寄存器中
  printf("  movq $%ld, %%rax\n", strtol(p, &p, 10));
  
  // 处理剩余输入字符串
  while(*p) {
    // 处理加法运算符
    if (*p == '+') {
      ++p;
      // 处理加法运算的第二个运算数
      printf("  leaq %ld(%%rax), %%rax\n", strtol(p, &p, 10));
      continue;
    }

    // 处理乘法运算符
    if (*p == '-') {
      ++p;
      // 处理减法运算的第二个运算数
      printf("  leaq %ld(%%rax), %%rax\n", -1 * strtol(p, &p, 10));
      continue;
    }
  }

  // ret为jalr x0, x1, 0别名指令，用于返回子程序
  printf("  ret\n");

  return 0;
}