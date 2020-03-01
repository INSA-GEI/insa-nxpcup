/*
** ###################################################################
**     Processors:          MWPR1516CAL
**                          MWPR1516CFM
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    MWPR1516RM, Rev. 2 Draft A, Sep 2014
**     Version:             rev. 1.5, 2014-12-12
**     Build:               b150421
**
**     Abstract:
**         This header file implements peripheral memory map for MWPR1516
**         processor.
**
**     Copyright (c) 1997 - 2015 Freescale Semiconductor, Inc.
**     All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-04-23)
**         Initial version.
**     - rev. 1.1 (2014-07-07)
**         ADC - Bitfield AUT_RSTA has been added into register CTL1.
**         CNC - Register ANACFG has been renamed to ANACFG1.
**         FSKDT - Register OTRGTH has been renamed to OPCTH.
**         FSKDT - Bitfield OTRGIE in register CR has been renamed to OPIE.
**         FSKDT - Bitfield OTRGF in register SR has been renamed to OPF.
**         FTM - Register EXTTRIG has been added.
**         LDO - Bitfield INCLPE in register CR has been renamed to BASHDN.
**     - rev. 1.2 (2014-08-01)
**         PMC - Added peripheral.
**     - rev. 1.3 (2014-08-08)
**         PMC - BITFIELD 5VT has been renamed to T5V.
**     - rev. 1.4 (2014-10-01)
**         FTM1 - Base address has been changed from 0x4003A000 to 0x40039000.
**         Other peripheries - little changes like after reset values and so on.
**     - rev. 1.5 (2014-12-12)
**         LDO - LDO_CTRM[15:9] has been changed to reserved.
**         WDOG - Interrupt name has been synchronized.
**
** ###################################################################
*/

/*!
 * @file MWPR1516.h
 * @version 1.5
 * @date 2014-12-12
 * @brief Peripheral memory map for MWPR1516
 *
 * This header file implements peripheral memory map for MWPR1516 processor.
 */


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(MCU_MWPR1516)  /* Check if memory map has not been already included */
#define MCU_MWPR1516

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error MWPR1516 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include <stdint.h>

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100u
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0005u


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
typedef enum {
  INT_Initial_Stack_Pointer    = 0,                /**< Initial Stack Pointer */
  INT_Initial_Program_Counter  = 1,                /**< Initial Program Counter */
  INT_NMI                      = 2,                /**< Non-maskable Interrupt (NMI) */
  INT_Hard_Fault               = 3,                /**< Hard Fault */
  INT_Reserved4                = 4,                /**< Reserved interrupt */
  INT_Reserved5                = 5,                /**< Reserved interrupt */
  INT_Reserved6                = 6,                /**< Reserved interrupt */
  INT_Reserved7                = 7,                /**< Reserved interrupt */
  INT_Reserved8                = 8,                /**< Reserved interrupt */
  INT_Reserved9                = 9,                /**< Reserved interrupt */
  INT_Reserved10               = 10,               /**< Reserved interrupt */
  INT_SVCall                   = 11,               /**< Supervisor call (SVCall) */
  INT_Reserved12               = 12,               /**< Reserved interrupt */
  INT_Reserved13               = 13,               /**< Reserved interrupt */
  INT_PendableSrvReq           = 14,               /**< Pendable request for system service (PendableSrvReq) */
  INT_SysTick                  = 15,               /**< System tick timer (SysTick) */
  INT_Reserved16               = 16,               /**< Reserved interrupt */
  INT_Reserved17               = 17,               /**< Reserved interrupt */
  INT_Reserved18               = 18,               /**< Reserved interrupt */
  INT_Reserved19               = 19,               /**< Reserved interrupt */
  INT_Reserved20               = 20,               /**< Reserved interrupt */
  INT_FTMRE                    = 21,               /**< Command complete and read collision */
  INT_PMC                      = 22,               /**< Low-voltage detect, low-voltage warning */
  INT_IRQ                      = 23,               /**< External Interrupt */
  INT_I2C0                     = 24,               /**< I2C0 interrupt */
  INT_Reserved25               = 25,               /**< Reserved interrupt */
  INT_Reserved26               = 26,               /**< Reserved interrupt */
  INT_Reserved27               = 27,               /**< Reserved interrupt */
  INT_UART0                    = 28,               /**< UART0 status and error */
  INT_Reserved29               = 29,               /**< Reserved interrupt */
  INT_ADC_ERR_ABORT            = 30,               /**< ADC error or conversion sequence abort */
  INT_ADC_CONV_COMPLETE        = 31,               /**< ADC conversion complete interrupt */
  INT_ACMP0                    = 32,               /**< ACMP0 interrupt */
  INT_FTM0                     = 33,               /**< FTM0 single interrupt vector for all sources */
  INT_FTM1                     = 34,               /**< FTM1 single interrupt vector for all sources */
  INT_Reserved35               = 35,               /**< Reserved interrupt */
  INT_RTC                      = 36,               /**< RTC overflow */
  INT_Reserved37               = 37,               /**< Reserved interrupt */
  INT_PIT_CH0                  = 38,               /**< PIT CH0 overflow */
  INT_PIT_CH1                  = 39,               /**< PIT CH1 overflow */
  INT_Reserved40               = 40,               /**< Reserved interrupt */
  INT_Reserved41               = 41,               /**< Reserved interrupt */
  INT_FSKDT                    = 42,               /**< FSKDT single interrupt vector for all sources */
  INT_ICS                      = 43,               /**< ICS interrupt */
  INT_WDOG                     = 44,               /**< Watchdog timeout */
  INT_Reserved45               = 45,               /**< Reserved interrupt */
  INT_CNC                      = 46,               /**< CNC single interrupt vector for all sources */
  INT_LDO                      = 47                /**< LDO single interrupt vector for all sources */
} IRQInterruptIndex;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Peripheral type defines
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_defines Peripheral type defines
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- ACMP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Peripheral ACMP
 * @{
 */

/** ACMP - Peripheral register structure */
typedef struct ACMP_MemMap {
  uint8_t CS;                                      /**< ACMP Control and Status Register, offset: 0x0 */
  uint8_t C0;                                      /**< ACMP Control Register 0, offset: 0x1 */
  uint8_t C1;                                      /**< ACMP Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< ACMP Control Register 2, offset: 0x3 */
} volatile *ACMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ACMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Accessor_Macros ACMP - Register accessor macros
 * @{
 */


/* ACMP - Register accessors */
#define ACMP_CS_REG(base)                        ((base)->CS)
#define ACMP_C0_REG(base)                        ((base)->C0)
#define ACMP_C1_REG(base)                        ((base)->C1)
#define ACMP_C2_REG(base)                        ((base)->C2)

/*!
 * @}
 */ /* end of group ACMP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ACMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Masks ACMP Register Masks
 * @{
 */

/* CS Bit Fields */
#define ACMP_CS_ACMOD_MASK                       0x3u
#define ACMP_CS_ACMOD_SHIFT                      0
#define ACMP_CS_ACMOD(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACMOD_SHIFT))&ACMP_CS_ACMOD_MASK)
#define ACMP_CS_ACOPE_MASK                       0x4u
#define ACMP_CS_ACOPE_SHIFT                      2
#define ACMP_CS_ACO_MASK                         0x8u
#define ACMP_CS_ACO_SHIFT                        3
#define ACMP_CS_ACIE_MASK                        0x10u
#define ACMP_CS_ACIE_SHIFT                       4
#define ACMP_CS_ACF_MASK                         0x20u
#define ACMP_CS_ACF_SHIFT                        5
#define ACMP_CS_HYST_MASK                        0x40u
#define ACMP_CS_HYST_SHIFT                       6
#define ACMP_CS_ACE_MASK                         0x80u
#define ACMP_CS_ACE_SHIFT                        7
/* C0 Bit Fields */
#define ACMP_C0_ACNSEL_MASK                      0x3u
#define ACMP_C0_ACNSEL_SHIFT                     0
#define ACMP_C0_ACNSEL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C0_ACNSEL_SHIFT))&ACMP_C0_ACNSEL_MASK)
#define ACMP_C0_ACPSEL_MASK                      0x30u
#define ACMP_C0_ACPSEL_SHIFT                     4
#define ACMP_C0_ACPSEL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C0_ACPSEL_SHIFT))&ACMP_C0_ACPSEL_MASK)
/* C1 Bit Fields */
#define ACMP_C1_DACVAL_MASK                      0x3Fu
#define ACMP_C1_DACVAL_SHIFT                     0
#define ACMP_C1_DACVAL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C1_DACVAL_SHIFT))&ACMP_C1_DACVAL_MASK)
#define ACMP_C1_DACREF_MASK                      0x40u
#define ACMP_C1_DACREF_SHIFT                     6
#define ACMP_C1_DACEN_MASK                       0x80u
#define ACMP_C1_DACEN_SHIFT                      7
/* C2 Bit Fields */
#define ACMP_C2_ACIPE_MASK                       0x7u
#define ACMP_C2_ACIPE_SHIFT                      0
#define ACMP_C2_ACIPE(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_C2_ACIPE_SHIFT))&ACMP_C2_ACIPE_MASK)

/*!
 * @}
 */ /* end of group ACMP_Register_Masks */


/* ACMP - Peripheral instance base addresses */
/** Peripheral ACMP0 base pointer */
#define ACMP0_BASE_PTR                           ((ACMP_MemMapPtr)0x40073000u)
/** Array initializer of ACMP peripheral base pointers */
#define ACMP_BASE_PTRS                           { ACMP0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ACMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Accessor_Macros ACMP - Register accessor macros
 * @{
 */


/* ACMP - Register instance definitions */
/* ACMP0 */
#define ACMP0_CS                                 ACMP_CS_REG(ACMP0_BASE_PTR)
#define ACMP0_C0                                 ACMP_C0_REG(ACMP0_BASE_PTR)
#define ACMP0_C1                                 ACMP_C1_REG(ACMP0_BASE_PTR)
#define ACMP0_C2                                 ACMP_C2_REG(ACMP0_BASE_PTR)

/*!
 * @}
 */ /* end of group ACMP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ACMP_Peripheral */


/* ----------------------------------------------------------------------------
   -- ADC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral ADC
 * @{
 */

/** ADC - Peripheral register structure */
typedef struct ADC_MemMap {
  uint8_t TIM;                                     /**< ADC Timing Register, offset: 0x0 */
  uint8_t STS;                                     /**< ADC Status Register, offset: 0x1 */
  uint8_t CTL1;                                    /**< ADC Control Register 1, offset: 0x2 */
  uint8_t CTL0;                                    /**< ADC Control Register 0, offset: 0x3 */
  uint8_t IE;                                      /**< ADC Interrupt Enable Register, offset: 0x4 */
  uint8_t EIE;                                     /**< ADC Error Interrupt Enable Register, offset: 0x5 */
  uint8_t FLWCTL;                                  /**< ADC Conversion Flow Control Register, offset: 0x6 */
  uint8_t FMT;                                     /**< ADC Format Register, offset: 0x7 */
  uint8_t CONIE1;                                  /**< ADC Conversion Interrupt Enable Register 1, offset: 0x8 */
  uint8_t CONIE0;                                  /**< ADC Conversion Interrupt Enable Register 0, offset: 0x9 */
  uint8_t IF;                                      /**< ADC Interrupt Flag Register, offset: 0xA */
  uint8_t EIF;                                     /**< ADC Error Interrupt Flag Register, offset: 0xB */
  uint8_t IMDRI1;                                  /**< ADC Intermediate Result Information Register 1, offset: 0xC */
  uint8_t IMDRI0;                                  /**< ADC Intermediate Result Information Register 0, offset: 0xD */
  uint8_t CONIF1;                                  /**< ADC Conversion Interrupt Flag Register 1, offset: 0xE */
  uint8_t CONIF0;                                  /**< ADC Conversion Interrupt Flag Register 0, offset: 0xF */
  uint8_t RESERVED_0[3];
  uint8_t EOLRI;                                   /**< ADC End Of List Result Information Register, offset: 0x13 */
  uint8_t RESERVED_1[1];
  uint8_t CMD2;                                    /**< ADC Command Register 2, offset: 0x15 */
  uint8_t CMD1;                                    /**< ADC Command Register 1, offset: 0x16 */
  uint8_t CMD0;                                    /**< ADC Command Register 0, offset: 0x17 */
  uint8_t RESERVED_2[4];
  uint8_t CBP2;                                    /**< ADC Command Base Pointer Register 2, offset: 0x1C */
  uint8_t CBP1;                                    /**< ADC Command Base Pointer Register 1, offset: 0x1D */
  uint8_t CBP0;                                    /**< ADC Command Base Pointer Register 0, offset: 0x1E */
  uint8_t CIDX;                                    /**< ADC Command Index Register, offset: 0x1F */
  uint8_t RBP2;                                    /**< ADC Result Base Pointer Register 2, offset: 0x20 */
  uint8_t RBP1;                                    /**< ADC Result Base Pointer Register 1, offset: 0x21 */
  uint8_t RESERVED_3[1];
  uint8_t RIDX;                                    /**< ADC Result Index Register, offset: 0x23 */
  uint8_t RESERVED_4[2];
  uint8_t CROFF1;                                  /**< ADC Command and Result Offset Register 1, offset: 0x26 */
  uint8_t CROFF0;                                  /**< ADC Command and Result Offset Register 0, offset: 0x27 */
} volatile *ADC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register accessors */
#define ADC_TIM_REG(base)                        ((base)->TIM)
#define ADC_STS_REG(base)                        ((base)->STS)
#define ADC_CTL1_REG(base)                       ((base)->CTL1)
#define ADC_CTL0_REG(base)                       ((base)->CTL0)
#define ADC_IE_REG(base)                         ((base)->IE)
#define ADC_EIE_REG(base)                        ((base)->EIE)
#define ADC_FLWCTL_REG(base)                     ((base)->FLWCTL)
#define ADC_FMT_REG(base)                        ((base)->FMT)
#define ADC_CONIE1_REG(base)                     ((base)->CONIE1)
#define ADC_CONIE0_REG(base)                     ((base)->CONIE0)
#define ADC_IF_REG(base)                         ((base)->IF)
#define ADC_EIF_REG(base)                        ((base)->EIF)
#define ADC_IMDRI1_REG(base)                     ((base)->IMDRI1)
#define ADC_IMDRI0_REG(base)                     ((base)->IMDRI0)
#define ADC_CONIF1_REG(base)                     ((base)->CONIF1)
#define ADC_CONIF0_REG(base)                     ((base)->CONIF0)
#define ADC_EOLRI_REG(base)                      ((base)->EOLRI)
#define ADC_CMD2_REG(base)                       ((base)->CMD2)
#define ADC_CMD1_REG(base)                       ((base)->CMD1)
#define ADC_CMD0_REG(base)                       ((base)->CMD0)
#define ADC_CBP2_REG(base)                       ((base)->CBP2)
#define ADC_CBP1_REG(base)                       ((base)->CBP1)
#define ADC_CBP0_REG(base)                       ((base)->CBP0)
#define ADC_CIDX_REG(base)                       ((base)->CIDX)
#define ADC_RBP2_REG(base)                       ((base)->RBP2)
#define ADC_RBP1_REG(base)                       ((base)->RBP1)
#define ADC_RIDX_REG(base)                       ((base)->RIDX)
#define ADC_CROFF1_REG(base)                     ((base)->CROFF1)
#define ADC_CROFF0_REG(base)                     ((base)->CROFF0)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/* TIM Bit Fields */
#define ADC_TIM_PRS_MASK                         0x7Fu
#define ADC_TIM_PRS_SHIFT                        0
#define ADC_TIM_PRS(x)                           (((uint8_t)(((uint8_t)(x))<<ADC_TIM_PRS_SHIFT))&ADC_TIM_PRS_MASK)
/* STS Bit Fields */
#define ADC_STS_READY_MASK                       0x8u
#define ADC_STS_READY_SHIFT                      3
#define ADC_STS_RVL_SEL_MASK                     0x40u
#define ADC_STS_RVL_SEL_SHIFT                    6
#define ADC_STS_CSL_SEL_MASK                     0x80u
#define ADC_STS_CSL_SEL_SHIFT                    7
/* CTL1 Bit Fields */
#define ADC_CTL1_AUT_RSTA_MASK                   0x10u
#define ADC_CTL1_AUT_RSTA_SHIFT                  4
#define ADC_CTL1_SMOD_ACC_MASK                   0x20u
#define ADC_CTL1_SMOD_ACC_SHIFT                  5
#define ADC_CTL1_RVL_BMOD_MASK                   0x40u
#define ADC_CTL1_RVL_BMOD_SHIFT                  6
#define ADC_CTL1_CSL_BMOD_MASK                   0x80u
#define ADC_CTL1_CSL_BMOD_SHIFT                  7
/* CTL0 Bit Fields */
#define ADC_CTL0_MOD_CFG_MASK                    0x1u
#define ADC_CTL0_MOD_CFG_SHIFT                   0
#define ADC_CTL0_STR_SEQA_MASK                   0x2u
#define ADC_CTL0_STR_SEQA_SHIFT                  1
#define ADC_CTL0_ACC_CFG_MASK                    0xCu
#define ADC_CTL0_ACC_CFG_SHIFT                   2
#define ADC_CTL0_ACC_CFG(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_CTL0_ACC_CFG_SHIFT))&ADC_CTL0_ACC_CFG_MASK)
#define ADC_CTL0_SWAI_MASK                       0x10u
#define ADC_CTL0_SWAI_SHIFT                      4
#define ADC_CTL0_FRZ_MOD_MASK                    0x20u
#define ADC_CTL0_FRZ_MOD_SHIFT                   5
#define ADC_CTL0_ADC_SR_MASK                     0x40u
#define ADC_CTL0_ADC_SR_SHIFT                    6
#define ADC_CTL0_ADC_EN_MASK                     0x80u
#define ADC_CTL0_ADC_EN_SHIFT                    7
/* IE Bit Fields */
#define ADC_IE_CONIF_OIE_MASK                    0x40u
#define ADC_IE_CONIF_OIE_SHIFT                   6
#define ADC_IE_SEQAD_IE_MASK                     0x80u
#define ADC_IE_SEQAD_IE_SHIFT                    7
/* EIE Bit Fields */
#define ADC_EIE_RA_EIE_MASK                      0x1u
#define ADC_EIE_RA_EIE_SHIFT                     0
#define ADC_EIE_LDOK_EIE_MASK                    0x2u
#define ADC_EIE_LDOK_EIE_SHIFT                   1
#define ADC_EIE_RSTAR_EIE_MASK                   0x4u
#define ADC_EIE_RSTAR_EIE_SHIFT                  2
#define ADC_EIE_TRIG_EIE_MASK                    0x8u
#define ADC_EIE_TRIG_EIE_SHIFT                   3
#define ADC_EIE_EOL_EIE_MASK                     0x20u
#define ADC_EIE_EOL_EIE_SHIFT                    5
#define ADC_EIE_CMD_EIE_MASK                     0x40u
#define ADC_EIE_CMD_EIE_SHIFT                    6
#define ADC_EIE_WA_EIE_MASK                      0x80u
#define ADC_EIE_WA_EIE_SHIFT                     7
/* FLWCTL Bit Fields */
#define ADC_FLWCTL_LDOK_MASK                     0x10u
#define ADC_FLWCTL_LDOK_SHIFT                    4
#define ADC_FLWCTL_RSTA_MASK                     0x20u
#define ADC_FLWCTL_RSTA_SHIFT                    5
#define ADC_FLWCTL_TRIG_MASK                     0x40u
#define ADC_FLWCTL_TRIG_SHIFT                    6
#define ADC_FLWCTL_SEQA_MASK                     0x80u
#define ADC_FLWCTL_SEQA_SHIFT                    7
/* FMT Bit Fields */
#define ADC_FMT_SRES_MASK                        0x7u
#define ADC_FMT_SRES_SHIFT                       0
#define ADC_FMT_SRES(x)                          (((uint8_t)(((uint8_t)(x))<<ADC_FMT_SRES_SHIFT))&ADC_FMT_SRES_MASK)
#define ADC_FMT_DJM_MASK                         0x80u
#define ADC_FMT_DJM_SHIFT                        7
/* CONIE1 Bit Fields */
#define ADC_CONIE1_EOL_IE_MASK                   0x1u
#define ADC_CONIE1_EOL_IE_SHIFT                  0
#define ADC_CONIE1_CON_IE_MASK                   0xFEu
#define ADC_CONIE1_CON_IE_SHIFT                  1
#define ADC_CONIE1_CON_IE(x)                     (((uint8_t)(((uint8_t)(x))<<ADC_CONIE1_CON_IE_SHIFT))&ADC_CONIE1_CON_IE_MASK)
/* CONIE0 Bit Fields */
#define ADC_CONIE0_CON_IE_MASK                   0xFFu
#define ADC_CONIE0_CON_IE_SHIFT                  0
#define ADC_CONIE0_CON_IE(x)                     (((uint8_t)(((uint8_t)(x))<<ADC_CONIE0_CON_IE_SHIFT))&ADC_CONIE0_CON_IE_MASK)
/* IF Bit Fields */
#define ADC_IF_CONIF_OIF_MASK                    0x40u
#define ADC_IF_CONIF_OIF_SHIFT                   6
#define ADC_IF_SEQAD_IF_MASK                     0x80u
#define ADC_IF_SEQAD_IF_SHIFT                    7
/* EIF Bit Fields */
#define ADC_EIF_RA_EIF_MASK                      0x1u
#define ADC_EIF_RA_EIF_SHIFT                     0
#define ADC_EIF_LDOK_EIF_MASK                    0x2u
#define ADC_EIF_LDOK_EIF_SHIFT                   1
#define ADC_EIF_RSTAR_EIF_MASK                   0x4u
#define ADC_EIF_RSTAR_EIF_SHIFT                  2
#define ADC_EIF_TRIG_EIF_MASK                    0x8u
#define ADC_EIF_TRIG_EIF_SHIFT                   3
#define ADC_EIF_EOL_EIF_MASK                     0x20u
#define ADC_EIF_EOL_EIF_SHIFT                    5
#define ADC_EIF_CMD_EIF_MASK                     0x40u
#define ADC_EIF_CMD_EIF_SHIFT                    6
#define ADC_EIF_WA_EIF_MASK                      0x80u
#define ADC_EIF_WA_EIF_SHIFT                     7
/* IMDRI1 Bit Fields */
#define ADC_IMDRI1_RIDX_IMD_MASK                 0x3Fu
#define ADC_IMDRI1_RIDX_IMD_SHIFT                0
#define ADC_IMDRI1_RIDX_IMD(x)                   (((uint8_t)(((uint8_t)(x))<<ADC_IMDRI1_RIDX_IMD_SHIFT))&ADC_IMDRI1_RIDX_IMD_MASK)
/* IMDRI0 Bit Fields */
#define ADC_IMDRI0_RVL_IMD_MASK                  0x40u
#define ADC_IMDRI0_RVL_IMD_SHIFT                 6
#define ADC_IMDRI0_CSL_IMD_MASK                  0x80u
#define ADC_IMDRI0_CSL_IMD_SHIFT                 7
/* CONIF1 Bit Fields */
#define ADC_CONIF1_EOL_IF_MASK                   0x1u
#define ADC_CONIF1_EOL_IF_SHIFT                  0
#define ADC_CONIF1_CON_IF_MASK                   0xFEu
#define ADC_CONIF1_CON_IF_SHIFT                  1
#define ADC_CONIF1_CON_IF(x)                     (((uint8_t)(((uint8_t)(x))<<ADC_CONIF1_CON_IF_SHIFT))&ADC_CONIF1_CON_IF_MASK)
/* CONIF0 Bit Fields */
#define ADC_CONIF0_CON_IF_MASK                   0xFFu
#define ADC_CONIF0_CON_IF_SHIFT                  0
#define ADC_CONIF0_CON_IF(x)                     (((uint8_t)(((uint8_t)(x))<<ADC_CONIF0_CON_IF_SHIFT))&ADC_CONIF0_CON_IF_MASK)
/* EOLRI Bit Fields */
#define ADC_EOLRI_RVL_EOL_MASK                   0x40u
#define ADC_EOLRI_RVL_EOL_SHIFT                  6
#define ADC_EOLRI_CSL_EOL_MASK                   0x80u
#define ADC_EOLRI_CSL_EOL_SHIFT                  7
/* CMD2 Bit Fields */
#define ADC_CMD2_SMP_MASK                        0xF8u
#define ADC_CMD2_SMP_SHIFT                       3
#define ADC_CMD2_SMP(x)                          (((uint8_t)(((uint8_t)(x))<<ADC_CMD2_SMP_SHIFT))&ADC_CMD2_SMP_MASK)
/* CMD1 Bit Fields */
#define ADC_CMD1_CH_SEL_MASK                     0x3Fu
#define ADC_CMD1_CH_SEL_SHIFT                    0
#define ADC_CMD1_CH_SEL(x)                       (((uint8_t)(((uint8_t)(x))<<ADC_CMD1_CH_SEL_SHIFT))&ADC_CMD1_CH_SEL_MASK)
#define ADC_CMD1_INTFLG_SEL_MASK                 0x40u
#define ADC_CMD1_INTFLG_SEL_SHIFT                6
#define ADC_CMD1_VRH_SEL_MASK                    0x80u
#define ADC_CMD1_VRH_SEL_SHIFT                   7
/* CMD0 Bit Fields */
#define ADC_CMD0_INTFLG_SEL_MASK                 0xFu
#define ADC_CMD0_INTFLG_SEL_SHIFT                0
#define ADC_CMD0_INTFLG_SEL(x)                   (((uint8_t)(((uint8_t)(x))<<ADC_CMD0_INTFLG_SEL_SHIFT))&ADC_CMD0_INTFLG_SEL_MASK)
#define ADC_CMD0_CMD_SEL_MASK                    0xC0u
#define ADC_CMD0_CMD_SEL_SHIFT                   6
#define ADC_CMD0_CMD_SEL(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_CMD0_CMD_SEL_SHIFT))&ADC_CMD0_CMD_SEL_MASK)
/* CBP2 Bit Fields */
#define ADC_CBP2_CMD_PTR_MASK                    0xFCu
#define ADC_CBP2_CMD_PTR_SHIFT                   2
#define ADC_CBP2_CMD_PTR(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_CBP2_CMD_PTR_SHIFT))&ADC_CBP2_CMD_PTR_MASK)
/* CBP1 Bit Fields */
#define ADC_CBP1_CMD_PTR_MASK                    0xFFu
#define ADC_CBP1_CMD_PTR_SHIFT                   0
#define ADC_CBP1_CMD_PTR(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_CBP1_CMD_PTR_SHIFT))&ADC_CBP1_CMD_PTR_MASK)
/* CBP0 Bit Fields */
#define ADC_CBP0_CMD_PTR_MASK                    0x80u
#define ADC_CBP0_CMD_PTR_SHIFT                   7
/* CIDX Bit Fields */
#define ADC_CIDX_CMD_IDX_MASK                    0x3Fu
#define ADC_CIDX_CMD_IDX_SHIFT                   0
#define ADC_CIDX_CMD_IDX(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_CIDX_CMD_IDX_SHIFT))&ADC_CIDX_CMD_IDX_MASK)
/* RBP2 Bit Fields */
#define ADC_RBP2_RES_PTR_MASK                    0xFCu
#define ADC_RBP2_RES_PTR_SHIFT                   2
#define ADC_RBP2_RES_PTR(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_RBP2_RES_PTR_SHIFT))&ADC_RBP2_RES_PTR_MASK)
/* RBP1 Bit Fields */
#define ADC_RBP1_RES_PTR_MASK                    0xFFu
#define ADC_RBP1_RES_PTR_SHIFT                   0
#define ADC_RBP1_RES_PTR(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_RBP1_RES_PTR_SHIFT))&ADC_RBP1_RES_PTR_MASK)
/* RIDX Bit Fields */
#define ADC_RIDX_RES_IDX_MASK                    0x3Fu
#define ADC_RIDX_RES_IDX_SHIFT                   0
#define ADC_RIDX_RES_IDX(x)                      (((uint8_t)(((uint8_t)(x))<<ADC_RIDX_RES_IDX_SHIFT))&ADC_RIDX_RES_IDX_MASK)
/* CROFF1 Bit Fields */
#define ADC_CROFF1_CMDRES_OFF1_MASK              0x7Fu
#define ADC_CROFF1_CMDRES_OFF1_SHIFT             0
#define ADC_CROFF1_CMDRES_OFF1(x)                (((uint8_t)(((uint8_t)(x))<<ADC_CROFF1_CMDRES_OFF1_SHIFT))&ADC_CROFF1_CMDRES_OFF1_MASK)
/* CROFF0 Bit Fields */
#define ADC_CROFF0_CMDRES_OFF0_MASK              0x7Fu
#define ADC_CROFF0_CMDRES_OFF0_SHIFT             0
#define ADC_CROFF0_CMDRES_OFF0(x)                (((uint8_t)(((uint8_t)(x))<<ADC_CROFF0_CMDRES_OFF0_SHIFT))&ADC_CROFF0_CMDRES_OFF0_MASK)

/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC base pointer */
#define ADC_BASE_PTR                             ((ADC_MemMapPtr)0x4003B000u)
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC */
#define ADC_TIM                                  ADC_TIM_REG(ADC_BASE_PTR)
#define ADC_STS                                  ADC_STS_REG(ADC_BASE_PTR)
#define ADC_CTL1                                 ADC_CTL1_REG(ADC_BASE_PTR)
#define ADC_CTL0                                 ADC_CTL0_REG(ADC_BASE_PTR)
#define ADC_IE                                   ADC_IE_REG(ADC_BASE_PTR)
#define ADC_EIE                                  ADC_EIE_REG(ADC_BASE_PTR)
#define ADC_FLWCTL                               ADC_FLWCTL_REG(ADC_BASE_PTR)
#define ADC_FMT                                  ADC_FMT_REG(ADC_BASE_PTR)
#define ADC_CONIE1                               ADC_CONIE1_REG(ADC_BASE_PTR)
#define ADC_CONIE0                               ADC_CONIE0_REG(ADC_BASE_PTR)
#define ADC_IF                                   ADC_IF_REG(ADC_BASE_PTR)
#define ADC_EIF                                  ADC_EIF_REG(ADC_BASE_PTR)
#define ADC_IMDRI1                               ADC_IMDRI1_REG(ADC_BASE_PTR)
#define ADC_IMDRI0                               ADC_IMDRI0_REG(ADC_BASE_PTR)
#define ADC_CONIF1                               ADC_CONIF1_REG(ADC_BASE_PTR)
#define ADC_CONIF0                               ADC_CONIF0_REG(ADC_BASE_PTR)
#define ADC_EOLRI                                ADC_EOLRI_REG(ADC_BASE_PTR)
#define ADC_CMD2                                 ADC_CMD2_REG(ADC_BASE_PTR)
#define ADC_CMD1                                 ADC_CMD1_REG(ADC_BASE_PTR)
#define ADC_CMD0                                 ADC_CMD0_REG(ADC_BASE_PTR)
#define ADC_CBP2                                 ADC_CBP2_REG(ADC_BASE_PTR)
#define ADC_CBP1                                 ADC_CBP1_REG(ADC_BASE_PTR)
#define ADC_CBP0                                 ADC_CBP0_REG(ADC_BASE_PTR)
#define ADC_CIDX                                 ADC_CIDX_REG(ADC_BASE_PTR)
#define ADC_RBP2                                 ADC_RBP2_REG(ADC_BASE_PTR)
#define ADC_RBP1                                 ADC_RBP1_REG(ADC_BASE_PTR)
#define ADC_RIDX                                 ADC_RIDX_REG(ADC_BASE_PTR)
#define ADC_CROFF1                               ADC_CROFF1_REG(ADC_BASE_PTR)
#define ADC_CROFF0                               ADC_CROFF0_REG(ADC_BASE_PTR)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ADC_Peripheral */


/* ----------------------------------------------------------------------------
   -- BP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Peripheral BP
 * @{
 */

/** BP - Peripheral register structure */
typedef struct BP_MemMap {
  uint32_t CTRL;                                   /**< FlashPatch Control Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  uint32_t COMP[2];                                /**< FlashPatch Comparator Register 0..FlashPatch Comparator Register 1, array offset: 0x8, array step: 0x4 */
  uint8_t RESERVED_1[4032];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *BP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register accessors */
#define BP_CTRL_REG(base)                        ((base)->CTRL)
#define BP_COMP_REG(base,index)                  ((base)->COMP[index])
#define BP_PID4_REG(base)                        ((base)->PID4)
#define BP_PID5_REG(base)                        ((base)->PID5)
#define BP_PID6_REG(base)                        ((base)->PID6)
#define BP_PID7_REG(base)                        ((base)->PID7)
#define BP_PID0_REG(base)                        ((base)->PID0)
#define BP_PID1_REG(base)                        ((base)->PID1)
#define BP_PID2_REG(base)                        ((base)->PID2)
#define BP_PID3_REG(base)                        ((base)->PID3)
#define BP_CID0_REG(base)                        ((base)->CID0)
#define BP_CID1_REG(base)                        ((base)->CID1)
#define BP_CID2_REG(base)                        ((base)->CID2)
#define BP_CID3_REG(base)                        ((base)->CID3)

/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- BP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Masks BP Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group BP_Register_Masks */


/* BP - Peripheral instance base addresses */
/** Peripheral BP base pointer */
#define BP_BASE_PTR                              ((BP_MemMapPtr)0xE0002000u)
/** Array initializer of BP peripheral base pointers */
#define BP_BASE_PTRS                             { BP_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register instance definitions */
/* BP */
#define BP_CTRL                                  BP_CTRL_REG(BP_BASE_PTR)
#define BP_COMP0                                 BP_COMP_REG(BP_BASE_PTR,0)
#define BP_COMP1                                 BP_COMP_REG(BP_BASE_PTR,1)
#define BP_PID4                                  BP_PID4_REG(BP_BASE_PTR)
#define BP_PID5                                  BP_PID5_REG(BP_BASE_PTR)
#define BP_PID6                                  BP_PID6_REG(BP_BASE_PTR)
#define BP_PID7                                  BP_PID7_REG(BP_BASE_PTR)
#define BP_PID0                                  BP_PID0_REG(BP_BASE_PTR)
#define BP_PID1                                  BP_PID1_REG(BP_BASE_PTR)
#define BP_PID2                                  BP_PID2_REG(BP_BASE_PTR)
#define BP_PID3                                  BP_PID3_REG(BP_BASE_PTR)
#define BP_CID0                                  BP_CID0_REG(BP_BASE_PTR)
#define BP_CID1                                  BP_CID1_REG(BP_BASE_PTR)
#define BP_CID2                                  BP_CID2_REG(BP_BASE_PTR)
#define BP_CID3                                  BP_CID3_REG(BP_BASE_PTR)

/* BP - Register array accessors */
#define BP_COMP(index)                           BP_COMP_REG(BP_BASE_PTR,index)

/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group BP_Peripheral */


/* ----------------------------------------------------------------------------
   -- CNC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CNC_Peripheral CNC
 * @{
 */

/** CNC - Peripheral register structure */
typedef struct CNC_MemMap {
  uint16_t CR;                                     /**< Control Register, offset: 0x0 */
  uint16_t ANACFG1;                                /**< Analog Configuration Register 1, offset: 0x2 */
  uint16_t ANACFG2;                                /**< Analog Configuration Register 2, offset: 0x4 */
  uint16_t STAS;                                   /**< Status Register, offset: 0x6 */
  uint16_t VRECOE;                                 /**< VREC Overvoltage clamp drive Enable Register, offset: 0x8 */
  uint16_t VRECFLTC;                               /**< VREC Filter Control Register, offset: 0xA */
  uint16_t VADFLTC;                                /**< AD_IN Filter Control Register, offset: 0xC */
} volatile *CNC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CNC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CNC_Register_Accessor_Macros CNC - Register accessor macros
 * @{
 */


/* CNC - Register accessors */
#define CNC_CR_REG(base)                         ((base)->CR)
#define CNC_ANACFG1_REG(base)                    ((base)->ANACFG1)
#define CNC_ANACFG2_REG(base)                    ((base)->ANACFG2)
#define CNC_STAS_REG(base)                       ((base)->STAS)
#define CNC_VRECOE_REG(base)                     ((base)->VRECOE)
#define CNC_VRECFLTC_REG(base)                   ((base)->VRECFLTC)
#define CNC_VADFLTC_REG(base)                    ((base)->VADFLTC)

/*!
 * @}
 */ /* end of group CNC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CNC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CNC_Register_Masks CNC Register Masks
 * @{
 */

/* CR Bit Fields */
#define CNC_CR_SWCLPD_MASK                       0x1u
#define CNC_CR_SWCLPD_SHIFT                      0
#define CNC_CR_CLPDPE_MASK                       0x20u
#define CNC_CR_CLPDPE_SHIFT                      5
#define CNC_CR_EXTCLPDE_MASK                     0x40u
#define CNC_CR_EXTCLPDE_SHIFT                    6
#define CNC_CR_VRECDE_MASK                       0x80u
#define CNC_CR_VRECDE_SHIFT                      7
#define CNC_CR_VADVDIE_MASK                      0x100u
#define CNC_CR_VADVDIE_SHIFT                     8
#define CNC_CR_SWADS_MASK                        0x200u
#define CNC_CR_SWADS_SHIFT                       9
#define CNC_CR_ADE_MASK                          0x400u
#define CNC_CR_ADE_SHIFT                         10
#define CNC_CR_LVIE_MASK                         0x1000u
#define CNC_CR_LVIE_SHIFT                        12
#define CNC_CR_OVIE_MASK                         0x2000u
#define CNC_CR_OVIE_SHIFT                        13
#define CNC_CR_ADANE_MASK                        0x4000u
#define CNC_CR_ADANE_SHIFT                       14
#define CNC_CR_ZCDE_MASK                         0x8000u
#define CNC_CR_ZCDE_SHIFT                        15
/* ANACFG1 Bit Fields */
#define CNC_ANACFG1_VADDIVOE_MASK                0x1u
#define CNC_ANACFG1_VADDIVOE_SHIFT               0
#define CNC_ANACFG1_VADLVTRM_MASK                0x6u
#define CNC_ANACFG1_VADLVTRM_SHIFT               1
#define CNC_ANACFG1_VADLVTRM(x)                  (((uint16_t)(((uint16_t)(x))<<CNC_ANACFG1_VADLVTRM_SHIFT))&CNC_ANACFG1_VADLVTRM_MASK)
#define CNC_ANACFG1_VADOVTRM_MASK                0x18u
#define CNC_ANACFG1_VADOVTRM_SHIFT               3
#define CNC_ANACFG1_VADOVTRM(x)                  (((uint16_t)(((uint16_t)(x))<<CNC_ANACFG1_VADOVTRM_SHIFT))&CNC_ANACFG1_VADOVTRM_MASK)
#define CNC_ANACFG1_VRECOVLVL_MASK               0x1800u
#define CNC_ANACFG1_VRECOVLVL_SHIFT              11
#define CNC_ANACFG1_VRECOVLVL(x)                 (((uint16_t)(((uint16_t)(x))<<CNC_ANACFG1_VRECOVLVL_SHIFT))&CNC_ANACFG1_VRECOVLVL_MASK)
#define CNC_ANACFG1_AC1DIVOE_MASK                0x2000u
#define CNC_ANACFG1_AC1DIVOE_SHIFT               13
#define CNC_ANACFG1_ZCDHYST_MASK                 0xC000u
#define CNC_ANACFG1_ZCDHYST_SHIFT                14
#define CNC_ANACFG1_ZCDHYST(x)                   (((uint16_t)(((uint16_t)(x))<<CNC_ANACFG1_ZCDHYST_SHIFT))&CNC_ANACFG1_ZCDHYST_MASK)
/* ANACFG2 Bit Fields */
#define CNC_ANACFG2_ACDIV_MASK                   0xFu
#define CNC_ANACFG2_ACDIV_SHIFT                  0
#define CNC_ANACFG2_ACDIV(x)                     (((uint16_t)(((uint16_t)(x))<<CNC_ANACFG2_ACDIV_SHIFT))&CNC_ANACFG2_ACDIV_MASK)
#define CNC_ANACFG2_ACFLTC_MASK                  0x30u
#define CNC_ANACFG2_ACFLTC_SHIFT                 4
#define CNC_ANACFG2_ACFLTC(x)                    (((uint16_t)(((uint16_t)(x))<<CNC_ANACFG2_ACFLTC_SHIFT))&CNC_ANACFG2_ACFLTC_MASK)
#define CNC_ANACFG2_ACFLTE_MASK                  0x40u
#define CNC_ANACFG2_ACFLTE_SHIFT                 6
#define CNC_ANACFG2_BIAE_MASK                    0x80u
#define CNC_ANACFG2_BIAE_SHIFT                   7
#define CNC_ANACFG2_VAOHY20_MASK                 0x100u
#define CNC_ANACFG2_VAOHY20_SHIFT                8
#define CNC_ANACFG2_VAOHY40_MASK                 0x200u
#define CNC_ANACFG2_VAOHY40_SHIFT                9
/* STAS Bit Fields */
#define CNC_STAS_FSKO_MASK                       0x1u
#define CNC_STAS_FSKO_SHIFT                      0
#define CNC_STAS_VADOV5P5_MASK                   0x2u
#define CNC_STAS_VADOV5P5_SHIFT                  1
#define CNC_STAS_VADOK4P5_MASK                   0x4u
#define CNC_STAS_VADOK4P5_SHIFT                  2
#define CNC_STAS_VADCHGF_MASK                    0x8u
#define CNC_STAS_VADCHGF_SHIFT                   3
#define CNC_STAS_VRECOVF_MASK                    0x10u
#define CNC_STAS_VRECOVF_SHIFT                   4
#define CNC_STAS_VRECLVF_MASK                    0x20u
#define CNC_STAS_VRECLVF_SHIFT                   5
#define CNC_STAS_VRECOVS_MASK                    0x40u
#define CNC_STAS_VRECOVS_SHIFT                   6
#define CNC_STAS_VRECLVS_MASK                    0x80u
#define CNC_STAS_VRECLVS_SHIFT                   7
/* VRECOE Bit Fields */
#define CNC_VRECOE_VRECOVE_MASK                  0x1u
#define CNC_VRECOE_VRECOVE_SHIFT                 0
/* VRECFLTC Bit Fields */
#define CNC_VRECFLTC_CNT_MASK                    0xFFFFu
#define CNC_VRECFLTC_CNT_SHIFT                   0
#define CNC_VRECFLTC_CNT(x)                      (((uint16_t)(((uint16_t)(x))<<CNC_VRECFLTC_CNT_SHIFT))&CNC_VRECFLTC_CNT_MASK)
/* VADFLTC Bit Fields */
#define CNC_VADFLTC_CNT_MASK                     0xFFFFu
#define CNC_VADFLTC_CNT_SHIFT                    0
#define CNC_VADFLTC_CNT(x)                       (((uint16_t)(((uint16_t)(x))<<CNC_VADFLTC_CNT_SHIFT))&CNC_VADFLTC_CNT_MASK)

/*!
 * @}
 */ /* end of group CNC_Register_Masks */


/* CNC - Peripheral instance base addresses */
/** Peripheral CNC base pointer */
#define CNC_BASE_PTR                             ((CNC_MemMapPtr)0x4006E000u)
/** Array initializer of CNC peripheral base pointers */
#define CNC_BASE_PTRS                            { CNC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- CNC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CNC_Register_Accessor_Macros CNC - Register accessor macros
 * @{
 */


/* CNC - Register instance definitions */
/* CNC */
#define CNC_CR                                   CNC_CR_REG(CNC_BASE_PTR)
#define CNC_ANACFG1                              CNC_ANACFG1_REG(CNC_BASE_PTR)
#define CNC_ANACFG2                              CNC_ANACFG2_REG(CNC_BASE_PTR)
#define CNC_STAS                                 CNC_STAS_REG(CNC_BASE_PTR)
#define CNC_VRECOE                               CNC_VRECOE_REG(CNC_BASE_PTR)
#define CNC_VRECFLTC                             CNC_VRECFLTC_REG(CNC_BASE_PTR)
#define CNC_VADFLTC                              CNC_VADFLTC_REG(CNC_BASE_PTR)

/*!
 * @}
 */ /* end of group CNC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CNC_Peripheral */


/* ----------------------------------------------------------------------------
   -- CoreDebug
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Peripheral CoreDebug
 * @{
 */

/** CoreDebug - Peripheral register structure */
typedef struct CoreDebug_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t base_DHCSR_Read;                        /**< Debug Halting Control and Status Register, offset: 0x0 */
    uint32_t base_DHCSR_Write;                       /**< Debug Halting Control and Status Register, offset: 0x0 */
  };
  uint32_t base_DCRSR;                             /**< Debug Core Register Selector Register, offset: 0x4 */
  uint32_t base_DCRDR;                             /**< Debug Core Register Data Register, offset: 0x8 */
  uint32_t base_DEMCR;                             /**< Debug Exception and Monitor Control Register, offset: 0xC */
} volatile *CoreDebug_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register accessors */
#define CoreDebug_base_DHCSR_Read_REG(base)      ((base)->base_DHCSR_Read)
#define CoreDebug_base_DHCSR_Write_REG(base)     ((base)->base_DHCSR_Write)
#define CoreDebug_base_DCRSR_REG(base)           ((base)->base_DCRSR)
#define CoreDebug_base_DCRDR_REG(base)           ((base)->base_DCRDR)
#define CoreDebug_base_DEMCR_REG(base)           ((base)->base_DEMCR)

/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CoreDebug Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Masks CoreDebug Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group CoreDebug_Register_Masks */


/* CoreDebug - Peripheral instance base addresses */
/** Peripheral CoreDebug base pointer */
#define CoreDebug_BASE_PTR                       ((CoreDebug_MemMapPtr)0xE000EDF0u)
/** Array initializer of CoreDebug peripheral base pointers */
#define CoreDebug_BASE_PTRS                      { CoreDebug_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register instance definitions */
/* CoreDebug */
#define DHCSR_Read                               CoreDebug_base_DHCSR_Read_REG(CoreDebug_BASE_PTR)
#define DHCSR_Write                              CoreDebug_base_DHCSR_Write_REG(CoreDebug_BASE_PTR)
#define DCRSR                                    CoreDebug_base_DCRSR_REG(CoreDebug_BASE_PTR)
#define DCRDR                                    CoreDebug_base_DCRDR_REG(CoreDebug_BASE_PTR)
#define DEMCR                                    CoreDebug_base_DEMCR_REG(CoreDebug_BASE_PTR)

/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CoreDebug_Peripheral */


/* ----------------------------------------------------------------------------
   -- DWT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Peripheral DWT
 * @{
 */

/** DWT - Peripheral register structure */
typedef struct DWT_MemMap {
  uint32_t CTRL;                                   /**< Control Register, offset: 0x0 */
  uint8_t RESERVED_0[24];
  uint32_t PCSR;                                   /**< Program Counter Sample Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< Comparator Register 0..Comparator Register 1, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< Mask Register 0..Mask Register 1, array offset: 0x24, array step: 0x10 */
    uint32_t FUNCTION;                               /**< Function Register 0..Function Register 1, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
} volatile *DWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register accessors */
#define DWT_CTRL_REG(base)                       ((base)->CTRL)
#define DWT_PCSR_REG(base)                       ((base)->PCSR)
#define DWT_COMP_REG(base,index)                 ((base)->COMPARATOR[index].COMP)
#define DWT_MASK_REG(base,index)                 ((base)->COMPARATOR[index].MASK)
#define DWT_FUNCTION_REG(base,index)             ((base)->COMPARATOR[index].FUNCTION)

/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Masks DWT Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group DWT_Register_Masks */


/* DWT - Peripheral instance base addresses */
/** Peripheral DWT base pointer */
#define DWT_BASE_PTR                             ((DWT_MemMapPtr)0xE0001000u)
/** Array initializer of DWT peripheral base pointers */
#define DWT_BASE_PTRS                            { DWT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register instance definitions */
/* DWT */
#define DWT_CTRL                                 DWT_CTRL_REG(DWT_BASE_PTR)
#define DWT_PCSR                                 DWT_PCSR_REG(DWT_BASE_PTR)
#define DWT_COMP0                                DWT_COMP_REG(DWT_BASE_PTR,0)
#define DWT_MASK0                                DWT_MASK_REG(DWT_BASE_PTR,0)
#define DWT_FUNCTION0                            DWT_FUNCTION_REG(DWT_BASE_PTR,0)
#define DWT_COMP1                                DWT_COMP_REG(DWT_BASE_PTR,1)
#define DWT_MASK1                                DWT_MASK_REG(DWT_BASE_PTR,1)
#define DWT_FUNCTION1                            DWT_FUNCTION_REG(DWT_BASE_PTR,1)

/* DWT - Register array accessors */
#define DWT_COMP(index)                          DWT_COMP_REG(DWT_BASE_PTR,index)
#define DWT_MASK(index)                          DWT_MASK_REG(DWT_BASE_PTR,index)
#define DWT_FUNCTION(index)                      DWT_FUNCTION_REG(DWT_BASE_PTR,index)

/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- FSKDT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FSKDT_Peripheral FSKDT
 * @{
 */

/** FSKDT - Peripheral register structure */
typedef struct FSKDT_MemMap {
  uint16_t CR;                                     /**< Control Register, offset: 0x0 */
  uint16_t SR;                                     /**< Status Register, offset: 0x2 */
  uint16_t PH0;                                    /**< Phase0 counter value, offset: 0x4 */
  uint16_t PH1;                                    /**< Phase1 counter value, offset: 0x6 */
  uint16_t PH2;                                    /**< Phase2 counter value, offset: 0x8 */
  uint16_t CURPOS;                                 /**< Current Position Register, offset: 0xA */
  uint16_t OPCTH;                                  /**< Out-of-Period Counter Threshold Register, offset: 0xC */
  uint16_t ERRTH;                                  /**< Error Threshold Register, offset: 0xE */
  uint16_t DATA;                                   /**< Demodulation Data Register, offset: 0x10 */
  uint16_t DSR;                                    /**< Demodulation Data Status Register, offset: 0x12 */
} volatile *FSKDT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FSKDT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FSKDT_Register_Accessor_Macros FSKDT - Register accessor macros
 * @{
 */


/* FSKDT - Register accessors */
#define FSKDT_CR_REG(base)                       ((base)->CR)
#define FSKDT_SR_REG(base)                       ((base)->SR)
#define FSKDT_PH0_REG(base)                      ((base)->PH0)
#define FSKDT_PH1_REG(base)                      ((base)->PH1)
#define FSKDT_PH2_REG(base)                      ((base)->PH2)
#define FSKDT_CURPOS_REG(base)                   ((base)->CURPOS)
#define FSKDT_OPCTH_REG(base)                    ((base)->OPCTH)
#define FSKDT_ERRTH_REG(base)                    ((base)->ERRTH)
#define FSKDT_DATA_REG(base)                     ((base)->DATA)
#define FSKDT_DSR_REG(base)                      ((base)->DSR)

/*!
 * @}
 */ /* end of group FSKDT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FSKDT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FSKDT_Register_Masks FSKDT Register Masks
 * @{
 */

/* CR Bit Fields */
#define FSKDT_CR_OPIE_MASK                       0x1u
#define FSKDT_CR_OPIE_SHIFT                      0
#define FSKDT_CR_EOSMIE_MASK                     0x2u
#define FSKDT_CR_EOSMIE_SHIFT                    1
#define FSKDT_CR_EOAMIE_MASK                     0x4u
#define FSKDT_CR_EOAMIE_SHIFT                    2
#define FSKDT_CR_ERRIE_MASK                      0x8u
#define FSKDT_CR_ERRIE_SHIFT                     3
#define FSKDT_CR_SWRST_MASK                      0x1000u
#define FSKDT_CR_SWRST_SHIFT                     12
#define FSKDT_CR_NST_MASK                        0x6000u
#define FSKDT_CR_NST_SHIFT                       13
#define FSKDT_CR_NST(x)                          (((uint16_t)(((uint16_t)(x))<<FSKDT_CR_NST_SHIFT))&FSKDT_CR_NST_MASK)
#define FSKDT_CR_EN_MASK                         0x8000u
#define FSKDT_CR_EN_SHIFT                        15
/* SR Bit Fields */
#define FSKDT_SR_OPF_MASK                        0x1u
#define FSKDT_SR_OPF_SHIFT                       0
#define FSKDT_SR_EOSMF_MASK                      0x2u
#define FSKDT_SR_EOSMF_SHIFT                     1
#define FSKDT_SR_EOAMF_MASK                      0x4u
#define FSKDT_SR_EOAMF_SHIFT                     2
#define FSKDT_SR_ERRF_MASK                       0x8u
#define FSKDT_SR_ERRF_SHIFT                      3
/* PH0 Bit Fields */
#define FSKDT_PH0_PH0CNTR_MASK                   0xFFFFu
#define FSKDT_PH0_PH0CNTR_SHIFT                  0
#define FSKDT_PH0_PH0CNTR(x)                     (((uint16_t)(((uint16_t)(x))<<FSKDT_PH0_PH0CNTR_SHIFT))&FSKDT_PH0_PH0CNTR_MASK)
/* PH1 Bit Fields */
#define FSKDT_PH1_PH1CNTR_MASK                   0xFFFFu
#define FSKDT_PH1_PH1CNTR_SHIFT                  0
#define FSKDT_PH1_PH1CNTR(x)                     (((uint16_t)(((uint16_t)(x))<<FSKDT_PH1_PH1CNTR_SHIFT))&FSKDT_PH1_PH1CNTR_MASK)
/* PH2 Bit Fields */
#define FSKDT_PH2_PH2CNTR_MASK                   0xFFFFu
#define FSKDT_PH2_PH2CNTR_SHIFT                  0
#define FSKDT_PH2_PH2CNTR(x)                     (((uint16_t)(((uint16_t)(x))<<FSKDT_PH2_PH2CNTR_SHIFT))&FSKDT_PH2_PH2CNTR_MASK)
/* CURPOS Bit Fields */
#define FSKDT_CURPOS_CURPOS_MASK                 0xFFFFu
#define FSKDT_CURPOS_CURPOS_SHIFT                0
#define FSKDT_CURPOS_CURPOS(x)                   (((uint16_t)(((uint16_t)(x))<<FSKDT_CURPOS_CURPOS_SHIFT))&FSKDT_CURPOS_CURPOS_MASK)
/* OPCTH Bit Fields */
#define FSKDT_OPCTH_OPCTH_MASK                   0x3FFu
#define FSKDT_OPCTH_OPCTH_SHIFT                  0
#define FSKDT_OPCTH_OPCTH(x)                     (((uint16_t)(((uint16_t)(x))<<FSKDT_OPCTH_OPCTH_SHIFT))&FSKDT_OPCTH_OPCTH_MASK)
/* ERRTH Bit Fields */
#define FSKDT_ERRTH_LOLMT_MASK                   0x3Fu
#define FSKDT_ERRTH_LOLMT_SHIFT                  0
#define FSKDT_ERRTH_LOLMT(x)                     (((uint16_t)(((uint16_t)(x))<<FSKDT_ERRTH_LOLMT_SHIFT))&FSKDT_ERRTH_LOLMT_MASK)
#define FSKDT_ERRTH_HILMT_MASK                   0xFFC0u
#define FSKDT_ERRTH_HILMT_SHIFT                  6
#define FSKDT_ERRTH_HILMT(x)                     (((uint16_t)(((uint16_t)(x))<<FSKDT_ERRTH_HILMT_SHIFT))&FSKDT_ERRTH_HILMT_MASK)
/* DATA Bit Fields */
#define FSKDT_DATA_DATA_MASK                     0x7FFu
#define FSKDT_DATA_DATA_SHIFT                    0
#define FSKDT_DATA_DATA(x)                       (((uint16_t)(((uint16_t)(x))<<FSKDT_DATA_DATA_SHIFT))&FSKDT_DATA_DATA_MASK)
#define FSKDT_DATA_BM_MASK                       0x2000u
#define FSKDT_DATA_BM_SHIFT                      13
#define FSKDT_DATA_WBNBIE_MASK                   0x4000u
#define FSKDT_DATA_WBNBIE_SHIFT                  14
#define FSKDT_DATA_NBIE_MASK                     0x8000u
#define FSKDT_DATA_NBIE_SHIFT                    15
/* DSR Bit Fields */
#define FSKDT_DSR_TCNTD_MASK                     0xFu
#define FSKDT_DSR_TCNTD_SHIFT                    0
#define FSKDT_DSR_TCNTD(x)                       (((uint16_t)(((uint16_t)(x))<<FSKDT_DSR_TCNTD_SHIFT))&FSKDT_DSR_TCNTD_MASK)
#define FSKDT_DSR_WBNF_MASK                      0x4000u
#define FSKDT_DSR_WBNF_SHIFT                     14
#define FSKDT_DSR_NBF_MASK                       0x8000u
#define FSKDT_DSR_NBF_SHIFT                      15

/*!
 * @}
 */ /* end of group FSKDT_Register_Masks */


/* FSKDT - Peripheral instance base addresses */
/** Peripheral FSKDT base pointer */
#define FSKDT_BASE_PTR                           ((FSKDT_MemMapPtr)0x40034000u)
/** Array initializer of FSKDT peripheral base pointers */
#define FSKDT_BASE_PTRS                          { FSKDT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FSKDT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FSKDT_Register_Accessor_Macros FSKDT - Register accessor macros
 * @{
 */


/* FSKDT - Register instance definitions */
/* FSKDT */
#define FSKDT_CR                                 FSKDT_CR_REG(FSKDT_BASE_PTR)
#define FSKDT_SR                                 FSKDT_SR_REG(FSKDT_BASE_PTR)
#define FSKDT_PH0                                FSKDT_PH0_REG(FSKDT_BASE_PTR)
#define FSKDT_PH1                                FSKDT_PH1_REG(FSKDT_BASE_PTR)
#define FSKDT_PH2                                FSKDT_PH2_REG(FSKDT_BASE_PTR)
#define FSKDT_CURPOS                             FSKDT_CURPOS_REG(FSKDT_BASE_PTR)
#define FSKDT_OPCTH                              FSKDT_OPCTH_REG(FSKDT_BASE_PTR)
#define FSKDT_ERRTH                              FSKDT_ERRTH_REG(FSKDT_BASE_PTR)
#define FSKDT_DATA                               FSKDT_DATA_REG(FSKDT_BASE_PTR)
#define FSKDT_DSR                                FSKDT_DSR_REG(FSKDT_BASE_PTR)

/*!
 * @}
 */ /* end of group FSKDT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FSKDT_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Peripheral FTM
 * @{
 */

/** FTM - Peripheral register structure */
typedef struct FTM_MemMap {
  uint32_t SC;                                     /**< Status And Control, offset: 0x0 */
  uint32_t CNT;                                    /**< Counter, offset: 0x4 */
  uint32_t MOD;                                    /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    uint32_t CnSC;                                   /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
    uint32_t CnV;                                    /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
  } CONTROLS[2];
  uint8_t RESERVED_0[80];
  uint32_t EXTTRIG;                                /**< FTM External Trigger, offset: 0x6C */
} volatile *FTM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register accessors */
#define FTM_SC_REG(base)                         ((base)->SC)
#define FTM_CNT_REG(base)                        ((base)->CNT)
#define FTM_MOD_REG(base)                        ((base)->MOD)
#define FTM_CnSC_REG(base,index)                 ((base)->CONTROLS[index].CnSC)
#define FTM_CnV_REG(base,index)                  ((base)->CONTROLS[index].CnV)
#define FTM_EXTTRIG_REG(base)                    ((base)->EXTTRIG)

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Masks FTM Register Masks
 * @{
 */

/* SC Bit Fields */
#define FTM_SC_PS_MASK                           0x7u
#define FTM_SC_PS_SHIFT                          0
#define FTM_SC_PS(x)                             (((uint32_t)(((uint32_t)(x))<<FTM_SC_PS_SHIFT))&FTM_SC_PS_MASK)
#define FTM_SC_CLKS_MASK                         0x18u
#define FTM_SC_CLKS_SHIFT                        3
#define FTM_SC_CLKS(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_SC_CLKS_SHIFT))&FTM_SC_CLKS_MASK)
#define FTM_SC_CPWMS_MASK                        0x20u
#define FTM_SC_CPWMS_SHIFT                       5
#define FTM_SC_TOIE_MASK                         0x40u
#define FTM_SC_TOIE_SHIFT                        6
#define FTM_SC_TOF_MASK                          0x80u
#define FTM_SC_TOF_SHIFT                         7
/* CNT Bit Fields */
#define FTM_CNT_COUNT_MASK                       0xFFFFu
#define FTM_CNT_COUNT_SHIFT                      0
#define FTM_CNT_COUNT(x)                         (((uint32_t)(((uint32_t)(x))<<FTM_CNT_COUNT_SHIFT))&FTM_CNT_COUNT_MASK)
/* MOD Bit Fields */
#define FTM_MOD_MOD_MASK                         0xFFFFu
#define FTM_MOD_MOD_SHIFT                        0
#define FTM_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_MOD_MOD_SHIFT))&FTM_MOD_MOD_MASK)
/* CnSC Bit Fields */
#define FTM_CnSC_ELSA_MASK                       0x4u
#define FTM_CnSC_ELSA_SHIFT                      2
#define FTM_CnSC_ELSB_MASK                       0x8u
#define FTM_CnSC_ELSB_SHIFT                      3
#define FTM_CnSC_MSA_MASK                        0x10u
#define FTM_CnSC_MSA_SHIFT                       4
#define FTM_CnSC_MSB_MASK                        0x20u
#define FTM_CnSC_MSB_SHIFT                       5
#define FTM_CnSC_CHIE_MASK                       0x40u
#define FTM_CnSC_CHIE_SHIFT                      6
#define FTM_CnSC_CHF_MASK                        0x80u
#define FTM_CnSC_CHF_SHIFT                       7
/* CnV Bit Fields */
#define FTM_CnV_VAL_MASK                         0xFFFFu
#define FTM_CnV_VAL_SHIFT                        0
#define FTM_CnV_VAL(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_CnV_VAL_SHIFT))&FTM_CnV_VAL_MASK)
/* EXTTRIG Bit Fields */
#define FTM_EXTTRIG_INITTRIGEN_MASK              0x40u
#define FTM_EXTTRIG_INITTRIGEN_SHIFT             6

/*!
 * @}
 */ /* end of group FTM_Register_Masks */


/* FTM - Peripheral instance base addresses */
/** Peripheral FTM0 base pointer */
#define FTM0_BASE_PTR                            ((FTM_MemMapPtr)0x40038000u)
/** Peripheral FTM1 base pointer */
#define FTM1_BASE_PTR                            ((FTM_MemMapPtr)0x40039000u)
/** Array initializer of FTM peripheral base pointers */
#define FTM_BASE_PTRS                            { FTM0_BASE_PTR, FTM1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register instance definitions */
/* FTM0 */
#define FTM0_SC                                  FTM_SC_REG(FTM0_BASE_PTR)
#define FTM0_CNT                                 FTM_CNT_REG(FTM0_BASE_PTR)
#define FTM0_MOD                                 FTM_MOD_REG(FTM0_BASE_PTR)
#define FTM0_C0SC                                FTM_CnSC_REG(FTM0_BASE_PTR,0)
#define FTM0_C0V                                 FTM_CnV_REG(FTM0_BASE_PTR,0)
#define FTM0_C1SC                                FTM_CnSC_REG(FTM0_BASE_PTR,1)
#define FTM0_C1V                                 FTM_CnV_REG(FTM0_BASE_PTR,1)
#define FTM0_EXTTRIG                             FTM_EXTTRIG_REG(FTM0_BASE_PTR)
/* FTM1 */
#define FTM1_SC                                  FTM_SC_REG(FTM1_BASE_PTR)
#define FTM1_CNT                                 FTM_CNT_REG(FTM1_BASE_PTR)
#define FTM1_MOD                                 FTM_MOD_REG(FTM1_BASE_PTR)
#define FTM1_C0SC                                FTM_CnSC_REG(FTM1_BASE_PTR,0)
#define FTM1_C0V                                 FTM_CnV_REG(FTM1_BASE_PTR,0)
#define FTM1_C1SC                                FTM_CnSC_REG(FTM1_BASE_PTR,1)
#define FTM1_C1V                                 FTM_CnV_REG(FTM1_BASE_PTR,1)
#define FTM1_EXTTRIG                             FTM_EXTTRIG_REG(FTM1_BASE_PTR)

/* FTM - Register array accessors */
#define FTM0_CnSC(index)                         FTM_CnSC_REG(FTM0_BASE_PTR,index)
#define FTM1_CnSC(index)                         FTM_CnSC_REG(FTM1_BASE_PTR,index)
#define FTM0_CnV(index)                          FTM_CnV_REG(FTM0_BASE_PTR,index)
#define FTM1_CnV(index)                          FTM_CnV_REG(FTM1_BASE_PTR,index)

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTM_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTMRE
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Peripheral FTMRE
 * @{
 */

/** FTMRE - Peripheral register structure */
typedef struct FTMRE_MemMap {
  uint8_t RESERVED_0[1];
  uint8_t FCCOBIX;                                 /**< Flash CCOB Index Register, offset: 0x1 */
  uint8_t FSEC;                                    /**< Flash Security Register, offset: 0x2 */
  uint8_t FCLKDIV;                                 /**< Flash Clock Divider Register, offset: 0x3 */
  uint8_t RESERVED_1[1];
  uint8_t FSTAT;                                   /**< Flash Status Register, offset: 0x5 */
  uint8_t RESERVED_2[1];
  uint8_t FCNFG;                                   /**< Flash Configuration Register, offset: 0x7 */
  uint8_t FCCOBLO;                                 /**< Flash Common Command Object Register: Low, offset: 0x8 */
  uint8_t FCCOBHI;                                 /**< Flash Common Command Object Register:High, offset: 0x9 */
  uint8_t RESERVED_3[1];
  uint8_t FPROT;                                   /**< Flash Protection Register, offset: 0xB */
  uint8_t RESERVED_4[3];
  uint8_t FOPT;                                    /**< Flash Option Register, offset: 0xF */
} volatile *FTMRE_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTMRE - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Register_Accessor_Macros FTMRE - Register accessor macros
 * @{
 */


/* FTMRE - Register accessors */
#define FTMRE_FCCOBIX_REG(base)                  ((base)->FCCOBIX)
#define FTMRE_FSEC_REG(base)                     ((base)->FSEC)
#define FTMRE_FCLKDIV_REG(base)                  ((base)->FCLKDIV)
#define FTMRE_FSTAT_REG(base)                    ((base)->FSTAT)
#define FTMRE_FCNFG_REG(base)                    ((base)->FCNFG)
#define FTMRE_FCCOBLO_REG(base)                  ((base)->FCCOBLO)
#define FTMRE_FCCOBHI_REG(base)                  ((base)->FCCOBHI)
#define FTMRE_FPROT_REG(base)                    ((base)->FPROT)
#define FTMRE_FOPT_REG(base)                     ((base)->FOPT)

/*!
 * @}
 */ /* end of group FTMRE_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTMRE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Register_Masks FTMRE Register Masks
 * @{
 */

/* FCCOBIX Bit Fields */
#define FTMRE_FCCOBIX_CCOBIX_MASK                0x7u
#define FTMRE_FCCOBIX_CCOBIX_SHIFT               0
#define FTMRE_FCCOBIX_CCOBIX(x)                  (((uint8_t)(((uint8_t)(x))<<FTMRE_FCCOBIX_CCOBIX_SHIFT))&FTMRE_FCCOBIX_CCOBIX_MASK)
/* FSEC Bit Fields */
#define FTMRE_FSEC_SEC_MASK                      0x3u
#define FTMRE_FSEC_SEC_SHIFT                     0
#define FTMRE_FSEC_SEC(x)                        (((uint8_t)(((uint8_t)(x))<<FTMRE_FSEC_SEC_SHIFT))&FTMRE_FSEC_SEC_MASK)
#define FTMRE_FSEC_KEYEN_MASK                    0xC0u
#define FTMRE_FSEC_KEYEN_SHIFT                   6
#define FTMRE_FSEC_KEYEN(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRE_FSEC_KEYEN_SHIFT))&FTMRE_FSEC_KEYEN_MASK)
/* FCLKDIV Bit Fields */
#define FTMRE_FCLKDIV_FDIV_MASK                  0x3Fu
#define FTMRE_FCLKDIV_FDIV_SHIFT                 0
#define FTMRE_FCLKDIV_FDIV(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FCLKDIV_FDIV_SHIFT))&FTMRE_FCLKDIV_FDIV_MASK)
#define FTMRE_FCLKDIV_FDIVLCK_MASK               0x40u
#define FTMRE_FCLKDIV_FDIVLCK_SHIFT              6
#define FTMRE_FCLKDIV_FDIVLD_MASK                0x80u
#define FTMRE_FCLKDIV_FDIVLD_SHIFT               7
/* FSTAT Bit Fields */
#define FTMRE_FSTAT_MGSTAT_MASK                  0x3u
#define FTMRE_FSTAT_MGSTAT_SHIFT                 0
#define FTMRE_FSTAT_MGSTAT(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FSTAT_MGSTAT_SHIFT))&FTMRE_FSTAT_MGSTAT_MASK)
#define FTMRE_FSTAT_MGBUSY_MASK                  0x8u
#define FTMRE_FSTAT_MGBUSY_SHIFT                 3
#define FTMRE_FSTAT_FPVIOL_MASK                  0x10u
#define FTMRE_FSTAT_FPVIOL_SHIFT                 4
#define FTMRE_FSTAT_ACCERR_MASK                  0x20u
#define FTMRE_FSTAT_ACCERR_SHIFT                 5
#define FTMRE_FSTAT_CCIF_MASK                    0x80u
#define FTMRE_FSTAT_CCIF_SHIFT                   7
/* FCNFG Bit Fields */
#define FTMRE_FCNFG_ERSAREQ_MASK                 0x20u
#define FTMRE_FCNFG_ERSAREQ_SHIFT                5
#define FTMRE_FCNFG_CCIE_MASK                    0x80u
#define FTMRE_FCNFG_CCIE_SHIFT                   7
/* FCCOBLO Bit Fields */
#define FTMRE_FCCOBLO_CCOB_MASK                  0xFFu
#define FTMRE_FCCOBLO_CCOB_SHIFT                 0
#define FTMRE_FCCOBLO_CCOB(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FCCOBLO_CCOB_SHIFT))&FTMRE_FCCOBLO_CCOB_MASK)
/* FCCOBHI Bit Fields */
#define FTMRE_FCCOBHI_CCOB_MASK                  0xFFu
#define FTMRE_FCCOBHI_CCOB_SHIFT                 0
#define FTMRE_FCCOBHI_CCOB(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRE_FCCOBHI_CCOB_SHIFT))&FTMRE_FCCOBHI_CCOB_MASK)
/* FPROT Bit Fields */
#define FTMRE_FPROT_FPLS_MASK                    0x3u
#define FTMRE_FPROT_FPLS_SHIFT                   0
#define FTMRE_FPROT_FPLS(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRE_FPROT_FPLS_SHIFT))&FTMRE_FPROT_FPLS_MASK)
#define FTMRE_FPROT_FPLDIS_MASK                  0x4u
#define FTMRE_FPROT_FPLDIS_SHIFT                 2
#define FTMRE_FPROT_RNV_MASK                     0x38u
#define FTMRE_FPROT_RNV_SHIFT                    3
#define FTMRE_FPROT_RNV(x)                       (((uint8_t)(((uint8_t)(x))<<FTMRE_FPROT_RNV_SHIFT))&FTMRE_FPROT_RNV_MASK)
#define FTMRE_FPROT_RNV6_MASK                    0x40u
#define FTMRE_FPROT_RNV6_SHIFT                   6
#define FTMRE_FPROT_FPOPEN_MASK                  0x80u
#define FTMRE_FPROT_FPOPEN_SHIFT                 7
/* FOPT Bit Fields */
#define FTMRE_FOPT_NV_MASK                       0xFFu
#define FTMRE_FOPT_NV_SHIFT                      0
#define FTMRE_FOPT_NV(x)                         (((uint8_t)(((uint8_t)(x))<<FTMRE_FOPT_NV_SHIFT))&FTMRE_FOPT_NV_MASK)

/*!
 * @}
 */ /* end of group FTMRE_Register_Masks */


/* FTMRE - Peripheral instance base addresses */
/** Peripheral FTMRE base pointer */
#define FTMRE_BASE_PTR                           ((FTMRE_MemMapPtr)0x40020000u)
/** Array initializer of FTMRE peripheral base pointers */
#define FTMRE_BASE_PTRS                          { FTMRE_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FTMRE - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRE_Register_Accessor_Macros FTMRE - Register accessor macros
 * @{
 */


/* FTMRE - Register instance definitions */
/* FTMRE */
#define FTMRE_FCCOBIX                            FTMRE_FCCOBIX_REG(FTMRE_BASE_PTR)
#define FTMRE_FSEC                               FTMRE_FSEC_REG(FTMRE_BASE_PTR)
#define FTMRE_FCLKDIV                            FTMRE_FCLKDIV_REG(FTMRE_BASE_PTR)
#define FTMRE_FSTAT                              FTMRE_FSTAT_REG(FTMRE_BASE_PTR)
#define FTMRE_FCNFG                              FTMRE_FCNFG_REG(FTMRE_BASE_PTR)
#define FTMRE_FCCOBLO                            FTMRE_FCCOBLO_REG(FTMRE_BASE_PTR)
#define FTMRE_FCCOBHI                            FTMRE_FCCOBHI_REG(FTMRE_BASE_PTR)
#define FTMRE_FPROT                              FTMRE_FPROT_REG(FTMRE_BASE_PTR)
#define FTMRE_FOPT                               FTMRE_FOPT_REG(FTMRE_BASE_PTR)

/*!
 * @}
 */ /* end of group FTMRE_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTMRE_Peripheral */


/* ----------------------------------------------------------------------------
   -- GPIO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral GPIO
 * @{
 */

/** GPIO - Peripheral register structure */
typedef struct GPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
  uint32_t PIDR;                                   /**< Port Input Disable Register, offset: 0x18 */
} volatile *GPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register accessors */
#define GPIO_PDOR_REG(base)                      ((base)->PDOR)
#define GPIO_PSOR_REG(base)                      ((base)->PSOR)
#define GPIO_PCOR_REG(base)                      ((base)->PCOR)
#define GPIO_PTOR_REG(base)                      ((base)->PTOR)
#define GPIO_PDIR_REG(base)                      ((base)->PDIR)
#define GPIO_PDDR_REG(base)                      ((base)->PDDR)
#define GPIO_PIDR_REG(base)                      ((base)->PIDR)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/* PDOR Bit Fields */
#define GPIO_PDOR_PDO_MASK                       0xFFFFFFFFu
#define GPIO_PDOR_PDO_SHIFT                      0
#define GPIO_PDOR_PDO(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDOR_PDO_SHIFT))&GPIO_PDOR_PDO_MASK)
/* PSOR Bit Fields */
#define GPIO_PSOR_PTSO_MASK                      0xFFFFFFFFu
#define GPIO_PSOR_PTSO_SHIFT                     0
#define GPIO_PSOR_PTSO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PSOR_PTSO_SHIFT))&GPIO_PSOR_PTSO_MASK)
/* PCOR Bit Fields */
#define GPIO_PCOR_PTCO_MASK                      0xFFFFFFFFu
#define GPIO_PCOR_PTCO_SHIFT                     0
#define GPIO_PCOR_PTCO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PCOR_PTCO_SHIFT))&GPIO_PCOR_PTCO_MASK)
/* PTOR Bit Fields */
#define GPIO_PTOR_PTTO_MASK                      0xFFFFFFFFu
#define GPIO_PTOR_PTTO_SHIFT                     0
#define GPIO_PTOR_PTTO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PTOR_PTTO_SHIFT))&GPIO_PTOR_PTTO_MASK)
/* PDIR Bit Fields */
#define GPIO_PDIR_PDI_MASK                       0xFFFFFFFFu
#define GPIO_PDIR_PDI_SHIFT                      0
#define GPIO_PDIR_PDI(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDIR_PDI_SHIFT))&GPIO_PDIR_PDI_MASK)
/* PDDR Bit Fields */
#define GPIO_PDDR_PDD_MASK                       0xFFFFFFFFu
#define GPIO_PDDR_PDD_SHIFT                      0
#define GPIO_PDDR_PDD(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDDR_PDD_SHIFT))&GPIO_PDDR_PDD_MASK)
/* PIDR Bit Fields */
#define GPIO_PIDR_PID_MASK                       0xFFFFFFFFu
#define GPIO_PIDR_PID_SHIFT                      0
#define GPIO_PIDR_PID(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PIDR_PID_SHIFT))&GPIO_PIDR_PID_MASK)

/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base pointer */
#define GPIOA_BASE_PTR                           ((GPIO_MemMapPtr)0x4000F000u)
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIOA_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register instance definitions */
/* GPIOA */
#define GPIOA_PDOR                               GPIO_PDOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PSOR                               GPIO_PSOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PCOR                               GPIO_PCOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PTOR                               GPIO_PTOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PDIR                               GPIO_PDIR_REG(GPIOA_BASE_PTR)
#define GPIOA_PDDR                               GPIO_PDDR_REG(GPIOA_BASE_PTR)
#define GPIOA_PIDR                               GPIO_PIDR_REG(GPIOA_BASE_PTR)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group GPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- I2C
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral I2C
 * @{
 */

/** I2C - Peripheral register structure */
typedef struct I2C_MemMap {
  uint8_t A1;                                      /**< I2C Address Register 1, offset: 0x0 */
  uint8_t F;                                       /**< I2C Frequency Divider register, offset: 0x1 */
  uint8_t C1;                                      /**< I2C Control Register 1, offset: 0x2 */
  uint8_t S;                                       /**< I2C Status register, offset: 0x3 */
  uint8_t D;                                       /**< I2C Data I/O register, offset: 0x4 */
  uint8_t C2;                                      /**< I2C Control Register 2, offset: 0x5 */
  uint8_t FLT;                                     /**< I2C Programmable Input Glitch Filter Register, offset: 0x6 */
  uint8_t RA;                                      /**< I2C Range Address register, offset: 0x7 */
  uint8_t SMB;                                     /**< I2C SMBus Control and Status register, offset: 0x8 */
  uint8_t A2;                                      /**< I2C Address Register 2, offset: 0x9 */
  uint8_t SLTH;                                    /**< I2C SCL Low Timeout Register High, offset: 0xA */
  uint8_t SLTL;                                    /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} volatile *I2C_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
#define I2C_A1_REG(base)                         ((base)->A1)
#define I2C_F_REG(base)                          ((base)->F)
#define I2C_C1_REG(base)                         ((base)->C1)
#define I2C_S_REG(base)                          ((base)->S)
#define I2C_D_REG(base)                          ((base)->D)
#define I2C_C2_REG(base)                         ((base)->C2)
#define I2C_FLT_REG(base)                        ((base)->FLT)
#define I2C_RA_REG(base)                         ((base)->RA)
#define I2C_SMB_REG(base)                        ((base)->SMB)
#define I2C_A2_REG(base)                         ((base)->A2)
#define I2C_SLTH_REG(base)                       ((base)->SLTH)
#define I2C_SLTL_REG(base)                       ((base)->SLTL)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/* A1 Bit Fields */
#define I2C_A1_AD_MASK                           0xFEu
#define I2C_A1_AD_SHIFT                          1
#define I2C_A1_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_A1_AD_SHIFT))&I2C_A1_AD_MASK)
/* F Bit Fields */
#define I2C_F_ICR_MASK                           0x3Fu
#define I2C_F_ICR_SHIFT                          0
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_F_ICR_SHIFT))&I2C_F_ICR_MASK)
#define I2C_F_MULT_MASK                          0xC0u
#define I2C_F_MULT_SHIFT                         6
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_F_MULT_SHIFT))&I2C_F_MULT_MASK)
/* C1 Bit Fields */
#define I2C_C1_WUEN_MASK                         0x2u
#define I2C_C1_WUEN_SHIFT                        1
#define I2C_C1_RSTA_MASK                         0x4u
#define I2C_C1_RSTA_SHIFT                        2
#define I2C_C1_TXAK_MASK                         0x8u
#define I2C_C1_TXAK_SHIFT                        3
#define I2C_C1_TX_MASK                           0x10u
#define I2C_C1_TX_SHIFT                          4
#define I2C_C1_MST_MASK                          0x20u
#define I2C_C1_MST_SHIFT                         5
#define I2C_C1_IICIE_MASK                        0x40u
#define I2C_C1_IICIE_SHIFT                       6
#define I2C_C1_IICEN_MASK                        0x80u
#define I2C_C1_IICEN_SHIFT                       7
/* S Bit Fields */
#define I2C_S_RXAK_MASK                          0x1u
#define I2C_S_RXAK_SHIFT                         0
#define I2C_S_IICIF_MASK                         0x2u
#define I2C_S_IICIF_SHIFT                        1
#define I2C_S_SRW_MASK                           0x4u
#define I2C_S_SRW_SHIFT                          2
#define I2C_S_RAM_MASK                           0x8u
#define I2C_S_RAM_SHIFT                          3
#define I2C_S_ARBL_MASK                          0x10u
#define I2C_S_ARBL_SHIFT                         4
#define I2C_S_BUSY_MASK                          0x20u
#define I2C_S_BUSY_SHIFT                         5
#define I2C_S_IAAS_MASK                          0x40u
#define I2C_S_IAAS_SHIFT                         6
#define I2C_S_TCF_MASK                           0x80u
#define I2C_S_TCF_SHIFT                          7
/* D Bit Fields */
#define I2C_D_DATA_MASK                          0xFFu
#define I2C_D_DATA_SHIFT                         0
#define I2C_D_DATA(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_D_DATA_SHIFT))&I2C_D_DATA_MASK)
/* C2 Bit Fields */
#define I2C_C2_AD_MASK                           0x7u
#define I2C_C2_AD_SHIFT                          0
#define I2C_C2_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_C2_AD_SHIFT))&I2C_C2_AD_MASK)
#define I2C_C2_RMEN_MASK                         0x8u
#define I2C_C2_RMEN_SHIFT                        3
#define I2C_C2_SBRC_MASK                         0x10u
#define I2C_C2_SBRC_SHIFT                        4
#define I2C_C2_ADEXT_MASK                        0x40u
#define I2C_C2_ADEXT_SHIFT                       6
#define I2C_C2_GCAEN_MASK                        0x80u
#define I2C_C2_GCAEN_SHIFT                       7
/* FLT Bit Fields */
#define I2C_FLT_FLT_MASK                         0xFu
#define I2C_FLT_FLT_SHIFT                        0
#define I2C_FLT_FLT(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_FLT_FLT_SHIFT))&I2C_FLT_FLT_MASK)
#define I2C_FLT_STARTF_MASK                      0x10u
#define I2C_FLT_STARTF_SHIFT                     4
#define I2C_FLT_SSIE_MASK                        0x20u
#define I2C_FLT_SSIE_SHIFT                       5
#define I2C_FLT_STOPF_MASK                       0x40u
#define I2C_FLT_STOPF_SHIFT                      6
#define I2C_FLT_SHEN_MASK                        0x80u
#define I2C_FLT_SHEN_SHIFT                       7
/* RA Bit Fields */
#define I2C_RA_RAD_MASK                          0xFEu
#define I2C_RA_RAD_SHIFT                         1
#define I2C_RA_RAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_RA_RAD_SHIFT))&I2C_RA_RAD_MASK)
/* SMB Bit Fields */
#define I2C_SMB_SHTF2IE_MASK                     0x1u
#define I2C_SMB_SHTF2IE_SHIFT                    0
#define I2C_SMB_SHTF2_MASK                       0x2u
#define I2C_SMB_SHTF2_SHIFT                      1
#define I2C_SMB_SHTF1_MASK                       0x4u
#define I2C_SMB_SHTF1_SHIFT                      2
#define I2C_SMB_SLTF_MASK                        0x8u
#define I2C_SMB_SLTF_SHIFT                       3
#define I2C_SMB_TCKSEL_MASK                      0x10u
#define I2C_SMB_TCKSEL_SHIFT                     4
#define I2C_SMB_SIICAEN_MASK                     0x20u
#define I2C_SMB_SIICAEN_SHIFT                    5
#define I2C_SMB_ALERTEN_MASK                     0x40u
#define I2C_SMB_ALERTEN_SHIFT                    6
#define I2C_SMB_FACK_MASK                        0x80u
#define I2C_SMB_FACK_SHIFT                       7
/* A2 Bit Fields */
#define I2C_A2_SAD_MASK                          0xFEu
#define I2C_A2_SAD_SHIFT                         1
#define I2C_A2_SAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_A2_SAD_SHIFT))&I2C_A2_SAD_MASK)
/* SLTH Bit Fields */
#define I2C_SLTH_SSLT_MASK                       0xFFu
#define I2C_SLTH_SSLT_SHIFT                      0
#define I2C_SLTH_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTH_SSLT_SHIFT))&I2C_SLTH_SSLT_MASK)
/* SLTL Bit Fields */
#define I2C_SLTL_SSLT_MASK                       0xFFu
#define I2C_SLTL_SSLT_SHIFT                      0
#define I2C_SLTL_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTL_SSLT_SHIFT))&I2C_SLTL_SSLT_MASK)

/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base pointer */
#define I2C0_BASE_PTR                            ((I2C_MemMapPtr)0x40066000u)
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register instance definitions */
/* I2C0 */
#define I2C0_A1                                  I2C_A1_REG(I2C0_BASE_PTR)
#define I2C0_F                                   I2C_F_REG(I2C0_BASE_PTR)
#define I2C0_C1                                  I2C_C1_REG(I2C0_BASE_PTR)
#define I2C0_S                                   I2C_S_REG(I2C0_BASE_PTR)
#define I2C0_D                                   I2C_D_REG(I2C0_BASE_PTR)
#define I2C0_C2                                  I2C_C2_REG(I2C0_BASE_PTR)
#define I2C0_FLT                                 I2C_FLT_REG(I2C0_BASE_PTR)
#define I2C0_RA                                  I2C_RA_REG(I2C0_BASE_PTR)
#define I2C0_SMB                                 I2C_SMB_REG(I2C0_BASE_PTR)
#define I2C0_A2                                  I2C_A2_REG(I2C0_BASE_PTR)
#define I2C0_SLTH                                I2C_SLTH_REG(I2C0_BASE_PTR)
#define I2C0_SLTL                                I2C_SLTL_REG(I2C0_BASE_PTR)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group I2C_Peripheral */


/* ----------------------------------------------------------------------------
   -- ICS
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Peripheral ICS
 * @{
 */

/** ICS - Peripheral register structure */
typedef struct ICS_MemMap {
  uint8_t C1;                                      /**< ICS Control Register 1, offset: 0x0 */
  uint8_t C2;                                      /**< ICS Control Register 2, offset: 0x1 */
  uint8_t C3;                                      /**< ICS Control Register 3, offset: 0x2 */
  uint8_t C4;                                      /**< ICS Control Register 4, offset: 0x3 */
  uint8_t S;                                       /**< ICS Status Register, offset: 0x4 */
} volatile *ICS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ICS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Accessor_Macros ICS - Register accessor macros
 * @{
 */


/* ICS - Register accessors */
#define ICS_C1_REG(base)                         ((base)->C1)
#define ICS_C2_REG(base)                         ((base)->C2)
#define ICS_C3_REG(base)                         ((base)->C3)
#define ICS_C4_REG(base)                         ((base)->C4)
#define ICS_S_REG(base)                          ((base)->S)

/*!
 * @}
 */ /* end of group ICS_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ICS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Masks ICS Register Masks
 * @{
 */

/* C1 Bit Fields */
#define ICS_C1_IREFSTEN_MASK                     0x1u
#define ICS_C1_IREFSTEN_SHIFT                    0
#define ICS_C1_IRCLKEN_MASK                      0x2u
#define ICS_C1_IRCLKEN_SHIFT                     1
#define ICS_C1_IREFS_MASK                        0x4u
#define ICS_C1_IREFS_SHIFT                       2
#define ICS_C1_RDIV_MASK                         0x38u
#define ICS_C1_RDIV_SHIFT                        3
#define ICS_C1_RDIV(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C1_RDIV_SHIFT))&ICS_C1_RDIV_MASK)
#define ICS_C1_CLKS_MASK                         0xC0u
#define ICS_C1_CLKS_SHIFT                        6
#define ICS_C1_CLKS(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C1_CLKS_SHIFT))&ICS_C1_CLKS_MASK)
/* C2 Bit Fields */
#define ICS_C2_LP_MASK                           0x10u
#define ICS_C2_LP_SHIFT                          4
#define ICS_C2_BDIV_MASK                         0xE0u
#define ICS_C2_BDIV_SHIFT                        5
#define ICS_C2_BDIV(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C2_BDIV_SHIFT))&ICS_C2_BDIV_MASK)
/* C3 Bit Fields */
#define ICS_C3_SCTRIM_MASK                       0xFFu
#define ICS_C3_SCTRIM_SHIFT                      0
#define ICS_C3_SCTRIM(x)                         (((uint8_t)(((uint8_t)(x))<<ICS_C3_SCTRIM_SHIFT))&ICS_C3_SCTRIM_MASK)
/* C4 Bit Fields */
#define ICS_C4_SCFTRIM_MASK                      0x1u
#define ICS_C4_SCFTRIM_SHIFT                     0
#define ICS_C4_CME_MASK                          0x20u
#define ICS_C4_CME_SHIFT                         5
#define ICS_C4_LOLIE_MASK                        0x80u
#define ICS_C4_LOLIE_SHIFT                       7
/* S Bit Fields */
#define ICS_S_CLKST_MASK                         0xCu
#define ICS_S_CLKST_SHIFT                        2
#define ICS_S_CLKST(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_S_CLKST_SHIFT))&ICS_S_CLKST_MASK)
#define ICS_S_IREFST_MASK                        0x10u
#define ICS_S_IREFST_SHIFT                       4
#define ICS_S_LOCK_MASK                          0x40u
#define ICS_S_LOCK_SHIFT                         6
#define ICS_S_LOLS_MASK                          0x80u
#define ICS_S_LOLS_SHIFT                         7

/*!
 * @}
 */ /* end of group ICS_Register_Masks */


/* ICS - Peripheral instance base addresses */
/** Peripheral ICS base pointer */
#define ICS_BASE_PTR                             ((ICS_MemMapPtr)0x40064000u)
/** Array initializer of ICS peripheral base pointers */
#define ICS_BASE_PTRS                            { ICS_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ICS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Accessor_Macros ICS - Register accessor macros
 * @{
 */


/* ICS - Register instance definitions */
/* ICS */
#define ICS_C1                                   ICS_C1_REG(ICS_BASE_PTR)
#define ICS_C2                                   ICS_C2_REG(ICS_BASE_PTR)
#define ICS_C3                                   ICS_C3_REG(ICS_BASE_PTR)
#define ICS_C4                                   ICS_C4_REG(ICS_BASE_PTR)
#define ICS_S                                    ICS_S_REG(ICS_BASE_PTR)

/*!
 * @}
 */ /* end of group ICS_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ICS_Peripheral */


/* ----------------------------------------------------------------------------
   -- IRQ
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Peripheral IRQ
 * @{
 */

/** IRQ - Peripheral register structure */
typedef struct IRQ_MemMap {
  uint8_t SC;                                      /**< Interrupt Pin Request Status and Control Register, offset: 0x0 */
} volatile *IRQ_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- IRQ - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Accessor_Macros IRQ - Register accessor macros
 * @{
 */


/* IRQ - Register accessors */
#define IRQ_SC_REG(base)                         ((base)->SC)

/*!
 * @}
 */ /* end of group IRQ_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- IRQ Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Masks IRQ Register Masks
 * @{
 */

/* SC Bit Fields */
#define IRQ_SC_IRQMOD_MASK                       0x1u
#define IRQ_SC_IRQMOD_SHIFT                      0
#define IRQ_SC_IRQIE_MASK                        0x2u
#define IRQ_SC_IRQIE_SHIFT                       1
#define IRQ_SC_IRQACK_MASK                       0x4u
#define IRQ_SC_IRQACK_SHIFT                      2
#define IRQ_SC_IRQF_MASK                         0x8u
#define IRQ_SC_IRQF_SHIFT                        3
#define IRQ_SC_IRQPE_MASK                        0x10u
#define IRQ_SC_IRQPE_SHIFT                       4
#define IRQ_SC_IRQEDG_MASK                       0x20u
#define IRQ_SC_IRQEDG_SHIFT                      5
#define IRQ_SC_IRQPDD_MASK                       0x40u
#define IRQ_SC_IRQPDD_SHIFT                      6

/*!
 * @}
 */ /* end of group IRQ_Register_Masks */


/* IRQ - Peripheral instance base addresses */
/** Peripheral IRQ base pointer */
#define IRQ_BASE_PTR                             ((IRQ_MemMapPtr)0x40031000u)
/** Array initializer of IRQ peripheral base pointers */
#define IRQ_BASE_PTRS                            { IRQ_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- IRQ - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Accessor_Macros IRQ - Register accessor macros
 * @{
 */


/* IRQ - Register instance definitions */
/* IRQ */
#define IRQ_SC                                   IRQ_SC_REG(IRQ_BASE_PTR)

/*!
 * @}
 */ /* end of group IRQ_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group IRQ_Peripheral */


/* ----------------------------------------------------------------------------
   -- LDO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LDO_Peripheral LDO
 * @{
 */

/** LDO - Peripheral register structure */
typedef struct LDO_MemMap {
  uint16_t CR;                                     /**< Control Register, offset: 0x0 */
  uint16_t SR;                                     /**< Status Register, offset: 0x2 */
  uint16_t CTRM;                                   /**< Current Trim Register, offset: 0x4 */
  uint16_t VTRM;                                   /**< Voltage Trim Register, offset: 0x6 */
  uint16_t OCFILT;                                 /**< Overcurrent Filter Register, offset: 0x8 */
  uint16_t OVFILT;                                 /**< Overvoltage Filter Register, offset: 0xA */
  uint16_t SCR;                                    /**< Shutdown Control Register, offset: 0xC */
} volatile *LDO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LDO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LDO_Register_Accessor_Macros LDO - Register accessor macros
 * @{
 */


/* LDO - Register accessors */
#define LDO_CR_REG(base)                         ((base)->CR)
#define LDO_SR_REG(base)                         ((base)->SR)
#define LDO_CTRM_REG(base)                       ((base)->CTRM)
#define LDO_VTRM_REG(base)                       ((base)->VTRM)
#define LDO_OCFILT_REG(base)                     ((base)->OCFILT)
#define LDO_OVFILT_REG(base)                     ((base)->OVFILT)
#define LDO_SCR_REG(base)                        ((base)->SCR)

/*!
 * @}
 */ /* end of group LDO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LDO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LDO_Register_Masks LDO Register Masks
 * @{
 */

/* CR Bit Fields */
#define LDO_CR_OVDTE_MASK                        0x1u
#define LDO_CR_OVDTE_SHIFT                       0
#define LDO_CR_OVIE_MASK                         0x2u
#define LDO_CR_OVIE_SHIFT                        1
#define LDO_CR_OCIE_MASK                         0x4u
#define LDO_CR_OCIE_SHIFT                        2
#define LDO_CR_CPCLKPS_MASK                      0x18u
#define LDO_CR_CPCLKPS_SHIFT                     3
#define LDO_CR_CPCLKPS(x)                        (((uint16_t)(((uint16_t)(x))<<LDO_CR_CPCLKPS_SHIFT))&LDO_CR_CPCLKPS_MASK)
#define LDO_CR_OVTHLD_MASK                       0xC0u
#define LDO_CR_OVTHLD_SHIFT                      6
#define LDO_CR_OVTHLD(x)                         (((uint16_t)(((uint16_t)(x))<<LDO_CR_OVTHLD_SHIFT))&LDO_CR_OVTHLD_MASK)
#define LDO_CR_OCDTE_MASK                        0x100u
#define LDO_CR_OCDTE_SHIFT                       8
#define LDO_CR_BASHDN_MASK                       0x200u
#define LDO_CR_BASHDN_SHIFT                      9
#define LDO_CR_OCTHLD_MASK                       0x1C00u
#define LDO_CR_OCTHLD_SHIFT                      10
#define LDO_CR_OCTHLD(x)                         (((uint16_t)(((uint16_t)(x))<<LDO_CR_OCTHLD_SHIFT))&LDO_CR_OCTHLD_MASK)
#define LDO_CR_LDOREGEN_MASK                     0x2000u
#define LDO_CR_LDOREGEN_SHIFT                    13
#define LDO_CR_CPEN_MASK                         0x4000u
#define LDO_CR_CPEN_SHIFT                        14
#define LDO_CR_LDOEN_MASK                        0x8000u
#define LDO_CR_LDOEN_SHIFT                       15
/* SR Bit Fields */
#define LDO_SR_OVF_MASK                          0x1u
#define LDO_SR_OVF_SHIFT                         0
#define LDO_SR_OCF_MASK                          0x2u
#define LDO_SR_OCF_SHIFT                         1
#define LDO_SR_OVST_MASK                         0x4u
#define LDO_SR_OVST_SHIFT                        2
#define LDO_SR_OCST_MASK                         0x8u
#define LDO_SR_OCST_SHIFT                        3
#define LDO_SR_CPOKF_MASK                        0x8000u
#define LDO_SR_CPOKF_SHIFT                       15
/* CTRM Bit Fields */
#define LDO_CTRM_CTRM_MASK                       0x1FFu
#define LDO_CTRM_CTRM_SHIFT                      0
#define LDO_CTRM_CTRM(x)                         (((uint16_t)(((uint16_t)(x))<<LDO_CTRM_CTRM_SHIFT))&LDO_CTRM_CTRM_MASK)
/* VTRM Bit Fields */
#define LDO_VTRM_VTRM_MASK                       0x1FFu
#define LDO_VTRM_VTRM_SHIFT                      0
#define LDO_VTRM_VTRM(x)                         (((uint16_t)(((uint16_t)(x))<<LDO_VTRM_VTRM_SHIFT))&LDO_VTRM_VTRM_MASK)
/* OCFILT Bit Fields */
#define LDO_OCFILT_CNT_MASK                      0xFFFFu
#define LDO_OCFILT_CNT_SHIFT                     0
#define LDO_OCFILT_CNT(x)                        (((uint16_t)(((uint16_t)(x))<<LDO_OCFILT_CNT_SHIFT))&LDO_OCFILT_CNT_MASK)
/* OVFILT Bit Fields */
#define LDO_OVFILT_CNT_MASK                      0xFFFFu
#define LDO_OVFILT_CNT_SHIFT                     0
#define LDO_OVFILT_CNT(x)                        (((uint16_t)(((uint16_t)(x))<<LDO_OVFILT_CNT_SHIFT))&LDO_OVFILT_CNT_MASK)
/* SCR Bit Fields */
#define LDO_SCR_OCASDE_MASK                      0x1u
#define LDO_SCR_OCASDE_SHIFT                     0
#define LDO_SCR_OVASDE_MASK                      0x2u
#define LDO_SCR_OVASDE_SHIFT                     1
#define LDO_SCR_EXTSDE_MASK                      0x4u
#define LDO_SCR_EXTSDE_SHIFT                     2

/*!
 * @}
 */ /* end of group LDO_Register_Masks */


/* LDO - Peripheral instance base addresses */
/** Peripheral LDO base pointer */
#define LDO_BASE_PTR                             ((LDO_MemMapPtr)0x40070000u)
/** Array initializer of LDO peripheral base pointers */
#define LDO_BASE_PTRS                            { LDO_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- LDO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LDO_Register_Accessor_Macros LDO - Register accessor macros
 * @{
 */


/* LDO - Register instance definitions */
/* LDO */
#define LDO_CR                                   LDO_CR_REG(LDO_BASE_PTR)
#define LDO_SR                                   LDO_SR_REG(LDO_BASE_PTR)
#define LDO_CTRM                                 LDO_CTRM_REG(LDO_BASE_PTR)
#define LDO_VTRM                                 LDO_VTRM_REG(LDO_BASE_PTR)
#define LDO_OCFILT                               LDO_OCFILT_REG(LDO_BASE_PTR)
#define LDO_OVFILT                               LDO_OVFILT_REG(LDO_BASE_PTR)
#define LDO_SCR                                  LDO_SCR_REG(LDO_BASE_PTR)

/*!
 * @}
 */ /* end of group LDO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group LDO_Peripheral */


/* ----------------------------------------------------------------------------
   -- MCM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral MCM
 * @{
 */

/** MCM - Peripheral register structure */
typedef struct MCM_MemMap {
  uint8_t RESERVED_0[8];
  uint16_t PLASC;                                  /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  uint16_t PLAMC;                                  /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  uint32_t PLACR;                                  /**< Platform Control Register, offset: 0xC */
} volatile *MCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register accessors */
#define MCM_PLASC_REG(base)                      ((base)->PLASC)
#define MCM_PLAMC_REG(base)                      ((base)->PLAMC)
#define MCM_PLACR_REG(base)                      ((base)->PLACR)

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/* PLASC Bit Fields */
#define MCM_PLASC_ASC_MASK                       0xFFu
#define MCM_PLASC_ASC_SHIFT                      0
#define MCM_PLASC_ASC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLASC_ASC_SHIFT))&MCM_PLASC_ASC_MASK)
/* PLAMC Bit Fields */
#define MCM_PLAMC_AMC_MASK                       0xFFu
#define MCM_PLAMC_AMC_SHIFT                      0
#define MCM_PLAMC_AMC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLAMC_AMC_SHIFT))&MCM_PLAMC_AMC_MASK)
/* PLACR Bit Fields */
#define MCM_PLACR_ARB_MASK                       0x200u
#define MCM_PLACR_ARB_SHIFT                      9
#define MCM_PLACR_EFDS_MASK                      0x4000u
#define MCM_PLACR_EFDS_SHIFT                     14
#define MCM_PLACR_DFCS_MASK                      0x8000u
#define MCM_PLACR_DFCS_SHIFT                     15
#define MCM_PLACR_ESFC_MASK                      0x10000u
#define MCM_PLACR_ESFC_SHIFT                     16

/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base pointer */
#define MCM_BASE_PTR                             ((MCM_MemMapPtr)0xF0003000u)
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register instance definitions */
/* MCM */
#define MCM_PLASC                                MCM_PLASC_REG(MCM_BASE_PTR)
#define MCM_PLAMC                                MCM_PLAMC_REG(MCM_BASE_PTR)
#define MCM_PLACR                                MCM_PLACR_REG(MCM_BASE_PTR)

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MCM_Peripheral */


/* ----------------------------------------------------------------------------
   -- NV
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral NV
 * @{
 */

/** NV - Peripheral register structure */
typedef struct NV_MemMap {
  uint8_t BACKKEY0;                                /**< Backdoor Comparison Key 0, offset: 0x0 */
  uint8_t BACKKEY1;                                /**< Backdoor Comparison Key 1, offset: 0x1 */
  uint8_t BACKKEY2;                                /**< Backdoor Comparison Key 2, offset: 0x2 */
  uint8_t BACKKEY3;                                /**< Backdoor Comparison Key 3, offset: 0x3 */
  uint8_t BACKKEY4;                                /**< Backdoor Comparison Key 4, offset: 0x4 */
  uint8_t BACKKEY5;                                /**< Backdoor Comparison Key 5, offset: 0x5 */
  uint8_t BACKKEY6;                                /**< Backdoor Comparison Key 6, offset: 0x6 */
  uint8_t BACKKEY7;                                /**< Backdoor Comparison Key 7, offset: 0x7 */
  uint8_t RESERVED_0[5];
  uint8_t FPROT;                                   /**< Non-volatile P-Flash Protection Register, offset: 0xD */
  uint8_t FSEC;                                    /**< Non-volatile Flash Security Register, offset: 0xE */
  uint8_t FOPT;                                    /**< Non-volatile Flash Option Register, offset: 0xF */
} volatile *NV_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register accessors */
#define NV_BACKKEY0_REG(base)                    ((base)->BACKKEY0)
#define NV_BACKKEY1_REG(base)                    ((base)->BACKKEY1)
#define NV_BACKKEY2_REG(base)                    ((base)->BACKKEY2)
#define NV_BACKKEY3_REG(base)                    ((base)->BACKKEY3)
#define NV_BACKKEY4_REG(base)                    ((base)->BACKKEY4)
#define NV_BACKKEY5_REG(base)                    ((base)->BACKKEY5)
#define NV_BACKKEY6_REG(base)                    ((base)->BACKKEY6)
#define NV_BACKKEY7_REG(base)                    ((base)->BACKKEY7)
#define NV_FPROT_REG(base)                       ((base)->FPROT)
#define NV_FSEC_REG(base)                        ((base)->FSEC)
#define NV_FOPT_REG(base)                        ((base)->FOPT)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/* BACKKEY0 Bit Fields */
#define NV_BACKKEY0_KEY_MASK                     0xFFu
#define NV_BACKKEY0_KEY_SHIFT                    0
#define NV_BACKKEY0_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY0_KEY_SHIFT))&NV_BACKKEY0_KEY_MASK)
/* BACKKEY1 Bit Fields */
#define NV_BACKKEY1_KEY_MASK                     0xFFu
#define NV_BACKKEY1_KEY_SHIFT                    0
#define NV_BACKKEY1_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY1_KEY_SHIFT))&NV_BACKKEY1_KEY_MASK)
/* BACKKEY2 Bit Fields */
#define NV_BACKKEY2_KEY_MASK                     0xFFu
#define NV_BACKKEY2_KEY_SHIFT                    0
#define NV_BACKKEY2_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY2_KEY_SHIFT))&NV_BACKKEY2_KEY_MASK)
/* BACKKEY3 Bit Fields */
#define NV_BACKKEY3_KEY_MASK                     0xFFu
#define NV_BACKKEY3_KEY_SHIFT                    0
#define NV_BACKKEY3_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY3_KEY_SHIFT))&NV_BACKKEY3_KEY_MASK)
/* BACKKEY4 Bit Fields */
#define NV_BACKKEY4_KEY_MASK                     0xFFu
#define NV_BACKKEY4_KEY_SHIFT                    0
#define NV_BACKKEY4_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY4_KEY_SHIFT))&NV_BACKKEY4_KEY_MASK)
/* BACKKEY5 Bit Fields */
#define NV_BACKKEY5_KEY_MASK                     0xFFu
#define NV_BACKKEY5_KEY_SHIFT                    0
#define NV_BACKKEY5_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY5_KEY_SHIFT))&NV_BACKKEY5_KEY_MASK)
/* BACKKEY6 Bit Fields */
#define NV_BACKKEY6_KEY_MASK                     0xFFu
#define NV_BACKKEY6_KEY_SHIFT                    0
#define NV_BACKKEY6_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY6_KEY_SHIFT))&NV_BACKKEY6_KEY_MASK)
/* BACKKEY7 Bit Fields */
#define NV_BACKKEY7_KEY_MASK                     0xFFu
#define NV_BACKKEY7_KEY_SHIFT                    0
#define NV_BACKKEY7_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY7_KEY_SHIFT))&NV_BACKKEY7_KEY_MASK)
/* FPROT Bit Fields */
#define NV_FPROT_FPLS_MASK                       0x3u
#define NV_FPROT_FPLS_SHIFT                      0
#define NV_FPROT_FPLS(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPLS_SHIFT))&NV_FPROT_FPLS_MASK)
#define NV_FPROT_FPLDIS_MASK                     0x4u
#define NV_FPROT_FPLDIS_SHIFT                    2
#define NV_FPROT_FPHS_MASK                       0x18u
#define NV_FPROT_FPHS_SHIFT                      3
#define NV_FPROT_FPHS(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPHS_SHIFT))&NV_FPROT_FPHS_MASK)
#define NV_FPROT_FPHDIS_MASK                     0x20u
#define NV_FPROT_FPHDIS_SHIFT                    5
#define NV_FPROT_FPOPEN_MASK                     0x80u
#define NV_FPROT_FPOPEN_SHIFT                    7
/* FSEC Bit Fields */
#define NV_FSEC_SEC_MASK                         0x3u
#define NV_FSEC_SEC_SHIFT                        0
#define NV_FSEC_SEC(x)                           (((uint8_t)(((uint8_t)(x))<<NV_FSEC_SEC_SHIFT))&NV_FSEC_SEC_MASK)
#define NV_FSEC_KEYEN_MASK                       0xC0u
#define NV_FSEC_KEYEN_SHIFT                      6
#define NV_FSEC_KEYEN(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FSEC_KEYEN_SHIFT))&NV_FSEC_KEYEN_MASK)

/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTMRE_FlashConfig base pointer */
#define FTMRE_FlashConfig_BASE_PTR               ((NV_MemMapPtr)0x400u)
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTMRE_FlashConfig_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register instance definitions */
/* FTMRE_FlashConfig */
#define NV_BACKKEY0                              NV_BACKKEY0_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY1                              NV_BACKKEY1_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY2                              NV_BACKKEY2_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY3                              NV_BACKKEY3_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY4                              NV_BACKKEY4_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY5                              NV_BACKKEY5_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY6                              NV_BACKKEY6_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_BACKKEY7                              NV_BACKKEY7_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_FPROT                                 NV_FPROT_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_FSEC                                  NV_FSEC_REG(FTMRE_FlashConfig_BASE_PTR)
#define NV_FOPT                                  NV_FOPT_REG(FTMRE_FlashConfig_BASE_PTR)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NV_Peripheral */


/* ----------------------------------------------------------------------------
   -- NVIC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Peripheral NVIC
 * @{
 */

/** NVIC - Peripheral register structure */
typedef struct NVIC_MemMap {
  uint32_t ISER;                                   /**< Interrupt Set Enable Register, offset: 0x0 */
  uint8_t RESERVED_0[124];
  uint32_t ICER;                                   /**< Interrupt Clear Enable Register, offset: 0x80 */
  uint8_t RESERVED_1[124];
  uint32_t ISPR;                                   /**< Interrupt Set Pending Register, offset: 0x100 */
  uint8_t RESERVED_2[124];
  uint32_t ICPR;                                   /**< Interrupt Clear Pending Register, offset: 0x180 */
  uint8_t RESERVED_3[380];
  uint32_t IP[8];                                  /**< Interrupt Priority Register 0..Interrupt Priority Register 7, array offset: 0x300, array step: 0x4 */
} volatile *NVIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register accessors */
#define NVIC_ISER_REG(base)                      ((base)->ISER)
#define NVIC_ICER_REG(base)                      ((base)->ICER)
#define NVIC_ISPR_REG(base)                      ((base)->ISPR)
#define NVIC_ICPR_REG(base)                      ((base)->ICPR)
#define NVIC_IP_REG(base,index)                  ((base)->IP[index])

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NVIC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Masks NVIC Register Masks
 * @{
 */

/* ISER Bit Fields */
#define NVIC_ISER_SETENA0_MASK                   0x1u
#define NVIC_ISER_SETENA0_SHIFT                  0
#define NVIC_ISER_SETENA1_MASK                   0x2u
#define NVIC_ISER_SETENA1_SHIFT                  1
#define NVIC_ISER_SETENA2_MASK                   0x4u
#define NVIC_ISER_SETENA2_SHIFT                  2
#define NVIC_ISER_SETENA3_MASK                   0x8u
#define NVIC_ISER_SETENA3_SHIFT                  3
#define NVIC_ISER_SETENA4_MASK                   0x10u
#define NVIC_ISER_SETENA4_SHIFT                  4
#define NVIC_ISER_SETENA5_MASK                   0x20u
#define NVIC_ISER_SETENA5_SHIFT                  5
#define NVIC_ISER_SETENA6_MASK                   0x40u
#define NVIC_ISER_SETENA6_SHIFT                  6
#define NVIC_ISER_SETENA7_MASK                   0x80u
#define NVIC_ISER_SETENA7_SHIFT                  7
#define NVIC_ISER_SETENA8_MASK                   0x100u
#define NVIC_ISER_SETENA8_SHIFT                  8
#define NVIC_ISER_SETENA9_MASK                   0x200u
#define NVIC_ISER_SETENA9_SHIFT                  9
#define NVIC_ISER_SETENA10_MASK                  0x400u
#define NVIC_ISER_SETENA10_SHIFT                 10
#define NVIC_ISER_SETENA11_MASK                  0x800u
#define NVIC_ISER_SETENA11_SHIFT                 11
#define NVIC_ISER_SETENA12_MASK                  0x1000u
#define NVIC_ISER_SETENA12_SHIFT                 12
#define NVIC_ISER_SETENA13_MASK                  0x2000u
#define NVIC_ISER_SETENA13_SHIFT                 13
#define NVIC_ISER_SETENA14_MASK                  0x4000u
#define NVIC_ISER_SETENA14_SHIFT                 14
#define NVIC_ISER_SETENA15_MASK                  0x8000u
#define NVIC_ISER_SETENA15_SHIFT                 15
#define NVIC_ISER_SETENA16_MASK                  0x10000u
#define NVIC_ISER_SETENA16_SHIFT                 16
#define NVIC_ISER_SETENA17_MASK                  0x20000u
#define NVIC_ISER_SETENA17_SHIFT                 17
#define NVIC_ISER_SETENA18_MASK                  0x40000u
#define NVIC_ISER_SETENA18_SHIFT                 18
#define NVIC_ISER_SETENA19_MASK                  0x80000u
#define NVIC_ISER_SETENA19_SHIFT                 19
#define NVIC_ISER_SETENA20_MASK                  0x100000u
#define NVIC_ISER_SETENA20_SHIFT                 20
#define NVIC_ISER_SETENA21_MASK                  0x200000u
#define NVIC_ISER_SETENA21_SHIFT                 21
#define NVIC_ISER_SETENA22_MASK                  0x400000u
#define NVIC_ISER_SETENA22_SHIFT                 22
#define NVIC_ISER_SETENA23_MASK                  0x800000u
#define NVIC_ISER_SETENA23_SHIFT                 23
#define NVIC_ISER_SETENA24_MASK                  0x1000000u
#define NVIC_ISER_SETENA24_SHIFT                 24
#define NVIC_ISER_SETENA25_MASK                  0x2000000u
#define NVIC_ISER_SETENA25_SHIFT                 25
#define NVIC_ISER_SETENA26_MASK                  0x4000000u
#define NVIC_ISER_SETENA26_SHIFT                 26
#define NVIC_ISER_SETENA27_MASK                  0x8000000u
#define NVIC_ISER_SETENA27_SHIFT                 27
#define NVIC_ISER_SETENA28_MASK                  0x10000000u
#define NVIC_ISER_SETENA28_SHIFT                 28
#define NVIC_ISER_SETENA29_MASK                  0x20000000u
#define NVIC_ISER_SETENA29_SHIFT                 29
#define NVIC_ISER_SETENA30_MASK                  0x40000000u
#define NVIC_ISER_SETENA30_SHIFT                 30
#define NVIC_ISER_SETENA31_MASK                  0x80000000u
#define NVIC_ISER_SETENA31_SHIFT                 31
/* ICER Bit Fields */
#define NVIC_ICER_CLRENA0_MASK                   0x1u
#define NVIC_ICER_CLRENA0_SHIFT                  0
#define NVIC_ICER_CLRENA1_MASK                   0x2u
#define NVIC_ICER_CLRENA1_SHIFT                  1
#define NVIC_ICER_CLRENA2_MASK                   0x4u
#define NVIC_ICER_CLRENA2_SHIFT                  2
#define NVIC_ICER_CLRENA3_MASK                   0x8u
#define NVIC_ICER_CLRENA3_SHIFT                  3
#define NVIC_ICER_CLRENA4_MASK                   0x10u
#define NVIC_ICER_CLRENA4_SHIFT                  4
#define NVIC_ICER_CLRENA5_MASK                   0x20u
#define NVIC_ICER_CLRENA5_SHIFT                  5
#define NVIC_ICER_CLRENA6_MASK                   0x40u
#define NVIC_ICER_CLRENA6_SHIFT                  6
#define NVIC_ICER_CLRENA7_MASK                   0x80u
#define NVIC_ICER_CLRENA7_SHIFT                  7
#define NVIC_ICER_CLRENA8_MASK                   0x100u
#define NVIC_ICER_CLRENA8_SHIFT                  8
#define NVIC_ICER_CLRENA9_MASK                   0x200u
#define NVIC_ICER_CLRENA9_SHIFT                  9
#define NVIC_ICER_CLRENA10_MASK                  0x400u
#define NVIC_ICER_CLRENA10_SHIFT                 10
#define NVIC_ICER_CLRENA11_MASK                  0x800u
#define NVIC_ICER_CLRENA11_SHIFT                 11
#define NVIC_ICER_CLRENA12_MASK                  0x1000u
#define NVIC_ICER_CLRENA12_SHIFT                 12
#define NVIC_ICER_CLRENA13_MASK                  0x2000u
#define NVIC_ICER_CLRENA13_SHIFT                 13
#define NVIC_ICER_CLRENA14_MASK                  0x4000u
#define NVIC_ICER_CLRENA14_SHIFT                 14
#define NVIC_ICER_CLRENA15_MASK                  0x8000u
#define NVIC_ICER_CLRENA15_SHIFT                 15
#define NVIC_ICER_CLRENA16_MASK                  0x10000u
#define NVIC_ICER_CLRENA16_SHIFT                 16
#define NVIC_ICER_CLRENA17_MASK                  0x20000u
#define NVIC_ICER_CLRENA17_SHIFT                 17
#define NVIC_ICER_CLRENA18_MASK                  0x40000u
#define NVIC_ICER_CLRENA18_SHIFT                 18
#define NVIC_ICER_CLRENA19_MASK                  0x80000u
#define NVIC_ICER_CLRENA19_SHIFT                 19
#define NVIC_ICER_CLRENA20_MASK                  0x100000u
#define NVIC_ICER_CLRENA20_SHIFT                 20
#define NVIC_ICER_CLRENA21_MASK                  0x200000u
#define NVIC_ICER_CLRENA21_SHIFT                 21
#define NVIC_ICER_CLRENA22_MASK                  0x400000u
#define NVIC_ICER_CLRENA22_SHIFT                 22
#define NVIC_ICER_CLRENA23_MASK                  0x800000u
#define NVIC_ICER_CLRENA23_SHIFT                 23
#define NVIC_ICER_CLRENA24_MASK                  0x1000000u
#define NVIC_ICER_CLRENA24_SHIFT                 24
#define NVIC_ICER_CLRENA25_MASK                  0x2000000u
#define NVIC_ICER_CLRENA25_SHIFT                 25
#define NVIC_ICER_CLRENA26_MASK                  0x4000000u
#define NVIC_ICER_CLRENA26_SHIFT                 26
#define NVIC_ICER_CLRENA27_MASK                  0x8000000u
#define NVIC_ICER_CLRENA27_SHIFT                 27
#define NVIC_ICER_CLRENA28_MASK                  0x10000000u
#define NVIC_ICER_CLRENA28_SHIFT                 28
#define NVIC_ICER_CLRENA29_MASK                  0x20000000u
#define NVIC_ICER_CLRENA29_SHIFT                 29
#define NVIC_ICER_CLRENA30_MASK                  0x40000000u
#define NVIC_ICER_CLRENA30_SHIFT                 30
#define NVIC_ICER_CLRENA31_MASK                  0x80000000u
#define NVIC_ICER_CLRENA31_SHIFT                 31
/* ISPR Bit Fields */
#define NVIC_ISPR_SETPEND0_MASK                  0x1u
#define NVIC_ISPR_SETPEND0_SHIFT                 0
#define NVIC_ISPR_SETPEND1_MASK                  0x2u
#define NVIC_ISPR_SETPEND1_SHIFT                 1
#define NVIC_ISPR_SETPEND2_MASK                  0x4u
#define NVIC_ISPR_SETPEND2_SHIFT                 2
#define NVIC_ISPR_SETPEND3_MASK                  0x8u
#define NVIC_ISPR_SETPEND3_SHIFT                 3
#define NVIC_ISPR_SETPEND4_MASK                  0x10u
#define NVIC_ISPR_SETPEND4_SHIFT                 4
#define NVIC_ISPR_SETPEND5_MASK                  0x20u
#define NVIC_ISPR_SETPEND5_SHIFT                 5
#define NVIC_ISPR_SETPEND6_MASK                  0x40u
#define NVIC_ISPR_SETPEND6_SHIFT                 6
#define NVIC_ISPR_SETPEND7_MASK                  0x80u
#define NVIC_ISPR_SETPEND7_SHIFT                 7
#define NVIC_ISPR_SETPEND8_MASK                  0x100u
#define NVIC_ISPR_SETPEND8_SHIFT                 8
#define NVIC_ISPR_SETPEND9_MASK                  0x200u
#define NVIC_ISPR_SETPEND9_SHIFT                 9
#define NVIC_ISPR_SETPEND10_MASK                 0x400u
#define NVIC_ISPR_SETPEND10_SHIFT                10
#define NVIC_ISPR_SETPEND11_MASK                 0x800u
#define NVIC_ISPR_SETPEND11_SHIFT                11
#define NVIC_ISPR_SETPEND12_MASK                 0x1000u
#define NVIC_ISPR_SETPEND12_SHIFT                12
#define NVIC_ISPR_SETPEND13_MASK                 0x2000u
#define NVIC_ISPR_SETPEND13_SHIFT                13
#define NVIC_ISPR_SETPEND14_MASK                 0x4000u
#define NVIC_ISPR_SETPEND14_SHIFT                14
#define NVIC_ISPR_SETPEND15_MASK                 0x8000u
#define NVIC_ISPR_SETPEND15_SHIFT                15
#define NVIC_ISPR_SETPEND16_MASK                 0x10000u
#define NVIC_ISPR_SETPEND16_SHIFT                16
#define NVIC_ISPR_SETPEND17_MASK                 0x20000u
#define NVIC_ISPR_SETPEND17_SHIFT                17
#define NVIC_ISPR_SETPEND18_MASK                 0x40000u
#define NVIC_ISPR_SETPEND18_SHIFT                18
#define NVIC_ISPR_SETPEND19_MASK                 0x80000u
#define NVIC_ISPR_SETPEND19_SHIFT                19
#define NVIC_ISPR_SETPEND20_MASK                 0x100000u
#define NVIC_ISPR_SETPEND20_SHIFT                20
#define NVIC_ISPR_SETPEND21_MASK                 0x200000u
#define NVIC_ISPR_SETPEND21_SHIFT                21
#define NVIC_ISPR_SETPEND22_MASK                 0x400000u
#define NVIC_ISPR_SETPEND22_SHIFT                22
#define NVIC_ISPR_SETPEND23_MASK                 0x800000u
#define NVIC_ISPR_SETPEND23_SHIFT                23
#define NVIC_ISPR_SETPEND24_MASK                 0x1000000u
#define NVIC_ISPR_SETPEND24_SHIFT                24
#define NVIC_ISPR_SETPEND25_MASK                 0x2000000u
#define NVIC_ISPR_SETPEND25_SHIFT                25
#define NVIC_ISPR_SETPEND26_MASK                 0x4000000u
#define NVIC_ISPR_SETPEND26_SHIFT                26
#define NVIC_ISPR_SETPEND27_MASK                 0x8000000u
#define NVIC_ISPR_SETPEND27_SHIFT                27
#define NVIC_ISPR_SETPEND28_MASK                 0x10000000u
#define NVIC_ISPR_SETPEND28_SHIFT                28
#define NVIC_ISPR_SETPEND29_MASK                 0x20000000u
#define NVIC_ISPR_SETPEND29_SHIFT                29
#define NVIC_ISPR_SETPEND30_MASK                 0x40000000u
#define NVIC_ISPR_SETPEND30_SHIFT                30
#define NVIC_ISPR_SETPEND31_MASK                 0x80000000u
#define NVIC_ISPR_SETPEND31_SHIFT                31
/* ICPR Bit Fields */
#define NVIC_ICPR_CLRPEND0_MASK                  0x1u
#define NVIC_ICPR_CLRPEND0_SHIFT                 0
#define NVIC_ICPR_CLRPEND1_MASK                  0x2u
#define NVIC_ICPR_CLRPEND1_SHIFT                 1
#define NVIC_ICPR_CLRPEND2_MASK                  0x4u
#define NVIC_ICPR_CLRPEND2_SHIFT                 2
#define NVIC_ICPR_CLRPEND3_MASK                  0x8u
#define NVIC_ICPR_CLRPEND3_SHIFT                 3
#define NVIC_ICPR_CLRPEND4_MASK                  0x10u
#define NVIC_ICPR_CLRPEND4_SHIFT                 4
#define NVIC_ICPR_CLRPEND5_MASK                  0x20u
#define NVIC_ICPR_CLRPEND5_SHIFT                 5
#define NVIC_ICPR_CLRPEND6_MASK                  0x40u
#define NVIC_ICPR_CLRPEND6_SHIFT                 6
#define NVIC_ICPR_CLRPEND7_MASK                  0x80u
#define NVIC_ICPR_CLRPEND7_SHIFT                 7
#define NVIC_ICPR_CLRPEND8_MASK                  0x100u
#define NVIC_ICPR_CLRPEND8_SHIFT                 8
#define NVIC_ICPR_CLRPEND9_MASK                  0x200u
#define NVIC_ICPR_CLRPEND9_SHIFT                 9
#define NVIC_ICPR_CLRPEND10_MASK                 0x400u
#define NVIC_ICPR_CLRPEND10_SHIFT                10
#define NVIC_ICPR_CLRPEND11_MASK                 0x800u
#define NVIC_ICPR_CLRPEND11_SHIFT                11
#define NVIC_ICPR_CLRPEND12_MASK                 0x1000u
#define NVIC_ICPR_CLRPEND12_SHIFT                12
#define NVIC_ICPR_CLRPEND13_MASK                 0x2000u
#define NVIC_ICPR_CLRPEND13_SHIFT                13
#define NVIC_ICPR_CLRPEND14_MASK                 0x4000u
#define NVIC_ICPR_CLRPEND14_SHIFT                14
#define NVIC_ICPR_CLRPEND15_MASK                 0x8000u
#define NVIC_ICPR_CLRPEND15_SHIFT                15
#define NVIC_ICPR_CLRPEND16_MASK                 0x10000u
#define NVIC_ICPR_CLRPEND16_SHIFT                16
#define NVIC_ICPR_CLRPEND17_MASK                 0x20000u
#define NVIC_ICPR_CLRPEND17_SHIFT                17
#define NVIC_ICPR_CLRPEND18_MASK                 0x40000u
#define NVIC_ICPR_CLRPEND18_SHIFT                18
#define NVIC_ICPR_CLRPEND19_MASK                 0x80000u
#define NVIC_ICPR_CLRPEND19_SHIFT                19
#define NVIC_ICPR_CLRPEND20_MASK                 0x100000u
#define NVIC_ICPR_CLRPEND20_SHIFT                20
#define NVIC_ICPR_CLRPEND21_MASK                 0x200000u
#define NVIC_ICPR_CLRPEND21_SHIFT                21
#define NVIC_ICPR_CLRPEND22_MASK                 0x400000u
#define NVIC_ICPR_CLRPEND22_SHIFT                22
#define NVIC_ICPR_CLRPEND23_MASK                 0x800000u
#define NVIC_ICPR_CLRPEND23_SHIFT                23
#define NVIC_ICPR_CLRPEND24_MASK                 0x1000000u
#define NVIC_ICPR_CLRPEND24_SHIFT                24
#define NVIC_ICPR_CLRPEND25_MASK                 0x2000000u
#define NVIC_ICPR_CLRPEND25_SHIFT                25
#define NVIC_ICPR_CLRPEND26_MASK                 0x4000000u
#define NVIC_ICPR_CLRPEND26_SHIFT                26
#define NVIC_ICPR_CLRPEND27_MASK                 0x8000000u
#define NVIC_ICPR_CLRPEND27_SHIFT                27
#define NVIC_ICPR_CLRPEND28_MASK                 0x10000000u
#define NVIC_ICPR_CLRPEND28_SHIFT                28
#define NVIC_ICPR_CLRPEND29_MASK                 0x20000000u
#define NVIC_ICPR_CLRPEND29_SHIFT                29
#define NVIC_ICPR_CLRPEND30_MASK                 0x40000000u
#define NVIC_ICPR_CLRPEND30_SHIFT                30
#define NVIC_ICPR_CLRPEND31_MASK                 0x80000000u
#define NVIC_ICPR_CLRPEND31_SHIFT                31
/* IP Bit Fields */
#define NVIC_IP_PRI_0_MASK                       0xC0u
#define NVIC_IP_PRI_0_SHIFT                      6
#define NVIC_IP_PRI_0(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_0_SHIFT))&NVIC_IP_PRI_0_MASK)
#define NVIC_IP_PRI_28_MASK                      0xC0u
#define NVIC_IP_PRI_28_SHIFT                     6
#define NVIC_IP_PRI_28(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_28_SHIFT))&NVIC_IP_PRI_28_MASK)
#define NVIC_IP_PRI_24_MASK                      0xC0u
#define NVIC_IP_PRI_24_SHIFT                     6
#define NVIC_IP_PRI_24(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_24_SHIFT))&NVIC_IP_PRI_24_MASK)
#define NVIC_IP_PRI_20_MASK                      0xC0u
#define NVIC_IP_PRI_20_SHIFT                     6
#define NVIC_IP_PRI_20(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_20_SHIFT))&NVIC_IP_PRI_20_MASK)
#define NVIC_IP_PRI_4_MASK                       0xC0u
#define NVIC_IP_PRI_4_SHIFT                      6
#define NVIC_IP_PRI_4(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_4_SHIFT))&NVIC_IP_PRI_4_MASK)
#define NVIC_IP_PRI_16_MASK                      0xC0u
#define NVIC_IP_PRI_16_SHIFT                     6
#define NVIC_IP_PRI_16(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_16_SHIFT))&NVIC_IP_PRI_16_MASK)
#define NVIC_IP_PRI_12_MASK                      0xC0u
#define NVIC_IP_PRI_12_SHIFT                     6
#define NVIC_IP_PRI_12(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_12_SHIFT))&NVIC_IP_PRI_12_MASK)
#define NVIC_IP_PRI_8_MASK                       0xC0u
#define NVIC_IP_PRI_8_SHIFT                      6
#define NVIC_IP_PRI_8(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_8_SHIFT))&NVIC_IP_PRI_8_MASK)
#define NVIC_IP_PRI_13_MASK                      0xC000u
#define NVIC_IP_PRI_13_SHIFT                     14
#define NVIC_IP_PRI_13(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_13_SHIFT))&NVIC_IP_PRI_13_MASK)
#define NVIC_IP_PRI_21_MASK                      0xC000u
#define NVIC_IP_PRI_21_SHIFT                     14
#define NVIC_IP_PRI_21(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_21_SHIFT))&NVIC_IP_PRI_21_MASK)
#define NVIC_IP_PRI_29_MASK                      0xC000u
#define NVIC_IP_PRI_29_SHIFT                     14
#define NVIC_IP_PRI_29(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_29_SHIFT))&NVIC_IP_PRI_29_MASK)
#define NVIC_IP_PRI_1_MASK                       0xC000u
#define NVIC_IP_PRI_1_SHIFT                      14
#define NVIC_IP_PRI_1(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_1_SHIFT))&NVIC_IP_PRI_1_MASK)
#define NVIC_IP_PRI_9_MASK                       0xC000u
#define NVIC_IP_PRI_9_SHIFT                      14
#define NVIC_IP_PRI_9(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_9_SHIFT))&NVIC_IP_PRI_9_MASK)
#define NVIC_IP_PRI_17_MASK                      0xC000u
#define NVIC_IP_PRI_17_SHIFT                     14
#define NVIC_IP_PRI_17(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_17_SHIFT))&NVIC_IP_PRI_17_MASK)
#define NVIC_IP_PRI_25_MASK                      0xC000u
#define NVIC_IP_PRI_25_SHIFT                     14
#define NVIC_IP_PRI_25(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_25_SHIFT))&NVIC_IP_PRI_25_MASK)
#define NVIC_IP_PRI_5_MASK                       0xC000u
#define NVIC_IP_PRI_5_SHIFT                      14
#define NVIC_IP_PRI_5(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_5_SHIFT))&NVIC_IP_PRI_5_MASK)
#define NVIC_IP_PRI_2_MASK                       0xC00000u
#define NVIC_IP_PRI_2_SHIFT                      22
#define NVIC_IP_PRI_2(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_2_SHIFT))&NVIC_IP_PRI_2_MASK)
#define NVIC_IP_PRI_26_MASK                      0xC00000u
#define NVIC_IP_PRI_26_SHIFT                     22
#define NVIC_IP_PRI_26(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_26_SHIFT))&NVIC_IP_PRI_26_MASK)
#define NVIC_IP_PRI_18_MASK                      0xC00000u
#define NVIC_IP_PRI_18_SHIFT                     22
#define NVIC_IP_PRI_18(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_18_SHIFT))&NVIC_IP_PRI_18_MASK)
#define NVIC_IP_PRI_14_MASK                      0xC00000u
#define NVIC_IP_PRI_14_SHIFT                     22
#define NVIC_IP_PRI_14(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_14_SHIFT))&NVIC_IP_PRI_14_MASK)
#define NVIC_IP_PRI_6_MASK                       0xC00000u
#define NVIC_IP_PRI_6_SHIFT                      22
#define NVIC_IP_PRI_6(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_6_SHIFT))&NVIC_IP_PRI_6_MASK)
#define NVIC_IP_PRI_30_MASK                      0xC00000u
#define NVIC_IP_PRI_30_SHIFT                     22
#define NVIC_IP_PRI_30(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_30_SHIFT))&NVIC_IP_PRI_30_MASK)
#define NVIC_IP_PRI_22_MASK                      0xC00000u
#define NVIC_IP_PRI_22_SHIFT                     22
#define NVIC_IP_PRI_22(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_22_SHIFT))&NVIC_IP_PRI_22_MASK)
#define NVIC_IP_PRI_10_MASK                      0xC00000u
#define NVIC_IP_PRI_10_SHIFT                     22
#define NVIC_IP_PRI_10(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_10_SHIFT))&NVIC_IP_PRI_10_MASK)
#define NVIC_IP_PRI_31_MASK                      0xC0000000u
#define NVIC_IP_PRI_31_SHIFT                     30
#define NVIC_IP_PRI_31(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_31_SHIFT))&NVIC_IP_PRI_31_MASK)
#define NVIC_IP_PRI_27_MASK                      0xC0000000u
#define NVIC_IP_PRI_27_SHIFT                     30
#define NVIC_IP_PRI_27(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_27_SHIFT))&NVIC_IP_PRI_27_MASK)
#define NVIC_IP_PRI_23_MASK                      0xC0000000u
#define NVIC_IP_PRI_23_SHIFT                     30
#define NVIC_IP_PRI_23(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_23_SHIFT))&NVIC_IP_PRI_23_MASK)
#define NVIC_IP_PRI_3_MASK                       0xC0000000u
#define NVIC_IP_PRI_3_SHIFT                      30
#define NVIC_IP_PRI_3(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_3_SHIFT))&NVIC_IP_PRI_3_MASK)
#define NVIC_IP_PRI_19_MASK                      0xC0000000u
#define NVIC_IP_PRI_19_SHIFT                     30
#define NVIC_IP_PRI_19(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_19_SHIFT))&NVIC_IP_PRI_19_MASK)
#define NVIC_IP_PRI_15_MASK                      0xC0000000u
#define NVIC_IP_PRI_15_SHIFT                     30
#define NVIC_IP_PRI_15(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_15_SHIFT))&NVIC_IP_PRI_15_MASK)
#define NVIC_IP_PRI_11_MASK                      0xC0000000u
#define NVIC_IP_PRI_11_SHIFT                     30
#define NVIC_IP_PRI_11(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_11_SHIFT))&NVIC_IP_PRI_11_MASK)
#define NVIC_IP_PRI_7_MASK                       0xC0000000u
#define NVIC_IP_PRI_7_SHIFT                      30
#define NVIC_IP_PRI_7(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_7_SHIFT))&NVIC_IP_PRI_7_MASK)

/*!
 * @}
 */ /* end of group NVIC_Register_Masks */


/* NVIC - Peripheral instance base addresses */
/** Peripheral NVIC base pointer */
#define NVIC_BASE_PTR                            ((NVIC_MemMapPtr)0xE000E100u)
/** Array initializer of NVIC peripheral base pointers */
#define NVIC_BASE_PTRS                           { NVIC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register instance definitions */
/* NVIC */
#define NVIC_ISER                                NVIC_ISER_REG(NVIC_BASE_PTR)
#define NVIC_ICER                                NVIC_ICER_REG(NVIC_BASE_PTR)
#define NVIC_ISPR                                NVIC_ISPR_REG(NVIC_BASE_PTR)
#define NVIC_ICPR                                NVIC_ICPR_REG(NVIC_BASE_PTR)
#define NVIC_IPR0                                NVIC_IP_REG(NVIC_BASE_PTR,0)
#define NVIC_IPR1                                NVIC_IP_REG(NVIC_BASE_PTR,1)
#define NVIC_IPR2                                NVIC_IP_REG(NVIC_BASE_PTR,2)
#define NVIC_IPR3                                NVIC_IP_REG(NVIC_BASE_PTR,3)
#define NVIC_IPR4                                NVIC_IP_REG(NVIC_BASE_PTR,4)
#define NVIC_IPR5                                NVIC_IP_REG(NVIC_BASE_PTR,5)
#define NVIC_IPR6                                NVIC_IP_REG(NVIC_BASE_PTR,6)
#define NVIC_IPR7                                NVIC_IP_REG(NVIC_BASE_PTR,7)

/* NVIC - Register array accessors */
#define NVIC_IP(index)                           NVIC_IP_REG(NVIC_BASE_PTR,index)

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NVIC_Peripheral */


/* ----------------------------------------------------------------------------
   -- OSC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Peripheral OSC
 * @{
 */

/** OSC - Peripheral register structure */
typedef struct OSC_MemMap {
  uint8_t CR;                                      /**< OSC Control Register, offset: 0x0 */
} volatile *OSC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register accessors */
#define OSC_CR_REG(base)                         ((base)->CR)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/* CR Bit Fields */
#define OSC_CR_OSCINIT_MASK                      0x1u
#define OSC_CR_OSCINIT_SHIFT                     0
#define OSC_CR_HGO_MASK                          0x2u
#define OSC_CR_HGO_SHIFT                         1
#define OSC_CR_RANGE_MASK                        0x4u
#define OSC_CR_RANGE_SHIFT                       2
#define OSC_CR_OSCOS_MASK                        0x10u
#define OSC_CR_OSCOS_SHIFT                       4
#define OSC_CR_OSCSTEN_MASK                      0x20u
#define OSC_CR_OSCSTEN_SHIFT                     5
#define OSC_CR_OSCEN_MASK                        0x80u
#define OSC_CR_OSCEN_SHIFT                       7

/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC base pointer */
#define OSC_BASE_PTR                             ((OSC_MemMapPtr)0x40065000u)
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register instance definitions */
/* OSC */
#define OSC_CR                                   OSC_CR_REG(OSC_BASE_PTR)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group OSC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PGA
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PGA_Peripheral PGA
 * @{
 */

/** PGA - Peripheral register structure */
typedef struct PGA_MemMap {
  uint8_t CTRL;                                    /**< Control Register, offset: 0x0 */
} volatile *PGA_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PGA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PGA_Register_Accessor_Macros PGA - Register accessor macros
 * @{
 */


/* PGA - Register accessors */
#define PGA_CTRL_REG(base)                       ((base)->CTRL)

/*!
 * @}
 */ /* end of group PGA_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PGA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PGA_Register_Masks PGA Register Masks
 * @{
 */

/* CTRL Bit Fields */
#define PGA_CTRL_PGAEN_MASK                      0x1u
#define PGA_CTRL_PGAEN_SHIFT                     0
#define PGA_CTRL_GAIN_MASK                       0x6u
#define PGA_CTRL_GAIN_SHIFT                      1
#define PGA_CTRL_GAIN(x)                         (((uint8_t)(((uint8_t)(x))<<PGA_CTRL_GAIN_SHIFT))&PGA_CTRL_GAIN_MASK)

/*!
 * @}
 */ /* end of group PGA_Register_Masks */


/* PGA - Peripheral instance base addresses */
/** Peripheral PGA base pointer */
#define PGA_BASE_PTR                             ((PGA_MemMapPtr)0x40071000u)
/** Array initializer of PGA peripheral base pointers */
#define PGA_BASE_PTRS                            { PGA_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PGA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PGA_Register_Accessor_Macros PGA - Register accessor macros
 * @{
 */


/* PGA - Register instance definitions */
/* PGA */
#define PGA_CTRL                                 PGA_CTRL_REG(PGA_BASE_PTR)

/*!
 * @}
 */ /* end of group PGA_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PGA_Peripheral */


/* ----------------------------------------------------------------------------
   -- PIT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral PIT
 * @{
 */

/** PIT - Peripheral register structure */
typedef struct PIT_MemMap {
  uint32_t MCR;                                    /**< PIT Module Control Register, offset: 0x0 */
  uint8_t RESERVED_0[252];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    uint32_t LDVAL;                                  /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    uint32_t CVAL;                                   /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    uint32_t TCTRL;                                  /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    uint32_t TFLG;                                   /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} volatile *PIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register accessors */
#define PIT_MCR_REG(base)                        ((base)->MCR)
#define PIT_LDVAL_REG(base,index)                ((base)->CHANNEL[index].LDVAL)
#define PIT_CVAL_REG(base,index)                 ((base)->CHANNEL[index].CVAL)
#define PIT_TCTRL_REG(base,index)                ((base)->CHANNEL[index].TCTRL)
#define PIT_TFLG_REG(base,index)                 ((base)->CHANNEL[index].TFLG)

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/* MCR Bit Fields */
#define PIT_MCR_FRZ_MASK                         0x1u
#define PIT_MCR_FRZ_SHIFT                        0
#define PIT_MCR_MDIS_MASK                        0x2u
#define PIT_MCR_MDIS_SHIFT                       1
/* LDVAL Bit Fields */
#define PIT_LDVAL_TSV_MASK                       0xFFFFFFFFu
#define PIT_LDVAL_TSV_SHIFT                      0
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_LDVAL_TSV_SHIFT))&PIT_LDVAL_TSV_MASK)
/* CVAL Bit Fields */
#define PIT_CVAL_TVL_MASK                        0xFFFFFFFFu
#define PIT_CVAL_TVL_SHIFT                       0
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_CVAL_TVL_SHIFT))&PIT_CVAL_TVL_MASK)
/* TCTRL Bit Fields */
#define PIT_TCTRL_TEN_MASK                       0x1u
#define PIT_TCTRL_TEN_SHIFT                      0
#define PIT_TCTRL_TIE_MASK                       0x2u
#define PIT_TCTRL_TIE_SHIFT                      1
#define PIT_TCTRL_CHN_MASK                       0x4u
#define PIT_TCTRL_CHN_SHIFT                      2
/* TFLG Bit Fields */
#define PIT_TFLG_TIF_MASK                        0x1u
#define PIT_TFLG_TIF_SHIFT                       0

/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT base pointer */
#define PIT_BASE_PTR                             ((PIT_MemMapPtr)0x40037000u)
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register instance definitions */
/* PIT */
#define PIT_MCR                                  PIT_MCR_REG(PIT_BASE_PTR)
#define PIT_LDVAL0                               PIT_LDVAL_REG(PIT_BASE_PTR,0)
#define PIT_CVAL0                                PIT_CVAL_REG(PIT_BASE_PTR,0)
#define PIT_TCTRL0                               PIT_TCTRL_REG(PIT_BASE_PTR,0)
#define PIT_TFLG0                                PIT_TFLG_REG(PIT_BASE_PTR,0)
#define PIT_LDVAL1                               PIT_LDVAL_REG(PIT_BASE_PTR,1)
#define PIT_CVAL1                                PIT_CVAL_REG(PIT_BASE_PTR,1)
#define PIT_TCTRL1                               PIT_TCTRL_REG(PIT_BASE_PTR,1)
#define PIT_TFLG1                                PIT_TFLG_REG(PIT_BASE_PTR,1)

/* PIT - Register array accessors */
#define PIT_LDVAL(index)                         PIT_LDVAL_REG(PIT_BASE_PTR,index)
#define PIT_CVAL(index)                          PIT_CVAL_REG(PIT_BASE_PTR,index)
#define PIT_TCTRL(index)                         PIT_TCTRL_REG(PIT_BASE_PTR,index)
#define PIT_TFLG(index)                          PIT_TFLG_REG(PIT_BASE_PTR,index)

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PIT_Peripheral */


/* ----------------------------------------------------------------------------
   -- PMC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral PMC
 * @{
 */

/** PMC - Peripheral register structure */
typedef struct PMC_MemMap {
  uint8_t CTRL;                                    /**< Control Register, offset: 0x0 */
  uint8_t RST;                                     /**< Reset Flags Register, offset: 0x1 */
  uint8_t TPCTRLSTAT;                              /**< Temperature Control and Status Register, offset: 0x2 */
  uint8_t TPTM;                                    /**< Temperature Offset Step Trim Register, offset: 0x3 */
  uint8_t RC20KTRM;                                /**< RC Oscillator Offset Step Trim Register, offset: 0x4 */
  uint8_t LVCTLSTAT1;                              /**< Low Voltage Control and Status Register 1 (system 5 V), offset: 0x5 */
  uint8_t LVCTLSTAT2;                              /**< Low Voltage Control and Status Register 2 (VREFH), offset: 0x6 */
  uint8_t VREFHCFG;                                /**< VREFH Configuration Register, offset: 0x7 */
  uint8_t VREFHLVW;                                /**< VREFH Low Voltage Warning (LVW) Configuration Register, offset: 0x8 */
  uint8_t STAT;                                    /**< Status Register, offset: 0x9 */
} volatile *PMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register accessors */
#define PMC_CTRL_REG(base)                       ((base)->CTRL)
#define PMC_RST_REG(base)                        ((base)->RST)
#define PMC_TPCTRLSTAT_REG(base)                 ((base)->TPCTRLSTAT)
#define PMC_TPTM_REG(base)                       ((base)->TPTM)
#define PMC_RC20KTRM_REG(base)                   ((base)->RC20KTRM)
#define PMC_LVCTLSTAT1_REG(base)                 ((base)->LVCTLSTAT1)
#define PMC_LVCTLSTAT2_REG(base)                 ((base)->LVCTLSTAT2)
#define PMC_VREFHCFG_REG(base)                   ((base)->VREFHCFG)
#define PMC_VREFHLVW_REG(base)                   ((base)->VREFHLVW)
#define PMC_STAT_REG(base)                       ((base)->STAT)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/* CTRL Bit Fields */
#define PMC_CTRL_RC20KENSTP_MASK                 0x2u
#define PMC_CTRL_RC20KENSTP_SHIFT                1
#define PMC_CTRL_VREFDN_MASK                     0x4u
#define PMC_CTRL_VREFDN_SHIFT                    2
#define PMC_CTRL_GWREN_MASK                      0x80u
#define PMC_CTRL_GWREN_SHIFT                     7
/* RST Bit Fields */
#define PMC_RST_LVRF_MASK                        0x20u
#define PMC_RST_LVRF_SHIFT                       5
#define PMC_RST_PORF_MASK                        0x40u
#define PMC_RST_PORF_SHIFT                       6
/* TPCTRLSTAT Bit Fields */
#define PMC_TPCTRLSTAT_HTIF_MASK                 0x1u
#define PMC_TPCTRLSTAT_HTIF_SHIFT                0
#define PMC_TPCTRLSTAT_HTIE_MASK                 0x2u
#define PMC_TPCTRLSTAT_HTIE_SHIFT                1
#define PMC_TPCTRLSTAT_HTDS_MASK                 0x4u
#define PMC_TPCTRLSTAT_HTDS_SHIFT                2
#define PMC_TPCTRLSTAT_TEMPEN_MASK               0x8u
#define PMC_TPCTRLSTAT_TEMPEN_SHIFT              3
#define PMC_TPCTRLSTAT_SWON_MASK                 0x10u
#define PMC_TPCTRLSTAT_SWON_SHIFT                4
/* TPTM Bit Fields */
#define PMC_TPTM_TOT_MASK                        0xFu
#define PMC_TPTM_TOT_SHIFT                       0
#define PMC_TPTM_TOT(x)                          (((uint8_t)(((uint8_t)(x))<<PMC_TPTM_TOT_SHIFT))&PMC_TPTM_TOT_MASK)
#define PMC_TPTM_TRMTPEN_MASK                    0x80u
#define PMC_TPTM_TRMTPEN_SHIFT                   7
/* RC20KTRM Bit Fields */
#define PMC_RC20KTRM_OSCOT_MASK                  0x3Fu
#define PMC_RC20KTRM_OSCOT_SHIFT                 0
#define PMC_RC20KTRM_OSCOT(x)                    (((uint8_t)(((uint8_t)(x))<<PMC_RC20KTRM_OSCOT_SHIFT))&PMC_RC20KTRM_OSCOT_MASK)
/* LVCTLSTAT1 Bit Fields */
#define PMC_LVCTLSTAT1_SLVWSEL_MASK              0x2u
#define PMC_LVCTLSTAT1_SLVWSEL_SHIFT             1
#define PMC_LVCTLSTAT1_SLVWIE_MASK               0x4u
#define PMC_LVCTLSTAT1_SLVWIE_SHIFT              2
#define PMC_LVCTLSTAT1_SLVWACK_MASK              0x8u
#define PMC_LVCTLSTAT1_SLVWACK_SHIFT             3
#define PMC_LVCTLSTAT1_SLVWF_MASK                0x10u
#define PMC_LVCTLSTAT1_SLVWF_SHIFT               4
/* LVCTLSTAT2 Bit Fields */
#define PMC_LVCTLSTAT2_RLVWIE_MASK               0x4u
#define PMC_LVCTLSTAT2_RLVWIE_SHIFT              2
#define PMC_LVCTLSTAT2_RLVWACK_MASK              0x8u
#define PMC_LVCTLSTAT2_RLVWACK_SHIFT             3
#define PMC_LVCTLSTAT2_RLVWF_MASK                0x10u
#define PMC_LVCTLSTAT2_RLVWF_SHIFT               4
/* VREFHCFG Bit Fields */
#define PMC_VREFHCFG_T5V_MASK                    0x3Fu
#define PMC_VREFHCFG_T5V_SHIFT                   0
#define PMC_VREFHCFG_T5V(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_VREFHCFG_T5V_SHIFT))&PMC_VREFHCFG_T5V_MASK)
/* VREFHLVW Bit Fields */
#define PMC_VREFHLVW_LVWCFG_MASK                 0x3u
#define PMC_VREFHLVW_LVWCFG_SHIFT                0
#define PMC_VREFHLVW_LVWCFG(x)                   (((uint8_t)(((uint8_t)(x))<<PMC_VREFHLVW_LVWCFG_SHIFT))&PMC_VREFHLVW_LVWCFG_MASK)
/* STAT Bit Fields */
#define PMC_STAT_VREFRDY_MASK                    0x1u
#define PMC_STAT_VREFRDY_SHIFT                   0
#define PMC_STAT_HBGRDY_MASK                     0x4u
#define PMC_STAT_HBGRDY_SHIFT                    2

/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base pointer */
#define PMC_BASE_PTR                             ((PMC_MemMapPtr)0x4007D000u)
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register instance definitions */
/* PMC */
#define PMC_CTRL                                 PMC_CTRL_REG(PMC_BASE_PTR)
#define PMC_RST                                  PMC_RST_REG(PMC_BASE_PTR)
#define PMC_TPCTRLSTAT                           PMC_TPCTRLSTAT_REG(PMC_BASE_PTR)
#define PMC_TPTM                                 PMC_TPTM_REG(PMC_BASE_PTR)
#define PMC_RC20KTRM                             PMC_RC20KTRM_REG(PMC_BASE_PTR)
#define PMC_LVCTLSTAT1                           PMC_LVCTLSTAT1_REG(PMC_BASE_PTR)
#define PMC_LVCTLSTAT2                           PMC_LVCTLSTAT2_REG(PMC_BASE_PTR)
#define PMC_VREFHCFG                             PMC_VREFHCFG_REG(PMC_BASE_PTR)
#define PMC_VREFHLVW                             PMC_VREFHLVW_REG(PMC_BASE_PTR)
#define PMC_STAT                                 PMC_STAT_REG(PMC_BASE_PTR)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PORT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral PORT
 * @{
 */

/** PORT - Peripheral register structure */
typedef struct PORT_MemMap {
  uint32_t IOFLT0;                                 /**< Port Filter Control Register 0, offset: 0x0 */
  uint32_t PUE0;                                   /**< Port Pullup Enable Register 0, offset: 0x4 */
} volatile *PORT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register accessors */
#define PORT_IOFLT0_REG(base)                    ((base)->IOFLT0)
#define PORT_PUE0_REG(base)                      ((base)->PUE0)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/* IOFLT0 Bit Fields */
#define PORT_IOFLT0_FLTRST_MASK                  0x3u
#define PORT_IOFLT0_FLTRST_SHIFT                 0
#define PORT_IOFLT0_FLTRST(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTRST_SHIFT))&PORT_IOFLT0_FLTRST_MASK)
#define PORT_IOFLT0_FLTDIV1_MASK                 0x3000000u
#define PORT_IOFLT0_FLTDIV1_SHIFT                24
#define PORT_IOFLT0_FLTDIV1(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTDIV1_SHIFT))&PORT_IOFLT0_FLTDIV1_MASK)
#define PORT_IOFLT0_FLTDIV2_MASK                 0x1C000000u
#define PORT_IOFLT0_FLTDIV2_SHIFT                26
#define PORT_IOFLT0_FLTDIV2(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTDIV2_SHIFT))&PORT_IOFLT0_FLTDIV2_MASK)
#define PORT_IOFLT0_FLTDIV3_MASK                 0xE0000000u
#define PORT_IOFLT0_FLTDIV3_SHIFT                29
#define PORT_IOFLT0_FLTDIV3(x)                   (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT0_FLTDIV3_SHIFT))&PORT_IOFLT0_FLTDIV3_MASK)
/* PUE0 Bit Fields */
#define PORT_PUE0_PTAPE0_MASK                    0x1u
#define PORT_PUE0_PTAPE0_SHIFT                   0
#define PORT_PUE0_PTAPE1_MASK                    0x2u
#define PORT_PUE0_PTAPE1_SHIFT                   1
#define PORT_PUE0_PTAPE2_MASK                    0x4u
#define PORT_PUE0_PTAPE2_SHIFT                   2
#define PORT_PUE0_PTAPE3_MASK                    0x8u
#define PORT_PUE0_PTAPE3_SHIFT                   3
#define PORT_PUE0_PTAPE4_MASK                    0x10u
#define PORT_PUE0_PTAPE4_SHIFT                   4
#define PORT_PUE0_PTAPE5_MASK                    0x20u
#define PORT_PUE0_PTAPE5_SHIFT                   5
#define PORT_PUE0_PTAPE6_MASK                    0x40u
#define PORT_PUE0_PTAPE6_SHIFT                   6
#define PORT_PUE0_PTAPE7_MASK                    0x80u
#define PORT_PUE0_PTAPE7_SHIFT                   7
#define PORT_PUE0_PTBPE0_MASK                    0x100u
#define PORT_PUE0_PTBPE0_SHIFT                   8
#define PORT_PUE0_PTBPE1_MASK                    0x200u
#define PORT_PUE0_PTBPE1_SHIFT                   9
#define PORT_PUE0_PTBPE2_MASK                    0x400u
#define PORT_PUE0_PTBPE2_SHIFT                   10
#define PORT_PUE0_PTBPE3_MASK                    0x800u
#define PORT_PUE0_PTBPE3_SHIFT                   11
#define PORT_PUE0_PTBPE4_MASK                    0x1000u
#define PORT_PUE0_PTBPE4_SHIFT                   12

/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORT base pointer */
#define PORT_BASE_PTR                            ((PORT_MemMapPtr)0x40049000u)
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register instance definitions */
/* PORT */
#define PORT_IOFLT0                              PORT_IOFLT0_REG(PORT_BASE_PTR)
#define PORT_PUE0                                PORT_PUE0_REG(PORT_BASE_PTR)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PORT_Peripheral */


/* ----------------------------------------------------------------------------
   -- RTC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral RTC
 * @{
 */

/** RTC - Peripheral register structure */
typedef struct RTC_MemMap {
  uint32_t SC;                                     /**< RTC Status and Control Register, offset: 0x0 */
  uint32_t MOD;                                    /**< RTC Modulo Register, offset: 0x4 */
  uint32_t CNT;                                    /**< RTC Counter Register, offset: 0x8 */
} volatile *RTC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register accessors */
#define RTC_SC_REG(base)                         ((base)->SC)
#define RTC_MOD_REG(base)                        ((base)->MOD)
#define RTC_CNT_REG(base)                        ((base)->CNT)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/* SC Bit Fields */
#define RTC_SC_RTCO_MASK                         0x10u
#define RTC_SC_RTCO_SHIFT                        4
#define RTC_SC_RTIE_MASK                         0x40u
#define RTC_SC_RTIE_SHIFT                        6
#define RTC_SC_RTIF_MASK                         0x80u
#define RTC_SC_RTIF_SHIFT                        7
#define RTC_SC_RTCPS_MASK                        0x700u
#define RTC_SC_RTCPS_SHIFT                       8
#define RTC_SC_RTCPS(x)                          (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTCPS_SHIFT))&RTC_SC_RTCPS_MASK)
#define RTC_SC_RTCLKS_MASK                       0xC000u
#define RTC_SC_RTCLKS_SHIFT                      14
#define RTC_SC_RTCLKS(x)                         (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTCLKS_SHIFT))&RTC_SC_RTCLKS_MASK)
/* MOD Bit Fields */
#define RTC_MOD_MOD_MASK                         0xFFFFu
#define RTC_MOD_MOD_SHIFT                        0
#define RTC_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_MOD_MOD_SHIFT))&RTC_MOD_MOD_MASK)
/* CNT Bit Fields */
#define RTC_CNT_CNT_MASK                         0xFFFFu
#define RTC_CNT_CNT_SHIFT                        0
#define RTC_CNT_CNT(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_CNT_CNT_SHIFT))&RTC_CNT_CNT_MASK)

/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base pointer */
#define RTC_BASE_PTR                             ((RTC_MemMapPtr)0x4003D000u)
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register instance definitions */
/* RTC */
#define RTC_SC                                   RTC_SC_REG(RTC_BASE_PTR)
#define RTC_MOD                                  RTC_MOD_REG(RTC_BASE_PTR)
#define RTC_CNT                                  RTC_CNT_REG(RTC_BASE_PTR)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RTC_Peripheral */


/* ----------------------------------------------------------------------------
   -- SCB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Peripheral SCB
 * @{
 */

/** SCB - Peripheral register structure */
typedef struct SCB_MemMap {
  uint8_t RESERVED_0[8];
  uint32_t ACTLR;                                  /**< Auxiliary Control Register,, offset: 0x8 */
  uint8_t RESERVED_1[3316];
  uint32_t CPUID;                                  /**< CPUID Base Register, offset: 0xD00 */
  uint32_t ICSR;                                   /**< Interrupt Control and State Register, offset: 0xD04 */
  uint32_t VTOR;                                   /**< Vector Table Offset Register, offset: 0xD08 */
  uint32_t AIRCR;                                  /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  uint32_t SCR;                                    /**< System Control Register, offset: 0xD10 */
  uint32_t CCR;                                    /**< Configuration and Control Register, offset: 0xD14 */
  uint8_t RESERVED_2[4];
  uint32_t SHPR2;                                  /**< System Handler Priority Register 2, offset: 0xD1C */
  uint32_t SHPR3;                                  /**< System Handler Priority Register 3, offset: 0xD20 */
  uint32_t SHCSR;                                  /**< System Handler Control and State Register, offset: 0xD24 */
  uint8_t RESERVED_3[8];
  uint32_t DFSR;                                   /**< Debug Fault Status Register, offset: 0xD30 */
} volatile *SCB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register accessors */
#define SCB_ACTLR_REG(base)                      ((base)->ACTLR)
#define SCB_CPUID_REG(base)                      ((base)->CPUID)
#define SCB_ICSR_REG(base)                       ((base)->ICSR)
#define SCB_VTOR_REG(base)                       ((base)->VTOR)
#define SCB_AIRCR_REG(base)                      ((base)->AIRCR)
#define SCB_SCR_REG(base)                        ((base)->SCR)
#define SCB_CCR_REG(base)                        ((base)->CCR)
#define SCB_SHPR2_REG(base)                      ((base)->SHPR2)
#define SCB_SHPR3_REG(base)                      ((base)->SHPR3)
#define SCB_SHCSR_REG(base)                      ((base)->SHCSR)
#define SCB_DFSR_REG(base)                       ((base)->DFSR)

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SCB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Masks SCB Register Masks
 * @{
 */

/* CPUID Bit Fields */
#define SCB_CPUID_REVISION_MASK                  0xFu
#define SCB_CPUID_REVISION_SHIFT                 0
#define SCB_CPUID_REVISION(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_REVISION_SHIFT))&SCB_CPUID_REVISION_MASK)
#define SCB_CPUID_PARTNO_MASK                    0xFFF0u
#define SCB_CPUID_PARTNO_SHIFT                   4
#define SCB_CPUID_PARTNO(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_PARTNO_SHIFT))&SCB_CPUID_PARTNO_MASK)
#define SCB_CPUID_VARIANT_MASK                   0xF00000u
#define SCB_CPUID_VARIANT_SHIFT                  20
#define SCB_CPUID_VARIANT(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_VARIANT_SHIFT))&SCB_CPUID_VARIANT_MASK)
#define SCB_CPUID_IMPLEMENTER_MASK               0xFF000000u
#define SCB_CPUID_IMPLEMENTER_SHIFT              24
#define SCB_CPUID_IMPLEMENTER(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_IMPLEMENTER_SHIFT))&SCB_CPUID_IMPLEMENTER_MASK)
/* ICSR Bit Fields */
#define SCB_ICSR_VECTPENDING_MASK                0x3F000u
#define SCB_ICSR_VECTPENDING_SHIFT               12
#define SCB_ICSR_VECTPENDING(x)                  (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_VECTPENDING_SHIFT))&SCB_ICSR_VECTPENDING_MASK)
#define SCB_ICSR_PENDSTCLR_MASK                  0x2000000u
#define SCB_ICSR_PENDSTCLR_SHIFT                 25
#define SCB_ICSR_PENDSTSET_MASK                  0x4000000u
#define SCB_ICSR_PENDSTSET_SHIFT                 26
#define SCB_ICSR_PENDSVCLR_MASK                  0x8000000u
#define SCB_ICSR_PENDSVCLR_SHIFT                 27
#define SCB_ICSR_PENDSVSET_MASK                  0x10000000u
#define SCB_ICSR_PENDSVSET_SHIFT                 28
#define SCB_ICSR_NMIPENDSET_MASK                 0x80000000u
#define SCB_ICSR_NMIPENDSET_SHIFT                31
/* VTOR Bit Fields */
#define SCB_VTOR_TBLOFF_MASK                     0xFFFFFF80u
#define SCB_VTOR_TBLOFF_SHIFT                    7
#define SCB_VTOR_TBLOFF(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_VTOR_TBLOFF_SHIFT))&SCB_VTOR_TBLOFF_MASK)
/* AIRCR Bit Fields */
#define SCB_AIRCR_VECTCLRACTIVE_MASK             0x2u
#define SCB_AIRCR_VECTCLRACTIVE_SHIFT            1
#define SCB_AIRCR_SYSRESETREQ_MASK               0x4u
#define SCB_AIRCR_SYSRESETREQ_SHIFT              2
#define SCB_AIRCR_ENDIANNESS_MASK                0x8000u
#define SCB_AIRCR_ENDIANNESS_SHIFT               15
#define SCB_AIRCR_VECTKEY_MASK                   0xFFFF0000u
#define SCB_AIRCR_VECTKEY_SHIFT                  16
#define SCB_AIRCR_VECTKEY(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_VECTKEY_SHIFT))&SCB_AIRCR_VECTKEY_MASK)
/* SCR Bit Fields */
#define SCB_SCR_SLEEPONEXIT_MASK                 0x2u
#define SCB_SCR_SLEEPONEXIT_SHIFT                1
#define SCB_SCR_SLEEPDEEP_MASK                   0x4u
#define SCB_SCR_SLEEPDEEP_SHIFT                  2
#define SCB_SCR_SEVONPEND_MASK                   0x10u
#define SCB_SCR_SEVONPEND_SHIFT                  4
/* CCR Bit Fields */
#define SCB_CCR_UNALIGN_TRP_MASK                 0x8u
#define SCB_CCR_UNALIGN_TRP_SHIFT                3
#define SCB_CCR_STKALIGN_MASK                    0x200u
#define SCB_CCR_STKALIGN_SHIFT                   9
/* SHPR2 Bit Fields */
#define SCB_SHPR2_PRI_11_MASK                    0xC0000000u
#define SCB_SHPR2_PRI_11_SHIFT                   30
#define SCB_SHPR2_PRI_11(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR2_PRI_11_SHIFT))&SCB_SHPR2_PRI_11_MASK)
/* SHPR3 Bit Fields */
#define SCB_SHPR3_PRI_14_MASK                    0xC00000u
#define SCB_SHPR3_PRI_14_SHIFT                   22
#define SCB_SHPR3_PRI_14(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_14_SHIFT))&SCB_SHPR3_PRI_14_MASK)
#define SCB_SHPR3_PRI_15_MASK                    0xC0000000u
#define SCB_SHPR3_PRI_15_SHIFT                   30
#define SCB_SHPR3_PRI_15(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_15_SHIFT))&SCB_SHPR3_PRI_15_MASK)
/* SHCSR Bit Fields */
#define SCB_SHCSR_SVCALLPENDED_MASK              0x8000u
#define SCB_SHCSR_SVCALLPENDED_SHIFT             15
/* DFSR Bit Fields */
#define SCB_DFSR_HALTED_MASK                     0x1u
#define SCB_DFSR_HALTED_SHIFT                    0
#define SCB_DFSR_BKPT_MASK                       0x2u
#define SCB_DFSR_BKPT_SHIFT                      1
#define SCB_DFSR_DWTTRAP_MASK                    0x4u
#define SCB_DFSR_DWTTRAP_SHIFT                   2
#define SCB_DFSR_VCATCH_MASK                     0x8u
#define SCB_DFSR_VCATCH_SHIFT                    3
#define SCB_DFSR_EXTERNAL_MASK                   0x10u
#define SCB_DFSR_EXTERNAL_SHIFT                  4

/*!
 * @}
 */ /* end of group SCB_Register_Masks */


/* SCB - Peripheral instance base addresses */
/** Peripheral SystemControl base pointer */
#define SystemControl_BASE_PTR                   ((SCB_MemMapPtr)0xE000E000u)
/** Array initializer of SCB peripheral base pointers */
#define SCB_BASE_PTRS                            { SystemControl_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register instance definitions */
/* SystemControl */
#define SCB_ACTLR                                SCB_ACTLR_REG(SystemControl_BASE_PTR)
#define SCB_CPUID                                SCB_CPUID_REG(SystemControl_BASE_PTR)
#define SCB_ICSR                                 SCB_ICSR_REG(SystemControl_BASE_PTR)
#define SCB_VTOR                                 SCB_VTOR_REG(SystemControl_BASE_PTR)
#define SCB_AIRCR                                SCB_AIRCR_REG(SystemControl_BASE_PTR)
#define SCB_SCR                                  SCB_SCR_REG(SystemControl_BASE_PTR)
#define SCB_CCR                                  SCB_CCR_REG(SystemControl_BASE_PTR)
#define SCB_SHPR2                                SCB_SHPR2_REG(SystemControl_BASE_PTR)
#define SCB_SHPR3                                SCB_SHPR3_REG(SystemControl_BASE_PTR)
#define SCB_SHCSR                                SCB_SHCSR_REG(SystemControl_BASE_PTR)
#define SCB_DFSR                                 SCB_DFSR_REG(SystemControl_BASE_PTR)

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SCB_Peripheral */


/* ----------------------------------------------------------------------------
   -- SIM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral SIM
 * @{
 */

/** SIM - Peripheral register structure */
typedef struct SIM_MemMap {
  uint32_t SRSID;                                  /**< System Reset Status and ID Register, offset: 0x0 */
  uint32_t SOPT0;                                  /**< System Options Register 0, offset: 0x4 */
  uint32_t TBARCFG0;                               /**< Trigger Crossbar Configuration Register 0, offset: 0x8 */
  uint32_t TBARCFG1;                               /**< Trigger Crossbar Configuration Register 1, offset: 0xC */
  uint32_t SBARCFG;                                /**< Signal Crossbar Configuration Register, offset: 0x10 */
  uint32_t XBARCFG;                                /**< FSK Configuration Register, offset: 0x14 */
  uint32_t SCGC;                                   /**< System Clock Gating Control Register, offset: 0x18 */
  uint32_t RST;                                    /**< Reset control Register, offset: 0x1C */
  uint32_t CLKDIV;                                 /**< Clock Divider Register, offset: 0x20 */
  uint32_t FLG;                                    /**< CNC external clamp and LDO external shutdown Flags Register, offset: 0x24 */
  uint32_t AOICFG;                                 /**< AOI function Configuration Register, offset: 0x28 */
  uint32_t CR;                                     /**< ACMP channel 2 Configuration and SIM_SCGC[ADC] write enable Register, offset: 0x2C */
  uint32_t UUIDL;                                  /**< Universally Unique Identifier Low Register, offset: 0x30 */
  uint32_t UUIDML;                                 /**< Universally Unique Identifier Middle Low Register, offset: 0x34 */
  uint32_t UUIDMH;                                 /**< Universally Unique Identifier Middle High Register, offset: 0x38 */
  uint32_t IFR0;                                   /**< Peripherals IFR bits Register 0, offset: 0x3C */
  uint32_t IFR1;                                   /**< Peripherals IFR bits Register 1, offset: 0x40 */
  uint32_t IFR2;                                   /**< Peripherals IFR bits Register 2, offset: 0x44 */
  uint32_t IFR3;                                   /**< Peripherals IFR bits Register 3, offset: 0x48 */
} volatile *SIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register accessors */
#define SIM_SRSID_REG(base)                      ((base)->SRSID)
#define SIM_SOPT0_REG(base)                      ((base)->SOPT0)
#define SIM_TBARCFG0_REG(base)                   ((base)->TBARCFG0)
#define SIM_TBARCFG1_REG(base)                   ((base)->TBARCFG1)
#define SIM_SBARCFG_REG(base)                    ((base)->SBARCFG)
#define SIM_XBARCFG_REG(base)                    ((base)->XBARCFG)
#define SIM_SCGC_REG(base)                       ((base)->SCGC)
#define SIM_RST_REG(base)                        ((base)->RST)
#define SIM_CLKDIV_REG(base)                     ((base)->CLKDIV)
#define SIM_FLG_REG(base)                        ((base)->FLG)
#define SIM_AOICFG_REG(base)                     ((base)->AOICFG)
#define SIM_CR_REG(base)                         ((base)->CR)
#define SIM_UUIDL_REG(base)                      ((base)->UUIDL)
#define SIM_UUIDML_REG(base)                     ((base)->UUIDML)
#define SIM_UUIDMH_REG(base)                     ((base)->UUIDMH)
#define SIM_IFR0_REG(base)                       ((base)->IFR0)
#define SIM_IFR1_REG(base)                       ((base)->IFR1)
#define SIM_IFR2_REG(base)                       ((base)->IFR2)
#define SIM_IFR3_REG(base)                       ((base)->IFR3)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/* SRSID Bit Fields */
#define SIM_SRSID_LVD_MASK                       0x2u
#define SIM_SRSID_LVD_SHIFT                      1
#define SIM_SRSID_LOC_MASK                       0x4u
#define SIM_SRSID_LOC_SHIFT                      2
#define SIM_SRSID_WDOG_MASK                      0x20u
#define SIM_SRSID_WDOG_SHIFT                     5
#define SIM_SRSID_PIN_MASK                       0x40u
#define SIM_SRSID_PIN_SHIFT                      6
#define SIM_SRSID_POR_MASK                       0x80u
#define SIM_SRSID_POR_SHIFT                      7
#define SIM_SRSID_LOCKUP_MASK                    0x200u
#define SIM_SRSID_LOCKUP_SHIFT                   9
#define SIM_SRSID_SW_MASK                        0x400u
#define SIM_SRSID_SW_SHIFT                       10
#define SIM_SRSID_MDMAP_MASK                     0x800u
#define SIM_SRSID_MDMAP_SHIFT                    11
#define SIM_SRSID_SACKERR_MASK                   0x2000u
#define SIM_SRSID_SACKERR_SHIFT                  13
#define SIM_SRSID_SUBFAMID_MASK                  0xF000000u
#define SIM_SRSID_SUBFAMID_SHIFT                 24
#define SIM_SRSID_SUBFAMID(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_SUBFAMID_SHIFT))&SIM_SRSID_SUBFAMID_MASK)
#define SIM_SRSID_FAMID_MASK                     0xF0000000u
#define SIM_SRSID_FAMID_SHIFT                    28
#define SIM_SRSID_FAMID(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_FAMID_SHIFT))&SIM_SRSID_FAMID_MASK)
/* SOPT0 Bit Fields */
#define SIM_SOPT0_NMIE_MASK                      0x2u
#define SIM_SOPT0_NMIE_SHIFT                     1
#define SIM_SOPT0_RSTPE_MASK                     0x4u
#define SIM_SOPT0_RSTPE_SHIFT                    2
#define SIM_SOPT0_SWDE_MASK                      0x8u
#define SIM_SOPT0_SWDE_SHIFT                     3
#define SIM_SOPT0_FTM0CHEN_MASK                  0x300u
#define SIM_SOPT0_FTM0CHEN_SHIFT                 8
#define SIM_SOPT0_FTM0CHEN(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_FTM0CHEN_SHIFT))&SIM_SOPT0_FTM0CHEN_MASK)
#define SIM_SOPT0_FTM1CHEN_MASK                  0xC00u
#define SIM_SOPT0_FTM1CHEN_SHIFT                 10
#define SIM_SOPT0_FTM1CHEN(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_FTM1CHEN_SHIFT))&SIM_SOPT0_FTM1CHEN_MASK)
#define SIM_SOPT0_UARTRXEN_MASK                  0x1000u
#define SIM_SOPT0_UARTRXEN_SHIFT                 12
#define SIM_SOPT0_UARTTXEN_MASK                  0x2000u
#define SIM_SOPT0_UARTTXEN_SHIFT                 13
#define SIM_SOPT0_SBARIN0EN_MASK                 0x4000u
#define SIM_SOPT0_SBARIN0EN_SHIFT                14
#define SIM_SOPT0_SBARIN1EN_MASK                 0x8000u
#define SIM_SOPT0_SBARIN1EN_SHIFT                15
#define SIM_SOPT0_BUSREF_MASK                    0x70000u
#define SIM_SOPT0_BUSREF_SHIFT                   16
#define SIM_SOPT0_BUSREF(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_BUSREF_SHIFT))&SIM_SOPT0_BUSREF_MASK)
#define SIM_SOPT0_CLKOE_MASK                     0x80000u
#define SIM_SOPT0_CLKOE_SHIFT                    19
#define SIM_SOPT0_DLYACT_MASK                    0x800000u
#define SIM_SOPT0_DLYACT_SHIFT                   23
#define SIM_SOPT0_DELAY_MASK                     0xFF000000u
#define SIM_SOPT0_DELAY_SHIFT                    24
#define SIM_SOPT0_DELAY(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SOPT0_DELAY_SHIFT))&SIM_SOPT0_DELAY_MASK)
/* TBARCFG0 Bit Fields */
#define SIM_TBARCFG0_ADCTRIG_MASK                0xFu
#define SIM_TBARCFG0_ADCTRIG_SHIFT               0
#define SIM_TBARCFG0_ADCTRIG(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_ADCTRIG_SHIFT))&SIM_TBARCFG0_ADCTRIG_MASK)
#define SIM_TBARCFG0_ADCRESTART_MASK             0xF0u
#define SIM_TBARCFG0_ADCRESTART_SHIFT            4
#define SIM_TBARCFG0_ADCRESTART(x)               (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_ADCRESTART_SHIFT))&SIM_TBARCFG0_ADCRESTART_MASK)
#define SIM_TBARCFG0_ADCABORT_MASK               0xF00u
#define SIM_TBARCFG0_ADCABORT_SHIFT              8
#define SIM_TBARCFG0_ADCABORT(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_ADCABORT_SHIFT))&SIM_TBARCFG0_ADCABORT_MASK)
#define SIM_TBARCFG0_ADCLOADOK_MASK              0xF000u
#define SIM_TBARCFG0_ADCLOADOK_SHIFT             12
#define SIM_TBARCFG0_ADCLOADOK(x)                (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_ADCLOADOK_SHIFT))&SIM_TBARCFG0_ADCLOADOK_MASK)
#define SIM_TBARCFG0_CNCEXCLAMP_MASK             0xF0000u
#define SIM_TBARCFG0_CNCEXCLAMP_SHIFT            16
#define SIM_TBARCFG0_CNCEXCLAMP(x)               (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_CNCEXCLAMP_SHIFT))&SIM_TBARCFG0_CNCEXCLAMP_MASK)
#define SIM_TBARCFG0_LDOSHUTDOWN0_MASK           0xF00000u
#define SIM_TBARCFG0_LDOSHUTDOWN0_SHIFT          20
#define SIM_TBARCFG0_LDOSHUTDOWN0(x)             (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_LDOSHUTDOWN0_SHIFT))&SIM_TBARCFG0_LDOSHUTDOWN0_MASK)
#define SIM_TBARCFG0_LDOSHUTDOWN1_MASK           0xF000000u
#define SIM_TBARCFG0_LDOSHUTDOWN1_SHIFT          24
#define SIM_TBARCFG0_LDOSHUTDOWN1(x)             (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_LDOSHUTDOWN1_SHIFT))&SIM_TBARCFG0_LDOSHUTDOWN1_MASK)
#define SIM_TBARCFG0_LDOSHUTDOWN2_MASK           0xF0000000u
#define SIM_TBARCFG0_LDOSHUTDOWN2_SHIFT          28
#define SIM_TBARCFG0_LDOSHUTDOWN2(x)             (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG0_LDOSHUTDOWN2_SHIFT))&SIM_TBARCFG0_LDOSHUTDOWN2_MASK)
/* TBARCFG1 Bit Fields */
#define SIM_TBARCFG1_TBAROUT_MASK                0xFu
#define SIM_TBARCFG1_TBAROUT_SHIFT               0
#define SIM_TBARCFG1_TBAROUT(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_TBARCFG1_TBAROUT_SHIFT))&SIM_TBARCFG1_TBAROUT_MASK)
/* SBARCFG Bit Fields */
#define SIM_SBARCFG_FSKDTIN_MASK                 0xFu
#define SIM_SBARCFG_FSKDTIN_SHIFT                0
#define SIM_SBARCFG_FSKDTIN(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_FSKDTIN_SHIFT))&SIM_SBARCFG_FSKDTIN_MASK)
#define SIM_SBARCFG_IRQ_MASK                     0xF0u
#define SIM_SBARCFG_IRQ_SHIFT                    4
#define SIM_SBARCFG_IRQ(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_IRQ_SHIFT))&SIM_SBARCFG_IRQ_MASK)
#define SIM_SBARCFG_FTM1CH0IN_MASK               0xF00u
#define SIM_SBARCFG_FTM1CH0IN_SHIFT              8
#define SIM_SBARCFG_FTM1CH0IN(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_FTM1CH0IN_SHIFT))&SIM_SBARCFG_FTM1CH0IN_MASK)
#define SIM_SBARCFG_FTM1CH1IN_MASK               0xF000u
#define SIM_SBARCFG_FTM1CH1IN_SHIFT              12
#define SIM_SBARCFG_FTM1CH1IN(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_FTM1CH1IN_SHIFT))&SIM_SBARCFG_FTM1CH1IN_MASK)
#define SIM_SBARCFG_UARTRX_MASK                  0xF0000u
#define SIM_SBARCFG_UARTRX_SHIFT                 16
#define SIM_SBARCFG_UARTRX(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_UARTRX_SHIFT))&SIM_SBARCFG_UARTRX_MASK)
#define SIM_SBARCFG_SBAROUT0_MASK                0xF00000u
#define SIM_SBARCFG_SBAROUT0_SHIFT               20
#define SIM_SBARCFG_SBAROUT0(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_SBAROUT0_SHIFT))&SIM_SBARCFG_SBAROUT0_MASK)
#define SIM_SBARCFG_SBAROUT1_MASK                0xF000000u
#define SIM_SBARCFG_SBAROUT1_SHIFT               24
#define SIM_SBARCFG_SBAROUT1(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_SBAROUT1_SHIFT))&SIM_SBARCFG_SBAROUT1_MASK)
#define SIM_SBARCFG_SBAROUT2_MASK                0xF0000000u
#define SIM_SBARCFG_SBAROUT2_SHIFT               28
#define SIM_SBARCFG_SBAROUT2(x)                  (((uint32_t)(((uint32_t)(x))<<SIM_SBARCFG_SBAROUT2_SHIFT))&SIM_SBARCFG_SBAROUT2_MASK)
/* XBARCFG Bit Fields */
#define SIM_XBARCFG_SBARDIV_MASK                 0xFu
#define SIM_XBARCFG_SBARDIV_SHIFT                0
#define SIM_XBARCFG_SBARDIV(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_XBARCFG_SBARDIV_SHIFT))&SIM_XBARCFG_SBARDIV_MASK)
#define SIM_XBARCFG_TBARDIV_MASK                 0x700u
#define SIM_XBARCFG_TBARDIV_SHIFT                8
#define SIM_XBARCFG_TBARDIV(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_XBARCFG_TBARDIV_SHIFT))&SIM_XBARCFG_TBARDIV_MASK)
#define SIM_XBARCFG_FILT0_MASK                   0xF000u
#define SIM_XBARCFG_FILT0_SHIFT                  12
#define SIM_XBARCFG_FILT0(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_XBARCFG_FILT0_SHIFT))&SIM_XBARCFG_FILT0_MASK)
#define SIM_XBARCFG_FILT1_MASK                   0xFF0000u
#define SIM_XBARCFG_FILT1_SHIFT                  16
#define SIM_XBARCFG_FILT1(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_XBARCFG_FILT1_SHIFT))&SIM_XBARCFG_FILT1_MASK)
#define SIM_XBARCFG_FSKCLKEN_MASK                0x80000000u
#define SIM_XBARCFG_FSKCLKEN_SHIFT               31
/* SCGC Bit Fields */
#define SIM_SCGC_RTC_MASK                        0x1u
#define SIM_SCGC_RTC_SHIFT                       0
#define SIM_SCGC_PIT_MASK                        0x2u
#define SIM_SCGC_PIT_SHIFT                       1
#define SIM_SCGC_FSKDT_MASK                      0x10u
#define SIM_SCGC_FSKDT_SHIFT                     4
#define SIM_SCGC_FTM0_MASK                       0x20u
#define SIM_SCGC_FTM0_SHIFT                      5
#define SIM_SCGC_FTM1_MASK                       0x40u
#define SIM_SCGC_FTM1_SHIFT                      6
#define SIM_SCGC_CNC_MASK                        0x100u
#define SIM_SCGC_CNC_SHIFT                       8
#define SIM_SCGC_PGA_MASK                        0x200u
#define SIM_SCGC_PGA_SHIFT                       9
#define SIM_SCGC_LDO_MASK                        0x400u
#define SIM_SCGC_LDO_SHIFT                       10
#define SIM_SCGC_FLASH_MASK                      0x1000u
#define SIM_SCGC_FLASH_SHIFT                     12
#define SIM_SCGC_SWD_MASK                        0x2000u
#define SIM_SCGC_SWD_SHIFT                       13
#define SIM_SCGC_I2C0_MASK                       0x10000u
#define SIM_SCGC_I2C0_SHIFT                      16
#define SIM_SCGC_UART0_MASK                      0x100000u
#define SIM_SCGC_UART0_SHIFT                     20
#define SIM_SCGC_IRQ_MASK                        0x8000000u
#define SIM_SCGC_IRQ_SHIFT                       27
#define SIM_SCGC_ADC_MASK                        0x20000000u
#define SIM_SCGC_ADC_SHIFT                       29
#define SIM_SCGC_ACMP0_MASK                      0x40000000u
#define SIM_SCGC_ACMP0_SHIFT                     30
/* RST Bit Fields */
#define SIM_RST_RTC_MASK                         0x1u
#define SIM_RST_RTC_SHIFT                        0
#define SIM_RST_PIT_MASK                         0x2u
#define SIM_RST_PIT_SHIFT                        1
#define SIM_RST_FSKDT_MASK                       0x10u
#define SIM_RST_FSKDT_SHIFT                      4
#define SIM_RST_FTM0_MASK                        0x20u
#define SIM_RST_FTM0_SHIFT                       5
#define SIM_RST_FTM1_MASK                        0x40u
#define SIM_RST_FTM1_SHIFT                       6
#define SIM_RST_CNC_MASK                         0x100u
#define SIM_RST_CNC_SHIFT                        8
#define SIM_RST_LDO_MASK                         0x400u
#define SIM_RST_LDO_SHIFT                        10
#define SIM_RST_I2C0_MASK                        0x10000u
#define SIM_RST_I2C0_SHIFT                       16
#define SIM_RST_UART0_MASK                       0x100000u
#define SIM_RST_UART0_SHIFT                      20
#define SIM_RST_IRQ_MASK                         0x8000000u
#define SIM_RST_IRQ_SHIFT                        27
#define SIM_RST_ACMP0_MASK                       0x40000000u
#define SIM_RST_ACMP0_SHIFT                      30
/* CLKDIV Bit Fields */
#define SIM_CLKDIV_OUTDIV3_MASK                  0x100000u
#define SIM_CLKDIV_OUTDIV3_SHIFT                 20
#define SIM_CLKDIV_OUTDIV2_MASK                  0x1000000u
#define SIM_CLKDIV_OUTDIV2_SHIFT                 24
#define SIM_CLKDIV_OUTDIV1_MASK                  0x30000000u
#define SIM_CLKDIV_OUTDIV1_SHIFT                 28
#define SIM_CLKDIV_OUTDIV1(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_CLKDIV_OUTDIV1_SHIFT))&SIM_CLKDIV_OUTDIV1_MASK)
/* FLG Bit Fields */
#define SIM_FLG_ECLAMPF_MASK                     0x1u
#define SIM_FLG_ECLAMPF_SHIFT                    0
#define SIM_FLG_ESHUTF_MASK                      0x2u
#define SIM_FLG_ESHUTF_SHIFT                     1
/* AOICFG Bit Fields */
#define SIM_AOICFG_PT3_DC_MASK                   0x3u
#define SIM_AOICFG_PT3_DC_SHIFT                  0
#define SIM_AOICFG_PT3_DC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT3_DC_SHIFT))&SIM_AOICFG_PT3_DC_MASK)
#define SIM_AOICFG_PT3_CC_MASK                   0xCu
#define SIM_AOICFG_PT3_CC_SHIFT                  2
#define SIM_AOICFG_PT3_CC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT3_CC_SHIFT))&SIM_AOICFG_PT3_CC_MASK)
#define SIM_AOICFG_PT3_BC_MASK                   0x30u
#define SIM_AOICFG_PT3_BC_SHIFT                  4
#define SIM_AOICFG_PT3_BC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT3_BC_SHIFT))&SIM_AOICFG_PT3_BC_MASK)
#define SIM_AOICFG_PT3_AC_MASK                   0xC0u
#define SIM_AOICFG_PT3_AC_SHIFT                  6
#define SIM_AOICFG_PT3_AC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT3_AC_SHIFT))&SIM_AOICFG_PT3_AC_MASK)
#define SIM_AOICFG_PT2_DC_MASK                   0x300u
#define SIM_AOICFG_PT2_DC_SHIFT                  8
#define SIM_AOICFG_PT2_DC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT2_DC_SHIFT))&SIM_AOICFG_PT2_DC_MASK)
#define SIM_AOICFG_PT2_CC_MASK                   0xC00u
#define SIM_AOICFG_PT2_CC_SHIFT                  10
#define SIM_AOICFG_PT2_CC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT2_CC_SHIFT))&SIM_AOICFG_PT2_CC_MASK)
#define SIM_AOICFG_PT2_BC_MASK                   0x3000u
#define SIM_AOICFG_PT2_BC_SHIFT                  12
#define SIM_AOICFG_PT2_BC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT2_BC_SHIFT))&SIM_AOICFG_PT2_BC_MASK)
#define SIM_AOICFG_PT2_AC_MASK                   0xC000u
#define SIM_AOICFG_PT2_AC_SHIFT                  14
#define SIM_AOICFG_PT2_AC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT2_AC_SHIFT))&SIM_AOICFG_PT2_AC_MASK)
#define SIM_AOICFG_PT1_DC_MASK                   0x30000u
#define SIM_AOICFG_PT1_DC_SHIFT                  16
#define SIM_AOICFG_PT1_DC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT1_DC_SHIFT))&SIM_AOICFG_PT1_DC_MASK)
#define SIM_AOICFG_PT1_CC_MASK                   0xC0000u
#define SIM_AOICFG_PT1_CC_SHIFT                  18
#define SIM_AOICFG_PT1_CC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT1_CC_SHIFT))&SIM_AOICFG_PT1_CC_MASK)
#define SIM_AOICFG_PT1_BC_MASK                   0x300000u
#define SIM_AOICFG_PT1_BC_SHIFT                  20
#define SIM_AOICFG_PT1_BC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT1_BC_SHIFT))&SIM_AOICFG_PT1_BC_MASK)
#define SIM_AOICFG_PT1_AC_MASK                   0xC00000u
#define SIM_AOICFG_PT1_AC_SHIFT                  22
#define SIM_AOICFG_PT1_AC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT1_AC_SHIFT))&SIM_AOICFG_PT1_AC_MASK)
#define SIM_AOICFG_PT0_DC_MASK                   0x3000000u
#define SIM_AOICFG_PT0_DC_SHIFT                  24
#define SIM_AOICFG_PT0_DC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT0_DC_SHIFT))&SIM_AOICFG_PT0_DC_MASK)
#define SIM_AOICFG_PT0_CC_MASK                   0xC000000u
#define SIM_AOICFG_PT0_CC_SHIFT                  26
#define SIM_AOICFG_PT0_CC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT0_CC_SHIFT))&SIM_AOICFG_PT0_CC_MASK)
#define SIM_AOICFG_PT0_BC_MASK                   0x30000000u
#define SIM_AOICFG_PT0_BC_SHIFT                  28
#define SIM_AOICFG_PT0_BC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT0_BC_SHIFT))&SIM_AOICFG_PT0_BC_MASK)
#define SIM_AOICFG_PT0_AC_MASK                   0xC0000000u
#define SIM_AOICFG_PT0_AC_SHIFT                  30
#define SIM_AOICFG_PT0_AC(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_AOICFG_PT0_AC_SHIFT))&SIM_AOICFG_PT0_AC_MASK)
/* CR Bit Fields */
#define SIM_CR_ADCGCWEN_MASK                     0x100u
#define SIM_CR_ADCGCWEN_SHIFT                    8
#define SIM_CR_ACMP0CH2SEL_MASK                  0x3000000u
#define SIM_CR_ACMP0CH2SEL_SHIFT                 24
#define SIM_CR_ACMP0CH2SEL(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_CR_ACMP0CH2SEL_SHIFT))&SIM_CR_ACMP0CH2SEL_MASK)
/* UUIDL Bit Fields */
#define SIM_UUIDL_ID_MASK                        0xFFFFFFFFu
#define SIM_UUIDL_ID_SHIFT                       0
#define SIM_UUIDL_ID(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_UUIDL_ID_SHIFT))&SIM_UUIDL_ID_MASK)
/* UUIDML Bit Fields */
#define SIM_UUIDML_ID_MASK                       0xFFFFFFFFu
#define SIM_UUIDML_ID_SHIFT                      0
#define SIM_UUIDML_ID(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_UUIDML_ID_SHIFT))&SIM_UUIDML_ID_MASK)
/* UUIDMH Bit Fields */
#define SIM_UUIDMH_ID_MASK                       0xFFFFu
#define SIM_UUIDMH_ID_SHIFT                      0
#define SIM_UUIDMH_ID(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_UUIDMH_ID_SHIFT))&SIM_UUIDMH_ID_MASK)
/* IFR0 Bit Fields */
#define SIM_IFR0_IFR0_20_10_MASK                 0x1FFC00u
#define SIM_IFR0_IFR0_20_10_SHIFT                10
#define SIM_IFR0_IFR0_20_10(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_IFR0_IFR0_20_10_SHIFT))&SIM_IFR0_IFR0_20_10_MASK)
#define SIM_IFR0_IFR0_31_21_MASK                 0xFFE00000u
#define SIM_IFR0_IFR0_31_21_SHIFT                21
#define SIM_IFR0_IFR0_31_21(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_IFR0_IFR0_31_21_SHIFT))&SIM_IFR0_IFR0_31_21_MASK)
/* IFR1 Bit Fields */
#define SIM_IFR1_IFR1_5_0_MASK                   0x3Fu
#define SIM_IFR1_IFR1_5_0_SHIFT                  0
#define SIM_IFR1_IFR1_5_0(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_IFR1_IFR1_5_0_SHIFT))&SIM_IFR1_IFR1_5_0_MASK)
#define SIM_IFR1_IFR1_11_6_MASK                  0xFC0u
#define SIM_IFR1_IFR1_11_6_SHIFT                 6
#define SIM_IFR1_IFR1_11_6(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_IFR1_IFR1_11_6_SHIFT))&SIM_IFR1_IFR1_11_6_MASK)
#define SIM_IFR1_IFR1_17_12_MASK                 0x3F000u
#define SIM_IFR1_IFR1_17_12_SHIFT                12
#define SIM_IFR1_IFR1_17_12(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_IFR1_IFR1_17_12_SHIFT))&SIM_IFR1_IFR1_17_12_MASK)
/* IFR2 Bit Fields */
#define SIM_IFR2_IFR2_10_0_MASK                  0x7FFu
#define SIM_IFR2_IFR2_10_0_SHIFT                 0
#define SIM_IFR2_IFR2_10_0(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_IFR2_IFR2_10_0_SHIFT))&SIM_IFR2_IFR2_10_0_MASK)
#define SIM_IFR2_IFR2_21_11_MASK                 0x3FF800u
#define SIM_IFR2_IFR2_21_11_SHIFT                11
#define SIM_IFR2_IFR2_21_11(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_IFR2_IFR2_21_11_SHIFT))&SIM_IFR2_IFR2_21_11_MASK)
/* IFR3 Bit Fields */
#define SIM_IFR3_IFR3_11_0_MASK                  0xFFFu
#define SIM_IFR3_IFR3_11_0_SHIFT                 0
#define SIM_IFR3_IFR3_11_0(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_IFR3_IFR3_11_0_SHIFT))&SIM_IFR3_IFR3_11_0_MASK)
#define SIM_IFR3_IFR3_22_12_MASK                 0x7FF000u
#define SIM_IFR3_IFR3_22_12_SHIFT                12
#define SIM_IFR3_IFR3_22_12(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_IFR3_IFR3_22_12_SHIFT))&SIM_IFR3_IFR3_22_12_MASK)

/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base pointer */
#define SIM_BASE_PTR                             ((SIM_MemMapPtr)0x40048000u)
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register instance definitions */
/* SIM */
#define SIM_SRSID                                SIM_SRSID_REG(SIM_BASE_PTR)
#define SIM_SOPT0                                SIM_SOPT0_REG(SIM_BASE_PTR)
#define SIM_TBARCFG0                             SIM_TBARCFG0_REG(SIM_BASE_PTR)
#define SIM_TBARCFG1                             SIM_TBARCFG1_REG(SIM_BASE_PTR)
#define SIM_SBARCFG                              SIM_SBARCFG_REG(SIM_BASE_PTR)
#define SIM_XBARCFG                              SIM_XBARCFG_REG(SIM_BASE_PTR)
#define SIM_SCGC                                 SIM_SCGC_REG(SIM_BASE_PTR)
#define SIM_RST                                  SIM_RST_REG(SIM_BASE_PTR)
#define SIM_CLKDIV                               SIM_CLKDIV_REG(SIM_BASE_PTR)
#define SIM_FLG                                  SIM_FLG_REG(SIM_BASE_PTR)
#define SIM_AOICFG                               SIM_AOICFG_REG(SIM_BASE_PTR)
#define SIM_CR                                   SIM_CR_REG(SIM_BASE_PTR)
#define SIM_UUIDL                                SIM_UUIDL_REG(SIM_BASE_PTR)
#define SIM_UUIDML                               SIM_UUIDML_REG(SIM_BASE_PTR)
#define SIM_UUIDMH                               SIM_UUIDMH_REG(SIM_BASE_PTR)
#define SIM_IFR0                                 SIM_IFR0_REG(SIM_BASE_PTR)
#define SIM_IFR1                                 SIM_IFR1_REG(SIM_BASE_PTR)
#define SIM_IFR2                                 SIM_IFR2_REG(SIM_BASE_PTR)
#define SIM_IFR3                                 SIM_IFR3_REG(SIM_BASE_PTR)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SIM_Peripheral */


/* ----------------------------------------------------------------------------
   -- SysTick
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Peripheral SysTick
 * @{
 */

/** SysTick - Peripheral register structure */
typedef struct SysTick_MemMap {
  uint32_t CSR;                                    /**< SysTick Control and Status Register, offset: 0x0 */
  uint32_t RVR;                                    /**< SysTick Reload Value Register, offset: 0x4 */
  uint32_t CVR;                                    /**< SysTick Current Value Register, offset: 0x8 */
  uint32_t CALIB;                                  /**< SysTick Calibration Value Register, offset: 0xC */
} volatile *SysTick_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register accessors */
#define SysTick_CSR_REG(base)                    ((base)->CSR)
#define SysTick_RVR_REG(base)                    ((base)->RVR)
#define SysTick_CVR_REG(base)                    ((base)->CVR)
#define SysTick_CALIB_REG(base)                  ((base)->CALIB)

/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SysTick Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Masks SysTick Register Masks
 * @{
 */

/* CSR Bit Fields */
#define SysTick_CSR_ENABLE_MASK                  0x1u
#define SysTick_CSR_ENABLE_SHIFT                 0
#define SysTick_CSR_TICKINT_MASK                 0x2u
#define SysTick_CSR_TICKINT_SHIFT                1
#define SysTick_CSR_CLKSOURCE_MASK               0x4u
#define SysTick_CSR_CLKSOURCE_SHIFT              2
#define SysTick_CSR_COUNTFLAG_MASK               0x10000u
#define SysTick_CSR_COUNTFLAG_SHIFT              16
/* RVR Bit Fields */
#define SysTick_RVR_RELOAD_MASK                  0xFFFFFFu
#define SysTick_RVR_RELOAD_SHIFT                 0
#define SysTick_RVR_RELOAD(x)                    (((uint32_t)(((uint32_t)(x))<<SysTick_RVR_RELOAD_SHIFT))&SysTick_RVR_RELOAD_MASK)
/* CVR Bit Fields */
#define SysTick_CVR_CURRENT_MASK                 0xFFFFFFu
#define SysTick_CVR_CURRENT_SHIFT                0
#define SysTick_CVR_CURRENT(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CVR_CURRENT_SHIFT))&SysTick_CVR_CURRENT_MASK)
/* CALIB Bit Fields */
#define SysTick_CALIB_TENMS_MASK                 0xFFFFFFu
#define SysTick_CALIB_TENMS_SHIFT                0
#define SysTick_CALIB_TENMS(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CALIB_TENMS_SHIFT))&SysTick_CALIB_TENMS_MASK)
#define SysTick_CALIB_SKEW_MASK                  0x40000000u
#define SysTick_CALIB_SKEW_SHIFT                 30
#define SysTick_CALIB_NOREF_MASK                 0x80000000u
#define SysTick_CALIB_NOREF_SHIFT                31

/*!
 * @}
 */ /* end of group SysTick_Register_Masks */


/* SysTick - Peripheral instance base addresses */
/** Peripheral SysTick base pointer */
#define SysTick_BASE_PTR                         ((SysTick_MemMapPtr)0xE000E010u)
/** Array initializer of SysTick peripheral base pointers */
#define SysTick_BASE_PTRS                        { SysTick_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register instance definitions */
/* SysTick */
#define SYST_CSR                                 SysTick_CSR_REG(SysTick_BASE_PTR)
#define SYST_RVR                                 SysTick_RVR_REG(SysTick_BASE_PTR)
#define SYST_CVR                                 SysTick_CVR_REG(SysTick_BASE_PTR)
#define SYST_CALIB                               SysTick_CALIB_REG(SysTick_BASE_PTR)

/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SysTick_Peripheral */


/* ----------------------------------------------------------------------------
   -- UART
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Peripheral UART
 * @{
 */

/** UART - Peripheral register structure */
typedef struct UART_MemMap {
  uint8_t BDH;                                     /**< UART Baud Rate Register: High, offset: 0x0 */
  uint8_t BDL;                                     /**< UART Baud Rate Register: Low, offset: 0x1 */
  uint8_t C1;                                      /**< UART Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< UART Control Register 2, offset: 0x3 */
  uint8_t S1;                                      /**< UART Status Register 1, offset: 0x4 */
  uint8_t S2;                                      /**< UART Status Register 2, offset: 0x5 */
  uint8_t C3;                                      /**< UART Control Register 3, offset: 0x6 */
  uint8_t D;                                       /**< UART Data Register, offset: 0x7 */
} volatile *UART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register accessors */
#define UART_BDH_REG(base)                       ((base)->BDH)
#define UART_BDL_REG(base)                       ((base)->BDL)
#define UART_C1_REG(base)                        ((base)->C1)
#define UART_C2_REG(base)                        ((base)->C2)
#define UART_S1_REG(base)                        ((base)->S1)
#define UART_S2_REG(base)                        ((base)->S2)
#define UART_C3_REG(base)                        ((base)->C3)
#define UART_D_REG(base)                         ((base)->D)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/* BDH Bit Fields */
#define UART_BDH_SBR_MASK                        0x1Fu
#define UART_BDH_SBR_SHIFT                       0
#define UART_BDH_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDH_SBR_SHIFT))&UART_BDH_SBR_MASK)
#define UART_BDH_SBNS_MASK                       0x20u
#define UART_BDH_SBNS_SHIFT                      5
#define UART_BDH_RXEDGIE_MASK                    0x40u
#define UART_BDH_RXEDGIE_SHIFT                   6
#define UART_BDH_LBKDIE_MASK                     0x80u
#define UART_BDH_LBKDIE_SHIFT                    7
/* BDL Bit Fields */
#define UART_BDL_SBR_MASK                        0xFFu
#define UART_BDL_SBR_SHIFT                       0
#define UART_BDL_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDL_SBR_SHIFT))&UART_BDL_SBR_MASK)
/* C1 Bit Fields */
#define UART_C1_PT_MASK                          0x1u
#define UART_C1_PT_SHIFT                         0
#define UART_C1_PE_MASK                          0x2u
#define UART_C1_PE_SHIFT                         1
#define UART_C1_ILT_MASK                         0x4u
#define UART_C1_ILT_SHIFT                        2
#define UART_C1_WAKE_MASK                        0x8u
#define UART_C1_WAKE_SHIFT                       3
#define UART_C1_M_MASK                           0x10u
#define UART_C1_M_SHIFT                          4
#define UART_C1_RSRC_MASK                        0x20u
#define UART_C1_RSRC_SHIFT                       5
#define UART_C1_UARTSWAI_MASK                    0x40u
#define UART_C1_UARTSWAI_SHIFT                   6
#define UART_C1_LOOPS_MASK                       0x80u
#define UART_C1_LOOPS_SHIFT                      7
/* C2 Bit Fields */
#define UART_C2_SBK_MASK                         0x1u
#define UART_C2_SBK_SHIFT                        0
#define UART_C2_RWU_MASK                         0x2u
#define UART_C2_RWU_SHIFT                        1
#define UART_C2_RE_MASK                          0x4u
#define UART_C2_RE_SHIFT                         2
#define UART_C2_TE_MASK                          0x8u
#define UART_C2_TE_SHIFT                         3
#define UART_C2_ILIE_MASK                        0x10u
#define UART_C2_ILIE_SHIFT                       4
#define UART_C2_RIE_MASK                         0x20u
#define UART_C2_RIE_SHIFT                        5
#define UART_C2_TCIE_MASK                        0x40u
#define UART_C2_TCIE_SHIFT                       6
#define UART_C2_TIE_MASK                         0x80u
#define UART_C2_TIE_SHIFT                        7
/* S1 Bit Fields */
#define UART_S1_PF_MASK                          0x1u
#define UART_S1_PF_SHIFT                         0
#define UART_S1_FE_MASK                          0x2u
#define UART_S1_FE_SHIFT                         1
#define UART_S1_NF_MASK                          0x4u
#define UART_S1_NF_SHIFT                         2
#define UART_S1_OR_MASK                          0x8u
#define UART_S1_OR_SHIFT                         3
#define UART_S1_IDLE_MASK                        0x10u
#define UART_S1_IDLE_SHIFT                       4
#define UART_S1_RDRF_MASK                        0x20u
#define UART_S1_RDRF_SHIFT                       5
#define UART_S1_TC_MASK                          0x40u
#define UART_S1_TC_SHIFT                         6
#define UART_S1_TDRE_MASK                        0x80u
#define UART_S1_TDRE_SHIFT                       7
/* S2 Bit Fields */
#define UART_S2_RAF_MASK                         0x1u
#define UART_S2_RAF_SHIFT                        0
#define UART_S2_LBKDE_MASK                       0x2u
#define UART_S2_LBKDE_SHIFT                      1
#define UART_S2_BRK13_MASK                       0x4u
#define UART_S2_BRK13_SHIFT                      2
#define UART_S2_RWUID_MASK                       0x8u
#define UART_S2_RWUID_SHIFT                      3
#define UART_S2_RXINV_MASK                       0x10u
#define UART_S2_RXINV_SHIFT                      4
#define UART_S2_RXEDGIF_MASK                     0x40u
#define UART_S2_RXEDGIF_SHIFT                    6
#define UART_S2_LBKDIF_MASK                      0x80u
#define UART_S2_LBKDIF_SHIFT                     7
/* C3 Bit Fields */
#define UART_C3_PEIE_MASK                        0x1u
#define UART_C3_PEIE_SHIFT                       0
#define UART_C3_FEIE_MASK                        0x2u
#define UART_C3_FEIE_SHIFT                       1
#define UART_C3_NEIE_MASK                        0x4u
#define UART_C3_NEIE_SHIFT                       2
#define UART_C3_ORIE_MASK                        0x8u
#define UART_C3_ORIE_SHIFT                       3
#define UART_C3_TXINV_MASK                       0x10u
#define UART_C3_TXINV_SHIFT                      4
#define UART_C3_TXDIR_MASK                       0x20u
#define UART_C3_TXDIR_SHIFT                      5
#define UART_C3_T8_MASK                          0x40u
#define UART_C3_T8_SHIFT                         6
#define UART_C3_R8_MASK                          0x80u
#define UART_C3_R8_SHIFT                         7
/* D Bit Fields */
#define UART_D_R0T0_MASK                         0x1u
#define UART_D_R0T0_SHIFT                        0
#define UART_D_R1T1_MASK                         0x2u
#define UART_D_R1T1_SHIFT                        1
#define UART_D_R2T2_MASK                         0x4u
#define UART_D_R2T2_SHIFT                        2
#define UART_D_R3T3_MASK                         0x8u
#define UART_D_R3T3_SHIFT                        3
#define UART_D_R4T4_MASK                         0x10u
#define UART_D_R4T4_SHIFT                        4
#define UART_D_R5T5_MASK                         0x20u
#define UART_D_R5T5_SHIFT                        5
#define UART_D_R6T6_MASK                         0x40u
#define UART_D_R6T6_SHIFT                        6
#define UART_D_R7T7_MASK                         0x80u
#define UART_D_R7T7_SHIFT                        7

/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base pointer */
#define UART0_BASE_PTR                           ((UART_MemMapPtr)0x4006A000u)
/** Array initializer of UART peripheral base pointers */
#define UART_BASE_PTRS                           { UART0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register instance definitions */
/* UART0 */
#define UART0_BDH                                UART_BDH_REG(UART0_BASE_PTR)
#define UART0_BDL                                UART_BDL_REG(UART0_BASE_PTR)
#define UART0_C1                                 UART_C1_REG(UART0_BASE_PTR)
#define UART0_C2                                 UART_C2_REG(UART0_BASE_PTR)
#define UART0_S1                                 UART_S1_REG(UART0_BASE_PTR)
#define UART0_S2                                 UART_S2_REG(UART0_BASE_PTR)
#define UART0_C3                                 UART_C3_REG(UART0_BASE_PTR)
#define UART0_D                                  UART_D_REG(UART0_BASE_PTR)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group UART_Peripheral */


/* ----------------------------------------------------------------------------
   -- WDOG
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral WDOG
 * @{
 */

/** WDOG - Peripheral register structure */
typedef struct WDOG_MemMap {
  uint8_t CS1;                                     /**< Watchdog Control and Status Register 1, offset: 0x0 */
  uint8_t CS2;                                     /**< Watchdog Control and Status Register 2, offset: 0x1 */
  union {                                          /* offset: 0x2 */
    uint16_t CNT;                                    /**< Watchdog Counter Register., offset: 0x2 */
    struct {                                         /* offset: 0x2 */
      uint8_t CNTH;                                    /**< Watchdog Counter Register: High, offset: 0x2 */
      uint8_t CNTL;                                    /**< Watchdog Counter Register: Low, offset: 0x3 */
    } CNT8B;
  };
  union {                                          /* offset: 0x4 */
    uint16_t TOVAL;                                  /**< Watchdog Timeout Value Register., offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint8_t TOVALH;                                  /**< Watchdog Timeout Value Register: High, offset: 0x4 */
      uint8_t TOVALL;                                  /**< Watchdog Timeout Value Register: Low, offset: 0x5 */
    } TOVAL8B;
  };
  union {                                          /* offset: 0x6 */
    uint16_t WIN;                                    /**< Watchdog Window Register., offset: 0x6 */
    struct {                                         /* offset: 0x6 */
      uint8_t WINH;                                    /**< Watchdog Window Register: High, offset: 0x6 */
      uint8_t WINL;                                    /**< Watchdog Window Register: Low, offset: 0x7 */
    } WIN8B;
  };
} volatile *WDOG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register accessors */
#define WDOG_CS1_REG(base)                       ((base)->CS1)
#define WDOG_CS2_REG(base)                       ((base)->CS2)
#define WDOG_CNT_REG(base)                       ((base)->CNT)
#define WDOG_CNTH_REG(base)                      ((base)->CNT8B.CNTH)
#define WDOG_CNTL_REG(base)                      ((base)->CNT8B.CNTL)
#define WDOG_TOVAL_REG(base)                     ((base)->TOVAL)
#define WDOG_TOVALH_REG(base)                    ((base)->TOVAL8B.TOVALH)
#define WDOG_TOVALL_REG(base)                    ((base)->TOVAL8B.TOVALL)
#define WDOG_WIN_REG(base)                       ((base)->WIN)
#define WDOG_WINH_REG(base)                      ((base)->WIN8B.WINH)
#define WDOG_WINL_REG(base)                      ((base)->WIN8B.WINL)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/* CS1 Bit Fields */
#define WDOG_CS1_STOP_MASK                       0x1u
#define WDOG_CS1_STOP_SHIFT                      0
#define WDOG_CS1_WAIT_MASK                       0x2u
#define WDOG_CS1_WAIT_SHIFT                      1
#define WDOG_CS1_DBG_MASK                        0x4u
#define WDOG_CS1_DBG_SHIFT                       2
#define WDOG_CS1_TST_MASK                        0x18u
#define WDOG_CS1_TST_SHIFT                       3
#define WDOG_CS1_TST(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_TST_SHIFT))&WDOG_CS1_TST_MASK)
#define WDOG_CS1_UPDATE_MASK                     0x20u
#define WDOG_CS1_UPDATE_SHIFT                    5
#define WDOG_CS1_INT_MASK                        0x40u
#define WDOG_CS1_INT_SHIFT                       6
#define WDOG_CS1_EN_MASK                         0x80u
#define WDOG_CS1_EN_SHIFT                        7
/* CS2 Bit Fields */
#define WDOG_CS2_CLK_MASK                        0x3u
#define WDOG_CS2_CLK_SHIFT                       0
#define WDOG_CS2_CLK(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS2_CLK_SHIFT))&WDOG_CS2_CLK_MASK)
#define WDOG_CS2_PRES_MASK                       0x10u
#define WDOG_CS2_PRES_SHIFT                      4
#define WDOG_CS2_FLG_MASK                        0x40u
#define WDOG_CS2_FLG_SHIFT                       6
#define WDOG_CS2_WIN_MASK                        0x80u
#define WDOG_CS2_WIN_SHIFT                       7
/* CNT Bit Fields */
#define WDOG_CNT_CNT_MASK                        0xFFFFu
#define WDOG_CNT_CNT_SHIFT                       0
#define WDOG_CNT_CNT(x)                          (((uint16_t)(((uint16_t)(x))<<WDOG_CNT_CNT_SHIFT))&WDOG_CNT_CNT_MASK)
/* CNTH Bit Fields */
#define WDOG_CNTH_CNTHIGH_MASK                   0xFFu
#define WDOG_CNTH_CNTHIGH_SHIFT                  0
#define WDOG_CNTH_CNTHIGH(x)                     (((uint8_t)(((uint8_t)(x))<<WDOG_CNTH_CNTHIGH_SHIFT))&WDOG_CNTH_CNTHIGH_MASK)
/* CNTL Bit Fields */
#define WDOG_CNTL_CNTLOW_MASK                    0xFFu
#define WDOG_CNTL_CNTLOW_SHIFT                   0
#define WDOG_CNTL_CNTLOW(x)                      (((uint8_t)(((uint8_t)(x))<<WDOG_CNTL_CNTLOW_SHIFT))&WDOG_CNTL_CNTLOW_MASK)
/* TOVAL Bit Fields */
#define WDOG_TOVAL_TOVAL_MASK                    0xFFFFu
#define WDOG_TOVAL_TOVAL_SHIFT                   0
#define WDOG_TOVAL_TOVAL(x)                      (((uint16_t)(((uint16_t)(x))<<WDOG_TOVAL_TOVAL_SHIFT))&WDOG_TOVAL_TOVAL_MASK)
/* TOVALH Bit Fields */
#define WDOG_TOVALH_TOVALHIGH_MASK               0xFFu
#define WDOG_TOVALH_TOVALHIGH_SHIFT              0
#define WDOG_TOVALH_TOVALHIGH(x)                 (((uint8_t)(((uint8_t)(x))<<WDOG_TOVALH_TOVALHIGH_SHIFT))&WDOG_TOVALH_TOVALHIGH_MASK)
/* TOVALL Bit Fields */
#define WDOG_TOVALL_TOVALLOW_MASK                0xFFu
#define WDOG_TOVALL_TOVALLOW_SHIFT               0
#define WDOG_TOVALL_TOVALLOW(x)                  (((uint8_t)(((uint8_t)(x))<<WDOG_TOVALL_TOVALLOW_SHIFT))&WDOG_TOVALL_TOVALLOW_MASK)
/* WIN Bit Fields */
#define WDOG_WIN_WIN_MASK                        0xFFFFu
#define WDOG_WIN_WIN_SHIFT                       0
#define WDOG_WIN_WIN(x)                          (((uint16_t)(((uint16_t)(x))<<WDOG_WIN_WIN_SHIFT))&WDOG_WIN_WIN_MASK)
/* WINH Bit Fields */
#define WDOG_WINH_WINHIGH_MASK                   0xFFu
#define WDOG_WINH_WINHIGH_SHIFT                  0
#define WDOG_WINH_WINHIGH(x)                     (((uint8_t)(((uint8_t)(x))<<WDOG_WINH_WINHIGH_SHIFT))&WDOG_WINH_WINHIGH_MASK)
/* WINL Bit Fields */
#define WDOG_WINL_WINLOW_MASK                    0xFFu
#define WDOG_WINL_WINLOW_SHIFT                   0
#define WDOG_WINL_WINLOW(x)                      (((uint8_t)(((uint8_t)(x))<<WDOG_WINL_WINLOW_SHIFT))&WDOG_WINL_WINLOW_MASK)

/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base pointer */
#define WDOG_BASE_PTR                            ((WDOG_MemMapPtr)0x40052000u)
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           { WDOG_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register instance definitions */
/* WDOG */
#define WDOG_CS1                                 WDOG_CS1_REG(WDOG_BASE_PTR)
#define WDOG_CS2                                 WDOG_CS2_REG(WDOG_BASE_PTR)
#define WDOG_CNT                                 WDOG_CNT_REG(WDOG_BASE_PTR)
#define WDOG_CNTH                                WDOG_CNTH_REG(WDOG_BASE_PTR)
#define WDOG_CNTL                                WDOG_CNTL_REG(WDOG_BASE_PTR)
#define WDOG_TOVAL                               WDOG_TOVAL_REG(WDOG_BASE_PTR)
#define WDOG_TOVALH                              WDOG_TOVALH_REG(WDOG_BASE_PTR)
#define WDOG_TOVALL                              WDOG_TOVALL_REG(WDOG_BASE_PTR)
#define WDOG_WIN                                 WDOG_WIN_REG(WDOG_BASE_PTR)
#define WDOG_WINH                                WDOG_WINH_REG(WDOG_BASE_PTR)
#define WDOG_WINL                                WDOG_WINL_REG(WDOG_BASE_PTR)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group WDOG_Peripheral */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma pop
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_defines */


/* ----------------------------------------------------------------------------
   -- Backward Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Backward_Compatibility_Symbols Backward Compatibility
 * @{
 */

#define INT_Watchdog                            INT_WDOG
#define LDO_CTRM_CSLTM_MASK                     This_symb_has_been_deprecated
#define LDO_CTRM_CSLTM_SHIFT                    This_symb_has_been_deprecated
#define LDO_CTRM_CSLTM(x)                       This_symb_has_been_deprecated
#define LDO_CTRM_CSHTM_MASK                     This_symb_has_been_deprecated
#define LDO_CTRM_CSHTM_SHIFT                    This_symb_has_been_deprecated
#define LDO_CTRM_CSHTM(x)                       This_symb_has_been_deprecated

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols */


#else /* #if !defined(MCU_MWPR1516) */
  /* There is already included the same memory map. Check if it is compatible (has the same major version) */
  #if (MCU_MEM_MAP_VERSION != 0x0100u)
    #if (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING))
      #warning There are included two not compatible versions of memory maps. Please check possible differences.
    #endif /* (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING)) */
  #endif /* (MCU_MEM_MAP_VERSION != 0x0100u) */
#endif  /* #if !defined(MCU_MWPR1516) */

/* MWPR1516.h, eof. */
