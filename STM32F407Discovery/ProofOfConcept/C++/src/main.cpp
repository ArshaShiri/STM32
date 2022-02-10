
#include <cstdint>
#include <limits>


int main()
{
  auto *pClockControlRegister =
    reinterpret_cast<volatile std::uint32_t *>(0x40023830);// NOLINT: Ignored reinterpret_cast by clang-tidy.
  auto *pPortDModeTypeRegister =
    reinterpret_cast<volatile std::uint32_t *>(0x40020C00);// NOLINT: Ignored reinterpret_cast by clang-tidy.
  auto *pPortDOudRegister =
    reinterpret_cast<volatile std::uint32_t *>(0x40020C14);// NOLINT: Ignored reinterpret_cast by clang-tidy.

  // Enable the clock for GPIOD peripheral in the AHB1ENR (Set the 3rd bit position)
  *pClockControlRegister |= (1U << 3U);


  // Configure the mode to output.
  // Clear the 24th and 25th bit positions.
  *pPortDModeTypeRegister &= ~(3U << 24U);// NOLINT

  // Set the 24th bit to 1
  *pPortDModeTypeRegister |= (1U << 24U);// NOLINT

  *pPortDModeTypeRegister |= (1U << 26U);// NOLINT
  *pPortDModeTypeRegister |= (1U << 28U);// NOLINT
  *pPortDModeTypeRegister |= (1U << 30U);// NOLINT


  // Set the 12th bit of the output data register to make I/O pin 12 high.
  *pPortDOudRegister |= (1U << 12U);// NOLINT
  *pPortDOudRegister |= (1U << 13U);// NOLINT
  *pPortDOudRegister |= (1U << 14U);// NOLINT
  *pPortDOudRegister |= (1U << 15U);// NOLINT


  /* Loop forever */
  for (std::size_t i = 0; i > -1; ++i)
  {
    // Add a very basic software LED toggle.
    const std::size_t randNumber = 10000;
    const std::size_t toggleVar = 0x1000;

    if ((i % randNumber) == 0)
    {
      *pPortDOudRegister ^= toggleVar;
    }

    if (i == std::numeric_limits<std::size_t>::max())
    {
      i = 0;
    }
  }
}
