/*
    作用域
*/
#include <iostream>

class Screen {
private:
    int height = 0;
public:
    Screen(int h) {
        height = h;
    }

    void printHeight() {
        // 三种写法等价，都是访问类的成员变量 height
        std::cout << height << std::endl;
        std::cout << this->height << std::endl;
        std::cout << Screen::height << std::endl;
    }
};

int main() {
    Screen s(10);
    s.printHeight();
    return 0;
}
