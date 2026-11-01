#include <stdio.h>
#include <Windows.h>

#define PROGRESS_BAR_MAX 10000
#define PROGRESS_BAR_WIDTH 100

int main(void)
{
	int i;
	int j;
	float percent;
	
	for (i = 0; i <= PROGRESS_BAR_MAX; i++)
	{
		printf("\r[", i, PROGRESS_BAR_MAX);
		
		percent = (float)i / PROGRESS_BAR_MAX * 100.0f;
		
		for (j = 0; j < PROGRESS_BAR_WIDTH; j++)
		{
			if (j < (int)(percent / (100.0f / PROGRESS_BAR_WIDTH)))
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		
		printf("] %d/%d (%0.2f%%)", i, PROGRESS_BAR_MAX, percent);
		Sleep(100);
	}
	
	printf("\nDone");
	
	return 0;
}
