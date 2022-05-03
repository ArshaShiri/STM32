#ifndef SRC_PROCESSORSPECIFIC_BASEADDRESSES
#define SRC_PROCESSORSPECIFIC_BASEADDRESSES

#include "targetSpecific/registers/registerType.h"

namespace processor
{

class BaseAddresses
{
public:
  static constexpr RegisterType nvicISER0 = UINT32_C(0xE000E100);
  static constexpr RegisterType nvicICER0 = UINT32_C(0xE000E180);
  static constexpr RegisterType nvicIPR0 = UINT32_C(0xE000E400);
};

} // namespace processor

#endif /* SRC_PROCESSORSPECIFIC_BASEADDRESSES */
