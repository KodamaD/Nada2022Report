#ifndef HEADER_vEB_FASTER
#define HEADER_vEB_FASTER

#include "vEB.hpp"
#include <cstdint>

namespace vEB {

template <>
class vEB<6> {
    std::uint64_t bit;

  public:
    vEB() : bit(0) {}

    explicit vEB(const std::array<bool, 64>& arr) : bit(0) {
        for (int i = 0; i < 64; ++i) {
            bit |= std::uint64_t(arr[i]) << i;
        }
    }

    bool EMPTY() const { return bit == 0; }

    int MINIMUM() const { return EMPTY() ? NIL : __builtin_ctzll(bit); }

    int MAXIMUM() const { return EMPTY() ? NIL : 63 - __builtin_clzll(bit); }

    void INSERT(const int x) { bit |= std::uint64_t(1) << x; }

    void DELETE(const int x) { bit &= ~(std::uint64_t(1) << x); }

    bool MEMBER(const int x) const { return bit >> x & 1; }

    int PREDECESSOR(const int x) const {
        if (EMPTY() or x < MINIMUM())
            return NIL;
        const std::uint64_t fixed = bit << (63 - x) >> (63 - x);
        return 63 - __builtin_clzll(fixed);
    }

    int SUCCESSOR(const int x) const {
        if (EMPTY() or x > MAXIMUM())
            return NIL;
        const std::uint64_t fixed = bit >> x << x;
        return __builtin_ctzll(fixed);
    }
};

}  // namespace vEB

#endif