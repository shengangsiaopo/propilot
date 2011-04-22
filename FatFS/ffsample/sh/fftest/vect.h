/***********************************************************************/
/*                                                                     */
/*  FILE        :vect.h                                                */
/*  DATE        :Tue, Mar 09, 2010                                     */
/*  DESCRIPTION :Definition of Vector                                  */
/*  CPU TYPE    :SH72623                                               */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.16).    */
/*                                                                     */
/***********************************************************************/
/*********************************************************************
*
* Device     : SH2A-FPU/SH7262,SH7264
*
* File Name  : vect.h
*
* Abstract   : Definition of Vector.
*
* History    : 1.00  (2009-11-13)  [Hardware Manual Revision : 2.00]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright(c) 2009 Renesas Technology Corp.
*               And Renesas Solutions Corp.,All Rights Reserved. 
*
*********************************************************************/
#ifndef VECT_H
#define VECT_H

//;<<VECTOR DATA START (POWER ON RESET)>>
//;0 Power On Reset PC
extern void PowerON_Reset_PC(void);                                                                                                                

//;<<VECTOR DATA END (POWER ON RESET)>>
// 1 Power On Reset SP

//;<<VECTOR DATA START (MANUAL RESET)>>
//;2 Manual Reset PC
extern void Manual_Reset_PC(void);                                                                                                                 

//;<<VECTOR DATA END (MANUAL RESET)>>
// 3 Manual Reset SP

// 4 Illegal code
#pragma interrupt INT_Illegal_code
extern void INT_Illegal_code(void);

// 5 Reserved

// 6 Illegal slot
#pragma interrupt INT_Illegal_slot
extern void INT_Illegal_slot(void);

// 7 Reserved

// 8 Reserved

// 9 CPU Address error
#pragma interrupt INT_CPU_Address
extern void INT_CPU_Address(void);

// 10 DMAC Address erro
#pragma interrupt INT_DMAC_Address
extern void INT_DMAC_Address(void);

// 11 NMI
#pragma interrupt INT_NMI
extern void INT_NMI(void);

// 12 Reserved

// 13 INT_FPU
#pragma interrupt INT_FPU
extern void INT_FPU(void);

// 14 User debug interface
#pragma interrupt INT_UDI
extern void INT_UDI(void);

// 15 Bank Overflow
#pragma interrupt INT_Bank_Overflow
extern void INT_Bank_Overflow(void);

// 16 Bank Underflow
#pragma interrupt INT_Bank_Underflow
extern void INT_Bank_Underflow(void);

// 17 Divide by zero
#pragma interrupt INT_Divide_by_Zero
extern void INT_Divide_by_Zero(void);

// 18 Divide Overflow
#pragma interrupt INT_Divide_Overflow
extern void INT_Divide_Overflow(void);

// 19 Reserved

// 20 Reserved

// 21 Reserved

// 22 Reserved

// 23 Reserved

// 24 Reserved

// 25 Reserved

// 26 Reserved

// 27 Reserved

// 28 Reserved

// 29 Reserved

// 30 Reserved

// 31 Reserved

// 32 TRAPA (User Vector)
#pragma interrupt INT_TRAPA32
extern void INT_TRAPA32(void);

// 33 TRAPA (User Vector)
#pragma interrupt INT_TRAPA33
extern void INT_TRAPA33(void);

// 34 TRAPA (User Vector)
#pragma interrupt INT_TRAPA34
extern void INT_TRAPA34(void);

// 35 TRAPA (User Vector)
#pragma interrupt INT_TRAPA35
extern void INT_TRAPA35(void);

// 36 TRAPA (User Vector)
#pragma interrupt INT_TRAPA36
extern void INT_TRAPA36(void);

// 37 TRAPA (User Vector)
#pragma interrupt INT_TRAPA37
extern void INT_TRAPA37(void);

// 38 TRAPA (User Vector)
#pragma interrupt INT_TRAPA38
extern void INT_TRAPA38(void);

// 39 TRAPA (User Vector)
#pragma interrupt INT_TRAPA39
extern void INT_TRAPA39(void);

// 40 TRAPA (User Vector)
#pragma interrupt INT_TRAPA40
extern void INT_TRAPA40(void);

// 41 TRAPA (User Vector)
#pragma interrupt INT_TRAPA41
extern void INT_TRAPA41(void);

// 42 TRAPA (User Vector)
#pragma interrupt INT_TRAPA42
extern void INT_TRAPA42(void);

// 43 TRAPA (User Vector)
#pragma interrupt INT_TRAPA43
extern void INT_TRAPA43(void);

// 44 TRAPA (User Vector)
#pragma interrupt INT_TRAPA44
extern void INT_TRAPA44(void);

// 45 TRAPA (User Vector)
#pragma interrupt INT_TRAPA45
extern void INT_TRAPA45(void);

// 46 TRAPA (User Vector)
#pragma interrupt INT_TRAPA46
extern void INT_TRAPA46(void);

// 47 TRAPA (User Vector)
#pragma interrupt INT_TRAPA47
extern void INT_TRAPA47(void);

// 48 TRAPA (User Vector)
#pragma interrupt INT_TRAPA48
extern void INT_TRAPA48(void);

// 49 TRAPA (User Vector)
#pragma interrupt INT_TRAPA49
extern void INT_TRAPA49(void);

// 50 TRAPA (User Vector)
#pragma interrupt INT_TRAPA50
extern void INT_TRAPA50(void);

// 51 TRAPA (User Vector)
#pragma interrupt INT_TRAPA51
extern void INT_TRAPA51(void);

// 52 TRAPA (User Vector)
#pragma interrupt INT_TRAPA52
extern void INT_TRAPA52(void);

// 53 TRAPA (User Vector)
#pragma interrupt INT_TRAPA53
extern void INT_TRAPA53(void);

// 54 TRAPA (User Vector)
#pragma interrupt INT_TRAPA54
extern void INT_TRAPA54(void);

// 55 TRAPA (User Vector)
#pragma interrupt INT_TRAPA55
extern void INT_TRAPA55(void);

// 56 TRAPA (User Vector)
#pragma interrupt INT_TRAPA56
extern void INT_TRAPA56(void);

// 57 TRAPA (User Vector)
#pragma interrupt INT_TRAPA57
extern void INT_TRAPA57(void);

// 58 TRAPA (User Vector)
#pragma interrupt INT_TRAPA58
extern void INT_TRAPA58(void);

// 59 TRAPA (User Vector)
#pragma interrupt INT_TRAPA59
extern void INT_TRAPA59(void);

// 60 TRAPA (User Vector)
#pragma interrupt INT_TRAPA60
extern void INT_TRAPA60(void);

// 61 TRAPA (User Vector)
#pragma interrupt INT_TRAPA61
extern void INT_TRAPA61(void);

// 62 TRAPA (User Vector)
#pragma interrupt INT_TRAPA62
extern void INT_TRAPA62(void);

// 63 TRAPA (User Vector)
#pragma interrupt INT_TRAPA63
extern void INT_TRAPA63(void);

// 64 Interrupt IRQ0
#pragma interrupt INT_IRQ0
extern void INT_IRQ0(void);

// 65 Interrupt IRQ1
#pragma interrupt INT_IRQ1
extern void INT_IRQ1(void);

// 66 Interrupt IRQ2
#pragma interrupt INT_IRQ2
extern void INT_IRQ2(void);

// 67 Interrupt IRQ3
#pragma interrupt INT_IRQ3
extern void INT_IRQ3(void);

// 68 Interrupt IRQ4
#pragma interrupt INT_IRQ4
extern void INT_IRQ4(void);

// 69 Interrupt IRQ5
#pragma interrupt INT_IRQ5
extern void INT_IRQ5(void);

// 70 Interrupt IRQ6
#pragma interrupt INT_IRQ6
extern void INT_IRQ6(void);

// 71 Interrupt IRQ7
#pragma interrupt INT_IRQ7
extern void INT_IRQ7(void);

// 72 Reserved

// 73 Reserved

// 74 Reserved

// 75 Reserved

// 76 Reserved

// 77 Reserved

// 78 Reserved

// 79 Reserved

// 80 PINT PINT0
#pragma interrupt INT_PINT_PINT0
extern void INT_PINT_PINT0(void);

// 81 PINT PINT1
#pragma interrupt INT_PINT_PINT1
extern void INT_PINT_PINT1(void);

// 82 PINT PINT2
#pragma interrupt INT_PINT_PINT2
extern void INT_PINT_PINT2(void);

// 83 PINT PINT3
#pragma interrupt INT_PINT_PINT3
extern void INT_PINT_PINT3(void);

// 84 PINT PINT4
#pragma interrupt INT_PINT_PINT4
extern void INT_PINT_PINT4(void);

// 85 PINT PINT5
#pragma interrupt INT_PINT_PINT5
extern void INT_PINT_PINT5(void);

// 86 PINT PINT6
#pragma interrupt INT_PINT_PINT6
extern void INT_PINT_PINT6(void);

// 87 PINT PINT7
#pragma interrupt INT_PINT_PINT7
extern void INT_PINT_PINT7(void);

// 88 Reserved

// 89 Reserved

// 90 Reserved

// 91 Reserved

// 92 Reserved

// 93 Reserved

// 94 Reserved

// 95 Reserved

// 96 Reserved

// 97 Reserved

// 98 Reserved

// 99 Reserved

// 100 Reserved

// 101 Reserved

// 102 Reserved

// 103 Reserved

// 104 Reserved

// 105 Reserved

// 106 Reserved

// 107 Reserved

// 108 DMAC0 DEI
#pragma interrupt INT_DMAC0_DEI0
extern void INT_DMAC0_DEI0(void);

// 109 DMAC0 HEI
#pragma interrupt INT_DMAC0_HEI0
extern void INT_DMAC0_HEI0(void);

// 110 Reserved

// 111 Reserved

// 112 DMAC1 DEI
#pragma interrupt INT_DMAC1_DEI1
extern void INT_DMAC1_DEI1(void);

// 113 DMAC1 HEI
#pragma interrupt INT_DMAC1_HEI1
extern void INT_DMAC1_HEI1(void);

// 114 Reserved

// 115 Reserved

// 116 DMAC2 DEI
#pragma interrupt INT_DMAC2_DEI2
extern void INT_DMAC2_DEI2(void);

// 117 DMAC2 HEI
#pragma interrupt INT_DMAC2_HEI2
extern void INT_DMAC2_HEI2(void);

// 118 Reserved

// 119 Reserved

// 120 DMAC3 DEI
#pragma interrupt INT_DMAC3_DEI3
extern void INT_DMAC3_DEI3(void);

// 121 DMAC3 HEI
#pragma interrupt INT_DMAC3_HEI3
extern void INT_DMAC3_HEI3(void);

// 122 Reserved

// 123 Reserved

// 124 DMAC4 DEI
#pragma interrupt INT_DMAC4_DEI4
extern void INT_DMAC4_DEI4(void);

// 125 DMAC4 HEI
#pragma interrupt INT_DMAC4_HEI4
extern void INT_DMAC4_HEI4(void);

// 126 Reserved

// 127 Reserved

// 128 DMAC5 DEI
#pragma interrupt INT_DMAC5_DEI5
extern void INT_DMAC5_DEI5(void);

// 129 DMAC5 HEI
#pragma interrupt INT_DMAC5_HEI5
extern void INT_DMAC5_HEI5(void);

// 130 Reserved

// 131 Reserved

// 132 DMAC6 DEI
#pragma interrupt INT_DMAC6_DEI6
extern void INT_DMAC6_DEI6(void);

// 133 DMAC6 HEI
#pragma interrupt INT_DMAC6_HEI6
extern void INT_DMAC6_HEI6(void);

// 134 Reserved

// 135 Reserved

// 136 DMAC7 DEI
#pragma interrupt INT_DMAC7_DEI7
extern void INT_DMAC7_DEI7(void);

// 137 DMAC7 HEI
#pragma interrupt INT_DMAC7_HEI7
extern void INT_DMAC7_HEI7(void);

// 138 Reserved

// 139 Reserved

// 140 DMAC8 DEI
#pragma interrupt INT_DMAC8_DEI8
extern void INT_DMAC8_DEI8(void);

// 141 DMAC8 HEI
#pragma interrupt INT_DMAC8_HEI8
extern void INT_DMAC8_HEI8(void);

// 142 Reserved

// 143 Reserved

// 144 DMAC9 DEI
#pragma interrupt INT_DMAC9_DEI9
extern void INT_DMAC9_DEI9(void);

// 145 DMAC9 HEI
#pragma interrupt INT_DMAC9_HEI9
extern void INT_DMAC9_HEI9(void);

// 146 Reserved

// 147 Reserved

// 148 DMAC10 DEI
#pragma interrupt INT_DMAC10_DEI10
extern void INT_DMAC10_DEI10(void);

// 149 DMAC10 HEI
#pragma interrupt INT_DMAC10_HEI10
extern void INT_DMAC10_HEI10(void);

// 150 Reserved

// 151 Reserved

// 152 DMAC11 DEI
#pragma interrupt INT_DMAC11_DEI11
extern void INT_DMAC11_DEI11(void);

// 153 DMAC11 HEI
#pragma interrupt INT_DMAC11_HEI11
extern void INT_DMAC11_HEI11(void);

// 154 Reserved

// 155 Reserved

// 156 DMAC12 DEI
#pragma interrupt INT_DMAC12_DEI12
extern void INT_DMAC12_DEI12(void);

// 157 DMAC12 HEI
#pragma interrupt INT_DMAC12_HEI12
extern void INT_DMAC12_HEI12(void);

// 158 Reserved

// 159 Reserved

// 160 DMAC13 DEI
#pragma interrupt INT_DMAC13_DEI13
extern void INT_DMAC13_DEI13(void);

// 161 DMAC13 HEI
#pragma interrupt INT_DMAC13_HEI13
extern void INT_DMAC13_HEI13(void);

// 162 Reserved

// 163 Reserved

// 164 DMAC14 DEI
#pragma interrupt INT_DMAC14_DEI14
extern void INT_DMAC14_DEI14(void);

// 165 DMAC14 HEI
#pragma interrupt INT_DMAC14_HEI14
extern void INT_DMAC14_HEI14(void);

// 166 Reserved

// 167 Reserved

// 168 DMAC15 DEI
#pragma interrupt INT_DMAC15_DEI15
extern void INT_DMAC15_DEI15(void);

// 169 DMAC15 HEI
#pragma interrupt INT_DMAC15_HEI15
extern void INT_DMAC15_HEI15(void);

// 170 USB2.0 USBI
#pragma interrupt INT_USB2_USBI
extern void INT_USB2_USBI(void);

// 171 VDC VIVSYNCJ
#pragma interrupt INT_VDC_VIVSYNCJ
extern void INT_VDC_VIVSYNCJ(void);

// 172 VDC VBUFERR
#pragma interrupt INT_VDC_VBUFERR
extern void INT_VDC_VBUFERR(void);

// 173 VDC VIFIELDE
#pragma interrupt INT_VDC_VIFIELDE
extern void INT_VDC_VIFIELDE(void);

// 174 VDC VOLINE
#pragma interrupt INT_VDC_VOLINE
extern void INT_VDC_VOLINE(void);

// 175 CMT CH0 CMI0
#pragma interrupt INT_CMT_CMI0
extern void INT_CMT_CMI0(void);

// 176 CMT CH1 CMI1
#pragma interrupt INT_CMT_CMI1
extern void INT_CMT_CMI1(void);

// 177 BSC CMI
#pragma interrupt INT_BSC_CMI
extern void INT_BSC_CMI(void);

// 178 WDT ITI
#pragma interrupt INT_WDT_ITI
extern void INT_WDT_ITI(void);

// 179 MTU2 MTU0 TGI0A
#pragma interrupt INT_MTU2_MTU0_TGI0A
extern void INT_MTU2_MTU0_TGI0A(void);

// 180 MTU2 MTU0 TGI0B
#pragma interrupt INT_MTU2_MTU0_TGI0B
extern void INT_MTU2_MTU0_TGI0B(void);

// 181 MTU2 MTU0 TGI0C
#pragma interrupt INT_MTU2_MTU0_TGI0C
extern void INT_MTU2_MTU0_TGI0C(void);

// 182 MTU2 MTU0 TGI0D
#pragma interrupt INT_MTU2_MTU0_TGI0D
extern void INT_MTU2_MTU0_TGI0D(void);

// 183 MTU2 MTU0 TCI0V
#pragma interrupt INT_MTU2_MTU0_TCI0V
extern void INT_MTU2_MTU0_TCI0V(void);

// 184 MTU2 MTU0 TGI0E
#pragma interrupt INT_MTU2_MTU0_TGI0E
extern void INT_MTU2_MTU0_TGI0E(void);

// 185 MTU2 MTU0 TGI0F
#pragma interrupt INT_MTU2_MTU0_TGI0F
extern void INT_MTU2_MTU0_TGI0F(void);

// 186 MTU2 MTU1 TGI1A
#pragma interrupt INT_MTU2_MTU1_TGI1A
extern void INT_MTU2_MTU1_TGI1A(void);

// 187 MTU2 MTU1 TGI1B
#pragma interrupt INT_MTU2_MTU1_TGI1B
extern void INT_MTU2_MTU1_TGI1B(void);

// 188 MTU2 MTU1 TCI1V
#pragma interrupt INT_MTU2_MTU1_TCI1V
extern void INT_MTU2_MTU1_TCI1V(void);

// 189 MTU2 MTU1 TCI1U
#pragma interrupt INT_MTU2_MTU1_TCI1U
extern void INT_MTU2_MTU1_TCI1U(void);

// 190 MTU2 MTU2 TGI2A
#pragma interrupt INT_MTU2_MTU2_TGI2A
extern void INT_MTU2_MTU2_TGI2A(void);

// 191 MTU2 MTU2 TGI2B
#pragma interrupt INT_MTU2_MTU2_TGI2B
extern void INT_MTU2_MTU2_TGI2B(void);

// 192 MTU2 MTU2 TCI2V
#pragma interrupt INT_MTU2_MTU2_TCI2V
extern void INT_MTU2_MTU2_TCI2V(void);

// 193 MTU2 MTU2 TCI2U
#pragma interrupt INT_MTU2_MTU2_TCI2U
extern void INT_MTU2_MTU2_TCI2U(void);

// 194 MTU2 MTU3 TGI3A
#pragma interrupt INT_MTU2_MTU3_TGI3A
extern void INT_MTU2_MTU3_TGI3A(void);

// 195 MTU2 MTU3 TGI3B
#pragma interrupt INT_MTU2_MTU3_TGI3B
extern void INT_MTU2_MTU3_TGI3B(void);

// 196 MTU2 MTU3 TGI3C
#pragma interrupt INT_MTU2_MTU3_TGI3C
extern void INT_MTU2_MTU3_TGI3C(void);

// 197 MTU2 MTU3 TGI3D
#pragma interrupt INT_MTU2_MTU3_TGI3D
extern void INT_MTU2_MTU3_TGI3D(void);

// 198 MTU2 MTU3 TCI3V
#pragma interrupt INT_MTU2_MTU3_TCI3V
extern void INT_MTU2_MTU3_TCI3V(void);

// 199 MTU2 MTU4 TGI4A
#pragma interrupt INT_MTU2_MTU4_TGI4A
extern void INT_MTU2_MTU4_TGI4A(void);

// 200 MTU2 MTU4 TGI4B
#pragma interrupt INT_MTU2_MTU4_TGI4B
extern void INT_MTU2_MTU4_TGI4B(void);

// 201 MTU2 MTU4 TGI4C
#pragma interrupt INT_MTU2_MTU4_TGI4C
extern void INT_MTU2_MTU4_TGI4C(void);

// 202 MTU2 MTU4 TGI4D
#pragma interrupt INT_MTU2_MTU4_TGI4D
extern void INT_MTU2_MTU4_TGI4D(void);

// 203 MTU2 MTU4 TCI4V
#pragma interrupt INT_MTU2_MTU4_TCI4V
extern void INT_MTU2_MTU4_TCI4V(void);

// 204 PWM CH1
#pragma interrupt INT_PWM_CH1
extern void INT_PWM_CH1(void);

// 205 PWM CH2
#pragma interrupt INT_PWM_CH2
extern void INT_PWM_CH2(void);

// 206 ADC ADI
#pragma interrupt INT_ADC_ADI
extern void INT_ADC_ADI(void);

// 207 SSI CH0 SSIF0
#pragma interrupt INT_SSI_CH0_SSIF0
extern void INT_SSI_CH0_SSIF0(void);

// 208 SSI CH0 SSIRXI0
#pragma interrupt INT_SSI_CH0_SSIRXI0
extern void INT_SSI_CH0_SSIRXI0(void);

// 209 SSI CH0 SSITXI0
#pragma interrupt INT_SSI_CH0_SSITXI0
extern void INT_SSI_CH0_SSITXI0(void);

// 210 SSI CH1 SSII1
#pragma interrupt INT_SSI_CH1_SSII1
extern void INT_SSI_CH1_SSII1(void);

// 211 SSI CH1 SSIRTI1
#pragma interrupt INT_SSI_CH1_SSIRTI1
extern void INT_SSI_CH1_SSIRTI1(void);

// 212 SSI CH2 SSII2
#pragma interrupt INT_SSI_CH2_SSII2
extern void INT_SSI_CH2_SSII2(void);

// 213 SSI CH2 SSIRTI2
#pragma interrupt INT_SSI_CH2_SSIRTI2
extern void INT_SSI_CH2_SSIRTI2(void);

// 214 SSI CH3 SSII3
#pragma interrupt INT_SSI_CH3_SSII3
extern void INT_SSI_CH3_SSII3(void);

// 215 SSI CH3 SSIRTI3
#pragma interrupt INT_SSI_CH3_SSIRTI3
extern void INT_SSI_CH3_SSIRTI3(void);

// 216 SPDIF SPDIFI
#pragma interrupt INT_SPDIF_SPDIFI
extern void INT_SPDIF_SPDIFI(void);

// 217 PCBI3 CH0 STPI0
#pragma interrupt INT_PCBI3_CH0_STPI0
extern void INT_PCBI3_CH0_STPI0(void);

// 218 PCBI3 CH0 NAKI0
#pragma interrupt INT_PCBI3_CH0_NAKI0
extern void INT_PCBI3_CH0_NAKI0(void);

// 219 PCBI3 CH0 RXI0
#pragma interrupt INT_PCBI3_CH0_RXI0
extern void INT_PCBI3_CH0_RXI0(void);

// 220 PCBI3 CH0 TXI0
#pragma interrupt INT_PCBI3_CH0_TXI0
extern void INT_PCBI3_CH0_TXI0(void);

// 221 PCBI3 CH0 TEI0
#pragma interrupt INT_PCBI3_CH0_TEI0
extern void INT_PCBI3_CH0_TEI0(void);

// 222 PCBI3 CH1 STPI1
#pragma interrupt INT_PCBI3_CH1_STPI1
extern void INT_PCBI3_CH1_STPI1(void);

// 223 PCBI3 CH1 NAKI1
#pragma interrupt INT_PCBI3_CH1_NAKI1
extern void INT_PCBI3_CH1_NAKI1(void);

// 224 PCBI3 CH1 RXI1
#pragma interrupt INT_PCBI3_CH1_RXI1
extern void INT_PCBI3_CH1_RXI1(void);

// 225 PCBI3 CH1 TXI1
#pragma interrupt INT_PCBI3_CH1_TXI1
extern void INT_PCBI3_CH1_TXI1(void);

// 226 PCBI3 CH1 TEI1
#pragma interrupt INT_PCBI3_CH1_TEI1
extern void INT_PCBI3_CH1_TEI1(void);

// 227 PCBI3 CH2 STPI2
#pragma interrupt INT_PCBI3_CH2_STPI2
extern void INT_PCBI3_CH2_STPI2(void);

// 228 PCBI3 CH2 NAKI2
#pragma interrupt INT_PCBI3_CH2_NAKI2
extern void INT_PCBI3_CH2_NAKI2(void);

// 229 PCBI3 CH2 RXI2
#pragma interrupt INT_PCBI3_CH2_RXI2
extern void INT_PCBI3_CH2_RXI2(void);

// 230 PCBI3 CH2 TXI2
#pragma interrupt INT_PCBI3_CH2_TXI2
extern void INT_PCBI3_CH2_TXI2(void);

// 231 PCBI3 CH2 TEI2
#pragma interrupt INT_PCBI3_CH2_TEI2
extern void INT_PCBI3_CH2_TEI2(void);

// 232 SCIF SCIF0 BRI0
#pragma interrupt INT_SCIF_SCIF0_BRI0
extern void INT_SCIF_SCIF0_BRI0(void);

// 233 SCIF SCIF0 ERI0
#pragma interrupt INT_SCIF_SCIF0_ERI0
extern void INT_SCIF_SCIF0_ERI0(void);

// 234 SCIF SCIF0 RXI0
#pragma interrupt INT_SCIF_SCIF0_RXI0
extern void INT_SCIF_SCIF0_RXI0(void);

// 235 SCIF SCIF0 TXI0
#pragma interrupt INT_SCIF_SCIF0_TXI0
extern void INT_SCIF_SCIF0_TXI0(void);

// 236 SCIF SCIF1 BRI1
#pragma interrupt INT_SCIF_SCIF1_BRI1
extern void INT_SCIF_SCIF1_BRI1(void);

// 237 SCIF SCIF1 ERI1
#pragma interrupt INT_SCIF_SCIF1_ERI1
extern void INT_SCIF_SCIF1_ERI1(void);

// 238 SCIF SCIF1 RXI1
#pragma interrupt INT_SCIF_SCIF1_RXI1
extern void INT_SCIF_SCIF1_RXI1(void);

// 239 SCIF SCIF1 TXI1
#pragma interrupt INT_SCIF_SCIF1_TXI1
extern void INT_SCIF_SCIF1_TXI1(void);

// 240 SCIF SCIF2 BRI2
#pragma interrupt INT_SCIF_SCIF2_BRI2
extern void INT_SCIF_SCIF2_BRI2(void);

// 241 SCIF SCIF2 ERI2
#pragma interrupt INT_SCIF_SCIF2_ERI2
extern void INT_SCIF_SCIF2_ERI2(void);

// 242 SCIF SCIF2 RXI2
#pragma interrupt INT_SCIF_SCIF2_RXI2
extern void INT_SCIF_SCIF2_RXI2(void);

// 243 SCIF SCIF2 TXI2
#pragma interrupt INT_SCIF_SCIF2_TXI2
extern void INT_SCIF_SCIF2_TXI2(void);

// 244 SCIF SCIF3 BRI3
#pragma interrupt INT_SCIF_SCIF3_BRI3
extern void INT_SCIF_SCIF3_BRI3(void);

// 245 SCIF SCIF3 ERI3
#pragma interrupt INT_SCIF_SCIF3_ERI3
extern void INT_SCIF_SCIF3_ERI3(void);

// 246 SCIF SCIF3 RXI3
#pragma interrupt INT_SCIF_SCIF3_RXI3
extern void INT_SCIF_SCIF3_RXI3(void);

// 247 SCIF SCIF3 TXI3
#pragma interrupt INT_SCIF_SCIF3_TXI3
extern void INT_SCIF_SCIF3_TXI3(void);

// 248 SCIF SCIF4 BRI4
#pragma interrupt INT_SCIF_SCIF4_BRI4
extern void INT_SCIF_SCIF4_BRI4(void);

// 249 SCIF SCIF4 ERI4
#pragma interrupt INT_SCIF_SCIF4_ERI4
extern void INT_SCIF_SCIF4_ERI4(void);

// 250 SCIF SCIF4 RXI4
#pragma interrupt INT_SCIF_SCIF4_RXI4
extern void INT_SCIF_SCIF4_RXI4(void);

// 251 SCIF SCIF4 TXI4
#pragma interrupt INT_SCIF_SCIF4_TXI4
extern void INT_SCIF_SCIF4_TXI4(void);

// 252 SCIF SCIF5 BRI5
#pragma interrupt INT_SCIF_SCIF5_BRI5
extern void INT_SCIF_SCIF5_BRI5(void);

// 253 SCIF SCIF5 ERI5
#pragma interrupt INT_SCIF_SCIF5_ERI5
extern void INT_SCIF_SCIF5_ERI5(void);

// 254 SCIF SCIF5 RXI5
#pragma interrupt INT_SCIF_SCIF5_RXI5
extern void INT_SCIF_SCIF5_RXI5(void);

// 255 SCIF SCIF5 TXI5
#pragma interrupt INT_SCIF_SCIF5_TXI5
extern void INT_SCIF_SCIF5_TXI5(void);

// 256 SCIF SCIF6 BRI6
#pragma interrupt INT_SCIF_SCIF6_BRI6
extern void INT_SCIF_SCIF6_BRI6(void);

// 257 SCIF SCIF6 ERI6
#pragma interrupt INT_SCIF_SCIF6_ERI6
extern void INT_SCIF_SCIF6_ERI6(void);

// 258 SCIF SCIF6 RXI6
#pragma interrupt INT_SCIF_SCIF6_RXI6
extern void INT_SCIF_SCIF6_RXI6(void);

// 259 SCIF SCIF6 TXI6
#pragma interrupt INT_SCIF_SCIF6_TXI6
extern void INT_SCIF_SCIF6_TXI6(void);

// 260 SCIF SCIF7 BRI7
#pragma interrupt INT_SCIF_SCIF7_BRI7
extern void INT_SCIF_SCIF7_BRI7(void);

// 261 SCIF SCIF7 ERI7
#pragma interrupt INT_SCIF_SCIF7_ERI7
extern void INT_SCIF_SCIF7_ERI7(void);

// 262 SCIF SCIF7 RXI7
#pragma interrupt INT_SCIF_SCIF7_RXI7
extern void INT_SCIF_SCIF7_RXI7(void);

// 263 SCIF SCIF7 TXI7
#pragma interrupt INT_SCIF_SCIF7_TXI7
extern void INT_SCIF_SCIF7_TXI7(void);

// 264 CSSIO SIOFI
#pragma interrupt INT_CSSIO_SIOFI
extern void INT_CSSIO_SIOFI(void);

// 265 RPI CH0 SPEI0
#pragma interrupt INT_RPI_CH0_SPEI0
extern void INT_RPI_CH0_SPEI0(void);

// 266 RPI CH0 SPRI0
#pragma interrupt INT_RPI_CH0_SPRI0
extern void INT_RPI_CH0_SPRI0(void);

// 267 RPI CH0 SPTI0
#pragma interrupt INT_RPI_CH0_SPTI0
extern void INT_RPI_CH0_SPTI0(void);

// 268 RPI CH1 SPEI1
#pragma interrupt INT_RPI_CH1_SPEI1
extern void INT_RPI_CH1_SPEI1(void);

// 269 RPI CH1 SPRI1
#pragma interrupt INT_RPI_CH1_SPRI1
extern void INT_RPI_CH1_SPRI1(void);

// 270 RPI CH1 SPTI1
#pragma interrupt INT_RPI_CH1_SPTI1
extern void INT_RPI_CH1_SPTI1(void);

// 271 CAN CH0 ERS0
#pragma interrupt INT_CAN_CH0_ERS0
extern void INT_CAN_CH0_ERS0(void);

// 272 CAN CH0 OVR0
#pragma interrupt INT_CAN_CH0_OVR0
extern void INT_CAN_CH0_OVR0(void);

// 273 CAN CH0 RM00
#pragma interrupt INT_CAN_CH0_RM00
extern void INT_CAN_CH0_RM00(void);

// 274 CAN CH0 RM10
#pragma interrupt INT_CAN_CH0_RM10
extern void INT_CAN_CH0_RM10(void);

// 275 CAN CH0 SLE0
#pragma interrupt INT_CAN_CH0_SLE0
extern void INT_CAN_CH0_SLE0(void);

// 276 CAN CH1 ERS1
#pragma interrupt INT_CAN_CH1_ERS1
extern void INT_CAN_CH1_ERS1(void);

// 277 CAN CH1 OVR1
#pragma interrupt INT_CAN_CH1_OVR1
extern void INT_CAN_CH1_OVR1(void);

// 278 CAN CH1 RM01
#pragma interrupt INT_CAN_CH1_RM01
extern void INT_CAN_CH1_RM01(void);

// 279 CAN CH1 RM11
#pragma interrupt INT_CAN_CH1_RM11
extern void INT_CAN_CH1_RM11(void);

// 280 CAN CH1 SLE1
#pragma interrupt INT_CAN_CH1_SLE1
extern void INT_CAN_CH1_SLE1(void);

// 281 IEBC IEB
#pragma interrupt INT_IEBC_IEB
extern void INT_IEBC_IEB(void);

// 282 CDROMDEC ISY
#pragma interrupt INT_CDROMDEC_ISY
extern void INT_CDROMDEC_ISY(void);

// 283 CDROMDEC IERR
#pragma interrupt INT_CDROMDEC_IERR
extern void INT_CDROMDEC_IERR(void);

// 284 CDROMDEC ITARG
#pragma interrupt INT_CDROMDEC_ITARG
extern void INT_CDROMDEC_ITARG(void);

// 285 CDROMDEC ISEC
#pragma interrupt INT_CDROMDEC_ISEC
extern void INT_CDROMDEC_ISEC(void);

// 286 CDROMDEC IBUF
#pragma interrupt INT_CDROMDEC_IBUF
extern void INT_CDROMDEC_IBUF(void);

// 287 CDROMDEC IREADY
#pragma interrupt INT_CDROMDEC_IREADY
extern void INT_CDROMDEC_IREADY(void);

// 288 FMC FLSTEI
#pragma interrupt INT_FMC_FLSTEI
extern void INT_FMC_FLSTEI(void);

// 289 FMC FLTENDI
#pragma interrupt INT_FMC_FLTENDI
extern void INT_FMC_FLTENDI(void);

// 290 FMC FLTREQ0I
#pragma interrupt INT_FMC_FLTREQ0I
extern void INT_FMC_FLTREQ0I(void);

// 291 FMC FLTREQ1I
#pragma interrupt INT_FMC_FLTREQ1I
extern void INT_FMC_FLTREQ1I(void);

// 292 SDHI SDHI3
#pragma interrupt INT_SDHI_SDHI3
extern void INT_SDHI_SDHI3(void);

// 293 SDHI SDHI0
#pragma interrupt INT_SDHI_SDHI0
extern void INT_SDHI_SDHI0(void);

// 294 SDHI SDHI1
#pragma interrupt INT_SDHI_SDHI1
extern void INT_SDHI_SDHI1(void);

// 295 Reserved

// 296 RTC ARM
#pragma interrupt INT_RTC_ARM
extern void INT_RTC_ARM(void);

// 297 RTC PRD
#pragma interrupt INT_RTC_PRD
extern void INT_RTC_PRD(void);

// 298 RTC CUP
#pragma interrupt INT_RTC_CUP
extern void INT_RTC_CUP(void);

// 299 SRC CH0 OVF0
#pragma interrupt INT_SRC_CH0_OVF0
extern void INT_SRC_CH0_OVF0(void);

// 300 SRC CH0 UDF0
#pragma interrupt INT_SRC_CH0_UDF0
extern void INT_SRC_CH0_UDF0(void);

// 301 SRC CH0 CEF0
#pragma interrupt INT_SRC_CH0_CEF0
extern void INT_SRC_CH0_CEF0(void);

// 302 SRC CH0 ODFI0
#pragma interrupt INT_SRC_CH0_ODFI0
extern void INT_SRC_CH0_ODFI0(void);

// 303 SRC CH0 IDEI0
#pragma interrupt INT_SRC_CH0_IDEI0
extern void INT_SRC_CH0_IDEI0(void);

// 304 SRC CH1 OVF1
#pragma interrupt INT_SRC_CH1_OVF1
extern void INT_SRC_CH1_OVF1(void);

// 305 SRC CH1 UDF1
#pragma interrupt INT_SRC_CH1_UDF1
extern void INT_SRC_CH1_UDF1(void);

// 306 SRC CH1 CEF1
#pragma interrupt INT_SRC_CH1_CEF1
extern void INT_SRC_CH1_CEF1(void);

// 307 SRC CH1 ODFI1
#pragma interrupt INT_SRC_CH1_ODFI1
extern void INT_SRC_CH1_ODFI1(void);

// 308 SRC CH1 IDEI1
#pragma interrupt INT_SRC_CH1_IDEI1
extern void INT_SRC_CH1_IDEI1(void);

// 309 DCU DCUEI
#pragma interrupt INT_SRC_DCU_DCUEI
extern void INT_SRC_DCU_DCUEI(void);

// 310 DCU OFFI
#pragma interrupt INT_SRC_DCU_OFFI
extern void INT_SRC_DCU_OFFI(void);

// 311 DCU IFEI
#pragma interrupt INT_SRC_DCU_IFEI
extern void INT_SRC_DCU_IFEI(void);

// Dummy
#pragma interrupt Dummy
extern void Dummy(void);

#endif /* VECT_H */

/* End of File */
