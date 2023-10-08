#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "mystack.h"

//#define ONE_SECOND (1000*1000)
#define ONE_SECOND (1*1000)

//Interchangable
static const int queueSize = 10;
static const int stacksToMake = 5;
static const int handle = 2;
static const int dataTypeSize = sizeof(char);

static void queue_reversal(int handle, void* obj)
{
  for (size_t i = 0; i < queueSize; i++)
  {
    mystack_pop(handle,obj+(dataTypeSize*i));
  }
}

int main (int argc, char * argv[])
{
  if(handle > stacksToMake)
  {
    printf("The handler in this case should be larger than the stacks to make\n");
    return 0;
  }

  char queue[queueSize]; /*You can easily change the type but also change the
                           dataTypeSize*/

  for (size_t i = 0; i < queueSize; i++)
  {
    queue[i] = i;
  }
  printf("Array before reversal\n");
  for (size_t i = 0; i < queueSize; i++)
  {
    printf("%d\n", queue[i]);
  }
  printf("\n");
  for (size_t i = 0; i < stacksToMake; i++)
  {
    mystack_create(sizeof(int));
  }

  for (size_t i = 0; i < queueSize; i++)
  {
    mystack_push(handle,&queue[i]);
  }

  //printf("Number of elements in handle %d: %d\n", handle,mystack_nofelem(handle));

  queue_reversal(handle,queue);
  printf("Array after reversal\n");
  for (size_t i = 0; i < queueSize; i++)
  {
    printf("%d\n", queue[i]);
  }

  for (size_t i = 1; i < stacksToMake+1; i++)
  {
    mystack_destroy(i);
  }

  return 0;
}
