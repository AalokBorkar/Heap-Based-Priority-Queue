Heap based priority Q

Heap based priority Q with full functionality (O(1) insertions and front-removal) written in C.

Function breakdown:

  * `pq_create()` - allocates and initializes a heap-based priority queue
  * `pq_free()` - frees all memory allocated to a priority queue
  * `pq_isempty()` - tells the user whether a priority queue is empty
  * `pq_insert()` - inserts an element with a specified priority value into a priority queue
  * `pq_first()` - returns the value of the first element in a priority queue
  * `pq_first_priority()` - returns the *priority value* associated with the first element in a priority queue
  * `pq_remove_first()` - removes the first element from a priority queue and return its value