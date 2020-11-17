#include "List.h"


typedef struct GInfo
{
	void* data;
	struct GInfo* next;
} Sginfo, *PtrGinfo;

struct Glist
{
	PtrGinfo root;
	PtrGinfo iterator;
	PtrGinfo last;
	size_t size;
	int (*compare)(void*, void*);
	int (*get_key)(void*, char*);
	int length;
};


int init_generic_list(PtrGlist* list, int (*compare)(void*, void*),
                      int (*get_key)(void*, char*), size_t size)
{
	//Already initiated
	if (*list != NULL)
		return (-1);

	if (compare == NULL || get_key == NULL || size <= 0)
		return (-2);

	(*list) = (PtrGlist)malloc(sizeof(struct Glist));
	(*list)->size = size;
	(*list)->compare = compare;
	(*list)->get_key = get_key;

	(*list)->root = NULL;
	(*list)->length = 0;
	(*list)->iterator = NULL;
	(*list)->last = NULL;

	return 0;
}

int insert_head(PtrGlist list, void * data)
{
	if (list == NULL || data == NULL)
		return (-1);

	PtrGinfo res = (PtrGinfo)malloc(sizeof(Sginfo));

	res->data = (void *)malloc(list->size);
	memcpy(res->data, data, list->size);
	if(list->root == NULL)
		list->last = res;
	res->next = list->root;
	list->root = res;
	list->iterator = res;
	list->length++;


	return 0;
}


int insert_tail(PtrGlist list, void * data)
{
	PtrGinfo res, iterator;
	//not initiated
	if (list == NULL || data == NULL)
		return (-1);

	res = (PtrGinfo)malloc(sizeof(Sginfo));
	res->data = malloc(list->size);
	memcpy(res->data, data, list->size);

	//Empty list case
	if (list->root == NULL)
	{
		res->next = NULL;
		//list->length++;
		list->root = res;
		list->iterator = res;
		list->last = res;
	}
	else {
		//non empty
		//for (iterator = list->root; iterator->next != NULL; iterator = iterator->next)
			;
		//iterator->next = res;

		//list->root->next == NULL

		list->last->next = res;
		res->next = NULL;
		list->last = res;
	}

	list->length++;
	return 0;
}

int get_element(PtrGlist list, void * info, char* key)
{

	if (list == NULL || info == NULL
	        || key == NULL)
		return (-1);

	if (list->length == 0)
		return (-2);

	PtrGinfo iterator = list->root;

	for (; iterator != NULL ; iterator = iterator->next)
		if (list->get_key(iterator->data, key) == 0) {
			memcpy(info, iterator->data, list->size);
			return 0;
		}

	return 1;
}

void clear_all(PtrGlist list)
{

	if (list == NULL)
		return;

	PtrGinfo iterator = list->root, root;

	while (iterator != NULL)
	{
		free(iterator->data);
		iterator->data = NULL;
		root = iterator;
		iterator = iterator->next;
		free(root);
		root = NULL;
		list->length--;
	}

	list->root = NULL;
	list->iterator = NULL;
}

int remove_element(PtrGlist list, void* elem)
{
	PtrGinfo iterator = list->root, last = NULL;

	if (list == NULL || elem == NULL)
		return (-1);

	if (iterator == NULL)
		return (-2);

	//Element in head.
	if (list->compare(iterator->data, elem) == 0)
	{
		if(iterator->next == NULL)
			list->last = NULL;
		list->root = iterator->next;
		list->iterator = iterator->next;

		free(iterator->data);
		iterator->data = NULL;
		free(iterator);
		iterator = NULL;
		list->length--;

		return 0;
	}

	for (; iterator != NULL; iterator = iterator->next)
	{
		if (list->compare(iterator->data, elem) == 0)
		{
			if(iterator->next == NULL)
				list->last = last;
			last->next = iterator->next;
			free(iterator->data);
			iterator->data = NULL;
			free(iterator);
			iterator = NULL;
			list->length--;
			return 0;
		}

		last = iterator;
	}

	return 1;
}

int get_iterator(PtrGlist list, void * res)
{
	if (list == NULL)
		return (-1);

	if (list->iterator == NULL)
	{
		list->iterator = list->root;
		return 1;
	}
	else
	{
		memcpy(res, list->iterator->data, list->size);
		list->iterator = list->iterator->next;
		return 0;
	}
}

int insert_order(PtrGlist list, void* info)
{

	if (list == NULL || info == NULL)
		return (-1);

	PtrGinfo iterator = list->root, last = NULL, listNew;

	//empty case
	if (iterator == NULL)
	{
		list->root = (PtrGinfo)malloc(sizeof(Sginfo));
		list->root->data = (void*)malloc(list->size);
		memcpy(list->root->data, info, list->size);
		list->root->next = NULL;
		list->iterator = list->root;
		list->length++;
		list->last = list->root;
		return 0;
	}

	for (; iterator != NULL
	        && ( list->compare(iterator->data, info) < 0); last = iterator, iterator = iterator->next)
		;

	listNew = (PtrGinfo)malloc(sizeof(Sginfo));
	listNew->data = (void*)malloc(list->size);
	memcpy(listNew->data, info, list->size);

	//Insert in first cycle
	if (last == NULL)
	{
		list->root = listNew;
		list->iterator = listNew;
	}
	//middle or final
	else{
		if(last->next == NULL)
			list->last = listNew;
		last->next = listNew;

	}

	listNew->next = iterator;

	list->length++;
	return 0;
}

int get_size(PtrGlist list)
{
	return list->length;
}

