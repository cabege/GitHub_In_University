#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM 5

int survive_player = NUM;

typedef struct weapon {

    char name[100];
    int power;
    int getPoint;
    int price;

}Weapon;

typedef struct player {

    char name[100];
    int hp;
    int power;
    int money;
    int speed;

    Weapon w;

}Player;

void showPlayer(Player p) {

    if (p.hp <= 0) {
        printf("%s | 패배\n", p.name);
        return;
    }

    printf("%s | 체력 : %3d 파워 : %3d 스피드 : %3d 돈 : %4d 무기 : %s \n", p.name, p.hp, p.power, p.speed, p.money, p.w.name);

}

void showAllPlayer(Player* p) {
    for (int i = 0; i < NUM; i++) {
        showPlayer(p[i]);
    }
} // 모든 플레이어의 정보를 출력합니다.

int buyWeapon(Player* p, Weapon* w) {
    // 무기를 구입할 플레이어와 무기 명단을 받고, 무기를 바꿀 수 있게 한다.
    int choose;
    printf("상점에 어서오세요\n");
    printf("=====================================\n");
    printf("   무기\t 가격\t파워\n");
    for (int i = 1; i < 5; i++) {
        printf("%d) %s\t%4d\t%4d\n", i, (w[i]).name, (w[i]).price, (w[i]).power);
    }


    while (1) {
        printf("어떤 무기로 바꾸시겠습니까?(숫자로 입력. 구매 안할시 0 입력) : ");
        scanf("%d", &choose);

        if (choose == 0) {
            printf("안녕히 가십시오.\n");
            printf("=====================================\n");
            return 0;
        }
        else if (choose > 5) {
            printf("잘못된 입력입니다.\n");
            continue;
        }
        else {
            if (p->money < (w[choose]).price) {
                printf("돈이 부족하여 구매할 수 없습니다.\n");
                continue;
            }
            else {
                p->money -= (w[choose]).price;
                printf("해당 무기로 교체하였습니다. (현재 %s님의 잔여 금액 : %d)\n", p->name, p->money);
                p->w = w[choose];
                return 1;
            }
        }

    }


}

void attack(Player* p, Player* target) {

    printf("!전투 로그!\n");
    target->hp -= (p->power + p->w.power);
    printf("     %s가 %s를 공격합니다! 무기는 %s!   %s hp => %d  \n", p->name, target->name, p->w.name, target->name, target->hp);
    p->money += (p->w.getPoint);
    printf("     %s는 %d만큼의 포인트를 획득했습니다! (현재 %s의 포인트 : %d)\n", p->name, p->w.getPoint, p->name, p->money);

    if (target->hp <= 0) {
        printf("%s는 패배했습니다.\n", target->name);
        survive_player--;
    }

    printf("!! 전투 로그 끝 !!\n");
}



int main() {

    int i = 0, choose, notbuy, turn = NUM;

    Player PL[NUM];
    Player* atk = NULL;

    Weapon WEP[NUM];

    FILE* fp1 = NULL;
    FILE* fp2 = NULL;

    fp1 = fopen("Player.txt", "r"); 
    fp2 = fopen("Weapon.txt", "r"); 
    if (fp1 != NULL) { //화일열기에 성공했다면
        while (!feof(fp1)) { //파일 끝가지 읽어오기
            fscanf(fp1, "%s", PL[i].name);
            fscanf(fp1, "%d", &PL[i].hp);
            fscanf(fp1, "%d", &PL[i].power);
            fscanf(fp1, "%d", &PL[i].money);
            fscanf(fp1, "%d", &PL[i].speed);
            i++;
        }
    }
    else printf("파일 열기 실패\n");

    i = 0;
    if (fp2 != NULL) { //화일열기에 성공했다면
        while (!feof(fp2)) { //파일 끝가지 읽어오기
            fscanf(fp2, "%s", WEP[i].name);
            fscanf(fp2, "%d", &WEP[i].power);
            fscanf(fp2, "%d", &WEP[i].getPoint);
            fscanf(fp2, "%d", &WEP[i].price);
            i++;
        }
        WEP[i].name[i] = '\0';
    }
    else printf("파일 열기 실패\n");

    fclose(fp1);
    fclose(fp2);
    

    for (i = 0; i < NUM; i++) {
        (PL[i]).w = WEP[0]; // 초기에는 전부 맨손을 무기로 갖는다.
    }

    printf("battle start! \n\n");
    while (1) {
        notbuy = 1;
        printf("===================================================================\n");
        showAllPlayer(PL); // 모든 플레이어의 정보를 다시 출력합니다.
        printf("===================================================================\n");
        if (survive_player <= 1) break;

        for (i = 0; i < NUM; i++) {
            if ((PL[i]).hp > 0 && (PL[i]).speed == turn) {
                atk = &PL[i];
            }
        }  // 누구의 턴인지 찾습니다.

        printf("%s의 턴입니다.\n", (*atk).name);
        printf("1. 상점 방문하기\n2. 공격하기\n입력 : ");
        scanf("%d", &choose);

        if (choose > 2 || choose < 1) {
            printf("잘못된 입력입니다.\n");
            while (choose > 2 || choose < 1) {
                printf("입력(1 또는 2) : ");
                scanf("%d", &choose);
            }
        }
        // 제대로 된 입력을 받습니다.

        if (choose == 1) {
            notbuy = buyWeapon(atk, WEP); // 무기 구입
        }

        if(choose == 2 || notbuy == 0) {
            printf("누굴 공격하시겠습니까?\n");
            for (i = 0; i < NUM; i++) {
                printf("%d) %s(체력 : %d)\n", i + 1, (PL[i]).name, (PL[i]).hp);
            }

            while (1) {

                printf("입력 : ");
                scanf("%d", &choose);

                if (!(1 <= choose && choose <= NUM + 1)) {
                    printf("잘못된 입력입니다.\n");
                    continue;
                }
                if (strcmp(((PL[choose - 1]).name), (*atk).name) == 0) {
                    printf("자기 자신을 공격할 수 없습니다.\n");
                    continue;
                }

                if ((PL[choose - 1]).hp <= 0) {
                    printf("이미 패배한 대상입니다.\n");
                    continue;
                }

                break;

            }
            attack(atk, &(PL[choose - 1]));

        } // 공격 명령.



        if (turn == 1) turn = 5;
        else --turn;
        //턴을 순환시키는 코드입니다.

    }

    for (i = 0; i < NUM; i++) {
        if (PL[i].hp > 0) {
            printf("%s의 승리!\n", (PL[i]).name);
            break;
        }
    }

}