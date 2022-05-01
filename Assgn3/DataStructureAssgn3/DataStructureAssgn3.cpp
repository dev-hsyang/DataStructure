#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 50
char inputString[50] = { NULL };
char redundant[50] = { NULL };
char unclosed[50] = { NULL };
int top = -1;
int countredundant = 0;

typedef struct TOKEN {
    char parentheses = 0;
}TOKEN;

TOKEN stack[MAX_STACK_SIZE];

void stackFull() {
    printf("Stack is Full\n");
}

void clearStack() {
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        stack[i] = { NULL };
    }
    top = -1;
}

void clearStrings() {
    for (int i = 0; i < 50; i++) {
        inputString[i] = { NULL };
        redundant[i] = { NULL };
        unclosed[i] = { NULL };
    }
}

void Push(char item ) {
    if (top >= MAX_STACK_SIZE) {
        stackFull();
        return;
    }
    stack[++top].parentheses = item;
}

char Pop() {
    return stack[top--].parentheses;
}

char Peek() {
    return stack[top].parentheses;
}

void getString() {
    printf("Input Your string: \n"); scanf_s("%s", inputString, sizeof(inputString));
}

char getCloseP() {//짝이 맞지 않는 첫 닫는 괄호를 찾는 함수
    if (Peek() == '(') {
        return ')';
    }
    else if (Peek() == '{') {
        return '}';
    }
    else if (Peek() == '[') {
        return ']';
    }
}

void unClosedP() {//스택에 남아있는 괄호를 배열 unclosed로 옮기는 함수
    int index = top + 1;
    char temp;
    for (int i = 0; i < index; i++ ) {
        unclosed[i] = Pop();        
    }
    for (int i = 0; i < strlen(unclosed)/2; i++) { //스택에 역순으로 저장되어있던 괄호들 뒤집기
        temp = unclosed[i];
        unclosed[i] = unclosed[(strlen(unclosed)-1) - i];
        unclosed[(strlen(unclosed)-1) - i] = temp;
    }
}

int compareP(int i) { //닫는 괄호가 들어왔을떄 여는 괄호와 짝과 맞으면 1, 틀리면 -1 반환
    if (inputString[i] == ')') {
        if (Peek() == '(') {
            Pop();
            return 1;
        }
        else
            return -1;
    }
    else if (inputString[i] == '}') {
        if (Peek() == '{') {
            Pop();
            return 1;
        }
        else
            return -1;
    }
    else if (inputString[i] == ']') {
        if (Peek() == '[') {
            Pop();
            return 1;
        }
        else
            return -1;
    }
}

int checkString() { //문자열의 괄호문자들의 짝이 맞는지 확인하는 함수
    int i = -1;
    while (1) {
        ++i;
        if (inputString[i] == '\0') {
            if (top != -1) { //스택에 괄호가 남아 있는 경우 = 아직 괄호가 안닫힌 경우
                unClosedP();
                printf("**Your string is not balanced. '%s' is not closed.\n", unclosed);
                break;
            }
            if (strlen(redundant)!= 0) {
                 printf("**Your string is not balanced. '%s' is redundant.\n", redundant);
                 countredundant = 0;
                 break;
            }
            else return 1;
        }
        if (inputString[i] == '(') {
            Push(inputString[i]);
        }
        else if (inputString[i] == '{') {
                Push(inputString[i]);
        }
        else if (inputString[i] == '[') {
                Push(inputString[i]);
        } //스택에는 여는 괄호만 push하고, 닫는 괄호가 나오면 스택에서 peek하여 비교해본다.
        else if (inputString[i] == ')') {
            if (top == -1) {
                redundant[countredundant++] = inputString[i];
            }
            else if (compareP(i) == -1) {                  
                 printf("**Your String is not balanced. ')' should have been '%c'\n",getCloseP()); // )와 상응하는 (이 없으면 에러
                 return -1;
            }
        }
        else if (inputString[i] == '}'){
            if (top == -1) {
                redundant[countredundant++] = inputString[i];               
            }
            else if (compareP(i) == -1) {
                printf("**Your String is not balanced. '}' should have been '%c'\n", getCloseP()); // }와 상응하는 {이 없으면 에러
                return -1;
            }
        }
        else if (inputString[i] == ']') {
            if (top == -1) {
                redundant[countredundant++] = inputString[i];
            }
            else if (compareP(i) == -1) {
                printf("**Your String is not balanced. ']' should have been '%c'\n", getCloseP()); // ]와 상응하는 [이 없으면 에러
                return -1;
            }
        }
    }
    return -1;
}

int main() {
    while (1) {
        clearStack();
        clearStrings();
        getString();
        if (inputString[0] == 'q') {
            printf("**Bye");
            return 0;
        }
        if (checkString() == 1) {
            printf("**Your string is balanced\n");
        }
    }
}
