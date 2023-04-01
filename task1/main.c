#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

//������ �� "������"
void InputHandling() {

	printf("�������� ������ ������.\n");
	while (getchar() != '\n') {} //������� ������ �����, ���� ���� ������� ������� �� �������������� ����
}

//��������� ����� �� ��������� ���������
int GenerateNumber(const int min,const int max) {

	int range = max - min + 1;
	int value = rand();

	return min + value % range;
}

//������ ����� �������� ������
float WinCalculation(const float bet, const int minNumber, const int maxNumber, const int amountofAttempts) {
	//���������� ������� ������, ��� ������� �� �������������� ���������� ����� - log2(N), ��� N - ���������� ����� � ���������.
	//���� � ������ log2(N) ��� ������ �������, ������� �������� 50� ��������.
	//���� � ������ ������� ������, ��� log2(N), �� �������� ������� �� ��������� �������:
	//������� = ������ * (�������� ����� / ���������� �������^2)

	int range = maxNumber - minNumber + 1;
	float guaranteedAttempts = ceil(log2(range));
	if (amountofAttempts >= guaranteedAttempts)
		return bet/2;
	else 
		return bet * ((float)range / ((float)amountofAttempts * (float)amountofAttempts));
}

//������� ��� �������� �� ���������� ����
int AgreementForGame() {

	int flag = 0;
	for (;;) {
		if (scanf("%d", &flag) && (flag == 1 || flag == 0)) {
			if (flag == 1) {
				printf("�� ����������� �� ����!\n");
				break;
			}
			else {
				printf("�� ���������� �� ����.");
				return flag;
			}
		}
		else {
			InputHandling();
			continue;
		}
	}
}

//������� ��� �������� �� ���������� ������
int AgreementForRefillingBalance() {

	int flag = 0;
	for (;;) {
		if (scanf("%d", &flag) && (flag == 1 || flag == 0)) {
			if (flag == 1) {
				printf("�� ����������� ��������� ������!\n");
				printf("������� ����� �� ������ �� ������?(�� ����� 100 ����� = 65 �����)\n");
				break;
			}
			else {
				printf("�� ���������� ��������� ������.\n");
				return flag;
			}
		}
		else {
			InputHandling();
			continue;
		}
	}

}

//���������� ����
void Game() {

	printf("��� �������� �� ���� ������� ����� 1, ���� 0 ��� ������ �� ����: ");
	if (!AgreementForGame()) return 0;

	float balance = 0;

	//�������� ����
	for (;;) {

		//���������� ����� ������
		while (1) {
			int balanceFlag = 1;
			float amountofCoins = 0;
			if (balance == 0) printf("� ��� �� ����� ��� �����, ������� ����� �� ������ ������? (�� ����� 100 ����� = 65 �����)\n");
			else {
				printf("� ��� �� ����� %.2f �����, ������� �� ������ ��� �����? ��� �������� ������� 1, ��� ������ ������� 0: ", balance);
				if (!AgreementForRefillingBalance()) balanceFlag = 0;
			}
			if (balanceFlag) {
				if (scanf("%f", &amountofCoins)) {
					if (amountofCoins <= 0) {
						printf("������ �����. ���������� ������ ������������� ���������� �����\n");
						continue;
					}
					printf("�� ������ %.2f �����\n", amountofCoins);
					amountofCoins *= 0.65;
					balance += amountofCoins;
					printf("���������� ����� �� ����� ����� = %.2f\n", balance);
					break;
				}
				else {
					InputHandling();
					continue;
				}
			}
			else {
				break;
			}
		}

		//���� ��������� ��������
		int minNumber = 0;
		int maxNumber = 0;
		printf("������� ��������, �� �������� ����� ������������ �����\n");
		while (1) {
			printf("������� ������� ���������: ");
			if (scanf("%d", &minNumber)) {
				while (1) {
					printf("������� �������� ���������: ");
					if (scanf("%d", &maxNumber)) {
						//�������� �� ��, ����� �������� ��������� �� ��� ������ ��������
						if (maxNumber < minNumber) {
							printf("�������� ��������� �� ����� ���� ������ ��������.\n");
							continue;
						}
						else break;
					}
					else {
						InputHandling();
						continue;
					}
				}
			}
			else {
				InputHandling();
				continue;
			}
			break;
		}

		int chosenNumber = GenerateNumber(minNumber, maxNumber); // ��������� �����

		//���� ���������� ������� ������
		int amountofAttempts = 0;
		for (;;) {
			printf("������� ���������� ������� �� ���������� �����: ");
			if (scanf("%d", &amountofAttempts)) {
				if (amountofAttempts <= 0) {
					printf("�������� ����� ���������� �������, ���������� ������� �� ����� ���� ������������ ��� ����� ����.\n");
					continue;
				}
				else if (amountofAttempts > 20) {
					printf("�������� ����� ���������� �������, ������������ ���������� ������� - 20.\n");
					continue;
				}
				else break;
			}
			else {
				InputHandling();
				continue;
			}
		}

		printf("����� ��������.\n");

		//���� ������ ������
		float bet = 0;
		for (;;) {
			printf("������� ����� �� ������ ���������?\n");
			if (scanf("%f", &bet)) {
				if (bet < 0) {
					printf("������ �����. ������ �� ����� ���� ������������� ������.\n");
					continue;
				}
				else if (bet > balance) {
					printf("������ �����. ������ �� ����� ���� ������ ���������� �������. ��������� ������ - %.2f.\n", balance);
					continue;
				}
				else break;
			}
			else {
				InputHandling();
				continue;
			}
		}

		balance -= bet;
		printf("������� �� ������� - %.2f\n", balance);

		printf("/###############################################/\n");
		printf("�������� ����� - [%d,%d]\n", minNumber, maxNumber);
		printf("���������� ������� - %d\n", amountofAttempts);
		printf("������ - %.2f\n", bet);
		printf("/###############################################/\n");

		//���������� �����
		int attempt = 1;
		int number = 0;
		printf("���� ��������!\n");
		for (attempt; attempt <= amountofAttempts; ++attempt) {
			printf("������� #%d: ", attempt);
			if (scanf("%d", &number)) {
				if (number < minNumber || number > maxNumber) {
					printf("��������� ����� ������� �� ��������, ������� �� ����� �����.\n");
					--attempt;
					continue;
				}
				if (number > chosenNumber) printf("���������� ����� ������ ����������.\n");
				else if (number < chosenNumber) printf("���������� ����� ������ ����������.\n");
				else {
					printf("�����������. �� ������� �����.\n");
					float wonPoints = WinCalculation(bet, minNumber, maxNumber, attempt);
					printf("�������� %.2f �����\n", wonPoints);
					balance += wonPoints;
					printf("��� ������ ����� %.2f\n", balance);
					break;
				}
				if (attempt == amountofAttempts) {
					printf("� ��������� �� ���������, �� �� ������ �������� ����� �� %d �������.\n", amountofAttempts);
					printf("���������� ����� - %d\n", chosenNumber);
					break;
				}
			}
			else {
				InputHandling();
				--attempt;
				continue;
			}

		}
		printf("������� ������� ��� ��� � ����? ��� �������� ������� 1, ��� ������ ������� 0: ");
		if (!AgreementForGame()) return 0;
	}
}

int main() {
	
	system("chcp 1251");

	srand(time(NULL)); // ������������� ������������, ��������� ������� �����

	printf("������, ������� ������� � ���� \"������ �����\"!\n");
	Game();
	
	return 0;
}