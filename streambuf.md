## StreamBuffer

- [Stream Buffer Reference](http://www.cplusplus.com/reference/streambuf/streambuf/)
- [Cop, Load, Redirect and Tee streams](http://wordaligned.org/articles/cpp-streambufs)
    - Copy
```
void stream_copy(std::ostream & dst, std::istream & src)
{
    dst << src.rdbuf();
}
```
    - Load
```
// Return a named file's contents as a string
std::string load_file(char const * filepath)
{
    std::ifstream src(filepath);
    std::ostringstream buf;
    buf << src.rdbuf();
    return buf.str();
}
```
    - Redirect
```
#include <fstream>
#include <iostream>

class redirecter
{
public:
    redirecter(std::ostream & dst, std::ostream & src)
        : src(src), sbuf(src.rdbuf(dst.rdbuf())) {}
    ~redirecter() { src.rdbuf(sbuf); }
private:
    std::ostream & src;
    std::streambuf * const sbuf;
};

void hello_world()
{
    std::cout << "Hello, world!\n";
}

int main()
{
    //redirect must be destroyed before log to restore std::cout’s original buffer. 
    std::ofstream log("hello-world.log");
    redirecter redirect(log, std::cout);
    hello_world();
    return 0;
}
```
    - Tee    
```
#include <iostream>

template <typename char_type,
          typename traits = std::char_traits<char_type> >
class basic_teebuf:
    public std::basic_streambuf<char_type, traits>
{
public:
    typedef typename traits::int_type int_type;
    
    basic_teebuf(std::basic_streambuf<char_type, traits> * sb1,
                 std::basic_streambuf<char_type, traits> * sb2)
      : sb1(sb1)
      , sb2(sb2)
    { }
    
private:    
    virtual int sync() {
        int const r1 = sb1->pubsync();
        int const r2 = sb2->pubsync();
        return r1 == 0 && r2 == 0 ? 0 : -1;
    }
    
    virtual int_type overflow(int_type c)    {
        int_type const eof = traits::eof();
        
        if (traits::eq_int_type(c, eof)) {
            return traits::not_eof(c);
        } else {
            char_type const ch = traits::to_char_type(c);
            int_type const r1 = sb1->sputc(ch);
            int_type const r2 = sb2->sputc(ch);
            
            return
                traits::eq_int_type(r1, eof) ||
                traits::eq_int_type(r2, eof) ? eof : c;
        }
    }
    
private:
    std::basic_streambuf<char_type, traits> * sb1;
    std::basic_streambuf<char_type, traits> * sb2;
};

typedef basic_teebuf<char> teebuf;

#include <fstream>
int main()
{
    std::ofstream log("hello-world.log");
    teestream tee(std::cout, log);
    tee << "Hello, world!\n";
    return 0;
}

#tee all std::cout's to a logfile and the console
int main()
{
    // initial buffer of std::cout
    std::streambuf * const coutbuf = std::cout.rdbuf();

    // open logfile
    std::ofstream log("hello-world.log");

    // create tee buffer that directs everything to console and file
    teebuf tee(coutbuf, log.rdbuf());

    // replace default cout buffer by teebuf
    std::cout.rdbuf(&tee);

    // prints !!!Hello World!!! to console and to file
    std::cout << "!!!Hello World!!!" << std::endl;

    // reset std::cout default buffer to prevent error at termination
    std::cout.rdbuf(coutbuf);
    return 0;
}
```

- [Print Binary as HexDecimal](https://stackoverflow.com/questions/10599068/how-do-i-print-bytes-as-hexadecimal):
