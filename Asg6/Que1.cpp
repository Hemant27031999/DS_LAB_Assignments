#include <iostream>
#include <stdlib.h>
#include <list>
#include <bits/stdc++.h>

using namespace std;

struct graphNode {
    int vertex;
    struct graphNode* next;
};

struct graphNode* createNode(int vertex) {
    struct graphNode* newNode = (graphNode*) malloc(sizeof(struct graphNode));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph {
    int noOfVertices;
    struct graphNode** edges;
    int* visited;
};

struct Graph* createGraph(int noOfVertices) {
    struct Graph* node = (Graph*) malloc(sizeof(struct Graph));
    node->noOfVertices = noOfVertices;

    node->edges = (graphNode**) malloc(noOfVertices * sizeof(struct graphNode*));
    node->visited = (int*) malloc(noOfVertices * sizeof(int));

    for(int i=0;i<noOfVertices;i++){
        node->edges[i] = NULL;
        node->visited[i] = 0;
    }

    return node;
}

void addEdge(struct Graph* graph, int start, int end){

    struct graphNode* newNode1 = createNode(start);
    newNode1->next = graph->edges[end];
    graph->edges[end] = newNode1;

    struct graphNode* newNode2 = createNode(end);
    newNode2->next = graph->edges[start];
    graph->edges[start] = newNode2;

}


struct linkedListNode {
    int data;
    linkedListNode* next;
};

class LinkedList {
    private:
        linkedListNode *head, *tail;

    public:
        LinkedList() {
            head = NULL;
            tail = NULL;
        }

        void insert(int data) {
            linkedListNode* newNode = new linkedListNode;
            newNode->data = data;
            newNode->next = NULL;

            if(head == NULL) {
                head = tail = newNode;
            }else{
                tail->next = newNode;
                tail = tail->next;
            }
        }

        void display(linkedListNode *head) {
            if(head){
                cout<<head->data<<" ";
                display(head->next);
            }
        }

        int getNode(int index, linkedListNode *first){
            linkedListNode *newNode = first;
            int pp = 0;
            while(pp != index) {
                first = first->next;
                pp++;
            }
            linkedListNode *newNode1 = first;
            first = newNode;
            return newNode1->data;

        }

        linkedListNode* getHead() {
            return head;
        }
};


struct tempQueue {
    int data[40];
    int front;
    int rear;
};


struct tempQueue* createQueue() {
    struct tempQueue* newQueue = (tempQueue*) malloc(sizeof(struct tempQueue));
    newQueue->front = -1;
    newQueue->rear = -1;
    return newQueue;
}


bool isEmpty(struct tempQueue* q) {
    if(q->rear == -1)
        return true;
    return false;
}


void enqueue(struct tempQueue* q, int data){
    if(q->front == -1){
        q->front = 0;
    }
    q->rear++;
    q->data[q->rear] = data;
}

int dequeue(struct tempQueue *q) {

    int item;
    if(isEmpty(q)){
        cout<<"Empty Queue!!!"<<endl;
        item = -1;
    }else{
        item = q->data[q->front];
        q->front++;
        if(q->front > q->rear){
            q->front = q->rear = -1;
        }
    }
    return item;
}


void printQueue(struct tempQueue *q) {
    int i = q->front;
    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->data[i]);
        }
    }
}


bool check(struct Graph* graph, int v, bool visited[], int parent){

    visited[v] = true;

    struct graphNode* temp = graph->edges[v];

    while(temp) {
        int adjacent = temp->vertex;

        if(!visited[adjacent]){
            if(check(graph, adjacent, visited, v)){
                return true;
            }  
        }else if(adjacent != parent){
            return true;
        }
        temp = temp->next;
    }

    return false;

}

bool isCyclic(struct Graph* graph) {

    bool *visited = new bool[7];
    for (int i = 0; i < 7; i++) 
        visited[i] = false;
    
    for(int i=0;i<7;i++){
        if(!visited[i]){
            if(check(graph, i, visited, -1)){
                return true;
            }
        }
    }
    return false;
}


pair<int, int> bfs(struct Graph* graph,int u) 
{ 
	int dis[7]; 
	memset(dis, -1, sizeof(dis)); 

	queue<int> q; 
	q.push(u); 

	dis[u] = 0; 

    while(!q.empty()){
        int pp = q.front();
        q.pop();

        struct graphNode* temp = graph->edges[pp];

        while(temp) {

            int adjacent = temp->vertex;

            if(dis[adjacent] == -1){
                q.push(adjacent);
                dis[adjacent] = dis[pp] + 1;
            }
            temp = temp->next;
        }
    }

	int maxDis = 0; 
	int nodeIdx; 
 
	for (int i = 0; i < 7; i++) 
	{ 
		if (dis[i] > maxDis) 
		{ 
			maxDis = dis[i]; 
			nodeIdx = i; 
		} 
	} 
	return make_pair(nodeIdx, maxDis); 
} 


void getDiameter(struct Graph* graph){
    pair<int, int> t1, t2;
    t1 = bfs(graph, 0);
    t2 = bfs(graph, t1.first);
    cout<<"Diameter is "<<t2.second<<endl;
}


void BFS(struct Graph* graph, int start) {

    int dis[7];
    for(int i=0;i<7;i++){
        dis[i] = -1;
    }

    struct tempQueue *q = createQueue();
    struct Graph* temp1 = graph;

    temp1->visited[start] = 1;
    enqueue(q, start);

    dis[start] = 0;
    
    while(!isEmpty(q)){
        int current = dequeue(q);
        cout<<current<<" ";

        struct graphNode* temp = temp1->edges[current];

        while(temp) {

            int adjacent = temp->vertex;

            if(temp1->visited[adjacent] == 0){
                temp1->visited[adjacent] = 1;
                enqueue(q, adjacent);
                dis[adjacent] = dis[q->front] + 1;
            }


            temp = temp->next;
        }
    }

    cout<<endl;

    int max = 0, index;

    for(int i=0;i<7;i++){
        if(dis[i] > max){
            max = dis[i];
            index = i;
        }
    }
}


void DFS(struct Graph* graph, int start) {
        struct graphNode* adjList = graph->edges[start];
        struct graphNode* temp = adjList;
        
        graph->visited[start] = 1;
        cout<<start<<" ";
    
        while(temp!=NULL) {
            int next = temp->vertex;
        
            if(graph->visited[next] == 0) {
                DFS(graph, next);
            }
            temp = temp->next;
        }       
}

int main() {

    struct Graph* graph = createGraph(7);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);

    char start, end;

    cout<<"1. Insert Edge"<<endl;
    cout<<"2. BFS traversal"<<endl;
    cout<<"3. DFS traversal"<<endl;
    cout<<"4. Calculate diameter of the graph"<<endl;
    cout<<"5. Cycle finding in the graph"<<endl;
    int option;
    cin>>option;

    switch(option) {

        case 1:
            cin>>start>>end;
            addEdge(graph, (int)start-65, (int)end-65);

        case 2:
            BFS(graph, 0);
            break;

        case 3:
            DFS(graph, 0);
            break;

        case 4:
            getDiameter(graph);
            break;

        case 5:
            if(isCyclic(graph)){
                cout<<"Yes"<<endl;
            }else{
                cout<<"No"<<endl;
            }
            break;

        default:
            cout<<"Enter valid option"<<endl;
    }

}