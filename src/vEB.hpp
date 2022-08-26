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

    static constexpr int low(const int x) { return x & (U_low - 1); }
    static constexpr int high(const int x) { return x >> K_low; }

    int min, max;
    std::array<vEB<K_low>, U_high> cluster;
    vEB<K_high> summary;

  public:
    vEB() : min(NIL), max(NIL), cluster{}, summary{} {}

    explicit vEB(const std::array<bool, U>& arr) {
        min = max = NIL;
        std::array<bool, U_high> accum = {};
        for (int i = 0; i < U_high; ++i) {
            std::array<bool, U_low> build = {};
            for (int j = 0; j < U_low; ++j) {
                const int k = i * U_low + j;
                if (arr[k]) {
                    if (min == NIL) {
                        min = k;
                    } else {
                        accum[i] = true;
                        build[j] = true;
                    }
                    max = k;
                }
            }
            cluster[i] = vEB<K_low>(build);
        }
        summary = vEB<K_high>(accum);
    }

    bool EMPTY() const { return min == NIL; }

    int MINIMUM() const { return min; }

    int MAXIMUM() const { return max; }

    void INSERT(int x) {
        if (EMPTY()) {
            min = max = x;
        } else if (min != x) {
            if (x < min)
                std::swap(x, min);
            const int i = high(x);
            if (cluster[i].EMPTY())
                summary.INSERT(i);
            cluster[i].INSERT(low(x));
            if (max < x)
                max = x;
        }
    }

    void DELETE(const int x) {
        if (min == x and max == x) {
            min = max = NIL;
        } else if (min == x) {
            const int i = summary.MINIMUM();
            const int x_ = cluster[i].MINIMUM();
            min = i * U_low + x_;
            cluster[i].DELETE(x_);
            if (cluster[i].EMPTY())
                summary.DELETE(i);
        } else if (max == x) {
            const int i = high(x);
            cluster[i].DELETE(low(x));
            if (cluster[i].EMPTY())
                summary.DELETE(i);
            if (summary.EMPTY()) {
                max = min;
            } else {
                const int i_ = summary.MAXIMUM();
                const int x_ = cluster[i_].MAXIMUM();
                max = i_ * U_low + x_;
            }
        } else if (min < x and x < max) {
            const int i = high(x);
            cluster[i].DELETE(low(x));
            if (cluster[i].EMPTY())
                summary.DELETE(i);
        }
    }

    bool MEMBER(const int x) const {
        if (EMPTY() or x < min or max < x) {
            return false;
        } else if (min == x or max == x) {
            return true;
        } else {
            return cluster[high(x)].MEMBER(low(x));
        }
    }

    int PREDECESSOR(const int x) const {
        if (EMPTY() or x < min) {
            return NIL;
        } else if (max <= x) {
            return max;
        } else {
            const int i = high(x);
            const int j = low(x);
            if (!cluster[i].EMPTY() and cluster[i].MINIMUM() <= j) {
                const int x_ = cluster[i].PREDECESSOR(j);
                return i * U_low + x_;
            } else {
                const int i_ = summary.PREDECESSOR(i - 1);
                if (i_ == NIL) {
                    return min;
                } else {
                    return i_ * U_low + cluster[i_].MAXIMUM();
                }
            }
        }
    }

    int SUCCESSOR(const int x) const {
        if (EMPTY() or max < x) {
            return NIL;
        } else if (x <= min) {
            return min;
        } else {
            const int i = high(x);
            const int j = low(x);
            if (!cluster[i].EMPTY() and cluster[i].MAXIMUM() >= j) {
                const int x_ = cluster[i].SUCCESSOR(j);
                return i * U_low + x_;
            } else {
                const int i_ = summary.SUCCESSOR(i + 1);
                return i_ * U_low + cluster[i_].MINIMUM();
            }
        }
    }
};

template <>
class vEB<1> {
    std::array<bool, 2> exists;

  public:
    vEB() : exists{} {}

    explicit vEB(const std::array<bool, 2>& arr) : exists(arr) {}

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