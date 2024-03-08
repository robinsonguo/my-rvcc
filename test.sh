#!/bin/bash

assert() {
  expected="$1"
  input="$2"

  ./rvcc "$input" > tmp.s || exit

  riscv64-linux-gnu-gcc -o tmp -static tmp.s

  qemu-riscv64 -L $RISCV/sysroot tmp

  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 0 0
assert 42 42

echo OK