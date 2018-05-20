# Algorithms

The game includes a simple implementation of the BFS (breadth first search) and DFS (depth first search).

## BFS (Breadth First Search)

The breadth first search is used for finding the number of steps of the shortest path to move to the goal. It's implemented on a queue used to store the next possible move. As we know, for every step there are 4 (or 3, 2) possible directions for the next step. We can start from the beginning, and keep adding the coordinates of the next possible blocks into the queue. we'll keep track of the number of steps (levels) as well. Once we reach the goal, we can terminate this process and store the number of steps. This will be the number of steps for the shortest path. It's like finding the gradient of a graph.

## DFS (Depth First Search)

After we get the least steps to reach the goal, we can implement the depth first search algorithm to find the shortest path. It's easier to implement in recursions. 