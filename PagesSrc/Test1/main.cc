#include <iostream>

using namespace std;

class A
{
public:
    virtual void print(int a = 10)
    {
        cout << "A : " << a << endl;
    }
	virtual void func()
	{
		cout<<"abc"<<endl;
	}
};

class B:public A
{
public:
    void print(int a = 20)
    {
        cout << "B : " << a << endl;
    }
};

int main()
{
    A a;
    B b;
    A *pA = &b;

    a.print();
    b.print();
	b.func();
    pA->print();
	pA->func();
    return 0;
}
