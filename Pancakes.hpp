#ifndef PANCAKES_H
#define PANCAKES_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include <sstream>
#include <utility>

typedef std::vector<int> stack_type;
typedef std::vector<stack_type::size_type> flip_type;

void simple_pancake_sort(const stack_type& pancakes, flip_type& flips);
void astar_pancake_sort(const stack_type& pancakes, flip_type& flips);

stack_type::iterator findMax(stack_type& v);

void flip(stack_type v, stack_type::iterator& flip_position);

std::string stackToString(std::pair<std::pair<stack_type,flip_type>,std::pair<int,int> >& stackA);
int getEstCost(std::pair<std::pair<stack_type,flip_type>,std::pair<int,int> >& stackA);
bool comp(const std::pair<std::pair<stack_type,flip_type>,std::pair<int,int> > stackA, const std::pair<std::pair<stack_type,flip_type>,std::pair<int,int> > stackB);



#endif // PANCAKES_H
