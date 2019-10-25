#include <iostream>
#include <sstream>
#include <thread>

struct Counter
{
    Counter()
    {
        std::ostringstream oss;
        oss << "Thread #" << std::this_thread::get_id() << " constructs Counter\n";
        std::cout << oss.str() << std::endl;
    }
    ~Counter()
     {
         std::ostringstream oss;
         oss << "Thread #" << std::this_thread::get_id() << " was called "
                   << c << " times";
         std::cout << oss.str() << std::endl;
     }

    unsigned int c = 0;
    void increment() { ++c; }
};

// thread_local: declared as global variable, but each thread has its own copy
// not created of not used in the thread
thread_local Counter c;

void do_work()
{
    c.increment();
}

void do_nothing(){}

int main() {
    //c.increment(); c is not created in main thread if not called
    std::thread t1(do_work);
    std::thread t2(do_work);
    t1.join();
    t2.join();
}
