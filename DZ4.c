#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *num, char *nodes, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = (size - 1); j > i; j--)
    {
      if (num[j - 1] > num[j]) 
      {
        char temp = nodes[j - 1];
        nodes[j - 1] = nodes[j];
        nodes[j] = temp;
        int temp1 = num[j - 1];
        num[j - 1] = num[j];
        num[j] = temp1;
      }
    }
  }
}

int main(int argc, char const *argv[])
{
	int number_of_nodes = 0;
	int number_of_ribs = 0;
	int check = 0;
	int connectivity = 0;
	int left = -1;
	int right = -1;
	int rib = 0;
	int del = 0;

	printf("enter the number of nodes:\n");
	scanf("%d", &number_of_nodes);
	printf("enter the number of ribs:\n");
	scanf("%d", &number_of_ribs);

	int graph[number_of_nodes][number_of_ribs];

	printf("enter values of incidence matrix (0 or 1):\n");
	for (int i = 0; i < number_of_nodes; i++)
	{
		for (int j = 0; j < number_of_ribs; j++)
		{
			scanf("%d", &graph[i][j]);
		}
	}

	//check input
	for (int i = 0; i < number_of_ribs; i++)
	{
		for (int j = 0; j < number_of_nodes; j++)
		{
			if (graph[j][i] == 1) 
			{
				check++;
			}
		}
		if (check >= 3)
		{
            printf("Wrong input!!!\n");
            exit(228);
        }
        check = 0;
	}

	//check connectivity
    connectivity = ((number_of_nodes - 1) * (number_of_nodes - 2)) / 2;
    if (number_of_ribs > connectivity) 
    {
    	printf("graph is connected\n");
    }
    else 
    {
    	printf("graph is not connected\n");
    }

	char nodes[number_of_nodes];
	printf("names of nodes:\n");
	for (int i = 0; i < number_of_nodes; ++i)
	{
		scanf("%s", &nodes[i]);
	}

	FILE* dot = fopen("diagram.txt", "w");

    if(dot == NULL) exit(000);

	fputs("graph G {\n", dot);
	for (int i = 0; i < number_of_nodes; ++i)
	{
		fprintf(dot, "%c;\n", nodes[i]);
	}
    for (int i = 0; i < number_of_ribs; i++)
    {
        for (int j = 0; j < number_of_nodes; j++)
        {
            if (graph[j][i] == 1){
                if(rib == 0) {
                	left = j;
                	rib++;
                } 
                else if(rib == 1) {
                	right = j;
                	rib++;
                } 
            }
        }
        if (rib == 1)
        {
        	fprintf(dot, "%c -- %c [label=%d];\n", nodes[left], nodes[left], i + 1);
        }
        else 
        {
        	fprintf(dot, "%c -- %c [label=%d];\n", nodes[left], nodes[right], i + 1);
        }
        left = -1;
        right = -1;
        rib = 0;
    }

    fputs("}", dot);
    fclose(dot);

    system("dot -Tpng diagram.txt -o diag.png");

    printf("what rib do u want to delete:\n");
	scanf("%d", &del);

	dot = fopen("diagram.txt", "w");

    if(dot == NULL) exit(000);

	fputs("graph G {\n", dot);
	for (int i = 0; i < number_of_nodes; ++i)
	{
		fprintf(dot, "%c;\n", nodes[i]);
	}
    for (int i = 0; i < number_of_ribs; i++)
    {
    	if ((i + 1) != del)
    	{
    		for (int j = 0; j < number_of_nodes; j++)
    		{
    			if (graph[j][i] == 1){
    				if(rib == 0) {
    					left = j;
    					rib++;
    				} 
    				else if(rib == 1) {
    					right = j;
    					rib++;
    				} 
    			}
    		}
    		if (rib == 1)
    		{
    			fprintf(dot, "%c -- %c [label=%d];\n", nodes[left], nodes[left], i + 1);
    		}
    		else 
    		{
    			fprintf(dot, "%c -- %c [label=%d];\n", nodes[left], nodes[right], i + 1);
    		}
    		left = -1;
    		right = -1;
    		rib = 0;
    	}
    }

    fputs("}", dot);
    fclose(dot);

    system("dot -Tpng diagram.txt -o diag.png");

    int arr[number_of_nodes];
    for (int i = 0; i < number_of_nodes; ++i)
	{
		arr[i] = 0;
	}

    for (int i = 0; i < number_of_ribs; i++)
    {
    	if ((i + 1) != del)
    	{
    		for (int j = 0; j < number_of_nodes; j++)
    		{
    			if (graph[j][i] == 1){
    				arr[j] = arr[j] + 1;
    			}
    		}
    	}
    }
    bubbleSort(arr, nodes, number_of_nodes);
    printf("sorted nodes in ascending order of vertex degree:\n");
    for (int i = 0; i < number_of_nodes; ++i)
    {
    	printf("%c\n", nodes[i]);
    }

	return 0;
}
