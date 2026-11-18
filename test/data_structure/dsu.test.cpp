#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using std::swap;
using std::vector;

#include "../../data_structure/dsu.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    dsu uf(n);

    for (int i = 0; i < q; ++i) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) {
            uf.merge(u, v);
        } else {
            std::cout << (uf.same(u, v) ? 1 : 0) << '\n';
        }
    }
}
