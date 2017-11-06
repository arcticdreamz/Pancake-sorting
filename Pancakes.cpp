
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include "pancakes.hpp"
#include <sstream>
#include <utility> // for pair
#include <unordered_set>


using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::set;
using std::string;


typedef pair<int,int> cost;
typedef pair<stack_type,flip_type> pancake_stack_raw;
typedef pair<pair<stack_type,flip_type>,pair<int,int> > pancake_stack;

//Compare function for the set
bool comp(const pancake_stack stackA, const pancake_stack stackB){

    int totalCostA = stackA.second.first + stackA.second.second;
    int totalCostB = stackB.second.first + stackB.second.second;
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
    return *(getMax(stackA.first.first));
}



string stackToString(pancake_stack& stackA) {
	std::stringstream result;
	std::copy(stackA.first.first.begin(), stackA.first.first.end(), std::ostream_iterator<int>(result, ""));
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
    cost zeroCost = std::make_pair(0,0); // Real cost , EstCost
    pancake_stack_raw initial_raw_stack = make_pair(pancakes_copy,flips);
    pancake_stack initial_stack = make_pair(initial_raw_stack,zeroCost);

    //Create a sorted stack to compare
    stack_type sorted_stack = pancakes_copy;
    sort(sorted_stack.begin(),sorted_stack.end());


    pancake_stack parent_stack = initial_stack;

    p_queue.insert(initial_stack); //First call


    std::unordered_set<string> stringStackVector;

    std::unordered_set<string>::iterator foundString;

    while(!std::equal(parent_stack.first.first.begin(),parent_stack.first.first.end(),sorted_stack.begin())) {

        if(!p_queue.empty()){ //don't want to dereference end pointer
        	parent_stack = *(p_queue.begin()); //Extract from the priority queue
            p_queue.erase(p_queue.begin()); //Delete the extracted element from the priority queue
        }
        //Looking in the stringStackVector if the stack hasn't already been encountered
        foundString = std::find(stringStackVector.begin(), stringStackVector.end(),stackToString(parent_stack));

//    	If the stack has indeed already been encountered before, we just loop again
      	if(foundString != stringStackVector.end()){
//            cout << *foundString << " has already been generated" << endl;
            continue;
        }
//
//     	cout << "Pushing parent into the stringStackVector" << endl;
        stringStackVector.insert(stackToString(parent_stack));

        // generate children from parent stack
        for(stack_type::size_type i = 1; i < parent_stack.first.first.size(); i++) { // generate children from parent stack

            pancake_stack child_stack = parent_stack;

            child_stack.first.second.push_back(i); //Pushing the flip
            std::reverse(child_stack.first.first.begin(),child_stack.first.first.begin()+ 1 + i); // flip at index i (i+1 because reverse() second argument is non-inclusive)



            //Looking in the stringStackVector if the stack hasn't already been encountered
            foundString = std::find(stringStackVector.begin(), stringStackVector.end(),stackToString(child_stack));

            //If the stack has indeed already been encountered before, we just loop again
            if(foundString != stringStackVector.end()){
                continue;
            }

            //Computing the cost
            int realCost = i+1; // i+1 pancakes were flipped
            int estCost = getEstCost(child_stack); //Compute the estimated end cost
            child_stack.second.first += realCost; // Add the child's realCost to the parent's realCost
            child_stack.second.second = estCost;

            //Insert child into the set
            p_queue.insert(child_stack);
        }
    }

    cout << "The size of the priority queue is : " << p_queue.size() << endl;
    cout << "The best cost was: " << parent_stack.second.first + parent_stack.second.second <<endl;
    cout << " The flips vector contains : ";
    for(flip_type::iterator it = parent_stack.first.second.begin(); it != parent_stack.first.second.end() ; it++ ) {
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


//    cout << "The stringStackVector contains : " <<  endl;
//   sort(stringStackVector.begin(),stringStackVector.end());
//    for(std::vector<string>::iterator it = stringStackVector.begin(); it != stringStackVector.end() ; it++ ) {
//        cout << ' '<<*it << endl; ;
//    }
//    cout << endl;
