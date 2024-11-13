CC = g++
CFLAGS =
COPTFLAGS = -O3 -g
LDFLAGS =

default:
	@echo "=================================================="
	@echo "To build your sorting code, use:"
	@echo "  make insertion-sort           # For Insertion sort"
	@echo "  make insertion-sort-bisearch  # For Insertion sort with binary search"
	@echo "  make mergesort    	           # For Mergesort"
	@echo ""
	@echo "To clean this subdirectory (remove object files"
	@echo "and other junk), use:"
	@echo "  make clean"
	@echo "=================================================="

# Queue driver 
queue: queue.o queue_test.o
	$(CC) $(COPTFLAGS) -o $@ $^

# Doubly linked list driver
dlist: dlist.o dlist_test.o
	$(CC) $(COPTFLAGS) -o $@ $^


%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ queue dlist queue_test dlist_test

# eof
