#include <stdio.h>
#include <stdlib.h>

// Nod din lista de adiacență
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Structura pentru graf
typedef struct Graph {
    int numVertices;
    int *visited;
    Node **adjLists;
} Graph;

// Structura pentru stivă
typedef struct Stack {
    int top;
    int capacity;
    int *items;
} Stack;

// Crează un nod nou
Node *createNode(int value) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Eroare la alocarea memoriei pentru nod.\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Crează un graf cu n vârfuri
Graph *createGraph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "Eroare la alocarea grafului.\n");
        exit(EXIT_FAILURE);
    }

    graph->numVertices = vertices;
    graph->visited = calloc(vertices, sizeof(int));
    graph->adjLists = malloc(vertices * sizeof(Node *));

    if (!graph->visited || !graph->adjLists) {
        fprintf(stderr, "Eroare la alocarea componentelor grafului.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Adaugă muchie neorientată în graf
void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Crează o stivă
Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "Eroare la alocarea stivei.\n");
        exit(EXIT_FAILURE);
    }

    stack->top = -1;
    stack->capacity = capacity;
    stack->items = malloc(capacity * sizeof(int));
    if (!stack->items) {
                    fprintf(stderr, "Eroare la alocarea memoriei pentru elementele stivei.\n");
                    exit(EXIT_FAILURE);
                }
            return stack;
        }
