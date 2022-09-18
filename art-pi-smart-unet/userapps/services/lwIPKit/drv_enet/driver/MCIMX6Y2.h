#ifndef _MCIMX6Y2_H_
#define _MCIMX6Y2_H_       

/* ----------------------------------------------------------------------------
   -- Configuration of the Cortex-A7 Processor and Core Peripherals
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Configuration of the Cortex-A7 Processor and Core Peripherals
 * @{
 */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0300U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0000U


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 160                /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  Software0_IRQn               = 0,                /**< Cortex-A7 Software Generated Interrupt 0 */
  Software1_IRQn               = 1,                /**< Cortex-A7 Software Generated Interrupt 1 */
  Software2_IRQn               = 2,                /**< Cortex-A7 Software Generated Interrupt 2 */
  Software3_IRQn               = 3,                /**< Cortex-A7 Software Generated Interrupt 3 */
  Software4_IRQn               = 4,                /**< Cortex-A7 Software Generated Interrupt 4 */
  Software5_IRQn               = 5,                /**< Cortex-A7 Software Generated Interrupt 5 */
  Software6_IRQn               = 6,                /**< Cortex-A7 Software Generated Interrupt 6 */
  Software7_IRQn               = 7,                /**< Cortex-A7 Software Generated Interrupt 7 */
  Software8_IRQn               = 8,                /**< Cortex-A7 Software Generated Interrupt 8 */
  Software9_IRQn               = 9,                /**< Cortex-A7 Software Generated Interrupt 9 */
  Software10_IRQn              = 10,               /**< Cortex-A7 Software Generated Interrupt 10 */
  Software11_IRQn              = 11,               /**< Cortex-A7 Software Generated Interrupt 11 */
  Software12_IRQn              = 12,               /**< Cortex-A7 Software Generated Interrupt 12 */
  Software13_IRQn              = 13,               /**< Cortex-A7 Software Generated Interrupt 13 */
  Software14_IRQn              = 14,               /**< Cortex-A7 Software Generated Interrupt 14 */
  Software15_IRQn              = 15,               /**< Cortex-A7 Software Generated Interrupt 15 */
  VirtualMaintenance_IRQn      = 25,               /**< Cortex-A7 Virtual Maintenance Interrupt */
  HypervisorTimer_IRQn         = 26,               /**< Cortex-A7 Hypervisor Timer Interrupt */
  VirtualTimer_IRQn            = 27,               /**< Cortex-A7 Virtual Timer Interrupt */
  LegacyFastInt_IRQn           = 28,               /**< Cortex-A7 Legacy nFIQ signal Interrupt */
  SecurePhyTimer_IRQn          = 29,               /**< Cortex-A7 Secure Physical Timer Interrupt */
  NonSecurePhyTimer_IRQn       = 30,               /**< Cortex-A7 Non-secure Physical Timer Interrupt */
  LegacyIRQ_IRQn               = 31,               /**< Cortex-A7 Legacy nIRQ Interrupt */

  /* Device specific interrupts */
  IOMUXC_IRQn                  = 32,               /**< General Purpose Register 1 from IOMUXC. Used to notify cores on exception condition while boot. */
  DAP_IRQn                     = 33,               /**< Debug Access Port interrupt request. */
  SDMA_IRQn                    = 34,               /**< SDMA interrupt request from all channels. */
  TSC_IRQn                     = 35,               /**< TSC interrupt. */
  SNVS_IRQn                    = 36,               /**< Logic OR of SNVS_LP and SNVS_HP interrupts. */
  LCDIF_IRQn                   = 37,               /**< LCDIF sync interrupt. */
  RNGB_IRQn                    = 38,               /**< RNGB interrupt. */
  CSI_IRQn                     = 39,               /**< CMOS Sensor Interface interrupt request. */
  PXP_IRQ0_IRQn                = 40,               /**< PXP interrupt pxp_irq_0. */
  SCTR_IRQ0_IRQn               = 41,               /**< SCTR compare interrupt ipi_int[0]. */
  SCTR_IRQ1_IRQn               = 42,               /**< SCTR compare interrupt ipi_int[1]. */
  WDOG3_IRQn                   = 43,               /**< WDOG3 timer reset interrupt request. */
  Reserved44_IRQn              = 44,               /**< Reserved */
  APBH_IRQn                    = 45,               /**< DMA Logical OR of APBH DMA channels 0-3 completion and error interrupts. */
  WEIM_IRQn                    = 46,               /**< WEIM interrupt request. */
  RAWNAND_BCH_IRQn             = 47,               /**< BCH operation complete interrupt. */
  RAWNAND_GPMI_IRQn            = 48,               /**< GPMI operation timeout error interrupt. */
  UART6_IRQn                   = 49,               /**< UART6 interrupt request. */
  PXP_IRQ1_IRQn                = 50,               /**< PXP interrupt pxp_irq_1. */
  SNVS_Consolidated_IRQn       = 51,               /**< SNVS consolidated interrupt. */
  SNVS_Security_IRQn           = 52,               /**< SNVS security interrupt. */
  CSU_IRQn                     = 53,               /**< CSU interrupt request 1. Indicates to the processor that one or more alarm inputs were asserted. */
  USDHC1_IRQn                  = 54,               /**< USDHC1 (Enhanced SDHC) interrupt request. */
  USDHC2_IRQn                  = 55,               /**< USDHC2 (Enhanced SDHC) interrupt request. */
  SAI3_RX_IRQn                 = 56,               /**< SAI3 interrupt ipi_int_sai_rx. */
  SAI3_TX_IRQn                 = 57,               /**< SAI3 interrupt ipi_int_sai_tx. */
  UART1_IRQn                   = 58,               /**< UART1 interrupt request. */
  UART2_IRQn                   = 59,               /**< UART2 interrupt request. */
  UART3_IRQn                   = 60,               /**< UART3 interrupt request. */
  UART4_IRQn                   = 61,               /**< UART4 interrupt request. */
  UART5_IRQn                   = 62,               /**< UART5 interrupt request. */
  eCSPI1_IRQn                  = 63,               /**< eCSPI1 interrupt request. */
  eCSPI2_IRQn                  = 64,               /**< eCSPI2 interrupt request. */
  eCSPI3_IRQn                  = 65,               /**< eCSPI3 interrupt request. */
  eCSPI4_IRQn                  = 66,               /**< eCSPI4 interrupt request. */
  I2C4_IRQn                    = 67,               /**< I2C4 interrupt request. */
  I2C1_IRQn                    = 68,               /**< I2C1 interrupt request. */
  I2C2_IRQn                    = 69,               /**< I2C2 interrupt request. */
  I2C3_IRQn                    = 70,               /**< I2C3 interrupt request. */
  UART7_IRQn                   = 71,               /**< UART-7 ORed interrupt. */
  UART8_IRQn                   = 72,               /**< UART-8 ORed interrupt. */
  Reserved73_IRQn              = 73,               /**< Reserved */
  USB_OTG2_IRQn                = 74,               /**< USBO2 USB OTG2 */
  USB_OTG1_IRQn                = 75,               /**< USBO2 USB OTG1 */
  USB_PHY1_IRQn                = 76,               /**< UTMI0 interrupt request. */
  USB_PHY2_IRQn                = 77,               /**< UTMI1 interrupt request. */
  DCP_IRQ_IRQn                 = 78,               /**< DCP interrupt request dcp_irq. */
  DCP_VMI_IRQ_IRQn             = 79,               /**< DCP interrupt request dcp_vmi_irq. */
  DCP_SEC_IRQ_IRQn             = 80,               /**< DCP interrupt request secure_irq. */
  TEMPMON_IRQn                 = 81,               /**< Temperature Monitor Temperature Sensor (temperature greater than threshold) interrupt request. */
  ASRC_IRQn                    = 82,               /**< ASRC interrupt request. */
  ESAI_IRQn                    = 83,               /**< ESAI interrupt request. */
  SPDIF_IRQn                   = 84,               /**< SPDIF interrupt. */
  Reserved85_IRQn              = 85,               /**< Reserved */
  PMU_IRQ1_IRQn                = 86,               /**< Brown-out event on either the 1.1, 2.5 or 3.0 regulators. */
  GPT1_IRQn                    = 87,               /**< Logical OR of GPT1 rollover interrupt line, input capture 1 and 2 lines, output compare 1, 2, and 3 interrupt lines. */
  EPIT1_IRQn                   = 88,               /**< EPIT1 output compare interrupt. */
  EPIT2_IRQn                   = 89,               /**< EPIT2 output compare interrupt. */
  GPIO1_INT7_IRQn              = 90,               /**< INT7 interrupt request. */
  GPIO1_INT6_IRQn              = 91,               /**< INT6 interrupt request. */
  GPIO1_INT5_IRQn              = 92,               /**< INT5 interrupt request. */
  GPIO1_INT4_IRQn              = 93,               /**< INT4 interrupt request. */
  GPIO1_INT3_IRQn              = 94,               /**< INT3 interrupt request. */
  GPIO1_INT2_IRQn              = 95,               /**< INT2 interrupt request. */
  GPIO1_INT1_IRQn              = 96,               /**< INT1 interrupt request. */
  GPIO1_INT0_IRQn              = 97,               /**< INT0 interrupt request. */
  GPIO1_Combined_0_15_IRQn     = 98,               /**< Combined interrupt indication for GPIO1 signals 0 - 15. */
  GPIO1_Combined_16_31_IRQn    = 99,               /**< Combined interrupt indication for GPIO1 signals 16 - 31. */
  GPIO2_Combined_0_15_IRQn     = 100,              /**< Combined interrupt indication for GPIO2 signals 0 - 15. */
  GPIO2_Combined_16_31_IRQn    = 101,              /**< Combined interrupt indication for GPIO2 signals 16 - 31. */
  GPIO3_Combined_0_15_IRQn     = 102,              /**< Combined interrupt indication for GPIO3 signals 0 - 15. */
  GPIO3_Combined_16_31_IRQn    = 103,              /**< Combined interrupt indication for GPIO3 signals 16 - 31. */
  GPIO4_Combined_0_15_IRQn     = 104,              /**< Combined interrupt indication for GPIO4 signals 0 - 15. */
  GPIO4_Combined_16_31_IRQn    = 105,              /**< Combined interrupt indication for GPIO4 signals 16 - 31. */
  GPIO5_Combined_0_15_IRQn     = 106,              /**< Combined interrupt indication for GPIO5 signals 0 - 15. */
  GPIO5_Combined_16_31_IRQn    = 107,              /**< Combined interrupt indication for GPIO5 signals 16 - 31. */
  Reserved108_IRQn             = 108,              /**< Reserved */
  Reserved109_IRQn             = 109,              /**< Reserved */
  Reserved110_IRQn             = 110,              /**< Reserved */
  Reserved111_IRQn             = 111,              /**< Reserved */
  WDOG1_IRQn                   = 112,              /**< WDOG1 timer reset interrupt request. */
  WDOG2_IRQn                   = 113,              /**< WDOG2 timer reset interrupt request. */
  KPP_IRQn                     = 114,              /**< Key Pad interrupt request. */
  PWM1_IRQn                    = 115,              /**< hasRegInstance(`PWM1`)?`Cumulative interrupt line for PWM1. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.`:`Reserved`) */
  PWM2_IRQn                    = 116,              /**< hasRegInstance(`PWM2`)?`Cumulative interrupt line for PWM2. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.`:`Reserved`) */
  PWM3_IRQn                    = 117,              /**< hasRegInstance(`PWM3`)?`Cumulative interrupt line for PWM3. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.`:`Reserved`) */
  PWM4_IRQn                    = 118,              /**< hasRegInstance(`PWM4`)?`Cumulative interrupt line for PWM4. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.`:`Reserved`) */
  CCM_IRQ1_IRQn                = 119,              /**< CCM interrupt request ipi_int_1. */
  CCM_IRQ2_IRQn                = 120,              /**< CCM interrupt request ipi_int_2. */
  GPC_IRQn                     = 121,              /**< GPC interrupt request 1. */
  Reserved122_IRQn             = 122,              /**< Reserved */
  SRC_IRQn                     = 123,              /**< SRC interrupt request src_ipi_int_1. */
  Reserved124_IRQn             = 124,              /**< Reserved */
  Reserved125_IRQn             = 125,              /**< Reserved */
  CPU_PerformanceUnit_IRQn     = 126,              /**< Performance Unit interrupt ~ipi_pmu_irq_b. */
  CPU_CTI_Trigger_IRQn         = 127,              /**< CTI trigger outputs interrupt ~ipi_cti_irq_b. */
  SRC_Combined_IRQn            = 128,              /**< Combined CPU wdog interrupts (4x) out of SRC. */
  SAI1_IRQn                    = 129,              /**< SAI1 interrupt request. */
  SAI2_IRQn                    = 130,              /**< SAI2 interrupt request. */
  Reserved131_IRQn             = 131,              /**< Reserved */
  ADC1_IRQn                    = 132,              /**< ADC1 interrupt request. */
  ADC_5HC_IRQn                 = 133,              /**< ADC_5HC interrupt request. */
  Reserved134_IRQn             = 134,              /**< Reserved */
  Reserved135_IRQn             = 135,              /**< Reserved */
  SJC_IRQn                     = 136,              /**< SJC interrupt from General Purpose register. */
  CAAM_Job_Ring0_IRQn          = 137,              /**< CAAM job ring 0 interrupt ipi_caam_irq0. */
  CAAM_Job_Ring1_IRQn          = 138,              /**< CAAM job ring 1 interrupt ipi_caam_irq1. */
  QSPI_IRQn                    = 139,              /**< QSPI1 interrupt request ipi_int_ored. */
  TZASC_IRQn                   = 140,              /**< TZASC (PL380) interrupt request. */
  GPT2_IRQn                    = 141,              /**< Logical OR of GPT2 rollover interrupt line, input capture 1 and 2 lines, output compare 1, 2 and 3 interrupt lines. */
  CAN1_IRQn                    = 142,              /**< Combined interrupt of ini_int_busoff,ini_int_error,ipi_int_mbor,ipi_int_txwarning and ipi_int_waken */
  CAN2_IRQn                    = 143,              /**< Combined interrupt of ini_int_busoff,ini_int_error,ipi_int_mbor,ipi_int_txwarning and ipi_int_waken */
  Reserved144_IRQn             = 144,              /**< Reserved */
  Reserved145_IRQn             = 145,              /**< Reserved */
  PWM5_IRQn                    = 146,              /**< Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line */
  PWM6_IRQn                    = 147,              /**< Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line */
  PWM7_IRQn                    = 148,              /**< Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line */
  PWM8_IRQn                    = 149,              /**< Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line */
  ENET1_IRQn                   = 150,              /**< ENET1 interrupt */
  ENET1_1588_IRQn              = 151,              /**< ENET1 1588 Timer interrupt [synchronous] request. */
  ENET2_IRQn                   = 152,              /**< ENET2 interrupt */
  ENET2_1588_IRQn              = 153,              /**< MAC 0 1588 Timer interrupt [synchronous] request. */
  Reserved154_IRQn             = 154,              /**< Reserved */
  Reserved155_IRQn             = 155,              /**< Reserved */
  Reserved156_IRQn             = 156,              /**< Reserved */
  Reserved157_IRQn             = 157,              /**< Reserved */
  Reserved158_IRQn             = 158,              /**< Reserved */
  PMU_IRQ2_IRQn                = 159               /**< Brown-out event on either core, gpu or soc regulators. */
} IRQn_Type;


#define __CA7_REV                      0x0005    /**< Core revision r0p5 */
#define __GIC_PRIO_BITS                5         /**< Number of Bits used for Priority Levels */
#define __FPU_PRESENT                  1         /**< FPU present or not */

#include "core_ca7.h"                  /* Core Peripheral Access Layer */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
/*!
 * @addtogroup iomuxc_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC SW_MUX_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC SW_MUX_CTL_PAD collections.
 */
typedef enum _iomuxc_sw_mux_ctl_pad
{
    kIOMUXC_SW_MUX_CTL_PAD_JTAG_MOD = 0U,          /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_JTAG_TMS = 1U,          /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_JTAG_TDO = 2U,          /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_JTAG_TDI = 3U,          /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_JTAG_TCK = 4U,          /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_JTAG_TRST_B = 5U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00 = 6U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01 = 7U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02 = 8U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 9U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO04 = 10U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO05 = 11U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06 = 12U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07 = 13U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08 = 14U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09 = 15U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA = 16U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA = 17U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART1_CTS_B = 18U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART1_RTS_B = 19U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA = 20U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA = 21U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART2_CTS_B = 22U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART2_RTS_B = 23U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART3_TX_DATA = 24U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART3_RX_DATA = 25U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART3_CTS_B = 26U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART3_RTS_B = 27U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART4_TX_DATA = 28U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART4_RX_DATA = 29U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART5_TX_DATA = 30U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_UART5_RX_DATA = 31U,    /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_RX_DATA0 = 32U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_RX_DATA1 = 33U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_RX_EN = 34U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_TX_DATA0 = 35U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_TX_DATA1 = 36U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_TX_EN = 37U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK = 38U,     /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET1_RX_ER = 39U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_RX_DATA0 = 40U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_RX_DATA1 = 41U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_RX_EN = 42U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA0 = 43U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA1 = 44U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_TX_EN = 45U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_TX_CLK = 46U,     /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_ENET2_RX_ER = 47U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_CLK  = 48U,         /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_ENABLE = 49U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_HSYNC = 50U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_VSYNC = 51U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_RESET = 52U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA00 = 53U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA01 = 54U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA02 = 55U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA03 = 56U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA04 = 57U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA05 = 58U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA06 = 59U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA07 = 60U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA08 = 61U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA09 = 62U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA10 = 63U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA11 = 64U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA12 = 65U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA13 = 66U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA14 = 67U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA15 = 68U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA16 = 69U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA17 = 70U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA18 = 71U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA19 = 72U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA20 = 73U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA21 = 74U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA22 = 75U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_LCD_DATA23 = 76U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_RE_B = 77U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_WE_B = 78U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA00 = 79U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA01 = 80U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA02 = 81U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA03 = 82U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA04 = 83U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA05 = 84U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA06 = 85U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DATA07 = 86U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_ALE = 87U,         /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_WP_B = 88U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_READY_B = 89U,     /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_CE0_B = 90U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B = 91U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_CLE = 92U,         /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_NAND_DQS = 93U,         /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_SD1_CMD  = 94U,         /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_SD1_CLK  = 95U,         /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_SD1_DATA0 = 96U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_SD1_DATA1 = 97U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_SD1_DATA2 = 98U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_SD1_DATA3 = 99U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_MCLK = 100U,        /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_PIXCLK = 101U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_VSYNC = 102U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_HSYNC = 103U,       /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA00 = 104U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA01 = 105U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA02 = 106U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA03 = 107U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA04 = 108U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA05 = 109U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA06 = 110U,      /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SW_MUX_CTL_PAD_CSI_DATA07 = 111U,      /**< IOMUXC SW_MUX_CTL_PAD index */
} iomuxc_sw_mux_ctl_pad_t;

/*!
 * @addtogroup iomuxc_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC SW_PAD_CTL_PAD_DDR
 *
 * Defines the enumeration for the IOMUXC SW_PAD_CTL_PAD_DDR collections.
 */
typedef enum _iomuxc_sw_pad_ctl_pad_ddr
{
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR00 = 0U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR01 = 1U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR02 = 2U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR03 = 3U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR04 = 4U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR05 = 5U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR06 = 6U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR07 = 7U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR08 = 8U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR09 = 9U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR10 = 10U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR11 = 11U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR12 = 12U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR13 = 13U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR14 = 14U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ADDR15 = 15U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_DQM0 = 16U,        /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_DQM1 = 17U,        /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_RAS_B = 18U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_CAS_B = 19U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_CS0_B = 20U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_CS1_B = 21U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDWE_B = 22U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ODT0 = 23U,        /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_ODT1 = 24U,        /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDBA0 = 25U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDBA1 = 26U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDBA2 = 27U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDCKE0 = 28U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDCKE1 = 29U,      /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDCLK0_P = 30U,    /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS0_P = 31U,     /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS1_P = 32U,     /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
    kIOMUXC_SW_PAD_CTL_PAD_DRAM_RESET = 33U,       /**< IOMUXC SW_PAD_CTL_PAD_DDR index */
} iomuxc_sw_pad_ctl_pad_ddr_t;

/*!
 * @addtogroup iomuxc_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC SW_PAD_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC SW_PAD_CTL_PAD collections.
 */
typedef enum _iomuxc_sw_pad_ctl_pad
{
    kIOMUXC_SW_PAD_CTL_PAD_JTAG_MOD = 0U,          /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_JTAG_TMS = 1U,          /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_JTAG_TDO = 2U,          /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_JTAG_TDI = 3U,          /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_JTAG_TCK = 4U,          /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_JTAG_TRST_B = 5U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00 = 6U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01 = 7U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02 = 8U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 9U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO04 = 10U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO05 = 11U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06 = 12U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07 = 13U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO08 = 14U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_GPIO1_IO09 = 15U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA = 16U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA = 17U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART1_CTS_B = 18U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART1_RTS_B = 19U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART2_TX_DATA = 20U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART2_RX_DATA = 21U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART2_CTS_B = 22U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART2_RTS_B = 23U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART3_TX_DATA = 24U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART3_RX_DATA = 25U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART3_CTS_B = 26U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART3_RTS_B = 27U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART4_TX_DATA = 28U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART4_RX_DATA = 29U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART5_TX_DATA = 30U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_UART5_RX_DATA = 31U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_RX_DATA0 = 32U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_RX_DATA1 = 33U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_RX_EN = 34U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_TX_DATA0 = 35U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_TX_DATA1 = 36U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_TX_EN = 37U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_TX_CLK = 38U,     /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET1_RX_ER = 39U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_RX_DATA0 = 40U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_RX_DATA1 = 41U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_RX_EN = 42U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_TX_DATA0 = 43U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_TX_DATA1 = 44U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_TX_EN = 45U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_TX_CLK = 46U,     /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_ENET2_RX_ER = 47U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_CLK  = 48U,         /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_ENABLE = 49U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_HSYNC = 50U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_VSYNC = 51U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_RESET = 52U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA00 = 53U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA01 = 54U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA02 = 55U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA03 = 56U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA04 = 57U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA05 = 58U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA06 = 59U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA07 = 60U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA08 = 61U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA09 = 62U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA10 = 63U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA11 = 64U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA12 = 65U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA13 = 66U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA14 = 67U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA15 = 68U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA16 = 69U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA17 = 70U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA18 = 71U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA19 = 72U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA20 = 73U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA21 = 74U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA22 = 75U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_LCD_DATA23 = 76U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_RE_B = 77U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_WE_B = 78U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA00 = 79U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA01 = 80U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA02 = 81U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA03 = 82U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA04 = 83U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA05 = 84U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA06 = 85U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DATA07 = 86U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_ALE = 87U,         /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_WP_B = 88U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_READY_B = 89U,     /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_CE0_B = 90U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_CE1_B = 91U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_CLE = 92U,         /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_NAND_DQS = 93U,         /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_SD1_CMD  = 94U,         /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_SD1_CLK  = 95U,         /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_SD1_DATA0 = 96U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_SD1_DATA1 = 97U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_SD1_DATA2 = 98U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_SD1_DATA3 = 99U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_MCLK = 100U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_PIXCLK = 101U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_VSYNC = 102U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_HSYNC = 103U,       /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA00 = 104U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA01 = 105U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA02 = 106U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA03 = 107U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA04 = 108U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA05 = 109U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA06 = 110U,      /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SW_PAD_CTL_PAD_CSI_DATA07 = 111U,      /**< IOMUXC SW_PAD_CTL_PAD index */
} iomuxc_sw_pad_ctl_pad_t;

/*!
 * @brief Enumeration for the IOMUXC select input
 *
 * Defines the enumeration for the IOMUXC select input collections.
 */
typedef enum _iomuxc_select_input
{
    kIOMUXC_ANATOP_USB_OTG_ID_SELECT_INPUT = 0U,   /**< IOMUXC select input index */
    kIOMUXC_USB_OTG2_ID_SELECT_INPUT = 1U,         /**< IOMUXC select input index */
    kIOMUXC_CCM_PMIC_READY_SELECT_INPUT = 2U,      /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA02_SELECT_INPUT = 3U,          /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA03_SELECT_INPUT = 4U,          /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA05_SELECT_INPUT = 5U,          /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA00_SELECT_INPUT = 6U,          /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA01_SELECT_INPUT = 7U,          /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA04_SELECT_INPUT = 8U,          /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA06_SELECT_INPUT = 9U,          /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA07_SELECT_INPUT = 10U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA08_SELECT_INPUT = 11U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA09_SELECT_INPUT = 12U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA10_SELECT_INPUT = 13U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA11_SELECT_INPUT = 14U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA12_SELECT_INPUT = 15U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA13_SELECT_INPUT = 16U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA14_SELECT_INPUT = 17U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA15_SELECT_INPUT = 18U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA16_SELECT_INPUT = 19U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA17_SELECT_INPUT = 20U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA18_SELECT_INPUT = 21U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA19_SELECT_INPUT = 22U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA20_SELECT_INPUT = 23U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA21_SELECT_INPUT = 24U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA22_SELECT_INPUT = 25U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_DATA23_SELECT_INPUT = 26U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_HSYNC_SELECT_INPUT  = 27U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_PIXCLK_SELECT_INPUT = 28U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_VSYNC_SELECT_INPUT  = 29U,         /**< IOMUXC select input index */
    kIOMUXC_CSI_FIELD_SELECT_INPUT  = 30U,         /**< IOMUXC select input index */
    kIOMUXC_ECSPI1_SCLK_SELECT_INPUT = 31U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI1_MISO_SELECT_INPUT = 32U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI1_MOSI_SELECT_INPUT = 33U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI1_SS0_B_SELECT_INPUT = 34U,       /**< IOMUXC select input index */
    kIOMUXC_ECSPI2_SCLK_SELECT_INPUT = 35U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI2_MISO_SELECT_INPUT = 36U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI2_MOSI_SELECT_INPUT = 37U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI2_SS0_B_SELECT_INPUT = 38U,       /**< IOMUXC select input index */
    kIOMUXC_ECSPI3_SCLK_SELECT_INPUT = 39U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI3_MISO_SELECT_INPUT = 40U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI3_MOSI_SELECT_INPUT = 41U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI3_SS0_B_SELECT_INPUT = 42U,       /**< IOMUXC select input index */
    kIOMUXC_ECSPI4_SCLK_SELECT_INPUT = 43U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI4_MISO_SELECT_INPUT = 44U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI4_MOSI_SELECT_INPUT = 45U,        /**< IOMUXC select input index */
    kIOMUXC_ECSPI4_SS0_B_SELECT_INPUT = 46U,       /**< IOMUXC select input index */
    kIOMUXC_ENET1_REF_CLK1_SELECT_INPUT = 47U,     /**< IOMUXC select input index */
    kIOMUXC_ENET1_MAC0_MDIO_SELECT_INPUT = 48U,    /**< IOMUXC select input index */
    kIOMUXC_ENET2_REF_CLK2_SELECT_INPUT = 49U,     /**< IOMUXC select input index */
    kIOMUXC_ENET2_MAC0_MDIO_SELECT_INPUT = 50U,    /**< IOMUXC select input index */
    kIOMUXC_FLEXCAN1_RX_SELECT_INPUT = 51U,        /**< IOMUXC select input index */
    kIOMUXC_FLEXCAN2_RX_SELECT_INPUT = 52U,        /**< IOMUXC select input index */
    kIOMUXC_GPT1_CAPTURE1_SELECT_INPUT = 53U,      /**< IOMUXC select input index */
    kIOMUXC_GPT1_CAPTURE2_SELECT_INPUT = 54U,      /**< IOMUXC select input index */
    kIOMUXC_GPT1_CLK_SELECT_INPUT   = 55U,         /**< IOMUXC select input index */
    kIOMUXC_GPT2_CAPTURE1_SELECT_INPUT = 56U,      /**< IOMUXC select input index */
    kIOMUXC_GPT2_CAPTURE2_SELECT_INPUT = 57U,      /**< IOMUXC select input index */
    kIOMUXC_GPT2_CLK_SELECT_INPUT   = 58U,         /**< IOMUXC select input index */
    kIOMUXC_I2C1_SCL_SELECT_INPUT   = 59U,         /**< IOMUXC select input index */
    kIOMUXC_I2C1_SDA_SELECT_INPUT   = 60U,         /**< IOMUXC select input index */
    kIOMUXC_I2C2_SCL_SELECT_INPUT   = 61U,         /**< IOMUXC select input index */
    kIOMUXC_I2C2_SDA_SELECT_INPUT   = 62U,         /**< IOMUXC select input index */
    kIOMUXC_I2C3_SCL_SELECT_INPUT   = 63U,         /**< IOMUXC select input index */
    kIOMUXC_I2C3_SDA_SELECT_INPUT   = 64U,         /**< IOMUXC select input index */
    kIOMUXC_I2C4_SCL_SELECT_INPUT   = 65U,         /**< IOMUXC select input index */
    kIOMUXC_I2C4_SDA_SELECT_INPUT   = 66U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_COL0_SELECT_INPUT   = 67U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_COL1_SELECT_INPUT   = 68U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_COL2_SELECT_INPUT   = 69U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_ROW0_SELECT_INPUT   = 70U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_ROW1_SELECT_INPUT   = 71U,         /**< IOMUXC select input index */
    kIOMUXC_KPP_ROW2_SELECT_INPUT   = 72U,         /**< IOMUXC select input index */
    kIOMUXC_LCD_BUSY_SELECT_INPUT   = 73U,         /**< IOMUXC select input index */
    kIOMUXC_SAI1_MCLK_SELECT_INPUT  = 74U,         /**< IOMUXC select input index */
    kIOMUXC_SAI1_RX_DATA_SELECT_INPUT = 75U,       /**< IOMUXC select input index */
    kIOMUXC_SAI1_TX_BCLK_SELECT_INPUT = 76U,       /**< IOMUXC select input index */
    kIOMUXC_SAI1_TX_SYNC_SELECT_INPUT = 77U,       /**< IOMUXC select input index */
    kIOMUXC_SAI2_MCLK_SELECT_INPUT  = 78U,         /**< IOMUXC select input index */
    kIOMUXC_SAI2_RX_DATA_SELECT_INPUT = 79U,       /**< IOMUXC select input index */
    kIOMUXC_SAI2_TX_BCLK_SELECT_INPUT = 80U,       /**< IOMUXC select input index */
    kIOMUXC_SAI2_TX_SYNC_SELECT_INPUT = 81U,       /**< IOMUXC select input index */
    kIOMUXC_SAI3_MCLK_SELECT_INPUT  = 82U,         /**< IOMUXC select input index */
    kIOMUXC_SAI3_RX_DATA_SELECT_INPUT = 83U,       /**< IOMUXC select input index */
    kIOMUXC_SAI3_TX_BCLK_SELECT_INPUT = 84U,       /**< IOMUXC select input index */
    kIOMUXC_SAI3_TX_SYNC_SELECT_INPUT = 85U,       /**< IOMUXC select input index */
    kIOMUXC_SDMA_EVENTS0_SELECT_INPUT = 86U,       /**< IOMUXC select input index */
    kIOMUXC_SDMA_EVENTS1_SELECT_INPUT = 87U,       /**< IOMUXC select input index */
    kIOMUXC_SPDIF_IN_SELECT_INPUT   = 88U,         /**< IOMUXC select input index */
    kIOMUXC_SPDIF_EXT_CLK_SELECT_INPUT = 89U,      /**< IOMUXC select input index */
    kIOMUXC_UART1_RTS_B_SELECT_INPUT = 90U,        /**< IOMUXC select input index */
    kIOMUXC_UART1_RX_DATA_SELECT_INPUT = 91U,      /**< IOMUXC select input index */
    kIOMUXC_UART2_RTS_B_SELECT_INPUT = 92U,        /**< IOMUXC select input index */
    kIOMUXC_UART2_RX_DATA_SELECT_INPUT = 93U,      /**< IOMUXC select input index */
    kIOMUXC_UART3_RTS_B_SELECT_INPUT = 94U,        /**< IOMUXC select input index */
    kIOMUXC_UART3_RX_DATA_SELECT_INPUT = 95U,      /**< IOMUXC select input index */
    kIOMUXC_UART4_RTS_B_SELECT_INPUT = 96U,        /**< IOMUXC select input index */
    kIOMUXC_UART4_RX_DATA_SELECT_INPUT = 97U,      /**< IOMUXC select input index */
    kIOMUXC_UART5_RTS_B_SELECT_INPUT = 98U,        /**< IOMUXC select input index */
    kIOMUXC_UART5_RX_DATA_SELECT_INPUT = 99U,      /**< IOMUXC select input index */
    kIOMUXC_UART6_RTS_B_SELECT_INPUT = 100U,       /**< IOMUXC select input index */
    kIOMUXC_UART6_RX_DATA_SELECT_INPUT = 101U,     /**< IOMUXC select input index */
    kIOMUXC_UART7_RTS_B_SELECT_INPUT = 102U,       /**< IOMUXC select input index */
    kIOMUXC_UART7_RX_DATA_SELECT_INPUT = 103U,     /**< IOMUXC select input index */
    kIOMUXC_UART8_RTS_B_SELECT_INPUT = 104U,       /**< IOMUXC select input index */
    kIOMUXC_UART8_RX_DATA_SELECT_INPUT = 105U,     /**< IOMUXC select input index */
    kIOMUXC_USB_OTG2_OC_SELECT_INPUT = 106U,       /**< IOMUXC select input index */
    kIOMUXC_USB_OTG_OC_SELECT_INPUT = 107U,        /**< IOMUXC select input index */
    kIOMUXC_USDHC1_CD_B_SELECT_INPUT = 108U,       /**< IOMUXC select input index */
    kIOMUXC_USDHC1_WP_SELECT_INPUT  = 109U,        /**< IOMUXC select input index */
    kIOMUXC_USDHC2_CLK_SELECT_INPUT = 110U,        /**< IOMUXC select input index */
    kIOMUXC_USDHC2_CD_B_SELECT_INPUT = 111U,       /**< IOMUXC select input index */
    kIOMUXC_USDHC2_CMD_SELECT_INPUT = 112U,        /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA0_SELECT_INPUT = 113U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA1_SELECT_INPUT = 114U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA2_SELECT_INPUT = 115U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA3_SELECT_INPUT = 116U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA4_SELECT_INPUT = 117U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA5_SELECT_INPUT = 118U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA6_SELECT_INPUT = 119U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_DATA7_SELECT_INPUT = 120U,      /**< IOMUXC select input index */
    kIOMUXC_USDHC2_WP_SELECT_INPUT  = 121U,        /**< IOMUXC select input index */
} iomuxc_select_input_t;

/* @} */

/*!
 * @brief Enumeration for the IOMUXC group
 *
 * Defines the enumeration for the IOMUXC group collections.
 */
typedef enum _iomuxc_grp
{
    kIOMUXC_SW_PAD_CTL_GRP_ADDDS    = 0U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_DDRMODE_CTL = 1U,       /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_B0DS     = 2U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_DDRPK    = 3U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_CTLDS    = 4U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_B1DS     = 5U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_DDRHYS   = 6U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_DDRPKE   = 7U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_DDRMODE  = 8U,          /**< IOMUXC group index */
    kIOMUXC_SW_PAD_CTL_GRP_DDR_TYPE = 9U,          /**< IOMUXC group index */
} iomuxc_grp_t;

/* @} */

/*!
 * @addtogroup iomuxc_snvs_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC_SNVS SW_MUX_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC_SNVS SW_MUX_CTL_PAD collections.
 */
typedef enum _iomuxc_snvs_sw_mux_ctl_pad
{
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_BOOT_MODE0 = 0U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_BOOT_MODE1 = 1U,   /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER0 = 2U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1 = 3U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER2 = 4U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = 5U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER4 = 6U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER5 = 7U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER6 = 8U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER7 = 9U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER8 = 10U, /**< IOMUXC SW_MUX_CTL_PAD index */
    kIOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER9 = 11U, /**< IOMUXC SW_MUX_CTL_PAD index */
} iomuxc_snvs_sw_mux_ctl_pad_t;

/*!
 * @addtogroup iomuxc_snvs_pads
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Enumeration for the IOMUXC_SNVS SW_PAD_CTL_PAD
 *
 * Defines the enumeration for the IOMUXC_SNVS SW_PAD_CTL_PAD collections.
 */
typedef enum _iomuxc_snvs_sw_pad_ctl_pad
{
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE = 0U,    /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B = 1U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF = 2U,        /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_PMIC_ON_REQ = 3U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_CCM_PMIC_STBY_REQ = 4U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_BOOT_MODE0 = 5U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_BOOT_MODE1 = 6U,   /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER0 = 7U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER1 = 8U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER2 = 9U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER3 = 10U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER4 = 11U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER5 = 12U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER6 = 13U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER7 = 14U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER8 = 15U, /**< IOMUXC SW_PAD_CTL_PAD index */
    kIOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER9 = 16U, /**< IOMUXC SW_PAD_CTL_PAD index */
} iomuxc_snvs_sw_pad_ctl_pad_t;


/*!
 * @}
 */ /* end of group Mapping_Information */


/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma push
  #pragma anon_unions
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif


/* ----------------------------------------------------------------------------
   -- IOMUXC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_Peripheral_Access_Layer IOMUXC Peripheral Access Layer
 * @{
 */

/** IOMUXC - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[68];
  __IO uint32_t SW_MUX_CTL_PAD[112];               /**< SW_MUX_CTL_PAD_JTAG_MOD SW MUX Control Register..SW_MUX_CTL_PAD_CSI_DATA07 SW MUX Control Register, array offset: 0x44, array step: 0x4 */
  __IO uint32_t SW_PAD_CTL_PAD_DDR[34];            /**< SW_PAD_CTL_PAD_DRAM_ADDR00 SW PAD Control Register..SW_PAD_CTL_PAD_DRAM_RESET SW PAD Control Register, array offset: 0x204, array step: 0x4 */
       uint8_t RESERVED_1[68];
  __IO uint32_t SW_PAD_CTL_PAD[112];               /**< SW_PAD_CTL_PAD_JTAG_MOD SW PAD Control Register..SW_PAD_CTL_PAD_CSI_DATA07 SW PAD Control Register, array offset: 0x2D0, array step: 0x4 */
  __IO uint32_t SW_PAD_CTL_GRP[10];                /**< SW_PAD_CTL_GRP_ADDDS SW GRP Register..SW_PAD_CTL_GRP_DDR_TYPE SW GRP Register, array offset: 0x490, array step: 0x4 */
  __IO uint32_t SELECT_INPUT[122];                 /**< USB_OTG1_ID_SELECT_INPUT DAISY Register..USDHC2_WP_SELECT_INPUT DAISY Register, array offset: 0x4B8, array step: 0x4 */
} IOMUXC_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_Register_Masks IOMUXC Register Masks
 * @{
 */

/*! @name SW_MUX_CTL_PAD - SW_MUX_CTL_PAD_JTAG_MOD SW MUX Control Register..SW_MUX_CTL_PAD_CSI_DATA07 SW MUX Control Register */
#define IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_MASK      (0xFU)  /* Merged from fields with different position or width, of widths (3, 4), largest definition used */
#define IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_SHIFT     (0U)
#define IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_SHIFT)) & IOMUXC_SW_MUX_CTL_PAD_MUX_MODE_MASK)  /* Merged from fields with different position or width, of widths (3, 4), largest definition used */
#define IOMUXC_SW_MUX_CTL_PAD_SION_MASK          (0x10U)
#define IOMUXC_SW_MUX_CTL_PAD_SION_SHIFT         (4U)
#define IOMUXC_SW_MUX_CTL_PAD_SION(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_MUX_CTL_PAD_SION_SHIFT)) & IOMUXC_SW_MUX_CTL_PAD_SION_MASK)

/* The count of IOMUXC_SW_MUX_CTL_PAD */
#define IOMUXC_SW_MUX_CTL_PAD_COUNT              (112U)

/*! @name SW_PAD_CTL_PAD_DDR - SW_PAD_CTL_PAD_DRAM_ADDR00 SW PAD Control Register..SW_PAD_CTL_PAD_DRAM_RESET SW PAD Control Register */
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DSE_MASK       (0x38U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DSE_SHIFT      (3U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DSE(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_DSE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_DSE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_ODT_MASK       (0x700U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_ODT_SHIFT      (8U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_ODT(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_ODT_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_ODT_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PKE_MASK       (0x1000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PKE_SHIFT      (12U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PKE(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_PKE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_PKE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PUE_MASK       (0x2000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PUE_SHIFT      (13U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PUE(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_PUE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_PUE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PUS_MASK       (0xC000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PUS_SHIFT      (14U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_PUS(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_PUS_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_PUS_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_HYS_MASK       (0x10000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_HYS_SHIFT      (16U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_HYS(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_HYS_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_HYS_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_INPUT_MASK (0x20000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_INPUT_SHIFT (17U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_INPUT(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_INPUT_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_INPUT_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_SEL_MASK   (0xC0000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_SEL_SHIFT  (18U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_SEL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_SEL_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_DDR_SEL_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_MASK   (0x300000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_SHIFT  (20U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_PADN_MASK (0x3000000U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_PADN_SHIFT (24U)
#define IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_PADN(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_PADN_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DDR_DO_TRIM_PADN_MASK)

/* The count of IOMUXC_SW_PAD_CTL_PAD_DDR */
#define IOMUXC_SW_PAD_CTL_PAD_DDR_COUNT          (34U)

/*! @name SW_PAD_CTL_PAD - SW_PAD_CTL_PAD_JTAG_MOD SW PAD Control Register..SW_PAD_CTL_PAD_CSI_DATA07 SW PAD Control Register */
#define IOMUXC_SW_PAD_CTL_PAD_SRE_MASK           (0x1U)
#define IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT          (0U)
#define IOMUXC_SW_PAD_CTL_PAD_SRE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_SRE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_DSE_MASK           (0x38U)
#define IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT          (3U)
#define IOMUXC_SW_PAD_CTL_PAD_DSE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_DSE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_SPEED_MASK         (0xC0U)
#define IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT        (6U)
#define IOMUXC_SW_PAD_CTL_PAD_SPEED(x)           (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_SPEED_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_ODE_MASK           (0x800U)
#define IOMUXC_SW_PAD_CTL_PAD_ODE_SHIFT          (11U)
#define IOMUXC_SW_PAD_CTL_PAD_ODE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_ODE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_ODE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_PKE_MASK           (0x1000U)
#define IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT          (12U)
#define IOMUXC_SW_PAD_CTL_PAD_PKE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_PKE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_PUE_MASK           (0x2000U)
#define IOMUXC_SW_PAD_CTL_PAD_PUE_SHIFT          (13U)
#define IOMUXC_SW_PAD_CTL_PAD_PUE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_PUE_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_PUE_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_PUS_MASK           (0xC000U)
#define IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT          (14U)
#define IOMUXC_SW_PAD_CTL_PAD_PUS(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_PUS_MASK)
#define IOMUXC_SW_PAD_CTL_PAD_HYS_MASK           (0x10000U)
#define IOMUXC_SW_PAD_CTL_PAD_HYS_SHIFT          (16U)
#define IOMUXC_SW_PAD_CTL_PAD_HYS(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_PAD_HYS_SHIFT)) & IOMUXC_SW_PAD_CTL_PAD_HYS_MASK)

/* The count of IOMUXC_SW_PAD_CTL_PAD */
#define IOMUXC_SW_PAD_CTL_PAD_COUNT              (112U)

/*! @name SW_PAD_CTL_GRP - SW_PAD_CTL_GRP_ADDDS SW GRP Register..SW_PAD_CTL_GRP_DDR_TYPE SW GRP Register */
#define IOMUXC_SW_PAD_CTL_GRP_DSE_MASK           (0x38U)
#define IOMUXC_SW_PAD_CTL_GRP_DSE_SHIFT          (3U)
#define IOMUXC_SW_PAD_CTL_GRP_DSE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_GRP_DSE_SHIFT)) & IOMUXC_SW_PAD_CTL_GRP_DSE_MASK)
#define IOMUXC_SW_PAD_CTL_GRP_PKE_MASK           (0x1000U)
#define IOMUXC_SW_PAD_CTL_GRP_PKE_SHIFT          (12U)
#define IOMUXC_SW_PAD_CTL_GRP_PKE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_GRP_PKE_SHIFT)) & IOMUXC_SW_PAD_CTL_GRP_PKE_MASK)
#define IOMUXC_SW_PAD_CTL_GRP_PUE_MASK           (0x2000U)
#define IOMUXC_SW_PAD_CTL_GRP_PUE_SHIFT          (13U)
#define IOMUXC_SW_PAD_CTL_GRP_PUE(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_GRP_PUE_SHIFT)) & IOMUXC_SW_PAD_CTL_GRP_PUE_MASK)
#define IOMUXC_SW_PAD_CTL_GRP_HYS_MASK           (0x10000U)
#define IOMUXC_SW_PAD_CTL_GRP_HYS_SHIFT          (16U)
#define IOMUXC_SW_PAD_CTL_GRP_HYS(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_GRP_HYS_SHIFT)) & IOMUXC_SW_PAD_CTL_GRP_HYS_MASK)
#define IOMUXC_SW_PAD_CTL_GRP_DDR_INPUT_MASK     (0x20000U)
#define IOMUXC_SW_PAD_CTL_GRP_DDR_INPUT_SHIFT    (17U)
#define IOMUXC_SW_PAD_CTL_GRP_DDR_INPUT(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_GRP_DDR_INPUT_SHIFT)) & IOMUXC_SW_PAD_CTL_GRP_DDR_INPUT_MASK)
#define IOMUXC_SW_PAD_CTL_GRP_DDR_SEL_MASK       (0xC0000U)
#define IOMUXC_SW_PAD_CTL_GRP_DDR_SEL_SHIFT      (18U)
#define IOMUXC_SW_PAD_CTL_GRP_DDR_SEL(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_SW_PAD_CTL_GRP_DDR_SEL_SHIFT)) & IOMUXC_SW_PAD_CTL_GRP_DDR_SEL_MASK)

/* The count of IOMUXC_SW_PAD_CTL_GRP */
#define IOMUXC_SW_PAD_CTL_GRP_COUNT              (10U)

/*! @name SELECT_INPUT - USB_OTG1_ID_SELECT_INPUT DAISY Register..USDHC2_WP_SELECT_INPUT DAISY Register */
#define IOMUXC_SELECT_INPUT_DAISY_MASK           (0x7U)  /* Merged from fields with different position or width, of widths (1, 2, 3), largest definition used */
#define IOMUXC_SELECT_INPUT_DAISY_SHIFT          (0U)
#define IOMUXC_SELECT_INPUT_DAISY(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SELECT_INPUT_DAISY_SHIFT)) & IOMUXC_SELECT_INPUT_DAISY_MASK)  /* Merged from fields with different position or width, of widths (1, 2, 3), largest definition used */

/* The count of IOMUXC_SELECT_INPUT */
#define IOMUXC_SELECT_INPUT_COUNT                (122U)


/*!
 * @}
 */ /* end of group IOMUXC_Register_Masks */


/* IOMUXC - Peripheral instance base addresses */
/** Peripheral IOMUXC base address */
#define IOMUXC_BASE                              (0x20E0000u)
/** Peripheral IOMUXC base pointer */
#define IOMUXC                                   ((IOMUXC_Type *)IOMUXC_BASE)
/** Array initializer of IOMUXC peripheral base addresses */
#define IOMUXC_BASE_ADDRS                        { IOMUXC_BASE }
/** Array initializer of IOMUXC peripheral base pointers */
#define IOMUXC_BASE_PTRS                         { IOMUXC }

/*!
 * @}
 */ /* end of group IOMUXC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- IOMUXC_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_GPR_Peripheral_Access_Layer IOMUXC_GPR Peripheral Access Layer
 * @{
 */

/** IOMUXC_GPR - Register Layout Typedef */
typedef struct {
  __IO uint32_t GPR0;                              /**< GPR0 General Purpose Register, offset: 0x0 */
  __IO uint32_t GPR1;                              /**< GPR1 General Purpose Register, offset: 0x4 */
  __IO uint32_t GPR2;                              /**< GPR2 General Purpose Register, offset: 0x8 */
  __IO uint32_t GPR3;                              /**< GPR3 General Purpose Register, offset: 0xC */
  __IO uint32_t GPR4;                              /**< GPR4 General Purpose Register, offset: 0x10 */
  __IO uint32_t GPR5;                              /**< GPR5 General Purpose Register, offset: 0x14 */
       uint8_t RESERVED_0[12];
  __I  uint32_t GPR9;                              /**< GPR9 General Purpose Register, offset: 0x24 */
  __IO uint32_t GPR10;                             /**< GPR10 General Purpose Register, offset: 0x28 */
       uint8_t RESERVED_1[12];
  __IO uint32_t GPR14;                             /**< GPR14 General Purpose Register, offset: 0x38 */
} IOMUXC_GPR_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_GPR_Register_Masks IOMUXC_GPR Register Masks
 * @{
 */

/*! @name GPR0 - GPR0 General Purpose Register */
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL0_MASK     (0x1U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL0_SHIFT    (0U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL0(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL0_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL0_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL1_MASK     (0x2U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL1_SHIFT    (1U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL1(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL1_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL1_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL2_MASK     (0x4U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL2_SHIFT    (2U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL2(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL2_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL2_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL3_MASK     (0x8U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL3_SHIFT    (3U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL3(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL3_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL3_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL4_MASK     (0x10U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL4_SHIFT    (4U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL4(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL4_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL4_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL5_MASK     (0x20U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL5_SHIFT    (5U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL5(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL5_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL5_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL6_MASK     (0x40U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL6_SHIFT    (6U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL6(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL6_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL6_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL7_MASK     (0x80U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL7_SHIFT    (7U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL7(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL7_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL7_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL8_MASK     (0x100U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL8_SHIFT    (8U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL8(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL8_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL8_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL9_MASK     (0x200U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL9_SHIFT    (9U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL9(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL9_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL9_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL10_MASK    (0x400U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL10_SHIFT   (10U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL10(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL10_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL10_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL11_MASK    (0x800U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL11_SHIFT   (11U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL11(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL11_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL11_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL12_MASK    (0x1000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL12_SHIFT   (12U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL12(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL12_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL12_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL13_MASK    (0x2000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL13_SHIFT   (13U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL13(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL13_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL13_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL14_MASK    (0x4000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL14_SHIFT   (14U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL14(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL14_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL14_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL15_MASK    (0x8000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL15_SHIFT   (15U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL15(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL15_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL15_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL16_MASK    (0x10000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL16_SHIFT   (16U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL16(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL16_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL16_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL17_MASK    (0x20000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL17_SHIFT   (17U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL17(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL17_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL17_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL18_MASK    (0x40000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL18_SHIFT   (18U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL18(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL18_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL18_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL19_MASK    (0x80000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL19_SHIFT   (19U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL19(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL19_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL19_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL20_MASK    (0x100000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL20_SHIFT   (20U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL20(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL20_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL20_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL21_MASK    (0x200000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL21_SHIFT   (21U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL21(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL21_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL21_MASK)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL22_MASK    (0x400000U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL22_SHIFT   (22U)
#define IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL22(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL22_SHIFT)) & IOMUXC_GPR_GPR0_DMAREQ_MUX_SEL22_MASK)

/*! @name GPR1 - GPR1 General Purpose Register */
#define IOMUXC_GPR_GPR1_ACT_CS0_MASK             (0x1U)
#define IOMUXC_GPR_GPR1_ACT_CS0_SHIFT            (0U)
#define IOMUXC_GPR_GPR1_ACT_CS0(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ACT_CS0_SHIFT)) & IOMUXC_GPR_GPR1_ACT_CS0_MASK)
#define IOMUXC_GPR_GPR1_ADDRS0_MASK              (0x6U)
#define IOMUXC_GPR_GPR1_ADDRS0_SHIFT             (1U)
#define IOMUXC_GPR_GPR1_ADDRS0(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ADDRS0_SHIFT)) & IOMUXC_GPR_GPR1_ADDRS0_MASK)
#define IOMUXC_GPR_GPR1_ACT_CS1_MASK             (0x8U)
#define IOMUXC_GPR_GPR1_ACT_CS1_SHIFT            (3U)
#define IOMUXC_GPR_GPR1_ACT_CS1(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ACT_CS1_SHIFT)) & IOMUXC_GPR_GPR1_ACT_CS1_MASK)
#define IOMUXC_GPR_GPR1_ADDRS1_MASK              (0x30U)
#define IOMUXC_GPR_GPR1_ADDRS1_SHIFT             (4U)
#define IOMUXC_GPR_GPR1_ADDRS1(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ADDRS1_SHIFT)) & IOMUXC_GPR_GPR1_ADDRS1_MASK)
#define IOMUXC_GPR_GPR1_ACT_CS2_MASK             (0x40U)
#define IOMUXC_GPR_GPR1_ACT_CS2_SHIFT            (6U)
#define IOMUXC_GPR_GPR1_ACT_CS2(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ACT_CS2_SHIFT)) & IOMUXC_GPR_GPR1_ACT_CS2_MASK)
#define IOMUXC_GPR_GPR1_ADDRS2_MASK              (0x180U)
#define IOMUXC_GPR_GPR1_ADDRS2_SHIFT             (7U)
#define IOMUXC_GPR_GPR1_ADDRS2(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ADDRS2_SHIFT)) & IOMUXC_GPR_GPR1_ADDRS2_MASK)
#define IOMUXC_GPR_GPR1_ACT_CS3_MASK             (0x200U)
#define IOMUXC_GPR_GPR1_ACT_CS3_SHIFT            (9U)
#define IOMUXC_GPR_GPR1_ACT_CS3(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ACT_CS3_SHIFT)) & IOMUXC_GPR_GPR1_ACT_CS3_MASK)
#define IOMUXC_GPR_GPR1_ADDRS3_MASK              (0xC00U)
#define IOMUXC_GPR_GPR1_ADDRS3_SHIFT             (10U)
#define IOMUXC_GPR_GPR1_ADDRS3(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ADDRS3_SHIFT)) & IOMUXC_GPR_GPR1_ADDRS3_MASK)
#define IOMUXC_GPR_GPR1_GINT_MASK                (0x1000U)
#define IOMUXC_GPR_GPR1_GINT_SHIFT               (12U)
#define IOMUXC_GPR_GPR1_GINT(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_GINT_SHIFT)) & IOMUXC_GPR_GPR1_GINT_MASK)
#define IOMUXC_GPR_GPR1_ENET1_CLK_SEL_MASK       (0x2000U)
#define IOMUXC_GPR_GPR1_ENET1_CLK_SEL_SHIFT      (13U)
#define IOMUXC_GPR_GPR1_ENET1_CLK_SEL(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ENET1_CLK_SEL_SHIFT)) & IOMUXC_GPR_GPR1_ENET1_CLK_SEL_MASK)
#define IOMUXC_GPR_GPR1_ENET2_CLK_SEL_MASK       (0x4000U)
#define IOMUXC_GPR_GPR1_ENET2_CLK_SEL_SHIFT      (14U)
#define IOMUXC_GPR_GPR1_ENET2_CLK_SEL(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ENET2_CLK_SEL_SHIFT)) & IOMUXC_GPR_GPR1_ENET2_CLK_SEL_MASK)
#define IOMUXC_GPR_GPR1_USB_EXP_MODE_MASK        (0x8000U)
#define IOMUXC_GPR_GPR1_USB_EXP_MODE_SHIFT       (15U)
#define IOMUXC_GPR_GPR1_USB_EXP_MODE(x)          (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_USB_EXP_MODE_SHIFT)) & IOMUXC_GPR_GPR1_USB_EXP_MODE_MASK)
#define IOMUXC_GPR_GPR1_ADD_DS_MASK              (0x10000U)
#define IOMUXC_GPR_GPR1_ADD_DS_SHIFT             (16U)
#define IOMUXC_GPR_GPR1_ADD_DS(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ADD_DS_SHIFT)) & IOMUXC_GPR_GPR1_ADD_DS_MASK)
#define IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR_MASK    (0x20000U)
#define IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR_SHIFT   (17U)
#define IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR_SHIFT)) & IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR_MASK)
#define IOMUXC_GPR_GPR1_ENET2_TX_CLK_DIR_MASK    (0x40000U)
#define IOMUXC_GPR_GPR1_ENET2_TX_CLK_DIR_SHIFT   (18U)
#define IOMUXC_GPR_GPR1_ENET2_TX_CLK_DIR(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ENET2_TX_CLK_DIR_SHIFT)) & IOMUXC_GPR_GPR1_ENET2_TX_CLK_DIR_MASK)
#define IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_MASK       (0x80000U)
#define IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_SHIFT      (19U)
#define IOMUXC_GPR_GPR1_SAI1_MCLK_DIR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_SHIFT)) & IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_MASK)
#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_MASK       (0x100000U)
#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_SHIFT      (20U)
#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_SHIFT)) & IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_MASK)
#define IOMUXC_GPR_GPR1_SAI3_MCLK_DIR_MASK       (0x200000U)
#define IOMUXC_GPR_GPR1_SAI3_MCLK_DIR_SHIFT      (21U)
#define IOMUXC_GPR_GPR1_SAI3_MCLK_DIR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_SAI3_MCLK_DIR_SHIFT)) & IOMUXC_GPR_GPR1_SAI3_MCLK_DIR_MASK)
#define IOMUXC_GPR_GPR1_EXC_MON_MASK             (0x400000U)
#define IOMUXC_GPR_GPR1_EXC_MON_SHIFT            (22U)
#define IOMUXC_GPR_GPR1_EXC_MON(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_EXC_MON_SHIFT)) & IOMUXC_GPR_GPR1_EXC_MON_MASK)
#define IOMUXC_GPR_GPR1_TZASC1_BOOT_LOCK_MASK    (0x800000U)
#define IOMUXC_GPR_GPR1_TZASC1_BOOT_LOCK_SHIFT   (23U)
#define IOMUXC_GPR_GPR1_TZASC1_BOOT_LOCK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_TZASC1_BOOT_LOCK_SHIFT)) & IOMUXC_GPR_GPR1_TZASC1_BOOT_LOCK_MASK)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_APB_DBG_EN_MASK (0x1000000U)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_APB_DBG_EN_SHIFT (24U)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_APB_DBG_EN(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ARMA7_CLK_APB_DBG_EN_SHIFT)) & IOMUXC_GPR_GPR1_ARMA7_CLK_APB_DBG_EN_MASK)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_ATB_EN_MASK    (0x2000000U)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_ATB_EN_SHIFT   (25U)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_ATB_EN(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ARMA7_CLK_ATB_EN_SHIFT)) & IOMUXC_GPR_GPR1_ARMA7_CLK_ATB_EN_MASK)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_AHB_EN_MASK    (0x4000000U)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_AHB_EN_SHIFT   (26U)
#define IOMUXC_GPR_GPR1_ARMA7_CLK_AHB_EN(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_ARMA7_CLK_AHB_EN_SHIFT)) & IOMUXC_GPR_GPR1_ARMA7_CLK_AHB_EN_MASK)

/*! @name GPR2 - GPR2 General Purpose Register */
#define IOMUXC_GPR_GPR2_PXP_MEM_EN_POWERSAVING_MASK (0x1U)
#define IOMUXC_GPR_GPR2_PXP_MEM_EN_POWERSAVING_SHIFT (0U)
#define IOMUXC_GPR_GPR2_PXP_MEM_EN_POWERSAVING(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_PXP_MEM_EN_POWERSAVING_SHIFT)) & IOMUXC_GPR_GPR2_PXP_MEM_EN_POWERSAVING_MASK)
#define IOMUXC_GPR_GPR2_PXP_MEM_SHUTDOWN_MASK    (0x2U)
#define IOMUXC_GPR_GPR2_PXP_MEM_SHUTDOWN_SHIFT   (1U)
#define IOMUXC_GPR_GPR2_PXP_MEM_SHUTDOWN(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_PXP_MEM_SHUTDOWN_SHIFT)) & IOMUXC_GPR_GPR2_PXP_MEM_SHUTDOWN_MASK)
#define IOMUXC_GPR_GPR2_PXP_MEM_DEEPSLEEP_MASK   (0x4U)
#define IOMUXC_GPR_GPR2_PXP_MEM_DEEPSLEEP_SHIFT  (2U)
#define IOMUXC_GPR_GPR2_PXP_MEM_DEEPSLEEP(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_PXP_MEM_DEEPSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_PXP_MEM_DEEPSLEEP_MASK)
#define IOMUXC_GPR_GPR2_PXP_MEM_LIGHTSLEEP_MASK  (0x8U)
#define IOMUXC_GPR_GPR2_PXP_MEM_LIGHTSLEEP_SHIFT (3U)
#define IOMUXC_GPR_GPR2_PXP_MEM_LIGHTSLEEP(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_PXP_MEM_LIGHTSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_PXP_MEM_LIGHTSLEEP_MASK)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_EN_POWERSAVING_MASK (0x10U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_EN_POWERSAVING_SHIFT (4U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_EN_POWERSAVING(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF1_MEM_EN_POWERSAVING_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF1_MEM_EN_POWERSAVING_MASK)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_SHUTDOWN_MASK (0x20U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_SHUTDOWN_SHIFT (5U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_SHUTDOWN(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF1_MEM_SHUTDOWN_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF1_MEM_SHUTDOWN_MASK)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_DEEPSLEEP_MASK (0x40U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_DEEPSLEEP_SHIFT (6U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_DEEPSLEEP(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF1_MEM_DEEPSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF1_MEM_DEEPSLEEP_MASK)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_LIGHTSLEEP_MASK (0x80U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_LIGHTSLEEP_SHIFT (7U)
#define IOMUXC_GPR_GPR2_LCDIF1_MEM_LIGHTSLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF1_MEM_LIGHTSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF1_MEM_LIGHTSLEEP_MASK)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_EN_POWERSAVING_MASK (0x100U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_EN_POWERSAVING_SHIFT (8U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_EN_POWERSAVING(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF2_MEM_EN_POWERSAVING_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF2_MEM_EN_POWERSAVING_MASK)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_SHUTDOWN_MASK (0x200U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_SHUTDOWN_SHIFT (9U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_SHUTDOWN(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF2_MEM_SHUTDOWN_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF2_MEM_SHUTDOWN_MASK)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_DEEPSLEEP_MASK (0x400U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_DEEPSLEEP_SHIFT (10U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_DEEPSLEEP(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF2_MEM_DEEPSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF2_MEM_DEEPSLEEP_MASK)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_LIGHTSLEEP_MASK (0x800U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_LIGHTSLEEP_SHIFT (11U)
#define IOMUXC_GPR_GPR2_LCDIF2_MEM_LIGHTSLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_LCDIF2_MEM_LIGHTSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_LCDIF2_MEM_LIGHTSLEEP_MASK)
#define IOMUXC_GPR_GPR2_L2_MEM_EN_POWERSAVING_MASK (0x1000U)
#define IOMUXC_GPR_GPR2_L2_MEM_EN_POWERSAVING_SHIFT (12U)
#define IOMUXC_GPR_GPR2_L2_MEM_EN_POWERSAVING(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_L2_MEM_EN_POWERSAVING_SHIFT)) & IOMUXC_GPR_GPR2_L2_MEM_EN_POWERSAVING_MASK)
#define IOMUXC_GPR_GPR2_L2_MEM_SHUTDOWN_MASK     (0x2000U)
#define IOMUXC_GPR_GPR2_L2_MEM_SHUTDOWN_SHIFT    (13U)
#define IOMUXC_GPR_GPR2_L2_MEM_SHUTDOWN(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_L2_MEM_SHUTDOWN_SHIFT)) & IOMUXC_GPR_GPR2_L2_MEM_SHUTDOWN_MASK)
#define IOMUXC_GPR_GPR2_L2_MEM_DEEPSLEEP_MASK    (0x4000U)
#define IOMUXC_GPR_GPR2_L2_MEM_DEEPSLEEP_SHIFT   (14U)
#define IOMUXC_GPR_GPR2_L2_MEM_DEEPSLEEP(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_L2_MEM_DEEPSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_L2_MEM_DEEPSLEEP_MASK)
#define IOMUXC_GPR_GPR2_L2_MEM_LIGHTSLEEP_MASK   (0x8000U)
#define IOMUXC_GPR_GPR2_L2_MEM_LIGHTSLEEP_SHIFT  (15U)
#define IOMUXC_GPR_GPR2_L2_MEM_LIGHTSLEEP(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_L2_MEM_LIGHTSLEEP_SHIFT)) & IOMUXC_GPR_GPR2_L2_MEM_LIGHTSLEEP_MASK)
#define IOMUXC_GPR_GPR2_MQS_CLK_DIV_MASK         (0xFF0000U)
#define IOMUXC_GPR_GPR2_MQS_CLK_DIV_SHIFT        (16U)
#define IOMUXC_GPR_GPR2_MQS_CLK_DIV(x)           (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_MQS_CLK_DIV_SHIFT)) & IOMUXC_GPR_GPR2_MQS_CLK_DIV_MASK)
#define IOMUXC_GPR_GPR2_MQS_SW_RST_MASK          (0x1000000U)
#define IOMUXC_GPR_GPR2_MQS_SW_RST_SHIFT         (24U)
#define IOMUXC_GPR_GPR2_MQS_SW_RST(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_MQS_SW_RST_SHIFT)) & IOMUXC_GPR_GPR2_MQS_SW_RST_MASK)
#define IOMUXC_GPR_GPR2_MQS_EN_MASK              (0x2000000U)
#define IOMUXC_GPR_GPR2_MQS_EN_SHIFT             (25U)
#define IOMUXC_GPR_GPR2_MQS_EN(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_MQS_EN_SHIFT)) & IOMUXC_GPR_GPR2_MQS_EN_MASK)
#define IOMUXC_GPR_GPR2_MQS_OVERSAMPLE_MASK      (0x4000000U)
#define IOMUXC_GPR_GPR2_MQS_OVERSAMPLE_SHIFT     (26U)
#define IOMUXC_GPR_GPR2_MQS_OVERSAMPLE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_MQS_OVERSAMPLE_SHIFT)) & IOMUXC_GPR_GPR2_MQS_OVERSAMPLE_MASK)
#define IOMUXC_GPR_GPR2_DRAM_RESET_BYPASS_MASK   (0x8000000U)
#define IOMUXC_GPR_GPR2_DRAM_RESET_BYPASS_SHIFT  (27U)
#define IOMUXC_GPR_GPR2_DRAM_RESET_BYPASS(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_DRAM_RESET_BYPASS_SHIFT)) & IOMUXC_GPR_GPR2_DRAM_RESET_BYPASS_MASK)
#define IOMUXC_GPR_GPR2_DRAM_RESET_MASK          (0x10000000U)
#define IOMUXC_GPR_GPR2_DRAM_RESET_SHIFT         (28U)
#define IOMUXC_GPR_GPR2_DRAM_RESET(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_DRAM_RESET_SHIFT)) & IOMUXC_GPR_GPR2_DRAM_RESET_MASK)
#define IOMUXC_GPR_GPR2_DRAM_CKE0_MASK           (0x20000000U)
#define IOMUXC_GPR_GPR2_DRAM_CKE0_SHIFT          (29U)
#define IOMUXC_GPR_GPR2_DRAM_CKE0(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_DRAM_CKE0_SHIFT)) & IOMUXC_GPR_GPR2_DRAM_CKE0_MASK)
#define IOMUXC_GPR_GPR2_DRAM_CKE1_MASK           (0x40000000U)
#define IOMUXC_GPR_GPR2_DRAM_CKE1_SHIFT          (30U)
#define IOMUXC_GPR_GPR2_DRAM_CKE1(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_DRAM_CKE1_SHIFT)) & IOMUXC_GPR_GPR2_DRAM_CKE1_MASK)
#define IOMUXC_GPR_GPR2_DRAM_CKE_BYPASS_MASK     (0x80000000U)
#define IOMUXC_GPR_GPR2_DRAM_CKE_BYPASS_SHIFT    (31U)
#define IOMUXC_GPR_GPR2_DRAM_CKE_BYPASS(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_DRAM_CKE_BYPASS_SHIFT)) & IOMUXC_GPR_GPR2_DRAM_CKE_BYPASS_MASK)

/*! @name GPR3 - GPR3 General Purpose Register */
#define IOMUXC_GPR_GPR3_OCRAM_CTL_MASK           (0xFU)
#define IOMUXC_GPR_GPR3_OCRAM_CTL_SHIFT          (0U)
#define IOMUXC_GPR_GPR3_OCRAM_CTL(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_OCRAM_CTL_SHIFT)) & IOMUXC_GPR_GPR3_OCRAM_CTL_MASK)
#define IOMUXC_GPR_GPR3_CORE_DBG_ACK_EN_MASK     (0x2000U)
#define IOMUXC_GPR_GPR3_CORE_DBG_ACK_EN_SHIFT    (13U)
#define IOMUXC_GPR_GPR3_CORE_DBG_ACK_EN(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_CORE_DBG_ACK_EN_SHIFT)) & IOMUXC_GPR_GPR3_CORE_DBG_ACK_EN_MASK)
#define IOMUXC_GPR_GPR3_OCRAM_STATUS_MASK        (0xF0000U)
#define IOMUXC_GPR_GPR3_OCRAM_STATUS_SHIFT       (16U)
#define IOMUXC_GPR_GPR3_OCRAM_STATUS(x)          (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_OCRAM_STATUS_SHIFT)) & IOMUXC_GPR_GPR3_OCRAM_STATUS_MASK)

/*! @name GPR4 - GPR4 General Purpose Register */
#define IOMUXC_GPR_GPR4_SDMA_STOP_REQ_MASK       (0x1U)
#define IOMUXC_GPR_GPR4_SDMA_STOP_REQ_SHIFT      (0U)
#define IOMUXC_GPR_GPR4_SDMA_STOP_REQ(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SDMA_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_SDMA_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_CAN1_STOP_REQ_MASK       (0x2U)
#define IOMUXC_GPR_GPR4_CAN1_STOP_REQ_SHIFT      (1U)
#define IOMUXC_GPR_GPR4_CAN1_STOP_REQ(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_CAN1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_CAN1_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_CAN2_STOP_REQ_MASK       (0x4U)
#define IOMUXC_GPR_GPR4_CAN2_STOP_REQ_SHIFT      (2U)
#define IOMUXC_GPR_GPR4_CAN2_STOP_REQ(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_CAN2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_CAN2_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_ENET1_STOP_REQ_MASK      (0x8U)
#define IOMUXC_GPR_GPR4_ENET1_STOP_REQ_SHIFT     (3U)
#define IOMUXC_GPR_GPR4_ENET1_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_ENET1_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_ENET2_STOP_REQ_MASK      (0x10U)
#define IOMUXC_GPR_GPR4_ENET2_STOP_REQ_SHIFT     (4U)
#define IOMUXC_GPR_GPR4_ENET2_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_ENET2_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_SAI1_STOP_REQ_MASK       (0x20U)
#define IOMUXC_GPR_GPR4_SAI1_STOP_REQ_SHIFT      (5U)
#define IOMUXC_GPR_GPR4_SAI1_STOP_REQ(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SAI1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_SAI1_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_SAI2_STOP_REQ_MASK       (0x40U)
#define IOMUXC_GPR_GPR4_SAI2_STOP_REQ_SHIFT      (6U)
#define IOMUXC_GPR_GPR4_SAI2_STOP_REQ(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SAI2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_SAI2_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_SAI3_STOP_REQ_MASK       (0x80U)
#define IOMUXC_GPR_GPR4_SAI3_STOP_REQ_SHIFT      (7U)
#define IOMUXC_GPR_GPR4_SAI3_STOP_REQ(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SAI3_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR4_SAI3_STOP_REQ_MASK)
#define IOMUXC_GPR_GPR4_ENET_IPG_CLK_S_EN_MASK   (0x100U)
#define IOMUXC_GPR_GPR4_ENET_IPG_CLK_S_EN_SHIFT  (8U)
#define IOMUXC_GPR_GPR4_ENET_IPG_CLK_S_EN(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET_IPG_CLK_S_EN_SHIFT)) & IOMUXC_GPR_GPR4_ENET_IPG_CLK_S_EN_MASK)
#define IOMUXC_GPR_GPR4_SDMA_STOP_ACK_MASK       (0x10000U)
#define IOMUXC_GPR_GPR4_SDMA_STOP_ACK_SHIFT      (16U)
#define IOMUXC_GPR_GPR4_SDMA_STOP_ACK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SDMA_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_SDMA_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_CAN1_STOP_ACK_MASK       (0x20000U)
#define IOMUXC_GPR_GPR4_CAN1_STOP_ACK_SHIFT      (17U)
#define IOMUXC_GPR_GPR4_CAN1_STOP_ACK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_CAN1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_CAN1_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_CAN2_STOP_ACK_MASK       (0x40000U)
#define IOMUXC_GPR_GPR4_CAN2_STOP_ACK_SHIFT      (18U)
#define IOMUXC_GPR_GPR4_CAN2_STOP_ACK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_CAN2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_CAN2_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_ENET1_STOP_ACK_MASK      (0x80000U)
#define IOMUXC_GPR_GPR4_ENET1_STOP_ACK_SHIFT     (19U)
#define IOMUXC_GPR_GPR4_ENET1_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_ENET1_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_ENET2_STOP_ACK_MASK      (0x100000U)
#define IOMUXC_GPR_GPR4_ENET2_STOP_ACK_SHIFT     (20U)
#define IOMUXC_GPR_GPR4_ENET2_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_ENET2_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_SAI1_STOP_ACK_MASK       (0x200000U)
#define IOMUXC_GPR_GPR4_SAI1_STOP_ACK_SHIFT      (21U)
#define IOMUXC_GPR_GPR4_SAI1_STOP_ACK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SAI1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_SAI1_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_SAI2_STOP_ACK_MASK       (0x400000U)
#define IOMUXC_GPR_GPR4_SAI2_STOP_ACK_SHIFT      (22U)
#define IOMUXC_GPR_GPR4_SAI2_STOP_ACK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SAI2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_SAI2_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_SAI3_STOP_ACK_MASK       (0x800000U)
#define IOMUXC_GPR_GPR4_SAI3_STOP_ACK_SHIFT      (23U)
#define IOMUXC_GPR_GPR4_SAI3_STOP_ACK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_SAI3_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR4_SAI3_STOP_ACK_MASK)
#define IOMUXC_GPR_GPR4_ARM_WFI_MASK             (0x40000000U)
#define IOMUXC_GPR_GPR4_ARM_WFI_SHIFT            (30U)
#define IOMUXC_GPR_GPR4_ARM_WFI(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ARM_WFI_SHIFT)) & IOMUXC_GPR_GPR4_ARM_WFI_MASK)
#define IOMUXC_GPR_GPR4_ARM_WFE_MASK             (0x80000000U)
#define IOMUXC_GPR_GPR4_ARM_WFE_SHIFT            (31U)
#define IOMUXC_GPR_GPR4_ARM_WFE(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ARM_WFE_SHIFT)) & IOMUXC_GPR_GPR4_ARM_WFE_MASK)

/*! @name GPR5 - GPR5 General Purpose Register */
#define IOMUXC_GPR_GPR5_WDOG1_MASK_MASK          (0x40U)
#define IOMUXC_GPR_GPR5_WDOG1_MASK_SHIFT         (6U)
#define IOMUXC_GPR_GPR5_WDOG1_MASK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_WDOG1_MASK_SHIFT)) & IOMUXC_GPR_GPR5_WDOG1_MASK_MASK)
#define IOMUXC_GPR_GPR5_WDOG2_MASK_MASK          (0x80U)
#define IOMUXC_GPR_GPR5_WDOG2_MASK_SHIFT         (7U)
#define IOMUXC_GPR_GPR5_WDOG2_MASK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_WDOG2_MASK_SHIFT)) & IOMUXC_GPR_GPR5_WDOG2_MASK_MASK)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_CSI_MASK (0x300U)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_CSI_SHIFT (8U)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_CSI(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_CSI_SHIFT)) & IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_CSI_MASK)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_LCDIF_MASK (0x3000U)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_LCDIF_SHIFT (12U)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_LCDIF(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_LCDIF_SHIFT)) & IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_LCDIF_MASK)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_PXP_MASK (0x30000U)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_PXP_SHIFT (16U)
#define IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_PXP(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_PXP_SHIFT)) & IOMUXC_GPR_GPR5_LCDIF_HANDSHAKE_PXP_MASK)
#define IOMUXC_GPR_GPR5_WDOG3_MASK_MASK          (0x100000U)
#define IOMUXC_GPR_GPR5_WDOG3_MASK_SHIFT         (20U)
#define IOMUXC_GPR_GPR5_WDOG3_MASK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_WDOG3_MASK_SHIFT)) & IOMUXC_GPR_GPR5_WDOG3_MASK_MASK)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN1_SEL_MASK     (0x800000U)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN1_SEL_SHIFT    (23U)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN1_SEL(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_GPT2_CAPIN1_SEL_SHIFT)) & IOMUXC_GPR_GPR5_GPT2_CAPIN1_SEL_MASK)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN2_SEL_MASK     (0x1000000U)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN2_SEL_SHIFT    (24U)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN2_SEL(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_GPT2_CAPIN2_SEL_SHIFT)) & IOMUXC_GPR_GPR5_GPT2_CAPIN2_SEL_MASK)
#define IOMUXC_GPR_GPR5_ENET1_EVENT3IN_SEL_MASK  (0x2000000U)
#define IOMUXC_GPR_GPR5_ENET1_EVENT3IN_SEL_SHIFT (25U)
#define IOMUXC_GPR_GPR5_ENET1_EVENT3IN_SEL(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_ENET1_EVENT3IN_SEL_SHIFT)) & IOMUXC_GPR_GPR5_ENET1_EVENT3IN_SEL_MASK)
#define IOMUXC_GPR_GPR5_ENET2_EVENT3IN_SEL_MASK  (0x4000000U)
#define IOMUXC_GPR_GPR5_ENET2_EVENT3IN_SEL_SHIFT (26U)
#define IOMUXC_GPR_GPR5_ENET2_EVENT3IN_SEL(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_ENET2_EVENT3IN_SEL_SHIFT)) & IOMUXC_GPR_GPR5_ENET2_EVENT3IN_SEL_MASK)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT1_MASK    (0x10000000U)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT1_SHIFT   (28U)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT1(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT1_SHIFT)) & IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT1_MASK)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT2_MASK    (0x20000000U)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT2_SHIFT   (29U)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT2(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT2_SHIFT)) & IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT2_MASK)
#define IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT1_MASK    (0x40000000U)
#define IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT1_SHIFT   (30U)
#define IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT1(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT1_SHIFT)) & IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT1_MASK)
#define IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT2_MASK    (0x80000000U)
#define IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT2_SHIFT   (31U)
#define IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT2(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT2_SHIFT)) & IOMUXC_GPR_GPR5_REF_1M_CLK_EPIT2_MASK)

/*! @name GPR9 - GPR9 General Purpose Register */
#define IOMUXC_GPR_GPR9_TZASC1_BYP_MASK          (0x1U)
#define IOMUXC_GPR_GPR9_TZASC1_BYP_SHIFT         (0U)
#define IOMUXC_GPR_GPR9_TZASC1_BYP(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR9_TZASC1_BYP_SHIFT)) & IOMUXC_GPR_GPR9_TZASC1_BYP_MASK)

/*! @name GPR10 - GPR10 General Purpose Register */
#define IOMUXC_GPR_GPR10_DBG_EN_MASK             (0x1U)
#define IOMUXC_GPR_GPR10_DBG_EN_SHIFT            (0U)
#define IOMUXC_GPR_GPR10_DBG_EN(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR10_DBG_EN_SHIFT)) & IOMUXC_GPR_GPR10_DBG_EN_MASK)
#define IOMUXC_GPR_GPR10_DBG_CLK_EN_MASK         (0x2U)
#define IOMUXC_GPR_GPR10_DBG_CLK_EN_SHIFT        (1U)
#define IOMUXC_GPR_GPR10_DBG_CLK_EN(x)           (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR10_DBG_CLK_EN_SHIFT)) & IOMUXC_GPR_GPR10_DBG_CLK_EN_MASK)
#define IOMUXC_GPR_GPR10_SEC_ERR_RESP_MASK       (0x4U)
#define IOMUXC_GPR_GPR10_SEC_ERR_RESP_SHIFT      (2U)
#define IOMUXC_GPR_GPR10_SEC_ERR_RESP(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR10_SEC_ERR_RESP_SHIFT)) & IOMUXC_GPR_GPR10_SEC_ERR_RESP_MASK)
#define IOMUXC_GPR_GPR10_OCRAM_TZ_EN_MASK        (0x400U)
#define IOMUXC_GPR_GPR10_OCRAM_TZ_EN_SHIFT       (10U)
#define IOMUXC_GPR_GPR10_OCRAM_TZ_EN(x)          (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR10_OCRAM_TZ_EN_SHIFT)) & IOMUXC_GPR_GPR10_OCRAM_TZ_EN_MASK)
#define IOMUXC_GPR_GPR10_OCRAM_TZ_ADDR_MASK      (0xF800U)
#define IOMUXC_GPR_GPR10_OCRAM_TZ_ADDR_SHIFT     (11U)
#define IOMUXC_GPR_GPR10_OCRAM_TZ_ADDR(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR10_OCRAM_TZ_ADDR_SHIFT)) & IOMUXC_GPR_GPR10_OCRAM_TZ_ADDR_MASK)

/*! @name GPR14 - GPR14 General Purpose Register */
#define IOMUXC_GPR_GPR14_GPR_MASK                (0xFFFFFFFCU)
#define IOMUXC_GPR_GPR14_GPR_SHIFT               (2U)
#define IOMUXC_GPR_GPR14_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_GPR_SHIFT)) & IOMUXC_GPR_GPR14_GPR_MASK)


/*!
 * @}
 */ /* end of group IOMUXC_GPR_Register_Masks */


/* IOMUXC_GPR - Peripheral instance base addresses */
/** Peripheral IOMUXC_GPR base address */
#define IOMUXC_GPR_BASE                          (0x20E4000u)
/** Peripheral IOMUXC_GPR base pointer */
#define IOMUXC_GPR                               ((IOMUXC_GPR_Type *)IOMUXC_GPR_BASE)
/** Array initializer of IOMUXC_GPR peripheral base addresses */
#define IOMUXC_GPR_BASE_ADDRS                    { IOMUXC_GPR_BASE }
/** Array initializer of IOMUXC_GPR peripheral base pointers */
#define IOMUXC_GPR_BASE_PTRS                     { IOMUXC_GPR }

/*!
 * @}
 */ /* end of group IOMUXC_GPR_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- IOMUXC_SNVS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_SNVS_Peripheral_Access_Layer IOMUXC_SNVS Peripheral Access Layer
 * @{
 */

/** IOMUXC_SNVS - Register Layout Typedef */
typedef struct {
  __IO uint32_t SW_MUX_CTL_PAD[12];                /**< SW_MUX_CTL_PAD_BOOT_MODE0 SW MUX Control Register..SW_MUX_CTL_PAD_SNVS_TAMPER9 SW MUX Control Register, array offset: 0x0, array step: 0x4 */
  __IO uint32_t SW_PAD_CTL_PAD[17];                /**< SW_PAD_CTL_PAD_TEST_MODE SW PAD Control Register..SW_PAD_CTL_PAD_SNVS_TAMPER9 SW PAD Control Register, array offset: 0x30, array step: 0x4 */
} IOMUXC_SNVS_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC_SNVS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_SNVS_Register_Masks IOMUXC_SNVS Register Masks
 * @{
 */

/*! @name SW_MUX_CTL_PAD - SW_MUX_CTL_PAD_BOOT_MODE0 SW MUX Control Register..SW_MUX_CTL_PAD_SNVS_TAMPER9 SW MUX Control Register */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_MUX_MODE_MASK (0xFU)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_MUX_MODE_SHIFT (0U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_MUX_MODE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_MUX_MODE_MASK)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_SION_MASK     (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_SION_SHIFT    (4U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_SION(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_SION_MASK)

/* The count of IOMUXC_SNVS_SW_MUX_CTL_PAD */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_COUNT         (12U)

/*! @name SW_PAD_CTL_PAD - SW_PAD_CTL_PAD_TEST_MODE SW PAD Control Register..SW_PAD_CTL_PAD_SNVS_TAMPER9 SW PAD Control Register */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SRE_MASK      (0x1U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SRE_SHIFT     (0U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SRE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_SRE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_SRE_MASK)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_DSE_MASK      (0x38U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_DSE_SHIFT     (3U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_DSE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_DSE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_DSE_MASK)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SPEED_MASK    (0xC0U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SPEED_SHIFT   (6U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SPEED(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_SPEED_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_SPEED_MASK)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ODE_MASK      (0x800U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ODE_SHIFT     (11U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ODE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_ODE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_ODE_MASK)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PKE_MASK      (0x1000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PKE_SHIFT     (12U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PKE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PKE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PKE_MASK)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PUE_MASK      (0x2000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PUE_SHIFT     (13U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PUE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PUE_MASK)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PUS_MASK      (0xC000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PUS_SHIFT     (14U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PUS(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PUS_MASK)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_HYS_MASK      (0x10000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_HYS_SHIFT     (16U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_HYS(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_HYS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_HYS_MASK)

/* The count of IOMUXC_SNVS_SW_PAD_CTL_PAD */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_COUNT         (17U)


/*!
 * @}
 */ /* end of group IOMUXC_SNVS_Register_Masks */


/* IOMUXC_SNVS - Peripheral instance base addresses */
/** Peripheral IOMUXC_SNVS base address */
#define IOMUXC_SNVS_BASE                         (0x2290000u)
/** Peripheral IOMUXC_SNVS base pointer */
#define IOMUXC_SNVS                              ((IOMUXC_SNVS_Type *)IOMUXC_SNVS_BASE)
/** Array initializer of IOMUXC_SNVS peripheral base addresses */
#define IOMUXC_SNVS_BASE_ADDRS                   { IOMUXC_SNVS_BASE }
/** Array initializer of IOMUXC_SNVS peripheral base pointers */
#define IOMUXC_SNVS_BASE_PTRS                    { IOMUXC_SNVS }

/*!
 * @}
 */ /* end of group IOMUXC_SNVS_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- ENET Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_Peripheral_Access_Layer ENET Peripheral Access Layer
 * @{
 */

/** ENET - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t EIR;                               /**< Interrupt Event Register, offset: 0x4 */
  __IO uint32_t EIMR;                              /**< Interrupt Mask Register, offset: 0x8 */
       uint8_t RESERVED_1[4];
  __IO uint32_t RDAR;                              /**< Receive Descriptor Active Register, offset: 0x10 */
  __IO uint32_t TDAR;                              /**< Transmit Descriptor Active Register, offset: 0x14 */
       uint8_t RESERVED_2[12];
  __IO uint32_t ECR;                               /**< Ethernet Control Register, offset: 0x24 */
       uint8_t RESERVED_3[24];
  __IO uint32_t MMFR;                              /**< MII Management Frame Register, offset: 0x40 */
  __IO uint32_t MSCR;                              /**< MII Speed Control Register, offset: 0x44 */
       uint8_t RESERVED_4[28];
  __IO uint32_t MIBC;                              /**< MIB Control Register, offset: 0x64 */
       uint8_t RESERVED_5[28];
  __IO uint32_t RCR;                               /**< Receive Control Register, offset: 0x84 */
       uint8_t RESERVED_6[60];
  __IO uint32_t TCR;                               /**< Transmit Control Register, offset: 0xC4 */
       uint8_t RESERVED_7[28];
  __IO uint32_t PALR;                              /**< Physical Address Lower Register, offset: 0xE4 */
  __IO uint32_t PAUR;                              /**< Physical Address Upper Register, offset: 0xE8 */
  __IO uint32_t OPD;                               /**< Opcode/Pause Duration Register, offset: 0xEC */
  __IO uint32_t TXIC;                              /**< Transmit Interrupt Coalescing Register, offset: 0xF0 */
       uint8_t RESERVED_8[12];
  __IO uint32_t RXIC;                              /**< Receive Interrupt Coalescing Register, offset: 0x100 */
       uint8_t RESERVED_9[20];
  __IO uint32_t IAUR;                              /**< Descriptor Individual Upper Address Register, offset: 0x118 */
  __IO uint32_t IALR;                              /**< Descriptor Individual Lower Address Register, offset: 0x11C */
  __IO uint32_t GAUR;                              /**< Descriptor Group Upper Address Register, offset: 0x120 */
  __IO uint32_t GALR;                              /**< Descriptor Group Lower Address Register, offset: 0x124 */
       uint8_t RESERVED_10[28];
  __IO uint32_t TFWR;                              /**< Transmit FIFO Watermark Register, offset: 0x144 */
       uint8_t RESERVED_11[56];
  __IO uint32_t RDSR;                              /**< Receive Descriptor Ring Start Register, offset: 0x180 */
  __IO uint32_t TDSR;                              /**< Transmit Buffer Descriptor Ring Start Register, offset: 0x184 */
  __IO uint32_t MRBR;                              /**< Maximum Receive Buffer Size Register, offset: 0x188 */
       uint8_t RESERVED_12[4];
  __IO uint32_t RSFL;                              /**< Receive FIFO Section Full Threshold, offset: 0x190 */
  __IO uint32_t RSEM;                              /**< Receive FIFO Section Empty Threshold, offset: 0x194 */
  __IO uint32_t RAEM;                              /**< Receive FIFO Almost Empty Threshold, offset: 0x198 */
  __IO uint32_t RAFL;                              /**< Receive FIFO Almost Full Threshold, offset: 0x19C */
  __IO uint32_t TSEM;                              /**< Transmit FIFO Section Empty Threshold, offset: 0x1A0 */
  __IO uint32_t TAEM;                              /**< Transmit FIFO Almost Empty Threshold, offset: 0x1A4 */
  __IO uint32_t TAFL;                              /**< Transmit FIFO Almost Full Threshold, offset: 0x1A8 */
  __IO uint32_t TIPG;                              /**< Transmit Inter-Packet Gap, offset: 0x1AC */
  __IO uint32_t FTRL;                              /**< Frame Truncation Length, offset: 0x1B0 */
       uint8_t RESERVED_13[12];
  __IO uint32_t TACC;                              /**< Transmit Accelerator Function Configuration, offset: 0x1C0 */
  __IO uint32_t RACC;                              /**< Receive Accelerator Function Configuration, offset: 0x1C4 */
       uint8_t RESERVED_14[56];
  __I  uint32_t RMON_T_DROP;                       /**< Reserved Statistic Register, offset: 0x200 */
  __I  uint32_t RMON_T_PACKETS;                    /**< Tx Packet Count Statistic Register, offset: 0x204 */
  __I  uint32_t RMON_T_BC_PKT;                     /**< Tx Broadcast Packets Statistic Register, offset: 0x208 */
  __I  uint32_t RMON_T_MC_PKT;                     /**< Tx Multicast Packets Statistic Register, offset: 0x20C */
  __I  uint32_t RMON_T_CRC_ALIGN;                  /**< Tx Packets with CRC/Align Error Statistic Register, offset: 0x210 */
  __I  uint32_t RMON_T_UNDERSIZE;                  /**< Tx Packets Less Than Bytes and Good CRC Statistic Register, offset: 0x214 */
  __I  uint32_t RMON_T_OVERSIZE;                   /**< Tx Packets GT MAX_FL bytes and Good CRC Statistic Register, offset: 0x218 */
  __I  uint32_t RMON_T_FRAG;                       /**< Tx Packets Less Than 64 Bytes and Bad CRC Statistic Register, offset: 0x21C */
  __I  uint32_t RMON_T_JAB;                        /**< Tx Packets Greater Than MAX_FL bytes and Bad CRC Statistic Register, offset: 0x220 */
  __I  uint32_t RMON_T_COL;                        /**< Tx Collision Count Statistic Register, offset: 0x224 */
  __I  uint32_t RMON_T_P64;                        /**< Tx 64-Byte Packets Statistic Register, offset: 0x228 */
  __I  uint32_t RMON_T_P65TO127;                   /**< Tx 65- to 127-byte Packets Statistic Register, offset: 0x22C */
  __I  uint32_t RMON_T_P128TO255;                  /**< Tx 128- to 255-byte Packets Statistic Register, offset: 0x230 */
  __I  uint32_t RMON_T_P256TO511;                  /**< Tx 256- to 511-byte Packets Statistic Register, offset: 0x234 */
  __I  uint32_t RMON_T_P512TO1023;                 /**< Tx 512- to 1023-byte Packets Statistic Register, offset: 0x238 */
  __I  uint32_t RMON_T_P1024TO2047;                /**< Tx 1024- to 2047-byte Packets Statistic Register, offset: 0x23C */
  __I  uint32_t RMON_T_P_GTE2048;                  /**< Tx Packets Greater Than 2048 Bytes Statistic Register, offset: 0x240 */
  __I  uint32_t RMON_T_OCTETS;                     /**< Tx Octets Statistic Register, offset: 0x244 */
  __I  uint32_t IEEE_T_DROP;                       /**< Reserved Statistic Register, offset: 0x248 */
  __I  uint32_t IEEE_T_FRAME_OK;                   /**< Frames Transmitted OK Statistic Register, offset: 0x24C */
  __I  uint32_t IEEE_T_1COL;                       /**< Frames Transmitted with Single Collision Statistic Register, offset: 0x250 */
  __I  uint32_t IEEE_T_MCOL;                       /**< Frames Transmitted with Multiple Collisions Statistic Register, offset: 0x254 */
  __I  uint32_t IEEE_T_DEF;                        /**< Frames Transmitted after Deferral Delay Statistic Register, offset: 0x258 */
  __I  uint32_t IEEE_T_LCOL;                       /**< Frames Transmitted with Late Collision Statistic Register, offset: 0x25C */
  __I  uint32_t IEEE_T_EXCOL;                      /**< Frames Transmitted with Excessive Collisions Statistic Register, offset: 0x260 */
  __I  uint32_t IEEE_T_MACERR;                     /**< Frames Transmitted with Tx FIFO Underrun Statistic Register, offset: 0x264 */
  __I  uint32_t IEEE_T_CSERR;                      /**< Frames Transmitted with Carrier Sense Error Statistic Register, offset: 0x268 */
  __I  uint32_t IEEE_T_SQE;                        /**< Reserved Statistic Register, offset: 0x26C */
  __I  uint32_t IEEE_T_FDXFC;                      /**< Flow Control Pause Frames Transmitted Statistic Register, offset: 0x270 */
  __I  uint32_t IEEE_T_OCTETS_OK;                  /**< Octet Count for Frames Transmitted w/o Error Statistic Register, offset: 0x274 */
       uint8_t RESERVED_15[12];
  __I  uint32_t RMON_R_PACKETS;                    /**< Rx Packet Count Statistic Register, offset: 0x284 */
  __I  uint32_t RMON_R_BC_PKT;                     /**< Rx Broadcast Packets Statistic Register, offset: 0x288 */
  __I  uint32_t RMON_R_MC_PKT;                     /**< Rx Multicast Packets Statistic Register, offset: 0x28C */
  __I  uint32_t RMON_R_CRC_ALIGN;                  /**< Rx Packets with CRC/Align Error Statistic Register, offset: 0x290 */
  __I  uint32_t RMON_R_UNDERSIZE;                  /**< Rx Packets with Less Than 64 Bytes and Good CRC Statistic Register, offset: 0x294 */
  __I  uint32_t RMON_R_OVERSIZE;                   /**< Rx Packets Greater Than MAX_FL and Good CRC Statistic Register, offset: 0x298 */
  __I  uint32_t RMON_R_FRAG;                       /**< Rx Packets Less Than 64 Bytes and Bad CRC Statistic Register, offset: 0x29C */
  __I  uint32_t RMON_R_JAB;                        /**< Rx Packets Greater Than MAX_FL Bytes and Bad CRC Statistic Register, offset: 0x2A0 */
  __I  uint32_t RMON_R_RESVD_0;                    /**< Reserved Statistic Register, offset: 0x2A4 */
  __I  uint32_t RMON_R_P64;                        /**< Rx 64-Byte Packets Statistic Register, offset: 0x2A8 */
  __I  uint32_t RMON_R_P65TO127;                   /**< Rx 65- to 127-Byte Packets Statistic Register, offset: 0x2AC */
  __I  uint32_t RMON_R_P128TO255;                  /**< Rx 128- to 255-Byte Packets Statistic Register, offset: 0x2B0 */
  __I  uint32_t RMON_R_P256TO511;                  /**< Rx 256- to 511-Byte Packets Statistic Register, offset: 0x2B4 */
  __I  uint32_t RMON_R_P512TO1023;                 /**< Rx 512- to 1023-Byte Packets Statistic Register, offset: 0x2B8 */
  __I  uint32_t RMON_R_P1024TO2047;                /**< Rx 1024- to 2047-Byte Packets Statistic Register, offset: 0x2BC */
  __I  uint32_t RMON_R_P_GTE2048;                  /**< Rx Packets Greater than 2048 Bytes Statistic Register, offset: 0x2C0 */
  __I  uint32_t RMON_R_OCTETS;                     /**< Rx Octets Statistic Register, offset: 0x2C4 */
  __I  uint32_t IEEE_R_DROP;                       /**< Frames not Counted Correctly Statistic Register, offset: 0x2C8 */
  __I  uint32_t IEEE_R_FRAME_OK;                   /**< Frames Received OK Statistic Register, offset: 0x2CC */
  __I  uint32_t IEEE_R_CRC;                        /**< Frames Received with CRC Error Statistic Register, offset: 0x2D0 */
  __I  uint32_t IEEE_R_ALIGN;                      /**< Frames Received with Alignment Error Statistic Register, offset: 0x2D4 */
  __I  uint32_t IEEE_R_MACERR;                     /**< Receive FIFO Overflow Count Statistic Register, offset: 0x2D8 */
  __I  uint32_t IEEE_R_FDXFC;                      /**< Flow Control Pause Frames Received Statistic Register, offset: 0x2DC */
  __I  uint32_t IEEE_R_OCTETS_OK;                  /**< Octet Count for Frames Received without Error Statistic Register, offset: 0x2E0 */
       uint8_t RESERVED_16[284];
  __IO uint32_t ATCR;                              /**< Adjustable Timer Control Register, offset: 0x400 */
  __IO uint32_t ATVR;                              /**< Timer Value Register, offset: 0x404 */
  __IO uint32_t ATOFF;                             /**< Timer Offset Register, offset: 0x408 */
  __IO uint32_t ATPER;                             /**< Timer Period Register, offset: 0x40C */
  __IO uint32_t ATCOR;                             /**< Timer Correction Register, offset: 0x410 */
  __IO uint32_t ATINC;                             /**< Time-Stamping Clock Period Register, offset: 0x414 */
  __I  uint32_t ATSTMP;                            /**< Timestamp of Last Transmitted Frame, offset: 0x418 */
       uint8_t RESERVED_17[488];
  __IO uint32_t TGSR;                              /**< Timer Global Status Register, offset: 0x604 */
  struct {                                         /* offset: 0x608, array step: 0x8 */
    __IO uint32_t TCSR;                              /**< Timer Control Status Register, array offset: 0x608, array step: 0x8 */
    __IO uint32_t TCCR;                              /**< Timer Compare Capture Register, array offset: 0x60C, array step: 0x8 */
  } CHANNEL[4];
} ENET_Type;

/* ----------------------------------------------------------------------------
   -- ENET Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_Register_Masks ENET Register Masks
 * @{
 */

/*! @name EIR - Interrupt Event Register */
#define ENET_EIR_TS_TIMER_MASK                   (0x8000U)
#define ENET_EIR_TS_TIMER_SHIFT                  (15U)
#define ENET_EIR_TS_TIMER(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TS_TIMER_SHIFT)) & ENET_EIR_TS_TIMER_MASK)
#define ENET_EIR_TS_AVAIL_MASK                   (0x10000U)
#define ENET_EIR_TS_AVAIL_SHIFT                  (16U)
#define ENET_EIR_TS_AVAIL(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TS_AVAIL_SHIFT)) & ENET_EIR_TS_AVAIL_MASK)
#define ENET_EIR_WAKEUP_MASK                     (0x20000U)
#define ENET_EIR_WAKEUP_SHIFT                    (17U)
#define ENET_EIR_WAKEUP(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_EIR_WAKEUP_SHIFT)) & ENET_EIR_WAKEUP_MASK)
#define ENET_EIR_PLR_MASK                        (0x40000U)
#define ENET_EIR_PLR_SHIFT                       (18U)
#define ENET_EIR_PLR(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_PLR_SHIFT)) & ENET_EIR_PLR_MASK)
#define ENET_EIR_UN_MASK                         (0x80000U)
#define ENET_EIR_UN_SHIFT                        (19U)
#define ENET_EIR_UN(x)                           (((uint32_t)(((uint32_t)(x)) << ENET_EIR_UN_SHIFT)) & ENET_EIR_UN_MASK)
#define ENET_EIR_RL_MASK                         (0x100000U)
#define ENET_EIR_RL_SHIFT                        (20U)
#define ENET_EIR_RL(x)                           (((uint32_t)(((uint32_t)(x)) << ENET_EIR_RL_SHIFT)) & ENET_EIR_RL_MASK)
#define ENET_EIR_LC_MASK                         (0x200000U)
#define ENET_EIR_LC_SHIFT                        (21U)
#define ENET_EIR_LC(x)                           (((uint32_t)(((uint32_t)(x)) << ENET_EIR_LC_SHIFT)) & ENET_EIR_LC_MASK)
#define ENET_EIR_EBERR_MASK                      (0x400000U)
#define ENET_EIR_EBERR_SHIFT                     (22U)
#define ENET_EIR_EBERR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_EIR_EBERR_SHIFT)) & ENET_EIR_EBERR_MASK)
#define ENET_EIR_MII_MASK                        (0x800000U)
#define ENET_EIR_MII_SHIFT                       (23U)
#define ENET_EIR_MII(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_MII_SHIFT)) & ENET_EIR_MII_MASK)
#define ENET_EIR_RXB_MASK                        (0x1000000U)
#define ENET_EIR_RXB_SHIFT                       (24U)
#define ENET_EIR_RXB(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_RXB_SHIFT)) & ENET_EIR_RXB_MASK)
#define ENET_EIR_RXF_MASK                        (0x2000000U)
#define ENET_EIR_RXF_SHIFT                       (25U)
#define ENET_EIR_RXF(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_RXF_SHIFT)) & ENET_EIR_RXF_MASK)
#define ENET_EIR_TXB_MASK                        (0x4000000U)
#define ENET_EIR_TXB_SHIFT                       (26U)
#define ENET_EIR_TXB(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TXB_SHIFT)) & ENET_EIR_TXB_MASK)
#define ENET_EIR_TXF_MASK                        (0x8000000U)
#define ENET_EIR_TXF_SHIFT                       (27U)
#define ENET_EIR_TXF(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_TXF_SHIFT)) & ENET_EIR_TXF_MASK)
#define ENET_EIR_GRA_MASK                        (0x10000000U)
#define ENET_EIR_GRA_SHIFT                       (28U)
#define ENET_EIR_GRA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIR_GRA_SHIFT)) & ENET_EIR_GRA_MASK)
#define ENET_EIR_BABT_MASK                       (0x20000000U)
#define ENET_EIR_BABT_SHIFT                      (29U)
#define ENET_EIR_BABT(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIR_BABT_SHIFT)) & ENET_EIR_BABT_MASK)
#define ENET_EIR_BABR_MASK                       (0x40000000U)
#define ENET_EIR_BABR_SHIFT                      (30U)
#define ENET_EIR_BABR(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIR_BABR_SHIFT)) & ENET_EIR_BABR_MASK)

/*! @name EIMR - Interrupt Mask Register */
#define ENET_EIMR_TS_TIMER_MASK                  (0x8000U)
#define ENET_EIMR_TS_TIMER_SHIFT                 (15U)
#define ENET_EIMR_TS_TIMER(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TS_TIMER_SHIFT)) & ENET_EIMR_TS_TIMER_MASK)
#define ENET_EIMR_TS_AVAIL_MASK                  (0x10000U)
#define ENET_EIMR_TS_AVAIL_SHIFT                 (16U)
#define ENET_EIMR_TS_AVAIL(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TS_AVAIL_SHIFT)) & ENET_EIMR_TS_AVAIL_MASK)
#define ENET_EIMR_WAKEUP_MASK                    (0x20000U)
#define ENET_EIMR_WAKEUP_SHIFT                   (17U)
#define ENET_EIMR_WAKEUP(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_WAKEUP_SHIFT)) & ENET_EIMR_WAKEUP_MASK)
#define ENET_EIMR_PLR_MASK                       (0x40000U)
#define ENET_EIMR_PLR_SHIFT                      (18U)
#define ENET_EIMR_PLR(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_PLR_SHIFT)) & ENET_EIMR_PLR_MASK)
#define ENET_EIMR_UN_MASK                        (0x80000U)
#define ENET_EIMR_UN_SHIFT                       (19U)
#define ENET_EIMR_UN(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_UN_SHIFT)) & ENET_EIMR_UN_MASK)
#define ENET_EIMR_RL_MASK                        (0x100000U)
#define ENET_EIMR_RL_SHIFT                       (20U)
#define ENET_EIMR_RL(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_RL_SHIFT)) & ENET_EIMR_RL_MASK)
#define ENET_EIMR_LC_MASK                        (0x200000U)
#define ENET_EIMR_LC_SHIFT                       (21U)
#define ENET_EIMR_LC(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_LC_SHIFT)) & ENET_EIMR_LC_MASK)
#define ENET_EIMR_EBERR_MASK                     (0x400000U)
#define ENET_EIMR_EBERR_SHIFT                    (22U)
#define ENET_EIMR_EBERR(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_EBERR_SHIFT)) & ENET_EIMR_EBERR_MASK)
#define ENET_EIMR_MII_MASK                       (0x800000U)
#define ENET_EIMR_MII_SHIFT                      (23U)
#define ENET_EIMR_MII(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_MII_SHIFT)) & ENET_EIMR_MII_MASK)
#define ENET_EIMR_RXB_MASK                       (0x1000000U)
#define ENET_EIMR_RXB_SHIFT                      (24U)
#define ENET_EIMR_RXB(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_RXB_SHIFT)) & ENET_EIMR_RXB_MASK)
#define ENET_EIMR_RXF_MASK                       (0x2000000U)
#define ENET_EIMR_RXF_SHIFT                      (25U)
#define ENET_EIMR_RXF(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_RXF_SHIFT)) & ENET_EIMR_RXF_MASK)
#define ENET_EIMR_TXB_MASK                       (0x4000000U)
#define ENET_EIMR_TXB_SHIFT                      (26U)
#define ENET_EIMR_TXB(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TXB_SHIFT)) & ENET_EIMR_TXB_MASK)
#define ENET_EIMR_TXF_MASK                       (0x8000000U)
#define ENET_EIMR_TXF_SHIFT                      (27U)
#define ENET_EIMR_TXF(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_TXF_SHIFT)) & ENET_EIMR_TXF_MASK)
#define ENET_EIMR_GRA_MASK                       (0x10000000U)
#define ENET_EIMR_GRA_SHIFT                      (28U)
#define ENET_EIMR_GRA(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_GRA_SHIFT)) & ENET_EIMR_GRA_MASK)
#define ENET_EIMR_BABT_MASK                      (0x20000000U)
#define ENET_EIMR_BABT_SHIFT                     (29U)
#define ENET_EIMR_BABT(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_BABT_SHIFT)) & ENET_EIMR_BABT_MASK)
#define ENET_EIMR_BABR_MASK                      (0x40000000U)
#define ENET_EIMR_BABR_SHIFT                     (30U)
#define ENET_EIMR_BABR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_EIMR_BABR_SHIFT)) & ENET_EIMR_BABR_MASK)

/*! @name RDAR - Receive Descriptor Active Register */
#define ENET_RDAR_RDAR_MASK                      (0x1000000U)
#define ENET_RDAR_RDAR_SHIFT                     (24U)
#define ENET_RDAR_RDAR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RDAR_RDAR_SHIFT)) & ENET_RDAR_RDAR_MASK)

/*! @name TDAR - Transmit Descriptor Active Register */
#define ENET_TDAR_TDAR_MASK                      (0x1000000U)
#define ENET_TDAR_TDAR_SHIFT                     (24U)
#define ENET_TDAR_TDAR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TDAR_TDAR_SHIFT)) & ENET_TDAR_TDAR_MASK)

/*! @name ECR - Ethernet Control Register */
#define ENET_ECR_RESET_MASK                      (0x1U)
#define ENET_ECR_RESET_SHIFT                     (0U)
#define ENET_ECR_RESET(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_RESET_SHIFT)) & ENET_ECR_RESET_MASK)
#define ENET_ECR_ETHEREN_MASK                    (0x2U)
#define ENET_ECR_ETHEREN_SHIFT                   (1U)
#define ENET_ECR_ETHEREN(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ECR_ETHEREN_SHIFT)) & ENET_ECR_ETHEREN_MASK)
#define ENET_ECR_MAGICEN_MASK                    (0x4U)
#define ENET_ECR_MAGICEN_SHIFT                   (2U)
#define ENET_ECR_MAGICEN(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ECR_MAGICEN_SHIFT)) & ENET_ECR_MAGICEN_MASK)
#define ENET_ECR_SLEEP_MASK                      (0x8U)
#define ENET_ECR_SLEEP_SHIFT                     (3U)
#define ENET_ECR_SLEEP(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_SLEEP_SHIFT)) & ENET_ECR_SLEEP_MASK)
#define ENET_ECR_EN1588_MASK                     (0x10U)
#define ENET_ECR_EN1588_SHIFT                    (4U)
#define ENET_ECR_EN1588(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ECR_EN1588_SHIFT)) & ENET_ECR_EN1588_MASK)
#define ENET_ECR_DBGEN_MASK                      (0x40U)
#define ENET_ECR_DBGEN_SHIFT                     (6U)
#define ENET_ECR_DBGEN(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_DBGEN_SHIFT)) & ENET_ECR_DBGEN_MASK)
#define ENET_ECR_DBSWP_MASK                      (0x100U)
#define ENET_ECR_DBSWP_SHIFT                     (8U)
#define ENET_ECR_DBSWP(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ECR_DBSWP_SHIFT)) & ENET_ECR_DBSWP_MASK)

/*! @name MMFR - MII Management Frame Register */
#define ENET_MMFR_DATA_MASK                      (0xFFFFU)
#define ENET_MMFR_DATA_SHIFT                     (0U)
#define ENET_MMFR_DATA(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_DATA_SHIFT)) & ENET_MMFR_DATA_MASK)
#define ENET_MMFR_TA_MASK                        (0x30000U)
#define ENET_MMFR_TA_SHIFT                       (16U)
#define ENET_MMFR_TA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_TA_SHIFT)) & ENET_MMFR_TA_MASK)
#define ENET_MMFR_RA_MASK                        (0x7C0000U)
#define ENET_MMFR_RA_SHIFT                       (18U)
#define ENET_MMFR_RA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_RA_SHIFT)) & ENET_MMFR_RA_MASK)
#define ENET_MMFR_PA_MASK                        (0xF800000U)
#define ENET_MMFR_PA_SHIFT                       (23U)
#define ENET_MMFR_PA(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_PA_SHIFT)) & ENET_MMFR_PA_MASK)
#define ENET_MMFR_OP_MASK                        (0x30000000U)
#define ENET_MMFR_OP_SHIFT                       (28U)
#define ENET_MMFR_OP(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_OP_SHIFT)) & ENET_MMFR_OP_MASK)
#define ENET_MMFR_ST_MASK                        (0xC0000000U)
#define ENET_MMFR_ST_SHIFT                       (30U)
#define ENET_MMFR_ST(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_MMFR_ST_SHIFT)) & ENET_MMFR_ST_MASK)

/*! @name MSCR - MII Speed Control Register */
#define ENET_MSCR_MII_SPEED_MASK                 (0x7EU)
#define ENET_MSCR_MII_SPEED_SHIFT                (1U)
#define ENET_MSCR_MII_SPEED(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MSCR_MII_SPEED_SHIFT)) & ENET_MSCR_MII_SPEED_MASK)
#define ENET_MSCR_DIS_PRE_MASK                   (0x80U)
#define ENET_MSCR_DIS_PRE_SHIFT                  (7U)
#define ENET_MSCR_DIS_PRE(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_MSCR_DIS_PRE_SHIFT)) & ENET_MSCR_DIS_PRE_MASK)
#define ENET_MSCR_HOLDTIME_MASK                  (0x700U)
#define ENET_MSCR_HOLDTIME_SHIFT                 (8U)
#define ENET_MSCR_HOLDTIME(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MSCR_HOLDTIME_SHIFT)) & ENET_MSCR_HOLDTIME_MASK)

/*! @name MIBC - MIB Control Register */
#define ENET_MIBC_MIB_CLEAR_MASK                 (0x20000000U)
#define ENET_MIBC_MIB_CLEAR_SHIFT                (29U)
#define ENET_MIBC_MIB_CLEAR(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MIBC_MIB_CLEAR_SHIFT)) & ENET_MIBC_MIB_CLEAR_MASK)
#define ENET_MIBC_MIB_IDLE_MASK                  (0x40000000U)
#define ENET_MIBC_MIB_IDLE_SHIFT                 (30U)
#define ENET_MIBC_MIB_IDLE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MIBC_MIB_IDLE_SHIFT)) & ENET_MIBC_MIB_IDLE_MASK)
#define ENET_MIBC_MIB_DIS_MASK                   (0x80000000U)
#define ENET_MIBC_MIB_DIS_SHIFT                  (31U)
#define ENET_MIBC_MIB_DIS(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_MIBC_MIB_DIS_SHIFT)) & ENET_MIBC_MIB_DIS_MASK)

/*! @name RCR - Receive Control Register */
#define ENET_RCR_LOOP_MASK                       (0x1U)
#define ENET_RCR_LOOP_SHIFT                      (0U)
#define ENET_RCR_LOOP(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_RCR_LOOP_SHIFT)) & ENET_RCR_LOOP_MASK)
#define ENET_RCR_DRT_MASK                        (0x2U)
#define ENET_RCR_DRT_SHIFT                       (1U)
#define ENET_RCR_DRT(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_DRT_SHIFT)) & ENET_RCR_DRT_MASK)
#define ENET_RCR_MII_MODE_MASK                   (0x4U)
#define ENET_RCR_MII_MODE_SHIFT                  (2U)
#define ENET_RCR_MII_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RCR_MII_MODE_SHIFT)) & ENET_RCR_MII_MODE_MASK)
#define ENET_RCR_PROM_MASK                       (0x8U)
#define ENET_RCR_PROM_SHIFT                      (3U)
#define ENET_RCR_PROM(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_RCR_PROM_SHIFT)) & ENET_RCR_PROM_MASK)
#define ENET_RCR_BC_REJ_MASK                     (0x10U)
#define ENET_RCR_BC_REJ_SHIFT                    (4U)
#define ENET_RCR_BC_REJ(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_BC_REJ_SHIFT)) & ENET_RCR_BC_REJ_MASK)
#define ENET_RCR_FCE_MASK                        (0x20U)
#define ENET_RCR_FCE_SHIFT                       (5U)
#define ENET_RCR_FCE(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_FCE_SHIFT)) & ENET_RCR_FCE_MASK)
#define ENET_RCR_RMII_MODE_MASK                  (0x100U)
#define ENET_RCR_RMII_MODE_SHIFT                 (8U)
#define ENET_RCR_RMII_MODE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_RCR_RMII_MODE_SHIFT)) & ENET_RCR_RMII_MODE_MASK)
#define ENET_RCR_RMII_10T_MASK                   (0x200U)
#define ENET_RCR_RMII_10T_SHIFT                  (9U)
#define ENET_RCR_RMII_10T(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RCR_RMII_10T_SHIFT)) & ENET_RCR_RMII_10T_MASK)
#define ENET_RCR_PADEN_MASK                      (0x1000U)
#define ENET_RCR_PADEN_SHIFT                     (12U)
#define ENET_RCR_PADEN(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RCR_PADEN_SHIFT)) & ENET_RCR_PADEN_MASK)
#define ENET_RCR_PAUFWD_MASK                     (0x2000U)
#define ENET_RCR_PAUFWD_SHIFT                    (13U)
#define ENET_RCR_PAUFWD(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_PAUFWD_SHIFT)) & ENET_RCR_PAUFWD_MASK)
#define ENET_RCR_CRCFWD_MASK                     (0x4000U)
#define ENET_RCR_CRCFWD_SHIFT                    (14U)
#define ENET_RCR_CRCFWD(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_CRCFWD_SHIFT)) & ENET_RCR_CRCFWD_MASK)
#define ENET_RCR_CFEN_MASK                       (0x8000U)
#define ENET_RCR_CFEN_SHIFT                      (15U)
#define ENET_RCR_CFEN(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_RCR_CFEN_SHIFT)) & ENET_RCR_CFEN_MASK)
#define ENET_RCR_MAX_FL_MASK                     (0x3FFF0000U)
#define ENET_RCR_MAX_FL_SHIFT                    (16U)
#define ENET_RCR_MAX_FL(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RCR_MAX_FL_SHIFT)) & ENET_RCR_MAX_FL_MASK)
#define ENET_RCR_NLC_MASK                        (0x40000000U)
#define ENET_RCR_NLC_SHIFT                       (30U)
#define ENET_RCR_NLC(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_NLC_SHIFT)) & ENET_RCR_NLC_MASK)
#define ENET_RCR_GRS_MASK                        (0x80000000U)
#define ENET_RCR_GRS_SHIFT                       (31U)
#define ENET_RCR_GRS(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_RCR_GRS_SHIFT)) & ENET_RCR_GRS_MASK)

/*! @name TCR - Transmit Control Register */
#define ENET_TCR_GTS_MASK                        (0x1U)
#define ENET_TCR_GTS_SHIFT                       (0U)
#define ENET_TCR_GTS(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_TCR_GTS_SHIFT)) & ENET_TCR_GTS_MASK)
#define ENET_TCR_FDEN_MASK                       (0x4U)
#define ENET_TCR_FDEN_SHIFT                      (2U)
#define ENET_TCR_FDEN(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TCR_FDEN_SHIFT)) & ENET_TCR_FDEN_MASK)
#define ENET_TCR_TFC_PAUSE_MASK                  (0x8U)
#define ENET_TCR_TFC_PAUSE_SHIFT                 (3U)
#define ENET_TCR_TFC_PAUSE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_TCR_TFC_PAUSE_SHIFT)) & ENET_TCR_TFC_PAUSE_MASK)
#define ENET_TCR_RFC_PAUSE_MASK                  (0x10U)
#define ENET_TCR_RFC_PAUSE_SHIFT                 (4U)
#define ENET_TCR_RFC_PAUSE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_TCR_RFC_PAUSE_SHIFT)) & ENET_TCR_RFC_PAUSE_MASK)
#define ENET_TCR_ADDSEL_MASK                     (0xE0U)
#define ENET_TCR_ADDSEL_SHIFT                    (5U)
#define ENET_TCR_ADDSEL(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCR_ADDSEL_SHIFT)) & ENET_TCR_ADDSEL_MASK)
#define ENET_TCR_ADDINS_MASK                     (0x100U)
#define ENET_TCR_ADDINS_SHIFT                    (8U)
#define ENET_TCR_ADDINS(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCR_ADDINS_SHIFT)) & ENET_TCR_ADDINS_MASK)
#define ENET_TCR_CRCFWD_MASK                     (0x200U)
#define ENET_TCR_CRCFWD_SHIFT                    (9U)
#define ENET_TCR_CRCFWD(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCR_CRCFWD_SHIFT)) & ENET_TCR_CRCFWD_MASK)

/*! @name PALR - Physical Address Lower Register */
#define ENET_PALR_PADDR1_MASK                    (0xFFFFFFFFU)
#define ENET_PALR_PADDR1_SHIFT                   (0U)
#define ENET_PALR_PADDR1(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_PALR_PADDR1_SHIFT)) & ENET_PALR_PADDR1_MASK)

/*! @name PAUR - Physical Address Upper Register */
#define ENET_PAUR_TYPE_MASK                      (0xFFFFU)
#define ENET_PAUR_TYPE_SHIFT                     (0U)
#define ENET_PAUR_TYPE(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_PAUR_TYPE_SHIFT)) & ENET_PAUR_TYPE_MASK)
#define ENET_PAUR_PADDR2_MASK                    (0xFFFF0000U)
#define ENET_PAUR_PADDR2_SHIFT                   (16U)
#define ENET_PAUR_PADDR2(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_PAUR_PADDR2_SHIFT)) & ENET_PAUR_PADDR2_MASK)

/*! @name OPD - Opcode/Pause Duration Register */
#define ENET_OPD_PAUSE_DUR_MASK                  (0xFFFFU)
#define ENET_OPD_PAUSE_DUR_SHIFT                 (0U)
#define ENET_OPD_PAUSE_DUR(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_OPD_PAUSE_DUR_SHIFT)) & ENET_OPD_PAUSE_DUR_MASK)
#define ENET_OPD_OPCODE_MASK                     (0xFFFF0000U)
#define ENET_OPD_OPCODE_SHIFT                    (16U)
#define ENET_OPD_OPCODE(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_OPD_OPCODE_SHIFT)) & ENET_OPD_OPCODE_MASK)

/*! @name TXIC - Transmit Interrupt Coalescing Register */
#define ENET_TXIC_ICTT_MASK                      (0xFFFFU)
#define ENET_TXIC_ICTT_SHIFT                     (0U)
#define ENET_TXIC_ICTT(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TXIC_ICTT_SHIFT)) & ENET_TXIC_ICTT_MASK)
#define ENET_TXIC_ICFT_MASK                      (0xFF00000U)
#define ENET_TXIC_ICFT_SHIFT                     (20U)
#define ENET_TXIC_ICFT(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TXIC_ICFT_SHIFT)) & ENET_TXIC_ICFT_MASK)
#define ENET_TXIC_ICCS_MASK                      (0x40000000U)
#define ENET_TXIC_ICCS_SHIFT                     (30U)
#define ENET_TXIC_ICCS(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TXIC_ICCS_SHIFT)) & ENET_TXIC_ICCS_MASK)
#define ENET_TXIC_ICEN_MASK                      (0x80000000U)
#define ENET_TXIC_ICEN_SHIFT                     (31U)
#define ENET_TXIC_ICEN(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TXIC_ICEN_SHIFT)) & ENET_TXIC_ICEN_MASK)

/*! @name RXIC - Receive Interrupt Coalescing Register */
#define ENET_RXIC_ICTT_MASK                      (0xFFFFU)
#define ENET_RXIC_ICTT_SHIFT                     (0U)
#define ENET_RXIC_ICTT(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RXIC_ICTT_SHIFT)) & ENET_RXIC_ICTT_MASK)
#define ENET_RXIC_ICFT_MASK                      (0xFF00000U)
#define ENET_RXIC_ICFT_SHIFT                     (20U)
#define ENET_RXIC_ICFT(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RXIC_ICFT_SHIFT)) & ENET_RXIC_ICFT_MASK)
#define ENET_RXIC_ICCS_MASK                      (0x40000000U)
#define ENET_RXIC_ICCS_SHIFT                     (30U)
#define ENET_RXIC_ICCS(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RXIC_ICCS_SHIFT)) & ENET_RXIC_ICCS_MASK)
#define ENET_RXIC_ICEN_MASK                      (0x80000000U)
#define ENET_RXIC_ICEN_SHIFT                     (31U)
#define ENET_RXIC_ICEN(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_RXIC_ICEN_SHIFT)) & ENET_RXIC_ICEN_MASK)

/*! @name IAUR - Descriptor Individual Upper Address Register */
#define ENET_IAUR_IADDR1_MASK                    (0xFFFFFFFFU)
#define ENET_IAUR_IADDR1_SHIFT                   (0U)
#define ENET_IAUR_IADDR1(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_IAUR_IADDR1_SHIFT)) & ENET_IAUR_IADDR1_MASK)

/*! @name IALR - Descriptor Individual Lower Address Register */
#define ENET_IALR_IADDR2_MASK                    (0xFFFFFFFFU)
#define ENET_IALR_IADDR2_SHIFT                   (0U)
#define ENET_IALR_IADDR2(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_IALR_IADDR2_SHIFT)) & ENET_IALR_IADDR2_MASK)

/*! @name GAUR - Descriptor Group Upper Address Register */
#define ENET_GAUR_GADDR1_MASK                    (0xFFFFFFFFU)
#define ENET_GAUR_GADDR1_SHIFT                   (0U)
#define ENET_GAUR_GADDR1(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_GAUR_GADDR1_SHIFT)) & ENET_GAUR_GADDR1_MASK)

/*! @name GALR - Descriptor Group Lower Address Register */
#define ENET_GALR_GADDR2_MASK                    (0xFFFFFFFFU)
#define ENET_GALR_GADDR2_SHIFT                   (0U)
#define ENET_GALR_GADDR2(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_GALR_GADDR2_SHIFT)) & ENET_GALR_GADDR2_MASK)

/*! @name TFWR - Transmit FIFO Watermark Register */
#define ENET_TFWR_TFWR_MASK                      (0x3FU)
#define ENET_TFWR_TFWR_SHIFT                     (0U)
#define ENET_TFWR_TFWR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TFWR_TFWR_SHIFT)) & ENET_TFWR_TFWR_MASK)
#define ENET_TFWR_STRFWD_MASK                    (0x100U)
#define ENET_TFWR_STRFWD_SHIFT                   (8U)
#define ENET_TFWR_STRFWD(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_TFWR_STRFWD_SHIFT)) & ENET_TFWR_STRFWD_MASK)

/*! @name RDSR - Receive Descriptor Ring Start Register */
#define ENET_RDSR_R_DES_START_MASK               (0xFFFFFFF8U)
#define ENET_RDSR_R_DES_START_SHIFT              (3U)
#define ENET_RDSR_R_DES_START(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_RDSR_R_DES_START_SHIFT)) & ENET_RDSR_R_DES_START_MASK)

/*! @name TDSR - Transmit Buffer Descriptor Ring Start Register */
#define ENET_TDSR_X_DES_START_MASK               (0xFFFFFFF8U)
#define ENET_TDSR_X_DES_START_SHIFT              (3U)
#define ENET_TDSR_X_DES_START(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_TDSR_X_DES_START_SHIFT)) & ENET_TDSR_X_DES_START_MASK)

/*! @name MRBR - Maximum Receive Buffer Size Register */
#define ENET_MRBR_R_BUF_SIZE_MASK                (0x3FF0U)
#define ENET_MRBR_R_BUF_SIZE_SHIFT               (4U)
#define ENET_MRBR_R_BUF_SIZE(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_MRBR_R_BUF_SIZE_SHIFT)) & ENET_MRBR_R_BUF_SIZE_MASK)

/*! @name RSFL - Receive FIFO Section Full Threshold */
#define ENET_RSFL_RX_SECTION_FULL_MASK           (0xFFU)
#define ENET_RSFL_RX_SECTION_FULL_SHIFT          (0U)
#define ENET_RSFL_RX_SECTION_FULL(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RSFL_RX_SECTION_FULL_SHIFT)) & ENET_RSFL_RX_SECTION_FULL_MASK)

/*! @name RSEM - Receive FIFO Section Empty Threshold */
#define ENET_RSEM_RX_SECTION_EMPTY_MASK          (0xFFU)
#define ENET_RSEM_RX_SECTION_EMPTY_SHIFT         (0U)
#define ENET_RSEM_RX_SECTION_EMPTY(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RSEM_RX_SECTION_EMPTY_SHIFT)) & ENET_RSEM_RX_SECTION_EMPTY_MASK)
#define ENET_RSEM_STAT_SECTION_EMPTY_MASK        (0x1F0000U)
#define ENET_RSEM_STAT_SECTION_EMPTY_SHIFT       (16U)
#define ENET_RSEM_STAT_SECTION_EMPTY(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RSEM_STAT_SECTION_EMPTY_SHIFT)) & ENET_RSEM_STAT_SECTION_EMPTY_MASK)

/*! @name RAEM - Receive FIFO Almost Empty Threshold */
#define ENET_RAEM_RX_ALMOST_EMPTY_MASK           (0xFFU)
#define ENET_RAEM_RX_ALMOST_EMPTY_SHIFT          (0U)
#define ENET_RAEM_RX_ALMOST_EMPTY(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RAEM_RX_ALMOST_EMPTY_SHIFT)) & ENET_RAEM_RX_ALMOST_EMPTY_MASK)

/*! @name RAFL - Receive FIFO Almost Full Threshold */
#define ENET_RAFL_RX_ALMOST_FULL_MASK            (0xFFU)
#define ENET_RAFL_RX_ALMOST_FULL_SHIFT           (0U)
#define ENET_RAFL_RX_ALMOST_FULL(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RAFL_RX_ALMOST_FULL_SHIFT)) & ENET_RAFL_RX_ALMOST_FULL_MASK)

/*! @name TSEM - Transmit FIFO Section Empty Threshold */
#define ENET_TSEM_TX_SECTION_EMPTY_MASK          (0xFFU)
#define ENET_TSEM_TX_SECTION_EMPTY_SHIFT         (0U)
#define ENET_TSEM_TX_SECTION_EMPTY(x)            (((uint32_t)(((uint32_t)(x)) << ENET_TSEM_TX_SECTION_EMPTY_SHIFT)) & ENET_TSEM_TX_SECTION_EMPTY_MASK)

/*! @name TAEM - Transmit FIFO Almost Empty Threshold */
#define ENET_TAEM_TX_ALMOST_EMPTY_MASK           (0xFFU)
#define ENET_TAEM_TX_ALMOST_EMPTY_SHIFT          (0U)
#define ENET_TAEM_TX_ALMOST_EMPTY(x)             (((uint32_t)(((uint32_t)(x)) << ENET_TAEM_TX_ALMOST_EMPTY_SHIFT)) & ENET_TAEM_TX_ALMOST_EMPTY_MASK)

/*! @name TAFL - Transmit FIFO Almost Full Threshold */
#define ENET_TAFL_TX_ALMOST_FULL_MASK            (0xFFU)
#define ENET_TAFL_TX_ALMOST_FULL_SHIFT           (0U)
#define ENET_TAFL_TX_ALMOST_FULL(x)              (((uint32_t)(((uint32_t)(x)) << ENET_TAFL_TX_ALMOST_FULL_SHIFT)) & ENET_TAFL_TX_ALMOST_FULL_MASK)

/*! @name TIPG - Transmit Inter-Packet Gap */
#define ENET_TIPG_IPG_MASK                       (0x1FU)
#define ENET_TIPG_IPG_SHIFT                      (0U)
#define ENET_TIPG_IPG(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TIPG_IPG_SHIFT)) & ENET_TIPG_IPG_MASK)

/*! @name FTRL - Frame Truncation Length */
#define ENET_FTRL_TRUNC_FL_MASK                  (0x3FFFU)
#define ENET_FTRL_TRUNC_FL_SHIFT                 (0U)
#define ENET_FTRL_TRUNC_FL(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_FTRL_TRUNC_FL_SHIFT)) & ENET_FTRL_TRUNC_FL_MASK)

/*! @name TACC - Transmit Accelerator Function Configuration */
#define ENET_TACC_SHIFT16_MASK                   (0x1U)
#define ENET_TACC_SHIFT16_SHIFT                  (0U)
#define ENET_TACC_SHIFT16(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_TACC_SHIFT16_SHIFT)) & ENET_TACC_SHIFT16_MASK)
#define ENET_TACC_IPCHK_MASK                     (0x8U)
#define ENET_TACC_IPCHK_SHIFT                    (3U)
#define ENET_TACC_IPCHK(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TACC_IPCHK_SHIFT)) & ENET_TACC_IPCHK_MASK)
#define ENET_TACC_PROCHK_MASK                    (0x10U)
#define ENET_TACC_PROCHK_SHIFT                   (4U)
#define ENET_TACC_PROCHK(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_TACC_PROCHK_SHIFT)) & ENET_TACC_PROCHK_MASK)

/*! @name RACC - Receive Accelerator Function Configuration */
#define ENET_RACC_PADREM_MASK                    (0x1U)
#define ENET_RACC_PADREM_SHIFT                   (0U)
#define ENET_RACC_PADREM(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_RACC_PADREM_SHIFT)) & ENET_RACC_PADREM_MASK)
#define ENET_RACC_IPDIS_MASK                     (0x2U)
#define ENET_RACC_IPDIS_SHIFT                    (1U)
#define ENET_RACC_IPDIS(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_RACC_IPDIS_SHIFT)) & ENET_RACC_IPDIS_MASK)
#define ENET_RACC_PRODIS_MASK                    (0x4U)
#define ENET_RACC_PRODIS_SHIFT                   (2U)
#define ENET_RACC_PRODIS(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_RACC_PRODIS_SHIFT)) & ENET_RACC_PRODIS_MASK)
#define ENET_RACC_LINEDIS_MASK                   (0x40U)
#define ENET_RACC_LINEDIS_SHIFT                  (6U)
#define ENET_RACC_LINEDIS(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RACC_LINEDIS_SHIFT)) & ENET_RACC_LINEDIS_MASK)
#define ENET_RACC_SHIFT16_MASK                   (0x80U)
#define ENET_RACC_SHIFT16_SHIFT                  (7U)
#define ENET_RACC_SHIFT16(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_RACC_SHIFT16_SHIFT)) & ENET_RACC_SHIFT16_MASK)

/*! @name RMON_T_PACKETS - Tx Packet Count Statistic Register */
#define ENET_RMON_T_PACKETS_TXPKTS_MASK          (0xFFFFU)
#define ENET_RMON_T_PACKETS_TXPKTS_SHIFT         (0U)
#define ENET_RMON_T_PACKETS_TXPKTS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_PACKETS_TXPKTS_SHIFT)) & ENET_RMON_T_PACKETS_TXPKTS_MASK)

/*! @name RMON_T_BC_PKT - Tx Broadcast Packets Statistic Register */
#define ENET_RMON_T_BC_PKT_TXPKTS_MASK           (0xFFFFU)
#define ENET_RMON_T_BC_PKT_TXPKTS_SHIFT          (0U)
#define ENET_RMON_T_BC_PKT_TXPKTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_BC_PKT_TXPKTS_SHIFT)) & ENET_RMON_T_BC_PKT_TXPKTS_MASK)

/*! @name RMON_T_MC_PKT - Tx Multicast Packets Statistic Register */
#define ENET_RMON_T_MC_PKT_TXPKTS_MASK           (0xFFFFU)
#define ENET_RMON_T_MC_PKT_TXPKTS_SHIFT          (0U)
#define ENET_RMON_T_MC_PKT_TXPKTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_MC_PKT_TXPKTS_SHIFT)) & ENET_RMON_T_MC_PKT_TXPKTS_MASK)

/*! @name RMON_T_CRC_ALIGN - Tx Packets with CRC/Align Error Statistic Register */
#define ENET_RMON_T_CRC_ALIGN_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_CRC_ALIGN_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_CRC_ALIGN_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_CRC_ALIGN_TXPKTS_SHIFT)) & ENET_RMON_T_CRC_ALIGN_TXPKTS_MASK)

/*! @name RMON_T_UNDERSIZE - Tx Packets Less Than Bytes and Good CRC Statistic Register */
#define ENET_RMON_T_UNDERSIZE_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_UNDERSIZE_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_UNDERSIZE_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_UNDERSIZE_TXPKTS_SHIFT)) & ENET_RMON_T_UNDERSIZE_TXPKTS_MASK)

/*! @name RMON_T_OVERSIZE - Tx Packets GT MAX_FL bytes and Good CRC Statistic Register */
#define ENET_RMON_T_OVERSIZE_TXPKTS_MASK         (0xFFFFU)
#define ENET_RMON_T_OVERSIZE_TXPKTS_SHIFT        (0U)
#define ENET_RMON_T_OVERSIZE_TXPKTS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_OVERSIZE_TXPKTS_SHIFT)) & ENET_RMON_T_OVERSIZE_TXPKTS_MASK)

/*! @name RMON_T_FRAG - Tx Packets Less Than 64 Bytes and Bad CRC Statistic Register */
#define ENET_RMON_T_FRAG_TXPKTS_MASK             (0xFFFFU)
#define ENET_RMON_T_FRAG_TXPKTS_SHIFT            (0U)
#define ENET_RMON_T_FRAG_TXPKTS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_FRAG_TXPKTS_SHIFT)) & ENET_RMON_T_FRAG_TXPKTS_MASK)

/*! @name RMON_T_JAB - Tx Packets Greater Than MAX_FL bytes and Bad CRC Statistic Register */
#define ENET_RMON_T_JAB_TXPKTS_MASK              (0xFFFFU)
#define ENET_RMON_T_JAB_TXPKTS_SHIFT             (0U)
#define ENET_RMON_T_JAB_TXPKTS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_JAB_TXPKTS_SHIFT)) & ENET_RMON_T_JAB_TXPKTS_MASK)

/*! @name RMON_T_COL - Tx Collision Count Statistic Register */
#define ENET_RMON_T_COL_TXPKTS_MASK              (0xFFFFU)
#define ENET_RMON_T_COL_TXPKTS_SHIFT             (0U)
#define ENET_RMON_T_COL_TXPKTS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_COL_TXPKTS_SHIFT)) & ENET_RMON_T_COL_TXPKTS_MASK)

/*! @name RMON_T_P64 - Tx 64-Byte Packets Statistic Register */
#define ENET_RMON_T_P64_TXPKTS_MASK              (0xFFFFU)
#define ENET_RMON_T_P64_TXPKTS_SHIFT             (0U)
#define ENET_RMON_T_P64_TXPKTS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P64_TXPKTS_SHIFT)) & ENET_RMON_T_P64_TXPKTS_MASK)

/*! @name RMON_T_P65TO127 - Tx 65- to 127-byte Packets Statistic Register */
#define ENET_RMON_T_P65TO127_TXPKTS_MASK         (0xFFFFU)
#define ENET_RMON_T_P65TO127_TXPKTS_SHIFT        (0U)
#define ENET_RMON_T_P65TO127_TXPKTS(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P65TO127_TXPKTS_SHIFT)) & ENET_RMON_T_P65TO127_TXPKTS_MASK)

/*! @name RMON_T_P128TO255 - Tx 128- to 255-byte Packets Statistic Register */
#define ENET_RMON_T_P128TO255_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_P128TO255_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_P128TO255_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P128TO255_TXPKTS_SHIFT)) & ENET_RMON_T_P128TO255_TXPKTS_MASK)

/*! @name RMON_T_P256TO511 - Tx 256- to 511-byte Packets Statistic Register */
#define ENET_RMON_T_P256TO511_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_P256TO511_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_P256TO511_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P256TO511_TXPKTS_SHIFT)) & ENET_RMON_T_P256TO511_TXPKTS_MASK)

/*! @name RMON_T_P512TO1023 - Tx 512- to 1023-byte Packets Statistic Register */
#define ENET_RMON_T_P512TO1023_TXPKTS_MASK       (0xFFFFU)
#define ENET_RMON_T_P512TO1023_TXPKTS_SHIFT      (0U)
#define ENET_RMON_T_P512TO1023_TXPKTS(x)         (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P512TO1023_TXPKTS_SHIFT)) & ENET_RMON_T_P512TO1023_TXPKTS_MASK)

/*! @name RMON_T_P1024TO2047 - Tx 1024- to 2047-byte Packets Statistic Register */
#define ENET_RMON_T_P1024TO2047_TXPKTS_MASK      (0xFFFFU)
#define ENET_RMON_T_P1024TO2047_TXPKTS_SHIFT     (0U)
#define ENET_RMON_T_P1024TO2047_TXPKTS(x)        (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P1024TO2047_TXPKTS_SHIFT)) & ENET_RMON_T_P1024TO2047_TXPKTS_MASK)

/*! @name RMON_T_P_GTE2048 - Tx Packets Greater Than 2048 Bytes Statistic Register */
#define ENET_RMON_T_P_GTE2048_TXPKTS_MASK        (0xFFFFU)
#define ENET_RMON_T_P_GTE2048_TXPKTS_SHIFT       (0U)
#define ENET_RMON_T_P_GTE2048_TXPKTS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_P_GTE2048_TXPKTS_SHIFT)) & ENET_RMON_T_P_GTE2048_TXPKTS_MASK)

/*! @name RMON_T_OCTETS - Tx Octets Statistic Register */
#define ENET_RMON_T_OCTETS_TXOCTS_MASK           (0xFFFFFFFFU)
#define ENET_RMON_T_OCTETS_TXOCTS_SHIFT          (0U)
#define ENET_RMON_T_OCTETS_TXOCTS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_T_OCTETS_TXOCTS_SHIFT)) & ENET_RMON_T_OCTETS_TXOCTS_MASK)

/*! @name IEEE_T_FRAME_OK - Frames Transmitted OK Statistic Register */
#define ENET_IEEE_T_FRAME_OK_COUNT_MASK          (0xFFFFU)
#define ENET_IEEE_T_FRAME_OK_COUNT_SHIFT         (0U)
#define ENET_IEEE_T_FRAME_OK_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_FRAME_OK_COUNT_SHIFT)) & ENET_IEEE_T_FRAME_OK_COUNT_MASK)

/*! @name IEEE_T_1COL - Frames Transmitted with Single Collision Statistic Register */
#define ENET_IEEE_T_1COL_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_T_1COL_COUNT_SHIFT             (0U)
#define ENET_IEEE_T_1COL_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_1COL_COUNT_SHIFT)) & ENET_IEEE_T_1COL_COUNT_MASK)

/*! @name IEEE_T_MCOL - Frames Transmitted with Multiple Collisions Statistic Register */
#define ENET_IEEE_T_MCOL_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_T_MCOL_COUNT_SHIFT             (0U)
#define ENET_IEEE_T_MCOL_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_MCOL_COUNT_SHIFT)) & ENET_IEEE_T_MCOL_COUNT_MASK)

/*! @name IEEE_T_DEF - Frames Transmitted after Deferral Delay Statistic Register */
#define ENET_IEEE_T_DEF_COUNT_MASK               (0xFFFFU)
#define ENET_IEEE_T_DEF_COUNT_SHIFT              (0U)
#define ENET_IEEE_T_DEF_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_DEF_COUNT_SHIFT)) & ENET_IEEE_T_DEF_COUNT_MASK)

/*! @name IEEE_T_LCOL - Frames Transmitted with Late Collision Statistic Register */
#define ENET_IEEE_T_LCOL_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_T_LCOL_COUNT_SHIFT             (0U)
#define ENET_IEEE_T_LCOL_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_LCOL_COUNT_SHIFT)) & ENET_IEEE_T_LCOL_COUNT_MASK)

/*! @name IEEE_T_EXCOL - Frames Transmitted with Excessive Collisions Statistic Register */
#define ENET_IEEE_T_EXCOL_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_T_EXCOL_COUNT_SHIFT            (0U)
#define ENET_IEEE_T_EXCOL_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_EXCOL_COUNT_SHIFT)) & ENET_IEEE_T_EXCOL_COUNT_MASK)

/*! @name IEEE_T_MACERR - Frames Transmitted with Tx FIFO Underrun Statistic Register */
#define ENET_IEEE_T_MACERR_COUNT_MASK            (0xFFFFU)
#define ENET_IEEE_T_MACERR_COUNT_SHIFT           (0U)
#define ENET_IEEE_T_MACERR_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_MACERR_COUNT_SHIFT)) & ENET_IEEE_T_MACERR_COUNT_MASK)

/*! @name IEEE_T_CSERR - Frames Transmitted with Carrier Sense Error Statistic Register */
#define ENET_IEEE_T_CSERR_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_T_CSERR_COUNT_SHIFT            (0U)
#define ENET_IEEE_T_CSERR_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_CSERR_COUNT_SHIFT)) & ENET_IEEE_T_CSERR_COUNT_MASK)

/*! @name IEEE_T_SQE - Reserved Statistic Register */
#define ENET_IEEE_T_SQE_COUNT_MASK               (0xFFFFU)
#define ENET_IEEE_T_SQE_COUNT_SHIFT              (0U)
#define ENET_IEEE_T_SQE_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_SQE_COUNT_SHIFT)) & ENET_IEEE_T_SQE_COUNT_MASK)

/*! @name IEEE_T_FDXFC - Flow Control Pause Frames Transmitted Statistic Register */
#define ENET_IEEE_T_FDXFC_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_T_FDXFC_COUNT_SHIFT            (0U)
#define ENET_IEEE_T_FDXFC_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_FDXFC_COUNT_SHIFT)) & ENET_IEEE_T_FDXFC_COUNT_MASK)

/*! @name IEEE_T_OCTETS_OK - Octet Count for Frames Transmitted w/o Error Statistic Register */
#define ENET_IEEE_T_OCTETS_OK_COUNT_MASK         (0xFFFFFFFFU)
#define ENET_IEEE_T_OCTETS_OK_COUNT_SHIFT        (0U)
#define ENET_IEEE_T_OCTETS_OK_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_T_OCTETS_OK_COUNT_SHIFT)) & ENET_IEEE_T_OCTETS_OK_COUNT_MASK)

/*! @name RMON_R_PACKETS - Rx Packet Count Statistic Register */
#define ENET_RMON_R_PACKETS_COUNT_MASK           (0xFFFFU)
#define ENET_RMON_R_PACKETS_COUNT_SHIFT          (0U)
#define ENET_RMON_R_PACKETS_COUNT(x)             (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_PACKETS_COUNT_SHIFT)) & ENET_RMON_R_PACKETS_COUNT_MASK)

/*! @name RMON_R_BC_PKT - Rx Broadcast Packets Statistic Register */
#define ENET_RMON_R_BC_PKT_COUNT_MASK            (0xFFFFU)
#define ENET_RMON_R_BC_PKT_COUNT_SHIFT           (0U)
#define ENET_RMON_R_BC_PKT_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_BC_PKT_COUNT_SHIFT)) & ENET_RMON_R_BC_PKT_COUNT_MASK)

/*! @name RMON_R_MC_PKT - Rx Multicast Packets Statistic Register */
#define ENET_RMON_R_MC_PKT_COUNT_MASK            (0xFFFFU)
#define ENET_RMON_R_MC_PKT_COUNT_SHIFT           (0U)
#define ENET_RMON_R_MC_PKT_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_MC_PKT_COUNT_SHIFT)) & ENET_RMON_R_MC_PKT_COUNT_MASK)

/*! @name RMON_R_CRC_ALIGN - Rx Packets with CRC/Align Error Statistic Register */
#define ENET_RMON_R_CRC_ALIGN_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_CRC_ALIGN_COUNT_SHIFT        (0U)
#define ENET_RMON_R_CRC_ALIGN_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_CRC_ALIGN_COUNT_SHIFT)) & ENET_RMON_R_CRC_ALIGN_COUNT_MASK)

/*! @name RMON_R_UNDERSIZE - Rx Packets with Less Than 64 Bytes and Good CRC Statistic Register */
#define ENET_RMON_R_UNDERSIZE_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_UNDERSIZE_COUNT_SHIFT        (0U)
#define ENET_RMON_R_UNDERSIZE_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_UNDERSIZE_COUNT_SHIFT)) & ENET_RMON_R_UNDERSIZE_COUNT_MASK)

/*! @name RMON_R_OVERSIZE - Rx Packets Greater Than MAX_FL and Good CRC Statistic Register */
#define ENET_RMON_R_OVERSIZE_COUNT_MASK          (0xFFFFU)
#define ENET_RMON_R_OVERSIZE_COUNT_SHIFT         (0U)
#define ENET_RMON_R_OVERSIZE_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_OVERSIZE_COUNT_SHIFT)) & ENET_RMON_R_OVERSIZE_COUNT_MASK)

/*! @name RMON_R_FRAG - Rx Packets Less Than 64 Bytes and Bad CRC Statistic Register */
#define ENET_RMON_R_FRAG_COUNT_MASK              (0xFFFFU)
#define ENET_RMON_R_FRAG_COUNT_SHIFT             (0U)
#define ENET_RMON_R_FRAG_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_FRAG_COUNT_SHIFT)) & ENET_RMON_R_FRAG_COUNT_MASK)

/*! @name RMON_R_JAB - Rx Packets Greater Than MAX_FL Bytes and Bad CRC Statistic Register */
#define ENET_RMON_R_JAB_COUNT_MASK               (0xFFFFU)
#define ENET_RMON_R_JAB_COUNT_SHIFT              (0U)
#define ENET_RMON_R_JAB_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_JAB_COUNT_SHIFT)) & ENET_RMON_R_JAB_COUNT_MASK)

/*! @name RMON_R_P64 - Rx 64-Byte Packets Statistic Register */
#define ENET_RMON_R_P64_COUNT_MASK               (0xFFFFU)
#define ENET_RMON_R_P64_COUNT_SHIFT              (0U)
#define ENET_RMON_R_P64_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P64_COUNT_SHIFT)) & ENET_RMON_R_P64_COUNT_MASK)

/*! @name RMON_R_P65TO127 - Rx 65- to 127-Byte Packets Statistic Register */
#define ENET_RMON_R_P65TO127_COUNT_MASK          (0xFFFFU)
#define ENET_RMON_R_P65TO127_COUNT_SHIFT         (0U)
#define ENET_RMON_R_P65TO127_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P65TO127_COUNT_SHIFT)) & ENET_RMON_R_P65TO127_COUNT_MASK)

/*! @name RMON_R_P128TO255 - Rx 128- to 255-Byte Packets Statistic Register */
#define ENET_RMON_R_P128TO255_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_P128TO255_COUNT_SHIFT        (0U)
#define ENET_RMON_R_P128TO255_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P128TO255_COUNT_SHIFT)) & ENET_RMON_R_P128TO255_COUNT_MASK)

/*! @name RMON_R_P256TO511 - Rx 256- to 511-Byte Packets Statistic Register */
#define ENET_RMON_R_P256TO511_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_P256TO511_COUNT_SHIFT        (0U)
#define ENET_RMON_R_P256TO511_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P256TO511_COUNT_SHIFT)) & ENET_RMON_R_P256TO511_COUNT_MASK)

/*! @name RMON_R_P512TO1023 - Rx 512- to 1023-Byte Packets Statistic Register */
#define ENET_RMON_R_P512TO1023_COUNT_MASK        (0xFFFFU)
#define ENET_RMON_R_P512TO1023_COUNT_SHIFT       (0U)
#define ENET_RMON_R_P512TO1023_COUNT(x)          (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P512TO1023_COUNT_SHIFT)) & ENET_RMON_R_P512TO1023_COUNT_MASK)

/*! @name RMON_R_P1024TO2047 - Rx 1024- to 2047-Byte Packets Statistic Register */
#define ENET_RMON_R_P1024TO2047_COUNT_MASK       (0xFFFFU)
#define ENET_RMON_R_P1024TO2047_COUNT_SHIFT      (0U)
#define ENET_RMON_R_P1024TO2047_COUNT(x)         (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P1024TO2047_COUNT_SHIFT)) & ENET_RMON_R_P1024TO2047_COUNT_MASK)

/*! @name RMON_R_P_GTE2048 - Rx Packets Greater than 2048 Bytes Statistic Register */
#define ENET_RMON_R_P_GTE2048_COUNT_MASK         (0xFFFFU)
#define ENET_RMON_R_P_GTE2048_COUNT_SHIFT        (0U)
#define ENET_RMON_R_P_GTE2048_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_P_GTE2048_COUNT_SHIFT)) & ENET_RMON_R_P_GTE2048_COUNT_MASK)

/*! @name RMON_R_OCTETS - Rx Octets Statistic Register */
#define ENET_RMON_R_OCTETS_COUNT_MASK            (0xFFFFFFFFU)
#define ENET_RMON_R_OCTETS_COUNT_SHIFT           (0U)
#define ENET_RMON_R_OCTETS_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_RMON_R_OCTETS_COUNT_SHIFT)) & ENET_RMON_R_OCTETS_COUNT_MASK)

/*! @name IEEE_R_DROP - Frames not Counted Correctly Statistic Register */
#define ENET_IEEE_R_DROP_COUNT_MASK              (0xFFFFU)
#define ENET_IEEE_R_DROP_COUNT_SHIFT             (0U)
#define ENET_IEEE_R_DROP_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_DROP_COUNT_SHIFT)) & ENET_IEEE_R_DROP_COUNT_MASK)

/*! @name IEEE_R_FRAME_OK - Frames Received OK Statistic Register */
#define ENET_IEEE_R_FRAME_OK_COUNT_MASK          (0xFFFFU)
#define ENET_IEEE_R_FRAME_OK_COUNT_SHIFT         (0U)
#define ENET_IEEE_R_FRAME_OK_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_FRAME_OK_COUNT_SHIFT)) & ENET_IEEE_R_FRAME_OK_COUNT_MASK)

/*! @name IEEE_R_CRC - Frames Received with CRC Error Statistic Register */
#define ENET_IEEE_R_CRC_COUNT_MASK               (0xFFFFU)
#define ENET_IEEE_R_CRC_COUNT_SHIFT              (0U)
#define ENET_IEEE_R_CRC_COUNT(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_CRC_COUNT_SHIFT)) & ENET_IEEE_R_CRC_COUNT_MASK)

/*! @name IEEE_R_ALIGN - Frames Received with Alignment Error Statistic Register */
#define ENET_IEEE_R_ALIGN_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_R_ALIGN_COUNT_SHIFT            (0U)
#define ENET_IEEE_R_ALIGN_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_ALIGN_COUNT_SHIFT)) & ENET_IEEE_R_ALIGN_COUNT_MASK)

/*! @name IEEE_R_MACERR - Receive FIFO Overflow Count Statistic Register */
#define ENET_IEEE_R_MACERR_COUNT_MASK            (0xFFFFU)
#define ENET_IEEE_R_MACERR_COUNT_SHIFT           (0U)
#define ENET_IEEE_R_MACERR_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_MACERR_COUNT_SHIFT)) & ENET_IEEE_R_MACERR_COUNT_MASK)

/*! @name IEEE_R_FDXFC - Flow Control Pause Frames Received Statistic Register */
#define ENET_IEEE_R_FDXFC_COUNT_MASK             (0xFFFFU)
#define ENET_IEEE_R_FDXFC_COUNT_SHIFT            (0U)
#define ENET_IEEE_R_FDXFC_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_FDXFC_COUNT_SHIFT)) & ENET_IEEE_R_FDXFC_COUNT_MASK)

/*! @name IEEE_R_OCTETS_OK - Octet Count for Frames Received without Error Statistic Register */
#define ENET_IEEE_R_OCTETS_OK_COUNT_MASK         (0xFFFFFFFFU)
#define ENET_IEEE_R_OCTETS_OK_COUNT_SHIFT        (0U)
#define ENET_IEEE_R_OCTETS_OK_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_IEEE_R_OCTETS_OK_COUNT_SHIFT)) & ENET_IEEE_R_OCTETS_OK_COUNT_MASK)

/*! @name ATCR - Adjustable Timer Control Register */
#define ENET_ATCR_EN_MASK                        (0x1U)
#define ENET_ATCR_EN_SHIFT                       (0U)
#define ENET_ATCR_EN(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_EN_SHIFT)) & ENET_ATCR_EN_MASK)
#define ENET_ATCR_OFFEN_MASK                     (0x4U)
#define ENET_ATCR_OFFEN_SHIFT                    (2U)
#define ENET_ATCR_OFFEN(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_OFFEN_SHIFT)) & ENET_ATCR_OFFEN_MASK)
#define ENET_ATCR_OFFRST_MASK                    (0x8U)
#define ENET_ATCR_OFFRST_SHIFT                   (3U)
#define ENET_ATCR_OFFRST(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_OFFRST_SHIFT)) & ENET_ATCR_OFFRST_MASK)
#define ENET_ATCR_PEREN_MASK                     (0x10U)
#define ENET_ATCR_PEREN_SHIFT                    (4U)
#define ENET_ATCR_PEREN(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_PEREN_SHIFT)) & ENET_ATCR_PEREN_MASK)
#define ENET_ATCR_PINPER_MASK                    (0x80U)
#define ENET_ATCR_PINPER_SHIFT                   (7U)
#define ENET_ATCR_PINPER(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_PINPER_SHIFT)) & ENET_ATCR_PINPER_MASK)
#define ENET_ATCR_RESTART_MASK                   (0x200U)
#define ENET_ATCR_RESTART_SHIFT                  (9U)
#define ENET_ATCR_RESTART(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_RESTART_SHIFT)) & ENET_ATCR_RESTART_MASK)
#define ENET_ATCR_CAPTURE_MASK                   (0x800U)
#define ENET_ATCR_CAPTURE_SHIFT                  (11U)
#define ENET_ATCR_CAPTURE(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_CAPTURE_SHIFT)) & ENET_ATCR_CAPTURE_MASK)
#define ENET_ATCR_SLAVE_MASK                     (0x2000U)
#define ENET_ATCR_SLAVE_SHIFT                    (13U)
#define ENET_ATCR_SLAVE(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATCR_SLAVE_SHIFT)) & ENET_ATCR_SLAVE_MASK)

/*! @name ATVR - Timer Value Register */
#define ENET_ATVR_ATIME_MASK                     (0xFFFFFFFFU)
#define ENET_ATVR_ATIME_SHIFT                    (0U)
#define ENET_ATVR_ATIME(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_ATVR_ATIME_SHIFT)) & ENET_ATVR_ATIME_MASK)

/*! @name ATOFF - Timer Offset Register */
#define ENET_ATOFF_OFFSET_MASK                   (0xFFFFFFFFU)
#define ENET_ATOFF_OFFSET_SHIFT                  (0U)
#define ENET_ATOFF_OFFSET(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATOFF_OFFSET_SHIFT)) & ENET_ATOFF_OFFSET_MASK)

/*! @name ATPER - Timer Period Register */
#define ENET_ATPER_PERIOD_MASK                   (0xFFFFFFFFU)
#define ENET_ATPER_PERIOD_SHIFT                  (0U)
#define ENET_ATPER_PERIOD(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_ATPER_PERIOD_SHIFT)) & ENET_ATPER_PERIOD_MASK)

/*! @name ATCOR - Timer Correction Register */
#define ENET_ATCOR_COR_MASK                      (0x7FFFFFFFU)
#define ENET_ATCOR_COR_SHIFT                     (0U)
#define ENET_ATCOR_COR(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ATCOR_COR_SHIFT)) & ENET_ATCOR_COR_MASK)

/*! @name ATINC - Time-Stamping Clock Period Register */
#define ENET_ATINC_INC_MASK                      (0x7FU)
#define ENET_ATINC_INC_SHIFT                     (0U)
#define ENET_ATINC_INC(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_ATINC_INC_SHIFT)) & ENET_ATINC_INC_MASK)
#define ENET_ATINC_INC_CORR_MASK                 (0x7F00U)
#define ENET_ATINC_INC_CORR_SHIFT                (8U)
#define ENET_ATINC_INC_CORR(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_ATINC_INC_CORR_SHIFT)) & ENET_ATINC_INC_CORR_MASK)

/*! @name ATSTMP - Timestamp of Last Transmitted Frame */
#define ENET_ATSTMP_TIMESTAMP_MASK               (0xFFFFFFFFU)
#define ENET_ATSTMP_TIMESTAMP_SHIFT              (0U)
#define ENET_ATSTMP_TIMESTAMP(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_ATSTMP_TIMESTAMP_SHIFT)) & ENET_ATSTMP_TIMESTAMP_MASK)

/*! @name TGSR - Timer Global Status Register */
#define ENET_TGSR_TF0_MASK                       (0x1U)
#define ENET_TGSR_TF0_SHIFT                      (0U)
#define ENET_TGSR_TF0(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF0_SHIFT)) & ENET_TGSR_TF0_MASK)
#define ENET_TGSR_TF1_MASK                       (0x2U)
#define ENET_TGSR_TF1_SHIFT                      (1U)
#define ENET_TGSR_TF1(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF1_SHIFT)) & ENET_TGSR_TF1_MASK)
#define ENET_TGSR_TF2_MASK                       (0x4U)
#define ENET_TGSR_TF2_SHIFT                      (2U)
#define ENET_TGSR_TF2(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF2_SHIFT)) & ENET_TGSR_TF2_MASK)
#define ENET_TGSR_TF3_MASK                       (0x8U)
#define ENET_TGSR_TF3_SHIFT                      (3U)
#define ENET_TGSR_TF3(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TGSR_TF3_SHIFT)) & ENET_TGSR_TF3_MASK)

/*! @name TCSR - Timer Control Status Register */
#define ENET_TCSR_TDRE_MASK                      (0x1U)
#define ENET_TCSR_TDRE_SHIFT                     (0U)
#define ENET_TCSR_TDRE(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TDRE_SHIFT)) & ENET_TCSR_TDRE_MASK)
#define ENET_TCSR_TMODE_MASK                     (0x3CU)
#define ENET_TCSR_TMODE_SHIFT                    (2U)
#define ENET_TCSR_TMODE(x)                       (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TMODE_SHIFT)) & ENET_TCSR_TMODE_MASK)
#define ENET_TCSR_TIE_MASK                       (0x40U)
#define ENET_TCSR_TIE_SHIFT                      (6U)
#define ENET_TCSR_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TIE_SHIFT)) & ENET_TCSR_TIE_MASK)
#define ENET_TCSR_TF_MASK                        (0x80U)
#define ENET_TCSR_TF_SHIFT                       (7U)
#define ENET_TCSR_TF(x)                          (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TF_SHIFT)) & ENET_TCSR_TF_MASK)
#define ENET_TCSR_TPWC_MASK                      (0xF800U)
#define ENET_TCSR_TPWC_SHIFT                     (11U)
#define ENET_TCSR_TPWC(x)                        (((uint32_t)(((uint32_t)(x)) << ENET_TCSR_TPWC_SHIFT)) & ENET_TCSR_TPWC_MASK)

/* The count of ENET_TCSR */
#define ENET_TCSR_COUNT                          (4U)

/*! @name TCCR - Timer Compare Capture Register */
#define ENET_TCCR_TCC_MASK                       (0xFFFFFFFFU)
#define ENET_TCCR_TCC_SHIFT                      (0U)
#define ENET_TCCR_TCC(x)                         (((uint32_t)(((uint32_t)(x)) << ENET_TCCR_TCC_SHIFT)) & ENET_TCCR_TCC_MASK)

/* The count of ENET_TCCR */
#define ENET_TCCR_COUNT                          (4U)


/*!
 * @}
 */ /* end of group ENET_Register_Masks */


/* ENET - Peripheral instance base addresses */
/** Peripheral ENET1 base address */
#define ENET1_BASE                               (0x2188000u)
/** Peripheral ENET1 base pointer */
#define ENET1                                    ((ENET_Type *)ENET1_BASE)
/** Peripheral ENET2 base address */
#define ENET2_BASE                               (0x20B4000u)
/** Peripheral ENET2 base pointer */
#define ENET2                                    ((ENET_Type *)ENET2_BASE)
/** Array initializer of ENET peripheral base addresses */
#define ENET_BASE_ADDRS                          { 0u, ENET1_BASE, ENET2_BASE }
/** Array initializer of ENET peripheral base pointers */
#define ENET_BASE_PTRS                           { (ENET_Type *)0u, ENET1, ENET2 }
/** Interrupt vectors for the ENET peripheral type */
#define ENET_Transmit_IRQS                       { NotAvail_IRQn, ENET1_IRQn, ENET2_IRQn }
#define ENET_Receive_IRQS                        { NotAvail_IRQn, ENET1_IRQn, ENET2_IRQn }
#define ENET_Error_IRQS                          { NotAvail_IRQn, ENET1_IRQn, ENET2_IRQn }
#define ENET_1588_Timer_IRQS                     { NotAvail_IRQn, ENET1_IRQn, ENET2_IRQn }
/* ENET Buffer Descriptor and Buffer Address Alignment. */
#define ENET_BUFF_ALIGNMENT                      (64U)


/*!
 * @}
 */ /* end of group ENET_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- OCOTP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OCOTP_Peripheral_Access_Layer OCOTP Peripheral Access Layer
 * @{
 */

/** OCOTP - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< OTP Controller Control Register, offset: 0x0 */
  __IO uint32_t CTRL_SET;                          /**< OTP Controller Control Register, offset: 0x4 */
  __IO uint32_t CTRL_CLR;                          /**< OTP Controller Control Register, offset: 0x8 */
  __IO uint32_t CTRL_TOG;                          /**< OTP Controller Control Register, offset: 0xC */
  __IO uint32_t TIMING;                            /**< OTP Controller Timing Register, offset: 0x10 */
       uint8_t RESERVED_0[12];
  __IO uint32_t DATA;                              /**< OTP Controller Write Data Register, offset: 0x20 */
       uint8_t RESERVED_1[12];
  __IO uint32_t READ_CTRL;                         /**< OTP Controller Read Control Register, offset: 0x30 */
       uint8_t RESERVED_2[12];
  __IO uint32_t READ_FUSE_DATA;                    /**< OTP Controller Read Fuse Data Register, offset: 0x40 */
       uint8_t RESERVED_3[12];
  __IO uint32_t SW_STICKY;                         /**< Sticky bit Register, offset: 0x50 */
       uint8_t RESERVED_4[12];
  __IO uint32_t SCS;                               /**< Software Controllable Signals Register, offset: 0x60 */
  __IO uint32_t SCS_SET;                           /**< Software Controllable Signals Register, offset: 0x64 */
  __IO uint32_t SCS_CLR;                           /**< Software Controllable Signals Register, offset: 0x68 */
  __IO uint32_t SCS_TOG;                           /**< Software Controllable Signals Register, offset: 0x6C */
  __IO uint32_t CRC_ADDR;                          /**< OTP Controller CRC Test Address, offset: 0x70 */
       uint8_t RESERVED_5[12];
  __IO uint32_t CRC_VALUE;                         /**< OTP Controller CRC Value Register, offset: 0x80 */
       uint8_t RESERVED_6[12];
  __I  uint32_t VERSION;                           /**< OTP Controller Version Register, offset: 0x90 */
       uint8_t RESERVED_7[108];
  __IO uint32_t TIMING2;                           /**< OTP Controller Timing Register 2, offset: 0x100 */
       uint8_t RESERVED_8[764];
  __IO uint32_t LOCK;                              /**< Value of OTP Bank0 Word0 (Lock controls), offset: 0x400 */
       uint8_t RESERVED_9[12];
  __IO uint32_t CFG0;                              /**< Value of OTP Bank0 Word1 (Configuration and Manufacturing Info.), offset: 0x410 */
       uint8_t RESERVED_10[12];
  __IO uint32_t CFG1;                              /**< Value of OTP Bank0 Word2 (Configuration and Manufacturing Info.), offset: 0x420 */
       uint8_t RESERVED_11[12];
  __IO uint32_t CFG2;                              /**< Value of OTP Bank0 Word3 (Configuration and Manufacturing Info.), offset: 0x430 */
       uint8_t RESERVED_12[12];
  __IO uint32_t CFG3;                              /**< Value of OTP Bank0 Word4 (Configuration and Manufacturing Info.), offset: 0x440 */
       uint8_t RESERVED_13[12];
  __IO uint32_t CFG4;                              /**< Value of OTP Bank0 Word5 (Configuration and Manufacturing Info.), offset: 0x450 */
       uint8_t RESERVED_14[12];
  __IO uint32_t CFG5;                              /**< Value of OTP Bank0 Word6 (Configuration and Manufacturing Info.), offset: 0x460 */
       uint8_t RESERVED_15[12];
  __IO uint32_t CFG6;                              /**< Value of OTP Bank0 Word7 (Configuration and Manufacturing Info.), offset: 0x470 */
       uint8_t RESERVED_16[12];
  __IO uint32_t MEM0;                              /**< Value of OTP Bank1 Word0 (Memory Related Info.), offset: 0x480 */
       uint8_t RESERVED_17[12];
  __IO uint32_t MEM1;                              /**< Value of OTP Bank1 Word1 (Memory Related Info.), offset: 0x490 */
       uint8_t RESERVED_18[12];
  __IO uint32_t MEM2;                              /**< Value of OTP Bank1 Word2 (Memory Related Info.), offset: 0x4A0 */
       uint8_t RESERVED_19[12];
  __IO uint32_t MEM3;                              /**< Value of OTP Bank1 Word3 (Memory Related Info.), offset: 0x4B0 */
       uint8_t RESERVED_20[12];
  __IO uint32_t MEM4;                              /**< Value of OTP Bank1 Word4 (Memory Related Info.), offset: 0x4C0 */
       uint8_t RESERVED_21[12];
  __IO uint32_t ANA0;                              /**< Value of OTP Bank1 Word5 (Memory Related Info.), offset: 0x4D0 */
       uint8_t RESERVED_22[12];
  __IO uint32_t ANA1;                              /**< Value of OTP Bank1 Word6 (General Purpose Customer Defined Info.), offset: 0x4E0 */
       uint8_t RESERVED_23[12];
  __IO uint32_t ANA2;                              /**< Value of OTP Bank1 Word7 (General Purpose Customer Defined Info.), offset: 0x4F0 */
       uint8_t RESERVED_24[12];
  __IO uint32_t OTPMK0;                            /**< Value of OTP Bank2 Word0 (OTPMK Key), offset: 0x500 */
       uint8_t RESERVED_25[12];
  __IO uint32_t OTPMK1;                            /**< Value of OTP Bank2 Word1 (OTPMK Key), offset: 0x510 */
       uint8_t RESERVED_26[12];
  __IO uint32_t OTPMK2;                            /**< Value of OTP Bank2 Word2 (OTPMK Key), offset: 0x520 */
       uint8_t RESERVED_27[12];
  __IO uint32_t OTPMK3;                            /**< Value of OTP Bank2 Word3 (OTPMK Key), offset: 0x530 */
       uint8_t RESERVED_28[12];
  __IO uint32_t OTPMK4;                            /**< Value of OTP Bank2 Word4 (OTPMK Key), offset: 0x540 */
       uint8_t RESERVED_29[12];
  __IO uint32_t OTPMK5;                            /**< Value of OTP Bank2 Word5 (OTPMK Key), offset: 0x550 */
       uint8_t RESERVED_30[12];
  __IO uint32_t OTPMK6;                            /**< Value of OTP Bank2 Word6 (OTPMK Key), offset: 0x560 */
       uint8_t RESERVED_31[12];
  __IO uint32_t OTPMK7;                            /**< Value of OTP Bank2 Word7 (OTPMK Key), offset: 0x570 */
       uint8_t RESERVED_32[12];
  __IO uint32_t SRK0;                              /**< Shadow Register for OTP Bank3 Word0 (SRK Hash), offset: 0x580 */
       uint8_t RESERVED_33[12];
  __IO uint32_t SRK1;                              /**< Shadow Register for OTP Bank3 Word1 (SRK Hash), offset: 0x590 */
       uint8_t RESERVED_34[12];
  __IO uint32_t SRK2;                              /**< Shadow Register for OTP Bank3 Word2 (SRK Hash), offset: 0x5A0 */
       uint8_t RESERVED_35[12];
  __IO uint32_t SRK3;                              /**< Shadow Register for OTP Bank3 Word3 (SRK Hash), offset: 0x5B0 */
       uint8_t RESERVED_36[12];
  __IO uint32_t SRK4;                              /**< Shadow Register for OTP Bank3 Word4 (SRK Hash), offset: 0x5C0 */
       uint8_t RESERVED_37[12];
  __IO uint32_t SRK5;                              /**< Shadow Register for OTP Bank3 Word5 (SRK Hash), offset: 0x5D0 */
       uint8_t RESERVED_38[12];
  __IO uint32_t SRK6;                              /**< Shadow Register for OTP Bank3 Word6 (SRK Hash), offset: 0x5E0 */
       uint8_t RESERVED_39[12];
  __IO uint32_t SRK7;                              /**< Shadow Register for OTP Bank3 Word7 (SRK Hash), offset: 0x5F0 */
       uint8_t RESERVED_40[12];
  __IO uint32_t SJC_RESP0;                         /**< Value of OTP Bank4 Word0 (Secure JTAG Response Field), offset: 0x600 */
       uint8_t RESERVED_41[12];
  __IO uint32_t SJC_RESP1;                         /**< Value of OTP Bank4 Word1 (Secure JTAG Response Field), offset: 0x610 */
       uint8_t RESERVED_42[12];
  __IO uint32_t MAC0;                              /**< Value of OTP Bank4 Word2 (MAC Address), offset: 0x620 */
       uint8_t RESERVED_43[12];
  __IO uint32_t MAC1;                              /**< Value of OTP Bank4 Word3 (MAC Address), offset: 0x630 */
       uint8_t RESERVED_44[12];
  __IO uint32_t MAC;                               /**< Value of OTP Bank4 Word4 (MAC Address) (OCOTP_RESERVED), offset: 0x640 */
       uint8_t RESERVED_45[12];
  __IO uint32_t CRC;                               /**< Value of OTP Bank4 Word5 (CRC Key), offset: 0x650 */
       uint8_t RESERVED_46[12];
  __IO uint32_t GP1;                               /**< Value of OTP Bank4 Word6 (General Purpose Customer Defined Info), offset: 0x660 */
       uint8_t RESERVED_47[12];
  __IO uint32_t GP2;                               /**< Value of OTP Bank4 Word7 (General Purpose Customer Defined Info), offset: 0x670 */
       uint8_t RESERVED_48[12];
  __IO uint32_t SW_GP0;                            /**< Value of OTP Bank5 Word0 (SW GP), offset: 0x680 */
       uint8_t RESERVED_49[12];
  __IO uint32_t SW_GP1;                            /**< Value of OTP Bank5 Word1 (SW GP), offset: 0x690 */
       uint8_t RESERVED_50[12];
  __IO uint32_t SW_GP2;                            /**< Value of OTP Bank5 Word2 (SW GP), offset: 0x6A0 */
       uint8_t RESERVED_51[12];
  __IO uint32_t SW_GP3;                            /**< Value of OTP Bank5 Word3 (SW GP), offset: 0x6B0 */
       uint8_t RESERVED_52[12];
  __IO uint32_t SW_GP4;                            /**< Value of OTP Bank5 Word4 (SW GP), offset: 0x6C0 */
       uint8_t RESERVED_53[12];
  __IO uint32_t MISC_CONF;                         /**< Value of OTP Bank5 Word5 (Misc Conf), offset: 0x6D0 */
       uint8_t RESERVED_54[12];
  __IO uint32_t FIELD_RETURN;                      /**< Value of OTP Bank5 Word6 (Field Return), offset: 0x6E0 */
       uint8_t RESERVED_55[12];
  __IO uint32_t SRK_REVOKE;                        /**< Value of OTP Bank5 Word7 (SRK Revoke), offset: 0x6F0 */
       uint8_t RESERVED_56[268];
  __IO uint32_t ROM_PATCH0;                        /**< Value of OTP Bank6 Word0 (ROM Patch), offset: 0x800 */
       uint8_t RESERVED_57[12];
  __IO uint32_t ROM_PATCH1;                        /**< Value of OTP Bank6 Word1 (ROM Patch), offset: 0x810 */
       uint8_t RESERVED_58[12];
  __IO uint32_t ROM_PATCH2;                        /**< Value of OTP Bank6 Word2 (ROM Patch), offset: 0x820 */
       uint8_t RESERVED_59[12];
  __IO uint32_t ROM_PATCH3;                        /**< Value of OTP Bank6 Word3 (ROM Patch), offset: 0x830 */
       uint8_t RESERVED_60[12];
  __IO uint32_t ROM_PATCH4;                        /**< Value of OTP Bank6 Word4 (ROM Patch), offset: 0x840 */
       uint8_t RESERVED_61[12];
  __IO uint32_t ROM_PATCH5;                        /**< Value of OTP Bank6 Word5 (ROM Patch), offset: 0x850 */
       uint8_t RESERVED_62[12];
  __IO uint32_t ROM_PATCH6;                        /**< Value of OTP Bank6 Word6 (ROM Patch), offset: 0x860 */
       uint8_t RESERVED_63[12];
  __IO uint32_t ROM_PATCH7;                        /**< Value of OTP Bank6 Word7 (ROM Patch), offset: 0x870 */
       uint8_t RESERVED_64[12];
  __IO uint32_t GP3_0;                             /**< Value of OTP Bank7 Word0 (General Purpose Customer Defined Info), offset: 0x880 */
       uint8_t RESERVED_65[12];
  __IO uint32_t GP3_1;                             /**< Value of OTP Bank7 Word1 (General Purpose Customer Defined Info), offset: 0x890 */
       uint8_t RESERVED_66[12];
  __IO uint32_t GP3_2;                             /**< Value of OTP Bank7 Word2 (General Purpose Customer Defined Info), offset: 0x8A0 */
       uint8_t RESERVED_67[12];
  __IO uint32_t GP3_3;                             /**< Value of OTP Bank7 Word3 (General Purpose Customer Defined Info), offset: 0x8B0 */
       uint8_t RESERVED_68[12];
  __IO uint32_t GP3_4;                             /**< Value of OTP Bank8 Word4 (General Purpose Customer Defined Info), offset: 0x8C0 */
       uint8_t RESERVED_69[12];
  __IO uint32_t GP4_0;                             /**< Value of OTP Bank7 Word5 (General Purpose Customer Defined Info), offset: 0x8D0 */
       uint8_t RESERVED_70[12];
  __IO uint32_t GP4_1;                             /**< Value of OTP Bank7 Word6 (General Purpose Customer Defined Info), offset: 0x8E0 */
       uint8_t RESERVED_71[12];
  __IO uint32_t GP4_2;                             /**< Value of OTP Bank7 Word7 (General Purpose Customer Defined Info), offset: 0x8F0 */
} OCOTP_Type;

/* ----------------------------------------------------------------------------
   -- OCOTP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OCOTP_Register_Masks OCOTP Register Masks
 * @{
 */

/*! @name CTRL - OTP Controller Control Register */
#define OCOTP_CTRL_ADDR_MASK                     (0x7FU)
#define OCOTP_CTRL_ADDR_SHIFT                    (0U)
#define OCOTP_CTRL_ADDR(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_ADDR_SHIFT)) & OCOTP_CTRL_ADDR_MASK)
#define OCOTP_CTRL_RSVD0_MASK                    (0x80U)
#define OCOTP_CTRL_RSVD0_SHIFT                   (7U)
#define OCOTP_CTRL_RSVD0(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_RSVD0_SHIFT)) & OCOTP_CTRL_RSVD0_MASK)
#define OCOTP_CTRL_BUSY_MASK                     (0x100U)
#define OCOTP_CTRL_BUSY_SHIFT                    (8U)
#define OCOTP_CTRL_BUSY(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_BUSY_SHIFT)) & OCOTP_CTRL_BUSY_MASK)
#define OCOTP_CTRL_ERROR_MASK                    (0x200U)
#define OCOTP_CTRL_ERROR_SHIFT                   (9U)
#define OCOTP_CTRL_ERROR(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_ERROR_SHIFT)) & OCOTP_CTRL_ERROR_MASK)
#define OCOTP_CTRL_RELOAD_SHADOWS_MASK           (0x400U)
#define OCOTP_CTRL_RELOAD_SHADOWS_SHIFT          (10U)
#define OCOTP_CTRL_RELOAD_SHADOWS(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_RELOAD_SHADOWS_MASK)
#define OCOTP_CTRL_CRC_TEST_MASK                 (0x800U)
#define OCOTP_CTRL_CRC_TEST_SHIFT                (11U)
#define OCOTP_CTRL_CRC_TEST(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CRC_TEST_SHIFT)) & OCOTP_CTRL_CRC_TEST_MASK)
#define OCOTP_CTRL_CRC_FAIL_MASK                 (0x1000U)
#define OCOTP_CTRL_CRC_FAIL_SHIFT                (12U)
#define OCOTP_CTRL_CRC_FAIL(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CRC_FAIL_SHIFT)) & OCOTP_CTRL_CRC_FAIL_MASK)
#define OCOTP_CTRL_RSVD1_MASK                    (0xE000U)
#define OCOTP_CTRL_RSVD1_SHIFT                   (13U)
#define OCOTP_CTRL_RSVD1(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_RSVD1_SHIFT)) & OCOTP_CTRL_RSVD1_MASK)
#define OCOTP_CTRL_WR_UNLOCK_MASK                (0xFFFF0000U)
#define OCOTP_CTRL_WR_UNLOCK_SHIFT               (16U)
#define OCOTP_CTRL_WR_UNLOCK(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_WR_UNLOCK_MASK)

/*! @name CTRL_SET - OTP Controller Control Register */
#define OCOTP_CTRL_SET_ADDR_MASK                 (0x7FU)
#define OCOTP_CTRL_SET_ADDR_SHIFT                (0U)
#define OCOTP_CTRL_SET_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_ADDR_SHIFT)) & OCOTP_CTRL_SET_ADDR_MASK)
#define OCOTP_CTRL_SET_RSVD0_MASK                (0x80U)
#define OCOTP_CTRL_SET_RSVD0_SHIFT               (7U)
#define OCOTP_CTRL_SET_RSVD0(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_RSVD0_SHIFT)) & OCOTP_CTRL_SET_RSVD0_MASK)
#define OCOTP_CTRL_SET_BUSY_MASK                 (0x100U)
#define OCOTP_CTRL_SET_BUSY_SHIFT                (8U)
#define OCOTP_CTRL_SET_BUSY(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_BUSY_SHIFT)) & OCOTP_CTRL_SET_BUSY_MASK)
#define OCOTP_CTRL_SET_ERROR_MASK                (0x200U)
#define OCOTP_CTRL_SET_ERROR_SHIFT               (9U)
#define OCOTP_CTRL_SET_ERROR(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_ERROR_SHIFT)) & OCOTP_CTRL_SET_ERROR_MASK)
#define OCOTP_CTRL_SET_RELOAD_SHADOWS_MASK       (0x400U)
#define OCOTP_CTRL_SET_RELOAD_SHADOWS_SHIFT      (10U)
#define OCOTP_CTRL_SET_RELOAD_SHADOWS(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_SET_RELOAD_SHADOWS_MASK)
#define OCOTP_CTRL_SET_CRC_TEST_MASK             (0x800U)
#define OCOTP_CTRL_SET_CRC_TEST_SHIFT            (11U)
#define OCOTP_CTRL_SET_CRC_TEST(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_CRC_TEST_SHIFT)) & OCOTP_CTRL_SET_CRC_TEST_MASK)
#define OCOTP_CTRL_SET_CRC_FAIL_MASK             (0x1000U)
#define OCOTP_CTRL_SET_CRC_FAIL_SHIFT            (12U)
#define OCOTP_CTRL_SET_CRC_FAIL(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_CRC_FAIL_SHIFT)) & OCOTP_CTRL_SET_CRC_FAIL_MASK)
#define OCOTP_CTRL_SET_RSVD1_MASK                (0xE000U)
#define OCOTP_CTRL_SET_RSVD1_SHIFT               (13U)
#define OCOTP_CTRL_SET_RSVD1(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_RSVD1_SHIFT)) & OCOTP_CTRL_SET_RSVD1_MASK)
#define OCOTP_CTRL_SET_WR_UNLOCK_MASK            (0xFFFF0000U)
#define OCOTP_CTRL_SET_WR_UNLOCK_SHIFT           (16U)
#define OCOTP_CTRL_SET_WR_UNLOCK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_SET_WR_UNLOCK_MASK)

/*! @name CTRL_CLR - OTP Controller Control Register */
#define OCOTP_CTRL_CLR_ADDR_MASK                 (0x7FU)
#define OCOTP_CTRL_CLR_ADDR_SHIFT                (0U)
#define OCOTP_CTRL_CLR_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_ADDR_SHIFT)) & OCOTP_CTRL_CLR_ADDR_MASK)
#define OCOTP_CTRL_CLR_RSVD0_MASK                (0x80U)
#define OCOTP_CTRL_CLR_RSVD0_SHIFT               (7U)
#define OCOTP_CTRL_CLR_RSVD0(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_RSVD0_SHIFT)) & OCOTP_CTRL_CLR_RSVD0_MASK)
#define OCOTP_CTRL_CLR_BUSY_MASK                 (0x100U)
#define OCOTP_CTRL_CLR_BUSY_SHIFT                (8U)
#define OCOTP_CTRL_CLR_BUSY(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_BUSY_SHIFT)) & OCOTP_CTRL_CLR_BUSY_MASK)
#define OCOTP_CTRL_CLR_ERROR_MASK                (0x200U)
#define OCOTP_CTRL_CLR_ERROR_SHIFT               (9U)
#define OCOTP_CTRL_CLR_ERROR(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_ERROR_SHIFT)) & OCOTP_CTRL_CLR_ERROR_MASK)
#define OCOTP_CTRL_CLR_RELOAD_SHADOWS_MASK       (0x400U)
#define OCOTP_CTRL_CLR_RELOAD_SHADOWS_SHIFT      (10U)
#define OCOTP_CTRL_CLR_RELOAD_SHADOWS(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_CLR_RELOAD_SHADOWS_MASK)
#define OCOTP_CTRL_CLR_CRC_TEST_MASK             (0x800U)
#define OCOTP_CTRL_CLR_CRC_TEST_SHIFT            (11U)
#define OCOTP_CTRL_CLR_CRC_TEST(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_CRC_TEST_SHIFT)) & OCOTP_CTRL_CLR_CRC_TEST_MASK)
#define OCOTP_CTRL_CLR_CRC_FAIL_MASK             (0x1000U)
#define OCOTP_CTRL_CLR_CRC_FAIL_SHIFT            (12U)
#define OCOTP_CTRL_CLR_CRC_FAIL(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_CRC_FAIL_SHIFT)) & OCOTP_CTRL_CLR_CRC_FAIL_MASK)
#define OCOTP_CTRL_CLR_RSVD1_MASK                (0xE000U)
#define OCOTP_CTRL_CLR_RSVD1_SHIFT               (13U)
#define OCOTP_CTRL_CLR_RSVD1(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_RSVD1_SHIFT)) & OCOTP_CTRL_CLR_RSVD1_MASK)
#define OCOTP_CTRL_CLR_WR_UNLOCK_MASK            (0xFFFF0000U)
#define OCOTP_CTRL_CLR_WR_UNLOCK_SHIFT           (16U)
#define OCOTP_CTRL_CLR_WR_UNLOCK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_CLR_WR_UNLOCK_MASK)

/*! @name CTRL_TOG - OTP Controller Control Register */
#define OCOTP_CTRL_TOG_ADDR_MASK                 (0x7FU)
#define OCOTP_CTRL_TOG_ADDR_SHIFT                (0U)
#define OCOTP_CTRL_TOG_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_ADDR_SHIFT)) & OCOTP_CTRL_TOG_ADDR_MASK)
#define OCOTP_CTRL_TOG_RSVD0_MASK                (0x80U)
#define OCOTP_CTRL_TOG_RSVD0_SHIFT               (7U)
#define OCOTP_CTRL_TOG_RSVD0(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_RSVD0_SHIFT)) & OCOTP_CTRL_TOG_RSVD0_MASK)
#define OCOTP_CTRL_TOG_BUSY_MASK                 (0x100U)
#define OCOTP_CTRL_TOG_BUSY_SHIFT                (8U)
#define OCOTP_CTRL_TOG_BUSY(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_BUSY_SHIFT)) & OCOTP_CTRL_TOG_BUSY_MASK)
#define OCOTP_CTRL_TOG_ERROR_MASK                (0x200U)
#define OCOTP_CTRL_TOG_ERROR_SHIFT               (9U)
#define OCOTP_CTRL_TOG_ERROR(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_ERROR_SHIFT)) & OCOTP_CTRL_TOG_ERROR_MASK)
#define OCOTP_CTRL_TOG_RELOAD_SHADOWS_MASK       (0x400U)
#define OCOTP_CTRL_TOG_RELOAD_SHADOWS_SHIFT      (10U)
#define OCOTP_CTRL_TOG_RELOAD_SHADOWS(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_TOG_RELOAD_SHADOWS_MASK)
#define OCOTP_CTRL_TOG_CRC_TEST_MASK             (0x800U)
#define OCOTP_CTRL_TOG_CRC_TEST_SHIFT            (11U)
#define OCOTP_CTRL_TOG_CRC_TEST(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_CRC_TEST_SHIFT)) & OCOTP_CTRL_TOG_CRC_TEST_MASK)
#define OCOTP_CTRL_TOG_CRC_FAIL_MASK             (0x1000U)
#define OCOTP_CTRL_TOG_CRC_FAIL_SHIFT            (12U)
#define OCOTP_CTRL_TOG_CRC_FAIL(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_CRC_FAIL_SHIFT)) & OCOTP_CTRL_TOG_CRC_FAIL_MASK)
#define OCOTP_CTRL_TOG_RSVD1_MASK                (0xE000U)
#define OCOTP_CTRL_TOG_RSVD1_SHIFT               (13U)
#define OCOTP_CTRL_TOG_RSVD1(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_RSVD1_SHIFT)) & OCOTP_CTRL_TOG_RSVD1_MASK)
#define OCOTP_CTRL_TOG_WR_UNLOCK_MASK            (0xFFFF0000U)
#define OCOTP_CTRL_TOG_WR_UNLOCK_SHIFT           (16U)
#define OCOTP_CTRL_TOG_WR_UNLOCK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_TOG_WR_UNLOCK_MASK)

/*! @name TIMING - OTP Controller Timing Register */
#define OCOTP_TIMING_STROBE_PROG_MASK            (0xFFFU)
#define OCOTP_TIMING_STROBE_PROG_SHIFT           (0U)
#define OCOTP_TIMING_STROBE_PROG(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING_STROBE_PROG_SHIFT)) & OCOTP_TIMING_STROBE_PROG_MASK)
#define OCOTP_TIMING_RELAX_MASK                  (0xF000U)
#define OCOTP_TIMING_RELAX_SHIFT                 (12U)
#define OCOTP_TIMING_RELAX(x)                    (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING_RELAX_SHIFT)) & OCOTP_TIMING_RELAX_MASK)
#define OCOTP_TIMING_STROBE_READ_MASK            (0x3F0000U)
#define OCOTP_TIMING_STROBE_READ_SHIFT           (16U)
#define OCOTP_TIMING_STROBE_READ(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING_STROBE_READ_SHIFT)) & OCOTP_TIMING_STROBE_READ_MASK)
#define OCOTP_TIMING_WAIT_MASK                   (0xFC00000U)
#define OCOTP_TIMING_WAIT_SHIFT                  (22U)
#define OCOTP_TIMING_WAIT(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING_WAIT_SHIFT)) & OCOTP_TIMING_WAIT_MASK)
#define OCOTP_TIMING_RSRVD0_MASK                 (0xF0000000U)
#define OCOTP_TIMING_RSRVD0_SHIFT                (28U)
#define OCOTP_TIMING_RSRVD0(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING_RSRVD0_SHIFT)) & OCOTP_TIMING_RSRVD0_MASK)

/*! @name DATA - OTP Controller Write Data Register */
#define OCOTP_DATA_DATA_MASK                     (0xFFFFFFFFU)
#define OCOTP_DATA_DATA_SHIFT                    (0U)
#define OCOTP_DATA_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_DATA_DATA_SHIFT)) & OCOTP_DATA_DATA_MASK)

/*! @name READ_CTRL - OTP Controller Read Control Register */
#define OCOTP_READ_CTRL_READ_FUSE_MASK           (0x1U)
#define OCOTP_READ_CTRL_READ_FUSE_SHIFT          (0U)
#define OCOTP_READ_CTRL_READ_FUSE(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_CTRL_READ_FUSE_SHIFT)) & OCOTP_READ_CTRL_READ_FUSE_MASK)
#define OCOTP_READ_CTRL_RSVD0_MASK               (0xFFFFFFFEU)
#define OCOTP_READ_CTRL_RSVD0_SHIFT              (1U)
#define OCOTP_READ_CTRL_RSVD0(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_CTRL_RSVD0_SHIFT)) & OCOTP_READ_CTRL_RSVD0_MASK)

/*! @name READ_FUSE_DATA - OTP Controller Read Fuse Data Register */
#define OCOTP_READ_FUSE_DATA_DATA_MASK           (0xFFFFFFFFU)
#define OCOTP_READ_FUSE_DATA_DATA_SHIFT          (0U)
#define OCOTP_READ_FUSE_DATA_DATA(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_FUSE_DATA_DATA_SHIFT)) & OCOTP_READ_FUSE_DATA_DATA_MASK)

/*! @name SW_STICKY - Sticky bit Register */
#define OCOTP_SW_STICKY_SRK_REVOKE_LOCK_MASK     (0x2U)
#define OCOTP_SW_STICKY_SRK_REVOKE_LOCK_SHIFT    (1U)
#define OCOTP_SW_STICKY_SRK_REVOKE_LOCK(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_STICKY_SRK_REVOKE_LOCK_SHIFT)) & OCOTP_SW_STICKY_SRK_REVOKE_LOCK_MASK)
#define OCOTP_SW_STICKY_FIELD_RETURN_LOCK_MASK   (0x4U)
#define OCOTP_SW_STICKY_FIELD_RETURN_LOCK_SHIFT  (2U)
#define OCOTP_SW_STICKY_FIELD_RETURN_LOCK(x)     (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_STICKY_FIELD_RETURN_LOCK_SHIFT)) & OCOTP_SW_STICKY_FIELD_RETURN_LOCK_MASK)
#define OCOTP_SW_STICKY_RSVD0_MASK               (0xFFFFFFE0U)
#define OCOTP_SW_STICKY_RSVD0_SHIFT              (5U)
#define OCOTP_SW_STICKY_RSVD0(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_STICKY_RSVD0_SHIFT)) & OCOTP_SW_STICKY_RSVD0_MASK)

/*! @name SCS - Software Controllable Signals Register */
#define OCOTP_SCS_HAB_JDE_MASK                   (0x1U)
#define OCOTP_SCS_HAB_JDE_SHIFT                  (0U)
#define OCOTP_SCS_HAB_JDE(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_HAB_JDE_SHIFT)) & OCOTP_SCS_HAB_JDE_MASK)
#define OCOTP_SCS_SPARE_MASK                     (0x7FFFFFFEU)
#define OCOTP_SCS_SPARE_SHIFT                    (1U)
#define OCOTP_SCS_SPARE(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_SPARE_SHIFT)) & OCOTP_SCS_SPARE_MASK)
#define OCOTP_SCS_LOCK_MASK                      (0x80000000U)
#define OCOTP_SCS_LOCK_SHIFT                     (31U)
#define OCOTP_SCS_LOCK(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_LOCK_SHIFT)) & OCOTP_SCS_LOCK_MASK)

/*! @name SCS_SET - Software Controllable Signals Register */
#define OCOTP_SCS_SET_HAB_JDE_MASK               (0x1U)
#define OCOTP_SCS_SET_HAB_JDE_SHIFT              (0U)
#define OCOTP_SCS_SET_HAB_JDE(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_SET_HAB_JDE_SHIFT)) & OCOTP_SCS_SET_HAB_JDE_MASK)
#define OCOTP_SCS_SET_SPARE_MASK                 (0x7FFFFFFEU)
#define OCOTP_SCS_SET_SPARE_SHIFT                (1U)
#define OCOTP_SCS_SET_SPARE(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_SET_SPARE_SHIFT)) & OCOTP_SCS_SET_SPARE_MASK)
#define OCOTP_SCS_SET_LOCK_MASK                  (0x80000000U)
#define OCOTP_SCS_SET_LOCK_SHIFT                 (31U)
#define OCOTP_SCS_SET_LOCK(x)                    (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_SET_LOCK_SHIFT)) & OCOTP_SCS_SET_LOCK_MASK)

/*! @name SCS_CLR - Software Controllable Signals Register */
#define OCOTP_SCS_CLR_HAB_JDE_MASK               (0x1U)
#define OCOTP_SCS_CLR_HAB_JDE_SHIFT              (0U)
#define OCOTP_SCS_CLR_HAB_JDE(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_CLR_HAB_JDE_SHIFT)) & OCOTP_SCS_CLR_HAB_JDE_MASK)
#define OCOTP_SCS_CLR_SPARE_MASK                 (0x7FFFFFFEU)
#define OCOTP_SCS_CLR_SPARE_SHIFT                (1U)
#define OCOTP_SCS_CLR_SPARE(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_CLR_SPARE_SHIFT)) & OCOTP_SCS_CLR_SPARE_MASK)
#define OCOTP_SCS_CLR_LOCK_MASK                  (0x80000000U)
#define OCOTP_SCS_CLR_LOCK_SHIFT                 (31U)
#define OCOTP_SCS_CLR_LOCK(x)                    (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_CLR_LOCK_SHIFT)) & OCOTP_SCS_CLR_LOCK_MASK)

/*! @name SCS_TOG - Software Controllable Signals Register */
#define OCOTP_SCS_TOG_HAB_JDE_MASK               (0x1U)
#define OCOTP_SCS_TOG_HAB_JDE_SHIFT              (0U)
#define OCOTP_SCS_TOG_HAB_JDE(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_TOG_HAB_JDE_SHIFT)) & OCOTP_SCS_TOG_HAB_JDE_MASK)
#define OCOTP_SCS_TOG_SPARE_MASK                 (0x7FFFFFFEU)
#define OCOTP_SCS_TOG_SPARE_SHIFT                (1U)
#define OCOTP_SCS_TOG_SPARE(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_TOG_SPARE_SHIFT)) & OCOTP_SCS_TOG_SPARE_MASK)
#define OCOTP_SCS_TOG_LOCK_MASK                  (0x80000000U)
#define OCOTP_SCS_TOG_LOCK_SHIFT                 (31U)
#define OCOTP_SCS_TOG_LOCK(x)                    (((uint32_t)(((uint32_t)(x)) << OCOTP_SCS_TOG_LOCK_SHIFT)) & OCOTP_SCS_TOG_LOCK_MASK)

/*! @name CRC_ADDR - OTP Controller CRC Test Address */
#define OCOTP_CRC_ADDR_DATA_START_ADDR_MASK      (0xFFU)
#define OCOTP_CRC_ADDR_DATA_START_ADDR_SHIFT     (0U)
#define OCOTP_CRC_ADDR_DATA_START_ADDR(x)        (((uint32_t)(((uint32_t)(x)) << OCOTP_CRC_ADDR_DATA_START_ADDR_SHIFT)) & OCOTP_CRC_ADDR_DATA_START_ADDR_MASK)
#define OCOTP_CRC_ADDR_DATA_END_ADDR_MASK        (0xFF00U)
#define OCOTP_CRC_ADDR_DATA_END_ADDR_SHIFT       (8U)
#define OCOTP_CRC_ADDR_DATA_END_ADDR(x)          (((uint32_t)(((uint32_t)(x)) << OCOTP_CRC_ADDR_DATA_END_ADDR_SHIFT)) & OCOTP_CRC_ADDR_DATA_END_ADDR_MASK)
#define OCOTP_CRC_ADDR_CRC_ADDR_MASK             (0x70000U)
#define OCOTP_CRC_ADDR_CRC_ADDR_SHIFT            (16U)
#define OCOTP_CRC_ADDR_CRC_ADDR(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CRC_ADDR_CRC_ADDR_SHIFT)) & OCOTP_CRC_ADDR_CRC_ADDR_MASK)
#define OCOTP_CRC_ADDR_OTPMK_CRC_MASK            (0x80000U)
#define OCOTP_CRC_ADDR_OTPMK_CRC_SHIFT           (19U)
#define OCOTP_CRC_ADDR_OTPMK_CRC(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_CRC_ADDR_OTPMK_CRC_SHIFT)) & OCOTP_CRC_ADDR_OTPMK_CRC_MASK)
#define OCOTP_CRC_ADDR_RSVD0_MASK                (0xFFF00000U)
#define OCOTP_CRC_ADDR_RSVD0_SHIFT               (20U)
#define OCOTP_CRC_ADDR_RSVD0(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CRC_ADDR_RSVD0_SHIFT)) & OCOTP_CRC_ADDR_RSVD0_MASK)

/*! @name CRC_VALUE - OTP Controller CRC Value Register */
#define OCOTP_CRC_VALUE_DATA_MASK                (0xFFFFFFFFU)
#define OCOTP_CRC_VALUE_DATA_SHIFT               (0U)
#define OCOTP_CRC_VALUE_DATA(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CRC_VALUE_DATA_SHIFT)) & OCOTP_CRC_VALUE_DATA_MASK)

/*! @name VERSION - OTP Controller Version Register */
#define OCOTP_VERSION_STEP_MASK                  (0xFFFFU)
#define OCOTP_VERSION_STEP_SHIFT                 (0U)
#define OCOTP_VERSION_STEP(x)                    (((uint32_t)(((uint32_t)(x)) << OCOTP_VERSION_STEP_SHIFT)) & OCOTP_VERSION_STEP_MASK)
#define OCOTP_VERSION_MINOR_MASK                 (0xFF0000U)
#define OCOTP_VERSION_MINOR_SHIFT                (16U)
#define OCOTP_VERSION_MINOR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_VERSION_MINOR_SHIFT)) & OCOTP_VERSION_MINOR_MASK)
#define OCOTP_VERSION_MAJOR_MASK                 (0xFF000000U)
#define OCOTP_VERSION_MAJOR_SHIFT                (24U)
#define OCOTP_VERSION_MAJOR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_VERSION_MAJOR_SHIFT)) & OCOTP_VERSION_MAJOR_MASK)

/*! @name TIMING2 - OTP Controller Timing Register 2 */
#define OCOTP_TIMING2_RELAX_PROG_MASK            (0xFFFU)
#define OCOTP_TIMING2_RELAX_PROG_SHIFT           (0U)
#define OCOTP_TIMING2_RELAX_PROG(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING2_RELAX_PROG_SHIFT)) & OCOTP_TIMING2_RELAX_PROG_MASK)
#define OCOTP_TIMING2_RELAX_READ_MASK            (0x3F0000U)
#define OCOTP_TIMING2_RELAX_READ_SHIFT           (16U)
#define OCOTP_TIMING2_RELAX_READ(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING2_RELAX_READ_SHIFT)) & OCOTP_TIMING2_RELAX_READ_MASK)
#define OCOTP_TIMING2_RELAX1_MASK                (0x1FC00000U)
#define OCOTP_TIMING2_RELAX1_SHIFT               (22U)
#define OCOTP_TIMING2_RELAX1(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_TIMING2_RELAX1_SHIFT)) & OCOTP_TIMING2_RELAX1_MASK)

/*! @name LOCK - Value of OTP Bank0 Word0 (Lock controls) */
#define OCOTP_LOCK_TESTER_MASK                   (0x3U)
#define OCOTP_LOCK_TESTER_SHIFT                  (0U)
#define OCOTP_LOCK_TESTER(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_TESTER_SHIFT)) & OCOTP_LOCK_TESTER_MASK)
#define OCOTP_LOCK_BOOT_CFG_MASK                 (0xCU)
#define OCOTP_LOCK_BOOT_CFG_SHIFT                (2U)
#define OCOTP_LOCK_BOOT_CFG(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_BOOT_CFG_SHIFT)) & OCOTP_LOCK_BOOT_CFG_MASK)
#define OCOTP_LOCK_MEM_TRIM_MASK                 (0x30U)
#define OCOTP_LOCK_MEM_TRIM_SHIFT                (4U)
#define OCOTP_LOCK_MEM_TRIM(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_MEM_TRIM_SHIFT)) & OCOTP_LOCK_MEM_TRIM_MASK)
#define OCOTP_LOCK_SJC_RESP_MASK                 (0x40U)
#define OCOTP_LOCK_SJC_RESP_SHIFT                (6U)
#define OCOTP_LOCK_SJC_RESP(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_SJC_RESP_SHIFT)) & OCOTP_LOCK_SJC_RESP_MASK)
#define OCOTP_LOCK_RSVD0_MASK                    (0x80U)
#define OCOTP_LOCK_RSVD0_SHIFT                   (7U)
#define OCOTP_LOCK_RSVD0(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_RSVD0_SHIFT)) & OCOTP_LOCK_RSVD0_MASK)
#define OCOTP_LOCK_MAC_ADDR_MASK                 (0x300U)
#define OCOTP_LOCK_MAC_ADDR_SHIFT                (8U)
#define OCOTP_LOCK_MAC_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_MAC_ADDR_SHIFT)) & OCOTP_LOCK_MAC_ADDR_MASK)
#define OCOTP_LOCK_GP1_MASK                      (0xC00U)
#define OCOTP_LOCK_GP1_SHIFT                     (10U)
#define OCOTP_LOCK_GP1(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_GP1_SHIFT)) & OCOTP_LOCK_GP1_MASK)
#define OCOTP_LOCK_GP2_MASK                      (0x3000U)
#define OCOTP_LOCK_GP2_SHIFT                     (12U)
#define OCOTP_LOCK_GP2(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_GP2_SHIFT)) & OCOTP_LOCK_GP2_MASK)
#define OCOTP_LOCK_SRK_MASK                      (0x4000U)
#define OCOTP_LOCK_SRK_SHIFT                     (14U)
#define OCOTP_LOCK_SRK(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_SRK_SHIFT)) & OCOTP_LOCK_SRK_MASK)
#define OCOTP_LOCK_GP3_MASK                      (0x8000U)
#define OCOTP_LOCK_GP3_SHIFT                     (15U)
#define OCOTP_LOCK_GP3(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_GP3_SHIFT)) & OCOTP_LOCK_GP3_MASK)
#define OCOTP_LOCK_SW_GP_MASK                    (0x10000U)
#define OCOTP_LOCK_SW_GP_SHIFT                   (16U)
#define OCOTP_LOCK_SW_GP(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_SW_GP_SHIFT)) & OCOTP_LOCK_SW_GP_MASK)
#define OCOTP_LOCK_OTPMK_MASK                    (0x20000U)
#define OCOTP_LOCK_OTPMK_SHIFT                   (17U)
#define OCOTP_LOCK_OTPMK(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_OTPMK_SHIFT)) & OCOTP_LOCK_OTPMK_MASK)
#define OCOTP_LOCK_ANALOG_MASK                   (0xC0000U)
#define OCOTP_LOCK_ANALOG_SHIFT                  (18U)
#define OCOTP_LOCK_ANALOG(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_ANALOG_SHIFT)) & OCOTP_LOCK_ANALOG_MASK)
#define OCOTP_LOCK_OTPMK_CRC_MASK                (0x100000U)
#define OCOTP_LOCK_OTPMK_CRC_SHIFT               (20U)
#define OCOTP_LOCK_OTPMK_CRC(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_OTPMK_CRC_SHIFT)) & OCOTP_LOCK_OTPMK_CRC_MASK)
#define OCOTP_LOCK_ROM_PATCH_MASK                (0x200000U)
#define OCOTP_LOCK_ROM_PATCH_SHIFT               (21U)
#define OCOTP_LOCK_ROM_PATCH(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_ROM_PATCH_SHIFT)) & OCOTP_LOCK_ROM_PATCH_MASK)
#define OCOTP_LOCK_MISC_CONF_MASK                (0x400000U)
#define OCOTP_LOCK_MISC_CONF_SHIFT               (22U)
#define OCOTP_LOCK_MISC_CONF(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_MISC_CONF_SHIFT)) & OCOTP_LOCK_MISC_CONF_MASK)
#define OCOTP_LOCK_GP4_MASK                      (0x800000U)
#define OCOTP_LOCK_GP4_SHIFT                     (23U)
#define OCOTP_LOCK_GP4(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_GP4_SHIFT)) & OCOTP_LOCK_GP4_MASK)
#define OCOTP_LOCK_PIN_MASK                      (0x2000000U)
#define OCOTP_LOCK_PIN_SHIFT                     (25U)
#define OCOTP_LOCK_PIN(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_PIN_SHIFT)) & OCOTP_LOCK_PIN_MASK)
#define OCOTP_LOCK_GP4_RLOCK_MASK                (0x40000000U)
#define OCOTP_LOCK_GP4_RLOCK_SHIFT               (30U)
#define OCOTP_LOCK_GP4_RLOCK(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_GP4_RLOCK_SHIFT)) & OCOTP_LOCK_GP4_RLOCK_MASK)
#define OCOTP_LOCK_GP3_RLOCK_MASK                (0x80000000U)
#define OCOTP_LOCK_GP3_RLOCK_SHIFT               (31U)
#define OCOTP_LOCK_GP3_RLOCK(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCK_GP3_RLOCK_SHIFT)) & OCOTP_LOCK_GP3_RLOCK_MASK)

/*! @name CFG0 - Value of OTP Bank0 Word1 (Configuration and Manufacturing Info.) */
#define OCOTP_CFG0_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_CFG0_BITS_SHIFT                    (0U)
#define OCOTP_CFG0_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CFG0_BITS_SHIFT)) & OCOTP_CFG0_BITS_MASK)

/*! @name CFG1 - Value of OTP Bank0 Word2 (Configuration and Manufacturing Info.) */
#define OCOTP_CFG1_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_CFG1_BITS_SHIFT                    (0U)
#define OCOTP_CFG1_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CFG1_BITS_SHIFT)) & OCOTP_CFG1_BITS_MASK)

/*! @name CFG2 - Value of OTP Bank0 Word3 (Configuration and Manufacturing Info.) */
#define OCOTP_CFG2_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_CFG2_BITS_SHIFT                    (0U)
#define OCOTP_CFG2_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CFG2_BITS_SHIFT)) & OCOTP_CFG2_BITS_MASK)

/*! @name CFG3 - Value of OTP Bank0 Word4 (Configuration and Manufacturing Info.) */
#define OCOTP_CFG3_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_CFG3_BITS_SHIFT                    (0U)
#define OCOTP_CFG3_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CFG3_BITS_SHIFT)) & OCOTP_CFG3_BITS_MASK)

/*! @name CFG4 - Value of OTP Bank0 Word5 (Configuration and Manufacturing Info.) */
#define OCOTP_CFG4_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_CFG4_BITS_SHIFT                    (0U)
#define OCOTP_CFG4_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CFG4_BITS_SHIFT)) & OCOTP_CFG4_BITS_MASK)

/*! @name CFG5 - Value of OTP Bank0 Word6 (Configuration and Manufacturing Info.) */
#define OCOTP_CFG5_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_CFG5_BITS_SHIFT                    (0U)
#define OCOTP_CFG5_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CFG5_BITS_SHIFT)) & OCOTP_CFG5_BITS_MASK)

/*! @name CFG6 - Value of OTP Bank0 Word7 (Configuration and Manufacturing Info.) */
#define OCOTP_CFG6_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_CFG6_BITS_SHIFT                    (0U)
#define OCOTP_CFG6_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CFG6_BITS_SHIFT)) & OCOTP_CFG6_BITS_MASK)

/*! @name MEM0 - Value of OTP Bank1 Word0 (Memory Related Info.) */
#define OCOTP_MEM0_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_MEM0_BITS_SHIFT                    (0U)
#define OCOTP_MEM0_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_MEM0_BITS_SHIFT)) & OCOTP_MEM0_BITS_MASK)

/*! @name MEM1 - Value of OTP Bank1 Word1 (Memory Related Info.) */
#define OCOTP_MEM1_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_MEM1_BITS_SHIFT                    (0U)
#define OCOTP_MEM1_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_MEM1_BITS_SHIFT)) & OCOTP_MEM1_BITS_MASK)

/*! @name MEM2 - Value of OTP Bank1 Word2 (Memory Related Info.) */
#define OCOTP_MEM2_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_MEM2_BITS_SHIFT                    (0U)
#define OCOTP_MEM2_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_MEM2_BITS_SHIFT)) & OCOTP_MEM2_BITS_MASK)

/*! @name MEM3 - Value of OTP Bank1 Word3 (Memory Related Info.) */
#define OCOTP_MEM3_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_MEM3_BITS_SHIFT                    (0U)
#define OCOTP_MEM3_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_MEM3_BITS_SHIFT)) & OCOTP_MEM3_BITS_MASK)

/*! @name MEM4 - Value of OTP Bank1 Word4 (Memory Related Info.) */
#define OCOTP_MEM4_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_MEM4_BITS_SHIFT                    (0U)
#define OCOTP_MEM4_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_MEM4_BITS_SHIFT)) & OCOTP_MEM4_BITS_MASK)

/*! @name ANA0 - Value of OTP Bank1 Word5 (Memory Related Info.) */
#define OCOTP_ANA0_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_ANA0_BITS_SHIFT                    (0U)
#define OCOTP_ANA0_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_ANA0_BITS_SHIFT)) & OCOTP_ANA0_BITS_MASK)

/*! @name ANA1 - Value of OTP Bank1 Word6 (General Purpose Customer Defined Info.) */
#define OCOTP_ANA1_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_ANA1_BITS_SHIFT                    (0U)
#define OCOTP_ANA1_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_ANA1_BITS_SHIFT)) & OCOTP_ANA1_BITS_MASK)

/*! @name ANA2 - Value of OTP Bank1 Word7 (General Purpose Customer Defined Info.) */
#define OCOTP_ANA2_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_ANA2_BITS_SHIFT                    (0U)
#define OCOTP_ANA2_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_ANA2_BITS_SHIFT)) & OCOTP_ANA2_BITS_MASK)

/*! @name OTPMK0 - Value of OTP Bank2 Word0 (OTPMK Key) */
#define OCOTP_OTPMK0_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK0_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK0_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK0_BITS_SHIFT)) & OCOTP_OTPMK0_BITS_MASK)

/*! @name OTPMK1 - Value of OTP Bank2 Word1 (OTPMK Key) */
#define OCOTP_OTPMK1_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK1_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK1_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK1_BITS_SHIFT)) & OCOTP_OTPMK1_BITS_MASK)

/*! @name OTPMK2 - Value of OTP Bank2 Word2 (OTPMK Key) */
#define OCOTP_OTPMK2_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK2_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK2_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK2_BITS_SHIFT)) & OCOTP_OTPMK2_BITS_MASK)

/*! @name OTPMK3 - Value of OTP Bank2 Word3 (OTPMK Key) */
#define OCOTP_OTPMK3_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK3_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK3_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK3_BITS_SHIFT)) & OCOTP_OTPMK3_BITS_MASK)

/*! @name OTPMK4 - Value of OTP Bank2 Word4 (OTPMK Key) */
#define OCOTP_OTPMK4_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK4_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK4_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK4_BITS_SHIFT)) & OCOTP_OTPMK4_BITS_MASK)

/*! @name OTPMK5 - Value of OTP Bank2 Word5 (OTPMK Key) */
#define OCOTP_OTPMK5_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK5_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK5_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK5_BITS_SHIFT)) & OCOTP_OTPMK5_BITS_MASK)

/*! @name OTPMK6 - Value of OTP Bank2 Word6 (OTPMK Key) */
#define OCOTP_OTPMK6_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK6_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK6_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK6_BITS_SHIFT)) & OCOTP_OTPMK6_BITS_MASK)

/*! @name OTPMK7 - Value of OTP Bank2 Word7 (OTPMK Key) */
#define OCOTP_OTPMK7_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_OTPMK7_BITS_SHIFT                  (0U)
#define OCOTP_OTPMK7_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_OTPMK7_BITS_SHIFT)) & OCOTP_OTPMK7_BITS_MASK)

/*! @name SRK0 - Shadow Register for OTP Bank3 Word0 (SRK Hash) */
#define OCOTP_SRK0_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK0_BITS_SHIFT                    (0U)
#define OCOTP_SRK0_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK0_BITS_SHIFT)) & OCOTP_SRK0_BITS_MASK)

/*! @name SRK1 - Shadow Register for OTP Bank3 Word1 (SRK Hash) */
#define OCOTP_SRK1_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK1_BITS_SHIFT                    (0U)
#define OCOTP_SRK1_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK1_BITS_SHIFT)) & OCOTP_SRK1_BITS_MASK)

/*! @name SRK2 - Shadow Register for OTP Bank3 Word2 (SRK Hash) */
#define OCOTP_SRK2_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK2_BITS_SHIFT                    (0U)
#define OCOTP_SRK2_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK2_BITS_SHIFT)) & OCOTP_SRK2_BITS_MASK)

/*! @name SRK3 - Shadow Register for OTP Bank3 Word3 (SRK Hash) */
#define OCOTP_SRK3_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK3_BITS_SHIFT                    (0U)
#define OCOTP_SRK3_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK3_BITS_SHIFT)) & OCOTP_SRK3_BITS_MASK)

/*! @name SRK4 - Shadow Register for OTP Bank3 Word4 (SRK Hash) */
#define OCOTP_SRK4_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK4_BITS_SHIFT                    (0U)
#define OCOTP_SRK4_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK4_BITS_SHIFT)) & OCOTP_SRK4_BITS_MASK)

/*! @name SRK5 - Shadow Register for OTP Bank3 Word5 (SRK Hash) */
#define OCOTP_SRK5_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK5_BITS_SHIFT                    (0U)
#define OCOTP_SRK5_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK5_BITS_SHIFT)) & OCOTP_SRK5_BITS_MASK)

/*! @name SRK6 - Shadow Register for OTP Bank3 Word6 (SRK Hash) */
#define OCOTP_SRK6_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK6_BITS_SHIFT                    (0U)
#define OCOTP_SRK6_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK6_BITS_SHIFT)) & OCOTP_SRK6_BITS_MASK)

/*! @name SRK7 - Shadow Register for OTP Bank3 Word7 (SRK Hash) */
#define OCOTP_SRK7_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_SRK7_BITS_SHIFT                    (0U)
#define OCOTP_SRK7_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK7_BITS_SHIFT)) & OCOTP_SRK7_BITS_MASK)

/*! @name SJC_RESP0 - Value of OTP Bank4 Word0 (Secure JTAG Response Field) */
#define OCOTP_SJC_RESP0_BITS_MASK                (0xFFFFFFFFU)
#define OCOTP_SJC_RESP0_BITS_SHIFT               (0U)
#define OCOTP_SJC_RESP0_BITS(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_SJC_RESP0_BITS_SHIFT)) & OCOTP_SJC_RESP0_BITS_MASK)

/*! @name SJC_RESP1 - Value of OTP Bank4 Word1 (Secure JTAG Response Field) */
#define OCOTP_SJC_RESP1_BITS_MASK                (0xFFFFFFFFU)
#define OCOTP_SJC_RESP1_BITS_SHIFT               (0U)
#define OCOTP_SJC_RESP1_BITS(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_SJC_RESP1_BITS_SHIFT)) & OCOTP_SJC_RESP1_BITS_MASK)

/*! @name MAC0 - Value of OTP Bank4 Word2 (MAC Address) */
#define OCOTP_MAC0_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_MAC0_BITS_SHIFT                    (0U)
#define OCOTP_MAC0_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_MAC0_BITS_SHIFT)) & OCOTP_MAC0_BITS_MASK)

/*! @name MAC1 - Value of OTP Bank4 Word3 (MAC Address) */
#define OCOTP_MAC1_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_MAC1_BITS_SHIFT                    (0U)
#define OCOTP_MAC1_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_MAC1_BITS_SHIFT)) & OCOTP_MAC1_BITS_MASK)

/*! @name MAC - Value of OTP Bank4 Word4 (MAC Address) (OCOTP_RESERVED) */
#define OCOTP_MAC_BITS_MASK                      (0xFFFFFFFFU)
#define OCOTP_MAC_BITS_SHIFT                     (0U)
#define OCOTP_MAC_BITS(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_MAC_BITS_SHIFT)) & OCOTP_MAC_BITS_MASK)

/*! @name CRC - Value of OTP Bank4 Word5 (CRC Key) */
#define OCOTP_CRC_BITS_MASK                      (0xFFFFFFFFU)
#define OCOTP_CRC_BITS_SHIFT                     (0U)
#define OCOTP_CRC_BITS(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_CRC_BITS_SHIFT)) & OCOTP_CRC_BITS_MASK)

/*! @name GP1 - Value of OTP Bank4 Word6 (General Purpose Customer Defined Info) */
#define OCOTP_GP1_BITS_MASK                      (0xFFFFFFFFU)
#define OCOTP_GP1_BITS_SHIFT                     (0U)
#define OCOTP_GP1_BITS(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_GP1_BITS_SHIFT)) & OCOTP_GP1_BITS_MASK)

/*! @name GP2 - Value of OTP Bank4 Word7 (General Purpose Customer Defined Info) */
#define OCOTP_GP2_BITS_MASK                      (0xFFFFFFFFU)
#define OCOTP_GP2_BITS_SHIFT                     (0U)
#define OCOTP_GP2_BITS(x)                        (((uint32_t)(((uint32_t)(x)) << OCOTP_GP2_BITS_SHIFT)) & OCOTP_GP2_BITS_MASK)

/*! @name SW_GP0 - Value of OTP Bank5 Word0 (SW GP) */
#define OCOTP_SW_GP0_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_SW_GP0_BITS_SHIFT                  (0U)
#define OCOTP_SW_GP0_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_GP0_BITS_SHIFT)) & OCOTP_SW_GP0_BITS_MASK)

/*! @name SW_GP1 - Value of OTP Bank5 Word1 (SW GP) */
#define OCOTP_SW_GP1_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_SW_GP1_BITS_SHIFT                  (0U)
#define OCOTP_SW_GP1_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_GP1_BITS_SHIFT)) & OCOTP_SW_GP1_BITS_MASK)

/*! @name SW_GP2 - Value of OTP Bank5 Word2 (SW GP) */
#define OCOTP_SW_GP2_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_SW_GP2_BITS_SHIFT                  (0U)
#define OCOTP_SW_GP2_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_GP2_BITS_SHIFT)) & OCOTP_SW_GP2_BITS_MASK)

/*! @name SW_GP3 - Value of OTP Bank5 Word3 (SW GP) */
#define OCOTP_SW_GP3_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_SW_GP3_BITS_SHIFT                  (0U)
#define OCOTP_SW_GP3_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_GP3_BITS_SHIFT)) & OCOTP_SW_GP3_BITS_MASK)

/*! @name SW_GP4 - Value of OTP Bank5 Word4 (SW GP) */
#define OCOTP_SW_GP4_BITS_MASK                   (0xFFFFFFFFU)
#define OCOTP_SW_GP4_BITS_SHIFT                  (0U)
#define OCOTP_SW_GP4_BITS(x)                     (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_GP4_BITS_SHIFT)) & OCOTP_SW_GP4_BITS_MASK)

/*! @name MISC_CONF - Value of OTP Bank5 Word5 (Misc Conf) */
#define OCOTP_MISC_CONF_BITS_MASK                (0xFFFFFFFFU)
#define OCOTP_MISC_CONF_BITS_SHIFT               (0U)
#define OCOTP_MISC_CONF_BITS(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_MISC_CONF_BITS_SHIFT)) & OCOTP_MISC_CONF_BITS_MASK)

/*! @name FIELD_RETURN - Value of OTP Bank5 Word6 (Field Return) */
#define OCOTP_FIELD_RETURN_BITS_MASK             (0xFFFFFFFFU)
#define OCOTP_FIELD_RETURN_BITS_SHIFT            (0U)
#define OCOTP_FIELD_RETURN_BITS(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_FIELD_RETURN_BITS_SHIFT)) & OCOTP_FIELD_RETURN_BITS_MASK)

/*! @name SRK_REVOKE - Value of OTP Bank5 Word7 (SRK Revoke) */
#define OCOTP_SRK_REVOKE_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_SRK_REVOKE_BITS_SHIFT              (0U)
#define OCOTP_SRK_REVOKE_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_SRK_REVOKE_BITS_SHIFT)) & OCOTP_SRK_REVOKE_BITS_MASK)

/*! @name ROM_PATCH0 - Value of OTP Bank6 Word0 (ROM Patch) */
#define OCOTP_ROM_PATCH0_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH0_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH0_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH0_BITS_SHIFT)) & OCOTP_ROM_PATCH0_BITS_MASK)

/*! @name ROM_PATCH1 - Value of OTP Bank6 Word1 (ROM Patch) */
#define OCOTP_ROM_PATCH1_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH1_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH1_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH1_BITS_SHIFT)) & OCOTP_ROM_PATCH1_BITS_MASK)

/*! @name ROM_PATCH2 - Value of OTP Bank6 Word2 (ROM Patch) */
#define OCOTP_ROM_PATCH2_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH2_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH2_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH2_BITS_SHIFT)) & OCOTP_ROM_PATCH2_BITS_MASK)

/*! @name ROM_PATCH3 - Value of OTP Bank6 Word3 (ROM Patch) */
#define OCOTP_ROM_PATCH3_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH3_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH3_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH3_BITS_SHIFT)) & OCOTP_ROM_PATCH3_BITS_MASK)

/*! @name ROM_PATCH4 - Value of OTP Bank6 Word4 (ROM Patch) */
#define OCOTP_ROM_PATCH4_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH4_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH4_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH4_BITS_SHIFT)) & OCOTP_ROM_PATCH4_BITS_MASK)

/*! @name ROM_PATCH5 - Value of OTP Bank6 Word5 (ROM Patch) */
#define OCOTP_ROM_PATCH5_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH5_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH5_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH5_BITS_SHIFT)) & OCOTP_ROM_PATCH5_BITS_MASK)

/*! @name ROM_PATCH6 - Value of OTP Bank6 Word6 (ROM Patch) */
#define OCOTP_ROM_PATCH6_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH6_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH6_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH6_BITS_SHIFT)) & OCOTP_ROM_PATCH6_BITS_MASK)

/*! @name ROM_PATCH7 - Value of OTP Bank6 Word7 (ROM Patch) */
#define OCOTP_ROM_PATCH7_BITS_MASK               (0xFFFFFFFFU)
#define OCOTP_ROM_PATCH7_BITS_SHIFT              (0U)
#define OCOTP_ROM_PATCH7_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_ROM_PATCH7_BITS_SHIFT)) & OCOTP_ROM_PATCH7_BITS_MASK)

/*! @name GP3_0 - Value of OTP Bank7 Word0 (General Purpose Customer Defined Info) */
#define OCOTP_GP3_0_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP3_0_BITS_SHIFT                   (0U)
#define OCOTP_GP3_0_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP3_0_BITS_SHIFT)) & OCOTP_GP3_0_BITS_MASK)

/*! @name GP3_1 - Value of OTP Bank7 Word1 (General Purpose Customer Defined Info) */
#define OCOTP_GP3_1_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP3_1_BITS_SHIFT                   (0U)
#define OCOTP_GP3_1_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP3_1_BITS_SHIFT)) & OCOTP_GP3_1_BITS_MASK)

/*! @name GP3_2 - Value of OTP Bank7 Word2 (General Purpose Customer Defined Info) */
#define OCOTP_GP3_2_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP3_2_BITS_SHIFT                   (0U)
#define OCOTP_GP3_2_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP3_2_BITS_SHIFT)) & OCOTP_GP3_2_BITS_MASK)

/*! @name GP3_3 - Value of OTP Bank7 Word3 (General Purpose Customer Defined Info) */
#define OCOTP_GP3_3_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP3_3_BITS_SHIFT                   (0U)
#define OCOTP_GP3_3_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP3_3_BITS_SHIFT)) & OCOTP_GP3_3_BITS_MASK)

/*! @name GP3_4 - Value of OTP Bank8 Word4 (General Purpose Customer Defined Info) */
#define OCOTP_GP3_4_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP3_4_BITS_SHIFT                   (0U)
#define OCOTP_GP3_4_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP3_4_BITS_SHIFT)) & OCOTP_GP3_4_BITS_MASK)

/*! @name GP4_0 - Value of OTP Bank7 Word5 (General Purpose Customer Defined Info) */
#define OCOTP_GP4_0_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP4_0_BITS_SHIFT                   (0U)
#define OCOTP_GP4_0_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP4_0_BITS_SHIFT)) & OCOTP_GP4_0_BITS_MASK)

/*! @name GP4_1 - Value of OTP Bank7 Word6 (General Purpose Customer Defined Info) */
#define OCOTP_GP4_1_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP4_1_BITS_SHIFT                   (0U)
#define OCOTP_GP4_1_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP4_1_BITS_SHIFT)) & OCOTP_GP4_1_BITS_MASK)

/*! @name GP4_2 - Value of OTP Bank7 Word7 (General Purpose Customer Defined Info) */
#define OCOTP_GP4_2_BITS_MASK                    (0xFFFFFFFFU)
#define OCOTP_GP4_2_BITS_SHIFT                   (0U)
#define OCOTP_GP4_2_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_GP4_2_BITS_SHIFT)) & OCOTP_GP4_2_BITS_MASK)


/*!
 * @}
 */ /* end of group OCOTP_Register_Masks */


/* OCOTP - Peripheral instance base addresses */
/** Peripheral OCOTP base address */
#define OCOTP_BASE                               (0x21BC000u)
/** Peripheral OCOTP base pointer */
#define OCOTP                                    ((OCOTP_Type *)OCOTP_BASE)
/** Array initializer of OCOTP peripheral base addresses */
#define OCOTP_BASE_ADDRS                         { OCOTP_BASE }
/** Array initializer of OCOTP peripheral base pointers */
#define OCOTP_BASE_PTRS                          { OCOTP }

/*!
 * @}
 */ /* end of group OCOTP_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t DR;                                /**< GPIO data register, offset: 0x0 */
  __IO uint32_t GDIR;                              /**< GPIO direction register, offset: 0x4 */
  __I  uint32_t PSR;                               /**< GPIO pad status register, offset: 0x8 */
  __IO uint32_t ICR1;                              /**< GPIO interrupt configuration register1, offset: 0xC */
  __IO uint32_t ICR2;                              /**< GPIO interrupt configuration register2, offset: 0x10 */
  __IO uint32_t IMR;                               /**< GPIO interrupt mask register, offset: 0x14 */
  __IO uint32_t ISR;                               /**< GPIO interrupt status register, offset: 0x18 */
  __IO uint32_t EDGE_SEL;                          /**< GPIO edge select register, offset: 0x1C */
} GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name DR - GPIO data register */
#define GPIO_DR_DR_MASK                          (0xFFFFFFFFU)
#define GPIO_DR_DR_SHIFT                         (0U)
#define GPIO_DR_DR(x)                            (((uint32_t)(((uint32_t)(x)) << GPIO_DR_DR_SHIFT)) & GPIO_DR_DR_MASK)

/*! @name GDIR - GPIO direction register */
#define GPIO_GDIR_GDIR_MASK                      (0xFFFFFFFFU)
#define GPIO_GDIR_GDIR_SHIFT                     (0U)
#define GPIO_GDIR_GDIR(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_GDIR_GDIR_SHIFT)) & GPIO_GDIR_GDIR_MASK)

/*! @name PSR - GPIO pad status register */
#define GPIO_PSR_PSR_MASK                        (0xFFFFFFFFU)
#define GPIO_PSR_PSR_SHIFT                       (0U)
#define GPIO_PSR_PSR(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_PSR_PSR_SHIFT)) & GPIO_PSR_PSR_MASK)

/*! @name ICR1 - GPIO interrupt configuration register1 */
#define GPIO_ICR1_ICR0_MASK                      (0x3U)
#define GPIO_ICR1_ICR0_SHIFT                     (0U)
#define GPIO_ICR1_ICR0(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR0_SHIFT)) & GPIO_ICR1_ICR0_MASK)
#define GPIO_ICR1_ICR1_MASK                      (0xCU)
#define GPIO_ICR1_ICR1_SHIFT                     (2U)
#define GPIO_ICR1_ICR1(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR1_SHIFT)) & GPIO_ICR1_ICR1_MASK)
#define GPIO_ICR1_ICR2_MASK                      (0x30U)
#define GPIO_ICR1_ICR2_SHIFT                     (4U)
#define GPIO_ICR1_ICR2(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR2_SHIFT)) & GPIO_ICR1_ICR2_MASK)
#define GPIO_ICR1_ICR3_MASK                      (0xC0U)
#define GPIO_ICR1_ICR3_SHIFT                     (6U)
#define GPIO_ICR1_ICR3(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR3_SHIFT)) & GPIO_ICR1_ICR3_MASK)
#define GPIO_ICR1_ICR4_MASK                      (0x300U)
#define GPIO_ICR1_ICR4_SHIFT                     (8U)
#define GPIO_ICR1_ICR4(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR4_SHIFT)) & GPIO_ICR1_ICR4_MASK)
#define GPIO_ICR1_ICR5_MASK                      (0xC00U)
#define GPIO_ICR1_ICR5_SHIFT                     (10U)
#define GPIO_ICR1_ICR5(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR5_SHIFT)) & GPIO_ICR1_ICR5_MASK)
#define GPIO_ICR1_ICR6_MASK                      (0x3000U)
#define GPIO_ICR1_ICR6_SHIFT                     (12U)
#define GPIO_ICR1_ICR6(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR6_SHIFT)) & GPIO_ICR1_ICR6_MASK)
#define GPIO_ICR1_ICR7_MASK                      (0xC000U)
#define GPIO_ICR1_ICR7_SHIFT                     (14U)
#define GPIO_ICR1_ICR7(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR7_SHIFT)) & GPIO_ICR1_ICR7_MASK)
#define GPIO_ICR1_ICR8_MASK                      (0x30000U)
#define GPIO_ICR1_ICR8_SHIFT                     (16U)
#define GPIO_ICR1_ICR8(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR8_SHIFT)) & GPIO_ICR1_ICR8_MASK)
#define GPIO_ICR1_ICR9_MASK                      (0xC0000U)
#define GPIO_ICR1_ICR9_SHIFT                     (18U)
#define GPIO_ICR1_ICR9(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR9_SHIFT)) & GPIO_ICR1_ICR9_MASK)
#define GPIO_ICR1_ICR10_MASK                     (0x300000U)
#define GPIO_ICR1_ICR10_SHIFT                    (20U)
#define GPIO_ICR1_ICR10(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR10_SHIFT)) & GPIO_ICR1_ICR10_MASK)
#define GPIO_ICR1_ICR11_MASK                     (0xC00000U)
#define GPIO_ICR1_ICR11_SHIFT                    (22U)
#define GPIO_ICR1_ICR11(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR11_SHIFT)) & GPIO_ICR1_ICR11_MASK)
#define GPIO_ICR1_ICR12_MASK                     (0x3000000U)
#define GPIO_ICR1_ICR12_SHIFT                    (24U)
#define GPIO_ICR1_ICR12(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR12_SHIFT)) & GPIO_ICR1_ICR12_MASK)
#define GPIO_ICR1_ICR13_MASK                     (0xC000000U)
#define GPIO_ICR1_ICR13_SHIFT                    (26U)
#define GPIO_ICR1_ICR13(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR13_SHIFT)) & GPIO_ICR1_ICR13_MASK)
#define GPIO_ICR1_ICR14_MASK                     (0x30000000U)
#define GPIO_ICR1_ICR14_SHIFT                    (28U)
#define GPIO_ICR1_ICR14(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR14_SHIFT)) & GPIO_ICR1_ICR14_MASK)
#define GPIO_ICR1_ICR15_MASK                     (0xC0000000U)
#define GPIO_ICR1_ICR15_SHIFT                    (30U)
#define GPIO_ICR1_ICR15(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR15_SHIFT)) & GPIO_ICR1_ICR15_MASK)

/*! @name ICR2 - GPIO interrupt configuration register2 */
#define GPIO_ICR2_ICR16_MASK                     (0x3U)
#define GPIO_ICR2_ICR16_SHIFT                    (0U)
#define GPIO_ICR2_ICR16(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR16_SHIFT)) & GPIO_ICR2_ICR16_MASK)
#define GPIO_ICR2_ICR17_MASK                     (0xCU)
#define GPIO_ICR2_ICR17_SHIFT                    (2U)
#define GPIO_ICR2_ICR17(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR17_SHIFT)) & GPIO_ICR2_ICR17_MASK)
#define GPIO_ICR2_ICR18_MASK                     (0x30U)
#define GPIO_ICR2_ICR18_SHIFT                    (4U)
#define GPIO_ICR2_ICR18(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR18_SHIFT)) & GPIO_ICR2_ICR18_MASK)
#define GPIO_ICR2_ICR19_MASK                     (0xC0U)
#define GPIO_ICR2_ICR19_SHIFT                    (6U)
#define GPIO_ICR2_ICR19(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR19_SHIFT)) & GPIO_ICR2_ICR19_MASK)
#define GPIO_ICR2_ICR20_MASK                     (0x300U)
#define GPIO_ICR2_ICR20_SHIFT                    (8U)
#define GPIO_ICR2_ICR20(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR20_SHIFT)) & GPIO_ICR2_ICR20_MASK)
#define GPIO_ICR2_ICR21_MASK                     (0xC00U)
#define GPIO_ICR2_ICR21_SHIFT                    (10U)
#define GPIO_ICR2_ICR21(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR21_SHIFT)) & GPIO_ICR2_ICR21_MASK)
#define GPIO_ICR2_ICR22_MASK                     (0x3000U)
#define GPIO_ICR2_ICR22_SHIFT                    (12U)
#define GPIO_ICR2_ICR22(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR22_SHIFT)) & GPIO_ICR2_ICR22_MASK)
#define GPIO_ICR2_ICR23_MASK                     (0xC000U)
#define GPIO_ICR2_ICR23_SHIFT                    (14U)
#define GPIO_ICR2_ICR23(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR23_SHIFT)) & GPIO_ICR2_ICR23_MASK)
#define GPIO_ICR2_ICR24_MASK                     (0x30000U)
#define GPIO_ICR2_ICR24_SHIFT                    (16U)
#define GPIO_ICR2_ICR24(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR24_SHIFT)) & GPIO_ICR2_ICR24_MASK)
#define GPIO_ICR2_ICR25_MASK                     (0xC0000U)
#define GPIO_ICR2_ICR25_SHIFT                    (18U)
#define GPIO_ICR2_ICR25(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR25_SHIFT)) & GPIO_ICR2_ICR25_MASK)
#define GPIO_ICR2_ICR26_MASK                     (0x300000U)
#define GPIO_ICR2_ICR26_SHIFT                    (20U)
#define GPIO_ICR2_ICR26(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR26_SHIFT)) & GPIO_ICR2_ICR26_MASK)
#define GPIO_ICR2_ICR27_MASK                     (0xC00000U)
#define GPIO_ICR2_ICR27_SHIFT                    (22U)
#define GPIO_ICR2_ICR27(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR27_SHIFT)) & GPIO_ICR2_ICR27_MASK)
#define GPIO_ICR2_ICR28_MASK                     (0x3000000U)
#define GPIO_ICR2_ICR28_SHIFT                    (24U)
#define GPIO_ICR2_ICR28(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR28_SHIFT)) & GPIO_ICR2_ICR28_MASK)
#define GPIO_ICR2_ICR29_MASK                     (0xC000000U)
#define GPIO_ICR2_ICR29_SHIFT                    (26U)
#define GPIO_ICR2_ICR29(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR29_SHIFT)) & GPIO_ICR2_ICR29_MASK)
#define GPIO_ICR2_ICR30_MASK                     (0x30000000U)
#define GPIO_ICR2_ICR30_SHIFT                    (28U)
#define GPIO_ICR2_ICR30(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR30_SHIFT)) & GPIO_ICR2_ICR30_MASK)
#define GPIO_ICR2_ICR31_MASK                     (0xC0000000U)
#define GPIO_ICR2_ICR31_SHIFT                    (30U)
#define GPIO_ICR2_ICR31(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR31_SHIFT)) & GPIO_ICR2_ICR31_MASK)

/*! @name IMR - GPIO interrupt mask register */
#define GPIO_IMR_IMR_MASK                        (0xFFFFFFFFU)
#define GPIO_IMR_IMR_SHIFT                       (0U)
#define GPIO_IMR_IMR(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_IMR_IMR_SHIFT)) & GPIO_IMR_IMR_MASK)

/*! @name ISR - GPIO interrupt status register */
#define GPIO_ISR_ISR_MASK                        (0xFFFFFFFFU)
#define GPIO_ISR_ISR_SHIFT                       (0U)
#define GPIO_ISR_ISR(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_ISR_ISR_SHIFT)) & GPIO_ISR_ISR_MASK)

/*! @name EDGE_SEL - GPIO edge select register */
#define GPIO_EDGE_SEL_GPIO_EDGE_SEL_MASK         (0xFFFFFFFFU)
#define GPIO_EDGE_SEL_GPIO_EDGE_SEL_SHIFT        (0U)
#define GPIO_EDGE_SEL_GPIO_EDGE_SEL(x)           (((uint32_t)(((uint32_t)(x)) << GPIO_EDGE_SEL_GPIO_EDGE_SEL_SHIFT)) & GPIO_EDGE_SEL_GPIO_EDGE_SEL_MASK)


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIO1 base address */
#define GPIO1_BASE                               (0x209C000u)
/** Peripheral GPIO1 base pointer */
#define GPIO1                                    ((GPIO_Type *)GPIO1_BASE)
/** Peripheral GPIO2 base address */
#define GPIO2_BASE                               (0x20A0000u)
/** Peripheral GPIO2 base pointer */
#define GPIO2                                    ((GPIO_Type *)GPIO2_BASE)
/** Peripheral GPIO3 base address */
#define GPIO3_BASE                               (0x20A4000u)
/** Peripheral GPIO3 base pointer */
#define GPIO3                                    ((GPIO_Type *)GPIO3_BASE)
/** Peripheral GPIO4 base address */
#define GPIO4_BASE                               (0x20A8000u)
/** Peripheral GPIO4 base pointer */
#define GPIO4                                    ((GPIO_Type *)GPIO4_BASE)
/** Peripheral GPIO5 base address */
#define GPIO5_BASE                               (0x20AC000u)
/** Peripheral GPIO5 base pointer */
#define GPIO5                                    ((GPIO_Type *)GPIO5_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { 0u, GPIO1_BASE, GPIO2_BASE, GPIO3_BASE, GPIO4_BASE, GPIO5_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { (GPIO_Type *)0u, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5 }
/** Interrupt vectors for the GPIO peripheral type */
#define GPIO_IRQS                                { NotAvail_IRQn, GPIO1_INT0_IRQn, GPIO1_INT1_IRQn, GPIO1_INT2_IRQn, GPIO1_INT3_IRQn, GPIO1_INT4_IRQn, GPIO1_INT5_IRQn, GPIO1_INT6_IRQn, GPIO1_INT7_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn }
#define GPIO_COMBINED_IRQS                       { NotAvail_IRQn, GPIO1_Combined_0_15_IRQn, GPIO1_Combined_16_31_IRQn, GPIO2_Combined_0_15_IRQn, GPIO2_Combined_16_31_IRQn, GPIO3_Combined_0_15_IRQn, GPIO3_Combined_16_31_IRQn, GPIO4_Combined_0_15_IRQn, GPIO4_Combined_16_31_IRQn, GPIO5_Combined_0_15_IRQn, GPIO5_Combined_16_31_IRQn }

/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */


#endif