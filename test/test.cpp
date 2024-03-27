#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int a[n];
    
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

}
