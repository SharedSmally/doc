// insert binary data into execute. 
// See https://stackoverflow.com/questions/4864866/c-c-with-gcc-statically-add-resource-files-to-executable-library

#include <iostream>
using namespace std;

int main()
{
   extern uint8_t data[]     asm("_binary_foo_bar_start");
   extern uint8_t data_end[] asm("_binary_foo_bar_end");
   extern uint8_t data_size[] asm("_binary_foo_bar_size");

   /*
   size_t foo_size = (size_t)((void *)foo_data_size);
   void  *foo_copy = malloc(foo_size);
   assert(foo_copy);
   memcpy(foo_copy, foo_data, foo_size);
   */
   size_t foo_size = (size_t)((void *)data_size);
   std::cout << " datasize=" << foo_size << std::endl;

   for (uint8_t *byte=data; byte<data_end; ++byte) {
        std::cout << std::hex << (int)*byte << " ";
   }
   std::cout << std::endl;
}
/*
# command to compile
#testBinary: testBinary.cc
# cp demo.txt foo.bar
# g++ -o $@ $< ${CXXFLAGS} -Wl,--format=binary -Wl,foo.bar -Wl,--format=default
*/

