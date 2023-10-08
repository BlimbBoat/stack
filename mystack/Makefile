ASSIGNMENT=mystack
MYSTACK_TEST=mystack_test
MYSTACK_SHARED=mystack_shared

UNITY_FOLDER=./Unity
INC_DIRS=-Iproduct
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)


SHARED_FILES=product/mystack.c

MAIN = product/main.c

MYSTACK_FILES=$(SHARED_FILES) \
	      $(MAIN)

MYSTACK_TEST_FILES=$(SHARED_FILES) \
	           $(UNITY_FOLDER)/unity.c \
	           test/mystack_test.c

HEADER_FILES=product/*.h

CC=gcc

#SYMBOLS=-g  -O0 -std=c99 -Wall -Werror -pedantic
SYMBOLS=-g  -O0 -std=c99
TEST_SYMBOLS=$(SYMBOLS) -DTEST

.PHONY: clean test mystack

all: $(ASSIGNMENT)

$(ASSIGNMENT): Makefile $(MYSTACK_FILES)  $(HEADER_FILES)
	$(CC) $(INC_DIRS) $(SYMBOLS) $(MYSTACK_FILES) -o $(ASSIGNMENT)

$(MYSTACK_TEST): Makefile $(MYSTACK_TEST_FILES)  $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(MYSTACK_TEST_FILES) -o $(MYSTACK_TEST)

$(MYSTACK_SHARED): $(MAIN)
	$(CC) $(MAIN) -o mystack_shared -L. -lmystack

clean:
	@rm -f $(ASSIGNMENT) $(MYSTACK_TEST) $(MYSTACK_SHARED)

test: $(MYSTACK_TEST)
	  @./$(MYSTACK_TEST)
