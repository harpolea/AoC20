import numpy as np
import sys

def count_trees(input, num_right, num_down):
    loc = np.array([0, 0])

    n_trees = 0

    while loc[1] < len(input):
        if input[loc[1]][loc[0]] == '#':
            n_trees += 1

        loc += np.array([num_right, num_down])
        loc[0] = loc[0] % len(input[0])

    return n_trees

def multiple_slopes(input, slope_list):

    product = 1

    for slope in slope_list:
        product *= count_trees(input, slope[0], slope[1])

    return product

if __name__ == "__main__":
    with open(sys.argv[1]) as f:
        puzzle_input = np.array([l.replace('\n', '') for l in f.readlines()])

        print(f'There are {count_trees(puzzle_input, 3, 1)} trees')

        slope_list = [[1, 1],
                      [3, 1],
                      [5, 1], 
                      [7, 1],
                      [1, 2]]
        
        print(f'Product of multiple slopes is {multiple_slopes(puzzle_input, slope_list)}')