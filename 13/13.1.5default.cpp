#include <iostream>
#include <string>

using std::string;

class Employee {
public:
	static int _sn;

	string name;
	int sn;

	Employee() : sn(++_sn) {}
	explicit Employee(const string &nam): name(nam), sn(++_sn) {}
	Employee(const Employee&) = delete;
	Employee& operator=(const Employee&) = delete;

	void print() const {
		std::cout << "Name:" << name << ", SN:" << sn << std::endl;
	}
};

int Employee::_sn = 0;

int main() {

	Employee em1, em2("z3");
	em1.print();
	em2.print();

	// 拷贝构造和拷贝赋值函数都已删除
	//Employee em3(em2);
	//Employee em4 = em2;

	return 0;
}
