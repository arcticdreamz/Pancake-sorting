

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include "pancakes.hpp"
#include <sstream>
 #include <utility> // for pair
#include <tuple>
#include <unordered_set>

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::set;
using std::string;
using std::get;
using std::unordered_set;


//typedef pair<int,int> cost;
//typedef pair<stack_type,flip_type> pancake_stack_raw;
//typedef pair<pair<stack_type,flip_type>,pair<int,int> > pancake_stack;

typedef std::tuple<int,int,stack_type,flip_type> pancake_stack; // real cost, cout est,

//Compare function for the set
 bool compare(const pancake_stack stackA, const pancake_stack stackB){

     int totalCostA = get<0>(stackA)+ get<1>(stackA);
     int totalCostB = get<0>(stackB)+ get<1>(stackB);
     if(totalCostA == totalCostB){
        return stackA < stackB;
     }
     return totalCostA < totalCostB ;
 }


// Get the estimated cost of a stack; the size of the largest pancake not yet at its place
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

int getEstCost(pancake_stack& stackA)  {
    return *(getMax(get<2>(stackA)));
}



size_t stackHash(const pancake_stack& stackA) {
    stack_type v = get<2>(stackA);

    std::hash<int> hasher;
    size_t value = 0;
    for (int i : v) {
        value ^= hasher(i) + 0x9e3779b9 + (value<<6) + (value>>2);
    }
    return value;
}

//size_t stackHash(pancake_stack& stackA) {
//    stack_type v = get<2>(stackA);
//
//    size_t intHash = 1;
//    stack_type::reverse_iterator riter = v.rbegin();
//    int R = 17790;
//    unsigned int i = 0;
//    while(i < v.size() && riter != v.rend()) {
//            intHash *= 2*(*riter) + R;
//            riter++;
//            i++;
//            //std::cout << intHash << std::endl;
//	}
//
//return intHash/2 ; //+1 car on perd de la precision
//}



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

    //Creating a container to store generated stacks
    unordered_set<size_t> StackSet;
    std::pair<unordered_set<size_t>::iterator,bool> foundStack;
    //Insert the initial stack into the set
    foundStack = StackSet.insert(stackHash(initial_stack));

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
        	foundStack = StackSet.insert(stackHash(child_stack));
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

    cout << "Output array: ";
    for(stack_type::iterator iter = get<2>(parent_stack).begin(); iter != get<2>(parent_stack).end() ; iter++ ) {
        cout << ' '<<*iter ;
    }


}


void simple_pancake_sort(const stack_type& pancakes, flip_type& flips){

    stack_type copied;
    stack_type::size_type i = 0;
    stack_type::iterator maximum;

    std::copy(pancakes.begin(),pancakes.end(),back_inserter(copied));
    if(!is_sorted(copied.begin(), copied.end())) {
	    while(copied.size() != 1){

		    maximum = getMax(copied);
		    
		    if(maximum == copied.begin()) {
                flips.push_back(0);

			    std::reverse(copied.begin(),copied.end()); // flip the whole stack
			    flips.push_back(distance(copied.begin(),copied.end()-1));

			} else if(maximum != copied.end()-1){
			    flips.push_back(distance(copied.begin(),maximum));
			    std::reverse(copied.begin(),++maximum); // flip the max to the top
			    std::reverse(copied.begin(),copied.end()); // flip the whole stack
		    	flips.push_back(distance(copied.begin(),copied.end()-1));


		    }
		    copied.pop_back();
	    }
	}
	    cout << "The flip vector contains :";
	    for(i = 0; i< flips.size();i++) {
	        cout << ' ' << flips[i];
		}
		cout << endl;

}





//
//      cout << " The flips vector of child contains : ";
//        for(flip_type::iterator it = child_stack.first.second.begin(); it != child_stack.first.second.end() ; it++ ) {
//            cout << *it ;
//        }
//        cout << endl;




//bool insertIntoMap(map<std::string,int> poppedStacksMap, pancake_stack stackA) {
//    std::stringstream result;
//    std::copy(stackA.first.first.begin(), stackA.first.first.end(), std::ostream_iterator<int>(result, ""));
//    std::string pancakestring = result.str().c_str();
//
//    static int number = 0;
//
//    cout << pancakestring<< endl;
//    pair<map<std::string,int>::iterator,bool> foundStack;
//    foundStack = poppedStacksMap.insert (pair<std::string,int>(pancakestring,number));
//    number++;
//    if(foundStack.second == true){
//        number--;
//        cout << "element 'z' already existed";
//        cout << " with a value of " << foundStack.first->second << '\n';
//    }
//    return foundStack.second;
//
//}


//            cout << " The pancake vector of child "<< i << " contains : ";
//            for(stack_type::iterator it = child_stack.first.first.begin(); it != child_stack.first.first.end() ; it++ ) {
//                cout << *it ;
//           }
//           cout << endl;


//        cout << "Pushing ";
//        for(stack_type::iterator iter = parent_stack.first.first.begin(); iter != parent_stack.first.first.end() ; iter++ ) {
//            cout << ' '<<*iter ;
//        }
//


//    cout << "The StackSet contains : " <<  endl;
//   sort(StackSet.begin(),StackSet.end());
//    for(std::vector<string>::iterator it = StackSet.begin(); it != StackSet.end() ; it++ ) {
//        cout << ' '<<*it << endl; ;
//    }
//    cout << endl;
