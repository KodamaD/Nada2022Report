#include <set>
#include <vector>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    constexpr int LOG = 24;
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> initial;
    initial.reserve(1 << LOG);
    for (int i = 0; i < N; ++i) {
        char c;
        std::cin >> c;
        if (c == '1') {
            initial.push_back(i);
        }
    }
    std::set<int> set(initial.begin(), initial.end());
    while (Q--) {
        int c, k;
        std::cin >> c >> k;
        if (c == 0) {
            set.insert(k);
        } else if (c == 1) {
            set.erase(k);
        } else if (c == 2) {
            std::cout << (set.find(k) != set.end()) << '\n';
        } else if (c == 3) {
            const auto itr = set.lower_bound(k);
            std::cout << (itr == set.end() ? -1 : *itr) << '\n';
        } else {
            const auto itr = set.upper_bound(k);
            std::cout << (itr == set.begin() ? -1 : *std::prev(itr)) << '\n';
        }
    }
    return 0;
}