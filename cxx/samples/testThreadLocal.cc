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

If you're using Pthreads you can do the following:

//declare static data members
pthread_key_t AnotherClass::key_value;
pthread_once_t AnotherClass::key_init_once = PTHREAD_ONCE_INIT;

//declare static function
void AnotherClass::init_key()
{
    //while you can pass a NULL as the second argument, you 
    //should pass some valid destrutor function that can properly
    //delete a pointer for your MyClass
    pthread_key_create(&key_value, NULL);
}

void AnotherClass::threadSpecificAction()
{
  //Initialize the key value
  pthread_once(&key_init_once, init_key);

  //this is where the thread-specific pointer is obtained
  //if storage has already been allocated, it won't return NULL

  MyClass *instance = NULL;
  if ((instance = (MyClass*)pthread_getspecific(key_value)) == NULL)
  {
    instance = new MyClass;
    pthread_setspecific(key_value, (void*)instance);
  }

  instance->doSomething();
}
