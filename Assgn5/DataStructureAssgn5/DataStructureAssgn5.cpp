#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node* TreePointer;
typedef struct node {
	char data;
	TreePointer leftChild, rightChild;
}node;

TreePointer createNode(char data) {
	TreePointer ptr = (TreePointer)malloc(sizeof(node));//예외가 처리되지 않음
	ptr->data = data;
	ptr->leftChild = NULL;
	ptr->rightChild = NULL;
	return ptr;
	//메모리 allocation, treenode만들고 저장
}

TreePointer createTree(char** expr) {//string에 대한 pointer의 주소값을 parameter로
	TreePointer ptr = createNode(**expr);
	if ((**expr == '+') || (**expr == '-') || (**expr == '*') || (**expr == '/')) {
		/*1*/
		*expr += 1;
		ptr->leftChild = createTree(expr);
		/*2*/
		*expr += 1;
		ptr->rightChild = createTree(expr);
		return ptr;
	}//1,2번에서 포인터의 이동이 있어야함
	return ptr;
}

int checkString(char* expr) {
	for (int i = 0; i < strlen(expr); i++) {
		if (expr[i] != '+' && expr[i] != '-' && expr[i] != '*' && expr[i] != '/' && expr[i] != '0' && expr[i] != '1' && expr[i] != '2' && expr[i] != '3' && expr[i] != '4' && expr[i] != '5' && expr[i] != '6' && expr[i] != '7' && expr[i] != '8' && expr[i] != '9') {
			return -1;
		}
	}
	return 1;
}

int EvaluateExprTree(TreePointer ptr) { //rootnode의 포인터
	if ((ptr->leftChild == NULL) && (ptr->rightChild == NULL)) return ptr->data-'0'; //char형 data 형변환
	int op1 = EvaluateExprTree(ptr->leftChild);
	int op2 = EvaluateExprTree(ptr->rightChild);
	//printf("%d %c %d 계산합니다\n", op1, ptr->data, op2);
	switch (ptr->data){
		case'+': return op1 + op2;
		case'-': return op1 - op2;
		case'*': return op1 * op2;
		case'/': return op1 / op2;
	}
}

int main() {
	while (1) {
		while (1) {
			TreePointer expr = NULL;
			char expression[20] = { NULL, };
			char* expressionP = expression;
			printf("수식을 입력하시오 (종료 시 q를 입력하시오):\n"); scanf_s("%s", expression, sizeof(expression));
			if (expression[0] == 'q') return 0;
			if (checkString(expression) == -1) {
				printf("잘못된 문자를 사용하였습니다.\n");
				break;
			}
			expr = createTree(&expressionP);
			printf("계산 결과는 %d 입니다.\n", EvaluateExprTree(expr));
		}
	}
}