#include <stdio.h>
#include <stdlib.h>

typedef struct list_item {
	struct list_item *next;
} LIST_ITEM;

#define INIT_LIST(LIST_NAME) \
 	LIST_ITEM  *LIST_NAME##_HEAD = NULL;

#define LIST_ENTRY(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define LIST_HEAD(LIST_NAME) LIST_NAME##_HEAD

struct foo {
	int val;
	LIST_ITEM list;
};

void add_list_item(LIST_ITEM *item, LIST_ITEM **head)
{
	LIST_ITEM *p;


	if (*head == NULL) {
		*head = item;
	} else {
		p = *head;
		while (p->next != NULL)
			p = p->next;
		p->next = item;
	}
}

void visit_list_item(LIST_ITEM *head) {
	LIST_ITEM *p = head;
	struct foo *foo;
	int i = 0;

	while (p) {
		foo = LIST_ENTRY(p, struct foo, list);
		printf("num %d val %d\n", ++i, foo->val);
		p = p->next;
	}
}


void reverse_list_item(LIST_ITEM **head) {
	LIST_ITEM *p, *next;
	
	p = *head;
	while (p->next != NULL) {
		next = p->next;
		p->next = next->next;
		next->next = *head;
		*head = next;
	}
}


INIT_LIST(FOO);

int main()
{
	int i, *val;	
	struct foo *pfoo;

	for (i = 0; i < 10; i++) {
		pfoo = (struct foo *) malloc(sizeof(struct foo));
		pfoo->val = i + 100;
		add_list_item(&pfoo->list, &LIST_HEAD(FOO));
	}
	
	visit_list_item(LIST_HEAD(FOO));
	reverse_list_item(&LIST_HEAD(FOO));
	visit_list_item(LIST_HEAD(FOO));

}
