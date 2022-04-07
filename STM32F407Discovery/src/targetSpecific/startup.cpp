#include <array>
#include <cstdint>

static constexpr auto SRAM_START = 0x20000000U;
static constexpr auto SRAM_SIZE = 128U * 1024U;
static constexpr auto SRAM_END = SRAM_START + SRAM_SIZE;
static constexpr auto STACK_START = SRAM_END;

extern std::uint32_t end_of_text; // NOLINT
extern std::uint32_t start_of_data; // NOLINT
extern std::uint32_t end_of_data; // NOLINT
extern std::uint32_t start_of_bss; // NOLINT
extern std::uint32_t end_of_bss; // NOLINT
extern std::uint32_t load_address_of_data; // NOLINT

int main();

void Default_Handler()
{
  while (true)
  {
  };
}

extern "C" void Reset_Handler() __attribute__((used, noinline));

extern "C" void NMI_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void HardFault_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void MemManage_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void BusFault_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void UsageFault_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void SVC_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DebugMon_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void PendSV_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void SysTick_Handler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void WWDG_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void PVD_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TAMP_STAMP_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void RTC_WKUP_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void RCC_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void EXTI0_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void EXTI1_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void EXTI2_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void EXTI3_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void EXTI4_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream0_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream1_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream2_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream3_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream4_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream5_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream6_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void ADC_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN1_TX_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN1_RX0_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN1_RX1_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN1_SCE_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void EXTI9_5_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM1_BRK_TIM9_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM1_UP_TIM10_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM1_CC_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM2_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM3_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM4_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void I2C1_EV_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void I2C1_ER_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void I2C2_EV_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void I2C2_ER_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void SPI1_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void SPI2_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void USART1_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void USART2_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void USART3_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void EXTI15_10_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void RTC_Alarm_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void OTG_FS_WKUP_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM8_BRK_TIM12_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM8_UP_TIM13_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM8_TRG_COM_TIM14_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM8_CC_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA1_Stream7_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void FSMC_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void SDIO_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM5_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void SPI3_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void UART4_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void UART5_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM6_DAC_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void TIM7_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream0_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream1_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream2_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream3_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream4_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void ETH_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void ETH_WKUP_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN2_TX_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN2_RX0_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN2_RX1_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CAN2_SCE_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void OTG_FS_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream5_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream6_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DMA2_Stream7_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void USART6_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void I2C3_EV_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void I2C3_ER_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void OTG_HS_EP1_OUT_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void OTG_HS_EP1_IN_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void OTG_HS_WKUP_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void OTG_HS_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void DCMI_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void CRYP_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void HASH_RNG_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}
extern "C" void FPU_IRQHandler()
{
  for (;;)
  {
    asm volatile("nop"); // NOLINT inline assembler
  }
}

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
  // Copy data section in SRAM
  const std::uint32_t sizeOfDataSection = static_cast<uint32_t>(&end_of_data - &start_of_data);

  std::uint8_t *pDestination = reinterpret_cast<std::uint8_t *>(&start_of_data); // // NOLINT  SRAM
  std::uint8_t *pSource = reinterpret_cast<std::uint8_t *>(&load_address_of_data); // NOLINT Flash

  for (std::uint32_t i = 0; i < sizeOfDataSection; i++)
  {
    *pDestination++ = *pSource++; // NOLINT
  }

  // Initialize the .bss section to zero in SRAM
  const std::uint32_t sizeOfBssSection = static_cast<uint32_t>(&end_of_bss - &start_of_bss);
  pDestination = reinterpret_cast<std::uint8_t *>(&start_of_bss); // NOLINT

  for (uint32_t i = 0; i < sizeOfBssSection; i++)
  {
    *pDestination++ = 0; // NOLINT
  }

  // Call main
  // Jump to main (and never return).
  asm volatile("ldr r3, =main"); // NOLINT
  asm volatile("blx r3"); // NOLINT
}
