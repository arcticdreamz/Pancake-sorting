#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "pancakes.hpp"
#include <cstdlib>      // std::rand
#include <math.h>       // power




using std::vector;

int myrandom (int i) { return std::rand()%i;}


int main()
{   stack_type v;
    flip_type flipsS;
    flip_type flipsA;

  for (int i = 0; i < 7; ++i){
        v.push_back(i);
  }

  std::random_shuffle( v.begin(), v.end(),myrandom);



std::cout << "Initial Stack : " << std::endl;
for(stack_type::iterator iter = v.begin(); iter != v.end() ; iter++ ) {
    std::cout << ' '<< *iter ;
}
std::cout << std::endl;




//int stackHash(pancake_stack& stackA) {
//    stack_type v = get<2>(stackA);
//
//    long long intHash = 0;
//    stack_type::reverse_iterator riter = v.rbegin();
//
//    unsigned int i = 0;
//    while(i < v.size() && riter != v.rend()) {
//            intHash += (*riter) * pow(10,i);
//            riter++;
//            i++;
//            std::cout << intHash << std::endl;
//	}
//
//return intHash+ 1 ; //+1 car on perd de la precision
//}


std::cout << ' ' << std::endl;

std::cout << " **********Simple Pancake sort *********** " << std::endl;
//simple_pancake_sort(v,flipsS);

std::cout << " **********A-star Pancake sort *********** " << std::endl;

astar_pancake_sort(v,flipsA);

    return 0;
}
