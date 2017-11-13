

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <unordered_set>
#include <utility> // for pair
#include <tuple>
#include "pancakes.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::set;
using std::string;
using std::get;
using std::unordered_set;


// <RealCost,Estimated End Cost,stack vector,flip vector>
typedef std::tuple<int,int,stack_type,flip_type> pancake_stack; 

/* ------------------------------------------------------------------------- *
 * Comparison function to sort the vectors in ascending order of cost in the set

 * PARAMETERS
 * - Two tuples that contain the vector of ints to sort as well as it's realCost and Estimated
 * end cost
 * ------------------------------------------------------------------------- */
 bool compare(const pancake_stack stackA, const pancake_stack stackB){

     int totalCostA = get<0>(stackA)+ get<1>(stackA);
     int totalCostB = get<0>(stackB)+ get<1>(stackB);
     if(totalCostA == totalCostB){
        return stackA < stackB;
     }
     return totalCostA < totalCostB ;
 }


/* ------------------------------------------------------------------------- *
 * Function that returns an iterator to the max that is not at it's place of a vector 
 * 
 * PARAMETERS
 * - One vector of ints
 * end cost
 * ------------------------------------------------------------------------- */
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



/* ------------------------------------------------------------------------- *
 * Function that generates a hashCode from a given vector of ints
 * 
 * PARAMETERS
 * - One vector of ints
 * ------------------------------------------------------------------------- */
size_t stackHash(const stack_type& stackA) {

    size_t intHash = 0;
    for (int i : stackA) {
        intHash = intHash*10 + i;
    }
    return intHash;
}

/* ------------------------------------------------------------------------- *
 * Function that returns the estimated end cost of a vector of ints
 * 
 * PARAMETERS
 * - One tuple containing information about the vector of ints to sort
 * ------------------------------------------------------------------------- */
int getEstCost(pancake_stack& stackA)  {
    return *(getMax(get<2>(stackA)));
}


void astar_pancake_sort(const stack_type& pancakes, flip_type& flips) {

    stack_type pancakes_copy;

    // Pointer to the comparison function
    bool(*compare_pt)(const pancake_stack, const pancake_stack) = compare;

    //Create the set
    set<pancake_stack,bool(*)(pancake_stack,pancake_stack)> p_queue(compare_pt);

    //Copy the original pancakes
    std::copy(pancakes.begin(),pancakes.end(),back_inserter(pancakes_copy));

    //Create and initialie the tuple
    pancake_stack initial_stack = std::make_tuple(0,0,pancakes_copy,flips);
    pancake_stack parent_stack = initial_stack ;

    //Inserting the first stack
    p_queue.insert(initial_stack); 

    //Creating a container and iterator to store generated stacks
    unordered_set<size_t> StackSet;
    std::pair<unordered_set<size_t>::iterator,bool> foundStack;

    //Insert the initial stack into the set
    foundStack = StackSet.insert(stackHash(get<2>(initial_stack)));

    while(!std::is_sorted(get<2>(parent_stack).begin(),get<2>(parent_stack).end())) {

        //Extract the lowest cost stack 
        if(!p_queue.empty()){ 
        	parent_stack = *(p_queue.begin()); 
            p_queue.erase(p_queue.begin()); 
        }


        //Generate children from parent stack
        for(stack_type::size_type i = 1; i < get<2>(parent_stack).size(); i++) { 

            pancake_stack child_stack = parent_stack;

            //Flip the stack
            std::reverse(get<2>(child_stack).begin(),get<2>(child_stack).begin()+ 1 + i); 

            //Looking in the StackSet if the stack hasn't already been encountered
        	foundStack = StackSet.insert(stackHash(get<2>(child_stack)));
            if(foundStack.second == false){
                continue;
            }
            //Pushing the flip
            get<3>(child_stack).push_back(i); 

            //Computing the cost
            int realCost = i+1; // i+1 pancakes were flipped
            int estCost = getEstCost(child_stack); 

            get<0>(child_stack) += realCost; // Add the child's realCost to the parent's realCost
            get<1>(child_stack) = estCost;

            //Insert child into the set
            p_queue.insert(child_stack);
        }
    }

    cout << "The size of the priority queue is : " << p_queue.size() << endl;
    cout << "The best cost was: " << get<0>(parent_stack) + get<1>(parent_stack) <<endl;
    cout << " The flips vector contains : ";
    for(flip_type::iterator it = get<3>(parent_stack).begin(); it != get<3>(parent_stack).end() ; it++ ) {
        cout << ' '<<*it ;
    }
    cout << endl;
}



void simple_pancake_sort(const stack_type& pancakes, flip_type& flips){

    stack_type pancakes_copy;
    stack_type::iterator maximum;

    std::copy(pancakes.begin(),pancakes.end(),back_inserter(pancakes_copy));

    if(!is_sorted(pancakes_copy.begin(), pancakes_copy.end())) {
	    while(pancakes_copy.size() != 1){

            //Extract the maximum
		    maximum = getMax(pancakes_copy);
		    
            //If the maximum is at the beginning, we just flip the whole stack
		    if(maximum == pancakes_copy.begin()) {
			    std::reverse(pancakes_copy.begin(),pancakes_copy.end()); // flip the whole stack
			    flips.push_back(distance(pancakes_copy.begin(),pancakes_copy.end()-1));


			}else if(maximum != pancakes_copy.end()-1){
			    flips.push_back(distance(pancakes_copy.begin(),maximum));
			    std::reverse(pancakes_copy.begin(),++maximum); // flip the max to the top
			    std::reverse(pancakes_copy.begin(),pancakes_copy.end()); // flip the whole stack
		    	flips.push_back(distance(pancakes_copy.begin(),pancakes_copy.end()-1));
		    }
		    pancakes_copy.pop_back();
	    }
	}

    cout << "The flip vector contains :";
    for(flip_type::size_type i = 0; i< flips.size();i++) {
        cout << ' ' << flips[i];
	}
	cout << endl;
}