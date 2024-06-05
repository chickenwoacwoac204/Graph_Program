#include <stdio.h>
#include <stdlib.h>

// Cấu trúc biểu diễn một cạnh
typedef struct Edge {
    int vertex;
    int weight;
    struct Edge* next;
} Edge;

// Cấu trúc biểu diễn một đỉnh
typedef struct Vertex {
    int data;
    Edge* edges;
} Vertex;

// Cấu trúc biểu diễn đồ thị
typedef struct Graph {
    int numVertices;
    Vertex* vertices;
} Graph;

// Hàm tạo một cạnh mới
Edge* createEdge(int v, int w) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->vertex = v;
    newEdge->weight = w;
    newEdge->next = NULL;
    return newEdge;
}

// Hàm thêm một cạnh vào danh sách kề của một đỉnh
void addEdge(Vertex* vertex, int v, int w) {
    Edge* newEdge = createEdge(v, w);
    newEdge->next = vertex->edges;
    vertex->edges = newEdge;
}

// Hàm tạo đồ thị
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));

    for (int i = 0; i < numVertices; i++) {
        graph->vertices[i].data = i;
        graph->vertices[i].edges = NULL;
    }

    return graph;
}

// Hàm nhập đồ thị từ bàn phím
void inputGraph(Graph* graph) {
    int numEdges;
    printf("Nhap so canh cua do thi: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        printf("Nhap canh thu %d (dinh_dau dinh_cuoi trong_so): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph->vertices[src], dest, weight);
    }
}

// Hàm in đồ thị
void printGraph(Graph* graph) {
    printf("Do thi:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Dinh %d: ", i);
        Edge* edge = graph->vertices[i].edges;
        while (edge != NULL) {
            printf("(%d, %d) ", edge->vertex, edge->weight);
            edge = edge->next;
        }
        printf("\n");
    }
}

int main() {
    int numVertices;
    printf("Nhap so dinh cua do thi: ");
    scanf("%d", &numVertices);

    Graph* graph = createGraph(numVertices);
    inputGraph(graph);
    printGraph(graph);

    return 0;
}