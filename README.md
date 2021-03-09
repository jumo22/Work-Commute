# Work-Commute

X is working in three different offices of the same company, having to commute every day between them. It doesn't matter the order in which he visits the offices as long as at the end of the day the job is done.
Given the layout of his city as a grid and the positions of his home and each of the three offices, display the most efficient path X can take to pass through each of them. If there is no path that X can take to achieve this, display nothing. Keep in mind that X can only travel in 4 directions (up, down, left, right) and the grid does not wrap around (going up from the first row is not possible).

Solution:

Reading the input data takes O(N*M) anyways, so working
with an adjacency matrix was a valid option.
Upon reading the letters, we save the coordinates of the
home (=source) and store the coordinates of the offices 
in an array. Starting from every possible building - and
by that I mean from the home and the three offices - we 
perform a BFS search for each of them, storing for each the 
distances from them to the other offices/home in matrices.
Having now 4 distance matrices and having only 6 options for
the shortest path, we check for each option whether it is
the minimum sum or not, thus finding out the order in which the offices 
are visited.
In order to print the path, we make use of the order of the offices
and search in each distance matrix the shortest path: we start from
the last visited office and look for the path to the 2nd-to-last visited
office in the distance matrix of the 2nd-to-last visited office, then we
look for the path from the 2nd-to-last visited office to the 1st visited
office in the distance matrix from the 1st office and the path from the
1st office to home in the home distance matrix, using again BFS and storing
the nodes in a stack.
I believe that there is some duplicate code that could be arranged better
and I will work on it as well.

Time Complexity - O ( N * M )
Space Complexity - O ( N * M )

