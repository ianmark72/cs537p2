#
# Sample makefile updated to include the commands to run the Clang Static Analyzer
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out

all: munch2.o queue.o munch1.o reader.o writer.o main.o
	$(CC) -o $(EXE) munch2.o queue.o munch1.o reader.o writer.o main.o -lpthread

main.o: main.c munch2.h queue.h munch1.h reader.h writer.h
	$(CC) $(WARNING_FLAGS) -c main.c -lpthread
munch2.o: munch2.c munch2.h
	$(CC) $(WARNING_FLAGS) -c munch2.c -lpthread
queue.o: queue.c queue.h
	$(CC) $(WARNING_FLAGS) -c queue.c -lpthread
munch1.o: munch1.c munch1.h
	$(CC) $(WARNING_FLAGS) -c munch1.c -lpthread
reader.o: reader.c reader.h
	$(CC) $(WARNING_FLAGS) -c reader.c -lpthread
writer.o: writer.c writer.h 
	$(CC) $(WARNING_FLAGS) -c writer.c -lpthread
clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 

