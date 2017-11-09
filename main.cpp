#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "pancakes.hpp"
#include <cstdlib>      // std::rand
#include <math.h>       // power
#include <ctime>



using std::vector;

int myrandom (int i) { return std::rand()%i;}


int main(){
	int start_s, stop_s;
   	stack_type v;
    flip_type flipsS;
    flip_type flipsA;

/*  for (int i = 0; i < 10; ++i){
        v.push_back(i);
  }

  std::random_shuffle( v.begin(), v.end(),myrandom);
  std::random_shuffle( v.begin(), v.end(),myrandom);
*/
        v.push_back(1);
        v.push_back(9);
        v.push_back(6);
        v.push_back(2);
        v.push_back(5);
        v.push_back(3);
        v.push_back(8);





std::cout << "Initial Stack : " << std::endl;
for(stack_type::iterator iter = v.begin(); iter != v.end() ; iter++ ) {
    std::cout << ' '<< *iter ;
}
std::cout << std::endl;



//stack_type::iterator getMax(stack_type& stackA) {
    stack_type::iterator maximum;
    stack_type::size_type i = 0;

    maximum = max_element(v.begin(),v.end());

    // Iterate until the found maximum is not at it's place
    while(maximum == v.end()-1-i) {
        i++;
        maximum = max_element(v.begin(),v.end()-i);
    }
    std::cout << *maximum << std::endl;
 //   return maximum;
//}

std::cout << ' ' << std::endl;


    while(v.size() != 0){

    stack_type::iterator maximum;
    stack_type::size_type i = 0;

    maximum = max_element(v.begin(),v.end());

    // Iterate until the found maximum is not at it's place
    while(maximum == v.end()-1-i) {
        i++;
        maximum = max_element(v.begin(),v.end()-i);
    }
    std::cout << *maximum << std::endl;
 //   return maximum;
//}

std::cout << ' ' << std::endl;
        
        if(maximum == v.begin()) {
          std::reverse(v.begin(),v.end()); // flip the whole stack
          //flips.push_back(distance(v.begin(),v.end()));

      } else if(maximum != v.end()-1){
          //flips.push_back(distance(v.begin(),maximum));
          std::reverse(v.begin(),++maximum); // push max to the top
        }
        v.pop_back();
      }

}
/*std::cout << " **********Simple Pancake sort *********** " << std::endl;
simple_pancake_sort(v,flipsS);
start_s = clock();
std::cout << " **********A-star Pancake sort *********** " << std::endl;

astar_pancake_sort(v,flipsA);
stop_s = clock();
std::cout << "time:" << (stop_s-start_s)/double(CLOCKS_PER_SEC) << std::endl;
    return 0;
}
*/