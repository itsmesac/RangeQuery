******************************************************************
Implementation of Range Query for numbers
******************************************************************

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Description:

The objective of the RangeQuery class is to allow efficient 
addition / deletion of ranges into a database and efficient
query operations. A tree based approach where the nodes of
the tree hold the corresponding ranges is used. The tree 
respects the property of a binary search tree and therefore,
the operations on the database can be done efficiently, in
an average case. The algorithms perform poorly(O(n)) only
in cases when ranges are added/deleted in such a manner that
the tree becomes heavily skewed.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Interfaces provided by RangeQuery class:

1 - void addRange(int min, int max)

	Insert a range specified by [min,max] into the database.
	
2 - void delRange(int min, int max)

	Delete the range specified by [min,max] from the database.
	
3 - bool queryPoint(int val)

	returns true if the value specified by val is inserted into 
	the database.
	
	returns false if the value specified by val is not inserted or 
	deleted from the database.
	
4 - void clear()

	deletes all the contents of the database.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Complexity Analysis:

{addRange,delRange,queryPoint}
Time : Average case - O(log (n + m))
       Worst case - O(n + m)
	   
Space : O(n + m)

{clear}
Time : O(n + m)

Space : O(n + m)

n : number of addRange operations.
m : number of delRange operations.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
