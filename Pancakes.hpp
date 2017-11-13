#ifndef PANCAKES_H
#define PANCAKES_H

#include <vector>

typedef std::vector<int> stack_type;
typedef std::vector<stack_type::size_type> flip_type;

/* ------------------------------------------------------------------------- *
 * Function that sorts a vector of ints using the prefix reversal method, 
 * commonly knows as pancake sorting
 * This function uses the naive approach to find the max, flip it on top
 * then flip the whole stack over. This guarantees a fast method but it is
 * not optimal.

 * PARAMETERS
 * - The vector of ints that needs to be sorted
 * - One vector of ints that will contain the index where the stack was flipped
 * ------------------------------------------------------------------------- */
void simple_pancake_sort(const stack_type& pancakes, flip_type& flips);


/* ------------------------------------------------------------------------- *
 * Function that sorts a vector of ints using the prefix reversal method, 
 * commonly knows as pancake sorting
 * 
 * This function uses the A*  algorithm to find the most optimal solution.

 * PARAMETERS
 * - The vector of ints that needs to be sorted
 * - One vector of ints that will contain the indexes where the stack was flipped
 * ------------------------------------------------------------------------- */
void astar_pancake_sort(const stack_type& pancakes, flip_type& flips);

#endif // PANCAKES_H
