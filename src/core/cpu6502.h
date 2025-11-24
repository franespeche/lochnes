#pragma once

#include "common/types.h"
#include <cstdint>

struct Bus;

struct CPU6502;

struct Instruction {
  uint8_t total_cycles;
  void (CPU6502::*execute)(uint8_t cycle);
};

struct CPU6502 : IClockConsumer {
  Bus *bus = nullptr;

  uint8_t A = 0x00;
  uint8_t X = 0x00;
  uint8_t Y = 0x00;
  uint8_t SP = 0x00;    // Stack Pointer ($0100 to $01FF)
  uint8_t P = 0x00;     // Processor Status
  uint16_t PC = 0x0000; // Program Counter

  // Current instruction
  uint8_t opcode = 0;
  uint8_t current_cycle = 0; // Current cycle for the current instruction
  uint8_t total_cycles = 0;  // Total cycles for the current instruction
  uint16_t addr = 0;         // Address for the current instruction
  uint8_t fetched = 0;       // Fetched data for the current instruction

  CPU6502(Bus *b);
  void tick() override;
  void reset();

  // Flags methods
  void set_flag(uint8_t f, bool cond);
  void clear_flag(uint8_t f, bool cond);
  bool has_flag(uint8_t f);

  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t value);

  // Instructions
  static Instruction instruction_table[256];
  void init_instruction_table();

  void op_nop(uint8_t cycle);

  void op_brk(uint8_t);
  void op_ora_ind_x(uint8_t);
  void op_ora_zp(uint8_t);
  void op_asl_zp(uint8_t);
  void op_php(uint8_t);
  void op_ora_imm(uint8_t);
  void op_asl_acc(uint8_t);
  void op_ora_abs(uint8_t);
  void op_asl_abs(uint8_t);

  void op_bpl(uint8_t);
  void op_ora_ind_y(uint8_t);
  void op_ora_zp_x(uint8_t);
  void op_asl_zp_x(uint8_t);
  void op_clc(uint8_t);
  void op_ora_abs_y(uint8_t);
  void op_ora_abs_x(uint8_t);
  void op_asl_abs_x(uint8_t);

  void op_jsr(uint8_t);
  void op_and_ind_x(uint8_t);
  void op_bit_zp(uint8_t);
  void op_and_zp(uint8_t);
  void op_rol_zp(uint8_t);
  void op_plp(uint8_t);
  void op_and_imm(uint8_t);
  void op_rol_acc(uint8_t);
  void op_bit_abs(uint8_t);
  void op_and_abs(uint8_t);
  void op_rol_abs(uint8_t);

  void op_bmi(uint8_t);
  void op_and_ind_y(uint8_t);
  void op_and_zp_x(uint8_t);
  void op_rol_zp_x(uint8_t);
  void op_sec(uint8_t);
  void op_and_abs_y(uint8_t);
  void op_and_abs_x(uint8_t);
  void op_rol_abs_x(uint8_t);

  void op_rti(uint8_t);
  void op_eor_ind_x(uint8_t);
  void op_eor_zp(uint8_t);
  void op_lsr_zp(uint8_t);
  void op_pha(uint8_t);
  void op_eor_imm(uint8_t);
  void op_lsr_acc(uint8_t);
  void op_jmp_abs(uint8_t);
  void op_eor_abs(uint8_t);
  void op_lsr_abs(uint8_t);

  void op_bvc(uint8_t);
  void op_eor_ind_y(uint8_t);
  void op_eor_zp_x(uint8_t);
  void op_lsr_zp_x(uint8_t);
  void op_cli(uint8_t);
  void op_eor_abs_y(uint8_t);
  void op_eor_abs_x(uint8_t);
  void op_lsr_abs_x(uint8_t);

  void op_rts(uint8_t);
  void op_adc_ind_x(uint8_t);
  void op_adc_zp(uint8_t);
  void op_ror_zp(uint8_t);
  void op_pla(uint8_t);
  void op_adc_imm(uint8_t);
  void op_ror_acc(uint8_t);
  void op_jmp_ind(uint8_t);
  void op_adc_abs(uint8_t);
  void op_ror_abs(uint8_t);

  void op_bvs(uint8_t);
  void op_adc_ind_y(uint8_t);
  void op_adc_zp_x(uint8_t);
  void op_ror_zp_x(uint8_t);
  void op_sei(uint8_t);
  void op_adc_abs_y(uint8_t);
  void op_adc_abs_x(uint8_t);
  void op_ror_abs_x(uint8_t);

  void op_sta_ind_x(uint8_t);
  void op_sty_zp(uint8_t);
  void op_sta_zp(uint8_t);
  void op_stx_zp(uint8_t);
  void op_dey(uint8_t);
  void op_txa(uint8_t);
  void op_sty_abs(uint8_t);
  void op_sta_abs(uint8_t);
  void op_stx_abs(uint8_t);

  void op_bcc(uint8_t);
  void op_sta_ind_y(uint8_t);
  void op_sty_zp_x(uint8_t);
  void op_sta_zp_x(uint8_t);
  void op_stx_zp_y(uint8_t);
  void op_tya(uint8_t);
  void op_sta_abs_y(uint8_t);
  void op_sta_abs_x(uint8_t);

  void op_lda_imm(uint8_t cycle);
  void op_ldy_imm(uint8_t);
  void op_lda_ind_x(uint8_t);
  void op_ldx_imm(uint8_t);
  void op_ldy_zp(uint8_t);
  void op_lda_zp(uint8_t);
  void op_ldx_zp(uint8_t);
  void op_tay(uint8_t);
  void op_tax(uint8_t);
  void op_ldy_abs(uint8_t);
  void op_lda_abs(uint8_t);
  void op_ldx_abs(uint8_t);

  void op_bcs(uint8_t);
  void op_lda_ind_y(uint8_t);
  void op_ldy_zp_x(uint8_t);
  void op_lda_zp_x(uint8_t);
  void op_ldx_zp_y(uint8_t);
  void op_clv(uint8_t);
  void op_lda_abs_y(uint8_t);
  void op_ldy_abs_x(uint8_t);
  void op_lda_abs_x(uint8_t);
  void op_ldx_abs_y(uint8_t);

  void op_cpy_imm(uint8_t);
  void op_cmp_ind_x(uint8_t);
  void op_cpy_zp(uint8_t);
  void op_cmp_zp(uint8_t);
  void op_dec_zp(uint8_t);
  void op_iny(uint8_t);
  void op_cmp_imm(uint8_t);
  void op_dex(uint8_t);
  void op_cpy_abs(uint8_t);
  void op_cmp_abs(uint8_t);
  void op_dec_abs(uint8_t);

  void op_bne(uint8_t);
  void op_cmp_ind_y(uint8_t);
  void op_cmp_zp_x(uint8_t);
  void op_dec_zp_x(uint8_t);
  void op_cld(uint8_t);
  void op_cmp_abs_y(uint8_t);
  void op_cmp_abs_x(uint8_t);
  void op_dec_abs_x(uint8_t);

  void op_cpx_imm(uint8_t);
  void op_sbc_ind_x(uint8_t);
  void op_cpx_zp(uint8_t);
  void op_sbc_zp(uint8_t);
  void op_inc_zp(uint8_t);
  void op_inx(uint8_t);
  void op_sbc_imm(uint8_t);
  void op_nop_imp(uint8_t);
  void op_cpx_abs(uint8_t);
  void op_sbc_abs(uint8_t);
  void op_inc_abs(uint8_t);

  void op_beq(uint8_t);
  void op_sbc_ind_y(uint8_t);
  void op_sbc_zp_x(uint8_t);
  void op_inc_zp_x(uint8_t);
  void op_sed(uint8_t);
  void op_sbc_abs_y(uint8_t);
  void op_sbc_abs_x(uint8_t);
  void op_inc_abs_x(uint8_t);
};
