// This is a testing program for a 
// page allocation tracer for user space programs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096
#define NUM_PAGES 10

/*
This functions touches all the memory pages in the given buffer.
*/
void access_memory(char *ptr, size_t size) {
    for (size_t i = 0; i < size; i += PAGE_SIZE) {
        ptr[i] = 'A';   // Touching grass
        usleep(100000); // Contemplating life
    }
}


int main() {
    printf("PID: %d\n", getpid());
    printf("Touching grass...\n");
    
    sleep(10);

    // Check the heap region allocations using malloc for 10 pages. 
    printf("Testing malloc...\n");
    char *buf1 = malloc(PAGE_SIZE * NUM_PAGES);
    access_memory(buf1, PAGE_SIZE * NUM_PAGES);
    
    // Check the mmap region allocations using mmap for 10 pages.
    printf("Testing mmap...\n");
    char *buf2 = mmap(NULL, PAGE_SIZE * NUM_PAGES,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS,
                     -1, 0);
    if (buf2 == MAP_FAILED) {
        perror("mmap failed");
        free(buf1);
        return 1;
    }
    access_memory(buf2, PAGE_SIZE * NUM_PAGES);

    // We are disciplined cavemen so we free the memory we allocated. 
    free(buf1);
    munmap(buf2, PAGE_SIZE * NUM_PAGES);
    
    printf("Touching grass completed. Going back into cave\n");
    return 0;
}