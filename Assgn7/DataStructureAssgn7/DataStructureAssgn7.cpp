#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
const int MAX_VERTICES = 20;
short int visited[MAX_VERTICES] = { 0. };
char* cityTokens[20] = { 0, };
char* path[100] = { 0, };
char pathStatus[9] = { NULL };
char cityName[40] = { NULL };
int citynum = 0;
int distance[MAX_VERTICES] = { 0, };
int found[MAX_VERTICES] = { 0, };
int pi[MAX_VERTICES] = { 0, };

typedef struct GraphNode* gnodePointer;
typedef struct IndexNode* inodePointer;
typedef struct GraphType* gtypePointer;

typedef struct GraphNode {
	int vertex;
	int cost;
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

void initGraph(gtypePointer graph) {
	graph->vertices = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		graph->adjList[v] = NULL;
	}
}

void insertVertex(gtypePointer g, int v) { //graph의 vertex가 몇개인지
	for (int i = 0; i < v; i++) {
		if ((g->vertices) + 1 > MAX_VERTICES) {
			printf("도시 수가 너무 많습니다.\n");
			return;
		}
		g->vertices++;
	}
}

void insertData(gtypePointer g, int u, int v, int c) { //정점u, 간선(u,v)
	if (u >= g->vertices || v >= g->vertices) {
		printf("그래프 정점개수 오류\n");
	}
	gnodePointer node1;
	gnodePointer node2;
	node1 = (gnodePointer)malloc(sizeof(GraphNode));
	node2 = (gnodePointer)malloc(sizeof(GraphNode));

	node1->vertex = v;
	node1->cost = c;
	node1->link = g->adjList[u];
	g->adjList[u] = node1;

	node2->vertex = u;
	node2->cost = c;
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

int isiniNode(char* city, inodePointer head) { //입력된 구축상황이 잘못되면 -1 반환 ::: 없는 도시를 입력하면 -1 반환
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

int getCityNum() { //city 수를 입력받고 저장
	int citynum = 0;
	printf("도시 수를 입력해 주세요\n"); scanf_s("%d", &citynum);
	getchar(); //gets()함수 위해 사용
	return citynum;
}

void getCityName() {
	printf("도시 이름을 입력해 주세요\n"); gets_s(cityName, sizeof(cityName));
	if (strlen(cityName) - (2 * citynum - 1) != citynum) {
		printf("제시된 도시 수와 입력된 도시 이름의 갯수가 다릅니다\n");
	}
}

void getCityToken(char* citynames) { //입력받은 도시 문자열을 도시 이름별로 저장
	int i = 0;
	char* city = strtok(citynames, " ");
	while (city != NULL) {
		cityTokens[i] = city; //자른 문자열을 문자열포인터배열 name에 보관
		i++;
		city = strtok(NULL, " ");
	}
}

void connectStatus(inodePointer head, gtypePointer graph) {
	int temp1, temp2, temp3, count = 0;
	char temp[9] = { 0, };
	printf("도시 간 도로 구축 상황을 입력하세요\n");
	while (1) {
	P1:
		memset(pathStatus, NULL, sizeof(pathStatus));
		temp1, temp2, temp3 = 0;
		scanf_s("%s", pathStatus, sizeof(pathStatus));
		if (strcmp(pathStatus, ".") == 0) { 
			printf("도시 간 도로 구축 데이터베이스를 만들었습니다.\n");
			break;
		}
		strcpy(temp, pathStatus);
		char* ptr = NULL;
		ptr = strtok(pathStatus, "-");
		if (isiniNode(ptr, head) == -1) {
			printf("1번 도시 이름이 잘못 입력되었습니다\n");
			goto P1;
		}
		temp1 = getIndex(ptr, head);
		ptr = strtok(NULL, "-");
		if (isiniNode(ptr, head) == -1) {
			printf("2번 도시 이름이 잘못 입력되었습니다\n");
			goto P1;
		}
		temp2 = getIndex(ptr, head);
		path[count] = (char*)malloc(sizeof(temp));
		strcpy(path[count++], temp);
		for (int i = 0; i < count - 1; i++) {
			if (strcmp(temp, path[i]) == 0) {
				printf("중복된 정보입니다\n");
				count--;
				goto P1;
			}
		}
		ptr = strtok(NULL, "-");
		temp3 = atoi(ptr);
		insertData(graph, temp1, temp2, temp3);
	}
	memset(path, 0, sizeof(path));
	return;
}

int choose(int distance[], int n, int found[]) {
	int min, minpos = 0;
	min = INT_MAX;
	minpos = -1;
	for (int i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void shortestPath(int v, gtypePointer g) {
	gnodePointer z = (gnodePointer)malloc(sizeof(GraphNode));
	gnodePointer x = (gnodePointer)malloc(sizeof(GraphNode));

	int u = 0;
	for (int i = 0; i <  citynum; i++) {
		found[i] = FALSE;
		for (z = g->adjList[v]; z; z = z->link) {
			if (z->vertex != i) {
				distance[i] = 1000;
			}
			else { 
				distance[i] = z->cost; 
				break;
			}
		}
		distance[v] = 0;
		if (distance[i] < 1000) pi[i] = v;
		else pi[i] = -1;
	}
	found[v] = TRUE;
	for (int i = 0; i < citynum - 2; i++) {
		u = choose(distance, citynum, found);
		found[u] = TRUE;
		for (int w = 0; w < citynum; w++) {
			if (!found[w]) {
				for (x = g->adjList[u]; x; x = x->link) {
					if (distance[u] + x->cost < distance[x->vertex]) {
						distance[x->vertex] = distance[u] + x->cost;
						pi[x->vertex] = u;
						break;
					}
				}
			}
		}
	}
}

void findPath(int n, inodePointer head) {
	inodePointer ptr = (inodePointer)malloc(sizeof(*ptr));
	ptr = head;
	for (int i = 0; i < citynum - 1; i++) {
		if (n == ptr->index) printf("%s-", ptr->name);
		ptr = ptr->link;
	}
	if (n == 0) return;
	n = pi[n];
	findPath(n, head);
}

void showShortestPath(inodePointer head, gtypePointer g) {
	getchar();
	while (1) {
		char arr[3] = { NULL, };
		int inputsindex = 0;
		S1:
		printf("** 도착 도시 이름을 입력하세요 (종료 시 ',' 입력)\n"); gets_s(arr, sizeof(arr));
		if (strcmp(arr, ".") == 0) {
			printf("** 검색을 종료합니다\n");
			return;
		}
		inputsindex = getIndex(arr, head);
		if (pi[inputsindex] == -1){
			printf("잘못된 도시 이름입니다\n");
		goto S1;
		}
		findPath(inputsindex, head);
		printf("%d\n", distance[inputsindex]);
	}
}

void getShortestPath(inodePointer head, gtypePointer g) {
	char sourceCity[3] = { 0, };
	int sourceVertex = 0;
	printf("** 출발 도시 이름을 입력하세요\n"); scanf("%s", sourceCity);
	sourceVertex = getIndex(sourceCity, head);
	shortestPath(sourceVertex, g);
}

int main() {
	int n = 0;
	printf("도시 간 최소 비용 경로 안내 서비스에 오신 것을 환영합니다.\n");
	while (1) {
		citynum = 0;
		gtypePointer cityStat = (gtypePointer)malloc(sizeof(GraphType));
		inodePointer cityIndex = NULL; //실행중에 도시들의 index를 초기화하면 안되기에 S2로 go
	S2:
		printf("-------\n원하는 기능을 선택하세요\n");
		printf("1 : 입력  2 : 검색  3: 종료\n"); scanf("%d", &n);
		switch (n) {
		case 1:
			memset(cityTokens, 0, sizeof(cityTokens));
			initGraph(cityStat);
			citynum = getCityNum(); //전역변수인데도 반환받아오지 않으면 실행안됨.
			insertVertex(cityStat, citynum);
			getCityName();
			getCityToken(cityName);
			for (int i = 0; i <= citynum - 1; i++) {
				cityIndex = insertNode(cityIndex, i, cityTokens);
			}
			connectStatus(cityIndex, cityStat);
			break;
		case 2:
			getShortestPath(cityIndex, cityStat);
			showShortestPath(cityIndex, cityStat);
			memset(distance, 0, sizeof(distance));
			memset(found, 0, sizeof(found));
			memset(pi, 0, sizeof(pi));
			break;
		case 3:
			return 0;
		}
		goto S2;
	}
}