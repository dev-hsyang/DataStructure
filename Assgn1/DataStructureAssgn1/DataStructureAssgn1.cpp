
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union record {

    int sales;
    int purchases;

}RECORD; //4byte memory공유


typedef struct info {

    RECORD sum;

}INFO;


typedef struct user {

    char name[20];
    char phonenum[20];
    INFO typeofuser;

}USER;


/*
 최저 구매자의 이름, 금액
 최고 구매자의 이름, 금액
 평균 구매액
 최저 판매자의 이름, 금액
 최고 판매자의 이름, 금액
 평균 판매액
 */
void output(USER* costum) {

    char MAXC[20];
    char MAXS[20];
    char MINC[20];
    char MINS[20];
    int CMAX = 0, SMAX = 0, CMIN = 0, SMIN = 0;
    float  AVS = 0, AVC = 0;

   
    for (int i = 0; ; i++) {
        

    }
    printf("<최저 구매자의 이름과 금액>: %s  %d", MINC, CMIN);

    printf("<최고 구매자의 이름과 금액>: %s  %d", MAXC, CMAX);

    printf("<평균 구매액>: %f", AVC);

    printf("<최저 판매자의 이름과 금액>: %s  %d", MINS, SMIN);

    printf("<최고 판매자의 이름과 금액>: %s  %d", MAXS, SMAX);

    printf("<평균 판매액>: %f", AVS);
}

int main(){


    char CS;
    USER costumer[100];


    for (int i = 0; ; i++) {
       

            printf("<고객이름>:\n"); 
            scanf_s("%s", costumer[i].name);
               
            if (strlen(costumer[i].name)==2)
           
                break;
            
            printf("\n<고객유형>:\n"); scanf_s(" %c", &CS);
            printf("\n<전화번호>:\n"); scanf_s("%s", costumer[i].phonenum);
            //printf("\n<금액>:\n"); scanf_s("%d", &costumer[i].typeofuser.sum.purchases);

            if (CS == 'C') {

                printf("\n<금액>:\n");
                scanf_s("%d", &costumer[i].typeofuser.sum.purchases);

            }
            else if (CS == 'S') {

                printf("\n<금액>:\n");
                scanf_s("%d", &costumer[i].typeofuser.sum.sales);

            }
            else {

                printf("\n::잘못된 고객유형입력::\n");
                break;
            }
            
            printf("\n\n");

       // }
    }
    //output(costumer);

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
