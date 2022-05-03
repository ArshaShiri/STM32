#include <algorithm>
#include <array>
#include <cstdint>

using FunctionType = void (*)();

extern "C" {
extern std::uint32_t end_of_text; // NOLINT
extern std::uint32_t start_of_data; // NOLINT
extern std::uint32_t end_of_data; // NOLINT
extern std::uint32_t start_of_bss; // NOLINT
extern std::uint32_t end_of_bss; // NOLINT
extern std::uint32_t load_address_of_data; // NOLINT
extern FunctionType start_of_constructors[];
extern FunctionType end_of_constructors[];
}

namespace
{
void initializeRam()
{
  // Copy data section in SRAM
  const std::uint32_t sizeOfDataSection = static_cast<uint32_t>(&end_of_data - &start_of_data);

  std::copy(&load_address_of_data, &load_address_of_data + sizeOfDataSection, &start_of_data);

  // Initialize the .bss section to zero in SRAM
  std::fill(&start_of_bss, &end_of_bss, static_cast<std::uint32_t>(0U));
}

void initializeConstructors()
{
  std::for_each(start_of_constructors, end_of_constructors, [](FunctionType &constructor) { constructor(); });
}

extern "C" void defaulHandler()
{
  while (true)
  {
  };
}
} // namespace

static constexpr auto SRAM_START = 0x20000000U;
static constexpr auto SRAM_SIZE = 128U * 1024U;
static constexpr auto SRAM_END = SRAM_START + SRAM_SIZE;
static constexpr auto STACK_START = SRAM_END;

extern "C" void Reset_Handler() __attribute__((used, noinline));

extern "C" void NMI_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void HardFault_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void MemManage_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void BusFault_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void UsageFault_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void SVC_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DebugMon_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void PendSV_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void SysTick_Handler() __attribute__((weak, alias("defaulHandler")));
extern "C" void WWDG_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void PVD_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TAMP_STAMP_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void RTC_WKUP_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void RCC_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void EXTI0_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void EXTI1_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void EXTI2_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void EXTI3_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void EXTI4_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream0_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream1_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream2_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream3_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream4_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream5_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream6_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void ADC_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN1_TX_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN1_RX0_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN1_RX1_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN1_SCE_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void EXTI9_5_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM1_BRK_TIM9_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM1_UP_TIM10_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM1_CC_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM2_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM3_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM4_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void I2C1_EV_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void I2C1_ER_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void I2C2_EV_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void I2C2_ER_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void SPI1_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void SPI2_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void USART1_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void USART2_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void USART3_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void EXTI15_10_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void RTC_Alarm_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void OTG_FS_WKUP_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM8_BRK_TIM12_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM8_UP_TIM13_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM8_TRG_COM_TIM14_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM8_CC_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA1_Stream7_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void FSMC_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void SDIO_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM5_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void SPI3_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void UART4_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void UART5_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM6_DAC_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void TIM7_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream0_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream1_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream2_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream3_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream4_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void ETH_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void ETH_WKUP_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN2_TX_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN2_RX0_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN2_RX1_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CAN2_SCE_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void OTG_FS_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream5_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream6_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DMA2_Stream7_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void USART6_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void I2C3_EV_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void I2C3_ER_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void OTG_HS_EP1_OUT_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void OTG_HS_EP1_IN_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void OTG_HS_WKUP_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void OTG_HS_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void DCMI_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void CRYP_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void HASH_RNG_IRQHandler() __attribute__((weak, alias("defaulHandler")));
extern "C" void FPU_IRQHandler() __attribute__((weak, alias("defaulHandler")));

namespace
{
using isr_type = void (*)();

constexpr std::size_t number_of_interrupts = 98U;
} // namespace

// From Table 61 of reference manual.
extern "C" const volatile std::array<isr_type, number_of_interrupts> isr_vector
  __attribute__((section(".isr_vector"))) = { { reinterpret_cast<isr_type>(STACK_START), // NOLINT inline assembler
                                                Reset_Handler,
                                                NMI_Handler,
                                                HardFault_Handler,
                                                MemManage_Handler,
                                                BusFault_Handler,
                                                UsageFault_Handler,
                                                0,
                                                0,
                                                0,
                                                0,
                                                SVC_Handler,
                                                DebugMon_Handler,
                                                0,
                                                PendSV_Handler,
                                                SysTick_Handler,
                                                WWDG_IRQHandler,
                                                PVD_IRQHandler,
                                                TAMP_STAMP_IRQHandler,
                                                RTC_WKUP_IRQHandler,
                                                0,
                                                RCC_IRQHandler,
                                                EXTI0_IRQHandler,
                                                EXTI1_IRQHandler,
                                                EXTI2_IRQHandler,
                                                EXTI3_IRQHandler,
                                                EXTI4_IRQHandler,
                                                DMA1_Stream0_IRQHandler,
                                                DMA1_Stream1_IRQHandler,
                                                DMA1_Stream2_IRQHandler,
                                                DMA1_Stream3_IRQHandler,
                                                DMA1_Stream4_IRQHandler,
                                                DMA1_Stream5_IRQHandler,
                                                DMA1_Stream6_IRQHandler,
                                                ADC_IRQHandler,
                                                CAN1_TX_IRQHandler,
                                                CAN1_RX0_IRQHandler,
                                                CAN1_RX1_IRQHandler,
                                                CAN1_SCE_IRQHandler,
                                                EXTI9_5_IRQHandler,
                                                TIM1_BRK_TIM9_IRQHandler,
                                                TIM1_UP_TIM10_IRQHandler,
                                                TIM1_TRG_COM_TIM11_IRQHandler,
                                                TIM1_CC_IRQHandler,
                                                TIM2_IRQHandler,
                                                TIM3_IRQHandler,
                                                TIM4_IRQHandler,
                                                I2C1_EV_IRQHandler,
                                                I2C1_ER_IRQHandler,
                                                I2C2_EV_IRQHandler,
                                                I2C2_ER_IRQHandler,
                                                SPI1_IRQHandler,
                                                SPI2_IRQHandler,
                                                USART1_IRQHandler,
                                                USART2_IRQHandler,
                                                USART3_IRQHandler,
                                                EXTI15_10_IRQHandler,
                                                RTC_Alarm_IRQHandler,
                                                OTG_FS_WKUP_IRQHandler,
                                                TIM8_BRK_TIM12_IRQHandler,
                                                TIM8_UP_TIM13_IRQHandler,
                                                TIM8_TRG_COM_TIM14_IRQHandler,
                                                TIM8_CC_IRQHandler,
                                                DMA1_Stream7_IRQHandler,
                                                FSMC_IRQHandler,
                                                SDIO_IRQHandler,
                                                TIM5_IRQHandler,
                                                SPI3_IRQHandler,
                                                UART4_IRQHandler,
                                                UART5_IRQHandler,
                                                TIM6_DAC_IRQHandler,
                                                TIM7_IRQHandler,
                                                DMA2_Stream0_IRQHandler,
                                                DMA2_Stream1_IRQHandler,
                                                DMA2_Stream2_IRQHandler,
                                                DMA2_Stream3_IRQHandler,
                                                DMA2_Stream4_IRQHandler,
                                                ETH_IRQHandler,
                                                ETH_WKUP_IRQHandler,
                                                CAN2_TX_IRQHandler,
                                                CAN2_RX0_IRQHandler,
                                                CAN2_RX1_IRQHandler,
                                                CAN2_SCE_IRQHandler,
                                                OTG_FS_IRQHandler,
                                                DMA2_Stream5_IRQHandler,
                                                DMA2_Stream6_IRQHandler,
                                                DMA2_Stream7_IRQHandler,
                                                USART6_IRQHandler,
                                                I2C3_EV_IRQHandler,
                                                I2C3_ER_IRQHandler,
                                                OTG_HS_EP1_OUT_IRQHandler,
                                                OTG_HS_EP1_IN_IRQHandler,
                                                OTG_HS_WKUP_IRQHandler,
                                                OTG_HS_IRQHandler,
                                                DCMI_IRQHandler,
                                                CRYP_IRQHandler,
                                                HASH_RNG_IRQHandler,
                                                FPU_IRQHandler } };

// First function that is executed.
void Reset_Handler()
{
  initializeRam();
  initializeConstructors();

  // Call main
  // Jump to main (and never return).
  asm volatile("ldr r3, =main"); // NOLINT
  asm volatile("blx r3"); // NOLINT
}
