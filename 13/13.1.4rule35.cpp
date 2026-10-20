#include <iostream>

using std::cout;
using std::endl;

class Numbered {
public:
	static int sn;
	int mysn;

	Numbered() : mysn(Numbered::sn++) {};
	Numbered(Numbered&);
};

int Numbered::sn = 1;

Numbered::Numbered(Numbered& orig): mysn(Numbered::sn++) {
}


void f(Numbered s) {
	cout << s.mysn << endl;
}

void f2(Numbered& s) {
	cout << s.mysn << endl;
}

int main() {

	// 如果没有拷贝构造函数，下面三个打印的都是1
	// 如果有拷贝构造函数，下面三个打印的会变成 4 5 6
	Numbered a, b = a, c = b;
	f(a);
	f(b);
	f(c);

	// 如果没有拷贝构造函数，下面三个打印的都是1
	// 如果有拷贝构造函数，下面三个打印的会变成 1 2 3
	f2(a);
	f2(b);
	f2(c);

	return 0;
}
