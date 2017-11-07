#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "pancakes.hpp"


using std::vector;



int main()
{   stack_type v;
    flip_type flipsS;
    flip_type flipsA;


    v.push_back(1);
    v.push_back(4);
    v.push_back(2);
    v.push_back(3);

    v.push_back(0);


std::cout << "Initial Stack : " << std::endl;
for(stack_type::iterator iter = v.begin(); iter != v.end() ; iter++ ) {
    std::cout << ' '<< *iter ;
}
std::cout << ' ' << std::endl;

std::cout << " **********Simple Pancake sort *********** " << std::endl;
simple_pancake_sort(v,flipsS);

std::cout << " **********A-star Pancake sort *********** " << std::endl;

astar_pancake_sort(v,flipsA);


    return 0;
}
