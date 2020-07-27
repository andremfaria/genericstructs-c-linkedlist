#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Glist *PtrGlist;

/**
 * @brief      Initializes the generic list.
 *
 * @param     list  List to initiate
 * @param  compare  Function to compare generic data
 * @param  get_key  Function to retrieve by key generic Data
 * @param  size Sizeof generic data
 *
 * @return Return code
 * 				- 0 OK
 * 				- (-1) List already initiated
 * 				- (-2) Parameters could not be NULL
 */
int init_generic_list(PtrGlist*,int (*)(void*,void*), int (*)(void*, char*),size_t);
/**
 * @brief      Insert head function
 *
 * @param  list  List to insert info
 * @param      data  Generic data to insert
 *
 * @return Return code
 * 				- 0 OK
 * 				- (-1) List or generic data is null.
 */
int insert_head(PtrGlist,void*);
/**
 * @brief      Insert in the end of the list
 *
 * @param  PtrGlist  List to insert info
 * @param      data  Generic data to insert
 *
 * @return Return code
 * 				- 0 OK
 * 				- (-1) List or generic data is null.
 */
int insert_tail(PtrGlist,void*);
/**
 * @brief      Insert in order by compare function
 *
 * @param  PtrGlist  List to insert info
 * @param      data  Generic data to insert
 *
 * @return Return code
 * 				- 0 OK
 * 				- (-1) List or generic data is null.
 */
int insert_order(PtrGlist,void*);
/**
 * @brief      Search an element in the list by key.
 *
 * @param  PtrGlist  List to search
 * @param      void* Data to return
 * @param char* Key 
 *
 * @return Return code
 * 				- 0 OK
 * 				- (-1) Parameters could not be NULL.
 * 				- (-2) List is empty. 
 * 				- 1 Not found
 */
int get_element(PtrGlist,void*, char*);
/**
 * @brief      Removes an element.
 *
 * @param  PtrGlist List to remove the element
 * @param      void*  Element to remove
 *
 * @return Return code
 * 				- 0 OK
 * 				- (-1) Parameters could not be NULL.
 * 				- (-2) List is empty. 
 * 				- 1 Not found
 */
int remove_element(PtrGlist,void*);
/**
 * @brief      Clear list
 *
 * @param  PtrGlist  List to be clear
 */
void clear_all(PtrGlist);
/**
 * @brief      Gets the iterator for the next element.
 *
 * @param  PtrGlist  List to iterate.
 * @param      void* Data to return
 *
 * @return Return code
 * 				- 0 OK.
 * 				- (-1) Parameter is null
 * 				- 1 Reach end of the list.
 */
int get_iterator(PtrGlist, void*);
/**
 * @brief      Gets the list size
 *
 * @param  PtrGlist  Size
 *
 * @return     The size.
 */
int get_size(PtrGlist);