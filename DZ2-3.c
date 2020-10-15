#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int number_of_nodes = 0;
	int number_of_ribs = 0;
	int check = 0;
	int connectivity = 0;
	int left = 2;
	int right = 2;

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

	FILE* dot = fopen("diagram.txt", "w+");

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
                if(left == 2) left = j;
                else if(right == 2) right = j;
            }
        }
        if (right == 2)
        {
        	fprintf(dot, "%c -- %c;\n", nodes[left], nodes[left]);
        }
        else 
        {
        	fprintf(dot, "%c -- %c;\n", nodes[left], nodes[right]);
        }
        left = 2;
        right = 2;
    }

    fputs("}", dot);
    fclose(dot);

    system("dot -Tpng diagram.txt -o diag.png");

	return 0;
}
