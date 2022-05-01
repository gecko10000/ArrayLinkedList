# ArrayLinkedList

This is an implementation of a linked list in which the elements are backed by an array, and each has an offset from the previous and next one. It is faster than the classic Linked List implementation by quite a margin.

## Node Objects in the Array LL

The array linked list is backed by a `Node[]`. Each Node has a value, and offsets to the previous and next elements. There are also values for the first, last, and current Node's array indices, as well as the current index of the pointer.
