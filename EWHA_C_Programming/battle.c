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
        printf("%s | �й�\n", p.name);
        return;
    }

    printf("%s | ü�� : %3d �Ŀ� : %3d ���ǵ� : %3d �� : %4d ���� : %s \n", p.name, p.hp, p.power, p.speed, p.money, p.w.name);

}

void showAllPlayer(Player* p) {
    for (int i = 0; i < NUM; i++) {
        showPlayer(p[i]);
    }
} // ��� �÷��̾��� ������ ����մϴ�.

int buyWeapon(Player* p, Weapon* w) {
    // ���⸦ ������ �÷��̾�� ���� ����� �ް�, ���⸦ �ٲ� �� �ְ� �Ѵ�.
    int choose;
    printf("������ �������\n");
    printf("=====================================\n");
    printf("   ����\t ����\t�Ŀ�\n");
    for (int i = 1; i < 5; i++) {
        printf("%d) %s\t%4d\t%4d\n", i, (w[i]).name, (w[i]).price, (w[i]).power);
    }


    while (1) {
        printf("� ����� �ٲٽðڽ��ϱ�?(���ڷ� �Է�. ���� ���ҽ� 0 �Է�) : ");
        scanf("%d", &choose);

        if (choose == 0) {
            printf("�ȳ��� ���ʽÿ�.\n");
            printf("=====================================\n");
            return 0;
        }
        else if (choose > 5) {
            printf("�߸��� �Է��Դϴ�.\n");
            continue;
        }
        else {
            if (p->money < (w[choose]).price) {
                printf("���� �����Ͽ� ������ �� �����ϴ�.\n");
                continue;
            }
            else {
                p->money -= (w[choose]).price;
                printf("�ش� ����� ��ü�Ͽ����ϴ�. (���� %s���� �ܿ� �ݾ� : %d)\n", p->name, p->money);
                p->w = w[choose];
                return 1;
            }
        }

    }


}

void attack(Player* p, Player* target) {

    printf("!���� �α�!\n");
    target->hp -= (p->power + p->w.power);
    printf("     %s�� %s�� �����մϴ�! ����� %s!   %s hp => %d  \n", p->name, target->name, p->w.name, target->name, target->hp);
    p->money += (p->w.getPoint);
    printf("     %s�� %d��ŭ�� ����Ʈ�� ȹ���߽��ϴ�! (���� %s�� ����Ʈ : %d)\n", p->name, p->w.getPoint, p->name, p->money);

    if (target->hp <= 0) {
        printf("%s�� �й��߽��ϴ�.\n", target->name);
        survive_player--;
    }

    printf("!! ���� �α� �� !!\n");
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
    if (fp1 != NULL) { //ȭ�Ͽ��⿡ �����ߴٸ�
        while (!feof(fp1)) { //���� ������ �о����
            fscanf(fp1, "%s", PL[i].name);
            fscanf(fp1, "%d", &PL[i].hp);
            fscanf(fp1, "%d", &PL[i].power);
            fscanf(fp1, "%d", &PL[i].money);
            fscanf(fp1, "%d", &PL[i].speed);
            i++;
        }
    }
    else printf("���� ���� ����\n");

    i = 0;
    if (fp2 != NULL) { //ȭ�Ͽ��⿡ �����ߴٸ�
        while (!feof(fp2)) { //���� ������ �о����
            fscanf(fp2, "%s", WEP[i].name);
            fscanf(fp2, "%d", &WEP[i].power);
            fscanf(fp2, "%d", &WEP[i].getPoint);
            fscanf(fp2, "%d", &WEP[i].price);
            i++;
        }
        WEP[i].name[i] = '\0';
    }
    else printf("���� ���� ����\n");

    fclose(fp1);
    fclose(fp2);
    

    for (i = 0; i < NUM; i++) {
        (PL[i]).w = WEP[0]; // �ʱ⿡�� ���� �Ǽ��� ����� ���´�.
    }

    printf("battle start! \n\n");
    while (1) {
        notbuy = 1;
        printf("===================================================================\n");
        showAllPlayer(PL); // ��� �÷��̾��� ������ �ٽ� ����մϴ�.
        printf("===================================================================\n");
        if (survive_player <= 1) break;

        for (i = 0; i < NUM; i++) {
            if ((PL[i]).hp > 0 && (PL[i]).speed == turn) {
                atk = &PL[i];
            }
        }  // ������ ������ ã���ϴ�.

        printf("%s�� ���Դϴ�.\n", (*atk).name);
        printf("1. ���� �湮�ϱ�\n2. �����ϱ�\n�Է� : ");
        scanf("%d", &choose);

        if (choose > 2 || choose < 1) {
            printf("�߸��� �Է��Դϴ�.\n");
            while (choose > 2 || choose < 1) {
                printf("�Է�(1 �Ǵ� 2) : ");
                scanf("%d", &choose);
            }
        }
        // ����� �� �Է��� �޽��ϴ�.

        if (choose == 1) {
            notbuy = buyWeapon(atk, WEP); // ���� ����
        }

        if(choose == 2 || notbuy == 0) {
            printf("���� �����Ͻðڽ��ϱ�?\n");
            for (i = 0; i < NUM; i++) {
                printf("%d) %s(ü�� : %d)\n", i + 1, (PL[i]).name, (PL[i]).hp);
            }

            while (1) {

                printf("�Է� : ");
                scanf("%d", &choose);

                if (!(1 <= choose && choose <= NUM + 1)) {
                    printf("�߸��� �Է��Դϴ�.\n");
                    continue;
                }
                if (strcmp(((PL[choose - 1]).name), (*atk).name) == 0) {
                    printf("�ڱ� �ڽ��� ������ �� �����ϴ�.\n");
                    continue;
                }

                if ((PL[choose - 1]).hp <= 0) {
                    printf("�̹� �й��� ����Դϴ�.\n");
                    continue;
                }

                break;

            }
            attack(atk, &(PL[choose - 1]));

        } // ���� ���.



        if (turn == 1) turn = 5;
        else --turn;
        //���� ��ȯ��Ű�� �ڵ��Դϴ�.

    }

    for (i = 0; i < NUM; i++) {
        if (PL[i].hp > 0) {
            printf("%s�� �¸�!\n", (PL[i]).name);
            break;
        }
    }

}