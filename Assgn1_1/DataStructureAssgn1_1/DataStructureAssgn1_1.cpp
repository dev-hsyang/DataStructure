#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum type {

	CONSUMER, SELLER

}CTYPE;

typedef union record {

	int sales;
	int purchases;

}CRECORD;

typedef struct info {

	CTYPE CTYPE;
	CRECORD TOTAL;
	char temp;

}CINFO;

typedef struct costumer {

	char name[20];
	char phonenum[20];
	CINFO info;

}COSTUMER;


void OUTPUT(COSTUMER* CSTMR, int* END) {

	char MAXC[20] = {};
	char MINC[20] = {};
	char MAXS[20] = {};
	char MINS[20] = {};
	float AVC = 0, AVS = 0, CSUM = 0, SSUM = 0, CMAX = 0, CMIN = 0, SMAX = 0, SMIN = 0;
	bool flagC = false, flagS = false;
	int SNUM = 0, CNUM = 0;
	
	for (int i = 0; i < *END; i++) {
		
		if (CSTMR[i].info.CTYPE == 0 && flagC == false) {
			flagC = true;
			CMAX = CSTMR[i].info.TOTAL.purchases;
			CMIN = CSTMR[i].info.TOTAL.purchases;
			strcpy_s(MAXC, strlen("CSTMR[i], name"), CSTMR[i].name);
			strcpy_s(MINC, strlen("CSTMR[i], name"), CSTMR[i].name);
		}
		else if (CSTMR[i].info.CTYPE == 1 && flagS == false) {
			flagS = true;
			SMAX = CSTMR[i].info.TOTAL.sales;
			SMIN = CSTMR[i].info.TOTAL.sales;
			strcpy_s(MAXS, strlen("CSTMR[i], name"), CSTMR[i].name);
			strcpy_s(MINS, strlen("CSTMR[i], name"), CSTMR[i].name);
		}
		if (flagC == true && flagS == true) {
			break;
		}
	}

	for (int i = 0; i<*END ; i++) {

		if (CSTMR[i].info.CTYPE == 0){//구매자일경우

			CNUM++;
			CSUM += CSTMR[i].info.TOTAL.purchases;
			
				if (CMAX < CSTMR[i].info.TOTAL.purchases) {
					CMAX = CSTMR[i].info.TOTAL.purchases;
					strcpy_s(MAXC, strlen("CSTMR[i], name"), CSTMR[i].name);
				}
				if (CMIN > CSTMR[i].info.TOTAL.purchases) {
					CMIN = CSTMR[i].info.TOTAL.purchases;
					strcpy_s(MINC, strlen("CSTMR[i], name"), CSTMR[i].name);
				}
		}
		else {//판매자일경우

			SNUM++;
			SSUM += CSTMR[i].info.TOTAL.sales;

				if (SMAX < CSTMR[i].info.TOTAL.sales) {
					SMAX = CSTMR[i].info.TOTAL.sales;
					strcpy_s(MAXS, strlen("CSTMR[i], name"), CSTMR[i].name);
				}
				if (SMIN > CSTMR[i].info.TOTAL.sales) {
					SMIN = CSTMR[i].info.TOTAL.sales;
					strcpy_s(MINS, strlen("CSTMR[i], name"), CSTMR[i].name);
				}
		}
	}

	if (CNUM != 0) {
		AVC = CSUM / CNUM;
	}
	else if (CNUM == 0) {
		AVC = NULL;
	}
	else if (SNUM != 0) {
		AVS = SSUM / SNUM;
	}
	else if (SNUM == 0) {
		AVS = NULL;
	}

	printf("최저 구매자: %s,  %.1f\n", MINC, CMIN);
	printf("최고 구매자: %s,  %.1f\n", MAXC, CMAX);
	printf("평균 구매액: %.1f\n", AVC);
	printf("최저 판매자: %s,  %.1f\n", MINS, SMIN);
	printf("최고 판매자: %s,  %.1f\n", MAXS, SMAX);
	printf("평균 판매액: %.1f\n", AVS);

}

int main() {

	COSTUMER user[100];
	int end = 0;
	printf("고객 정보를 입력해 주십시오 <이름> <고객유형> <전화번호> <금액>\n\n ");

	for (int i = 0; ; i++) {

		
		printf("<고객이름>:\n"); scanf_s("%s", user[i].name, 20);

		if (strlen(user[i].name) == 2) {
			end = i;
			break;
		}

		printf("\n<고객유형>:\n"); scanf_s(" %c", &user[i].info.temp, 1);
		
		if (user[i].info.temp == 'C') {
			user[i].info.CTYPE = CONSUMER;
		}
		else {
			user[i].info.CTYPE = SELLER;
		}

		printf("\n<전화번호>:\n"); scanf_s("%s", user[i].phonenum, 20);

		if (user[i].info.CTYPE == 0) {
			printf("\n<금액>:\n"); scanf_s("%d", &user[i].info.TOTAL.purchases);
		}
		else {
			printf("\n<금액>:\n"); scanf_s("%d", &user[i].info.TOTAL.sales);
		}

		printf("\n\n");
	}

	OUTPUT(user, &end);
	
	return 0;
}