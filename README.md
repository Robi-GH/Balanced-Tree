Generic Balanced Binary Search Tree
This project implements a generic data structure that stores elements as a binary search tree while maintaining balance to optimize performance.

Features

Generic Design: 
Supports storing elements of any comparable type.

Balanced Structure: 
Automatically balances the tree when the balance condition is violated.

Efficient Rebalancing:
If, at a height of at least 3, the number of elements in one subtree is twice as large as the other, the affected subtree is restructured.

Rebalancing is done by creating a sorted array of the subtree's elements and reconstructing an ideally balanced subtree.

Optimized Operations: 
Insertions and deletions maintain an average time complexity of 𝑂(log(𝑛)). Rebalancing operations may temporarily exceed this complexity.

How It Works

Insertions and Deletions: 
Standard binary search tree operations.

Balancing Condition:
Monitors the size of subtrees to ensure balance. When violated, triggers the rebalancing process.

Rebalancing:
Collects subtree elements into a sorted array. Constructs a new balanced subtree from the array.

Usage:
This data structure can be used in applications requiring dynamic and efficient data organization with balanced operations, such as:
-Priority queues
-Interval trees
-Dynamic sets

Complexity
Insertions and Deletions: 𝑂(log(𝑛)) on average.
Rebalancing: May exceed O(log(n)) but ensures overall balance for future operations.
