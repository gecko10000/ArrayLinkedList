# ArrayLinkedList

This is an implementation of a doubly linked list in which the elements are backed by an array, and each has an offset from the previous and next one. It is faster than the classic Linked List implementation by quite a margin.

## Node Objects in the Array LL

The array linked list is backed by a `Node[]`. Each Node has a value, and offsets to the previous and next elements. There are also values for the first, last, and current Node's array indices, as well as the current index of the pointer.

## Speedup

The speedup compared to a classic doubly linked list is by about 30%. Having run the test file with a few different sizes, the trend is apparent:
```
$ ./LLTests 100000000
---Normal Linked List---
Appended in 4 seconds.
Deleted in 2 seconds.
---Array Linked List---
Appended in 3 seconds.
Deleted in 1 seconds.
$ ./LLTests 200000000
---Normal Linked List---
Appended in 7 seconds.
Deleted in 4 seconds.
---Array Linked List---
Appended in 5 seconds.
Deleted in 4 seconds.
$ ./LLTests 600000000
---Normal Linked List---
Appended in 20 seconds.
Deleted in 13 seconds.
---Array Linked List---
Appended in 15 seconds.
Deleted in 11 seconds.
```
Deletion is a bit more similar because each value is being compared to ensure it is the correct one.

## Limitations

The array LL currently has a fixed size in the constructor. It also cannot contain null pointers, as those are used to represent a non-existent Node. I am hoping to change that in the future.

## Usage

To compile, run `$ make [all]`. Then, use `$ ./LLTests [size]` to run. The size will default to 100,000,000.
