#include <iostream>
#include <string>
#include "bfs.h"

using namespace std;

void shortest(int *column_indices, int *row_offsets, int *visited, int *queue, int src)
{
#pragma HLS INTERFACE m_axi depth=27444 port=column_indices offset=slave bundle=input
#pragma HLS INTERFACE m_axi depth=4721 port=visited offset=slave bundle=output
#pragma HLS INTERFACE m_axi depth=4721 port=queue offset=slave bundle=output
#pragma HLS INTERFACE m_axi depth=4722 port=row_offsets offset=slave bundle=input

#pragma HLS INTERFACE s_axilite port=column_indices
#pragma HLS INTERFACE s_axilite port=row_offsets
#pragma HLS INTERFACE s_axilite port=visited
#pragma HLS INTERFACE s_axilite port=queue
#pragma HLS INTERFACE s_axilite port=src bundle=sqrt
#pragma HLS INTERFACE ap_ctrl_hs port=return

    int front = 0;
    int current_node = src;
    int edge_start, edge_end;

    queue[front] = src;

    bfs_loop: for (int step = 0; step < V; ++step)
    {
#pragma HLS PIPELINE
        current_node = queue[step];
        visited[current_node] = 1;

        edge_start = row_offsets[current_node];
        edge_end = row_offsets[current_node + 1];

        traverse_neighbors: for (int edge_idx = edge_start; edge_idx < edge_end; ++edge_idx)
        {
            int neighbor = column_indices[edge_idx];

            if (!visited[neighbor])
            {
                ++front;
                queue[front] = neighbor;
                visited[neighbor] = 1;
            }
        }
    }
}
