#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"bfs.h"
using namespace std;
int graph[V+1][V+1]={0};
int *queue;
int *visited;
int *row, *column_indices;
int *row_offsets;
int main()
{
	int i;
	int src = 1;
	queue = new int [V];
	visited = new int [V+1];
	row = new int [E];
	column_indices = new int [E];
	row_offsets = new int [V+2];
	for(i=1;i<V+1;i++)
	{
		visited[i] = 0;
		}
  FILE *fp = fopen("edge_list.txt","r");
  char line[100];
  	  if((fp = fopen("edge_list.txt","r")) == NULL)
  	  {
         fprintf(stderr,"[Error] Cannot open the file");
         exit(1);
  	  }
  	int node1, node2;
  	while(!feof(fp))
  	{
  		fscanf(fp,"%d%d", &node1, &node2);
  		graph[node1][node2]=1;
  		graph[node2][node1]=1;
  	}
  	fclose(fp);
  	int m = 0, j;
  	    row_offsets[0] = 0;
  	    for(int i=1;i<V+1;i++)
  	    {
  	        row_offsets[i] = m;
  	        for(int j=1;j<V+1;j++)
  	        {
  	            if(graph[i][j]!=0)
  	            {
  	                row[m]=i;
  	                column_indices[m]=j;
  	                m++;
  	            }
  	        }
  	    }
  	    row_offsets[V+1]=E;
  	 for(i=0;i<E;i++)
  	 {
  		 cout<<row[i]<<" ";
  	 }
  	 cout<<endl;
  	for(i=0;i<E;i++)
  	  	 {
  	  		 cout<<column_indices[i]<<" ";
  	  	 }
  	cout<<endl;
  	cout<<endl;
  	for(i=0;i<V+2;i++)
  	  	  	 {
  	  	  		 cout<<row_offsets[i]<<" ";
  	  	  	 }
  	cout<<endl;
  	for(i=0;i<V+1;i++)
  	  	  	  	 {
  	  	  	  		 cout<<row_offsets[i+1]-row_offsets[i]<<" ";
  	  	  	  	 }

   shortest(column_indices, row_offsets, visited, queue, src);
  cout<<"\n BFS traversal is"<<endl;
	for(i=1;i<V+1;i++)
	{
	  cout<<queue[i]<<endl;
	}
	delete [] queue, visited, row, column_indices, row_offsets;
	return 0;

}
