#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <sys/mman.h> 
 
int main() 
{ 
 const int Size = 4096; 
 const char* data = "Operating system"; 
 int shm_file_dr; 
 void* ptr; 
 shm_file_dr = shm_open(data, O_RDONLY, 0666); 
 ptr = mmap(0, Size, PROT_READ, MAP_SHARED, shm_file_dr, 0); 
 printf("%s", (char*)ptr); 
 shm_unlink(data); 
 return 0; 
}
