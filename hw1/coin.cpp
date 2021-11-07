#include <iostream>
#include <vector>
#include "finder.h"

int find_fake_coin(fake_coin_finder &finder, int n) {
    for (int i = 0; i < n; i++) {
        try {
            int result_left = finder.scale({i}, {(i + n - 1) % n});
            int result_right = finder.scale({i}, {(i + 1) % n});
            if (result_left != 0 && result_right != 0)
                return i;
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }
    return -1;
}

int main() {
    int n;
    while (std::cin >> n) {
        fake_coin_finder finder(n);
        for (int i = 0; i < n; i++) {
            int weight; std::cin >> weight;
            finder.set_weight(i, weight);
        }

        std::cout << find_fake_coin(finder, n) << std::endl;
    }
}
