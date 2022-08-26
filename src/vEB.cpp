#include "vEB.hpp"
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    constexpr int LOG = 24;
    int N, Q;
    std::cin >> N >> Q;
    std::array<bool, (1 << LOG)> T = {};
    for (int i = 0; i < N; ++i) {
        char c;
        std::cin >> c;
        if (c == '1') {
            T[i] = true;
        }
    }
    vEB::vEB<LOG> veb(T);
    while (Q--) {
        int c, k;
        std::cin >> c >> k;
        if (c == 0) {
            veb.INSERT(k);
        } else if (c == 1) {
            veb.DELETE(k);
        } else if (c == 2) {
            std::cout << veb.MEMBER(k) << '\n';
        } else if (c == 3) {
            std::cout << veb.SUCCESSOR(k) << '\n';
        } else {
            std::cout << veb.PREDECESSOR(k) << '\n';
        }
    }
    return 0;
}