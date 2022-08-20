#ifndef HEADER_vEB
#define HEADER_vEB

#include <algorithm>
#include <array>

namespace vEB {

constexpr int NIL = -1;

template <int K>
class vEB {
    static constexpr int K_low = K / 2;
    static constexpr int K_high = (K + 1) / 2;
    static constexpr int U = 1 << K;
    static constexpr int U_low = 1 << K_low;
    static constexpr int U_high = 1 << K_high;

    static constexpr low(const int x) { return x & (U_low - 1); }
    static constexpr high(const int x) { return x >> K_low; }

    int min, max;
    std::array<vEB<K_low>, U_high> cluster;
    vEB<K_high> summary;

  public:
    vEB() : min(NIL), max(NIL), cluster{}, summary() {}

    bool EMPTY() const { return min == NIL; }

    int MINIMUM() const { return min; }

    int MAXIMUM() const { return max; }

    void INSERT(int x) {
        if (empty()) {
            min = max = x;
        } else if (min != x) {
            if (x < min)
                std::swap(x, min);
            const int i = high(x);
            if (cluster[i].EMPTY())
                summary.INSERT(i);
            cluster[i].INSERT(low(x));
        }
    }

    void DELETE(const int x) {
        if (min == x and max == x) {
            min = max = x;
        } else if (min == x) {
            const int i = summary.MINIMUM();
            const int x = cluster[i].MINIMUM();
            min = i * U_low + x;
            cluster[i].DELETE(x);
            if (cluster[i].EMPTY())
                summary.DELTE(i);
        } else if (max == x) {
            const int i = high(x);
            cluster[i].DELETE(high(x));
            if (cluster[i].EMPTY()) {
                summary.DELETE(i);
                if (summary.EMPTY()) {
                    max = min;
                } else {
                    const int i = summary.MAXIMUM();
                    const int x = cluster[i_].MAXIMUM();
                    max = i * U_low + x;
                }
            }
        } else if (min < x and x < max) {
            const int i = high(x);
            cluster[i].DELETE(high(x));
            if (cluster[i].EMPTY())
                summary.DELETE(i);
        }
    }
};

template <>
class vEB<1> {
    std::array<bool, 2> exists;

  public:
    vEB() : exists{} {}

    bool EMPTY() const { return !exists[0] and !exists[1]; }

    int MINIMUM() const {
        if (exists[0])
            return 0;
        if (exists[1])
            return 1;
        return NIL;
    }

    int MAXIMUM() const {
        if (exists[1])
            return 1;
        if (exists[0])
            return 0;
        return NIL;
    }

    void INSERT(const int x) { exists[x] = true; }

    void DELETE(const int x) { exists[x] = false; }

    bool MEMBER(const int x) const { return exists[x]; }

    int PREDECESSOR(const int x) const {
        for (int i = x; i >= 0; --i)
            if (exists[i])
                return i;
        return NIL;
    }

    int SUCCESSOR(const int x) const {
        for (int i = x; i <= 1; ++i)
            if (exists[i])
                return i;
        return NIL;
    }
};

}  // namespace vEB

#endif