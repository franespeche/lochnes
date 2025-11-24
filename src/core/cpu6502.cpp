#include "core/cpu6502.h"
#include "common/types.h"
#include "core/bus.h"
#include <bitset>
#include <iostream>

Instruction CPU6502::instruction_table[256];

void CPU6502::op_ora_ind_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ora_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_asl_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_php(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ora_imm(uint8_t cycle) { (void)cycle; }
void CPU6502::op_asl_acc(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ora_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_asl_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_bpl(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ora_ind_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ora_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_asl_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_clc(uint8_t cycle) {
  if (cycle == 2)
    clear_flag(C, true);
}
void CPU6502::op_ora_abs_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ora_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_asl_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_jsr(uint8_t cycle) { (void)cycle; }
void CPU6502::op_and_ind_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_bit_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_and_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_rol_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_plp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_and_imm(uint8_t cycle) { (void)cycle; }
void CPU6502::op_rol_acc(uint8_t cycle) { (void)cycle; }
void CPU6502::op_bit_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_and_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_rol_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_bmi(uint8_t cycle) { (void)cycle; }
void CPU6502::op_and_ind_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_and_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_rol_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sec(uint8_t cycle) {
  if (cycle == 2)
    set_flag(C, true);
}
void CPU6502::op_and_abs_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_and_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_rol_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_rti(uint8_t cycle) { (void)cycle; }
void CPU6502::op_eor_ind_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_eor_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_lsr_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_pha(uint8_t cycle) { (void)cycle; }
void CPU6502::op_eor_imm(uint8_t cycle) { (void)cycle; }
void CPU6502::op_lsr_acc(uint8_t cycle) { (void)cycle; }
void CPU6502::op_jmp_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_eor_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_lsr_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_bvc(uint8_t cycle) { (void)cycle; }
void CPU6502::op_eor_ind_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_eor_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_lsr_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cli(uint8_t cycle) {
  if (cycle == 2)
    clear_flag(I, true);
}
void CPU6502::op_eor_abs_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_eor_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_lsr_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_rts(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ror_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_pla(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ror_acc(uint8_t cycle) { (void)cycle; }
void CPU6502::op_jmp_ind(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ror_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_bvs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ror_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sei(uint8_t cycle) {
  if (cycle == 2)
    set_flag(I, true);
}
void CPU6502::op_ror_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sty_zp(uint8_t cycle) {
  if (cycle == 2)
    addr = read(PC++);
  else if (cycle == 3)
    write(addr, Y);
}
void CPU6502::op_stx_zp(uint8_t cycle) {
  if (cycle == 2)
    addr = read(PC++);
  else if (cycle == 3)
    write(addr, X);
}
void CPU6502::op_dey(uint8_t cycle) {
  if (cycle == 2) {
    Y--;
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
  }
}
void CPU6502::op_txa(uint8_t cycle) {
  if (cycle == 2) {
    A = X;
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
  }
}
void CPU6502::op_sty_abs(uint8_t cycle) {
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } else if (cycle == 4)
    write(addr, Y);
}
void CPU6502::op_stx_abs(uint8_t cycle) {
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } else if (cycle == 4)
    write(addr, X);
}
void CPU6502::op_bcc(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sty_zp_x(uint8_t cycle) {
  if (cycle == 2)
    addr = (read(PC++) + X) & 0xFF;
  else if (cycle == 4)
    write(addr, Y);
}
void CPU6502::op_stx_zp_y(uint8_t cycle) {
  if (cycle == 2)
    addr = (read(PC++) + Y) & 0xFF;
  else if (cycle == 4)
    write(addr, X);
}
void CPU6502::op_tya(uint8_t cycle) {
  if (cycle == 2) {
    A = Y;
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
  }
}
void CPU6502::op_ldx_imm(uint8_t cycle) {
  if (cycle == 2) {
    X = read(PC++);
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_ldx_zp(uint8_t cycle) {
  if (cycle == 2)
    addr = read(PC++);
  else if (cycle == 3) {
    X = read(addr);
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_tay(uint8_t cycle) {
  if (cycle == 2) {
    Y = A;
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
  }
}
void CPU6502::op_tax(uint8_t cycle) {
  if (cycle == 2) {
    X = A;
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_ldx_abs(uint8_t cycle) {
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } else if (cycle == 4) {
    X = read(addr);
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_ldx_zp_y(uint8_t cycle) {
  if (cycle == 2)
    addr = (read(PC++) + Y) & 0xFF;
  else if (cycle == 4) {
    X = read(addr);
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_bcs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_ldx_abs_y(uint8_t cycle) {
  static bool page_cross = false;
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += Y;
    page_cross = (addr & 0xFF00) != old_page;
  } else if (cycle == 4 && !page_cross) {
    X = read(addr);
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  } else if (cycle == 5) {
    X = read(addr);
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_clv(uint8_t cycle) {
  if (cycle == 2)
    clear_flag(O, true);
}
void CPU6502::op_cpy_imm(uint8_t cycle) {
  if (cycle == 2) {
    fetched = read(PC++);
    uint8_t result = Y - fetched;
    set_flag(C, Y >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_cmp_ind_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cpy_zp(uint8_t cycle) {
  if (cycle == 2)
    addr = read(PC++);
  else if (cycle == 3) {
    fetched = read(addr);
    uint8_t result = Y - fetched;
    set_flag(C, Y >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_cmp_zp(uint8_t cycle) {
  if (cycle == 2)
    addr = read(PC++);
  else if (cycle == 3) {
    fetched = read(addr);
    uint8_t result = A - fetched;
    set_flag(C, A >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_dec_zp(uint8_t cycle) {
  if (cycle == 2)
    addr = read(PC++);
  else if (cycle == 3)
    fetched = read(addr);
  else if (cycle == 4) {
    fetched--;
    write(addr, fetched);
    set_flag(Z, fetched == 0);
    set_flag(N, fetched & 0x80);
  }
}
void CPU6502::op_cmp_imm(uint8_t cycle) {
  if (cycle == 2) {
    fetched = read(PC++);
    uint8_t result = A - fetched;
    set_flag(C, A >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_dex(uint8_t cycle) {
  if (cycle == 2) {
    X--;
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_cpy_abs(uint8_t cycle) {
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } else if (cycle == 4) {
    fetched = read(addr);
    uint8_t result = Y - fetched;
    set_flag(C, Y >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_cmp_abs(uint8_t cycle) {
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } else if (cycle == 4) {
    fetched = read(addr);
    uint8_t result = A - fetched;
    set_flag(C, A >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_dec_abs(uint8_t cycle) {
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } else if (cycle == 4)
    fetched = read(addr);
  else if (cycle == 5) {
    fetched--;
    write(addr, fetched);
    set_flag(Z, fetched == 0);
    set_flag(N, fetched & 0x80);
  }
}
void CPU6502::op_bne(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cmp_ind_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cmp_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_dec_zp_x(uint8_t cycle) {
  if (cycle == 2)
    addr = (read(PC++) + X) & 0xFF;
  else if (cycle == 4)
    fetched = read(addr);
  else if (cycle == 5) {
    fetched--;
    write(addr, fetched);
    set_flag(Z, fetched == 0);
    set_flag(N, fetched & 0x80);
  }
}
void CPU6502::op_cld(uint8_t cycle) {
  if (cycle == 2)
    clear_flag(D, true);
}
void CPU6502::op_cmp_abs_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cmp_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_dec_abs_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cpx_imm(uint8_t cycle) {
  if (cycle == 2) {
    fetched = read(PC++);
    uint8_t result = X - fetched;
    set_flag(C, X >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_sbc_ind_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cpx_zp(uint8_t cycle) {
  if (cycle == 2)
    addr = read(PC++);
  else if (cycle == 3) {
    fetched = read(addr);
    uint8_t result = X - fetched;
    set_flag(C, X >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_sbc_zp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_inx(uint8_t cycle) {
  if (cycle == 2) {
    X++;
    set_flag(Z, X == 0);
    set_flag(N, X & 0x80);
  }
}
void CPU6502::op_sbc_imm(uint8_t cycle) { (void)cycle; }
void CPU6502::op_nop_imp(uint8_t cycle) { (void)cycle; }
void CPU6502::op_cpx_abs(uint8_t cycle) {
  if (cycle == 2) {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } else if (cycle == 4) {
    fetched = read(addr);
    uint8_t result = X - fetched;
    set_flag(C, X >= fetched);
    set_flag(Z, result == 0);
    set_flag(N, result & 0x80);
  }
}
void CPU6502::op_sbc_abs(uint8_t cycle) { (void)cycle; }
void CPU6502::op_beq(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sbc_ind_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sbc_zp_x(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sed(uint8_t cycle) {
  if (cycle == 2)
    set_flag(D, true);
}
void CPU6502::op_sbc_abs_y(uint8_t cycle) { (void)cycle; }
void CPU6502::op_sbc_abs_x(uint8_t cycle) { (void)cycle; }

void CPU6502::init_instruction_table() {
  // Clear table
  for (int i = 0; i < 256; i++) {
    instruction_table[i].total_cycles = 0;
    instruction_table[i].execute = nullptr;
  }

  // Populate instruction table with all 6502 opcodes
  instruction_table[0x00] = {7, &CPU6502::op_brk};
  instruction_table[0x01] = {6, &CPU6502::op_ora_ind_x};
  instruction_table[0x05] = {3, &CPU6502::op_ora_zp};
  instruction_table[0x06] = {5, &CPU6502::op_asl_zp};
  instruction_table[0x08] = {3, &CPU6502::op_php};
  instruction_table[0x09] = {2, &CPU6502::op_ora_imm};
  instruction_table[0x0A] = {2, &CPU6502::op_asl_acc};
  instruction_table[0x0D] = {4, &CPU6502::op_ora_abs};
  instruction_table[0x0E] = {6, &CPU6502::op_asl_abs};
  instruction_table[0x10] = {2, &CPU6502::op_bpl};
  instruction_table[0x11] = {5, &CPU6502::op_ora_ind_y};
  instruction_table[0x15] = {4, &CPU6502::op_ora_zp_x};
  instruction_table[0x16] = {6, &CPU6502::op_asl_zp_x};
  instruction_table[0x18] = {2, &CPU6502::op_clc};
  instruction_table[0x19] = {4, &CPU6502::op_ora_abs_y};
  instruction_table[0x1D] = {4, &CPU6502::op_ora_abs_x};
  instruction_table[0x1E] = {7, &CPU6502::op_asl_abs_x};
  instruction_table[0x20] = {6, &CPU6502::op_jsr};
  instruction_table[0x21] = {6, &CPU6502::op_and_ind_x};
  instruction_table[0x24] = {3, &CPU6502::op_bit_zp};
  instruction_table[0x25] = {3, &CPU6502::op_and_zp};
  instruction_table[0x26] = {5, &CPU6502::op_rol_zp};
  instruction_table[0x28] = {4, &CPU6502::op_plp};
  instruction_table[0x29] = {2, &CPU6502::op_and_imm};
  instruction_table[0x2A] = {2, &CPU6502::op_rol_acc};
  instruction_table[0x2C] = {4, &CPU6502::op_bit_abs};
  instruction_table[0x2D] = {4, &CPU6502::op_and_abs};
  instruction_table[0x2E] = {6, &CPU6502::op_rol_abs};
  instruction_table[0x30] = {2, &CPU6502::op_bmi};
  instruction_table[0x31] = {5, &CPU6502::op_and_ind_y};
  instruction_table[0x35] = {4, &CPU6502::op_and_zp_x};
  instruction_table[0x36] = {6, &CPU6502::op_rol_zp_x};
  instruction_table[0x38] = {2, &CPU6502::op_sec};
  instruction_table[0x39] = {4, &CPU6502::op_and_abs_y};
  instruction_table[0x3D] = {4, &CPU6502::op_and_abs_x};
  instruction_table[0x3E] = {7, &CPU6502::op_rol_abs_x};
  instruction_table[0x40] = {6, &CPU6502::op_rti};
  instruction_table[0x41] = {6, &CPU6502::op_eor_ind_x};
  instruction_table[0x45] = {3, &CPU6502::op_eor_zp};
  instruction_table[0x46] = {5, &CPU6502::op_lsr_zp};
  instruction_table[0x48] = {3, &CPU6502::op_pha};
  instruction_table[0x49] = {2, &CPU6502::op_eor_imm};
  instruction_table[0x4A] = {2, &CPU6502::op_lsr_acc};
  instruction_table[0x4C] = {3, &CPU6502::op_jmp_abs};
  instruction_table[0x4D] = {4, &CPU6502::op_eor_abs};
  instruction_table[0x4E] = {6, &CPU6502::op_lsr_abs};
  instruction_table[0x50] = {2, &CPU6502::op_bvc};
  instruction_table[0x51] = {5, &CPU6502::op_eor_ind_y};
  instruction_table[0x55] = {4, &CPU6502::op_eor_zp_x};
  instruction_table[0x56] = {6, &CPU6502::op_lsr_zp_x};
  instruction_table[0x58] = {2, &CPU6502::op_cli};
  instruction_table[0x59] = {4, &CPU6502::op_eor_abs_y};
  instruction_table[0x5D] = {4, &CPU6502::op_eor_abs_x};
  instruction_table[0x5E] = {7, &CPU6502::op_lsr_abs_x};
  instruction_table[0x60] = {6, &CPU6502::op_rts};
  instruction_table[0x61] = {6, &CPU6502::op_adc_ind_x};
  instruction_table[0x65] = {3, &CPU6502::op_adc_zp};
  instruction_table[0x66] = {5, &CPU6502::op_ror_zp};
  instruction_table[0x68] = {4, &CPU6502::op_pla};
  instruction_table[0x69] = {2, &CPU6502::op_adc_imm};
  instruction_table[0x6A] = {2, &CPU6502::op_ror_acc};
  instruction_table[0x6C] = {5, &CPU6502::op_jmp_ind};
  instruction_table[0x6D] = {4, &CPU6502::op_adc_abs};
  instruction_table[0x6E] = {6, &CPU6502::op_ror_abs};
  instruction_table[0x70] = {2, &CPU6502::op_bvs};
  instruction_table[0x71] = {5, &CPU6502::op_adc_ind_y};
  instruction_table[0x75] = {4, &CPU6502::op_adc_zp_x};
  instruction_table[0x76] = {6, &CPU6502::op_ror_zp_x};
  instruction_table[0x78] = {2, &CPU6502::op_sei};
  instruction_table[0x79] = {4, &CPU6502::op_adc_abs_y};
  instruction_table[0x7D] = {4, &CPU6502::op_adc_abs_x};
  instruction_table[0x7E] = {7, &CPU6502::op_ror_abs_x};
  instruction_table[0x81] = {6, &CPU6502::op_sta_ind_x};
  instruction_table[0x84] = {3, &CPU6502::op_sty_zp};
  instruction_table[0x85] = {3, &CPU6502::op_sta_zp};
  instruction_table[0x86] = {3, &CPU6502::op_stx_zp};
  instruction_table[0x88] = {2, &CPU6502::op_dey};
  instruction_table[0x8A] = {2, &CPU6502::op_txa};
  instruction_table[0x8C] = {4, &CPU6502::op_sty_abs};
  instruction_table[0x8D] = {4, &CPU6502::op_sta_abs};
  instruction_table[0x8E] = {4, &CPU6502::op_stx_abs};
  instruction_table[0x90] = {2, &CPU6502::op_bcc};
  instruction_table[0x91] = {6, &CPU6502::op_sta_ind_y};
  instruction_table[0x94] = {4, &CPU6502::op_sty_zp_x};
  instruction_table[0x95] = {4, &CPU6502::op_sta_zp_x};
  instruction_table[0x96] = {4, &CPU6502::op_stx_zp_y};
  instruction_table[0x98] = {2, &CPU6502::op_tya};
  instruction_table[0x99] = {5, &CPU6502::op_sta_abs_y};
  instruction_table[0x9D] = {5, &CPU6502::op_sta_abs_x};
  instruction_table[0xA0] = {2, &CPU6502::op_ldy_imm};
  instruction_table[0xA1] = {6, &CPU6502::op_lda_ind_x};
  instruction_table[0xA2] = {2, &CPU6502::op_ldx_imm};
  instruction_table[0xA4] = {3, &CPU6502::op_ldy_zp};
  instruction_table[0xA5] = {3, &CPU6502::op_lda_zp};
  instruction_table[0xA6] = {3, &CPU6502::op_ldx_zp};
  instruction_table[0xA8] = {2, &CPU6502::op_tay};
  instruction_table[0xA9] = {2, &CPU6502::op_lda_imm};
  instruction_table[0xAA] = {2, &CPU6502::op_tax};
  instruction_table[0xAC] = {4, &CPU6502::op_ldy_abs};
  instruction_table[0xAD] = {4, &CPU6502::op_lda_abs};
  instruction_table[0xAE] = {4, &CPU6502::op_ldx_abs};
  instruction_table[0xB0] = {2, &CPU6502::op_bcs};
  instruction_table[0xB1] = {5, &CPU6502::op_lda_ind_y};
  instruction_table[0xB4] = {4, &CPU6502::op_ldy_zp_x};
  instruction_table[0xB5] = {4, &CPU6502::op_lda_zp_x};
  instruction_table[0xB6] = {4, &CPU6502::op_ldx_zp_y};
  instruction_table[0xB8] = {2, &CPU6502::op_clv};
  instruction_table[0xB9] = {4, &CPU6502::op_lda_abs_y};
  // 0xBA is TSX - not implemented yet, using NOP
  instruction_table[0xBA] = {2, &CPU6502::op_nop};
  instruction_table[0xBC] = {4, &CPU6502::op_ldy_abs_x};
  instruction_table[0xBD] = {4, &CPU6502::op_lda_abs_x};
  instruction_table[0xBE] = {4, &CPU6502::op_ldx_abs_y};
  instruction_table[0xC0] = {2, &CPU6502::op_cpy_imm};
  instruction_table[0xC1] = {6, &CPU6502::op_cmp_ind_x};
  instruction_table[0xC4] = {3, &CPU6502::op_cpy_zp};
  instruction_table[0xC5] = {3, &CPU6502::op_cmp_zp};
  instruction_table[0xC6] = {5, &CPU6502::op_dec_zp};
  instruction_table[0xC8] = {2, &CPU6502::op_iny};
  instruction_table[0xC9] = {2, &CPU6502::op_cmp_imm};
  instruction_table[0xCA] = {2, &CPU6502::op_dex};
  instruction_table[0xCC] = {4, &CPU6502::op_cpy_abs};
  instruction_table[0xCD] = {4, &CPU6502::op_cmp_abs};
  instruction_table[0xCE] = {6, &CPU6502::op_dec_abs};
  instruction_table[0xD0] = {2, &CPU6502::op_bne};
  instruction_table[0xD1] = {5, &CPU6502::op_cmp_ind_y};
  instruction_table[0xD5] = {4, &CPU6502::op_cmp_zp_x};
  instruction_table[0xD6] = {6, &CPU6502::op_dec_zp_x};
  instruction_table[0xD8] = {2, &CPU6502::op_cld};
  instruction_table[0xD9] = {4, &CPU6502::op_cmp_abs_y};
  instruction_table[0xDD] = {4, &CPU6502::op_cmp_abs_x};
  instruction_table[0xDE] = {7, &CPU6502::op_dec_abs_x};
  instruction_table[0xE0] = {2, &CPU6502::op_cpx_imm};
  instruction_table[0xE1] = {6, &CPU6502::op_sbc_ind_x};
  instruction_table[0xE4] = {3, &CPU6502::op_cpx_zp};
  instruction_table[0xE5] = {2, &CPU6502::op_sbc_zp};
  instruction_table[0xE6] = {5, &CPU6502::op_inc_zp};
  instruction_table[0xE8] = {2, &CPU6502::op_inx};
  instruction_table[0xE9] = {2, &CPU6502::op_sbc_imm};
  instruction_table[0xEA] = {2, &CPU6502::op_nop};
  instruction_table[0xEC] = {4, &CPU6502::op_cpx_abs};
  instruction_table[0xED] = {4, &CPU6502::op_sbc_abs};
  instruction_table[0xEE] = {6, &CPU6502::op_inc_abs};
  instruction_table[0xF0] = {2, &CPU6502::op_beq};
  instruction_table[0xF1] = {5, &CPU6502::op_sbc_ind_y};
  instruction_table[0xF5] = {4, &CPU6502::op_sbc_zp_x};
  instruction_table[0xF6] = {6, &CPU6502::op_inc_zp_x};
  instruction_table[0xF8] = {2, &CPU6502::op_sed};
  instruction_table[0xF9] = {4, &CPU6502::op_sbc_abs_y};
  instruction_table[0xFD] = {4, &CPU6502::op_sbc_abs_x};
  instruction_table[0xFE] = {7, &CPU6502::op_inc_abs_x};
}

CPU6502::CPU6502(Bus *b) : bus(b) { init_instruction_table(); }

void CPU6502::tick() {
  std::cout << "--------------------------------------------------------\n";
  std::cout << std::hex << std::uppercase << "PC: " << static_cast<int>(PC)
            << "Val: " << static_cast<int>(read(PC)) << "\n";

  if (current_cycle == 0) {
    std::cout << "\nNEW INSTRUCTION\n";
    opcode = read(PC++);
    Instruction &inst = instruction_table[opcode];
    total_cycles = inst.total_cycles;
    current_cycle = 1;
  } else {
    ++current_cycle;
  }

  Instruction &inst = instruction_table[opcode];

  if (total_cycles == 0) {
    current_cycle = 0;
    return;
  }

  std::cout << " | "
            << "A: $" << static_cast<int>(A) << " | "
            << "X: $" << static_cast<int>(X) << " | "
            << "Y: $" << static_cast<int>(Y) << " | "
            << "SP: $" << static_cast<int>(SP) << " | "
            << "P: $" << static_cast<int>(P);

  std::cout << "\nOpcode: $" << std::hex << std::uppercase
            << static_cast<int>(opcode) << " | "
            << "Cycle: " << static_cast<int>(current_cycle) << " / "
            << static_cast<int>(total_cycles) << "\n";

  if (inst.execute != nullptr)
    (this->*inst.execute)(current_cycle);

  if (current_cycle == total_cycles) {
    current_cycle = 0;
  }
}

void CPU6502::reset() {
  SP = 0xFD;
  P = I;

  uint8_t lo = read(RESET_VECTOR_LO);
  uint8_t hi = read(RESET_VECTOR_HI);
  PC = static_cast<uint16_t>(hi) << 8 | lo;
}

void CPU6502::set_flag(uint8_t f, bool cond) {
  if (cond) {
    P |= f;
  }
}

void CPU6502::clear_flag(uint8_t f, bool cond) {
  if (cond) {
    P &= ~f;
  }
}

bool CPU6502::has_flag(uint8_t f) { return (P & f) != 0; }

uint8_t CPU6502::read(uint16_t address) { return bus->read(address); }

void CPU6502::write(uint16_t address, uint8_t value) {
  bus->write(address, value);
}

// Addressing mode helpers are inlined in each instruction

// Instructions
void CPU6502::op_nop(uint8_t cycle) { (void)cycle; }

void CPU6502::op_lda_imm(uint8_t cycle) {
  switch (cycle) {
  case 2:
    A = read(PC++);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_lda_zp(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = read(PC++);
    break;
  case 3:
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_lda_zp_x(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = (read(PC++) + X) & 0xFF;
    break;
  case 3:
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_lda_abs(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_lda_abs_x(uint8_t cycle) {
  static bool page_cross = false;
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += X;
    page_cross = (addr & 0xFF00) != old_page;
  } break;
  case 3:
    break;
  case 4:
    if (page_cross)
      break;
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  case 5:
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_lda_abs_y(uint8_t cycle) {
  static bool page_cross = false;
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += Y;
    page_cross = (addr & 0xFF00) != old_page;
  } break;
  case 3:
    break;
  case 4:
    if (page_cross)
      break;
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  case 5:
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_lda_ind_x(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t zp = read(PC++);
    uint8_t eff_zp = (zp + X) & 0xFF;
    uint8_t lo = read(eff_zp);
    uint8_t hi = read((eff_zp + 1) & 0xFF);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_lda_ind_y(uint8_t cycle) {
  static bool page_cross = false;
  switch (cycle) {
  case 2: {
    uint8_t zp = read(PC++);
    uint8_t lo = read(zp);
    uint8_t hi = read((zp + 1) & 0xFF);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += Y;
    page_cross = (addr & 0xFF00) != old_page;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    if (page_cross)
      break;
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  case 6:
    A = read(addr);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_sta_zp(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = read(PC++);
    break;
  case 3:
    write(addr, A);
    break;
  default:
    break;
  }
}

void CPU6502::op_sta_zp_x(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = (read(PC++) + X) & 0xFF;
    break;
  case 3:
    write(addr, A);
    break;
  default:
    break;
  }
}

void CPU6502::op_sta_abs(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    write(addr, A);
    break;
  default:
    break;
  }
}

void CPU6502::op_sta_abs_x(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    addr += X;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    write(addr, A);
    break;
  default:
    break;
  }
}

void CPU6502::op_sta_abs_y(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    addr += Y;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    write(addr, A);
    break;
  default:
    break;
  }
}

void CPU6502::op_sta_ind_x(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t zp = read(PC++);
    uint8_t eff_zp = (zp + X) & 0xFF;
    uint8_t lo = read(eff_zp);
    uint8_t hi = read((eff_zp + 1) & 0xFF);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    write(addr, A);
    break;
  default:
    break;
  }
}

void CPU6502::op_sta_ind_y(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t zp = read(PC++);
    uint8_t lo = read(zp);
    uint8_t hi = read((zp + 1) & 0xFF);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    addr += Y;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    write(addr, A);
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_imm(uint8_t cycle) {
  switch (cycle) {
  case 2:
    fetched = read(PC++);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_zp(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = read(PC++);
    break;
  case 3:
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_zp_x(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = (read(PC++) + X) & 0xFF;
    break;
  case 3:
    break;
  case 4:
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_abs(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_abs_x(uint8_t cycle) {
  static bool page_cross = false;
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += X;
    page_cross = (addr & 0xFF00) != old_page;
  } break;
  case 3:
    break;
  case 4:
    if (page_cross)
      break;
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  case 5:
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_abs_y(uint8_t cycle) {
  static bool page_cross = false;
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += Y;
    page_cross = (addr & 0xFF00) != old_page;
  } break;
  case 3:
    break;
  case 4:
    if (page_cross)
      break;
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  case 5:
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_ind_x(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t zp = read(PC++);
    uint8_t eff_zp = (zp + X) & 0xFF;
    uint8_t lo = read(eff_zp);
    uint8_t hi = read((eff_zp + 1) & 0xFF);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_adc_ind_y(uint8_t cycle) {
  static bool page_cross = false;
  switch (cycle) {
  case 2: {
    uint8_t zp = read(PC++);
    uint8_t lo = read(zp);
    uint8_t hi = read((zp + 1) & 0xFF);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += Y;
    page_cross = (addr & 0xFF00) != old_page;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    if (page_cross)
      break;
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  case 6:
    fetched = read(addr);
    {
      uint16_t result = static_cast<uint16_t>(A) +
                        static_cast<uint16_t>(fetched) + (has_flag(C) ? 1 : 0);
      set_flag(C, result > 0xFF);
      set_flag(Z, (result & 0xFF) == 0);
      set_flag(N, result & 0x80);
      set_flag(O, ((A ^ result) & (fetched ^ result) & 0x80) != 0);
      A = result & 0xFF;
    }
    break;
  default:
    break;
  }
}

void CPU6502::op_inc_zp(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = read(PC++);
    break;
  case 3:
    fetched = read(addr);
    break;
  case 4:
    fetched++;
    write(addr, fetched);
    set_flag(Z, fetched == 0);
    set_flag(N, fetched & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_inc_zp_x(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = (read(PC++) + X) & 0xFF;
    break;
  case 3:
    break;
  case 4:
    fetched = read(addr);
    break;
  case 5:
    fetched++;
    write(addr, fetched);
    set_flag(Z, fetched == 0);
    set_flag(N, fetched & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_inc_abs(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    fetched = read(addr);
    break;
  case 5:
    fetched++;
    write(addr, fetched);
    set_flag(Z, fetched == 0);
    set_flag(N, fetched & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_inc_abs_x(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    addr += X;
  } break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    fetched = read(addr);
    break;
  case 6:
    fetched++;
    write(addr, fetched);
    set_flag(Z, fetched == 0);
    set_flag(N, fetched & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_iny(uint8_t cycle) {
  switch (cycle) {
  case 2:
    Y++;
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_ldy_imm(uint8_t cycle) {
  switch (cycle) {
  case 2:
    Y = read(PC++);
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_ldy_zp(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = read(PC++);
    break;
  case 3:
    Y = read(addr);
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_ldy_zp_x(uint8_t cycle) {
  switch (cycle) {
  case 2:
    addr = (read(PC++) + X) & 0xFF;
    break;
  case 3:
    break;
  case 4:
    Y = read(addr);
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_ldy_abs(uint8_t cycle) {
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
  } break;
  case 3:
    break;
  case 4:
    Y = read(addr);
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_ldy_abs_x(uint8_t cycle) {
  static bool page_cross = false;
  switch (cycle) {
  case 2: {
    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (static_cast<uint16_t>(hi) << 8) | lo;
    uint16_t old_page = addr & 0xFF00;
    addr += X;
    page_cross = (addr & 0xFF00) != old_page;
  } break;
  case 3:
    break;
  case 4:
    if (page_cross)
      break;
    Y = read(addr);
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
    break;
  case 5:
    Y = read(addr);
    set_flag(Z, Y == 0);
    set_flag(N, Y & 0x80);
    break;
  default:
    break;
  }
}

void CPU6502::op_brk(uint8_t cycle) {
  switch (cycle) {
  case 2:
    PC++;
    break;
  case 3:
    write(0x0100 + SP, (PC >> 8) & 0xFF);
    SP--;
    break;
  case 4:
    write(0x0100 + SP, PC & 0xFF);
    SP--;
    break;
  case 5:
    write(0x0100 + SP, P | B);
    SP--;
    break;
  case 6: {
    uint8_t lo = read(0xFFFE);
    uint8_t hi = read(0xFFFF);
    PC = (static_cast<uint16_t>(hi) << 8) | lo;
  }
    set_flag(I, true);
    break;
  default:
    break;
  }
}
