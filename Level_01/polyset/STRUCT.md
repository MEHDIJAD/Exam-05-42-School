## The Class Hierarchy

```txt
[ BAG ]
         (The Abstract Concept)
      Defines: insert(), print()...
                 /   \
                /     \
    (Storage Path)   (Capability Path)
          |                 |
   [ ARRAY_BAG ]     [ SEARCHABLE_BAG ]
  (The Implementation)  (The Requirement)
   "I store data in      "I require a
    an array."            has() function."
          \                 /
           \               /
            \             /
      [ SEARCHABLE_ARRAY_BAG ]
         (The Final Product)
     "I store data in an array AND
      I implement the has() function."
```

## Have VS Giving Classes

| Status | Filename | Description |
| :--- | :--- | :--- |
| **GIVEN** | `bag.hpp` | Abstract base class (Grandparent). |
| **GIVEN** | `searchable_bag.hpp` | Abstract interface for searching (Parent 2). |
| **GIVEN** | `array_bag.hpp` | Implementation using arrays (Parent 1). |
| **GIVEN** | `tree_bag.hpp` | Implementation using binary trees (Parent 1). |
| **GIVEN** | `main.cpp` | Test file that must compile with your code. |
| **GIVEN** | `shame.en.txt` | Explanatory text for sets/bags. |
| **TO IMPLEMENT** | `searchable_array_bag.hpp` | Header for the array-based searchable bag. |
| **TO IMPLEMENT** | `searchable_array_bag.cpp` | Implementation for the array-based searchable bag. |
| **TO IMPLEMENT** | `searchable_tree_bag.hpp` | Header for the tree-based searchable bag. |
| **TO IMPLEMENT** | `searchable_tree_bag.cpp` | Implementation for the tree-based searchable bag. |
| **TO IMPLEMENT** | `set.hpp` | Header for the set wrapper. |
| **TO IMPLEMENT** | `set.cpp` | Implementation for the set wrapper. |


## Array-Based Searchable Bag


## Tree-Based Searchable Bag

```txt
[ BAG ]
		 (The Abstract Concept)
	  Defines: insert(), print()...
				 /   \
				/     \
	(Storage Path)   (Capability Path)
		  |                 |
   [ TREE_BAG ]      [ SEARCHABLE_BAG ]
  (The Implementation)  (The Requirement)
   "I store data in      "I require a
	a binary tree."      has() function."
		  \                 /
		   \               /
			\             /
	  [ SEARCHABLE_TREE_BAG ]
		 (The Final Product)
	 "I store data in a binary tree AND
	  I implement the has() function."
```

```
	   [ 5 ]  <-- This is "tree" (The Root)
      /     \
   [ 3 ]   [ 8 ]
   /   \
[ 1 ] [ 4 ]
```