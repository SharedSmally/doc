#include <string>
#include <exception>

#include <dlfcn.h>

class DllException : public std::exception
{
public:
    DllException(const std::string & reason)
    : reason_(reason){}
    virtual ~DllException() noexcept {}

    virtual const char* what() const throw()
    {
        return reason_.c_str();
    }
    const std::string & reason() const { return reason_; }

protected:
    std::string reason_;
};

class DllLoader
{

public:
    DllLoader(const std::string & filename, bool lazy=true, bool global=true) throw (DllException)
    {
        int flag = lazy ? RTLD_LAZY : RTLD_NOW;
        flag |= global ? RTLD_GLOBAL : RTLD_LOCAL;
        open(filename, flag);
    }
    DllLoader(const std::string & filename, int flag) throw (DllException)
    {
        open(filename, flag);
    }

    void * getSymbol(const std::string & symbol)
    {
        void * ptr = dlsym(handle_, symbol.c_str());
        if (ptr == nullptr) throw DllException(dlerror());
        return ptr;
    }

    // return function pointer
    //returned-function-return-type (* function-name (parameter-list) ) (function-to-return-parameter-list)
    template <typename R, typename T>
    R (* getFunction (const std::string & symbol) ) (T)
    {
        void * ptr = dlsym(handle_, symbol.c_str());
        if (ptr == nullptr) throw DllException(dlerror());

        //  POSIX.1-2003 TC1 conversion: see man dlopen
#ifdef POSIX_2003_TC1
        R (*fptr)(T);
        *(void **) (&fptr) = ptr;
        return fptr;
#else
        return (R (*)(T))  ptr; //more naturally conversion
#endif
    }

    void (* getF0 (const std::string & symbol) ) (void )
    {
        void * ptr = dlsym(handle_, symbol.c_str());
        if (ptr == nullptr) throw DllException(dlerror());

        //  POSIX.1-2003 TC1 conversion: see man dlopen
#ifdef POSIX_2003_TC1
        void (*fptr)(void);
        *(void **) (&fptr) = ptr;
        return fptr;
#else
        return (void (*)(void)) ptr; //more naturally conversion
#endif
    }

    /*
    template<typename T, typename... Args>
    void func(T t, Args... args) // recursive variadic function
    */
    template <typename T, typename... Args>
    void (* getF1 (const std::string & symbol) ) (T value, Args... args)
    {
        void * ptr = dlsym(handle_, symbol.c_str());
        if (ptr == nullptr) throw DllException(dlerror());

        //  POSIX.1-2003 TC1 conversion: see man dlopen
#ifdef POSIX_2003_TC1
        void (*fptr)(T, Args...);
        *(void **) (&fptr) = ptr;
        return fptr;
#else
        return (void (*)(T, Args...)) ptr; //more naturally conversion
#endif
    }

    template <typename R, typename... Args>
    R (* getFn (const std::string & symbol) ) ( Args... args)
    {
        void * ptr = dlsym(handle_, symbol.c_str());
        if (ptr == nullptr) throw DllException(dlerror());

        //  POSIX.1-2003 TC1 conversion: see man dlopen
#ifdef POSIX_2003_TC1
        R (*fptr)(Args...);
        *(void **) (&fptr) = ptr;
        return fptr;
#else
        return (R (*)(Args...)) ptr; //more naturally conversion
#endif
    }

    ~DllLoader()
    {
        dlclose(handle_);
    }

protected:
    void open(const std::string & filename, int flag) throw (DllException)
    {
        handle_ = dlopen(filename.empty()?nullptr:filename.c_str(), flag);

        if (handle_ == nullptr)
        {
            throw DllException(dlerror());
        }
    }

protected:
   void * handle_;
};


#include <iostream>
using namespace std;

int main()
{
   cout << "test dll loading" << endl;
   double (*cosine)(double);
   try
   {
      DllLoader loader("libm.so");
      cosine = (double (*)(double)) loader.getSymbol("cos");
      cout << "cos(2.0)=" << (*cosine)(2.0) << endl;

      //auto sine=loader.getFunction<double, double>("sin");
      auto sine=loader.getFn<double, double>("sin");
      cout << "sin(2.0)=" << (*sine)(2.0) << endl;

      auto bc=loader.getFn<double, double>("bc"); ///lib64/libm.so.6: undefined symbol: bc
   }
   catch (const DllException & ex)
   {
       cout << " DllException:" << ex.reason() << endl;
   }
   return 0;
}
