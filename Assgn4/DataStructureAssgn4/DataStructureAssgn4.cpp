#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

//listPointer start = NULL; start = (listPointer)malloc(sizeof(*start));
int inputvalue;
int deletevalue;
listPointer deletenodeFront = (listPointer)malloc(sizeof(deletenodeFront));

int checkRedundant(listPointer first) {
	if (first == NULL); return -1; //비어있는 list
	for (; first != NULL; first = first->link) {
		if ((first->data) == inputvalue) return 1;
	}
	return -1;
}

void insertValue(listPointer* first) {
	listPointer temp = (listPointer)malloc(sizeof(temp));
	listPointer temp2 = (listPointer)malloc(sizeof(temp2));
	temp->data = inputvalue;
	temp2 = *first;
	if (checkRedundant(temp2) == 1) {
		printf("중복된 데이터입니다.\n");
		return;
	}
	if (*first!=NULL) {
		printf("list에 node가 있는경우 추가합니다\n");
		temp->link = *first;
		*first = temp;
	}
	else {
		printf("list에 node가 없는경우 추가합니다\n");
		temp->link = NULL;
		*first = temp;
	}
}

listPointer findNode(listPointer first) { //지우려는 값을 list에서 찾아 주소값을 반환해주는 함수
	listPointer temp = NULL; temp = (listPointer)malloc(sizeof(temp));
	temp = first;
	if (first == NULL) return NULL; //list가 비어있는 경우
	for (; temp != NULL; temp = temp->link) {
		if ((temp->data) == deletevalue) return temp;
		deletenodeFront = temp;
	}
	return first;
}

void deleteValue(listPointer first) {
	if (findNode(first)) {
		deletenodeFront->link = findNode(first)->link;
		printf("성공했습니다.\n");
	}
	else if (findNode(first) == first) {
		printf("해당하는 데이터가 없습니다.\n");
	}
	else {
		printf("list가 비어있습니다.\n");
	}
}

int main(){
	listPointer start = NULL; start = (listPointer)malloc(sizeof(*start));
    char select = NULL;

	while (1) {
		printf("*명령어를 입력하세요\n\n"); scanf_s(" %c", &select, sizeof(select));
		switch (select) {
		case 'a':{
			printf("추가할 데이터를 입력하세요:\n"); scanf_s("%d", &inputvalue);
			insertValue(&start);
			//printf("%d\n", start->data); printf("%d\n", start->link->data);
			break;
		}
		case 'd':{
			printf("삭제할 데이터를 입력하세요:\n"); scanf_s("%d", &deletevalue);
			deleteValue(start);
			break;
		}
		case 'p':{
			printf("c selected\n");
			break;
		}
		case 'r':{
			printf("r selected\n");
			break;
		}
		case 'q':{
			return 0;
		}
		default: printf("명령어를 잘못 입력하셨습니다.\n");
				break;
		}
	}  
}
