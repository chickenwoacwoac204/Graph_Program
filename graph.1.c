#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// Hàm tìm đỉnh có khoảng cách nhỏ nhất từ tập đỉnh chưa xét
int findMinDistance(int* distances, int* visited, int numVertices) {
    int minDistance = INT_MAX;
    int minVertex = -1;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minVertex = i;
        }
    }

    return minVertex;
}

// Hàm tìm đường đi ngắn nhất từ đỉnh nguồn đến các đỉnh khác
void dijkstra(Graph* graph, int src) {
    int numVertices = graph->numVertices;
    int* distances = (int*)malloc(numVertices * sizeof(int));
    int* visited = (int*)malloc(numVertices * sizeof(int));

    // Khởi tạo khoảng cách ban đầu là vô cùng và chưa xét đỉnh nào
    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    // Khoảng cách từ đỉnh nguồn đến chính nó là 0
    distances[src] = 0;

    // Tìm đường đi ngắn nhất cho tất cả các đỉnh
    for (int i = 0; i < numVertices - 1; i++) {
        // Tìm đỉnh có khoảng cách nhỏ nhất từ tập đỉnh chưa xét
        int u = findMinDistance(distances, visited, numVertices);
        visited[u] = 1;

        // Cập nhật khoảng cách của các đỉnh kề với đỉnh vừa xét
        Edge* edge = graph->vertices[u].edges;
        while (edge != NULL) {
            int v = edge->vertex;
            int weight = edge->weight;
            if (!visited[v] && distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
            edge = edge->next;
        }
    }

    // In khoảng cách ngắn nhất từ đỉnh nguồn đến các đỉnh khác
    printf("Khoang cach ngan nhat tu dinh %d den cac dinh khac:\n", src);
    for (int i = 0; i < numVertices; i++) {
        printf("Dinh %d: %d\n", i, distances[i]);
    }

    free(distances);
    free(visited);
}

int main() {
    int numVertices;
    printf("Nhap so dinh cua do thi: ");
    scanf("%d", &numVertices);

    Graph* graph = createGraph(numVertices);
    inputGraph(graph);
    printGraph(graph);
    
    int src;
    printf("Nhap dinh nguon: ");
    scanf("%d", &src);

    dijkstra(graph, src);

    return 0;
}