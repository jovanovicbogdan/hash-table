# Hash Table Data Structure Implementation in C

1. Compute hash code (integer) based on key using [FNV-1](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function) hash function.
2. Map key-value pair to an index in array. This can be done like this `hash(key) % array_length`.
3. Since there can be infinite number of keys and finite number of ints there is a possibility for collision. Collision will be handled by adding a new bucket to the beginning of a linked list in `O(1)` time.

Hash table key lookup will be done on average in `O(1)` but in worst case can be `O(n)` where `n` is the number of elements stored in linked list.
