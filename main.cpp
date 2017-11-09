#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "pancakes.hpp"
#include <cstdlib>      // std::rand
#include <math.h>       // power

#include <set>
#include <string>
#include <sstream>
 #include <utility> // for pair
#include <tuple>
#include <unordered_set>
#include <ctime>


using std::vector;
using std::cout;
using std::endl;

int myrandom (int i) { return std::rand()%i;}

int get_size_largest_pancake(stack_type& vec){

	stack_type::iterator index_max;
	int index;
	int largest_pancake = 0;

	for(stack_type::iterator i = vec.end(); i != vec.begin(); --i){

		index_max = std::max_element(vec.begin(), i);

		if(index_max+1 != i){
			index = std::distance(vec.begin(), i-1);
			largest_pancake = vec[index];
		}
	}
	return largest_pancake;
}




stack_type::iterator getMax(stack_type& stackA) {
    stack_type::iterator maximum;
    stack_type::size_type i = 0;

    maximum = max_element(stackA.begin(),stackA.end());

    // Iterate until the found maximum is not at it's place
    while(maximum == stackA.end()-1-i) {
        i++;
        maximum = max_element(stackA.begin(),stackA.end()-i);
    }
    return maximum;
}


int main()
{   stack_type v;
    flip_type flipsA;
    flip_type flipsS;
    double start_s, stop_s;

/*  for (int i = 0; i < 10 ; ++i){
        v.push_back(i);
  }*/
       v.push_back(1);
       v.push_back(9);
       v.push_back(5);
       v.push_back(7);
       v.push_back(6);
       v.push_back(0);
       v.push_back(2);
       v.push_back(4);
       v.push_back(3);
       v.push_back(8);
       
  //std::random_shuffle( v.begin(), v.end());



std::cout << "Initial Stack : " << std::endl;
for(stack_type::iterator iter = v.begin(); iter != v.end() ; iter++ ) {
    std::cout << ' '<< *iter ;
}
std::cout << std::endl;





    stack_type copied;
    stack_type::size_type i = 0;
    stack_type::iterator maximum;
    std::copy(v.begin(),v.end(),back_inserter(copied));
    if(!is_sorted(copied.begin(), copied.end())) {
	    while(copied.size() != 0){

		    maximum = getMax(copied);
		    std::cout << "Maximum: " << *maximum << " and his position :" << distance(copied.begin(),maximum) << std::endl;
		    if(maximum == copied.begin()) {

		    	std::cout << " Stack before flipping : " << std::endl;
				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

				std::reverse(copied.begin(),copied.end()); // flip the whole stack

				std::cout << " Stack after flipping : " << std::endl;

				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    flipsA.push_back(distance(copied.begin(),copied.end()));
			   	copied.pop_back();


			} else if(maximum != copied.end()-1){
			    

				std::cout << " Stack before flipping : " << std::endl;
				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    std::reverse(copied.begin(),++maximum); // push max to the bottom

				std::cout << " Stack after flipping : " << std::endl;

				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    flipsA.push_back(distance(copied.begin(),maximum));

			    				std::cout << " Stack before flipping : " << std::endl;
				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    std::reverse(copied.begin(),copied.end()); // flip the whole stack
		    	flipsA.push_back(distance(copied.begin(),copied.end()));

				std::cout << " Stack after flipping : " << std::endl;

				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;


    		    copied.pop_back();

		    }
		    else{
			    copied.pop_back();

		    }



			std::cout << std::endl;		


	    }
	}


    cout << " The flips vector contains : ";
    for(flip_type::iterator it = flipsA.begin(); it != flipsA.end() ; it++ ) {
        cout << ' '<<*it ;
    }

std::cout << "Initial Stack : " << std::endl;
for(stack_type::iterator iter = v.begin(); iter != v.end() ; iter++ ) {
    std::cout << ' '<< *iter ;
}
std::cout << std::endl;





    stack_type copied;
    stack_type::size_type i = 0;
    stack_type::iterator maximum;
    std::copy(v.begin(),v.end(),back_inserter(copied));
    if(!is_sorted(copied.begin(), copied.end())) {
	    while(copied.size() != 0){

		    maximum = getMax(copied);
		    std::cout << "Maximum: " << *maximum << " and his position :" << distance(copied.begin(),maximum) << std::endl;
		    if(maximum == copied.begin()) {

		    	std::cout << " Stack before flipping : " << std::endl;
				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

				std::reverse(copied.begin(),copied.end()); // flip the whole stack

				std::cout << " Stack after flipping : " << std::endl;

				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    flipsA.push_back(distance(copied.begin(),copied.end()));
			   	copied.pop_back();


			} else if(maximum != copied.end()-1){
			    

				std::cout << " Stack before flipping : " << std::endl;
				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    std::reverse(copied.begin(),++maximum); // push max to the bottom

				std::cout << " Stack after flipping : " << std::endl;

				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    flipsA.push_back(distance(copied.begin(),maximum));

			    				std::cout << " Stack before flipping : " << std::endl;
				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;

			    std::reverse(copied.begin(),copied.end()); // flip the whole stack
		    	flipsA.push_back(distance(copied.begin(),copied.end()));

				std::cout << " Stack after flipping : " << std::endl;

				for(stack_type::iterator iter = copied.begin(); iter != copied.end() ; iter++ ) {
			    std::cout << ' '<< *iter ;
				}
				std::cout << ' ' << std::endl;


    		    copied.pop_back();

		    }
		    else{
			    copied.pop_back();

		    }



			std::cout << std::endl;		


	    }
	}


    cout << " The flips vector contains : ";
    for(flip_type::iterator it = flipsA.begin(); it != flipsA.end() ; it++ ) {
        cout << ' '<<*it ;
    }











std::cout << ' ' << std::endl;

std::cout << " **********Simple Pancake sort *********** " << std::endl;
//simple_pancake_sort(v,flipsS);

start_s = clock();
std::cout << " **********A-star Pancake sort *********** " << std::endl;
//astar_pancake_sort(v,flipsA);
stop_s = clock();

double time = (stop_s - start_s)/double(CLOCKS_PER_SEC);
std::cout << "time: " << time << std::endl;

    return 0;
}
