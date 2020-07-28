#include "isp/isp.hpp"
#include <iostream>
#include <thread>

using namespace std;

Host host;

void func_2()
{
    Scope s(host, "Function 2", EVENT_ID);

    std::this_thread::sleep_for(150ms);

}

void func_1()
{
    Scope s(host, "Function 1", EVENT_ID);

    std::this_thread::sleep_for(100ms);
    func_2();
    std::this_thread::sleep_for(200ms);
}


int main()
{
    cout << "Hello, world " << __FILE__ << " " << __LINE__ << endl;
    cout << "event id = " << EVENT_ID << endl;
    cout << "event id = " << EVENT_ID << endl;
    cout << "event id = " << EVENT_ID << endl;
    cout << "event id = " << EVENT_ID << endl;
    cout << "event id = " << EVENT_ID << endl;
    cout << "event id = " << EVENT_ID << endl;
    cout << "event id = " << EVENT_ID << endl;
    func_1();
    host.write_timeline("test.json");
    return 0;
}
