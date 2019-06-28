#include <Group.h>

class MyString : public String
{
public:
        MyString(){}
        MyString(const String & val) : String(val){};
    virtual ~MyString() { std::cout << "~MyString" << std::endl;}
};

typedef Group<MyString> MyProperties;

void test1()
{
    MyProperties ps;
    ps.set("MyName1", MyString("MyValue1") );
    ps.set("MyName2", MyString("MyValue2") );
    ps.output();

    bool ret = ps.set("MyName1", MyString("MyValue3"));
    std::cout << "\ninsert duplicated MyName1:" << ret << "\n";
    ps.output();

    ret = ps.set("MyName1", MyString("MyValue3"), true);
    std::cout << "\ninsert duplicated MyName1:" << ret << "\n";
    ps.output();

    std::cout << "\n MyName1=" << ps.get("MyName1") << "\n";
    std::cout << " MyName2=" << ps.get("MyName2") << "\n";
    std::cout << " MyName3=" << ps.get("MyName3") << "\n";

    ret = ps.erase("MyName1");
    std::cout << "\nerase MyName1:" << ret << "\n";
    ps.output();

    ret = ps.erase("MyName3");
    std::cout << "\nerase MyName3:" << ret << "\n";
    ps.output();
}

void test2()
{
    Group<MyString *> ps;
    MyString val1("MyValue1");
    MyString val2("MyValue1");
    MyString val3("MyValue1");

    ps.set("MyName1", val1 );
    ps.set("MyName2", val2 );
    ps.output();

    bool ret = ps.set("MyName1", val3);
    std::cout << "\ninsert duplicated MyName1:" << ret << "\n";
    ps.output();

    ret = ps.set("MyName1", val3, true);
    std::cout << "\ninsert duplicated MyName1:" << ret << "\n";
    ps.output();

    std::cout << "\n MyName1=" << *(ps.get("MyName1")) << "\n";
    std::cout << " MyName2=" << *(ps.get("MyName2")) << "\n";
    //std::cout << " MyName3=" << *(ps.get("MyName3")) << "\n"; //nullptr

    ret = ps.erase("MyName1");
    std::cout << "\nerase MyName1:" << ret << "\n";
    ps.output();

    ret = ps.erase("MyName3");
    std::cout << "\nerase MyName3:" << ret << "\n";
    ps.output();

}

void test3()
{
        PropertiesGroup group;
        Properties * props1 = &(group.obtain("group1"));
        props1->set("name1_1","value1_1");
        props1->set("name1_2","value1_2");

        Properties * props2 = &(group.obtain("group2"));
        props2->set("name2_1","value2_1");
        props2->set("name2_2","value2_2");

        std::cout << group << std::endl;
}

int main()
{
        //test1();
        //test2();
        test3();
}
