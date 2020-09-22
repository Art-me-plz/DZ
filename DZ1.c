#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int value;
	struct Node* next; 
} Node;

void push (Node** head, int val) {
	Node* new = (Node*)calloc(sizeof(Node), 1);
	if (new == NULL) return;
	new->value = val;
	new->next = (*head);
	(*head) = new;
}

void delete (Node** head, int val) {
	if ((*head) == NULL) return;
	if ((*head)->value == val)
	{
		Node* temp = NULL;
		temp = (*head)->next;
		free(*head);
		(*head) = temp;
	}
	else delete(&((*head)->next), val);
}

void list (Node* p) {
	printf("list:\n");
	while (p != NULL) {
		printf("%d\n", p->value);
		p = p->next;
	}
}

int main(int argc, char const *argv[])
{
	Node* head = NULL;
	Node* end = NULL;
	int menu = 0;
	int val = 0;

	while (menu == 0) {
		printf("Select the action\n 1) add\n 2) delete\n 9) exit\n");
		scanf("%d", &menu);
		switch(menu) {
			case 1:
				printf("enter new value:\n");
				scanf("%d", &val);
				push(&head, val);
				val = 0;
				menu = 0;
				list(head);
				break;
			case 2:
				printf("enter deleting value:\n");
				scanf("%d", &val);
				delete(&head, val);
				val = 0;
				menu = 0;
				list(head);
				break;
		}
	}
	while (head != NULL) {
		end = head->next;
		free(head);
		head = end;
	}
	
	return 0;
}
