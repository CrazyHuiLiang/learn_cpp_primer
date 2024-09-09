#include <iostream>

using namespace std;

int main() {
    std::cout << "This is cout" << std::endl;
    cerr << "This is a cerr" << endl;
    clog << "This is a clog" << endl;

    cout << "Enter tow numbers:" << endl;
    int v1 = 0, v2 = 0;
    cin >> v1 >> v2; 
    cout << "The sum of " << v1 << " and " << v2 << " is " << v1 + v2 << endl;
    system("pause");
    return 0;
}
