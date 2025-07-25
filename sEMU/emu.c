#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

u_int8_t PC = 0;
u_int8_t R[4];
u_int8_t M[16] = {0x80, 0x90, 0xa0, 0xb1, 0x17, 0x29, 0xcd, 0xdb};

void inst_cycle() {
  u_int8_t current;
  u_int8_t high2;

  // fetch
  current = M[PC];
  high2 = (current >> 6) & 0x03;
  // decode
  // && exe
  if (high2 == 0x02) {
    u_int8_t ld_r = (current >> 4) & 0x03; // load register
    u_int8_t low4 = current & 0x0f;
    R[ld_r] = low4;
  } else if (high2 == 0x00) {
    u_int8_t save_r = (current >> 4) & 0x03; // save register
    u_int8_t add_r1 = (current >> 2) & 0x03; // add register1
    u_int8_t add_r2 = current & 0x03;        // add register2
    R[save_r] = R[add_r1] + R[add_r2];
  } else if (high2 == 0x03) {
    u_int8_t jumpto = (current >> 2) & 0x0f; // jumpto addr
    u_int8_t cmp_r = current & 0x03;         // compare register
    if (R[0] != R[cmp_r]) {
      PC = jumpto;
    }
  }
  int i = 0;
  for (i = 0; i <= 3; i++) {
    printf("R[%d] = %d\n", i, R[i]);
  }
  // update PC
  PC++;
  printf("PC = %d\n", PC);
}

int main(int argc, char *argv[]) {
  u_int8_t r0 = atoi(argv[1]);
  M[0] = M[0] ^ r0;
  while (1) {
    inst_cycle();
  }
  return 0;
}
