* **SalesmanProblem : OptimizationProblem**

    contains details about concrete problem being solved. 
in this case, it's a [travelling salesman problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem)
OptimizationProblem class is an abstraction, 
which can be used to solve other problems with this code by overriding it's methods

* **SalesmanProblemSolutionProgress**

  controls current iteration and allows stopping iterating at any point, 
also can iterate to maximum set iteration

* **Destination**

  used to contain coordinates of some place and can calculate distance to other Destination

* **Population**

  contains a collection of Creature objects and can make them mate, 
mutate and die to continue evolution process

* **Creature**

  contains collection of chromosomes, which can be mutated using their internal functions

* **ScoredCreature**

  this structure groups creature, and it's score obtained using OptimizationProblem target function
it is used inside Population class.

* **EnumChromosome**

  contains set of unique genes (integers) which can be permuted inside it.
For this task order of integers represents an order in which cities are being visited by salesman

* **main.cpp, mainwindow.cpp, mainwindow.h**

  files contain code for GUI of an app


Algorithm logic is implemented in function EvolveGeneration of Population class.
Chromosomes contain order of visited cities

**[Crossingover operation](https://en.wikipedia.org/wiki/Crossover_(genetic_algorithm))** reverses tail of chromosome after some position

**[Mutation operation](https://en.wikipedia.org/wiki/Mutation_(genetic_algorithm))** swaps two genes to allow new possibilities founding new solutions

In this implementation best half of the population is allowed to mate (use crossingover)
and creates for each specimen two new creatures. 
After mating, some percentage of creatures mutate and iteration can be repeated.