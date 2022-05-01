#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
const int MAX_VERTICES = 20;
short int visited[MAX_VERTICES] = { 0. };
//short int visitedC[MAX_VERTICES] = { 0, };
char* name[20] = { 0, };
char* path[100] = { 0, };
//char* reco[3] = { 0, };
char pathStatus[6] = { NULL };
//int index[20] = { 0, };
int citynum = 0;
//int c = 0;

typedef struct GraphNode* gnodePointer;
typedef struct IndexNode* inodePointer;

typedef struct GraphNode {
	int vertex;
	char cityname[10];
	gnodePointer link;
}GraphNode;

typedef struct IndexNode {
	int index;
	char name[3];
	inodePointer link;
}IndexNode;

typedef struct GraphType {
	int vertices; //현재 저장된 listnode 개수
	gnodePointer adjList[MAX_VERTICES];
}GraphType;

void initGraph(GraphType* graph) {
	graph->vertices = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		graph->adjList[v] = NULL;
	}
}

void insertVertex(GraphType* g, int v) { //graph의 vertex가 몇개인지
	for (int i = 0; i < v; i++) {
		if ((g->vertices) + 1 > MAX_VERTICES) {
			printf("도시 수가 너무 많습니다.\n");
			return;
		}
		g->vertices++;
	}
}

void insertEdge(GraphType* g, int u, int v) { //정점u, 간선(u,v)
	if (u >= g->vertices || v >= g->vertices) {
		printf("그래프 정점개수 오류\n");
	}
	gnodePointer node1;
	gnodePointer node2;
	node1 = (gnodePointer)malloc(sizeof(GraphNode));
	node2 = (gnodePointer)malloc(sizeof(GraphNode));

	node1->vertex = v;
	node1->link = g->adjList[u];
	g->adjList[u] = node1;

	node2->vertex = u;
	node2->link = g->adjList[v];
	g->adjList[v] = node2;
}

inodePointer newNode(int k, char** name) {
	inodePointer ptr = (inodePointer)malloc(sizeof(*ptr));
	ptr->index = k;
	strcpy(ptr->name, name[k]);
	ptr->link = NULL;
	return ptr;
}

inodePointer insertNode(inodePointer node, int k, char** name) { //입력받은 도시를 도시이름과 index정보로 chained linkedlist형태로 저장 ::: 도시이름 index화
	if (node == NULL) return newNode(k, name);
	node->link = insertNode(node->link, k, name);
	return node;
}

int checkiNode(char* city, inodePointer head) { //입력된 구축상황이 잘못되면 -1 반환 ::: 없는 도시를 입력하면 -1 반환
	for (int i = 0; i < citynum; i++) {
		if (strcmp(city, head->name) == 0) {
			return 1;
		}
		else head = head->link;
	}
	return -1;
}

int getIndex(char* city, inodePointer head) { //입력된 구축상황의 도시에 해당하는 index를 반환
	for (int i = 0; i < citynum - 1; i++) {
		if (strcmp(city, head->name) == 0)
			return head->index;
		head = head->link;
	}
}

void connectStatus(inodePointer head, GraphType* graph) {
	int temp1, temp2, count = 0;
	char temp[6] = { 0, };
	printf("도시 간 도로 구축 상황을 입력하세요\n");
	while (1) {
	P1:
		memset(pathStatus, NULL, sizeof(pathStatus));
		temp1, temp2 = 0;
		scanf_s("%s", pathStatus, sizeof(pathStatus));
		if (strcmp(pathStatus, ".") == 0) break;
		strcpy(temp, pathStatus);
		char* ptr = NULL;
		ptr = strtok(pathStatus, "-");
		if (checkiNode(ptr, head) == -1) {
			printf("1번 도시 이름이 잘못 입력되었습니다\n");
			goto P1;
		}
		temp1 = getIndex(ptr, head);
		ptr = strtok(NULL, "-");
		if (checkiNode(ptr, head) == -1) {
			printf("2번 도시 이름이 잘못 입력되었습니다\n");
			goto P1;
		}
		temp2 = getIndex(ptr, head);
		path[count] = (char*)malloc(sizeof(temp));
		strcpy(path[count++], temp);
		for (int i = 0; i < count-1; i++) {
			if (strcmp(temp, path[i]) == 0){
				printf("중복된 정보입니다\n");
				count--;
				goto P1;
			}
		}
		insertEdge(graph, temp1, temp2);
	}
	memset(path, 0, sizeof(path));
	return;
}

int getCityNum() { //city 수를 입력받고 저장
	int citynum = 0;
	printf("도시 수를 입력해 주세요\n"); scanf_s("%d", &citynum);
	getchar(); //gets()함수 위해 사용
	return citynum;
}

void getCityToken(char* citynames) { //입력받은 도시 문자열을 도시 이름별로 저장
	int i = 0;
	char* city = strtok(citynames, " ");
	while (city != NULL) {
		name[i] = city; //자른 문자열을 문자열포인터배열 name에 보관
		i++;
		city = strtok(NULL, " ");
	}
}
/*
void printAdjList(GraphType* graph) { //graph의 adjlist를 출력
	for (int i = 0; i < graph->vertices; i++) {
		gnodePointer node = (gnodePointer)malloc(sizeof(GraphNode));
		node = graph->adjList[i];
		printf("vertex %d's adjList:", i);
		while (node != NULL) {
			printf("->%d", node->vertex);
			node = node->link;
		}
		printf("\n");
	}
}
*/
void dfs(GraphType* graph, int v) { //graph를 dfs 하는 함수
	visited[v] = TRUE;
	gnodePointer w = (gnodePointer)malloc(sizeof(GraphNode));
	for (w = graph->adjList[v]; w; w = w->link) {
		if (!visited[w->vertex]) {
			dfs(graph, w->vertex);
		}
	}
}
/*
void unconnect1(GraphType* graph, int v) { //graph를 dfs 하는 함수
	visitedC[v] = TRUE;
	gnodePointer w = (gnodePointer)malloc(sizeof(GraphNode));
	printf("%s ", name[v]);
	reco[c] = (char*)malloc(sizeof(name[v]));
	strcpy(reco[c], name[v]);
	for (w = graph->adjList[v]; w; w = w->link) {
		if (!visitedC[w->vertex]) {
			unconnect1(graph, w->vertex);
		}
	}
}

void unconnect2(GraphType* graph, int n) {
	for (int i = 0; i < n; i++) {
		if (!visited[i])
			unconnect1(graph, i);
	}
}

void unconnectedC(GraphType* graph) {
	printf("이 도로 구축은 전체 도시들을 연결하지 못하고 있습니다\n");
	printf("( ");
	unconnect1(graph, 0);
	c++;
	printf("), ( ");
	memset(visitedC, 0, sizeof(visitedC));
	unconnect2(graph, citynum );
	printf(")로 분리됩니다\n");
	printf("다음의 경로를 추천합니다\n");
	printf("%s-%s\n", reco[0], reco[1]);

	printf("--------------------------------------------\n\n");
}

void connected(GraphType* graph, int n) {
	for (int i = 0; i < n; i++) {
		if (!visited[i])//연결된 도시는 지나침
			dfs(graph, i);
		printf("%s ", name[i]);
	}
}

void printConnectedCity() {

}
*/
int main() {
	while (1) {
	CASE2:
		citynum = 0;
		char citynames[40] = { NULL };
		GraphType* graph2 = (GraphType*)malloc(sizeof(GraphType));
		inodePointer indexedCity = NULL;
		printf("도시 간 경로 평가 서비스에 오신 것을 환영합니다\n");
	CASE1:
		initGraph(graph2); //그래프 초기화
		memset(name, 0, sizeof(name)); //name 초기화
		citynum = getCityNum();
		if (citynum == 0) {
			printf("서비스를 종료합니다\n");
			return 0;
		}
		insertVertex(graph2, citynum);
		printf("도시 이름을 입력해 주세요\n"); gets_s(citynames, sizeof(citynames));
		if (strlen(citynames) - (2 * citynum - 1) != citynum) {
			printf("제시된 도시 수와 입력된 도시 이름의 갯수가 다릅니다\n");
			goto CASE1;
		}
		getCityToken(citynames); //입력받은 문자열에서 도시이름만 개별로 저장
		for (int i = 0; i <= citynum - 1; i++) {
			indexedCity = insertNode(indexedCity, i, name);
		}
		connectStatus(indexedCity, graph2);
		dfs(graph2, 0);
		for (int i = 0; i <= citynum-1; i++) {
			if (visited[i] == FALSE) {
				printf("이 도로 구축은 전체 도시들을 연결하지 못하고 있습니다\n");
				printf("----------------------------------------------------------------\n\n");
				goto CASE2;
			}
		}
		printf("성공적인 도로 구축 계획입니다\n");
		printf("----------------------------------------------------------------\n\n");		
		memset(visited, 0, sizeof(visited));
		//memset(visitedC, 0, sizeof(visitedC));
		free(graph2);
		free(indexedCity);
		//c = 0;
	}
	return 0;
}