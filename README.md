  This program demonstrates three classic page replacement algorithms used in computer memory management: Least Recently Used (LRU), Optimal, and First-In-First-Out (FIFO). Each algorithm is implemented as a separate function. The main function handles the simulation by taking a sequence of page references and the number of available memory frames as input. It then sequentially applies each algorithm to the page reference sequence, tracking page faults and displaying the state of memory (page table and frames) at each step. Finally, it presents the total number of page faults incurred by each algorithm. The code employs simple data structures like vectors, maps, and queues to represent memory and efficiently simulate the algorithms. For my code, I hardcoded the input string as 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 (per assingment) and then also made the number frames equal to 4.
