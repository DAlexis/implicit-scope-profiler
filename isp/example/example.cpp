#include "isp/isp.hpp"
#include <iostream>
#include <thread>

using namespace std;
using namespace isp;

void func_2()
{
    ISP_SCOPE("Function 2");
    std::this_thread::sleep_for(150ms);
    Scope s(default_host, "some subtask", ISP_EVENT_ID);

    ISP_INSTANT("Some point 1");
    std::this_thread::sleep_for(150ms);
    ISP_INSTANT("Some point 2");
    std::this_thread::sleep_for(50ms);

}

void func_1()
{
    ISP_SCOPE("Function 1");

    std::this_thread::sleep_for(100ms);
    func_2();
    std::this_thread::sleep_for(200ms);
}


int main()
{
    std::thread t(func_1);
    func_1();
    t.join();
    ISP_WRITE_TIMELINE("test.json");
    return 0;
}
