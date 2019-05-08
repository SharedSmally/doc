#include <chrono>
#include <iostream>
#include <sstream>
using namespace std;

#include <Executor.h>

class Task : public Runnable
{
public:
	Task(int i) : ind_(i){}

	virtual void run() {
		std::ostringstream oss;
		oss << "Running task in " << std::this_thread::get_id() << "; ind=" << ind_ << "\n";
		std::cout << oss.str(); oss.clear(); oss.str("");
		std::this_thread::sleep_for (std::chrono::seconds(1));
		oss << "Finish task in " << std::this_thread::get_id() << "; ind=" << ind_ << "\n";
		std::cout << oss.str(); oss.clear(); oss.str("");
	}
protected:
	int ind_;
};

void test1()
{
    ThreadExecutor executor;
    for (int i=0; i<10; i++) {
    	RunnablePtr task =  std::make_shared<Task>(i) ;
    	executor.execute( task );
    }
    std::this_thread::sleep_for (std::chrono::seconds(10));
}

void test2()
{
    ThreadPoolExecutor executor(2);
    for (int i=0; i<10; i++) {
    	RunnablePtr task =  std::make_shared<Task>(i) ;
    	executor.execute( task );
    }
    std::this_thread::sleep_for (std::chrono::seconds(10));
}

int main()
{
     test1();
     //test2();

}
