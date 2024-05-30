//#include <stdio.h>
//#include <Windows.h>
//#include <time.h>
//
//int main(void) {
//	printf("############\n#  부산헹  #\n############\n");
//	int LEN_MIN, LEN_MAX, PROB_MIN, PROB_MAX, citizen_move, citizen_per;
//	int zombie_move, zombie_per;
//	int zombie_stay = 1;
//	citizen_per = 0;
//	zombie_per = 0;
//	LEN_MAX = 0;
//	PROB_MAX = 0;
//	printf("train length(15~50)>>");
//	scanf_s("%d", &LEN_MIN);
//	citizen_move = LEN_MIN - 6;
//	zombie_move = LEN_MIN - 3;
//	if (LEN_MIN > 50) {
//		printf("종료");
//	}
//	else if (LEN_MIN < 15) {
//		printf("종료");
//	}
//	else {
//		printf("percentile probability 'p'(10~90)>>");
//		scanf_s("%d", &PROB_MIN);
//		if (PROB_MIN > 90) {
//			printf("종료");
//		}
//		else if (PROB_MIN < 10) {
//			printf("종료");
//		}
//		else {  //여기서부터 시작
//			int q = 0;
//			for (int i = 1; i <= LEN_MIN; i++) {
//				printf("#");
//			}
//			printf("\n#");
//			for (int i = 1; i <= citizen_move - 1; i++) {
//				printf(" ");
//			}
//			printf("C");
//			for (int i = 1; i <= zombie_move - citizen_move - 1; i++) {
//				printf(" ");
//			}
//			printf("Z");
//			for (int i = 1; i <= LEN_MIN - zombie_move - 3; i++) {
//				printf(" ");
//			}
//			printf("M#");
//			printf("\n");
//			for (int i = 1; i <= LEN_MIN; i++) {
//				printf("#");
//			}                      //초기 화면
//			while (q < 1) {        //시작
//				srand((unsigned int)time(NULL));
//				citizen_per = rand() % 100;
//				if (citizen_per >= PROB_MIN) {
//					citizen_move -= 1;
//				}
//				if (zombie_stay % 2 == 1) {
//					zombie_per = rand() % 100;
//					if (zombie_per < PROB_MIN) {
//						zombie_move -= 1;
//					}
//				}
//				printf("\n\n\n\n");
//				for (int i = 1; i <= LEN_MIN; i++) {
//					printf("#");
//				}
//				printf("\n#");
//				for (int i = 1; i <= citizen_move - 1; i++) {
//					printf(" ");
//				}
//				printf("C");
//				for (int i = 1; i <= zombie_move - citizen_move - 1; i++) {
//					printf(" ");
//				}
//				printf("Z");
//				for (int i = 1; i <= LEN_MIN - zombie_move - 3; i++) {
//					printf(" ");
//				}
//				printf("M#");
//				printf("\n");
//				for (int i = 1; i <= LEN_MIN; i++) {
//					printf("#");
//				}
//				printf("\n\n\n");
//				if (citizen_per >= PROB_MIN) {
//					printf("citizen: %d -> %d\n", citizen_move + 1, citizen_move);
//				}
//				if (citizen_per < PROB_MIN) {
//					printf("citizen: stay %d\n", citizen_move);
//				}
//				if (zombie_stay % 2 == 1) {
//					if (zombie_per < PROB_MIN) {
//						printf("zomvie: %d -> %d\n", zombie_move + 1, zombie_move);
//					}
//					if (zombie_per >= PROB_MIN) {
//						printf("zomvie: stay %d\n", zombie_move);
//					}
//				}
//				else {
//					printf("zombie: %d (cannot move)", zombie_move);
//				}
//				if (zombie_move == citizen_move) {
//					q = 1;
//					printf("\n\n\nGAME OVER!\nCitizen(s) has(have) been attacked by a zombie\n\n\n");
//					break;
//				}
//				if (citizen_move == 1) {
//					q = 1;
//					printf("\n\n\nSUCCESS!\ncitizen(s) escaped to the next train\n\n\n");
//					break;
//				}
//				zombie_stay = zombie_stay + 1;
//				Sleep(4000);
//			}
//		}
//	}
//	return 0;
//}
