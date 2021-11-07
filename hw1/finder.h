#ifndef _FINDER_H
#define _FINDER_H
#include <vector>
#include <algorithm>

class fake_coin_finder{
private:
    int n;
    std::vector<int> weights;
public:
    fake_coin_finder(int n): n(n) {
        weights.resize(n);
    }

    void set_weight(int index, int weight) {
        weights[index] = weight;
    }

    /*
    Given two vectors of indicies, indicate which side is heavier.
    Return value:
    -1 if right side is heavier
    1 if left side is heavier
    0 if both side have equal weight
    */
    int scale(std::vector<int> left, std::vector<int> right) {
        std::sort(left.begin(), left.end());
        std::sort(right.begin(), right.end());

        /*
        Check if all the indicies are between 0 and n - 1.
        Since the elements are sorted, only the first and
        the last element need to be checked.
        */
        if (left[0] < 0 || left.back() >= n)
            throw std::invalid_argument("Left plate has index not in range [0, n).");
        if (right[0] < 0 || right.back() >= n)
            throw std::invalid_argument("Right plate has index not in range [0, n).");

        /*
        Check if either side have same elements.
        */
        for (int i = 0; i < (int)left.size() - 1; i++) {
            if (left[i] == left[i + 1])
                throw std::invalid_argument("Left plate has same index.");
        }
        for (int i = 0; i < (int)right.size() - 1; i++) {
            if (right[i] == right[i + 1])
                throw std::invalid_argument("Right plate has same index.");
        }

        /*
        Check if both side have the same index using two pointers method.
        */
        int right_index = 0;
        for (int i = 0; i < (int)left.size(); i++) {
            while (right_index < (int)right.size() - 1
                && right[right_index] < left[i]) right_index++;
            if (left[i] == right[right_index])
                throw std::invalid_argument("Both side has same index.");
        }

        long long left_weight = 0, right_weight = 0;
        for (int i : left) left_weight += weights[i];
        for (int i : right) right_weight += weights[i];

        if (left_weight > right_weight) return 1;
        else if (left_weight == right_weight) return 0;
        else return -1;
    }
};
#endif /* _FINDER_H */
