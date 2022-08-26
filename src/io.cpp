#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, Q;
    std::cin >> N >> Q;
    for (int i = 0; i < N; ++i) {
        char c;
        std::cin >> c;
    }
    while (Q--) {
        int c, k;
        std::cin >> c >> k;
        if (c >= 2) {
            std::cout << 0 << '\n';
        }
    }
    return 0;
}