#ifndef REGISTERACCESS
#define REGISTERACCESS

#include "targetSpecific/registerType.h"

template<typename RegisterAddressType,
         typename RegisterValueType,
         const RegisterAddressType address,
         const RegisterValueType value = static_cast<RegisterValueType>(0)>
struct registerAccess
{
  static void regSet() { *reinterpret_cast<volatile RegisterAddressType *>(address) = value; }
  static void regAnd() { *reinterpret_cast<volatile RegisterAddressType *>(address) &= value; }
  static void regOr() { *reinterpret_cast<volatile RegisterAddressType *>(address) |= value; }
  static RegisterValueType regGet() { return *reinterpret_cast<volatile RegisterAddressType *>(address); }

  static void regBitSet()
  {
    reinterpret_cast<volatile RegisterAddressType *>(address) |= static_cast<RegisterValueType>(1ULL << value);
  }

  static void regBitClear()
  {
    reinterpret_cast<volatile RegisterAddressType *>(address) &=
      static_cast<RegisterValueType>(~static_cast<RegisterValueType>(1ULL << value));
  }

  static void regBitToggle()
  {
    reinterpret_cast<volatile RegisterAddressType *>(address) ^= static_cast<RegisterValueType>(1ULL << value);
  }

  static bool regBitGet()
  {
    return (static_cast<volatile RegisterValueType>((regGet() & static_cast<RegisterValueType>(1ULL << value))) !=
            static_cast<register_value_type>(0U));
  }
};


#endif /* REGISTERACCESS */
