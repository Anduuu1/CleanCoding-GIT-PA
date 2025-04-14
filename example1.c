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

// Adaugă element în stivă
void push(Stack *stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->items[++stack->top] = value;
    }
}

// Resetează vectorul de vizite
void resetVisited(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// DFS recursiv
void depthFirstSearch(Graph *graph, Stack *stack, int startVertex) {
    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);
    push(stack, startVertex);

    Node *adj = graph->adjLists[startVertex];
    while (adj != NULL) {
        int connectedVertex = adj->value;
        if (!graph->visited[connectedVertex]) {
            depthFirstSearch(graph, stack, connectedVertex);
        }
        adj = adj->next;
    }
}

// Citește muchiile
void readEdges(Graph *graph, int edgeCount) {
    printf("Introduceți %d muchii (perechi de noduri între 0 și %d):\n", edgeCount, graph->numVertices - 1);
    for (int i = 0; i < edgeCount; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

// Eliberează memoria grafului
void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node *temp = graph->adjLists[i];
        while (temp != NULL) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}

// Eliberează memoria stivei
void freeStack(Stack *stack) {
    free(stack->items);
    free(stack);
}

// Funcție principală
int main() {
    int numVertices, numEdges;

    printf("Numărul de noduri: ");
    if (scanf("%d", &numVertices) != 1 || numVertices <= 0) {
        fprintf(stderr, "Eroare: Introduceți un număr valid de noduri.\n");
        return EXIT_FAILURE;
    }

    printf("Numărul de muchii: ");
    if (scanf("%d", &numEdges) != 1 || numEdges < 0) {
        fprintf(stderr, "Eroare: Introduceți un număr valid de muchii.\n");
        return EXIT_FAILURE;
    }

    Graph *graph = createGraph(numVertices);
    Stack *dfsStack = createStack(2 * numVertices);

    readEdges(graph, numEdges);

    printf("Parcurgere DFS de la nodul 0:\n");
    depthFirstSearch(graph, dfsStack, 0);
    printf("\n");

    freeGraph(graph);
    freeStack(dfsStack);

    return 0;
}
