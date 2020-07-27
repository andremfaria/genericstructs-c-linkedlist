#include "List.h"


typedef struct GInfo
{
	void* data;
	struct GInfo* next;
} Sginfo, *PtrGinfo;

struct Glist
{
	PtrGinfo atual;
	PtrGinfo iterator;
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

	(*list)->atual = NULL;
	(*list)->length = 0;
	(*list)->iterator = NULL;

	return 0;
}

int insert_head(PtrGlist list, void * data)
{
	if (list == NULL || data == NULL)
		return (-1);

	PtrGinfo res = (PtrGinfo)malloc(sizeof(Sginfo));

	res->data = (void *)malloc(list->size);
	memcpy(res->data, data, list->size);
	res->next = list->atual;
	list->atual = res;
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
	if (list->atual == NULL)
	{
		res->next = NULL;
		list->length++;
		list->atual = res;
		list->iterator = res;
	}
	else {
		//non empty
		for (iterator = list->atual; iterator->next != NULL; iterator = iterator->next)
			;
		iterator->next = res;
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

	PtrGinfo iterator = list->atual;

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

	PtrGinfo iterator = list->atual, atual;

	while (iterator != NULL)
	{
		free(iterator->data);
		iterator->data = NULL;
		atual = iterator;
		iterator = iterator->next;
		free(atual);
		atual = NULL;
		list->length--;
	}

	list->atual = NULL;
	list->iterator = NULL;
}

int remove_element(PtrGlist list, void* elem)
{
	PtrGinfo iterator = list->atual, last = NULL;

	if (list == NULL || elem == NULL)
		return (-1);

	if (iterator == NULL)
		return (-2);

	//Element in head.
	if (list->compare(iterator->data, elem) == 0)
	{
		list->atual = iterator->next;
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
		list->iterator = list->atual;
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

	PtrGinfo iterator = list->atual, last = NULL, listNew;

	//empty case
	if (iterator == NULL)
	{
		list->atual = (PtrGinfo)malloc(sizeof(Sginfo));
		list->atual->data = (void*)malloc(list->size);
		memcpy(list->atual->data, info, list->size);
		list->atual->next = NULL;
		list->iterator = list->atual;
		list->length++;
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
		list->atual = listNew;
		list->iterator = listNew;
	}
	//middle or final
	else
		last->next = listNew;

	listNew->next = iterator;

	list->length++;
	return 0;
}

int get_size(PtrGlist list)
{
	return list->length;
}

