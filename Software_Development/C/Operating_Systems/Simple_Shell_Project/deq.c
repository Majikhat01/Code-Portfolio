#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}


// This function inserts a new Node containg data 'd' into a doubly linked list
// represented by the Rep 'r' at either the Head or Tail, specified by End 'e'.
static void put(Rep r, End e, Data d) {
	// Allocate memory for a new Node
	Node new_node = (Node)malloc(sizeof(struct Node));

	// Check if memory allocation was successful
	if (!new_node) {
		ERROR("Out of memory");
	}

	// Set the data of the new Node to the provided data 'd'
	new_node->data = d;

	// Initialize the next and previous pointers of the new Node to NULL
	new_node->np[Head] = new_node->np[Tail] = NULL;

	// Check if the list is empty
	if (r->len == 0) {
		// If the list is empty, set both Head and Tail pointers to the new Node
		r->ht[Head] = r->ht[Tail] = new_node;
	} else {
		// If the list is not empty, update the pointers accordingly

		// Set the next pointer of the new Node to the current Head or Tail depending on the 'e' value
		new_node->np[!e] = r->ht[e];

		// If the current Head or Tail exists, update its previous pointer
		if (r->ht[e] != NULL) {
			r->ht[e]->np[e] = new_node;
		}

		// Update the Head or Tail pointer to the new Node
		r->ht[e] = new_node;
	}

	// Incrememnt the length of the list
	r->len++;

	// Print statements for debugging
//	printf("Added new node: %p with data: %d\n", new_node, *(int*)(new_node->data));
//	printf("New node's next pointer: %p\n", new_node->np[e]);
//	printf("New node's previous pointer: %p\n", new_node->np[!e]);
//	printf("Deque head: %p, Deque tail: %p\n", r->ht[Head], r->ht[Tail]);
//	printf("Deque length: %d\n\n", r->len);
}

// This function retrieves the data at the i-th position in a doubly linked list
// represented by the Rep 'r' starting from eitherr the Head or Tail, specified by End 'e'.
static Data ith(Rep r, End e, int i)  {
	// Check if the provided index 'e' is out of bounds
	if (i < 0 || i >= r->len) {
		ERROR("Index out of bounds");
	}

	// Initialize a current node pointer starting from the Head or Tail
	Node current = r->ht[e];

	// Initialize an index variable based on the starting End 'e'
	int index = (e == Head) ? 0 : r->len - 1;

	// Traverse the list until the current node becomes Null
	while (current != NULL) {
		// Check if the current index matches the desired index 'i'
		if (index == i) {
			// If the index matches, return the data stored in the current node
			return current->data;
		}

		// Move the current node pointer to the next or previous node based on 'e'
		current = current->np[!e];

		// Update the index accordingly (increment or decrememnt)
		index += (e == Head) ? 1 : -1;
	}

	// If the desired index is not found, return NULL
	return NULL;
}

// This function removes and returns the data from the Head or Tail of a doubly linked list
// represented by the Rep 'r', based on the End 'e'.
static Data get(Rep r, End e)         {
	// Check if the list is empty
	if (r->len == 0) {
		ERROR("The queue is empty");
	}

	// Get the node to remove based on the specified End 'e'
	Node node_to_remove = r->ht[e];

	// Check if the node to remove is NULL
	if (node_to_remove == NULL) {
		ERROR("Attempting to remove a NULL node");
	}

	// Get the data stored in the node to remove
	Data data = node_to_remove->data;

	// Print information about the removed node for debugging
//	printf("Removing node: %p with data: %d\n", node_to_remove, *(int*)(node_to_remove->data));
//	printf("Node's next pointer: %p\n", node_to_remove->np[e]);
//	printf("Node's previous pointer: %p\n", node_to_remove->np[!e]);

	// If the length of the deque is 1, set deque's head and tail to null before removing the node
	if (r->len == 1) {
		r->ht[Head] = r->ht[Tail] = NULL;
	} else {
		// Check if the node to be removed has a prev node.
		// If so, update the next pointer of the previous node to skip over the node being removed
		if (node_to_remove->np[!e]) {
			node_to_remove->np[!e]->np[e] = NULL;
		}

		// Check if the node to be removed has a next node.
		// If so, update the prev pointer of the next node to skip over the node being removed
		if (node_to_remove->np[e]) {
			node_to_remove->np[e]->np[!e] = NULL;
		}

		// Update the head or tail pointer of the deque to point to the next node in the list
		r->ht[e] = node_to_remove->np[!e];
	}

	// Decrease the length of the list
	r->len--;

        // Free memory allocated for the removed node
        free(node_to_remove);

	// Print information about the current state of the list for debugging
//	printf("Deque head: %p, Deque tail: %p\n", r->ht[Head], r->ht[Tail]);
//	printf("Deque length: %d\n\n", r->len);

	// Return the data from the removed node
	return data;
}

// This function removes and returns a node with the specified data 'd' from a doubly linked list
// represented by the Rep 'r', starting from either the Head or Tail, specified by End 'e'.
static Data rem(Rep r, End e, Data d) {
	// Initialize a current node pointer starting from the specified End 'e'
	Node current = r->ht[e];

	// Traverse the list until the current node becomes NULL
	while (current != NULL) {
//		printf("Checking node with data: %d\n", *(int*)current->data); // Debug print statement

		// Check if the data in the current node matches the specified data 'd'
		if (*(int*)current->data == *(int*)d) {
//			printf("Data %d found in the current node\n", *(int*)d); // Debug print statement

			// Update the next and previous pointers of neighboring nodes
			if (current->np[Head] != NULL) {
				current->np[Head]->np[Tail] = current->np[Tail];
			} else {
				r->ht[Head] = current->np[Tail];
			}

			if (current->np[Tail] != NULL) {
				current->np[Tail]->np[Head] = current->np[Head];
			} else {
				r->ht[Tail] = current->np[Head];
			}

			// Get the data from the current node
			Data data = current->data;

			// Free the memory allocated for the current node
			free(current);

			// Decrease the length of the list
			r->len--;

//			printf("Data %d removed successfully\n", *(int*)data); // Debug print statement

			// Return the data that was removed
			return data;
		}

		// Move to the next node based on the specified End 'e'
		current = current->np[!e];
	}

//	printf("Data %d not found in the deque\n", *(int*)d); // Debug print statement

	// If the specified data 'd' is not found, return NULL
	return NULL;
}

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
