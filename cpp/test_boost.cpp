#define BOOST_DATE_TIME_SOURCE
//#define BOOST_THREAD_NO_LIB
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/pthread/once.hpp>
//#include <libs/thread/src/pthread/thread.cpp>
//#include <libs/thread/src/pthread/once.cpp>
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

int main()
{
//atom_int x;

//thread(printing, ref(x), "hello");
//thread(printing, ref(x), "boost");
	boost::thread t1(printing, "hello"); 
	t1.join();
}

