
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

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::set;
using std::string;
using std::get;


//typedef pair<int,int> cost;
//typedef pair<stack_type,flip_type> pancake_stack_raw;
//typedef pair<pair<stack_type,flip_type>,pair<int,int> > pancake_stack;

typedef std::tuple<int,int,stack_type,flip_type> pancake_stack; // real cost, cout est, 

//Compare function for the set
 bool comp(const pancake_stack stackA, const pancake_stack stackB){

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



string stackToString(pancake_stack& stackA) {
	stack_type vector = get<2>(stackA);
	std::stringstream result;
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<int>(result, ""));
	std::string pancakestring = result.str();
	return pancakestring;
}



void astar_pancake_sort(const stack_type& pancakes, flip_type& flips) {

    stack_type pancakes_copy;
    stack_type::iterator iter;

    // Pointer to the comparison function
    bool(*comp_pt)(const pancake_stack, const pancake_stack) = comp;

    //Create the set
    set<pancake_stack,bool(*)(pancake_stack,pancake_stack)> p_queue(comp_pt);

    //Copy the original pancakes
    std::copy(pancakes.begin(),pancakes.end(),back_inserter(pancakes_copy));

    //Initialise the stacks
    pancake_stack initial_stack = std::make_tuple(0,0,pancakes_copy,flips);

    //Create a sorted stack to compare
    stack_type sorted_stack = pancakes_copy;
    sort(sorted_stack.begin(),sorted_stack.end());


    pancake_stack parent_stack = initial_stack;

    p_queue.insert(initial_stack); //First call

    set<string> stringStackSet;

    set<string>::iterator foundString;

    while(!std::equal(get<2>(parent_stack).begin(),get<2>(parent_stack).end(),sorted_stack.begin())) {

        if(!p_queue.empty()){ //don't want to dereference end pointer
        	parent_stack = *(p_queue.begin()); //Extract from the priority queue
            p_queue.erase(p_queue.begin()); //Delete the extracted element from the priority queue
        }

        if(stringStackSet.empty()) {
        	stringStackSet.insert(stackToString(initial_stack));
        }else{
        	//Looking in the stringStackSet if the stack hasn't already been encountered
	        foundString = std::find(stringStackSet.begin(), stringStackSet.end(),stackToString(parent_stack));
	      	if(foundString != stringStackSet.end()){
	//            cout << *foundString << " has already been generated" << endl;
	            continue;
			}
        }
     	//cout << "Pushing parent into the stringStackSet" << endl;
        stringStackSet.insert(stackToString(parent_stack));

        // generate children from parent stack
        for(stack_type::size_type i = 1; i < get<2>(parent_stack).size(); i++) { // generate children from parent stack

            pancake_stack child_stack = parent_stack;

            get<3>(child_stack).push_back(i); //Pushing the flip
            std::reverse(get<2>(child_stack).begin(),get<2>(child_stack).begin()+ 1 + i); // flip at index i (i+1 because reverse() second argument is non-inclusive)

            //Looking in the stringStackSet if the stack hasn't already been encountered
            foundString = std::find(stringStackSet.begin(), stringStackSet.end(),stackToString(child_stack));

            //If the stack has indeed already been encountered before, we just loop again
            if(foundString != stringStackSet.end()){
                continue;
            }

            //Computing the cost
            int realCost = i+1; // i+1 pancakes were flipped
            int estCost = getEstCost(child_stack); //Compute the estimated end cost
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

    stack_type copied;
    stack_type::size_type i = 0;
    stack_type::iterator maximum;



    std::copy(pancakes.begin(),pancakes.end(),back_inserter(copied));


//    while(i < copied.size()){
//
//
//        maximum = max_element(copied.begin(),copied.end()- i );
//        flips.push_back(distance(copied.begin(),maximum));
//
//        std::reverse(copied.begin(),++maximum); // push max to the top
//        std::reverse(copied.begin(),copied.end()-i); // put the max at it's place
//        flips.push_back(distance(copied.begin(),copied.end()-i-1));
//        i++;
//    }


    while(copied.size() != 0){


        maximum = getMax(copied);
//        if(maximum == copied.begin()) {
//                break;
//        }
        flips.push_back(distance(copied.begin(),maximum));

        std::reverse(copied.begin(),++maximum); // push max to the top
        std::reverse(copied.begin(),copied.end()); // put the max at it's place
        copied.pop_back();
        flips.push_back(distance(copied.begin(),copied.end()));
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
//    pair<map<std::string,int>::iterator,bool> ret;
//    ret = poppedStacksMap.insert (pair<std::string,int>(pancakestring,number));
//    number++;
//    if(ret.second == true){
//        number--;
//        cout << "element 'z' already existed";
//        cout << " with a value of " << ret.first->second << '\n';
//    }
//    return ret.second;
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


//    cout << "The stringStackSet contains : " <<  endl;
//   sort(stringStackSet.begin(),stringStackSet.end());
//    for(std::vector<string>::iterator it = stringStackSet.begin(); it != stringStackSet.end() ; it++ ) {
//        cout << ' '<<*it << endl; ;
//    }
//    cout << endl;
