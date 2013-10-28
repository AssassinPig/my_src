#define BOOST_DATE_TIME_SOURCE
//#define BOOST_THREAD_NO_LIB
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/pthread/once.hpp>
using namespace boost;

#include <string>
#include <iostream>
using namespace std;


mutex io_mu;
//void printing(atom_int& x, const string& s)
void printing(const string& str)
{
	for (int i=0; i<5; ++i) {
		mutex::scoped_lock lock(io_mu);
		cout << str <<endl;
	}
}


class A
{
public:
	void print()
	{
		cout<<"A::print()"<<endl;	
	}

	void print1(int n)
	{
		cout<<"A::print(int n) with "<<n<<endl;	
	}
};

int main()
{
	//atom_int x;
	
	//thread(printing, ref(x), "hello");
	//thread(printing, ref(x), "boost");
	boost::thread t1(printing, "hello"); 
	t1.join();

	A a;
	boost::function<void ()> fun = boost::bind(&A::print, &a);
	fun();

	boost::function<void (int)> fun1 = boost::bind(&A::print1, &a, _1);
	fun1(2);

}

