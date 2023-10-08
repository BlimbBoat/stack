#include <stdlib.h>
#include <string.h>

#include "mystack.h"
#include "logging.h"
/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */

typedef struct stackObject* pStackObject_t;
typedef struct stackObject
{
	void* obj;
	pStackObject_t next;
} StackObject_t;

typedef struct stackMEta* pStackMeta_t;
typedef struct stackMEta
{
	pStackObject_t stack;
	size_t objsize;
	int numelem;
	int handle;
	pStackMeta_t next;
} StackMeta_t;

static pStackMeta_t gStackList = NULL;

static int returnUnusedHandle()
{
	if(gStackList == NULL)
	{
		return 1;
	}

	int handle = 1;
	pStackMeta_t walker = gStackList;

	while(walker->next != NULL)
	{
		if(walker->handle == handle)
		{
			handle++;
			walker = gStackList;
		}
		walker = walker->next;
	}

	if(walker->next == NULL)
	{
		if(walker->handle == handle)
		{
			handle++;
		}
	}
	return handle;
}

static int searchHandle(pStackMeta_t* walker, int handle)
{
	while((*walker)->next != NULL && (*walker)->handle != handle)
	{
		*walker = (*walker)->next;
	}

	if((*walker)->next == NULL && (*walker)->handle != handle)
	{
		return -1;
	}

	return 0;
}

 int mystack_create(size_t objsize)
 {
 	/* Hint: use gStackList */
 	int handle = returnUnusedHandle();
	pStackMeta_t temp = malloc(sizeof(StackMeta_t));
	if(temp == NULL)
	{
		return -1;
	}

	temp->stack = NULL;
	temp->numelem = 0;
	temp->objsize = objsize;
	temp->next = NULL;
	temp->handle = handle;

	if(gStackList == NULL)
	{
		gStackList = temp;
		DBG_PRINTF("Created stack with handle: %d and objsize %zu bytes\n", gStackList->handle, gStackList->objsize);
	}
	else
	{
		pStackMeta_t walker = gStackList;
		while(walker->next != NULL)
		{
			walker = walker->next;
		}
		walker->next = temp;
		DBG_PRINTF("Created stack with handle: %d and objsize %zu bytes\n", walker->next->handle, walker->objsize);
	}
 	return handle;
 }

 int mystack_push(int handle, void* obj)
 {
	 if(gStackList == NULL || obj == NULL)
	 {
		 return -1;
	 }

	 pStackMeta_t walker = gStackList;
	 if(searchHandle(&walker, handle) == -1)
	 {
		 return -1;
	 }

	 pStackObject_t temp = malloc(sizeof(StackObject_t));
	 if(temp == NULL)
	 {
		 return -1;
	 }

	 temp->obj = malloc(walker->objsize);
	 if(temp->obj == NULL)
	 {
		 free(temp);
		 return -1;
	 }
	 memcpy(temp->obj,obj,walker->objsize);

	 temp->next = NULL;
	 if(walker->stack == NULL)
	 {
		 walker->stack = temp;
	 }
	 else
	 {
		 pStackObject_t objWalker = walker->stack;
		 while(objWalker->next != NULL)
		 {
			 objWalker = objWalker->next;
		 }
		 objWalker->next = temp;
	 }
	walker->numelem += 1;

  DBG_PRINTF("handle: %d, obj: %p\n", walker->handle, obj);
 	return 0;
 }

 int mystack_pop(int handle, void* obj)
 {
	 if(gStackList == NULL || obj == NULL)
	 {
		 return -1;
	 }

	 pStackMeta_t walker = gStackList;
	 if(searchHandle(&walker, handle) == -1)
	 {
		 return -1;
	 }

	 if(walker->stack == NULL)
	 {
		 return -1;
	 }
	 else
	 {
		 pStackObject_t objWalker = walker->stack;
		 pStackObject_t objPrevWalker = objWalker;
		 while(objWalker->next != NULL)
		 {
			 objPrevWalker = objWalker;
			 objWalker = objWalker->next;
		 }
		 memcpy(obj,objWalker->obj,walker->objsize);
		 if(objPrevWalker == objWalker)
		 {
			 walker->stack = NULL;
		 }
		 else
		 {
			 objPrevWalker->next = objWalker->next;
		 }
		 free(objWalker->obj);
		 free(objWalker);
	 }

	walker->numelem -= 1;
  DBG_PRINTF("handle: %d\n, obj: %p\n", handle, obj);
 	return 0;
 }

 int mystack_destroy(int handle)
 {
	 if(gStackList == NULL)
	 {
		 return 0;
	 }

	 pStackMeta_t walker = gStackList;
	 pStackMeta_t prevWalker = walker;

	 while(walker->next != NULL && walker->handle != handle)
 	 {
		 prevWalker = walker;
 		 walker = walker->next;
 	 }

 	 if(walker->next == NULL && walker->handle != handle)
 	 {
 		 return -1;
 	 }

	 if(walker->stack != NULL)
	 {
		 void* p = 0;
		 while(mystack_pop(handle, &p) == 0)
		 {
			 //Do nothing
		 }
	 }

	 if(walker == gStackList)
	 {
		 gStackList = walker->next;
		 free(walker);
	 }
	 else
	 {
		 prevWalker->next = walker->next;
		 free(walker);
	 }

  DBG_PRINTF("handle: %d\n", handle);
 	return 0;
 }

 int mystack_nofelem(int handle)
 {
	 if(gStackList == NULL)
	 {
		 return -1;
	 }

	 pStackMeta_t walker = gStackList;
	 if(searchHandle(&walker, handle) == -1)
	 {
		 return -1;
	 }

  DBG_PRINTF("handle: %d\n", handle);
 	return walker->numelem;
 }
