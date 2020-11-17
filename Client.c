#include "List.h"

typedef struct SClient
{
	char* name;
	int age;
} StClient, *PtrClient;


int compare(void * client, void * client2)
{
	PtrClient clientCast = (PtrClient) client, client2Cast = (PtrClient)client2;
	return strncmp(clientCast->name, client2Cast->name, strlen(clientCast->name));
}

int get_key(void * client, char * key)
{
	PtrClient clientCast = (PtrClient) client;
	return strncmp(clientCast->name, key, strlen(key));
}

void print_elem(PtrClient data)
{
	printf("\n***Client info***\n");
	printf("Client name: %s\n", data->name);
	printf("Client age: %d\n", data->age);
}

void print_generic_struct(PtrGlist list)
{
	PtrClient aux, iterator = (PtrClient)malloc(sizeof(StClient));

	while (get_iterator(list, iterator) == 0)
	{
		print_elem(iterator);
		free(iterator);
		iterator = NULL;
		iterator = (PtrClient)malloc(sizeof(StClient));
	}

	free(iterator);
	iterator = NULL;
}


PtrClient create_client(char* name, int age)
{
	PtrClient ptrClient = (PtrClient)malloc(sizeof(StClient));

	ptrClient->name = (char*)malloc(48);
	strncpy(ptrClient->name, name, strlen(name));
	ptrClient->age = age;

	return ptrClient;
}

int main(int argc, char const *argv[])
{
	PtrGlist list = NULL;
	init_generic_list(&list, compare, get_key, sizeof(StClient));
	// Insert head: Test
	puts("\n\n#### [TEST] Insert head ####\n\n");

	(void) insert_head(list, create_client("Andy", 18));
	(void) insert_head(list, create_client("Querty", 28));
	(void) insert_head(list, create_client("Dasdas", 28));

	//Get iterator test
	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));


	//Get element
	puts("\n\n#### [TEST] Get element test ####\n\n");
	PtrClient retrievedClient = (PtrClient)malloc(sizeof(StClient));
	int flag = get_element(list, retrievedClient, "Dasdas");

	if (flag == 0)
		print_elem(retrievedClient);

	//Insert tail
	puts("\n\n#### [TEST] Insert tail ####\n\n");
	(void) insert_tail(list, create_client("Long", 35));
	(void) insert_tail(list, create_client("Malloc", 41));

	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));



	// Remove element
	puts("\n\n#### [TEST] Remove element ####\n\n");
	flag = remove_element(list, create_client("Long", 35));
	printf("Result remove1:%d\n", flag);
	flag = remove_element(list, create_client("Malloc", 35));
	printf("Result remove2:%d\n", flag);
	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));


	//Clear all
	puts("\n\n#### [TEST] Clear all and get_size ####\n\n");
	clear_all(list);
	puts("Priting list...\n");
	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));

	//Insert order
	puts("\n\n#### [TEST] Test O(1) insertTail ####\n\n");
	puts("\n## [1] Final List Expected : [3, Anthony, Andre,Test, JohnDoe,4] | size:6 ##\n");

	(void) insert_order(list, create_client("Anthony", 41));
	(void) insert_order(list, create_client("Andre", 31));
	(void) insert_order(list, create_client("Test", 21));
	(void) insert_order(list, create_client("JohnDoe", 11));
	(void) insert_head(list, create_client("3", 41));
	(void) insert_tail(list, create_client("4", 41));


	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));

	puts("\n## [2] Final List Expected : [1,2,4] | size:3 ##\n");
	clear_all(list);
	(void) insert_head(list, create_client("3", 41));
	(void) insert_head(list, create_client("2", 31));
	(void) insert_head(list, create_client("1", 21));
	flag = remove_element(list, create_client("3", 35));
	printf("Result remove:%d\n", flag);
	(void) insert_tail(list, create_client("4", 41));
	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));

	puts("\n## [3] Final List Expected : [3,4] | size:2 ##\n");
	clear_all(list);
	(void) insert_head(list, create_client("3", 41));
	(void) insert_tail(list, create_client("4", 41));
	(void) insert_head(list, create_client("2", 31));
	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));
	flag = remove_element(list, create_client("2", 35));
	printf("Result remove:%d\n", flag);
	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));


	puts("\n## [4] Final List Expected : [5] , size:1 ##\n");
	(void) remove_element(list, create_client("4", 35));
	(void) remove_element(list, create_client("3", 35));
	(void) insert_tail(list, create_client("5", 41));
	print_generic_struct(list);
	printf("List size:%d\n", get_size(list));



	return 0;
}