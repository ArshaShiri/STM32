#ifndef REGISTERACCESS
#define REGISTERACCESS

#include "targetSpecific/registers/registerType.h"

template<typename RegisterAddressType, typename RegisterValueType>
struct RegisterAccess
{
  static void regSet(const RegisterAddressType address,
                     const RegisterValueType value = static_cast<RegisterValueType>(0))
  {
    memory(address) = value;
  }

  static void regAnd(const RegisterAddressType address,
                     const RegisterValueType value = static_cast<RegisterValueType>(0))
  {
    memory(address) = (memory(address)) & value;
  }

  static void regOr(const RegisterAddressType address,
                    const RegisterValueType value = static_cast<RegisterValueType>(0))
  {
    memory(address) = (memory(address)) | value;
  }

  static RegisterValueType regGet(const RegisterAddressType address) { return memory(address); }

  static void regBitSet(const RegisterAddressType address,
                        const RegisterValueType value = static_cast<RegisterValueType>(0))
  {
    memory(address) = (memory(address)) | static_cast<RegisterValueType>(1ULL << value);
  }

  static void regBitClear(const RegisterAddressType address,
                          const RegisterValueType value = static_cast<RegisterValueType>(0))
  {
    memory(address) =
      (memory(address)) & static_cast<RegisterValueType>(~static_cast<RegisterValueType>(1ULL << value));
  }

  static void regBitToggle(const RegisterAddressType address,
                           const RegisterValueType value = static_cast<RegisterValueType>(0))
  {
    memory(address) = (memory(address)) ^ static_cast<RegisterValueType>(1ULL << value);
  }

  static bool regBitGet(const RegisterAddressType address,
                        const RegisterValueType value = static_cast<RegisterValueType>(0))
  {
    return (static_cast<volatile RegisterValueType>(
              (regGet(address) & static_cast<RegisterValueType>(1ULL << value))) != static_cast<RegisterValueType>(0U));
  }

private:
  static volatile RegisterAddressType &memory(const RegisterAddressType address)
  {
    return *reinterpret_cast<volatile RegisterAddressType *>(address);
  }
};

struct RegAccess
{
  static void regSet(const RegisterType address, const RegisterType value = static_cast<RegisterType>(0))
  {
    RegisterAccess<RegisterType, RegisterType>::regSet(address, value);
  }

  static void regAnd(const RegisterType address, const RegisterType value = static_cast<RegisterType>(0))
  {
    RegisterAccess<RegisterType, RegisterType>::regAnd(address, value);
  }

  static void regOr(const RegisterType address, const RegisterType value = static_cast<RegisterType>(0))
  {
    RegisterAccess<RegisterType, RegisterType>::regOr(address, value);
  }

  static RegisterType regGet(const RegisterType address)
  {
    return RegisterAccess<RegisterType, RegisterType>::regGet(address);
  }

  static void regBitSet(const RegisterType address, const RegisterType value = static_cast<RegisterType>(0))
  {
    RegisterAccess<RegisterType, RegisterType>::regBitSet(address, value);
  }

  static void regBitClear(const RegisterType address, const RegisterType value = static_cast<RegisterType>(0))
  {
    RegisterAccess<RegisterType, RegisterType>::regBitClear(address, value);
  }

  static void regBitToggle(const RegisterType address, const RegisterType value = static_cast<RegisterType>(0))
  {
    RegisterAccess<RegisterType, RegisterType>::regBitToggle(address, value);
  }

  static bool regBitGet(const RegisterType address, const RegisterType value = static_cast<RegisterType>(0))
  {
    return RegisterAccess<RegisterType, RegisterType>::regBitGet(address, value);
  }
};

#endif /* REGISTERACCESS */
