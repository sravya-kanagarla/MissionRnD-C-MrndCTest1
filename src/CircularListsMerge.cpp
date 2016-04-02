/*
Given two SORTED Circular Linked Lists ,
Write a function to merge those two linked lists .
The First Linked List head should point to the final merged linked list .
The Final merged linked list should also be in SORTED order and a Circular Linked List.
You need to return the Length of Final SLL.

*********
The First linked list head should now point to the Final sorted(Ascending) Linked list First Node
*********
Ex : A: 0->3->5->10->20 (and 20 now pointing back to 0,instead of Null )
B: 1->2->6->11->21->50->70 (70 Pointing back to 1).

The Final Linked List is A:0->1->2->3->5->6->10->11->20->21->50->70 .

Note : Dont use Malloc or create any new nodes ,Only pointers need to be interchanged,
You can use temp pointers although.
Note : The Final Linked List should be  also be a circular Linked List where Last node is
pointing towards the first node.
Note : Return -1 for Invalid Inputs like NULL;

Input : head1 and head2 are Addresses of Two Circular Linked Lists heads .
Output :Return Length of New SLL .Modify the head1 value, such that it now points to 
Merged Sorted Circular SLL .

Difficulty : Medium
*/
#include <stdlib.h>
#include <stdio.h>

struct node{
	int data;
	struct node *next;
};

int findLen(struct node *head) {
	struct node *temp = head;
	int len = 0;
	if (head == NULL)
		return len;
	while (temp->next != head) {
		temp = temp->next;
		len++;
	}
	len++;
	return len;
}

void makeNull(struct  node *head) {
	struct node *temp = head;
	while (temp->next != head) {
		temp = temp->next;
	}
	temp->next = NULL;
}

int merge_circularlists(struct node **head1, struct node **head2){
	//Returns Length of merged Sorted circular SLL and also points *head1 to final SLL .
	if (*head1 == NULL && *head2 == NULL)
		return -1;
	if (*head1 == NULL) {
		head1 = head2;
		return findLen(*head2);
	}
	if (*head2 == NULL) {
		return findLen(*head1);
	}
	makeNull(*head1);
	makeNull(*head2);
	struct node *iter1 = *head1;
	struct node *iter2 = *head2;
	struct node *head = NULL;
	struct node *last = NULL;
	struct node *temp = NULL;
	while (iter1 != NULL && iter2 != NULL) {
		if (iter1->data < iter2->data) {
			temp = iter1;
			iter1 = iter1->next;
		}
		else {
			temp = iter2;
			iter2 = iter2->next;
		}
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			last = temp;
		}
		else {
			last->next = temp;
			last = last->next;
		}
	}
	if (iter1 == NULL && iter2 != NULL) {
		last->next = iter2;
	}
	else {
		last->next = iter1;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = head;
	head1 = &head;
	return findLen(*head1);
}