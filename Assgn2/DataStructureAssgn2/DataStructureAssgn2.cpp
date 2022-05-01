#include <stdio.h>
#include <string.h>

#define MAX_QUEUE_SIZE 6
int front = 0;
int rear = 0; //front == rear 인것은 큐가 EMPTY일때만 .
char NAME[20] = { NULL };
int stackSize = 0;

typedef struct queue {
	char name[20];
	//int front;
	//int rear;
	//int qsize;
}QUEUE;

QUEUE HOSPITAL[MAX_QUEUE_SIZE];

void enqueue(char *str) {
	++stackSize;
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	strcpy_s(HOSPITAL[rear].name, str);
}

QUEUE dequeue() {
	--stackSize;
	front = (front + 1) % MAX_QUEUE_SIZE;
	return HOSPITAL[front];
}

int isQueueFull() {
	int tempRear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == tempRear) {
		return -1;
	}else 
	return 1;
}

int isQueueEmpty() {
	int tempFront = (front + 1) % MAX_QUEUE_SIZE;
	if (tempFront == rear) {
		stackSize = 0;
		return -1;
	}
	else
		return 1;
}

void getName() {
	int n;
	printf("현재 대기자 수는 %d명 입니다. 다음에서 원하는 기능의 번호를 선택해 주세요.\n1. 대기자 등록	2. 취소\n\n", stackSize); scanf_s("%d", &n);
	switch (n)
	{
	case 1:
		printf("대기자의 이름을 등록해주세요\n"); scanf_s("%s", NAME, 20); //printf("%s", NAME);
		printf("감사합니다.\n");
		break;
	case 2:
		break;
	default:
		printf("번호를 잘못 입력하셨습니다.\n");
	}
}
int nextPatient() {
	int tempfront = front;
	if (tempfront < 4) {
		return ((tempfront + 1) % MAX_QUEUE_SIZE + 1);
	}
	else {
		tempfront = 0;
		return tempfront;
	}
}

int main() {
	int OPERATION = 0;
	while (1) {
		printf("\n\n진료 관리 서비스에 오신 것을 환영합니다. 원하는 기능의 번호를 선택해 주세요.\n\n1. 병원 도착\n2. 진료 완료\n3. 서비스 종료\n\n");
		scanf_s("%d", &OPERATION);
		switch (OPERATION)
		{
		case 1:
			printf("병원도착을 선택하셨습니다.\n");
			if (isQueueFull() == -1) {
				printf("새 진료 접수가 불가합니다.\n");
				break;
			}
			getName();
			enqueue(NAME); //rear ++
			break;
		case 2:
			printf("진료완료를 선택하셨습니다.\n");
			if (isQueueEmpty() == -1) {
				printf("대기 중인 환자가 없습니다.\n");
				//stackSize = 0;
				break;
			}
			printf("%s 님이 진료 대기입니다.\n감사합니다.\n", HOSPITAL[nextPatient()].name);
			dequeue(); //front ++
			break;
		case 3:
			return 0;
		default:
			printf("번호를 잘못 입력하셨습니다.\n");
		}
	}
	return 0;
}//HOSPITAL[(++front)+1].name