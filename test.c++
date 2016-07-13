// --------------------------------
// projects/c++/deque/TestDeque.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// http://www.cplusplus.com/reference/deque/deque/

// --------
// includes
// --------

#include <deque>     // deque
#include <stdexcept> // invalid_argument, out_of_range
#include "gtest/gtest.h"


#include "Deque.h"

// -----
// Using
// -----

using namespace std;



// -----
// Types
// -----


int main(){
	// my_deque<int> y;
	// cout<<y.empty() << " " << y.size() << endl;
	my_deque<int> x (13,2);
	// cout<<"back " <<x.back()<<endl;
	// auto i = begin(x);
	// cout<< "iter " << *i <<endl;
	// cout<< "iter " << *(++i) <<endl;

	// cout<< "iter " << *(++i) <<endl;
	// cout<< "iter " << *(++i) <<endl;
	// cout<< "iter " << *(++i) <<endl;




    my_deque<int> z (x);
	// cout<<"size ::" <<z.size()<<endl;
	// auto i = z.erase(z.begin());
	// cout<<"i ::" <<*i<<endl;

    z.resize(15,5);
	// cout<<"size ::" <<z.size()<<endl;
 //    // auto i = z.insert(z.begin(),4);
	for (int i =0 ;i < z.size();++i){
		cout<<z[i]<<endl;
		cout<<"i: "<<i<<endl;
	}
   cout<< "finish"<<endl;
	return 0;
}




// -----
// Tests
// -----


