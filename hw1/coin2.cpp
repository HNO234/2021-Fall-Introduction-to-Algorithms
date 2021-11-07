#include <iostream>
#include <vector>
#include "finder.h"

int scale_range(fake_coin_finder &finder, int l1, int r1, int l2, int r2) {
    // std::cerr << l1 << ' ' << r1 << ' ' << l2 << ' ' <<r2 <<std::endl;
    std::vector<int> left, right;
    for (int i = l1; i <= r1; i++) left.push_back(i);
    for (int i = l2; i <= r2; i++) right.push_back(i);
    try {
        int result = finder.scale(left, right);
        return result;
    } catch (std::invalid_argument& e) {
        throw e;
    }
}

int find_fake_coin(fake_coin_finder &finder, int n) {
    int left = 0, right = n - 1;

    while (right - left + 1 >= 3) {
        try {
            int len3 = right - left + 1;
            int len = len3 / 3;
            int result1 = scale_range(finder, left, left + len - 1, left + len, left + 2 * len - 1);
            int result2 = scale_range(finder, left, left + len - 1, left + len * 2, left + 3 * len - 1);

            if (result1 != 0 && result2 != 0)
                right = left + len - 1, left = left;
            else if (result1 != 0 && result2 == 0)
                right = left + 2 * len - 1, left = left + len;
            else if (result1 == 0 && result2 != 0)
                right = left + 3 * len - 1, left = left + len * 2;
            else {
                if (len3 - len * 3 == 1) return len3 - 1;
                else {
                    int result3 = scale_range(finder, left, left, len3 - 2, len3 - 2);
                    if (result3 == 0) return len3 - 1;
                    else return len3 - 2;
                }
            }
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }
    if (right - left + 1 == 1) return left;
    else {
        int outside = (left - 1 >= 0 ? left - 1 : right + 1);
        if (scale_range(finder, outside, outside, left, left) == 0) return right;
        else return left;
    }
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
