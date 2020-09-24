# ex4 - Project

NadavSRB & Tseela

## Our Server
This project is a server that can solve matrix-graph problems using several algorithms.
We support DFS, BFS, A* and BestFS.

### Errors the server might return
```cpp
NOT_ENOUGH_ARG                                      // the user didn't send enough arguments
NOT_SUPPORTED_PROBLEM                               // the problem the user entered has no reference in the server
TIMEOUT_HAS_PASSED                                  // the user didn't send anything to the server for more then 5 seconds
NO_START_BREAKS                                     // there supposed to be 2 empty lines (but the user forgot that...)
NOT_SUPPORTED_ALG                                   // the givven algorithm is not supported by the server
MISSING_ROW_WITH_TWO_VALUES                         // a value is missing from a line
NO_INT_ROW_WITH_TWO_VALUES                          // a value that supposed to be `int` is missing
INVALID_MATRIX_VALUE                                // the given matrix has an invalid cell value
NUM_VALUES_NOT_EQUALS_MATRIX_WIDTH                  // there are too many or too little numbers in one line of the matrix
LAST_ROW_NOT_EMPTY                                  // the last row isn't empty
VALUE_MUST_BE_POSITIVE                              // there is a value in the matrix which is smaller then 1
```

Our server supports a serial & parallel version, it kicks users the don't send anything to the server for more then 5 seconds and it will shut down 2 hours after no user connects it.

### Algorithms & Cache
We have 4 algorithms that can solve the matrix-graph problem. You can add any problem / solution you would like by inheriting from classes "Problem.cpp" & "Solution.cpp".
Also, we have a option in "Solver.cpp" to use out cache manager. It will use it automatically but you can disable the use.


# Michael
We love u and it was a great pleasure to learn from u in this difficult course.
Here are some of Taylor's songs:

[We Are Never Ever Getting Back Together](https://www.youtube.com/watch?list=PLSyf1w-9zNb3mWbUagnNkpkuwd80pujQu&v=WA4iX5D9Z64)

[Look What You Made Me Do](https://www.youtube.com/watch?v=3tmd-ClpJxA)

[I Knew You Were Trouble](https://www.youtube.com/watch?v=vNoKguSdy4Y)

And for dessert: [Holy](https://www.youtube.com/watch?v=pvPsJFRGleA)