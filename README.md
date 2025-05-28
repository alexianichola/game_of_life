# Game of life
  Game of Life is a project that creatively explores data structures. Inspired by Conway’s classic Game of Life, this enhanced version integrates core data structures such as: lists, stacks, trees, and graphs to provide developers with a fun and engaging way to practice and understand how these structures work together.

## Objectives 

- Task 1: Implements the main rules of the game applying them on arrays and simulate K generations.
- Task 2: Improve efficiency by using stacks of lists to track only cell state changes between generations.
- Task 3: Use the difference lists from Task 2 to build a binary tree and simulate the game with both standard and custom rules.
- Task 4: Introducing a graph to create the longest Hamiltonian path for every node of the tree.
- Bonus:  Reverse Task 2: recover the initial grid using the stack of differences.
 If you would like to find more about it and see examples you can find it explained briefly [here](https://site-pa.netlify.app/proiecte/game_of_life/).


## Task 1

### Functions:
-  nr_vecini_celula
- reguli

  The nr_vecini_celule function checks all the surrounding cells and counts how many neighbors the current cell has.
  The reguli function applies the rules to the array based on the result from nr_vecini_celule.

  Everything works perfectly, there is only one version of this task.



## Task 2

### Functions:
- addAtBeginning
- push
- printStack
- deletelist
- deleteStack
- schimbari

 The core functions like addAtBeginning, push, printStack, deleteList, and deleteStack do exactly what their names suggest.
 The schimbari function compares the old and new array and adds the changes to a list, which will be pushed into the stack.

 There are two versions of this task, one that works with arrays and one that works only with lists. And the principle is the same but there are a few changes. You can find the firts version with arays at commit "Added task 2" and the version with lists at "Task 2 using lists".


## Task 3
### Functions:

- reguli_B
- insert
- arbore_creat
- preordine
- deleteTree
- copie_matrice 
  

 The functions insert,deleteTree and copie_matrice do exactly what their names suggest.
 The reguli_B function applies the new rule to the tree.
Arbore_creat ensures that the rules are applied in a specific order, and preordine populates the tree.

  There are three versions of Task 3:
- The first version works with arrays and uses the functions listed above — this version works correctly for the entire tree.
- The second version uses lists — it does not work properly, stopping after the sixth node.
- The third version tries to use lists based on the array version from Task 2 — this version also stops after the sixth tree node and does not function fully.

## Task 4
### Functions:

- createNode
- addEdge
- createGraph
- DFS_scan
- backtrackLongestPath
- printLongestPathToFile

  This version of Task 4 creates a graph by transforming the nodes into indices and checking if they are neighbors. It uses adjacency lists and includes a function called DFS_scan, which identifies the first node of each component and stores all components of the graph while populating it. There is also a function named backtrackLongestPath that attempts to find the longest Hamiltonian path in the graph, along with another function named printLongestPathToFile that prints the resulting path in a file.
  Unfortunately, this task does not work correctly.
  
## Bonus
  For the bonus part, I had to create additional files to verify that my output was correct, since the checker does not support testing this functionality directly. I also implemented a dedicated function that performs the reverse operation, which can be easily integrated into the main project if needed.

## Checker Explanation

  The project includes a checker — an automated script that verifies the correctness and quality of your program. It performs several checks:
- Memory Check: Verifies that there are no memory leaks or illegal memory accesses (typically using tools like valgrind).
- Style Check: Ensures the code follows the required coding style (indentation, naming, formatting, etc.).
- Output Check: Compares the program’s output to the expected output to confirm correctness.
  The checker runs your implementation against a set of predefined tests and reports whether each part passes or fails.

## Credits

  This project was developed as part of the Algorithm Design course at the University Politehnica of Bucharest, during the academic semester. Enjoy!
