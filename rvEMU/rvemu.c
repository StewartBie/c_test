#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define GETBITS(v, move, mask) ((v) >> (move) & (mask))

u_int32_t PC = 0;
u_int32_t R[32] = {0};
// u_int8_t *M = NULL;
u_int8_t M[4 * 1024 * 1024] = {0};

// addi

void addi(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x13);
  assert(GETBITS(INS, 12, 0x7) == 0x0);
  u_int8_t rd;
  u_int8_t rs1;
  u_int32_t imm;

  rd = GETBITS(INS, 7, 0x1F);
  rs1 = GETBITS(INS, 15, 0x1F);
  imm = GETBITS(INS, 20, 0xFFF);
  if (GETBITS(imm, 11, 1) == 1) {
    imm |= 0xFFFFF000;
  }
  R[rd] = R[rs1] + imm;
  R[0] = 0;
}

void add(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x33);
  assert(GETBITS(INS, 12, 0x7) == 0x0);
  assert(GETBITS(INS, 25, 0x7F) == 0x0);
  u_int8_t rd;
  u_int8_t rs1;
  u_int8_t rs2;

  rd = GETBITS(INS, 7, 0x1F);
  rs1 = GETBITS(INS, 15, 0x1F);
  rs2 = GETBITS(INS, 20, 0x1F);
  R[rd] = R[rs1] + R[rs2];
  R[0] = 0;
}

// U type
void lui(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x37); // opcode
  u_int8_t rd;
  u_int32_t imm;

  rd = GETBITS(INS, 7, 0x1F);
  imm = GETBITS(INS, 12, 0xFFFFF) << 12;
  R[rd] = imm;
  R[0] = 0;
}

// I type
void lw(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x3);
  assert(GETBITS(INS, 12, 0x7) == 0x2);
  u_int8_t rd;
  u_int8_t rs1;
  u_int32_t offset;
  u_int32_t addr;

  rd = GETBITS(INS, 7, 0x1F);
  rs1 = GETBITS(INS, 15, 0x1F);
  offset = GETBITS(INS, 20, 0xFFF);
  if (GETBITS(offset, 11, 1) == 1) {
    offset |= 0xFFFFF000;
  }
  addr = R[rs1] + offset;
  R[rd] = *(u_int32_t *)(M + addr);
  R[0] = 0;
}

// I type
void lbu(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x3);
  assert(GETBITS(INS, 12, 0x7) == 0x4);
  u_int8_t rd;
  u_int8_t rs1;
  u_int32_t offset;
  u_int32_t addr;

  rd = GETBITS(INS, 7, 0x1F);
  rs1 = GETBITS(INS, 15, 0x1F);
  offset = GETBITS(INS, 20, 0xFFF);
  if (GETBITS(offset, 11, 1) == 1) {
    offset |= 0xFFFFF000;
  }
  addr = R[rs1] + offset;
  R[rd] = *(M + addr);
  R[0] = 0;
}
// S type
void sw(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x23);
  assert(GETBITS(INS, 12, 0x7) == 0x2);
  u_int32_t offset;
  u_int8_t rs1;
  u_int8_t rs2;
  u_int32_t highset; // offset high 7 bits
	u_int32_t addr;

  offset = GETBITS(INS, 7, 0x1F); // low 5 bits
  rs1 = GETBITS(INS, 15, 0x1F);
  rs2 = GETBITS(INS, 20, 0x1F);
  highset = GETBITS(INS, 20, 0xFE0); // mask 1111_1110_0000
  offset |= highset;
  if (GETBITS(offset, 11, 1) == 1) {
    offset |= 0xFFFFF000;
  }
  addr = R[rs1] + offset;
  *(u_int32_t *)(M + addr ) = R[rs2];
  R[0] = 0;
}

// S type
void sb(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x23);
  assert(GETBITS(INS, 12, 0x7) == 0x0);
  u_int32_t offset;
  u_int8_t rs1;
  u_int8_t rs2;
  u_int32_t highset; // offset high 7 bits
	u_int32_t addr;

  offset = GETBITS(INS, 7, 0x1F); // low 5 bits
  rs1 = GETBITS(INS, 15, 0x1F);
  rs2 = GETBITS(INS, 20, 0x1F);
  highset = GETBITS(INS, 20, 0xFE0); // mask 1111_1110_0000
  offset |= highset;
  if (GETBITS(offset, 11, 1) == 1) {
    offset |= 0xFFFFF000;
  }
  addr = R[rs1] + offset;
  *(M +  addr) = (R[rs2] & 0xFF);
  R[0] = 0;
}
// I type
void jalr(u_int32_t INS) {
  assert((GETBITS(INS, 0, 0x7F)) == 0x67);
  assert(GETBITS(INS, 12, 0x7) == 0x0);
  u_int8_t rd;
  u_int8_t rs1;
  u_int32_t offset;
  u_int32_t t; // temp PC

  rd = GETBITS(INS, 7, 0x1F);
  rs1 = GETBITS(INS, 15, 0x1F);
  offset = GETBITS(INS, 20, 0xFFF);
  if (GETBITS(offset, 11, 1) == 1) {
    offset |= 0xFFFFF000;
  }
  t = PC + 4;
  PC = (R[rs1] + offset) & ~1; // lowest bit turn 0
  R[rd] = t;
  R[0] = 0;
}

int main(int argc, char *argv[]) {

  printf("EMU Start:\n");
  const char *filename = "./pro/sum.bin";
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Failed open file");
    return 1;
  }
  fseek(file, 0, SEEK_END);
  size_t filesize = ftell(file);
  rewind(file);
  // M = calloc(1, filesize);
  assert(M != NULL);
  size_t read = fread(M, 1, filesize, file);
  if (read != filesize) {
    perror("File to read completely");
    return 1;
  }

  static int inst_cnt = 0;
  while (1) {
    u_int32_t inst = *(u_int32_t *)(M + PC);
    u_int8_t opcode = GETBITS(inst, 0, 0x7F);
    u_int8_t func3 = GETBITS(inst, 12, 0x7);
    printf("PC:\t0x%8x; \n instruct: 0x%8x\n", PC, inst);
    // printf("inst:\t0b%032b\n", inst);
    // printf("opcode:\t0b%07b\n", opcode);
    // printf("func3:\t0b%03b\n", func3);

    switch (opcode) {
    case 0x33: // R type
      add(inst);
      break;
    case 0x13: // I type
      addi(inst);
      break;
    case 0x37:
      lui(inst);
      break;
    case 0x03: // U type
      if (func3 == 0x2)
        lw(inst);
      else if (func3 == 0x4)
        lbu(inst);

      break;
    case 0x23: // S type
      if (func3 == 0x2) {
        sw(inst);
      }
      if (func3 == 0x0) {
        sb(inst);
      }
      break;
    case 0x67:
      jalr(inst);
      break;
    default:
      printf("Unexpected opcode:0x%x\n", opcode);
      exit(1);
      break;
    }
    if (opcode != 0x67) {
      PC += 4;
    }
		if (R[10] == 0) {
			return 0;
		}
  }
  return 0;
}
