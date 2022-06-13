#ifndef HELPERS
#define HELPERS

#include <algorithm>
#include <array>
#include <stdexcept>

// Thanks to C++ Weekly - Ep 233 - std::map vs constexpr map (huge perf difference!)
template<typename Key, typename Value, std::size_t size>
struct StaticMap
{
  std::array<std::pair<Key, Value>, size> data;

  [[nodiscard]] constexpr Value at(const Key &key) const
  {
    const auto it = std::find_if(data.begin(), data.end(), [&key](const auto &pair) { return pair.first == key; });
    if (it != data.end())
      return it->second;
    // Had to comment this out since the target code cannot have exception handling!
    // else
    //   return 0;
  }
};

template<size_t delayCounter>
void softwareDelay()
{
  auto i = size_t{ 0 };
  for ([[maybe_unused]] volatile size_t counter = 0; i < delayCounter; counter = i, ++i)
  {
  }
}

#endif /* HELPERS */
