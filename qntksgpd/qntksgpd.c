#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int intro(void);
int set_l(int);
int set_p(int);
int set_m(int);
int state_T(int, int, int, int);
void state_S(int, int, int);
void state_M(int, int);
int lines(int);
int move_Z(int, int, int);
int move_C(int, int);
int move_M(int, int);
int act_CZ(int, int, int, int);
int act_M(int, int, int, int);
void over(int, int);
int agro_M(int);
int stamina_M(int);
int agro_C(int);

int agro_c = 1;
int agro_m = 1;
int stay_z = 1;
int moving_c, moving_z, choice_m;
char pos[55];


int lines(int len) {
	printf("\n");
	for (int i = 0; i < len; i++){
		printf("#");
	}
	printf("\n");
	return 0;
}
int intro(void) {
	printf("############\n#  ºÎ»êÇó  #\n############\n");
	return 0;
}
int set_l(int len) {
	while (1) {
		printf("train length(15~50)>>");
		scanf_s("%d", &len);
		if (len <= 50 && len >= 15) {
			break;
		}
	}
	return len;
}
int set_m(int stamina) {
	while (1) {
		printf("madongseok stamina(0~5)>>");
		scanf_s("%d", &stamina);
		if (stamina <= 5 && stamina >= 0) {
			break;
		}
	}
	return stamina;
}
int set_p(int per) {
	while (1) {
		printf("percentile probability 'p'(10~90)>>");
		scanf_s("%d", &per);
		if (per <= 90 && per >= 10) {
			break;
		}
	}
	printf("\n\n");
	return per;
}
int move_C(int per, int move_c) {
	moving_c = rand() % 100 + 1;
	if (moving_c > per) {
		move_c -= 1;
		agro_c += 1;
		agro_c = agro_C(agro_c);
	}
	else {
		agro_c -= 1;
		agro_c = agro_C(agro_c);
	}
	return move_c;
}
int move_Z(int per, int move_z, int move_m) {
	if (stay_z % 2 == 0) {
		moving_z = rand() % 100 + 1;
		if (moving_z < per) {
			if (agro_m > agro_c) {
				if (move_z + 1 != move_m) {
					move_z += 1;
				}
			}
			else {
				move_z -= 1;
			}
		}
	}
	stay_z += 1;
	return move_z;
}
int move_M(int move_m, int move_z) {
	while (1) {
		if (move_z + 1 == move_m) {
			printf("madongseok move(0:stay)>>");
			scanf_s("%d", &choice_m);
			if (choice_m == 0) {
				agro_m -= 1;
				break;
			}
		}
		else {
			printf("madongseok move(0:stay, 1:left)>>");
			scanf_s("%d", &choice_m);
			if (choice_m == 1) {
				move_m -= 1;
				agro_m += 1;
				break;
			}
			else if (choice_m == 0) {
				agro_m -= 1;
				break;
			}
		}
	}
	return move_m;
}
int state_T(int len, int move_c, int move_z, int move_m) {
	for (int i = 0; i < 55; i++) {
		pos[i] = ' ';
	}
	pos[0] = '#';
	pos[len-1] = '#';
	pos[move_c] = 'C';
	pos[move_z] = 'Z';
	pos[move_m] = 'M';
	lines(len);
	for (int i = 0; i < len; i++) {
		printf("%c", pos[i]);
	}
	lines(len);
	printf("\n\n");
	return 0;
}
void state_S(int move_z, int move_c, int per) {
	if (moving_c > per) {
		printf("\n\ncitizen: %d -> %d (aggro: %d -> %d)\n", move_c + 1, move_c, agro_c - 1, agro_c);
	}
	else {
		printf("\n\ncitizen: stay %d (aggro: %d -> %d)\n", move_c, agro_c + 1, agro_c);
	}
	moving_c = 0;
	if (moving_z > per) {
		if (agro_m > agro_c) {
			printf("zombie: %d -> %d\n\n\n", move_z - 1, move_z);
		}
		else {
			printf("zombie: %d -> %d\n\n\n", move_z + 1, move_z);
		}
	}
	else if (moving_z == 0) {
		printf("zombie: stay %d (cannot move)\n\n\n", move_z);
	}
	else {
		printf("zombie: stay %d\n\n\n", move_z);
	}
	moving_z = 0;
}
void state_M(int move_m, int stamina) {
	if (choice_m == 0) {
		if (agro_m == 0) {
			agro_m = 1;
			printf("\n\nmadongseok: stay %d(aggro: %d, stamina: %d)\n\n", move_m, agro_m, stamina);
		}
		else {
			printf("\n\nmadongseok: stay %d(aggro: %d -> %d, stamina: %d)\n\n", move_m, agro_m +1, agro_m, stamina);
		}
	}
	else if (choice_m == 1) {
		if (agro_m == 6) {
			agro_m = agro_M(agro_m);
			printf("\n\nmadongseok: %d -> %d (aggro: %d, stamina: %d)\n\n", move_m+1, move_m, agro_m, stamina);
		}
		else {
			printf("\n\nmadongseok: %d -> %d(aggro: %d -> %d, stamina: %d)\n\n", move_m + 1, move_m, agro_m - 1, agro_m, stamina);
		}
	}
	choice_m = 0;
}
int act_CZ(int move_c, int move_z, int move_m, int stamina) {
	if (move_z + 1 == move_m) {
		if (move_z - 1 == move_c) {
			if (agro_c > agro_m) {
				stamina -= 1;
				printf("citizen does nothing.\n");
				printf("Zomibe attacked madongseok (aggro: %d vs. %d, madingseok stamina: %d -> ",agro_c, agro_m, stamina);
				stamina -= 1;
				printf("%d)\n\n", stamina);
			}
			else {
				printf("citizen does nothing.\n");
				printf("GAME OEVER! citizen dead...");
				exit(0);
			}
		}
		else {
			printf("citizen does nothing.\n");
			printf("Zombie attacked madongseok (madingseok stamina: %d -> ", stamina);
			stamina -= 1;
			printf("%d)\n\n", stamina);
		}
	}
	else if (move_z - 1 == move_c) {
		printf("citizen does nothing.\n");
		printf("GAME OEVER! citizen dead...");
		exit(0);
	}
	else {
		printf("citizen does nothing.\n");
		printf("zombie attacked nobody.\n\n");
	}
	return stamina;
}
int act_M(int move_z, int move_m, int per, int stamina) {
	int p = 0;
	while (p < 1) {
		if (move_m - 1 == move_z) {
			printf("madongseok action(0.rest, 1.provoke, 2.pull)>>");
			scanf_s("%d", &choice_m);
			switch (choice_m) {
			case 0:
				p = 2;
				printf("\n\nmadongseok rests...\nmadongseok: %d (aggro : %d", move_m, agro_m);
				agro_m -= 1;
				agro_m = agro_M(agro_m);
				printf(" -> %d, stamina : %d", agro_m, stamina);
				stamina += 1;
				stamina = stamina_M(stamina);
				printf(" -> %d)\n\n", stamina);
				break;
			case 1:
				p = 2;
				printf("madongseok provoked zombie... \nmadongseok: %d (aggro : %d -> 5, stamina : %d)\n\n", move_m, agro_m, stamina);
				agro_m = 5;
				break;
			case 2:
				p = 2;
				moving_c = rand() % 100 + 1;
				if (moving_c > per) {
					stay_z = 1;
					printf("madongseok pulled zombie... Next turn, it can't move\n");
				}
				else {
					printf("madongseok failed to pull zombie\n");
				}
				printf("madongseok: %d (aggro: %d", move_m, agro_m);
				agro_m += 2;
				agro_m = agro_M(agro_m);
				printf(" -> %d, stamina: %d", agro_m, stamina);
				stamina -= 1;
				printf(" -> %d)\n\n", stamina);
				break;
			}
		}
		else {
			printf("madongseok action(0.rest, 1.provoke)>>");
			scanf_s("%d", &choice_m);
			switch (choice_m) {
			case 0 :
				p = 2;
				printf("\n\nmadongseok rests...\nmadongseok: %d (aggro : %d", move_m, agro_m);
				agro_m -= 1;
				agro_m = agro_M(agro_m);
				printf(" -> %d, stamina : %d", agro_m, stamina);
				stamina += 1;
				stamina = stamina_M(stamina);
				printf(" -> %d)\n\n", stamina);
				break;
			case 1:
				p = 2;
				printf("madongseok provoked zoBmbie... \nmadongseok: %d (aggro : %d -> 5, stamina : %d)\n\n", move_m, agro_m, stamina);
				agro_m = 5;
				break;
			}
		}
	}
	return stamina;
}
void over(int stamina, int move_c) {
	if (stamina <= 0) {
		printf("\n\n\nGAME OEVER! madongseok dead...");
		exit(0);
	}
	if (move_c == 1) {
		printf("\n\n\nSUCCESS! \nYOU WIN! ¡¦");
		exit(0);
	}
}
int agro_C(int agro_c) {
	if (agro_c < 1) {
		agro_c = 1;
	}
	if (agro_c > 5) {
		agro_c = 5;
	}
	return agro_c;
}
int agro_M(int agro_m) {
	if (agro_m < 1) {
		agro_m = 1;
	}
	if (agro_m > 5) {
		agro_m = 5;
	}
	return agro_m;
}
int stamina_M(int stamina) {
	if (stamina > 5) {
		stamina = 5;
	}
	return stamina;
}

int main(void) {
	int len, move_c, move_z, move_m, stamina, per;
	len = 0;
	stamina = 0;
	per = 0;
	srand((unsigned int)time(NULL));
	intro();
	len = set_l(len);
	stamina = set_m(stamina);
	per = set_p(per);
	move_m = len - 2;
	move_c = len - 6;
	move_z = len - 3;
	state_T(len, move_c, move_z, move_m);
	while (1) {
		move_c = move_C(per, move_c);
		move_z = move_Z(per, move_z, move_m);
		state_T(len, move_c, move_z, move_m);
		state_S(move_z, move_c, per);
		over(stamina, move_c);
		move_m = move_M(move_m, move_z);
		state_T(len, move_c, move_z, move_m);
		state_M(move_m, stamina);
		stamina = act_CZ(move_c, move_z, move_m, stamina);
		stamina = act_M(move_z, move_m, per, stamina);
		
		
	}



	return 0;
}