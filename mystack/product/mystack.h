#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include <stddef.h>

/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 *
 * The usera are only allowed to use the stack API
 * that is defined below.
 */

/* note: library comtains is non-reentrant code */


/* Creates a stack of c objects of size objsize and returns
 * a handle (number > 0 ) to the just created stack. On error,
 * -1 is returned.
 */
extern int mystack_create(size_t objsize);
/* Pushes an object to the stack identified by its handle
 * returns 0 on success and -1 on an error
 */
extern int mystack_push(int handle, void* obj);

extern int mystack_pop(int handle, void* obj);
extern int mystack_destroy(int handle);
extern int mystack_nofelem(int handle);

#endif /* __MSTACK_H__ */
