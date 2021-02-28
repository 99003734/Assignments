#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
int main() 
{ 
	time_t data, val = 1; 
	struct tm* current_Time; 
	data = time(NULL); 
	current_Time = localtime(&data); 

	
	printf("%02d:%02d:%02d", 
		current_Time->tm_hour, 
		current_Time->tm_min, 
		current_Time->tm_sec); 

	return 0; 
} 
