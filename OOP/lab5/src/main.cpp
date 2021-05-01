#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>

void printVector(std::vector<int> &v, const std::string& message) {
    std::cout << message << " ";
    for (int i : v) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

void task1() {
    std::vector<int> v(20);
    std::iota(v.begin(), v.end(), 0);
    printVector(v, "v:");

    auto b = std::remove_if(v.begin(), v.end(), [](int i) { return i > 10; });
    v.erase(b, v.end());

    printVector(v, "v:");

    std::list<int> list(20);
    std::iota(list.begin(), list.end(), 50);

    v.erase(v.begin() + 5, v.end());
    printVector(v, "v after erasing:");
    for (int i : list) {
        v.push_back(i);
    }

    printVector(v, "v after merging:");
}

void task2() {
    std::vector<int> v1(20);
    std::iota(v1.begin(), v1.end(), 0);
    printVector(v1, "v1:");
    std::sort(v1.begin(), v1.end(), [](int a, int b) { return a >= b; });
    printVector(v1, "v1 after reverse sort:");
    std::vector<int> v2(0);
    std::copy_if(v1.begin(), v1.end(), std::back_inserter(v2), [](int a) { return a >= 10; });
    printVector(v2, "v2:");
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    printVector(v1, "v1 after sort:");
    printVector(v2, "v2 after sort:");
    std::vector<int> v3(0);
    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));
    printVector(v3, "v3 after union:");
    int count = std::count_if(v3.begin(), v3.end(), [](int x){return x < 4;});
    std::cout << count << " elements => x < 4:";
}

int main() {
    std::cout << "\ntask 1\n\n";
    task1();
    std::cout << "\ntask 2\n\n";
    task2();
}
