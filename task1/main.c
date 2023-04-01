#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

//Защита от "Дурака"
void InputHandling() {

	printf("Неверный формат записи.\n");
	while (getchar() != '\n') {} //очистка потока ввода, если были введены символы не целочисленного типа
}

//Генерация числа из заданного диапазона
int GenerateNumber(const int min,const int max) {

	int range = max - min + 1;
	int value = rand();

	return min + value % range;
}

//Расчет суммы выигрыша игрока
float WinCalculation(const float bet, const int minNumber, const int maxNumber, const int amountofAttempts) {
	//Количество попыток игрока, при которых он гарантированно отгадывает число - log2(N), где N - количество чисел в диапазоне.
	//Если у игрока log2(N) или больше попыток, система забирает 50№ выигрыша.
	//Если у игрока попыток меньше, чем log2(N), он получает выигрыш по следующей формуле:
	//Выигрыш = Ставка * (Диапазон чисел / Количество попыток^2)

	int range = maxNumber - minNumber + 1;
	float guaranteedAttempts = ceil(log2(range));
	if (amountofAttempts >= guaranteedAttempts)
		return bet/2;
	else 
		return bet * ((float)range / ((float)amountofAttempts * (float)amountofAttempts));
}

//Функция для согласия на проведение игры
int AgreementForGame() {

	int flag = 0;
	for (;;) {
		if (scanf("%d", &flag) && (flag == 1 || flag == 0)) {
			if (flag == 1) {
				printf("Вы согласились на игру!\n");
				break;
			}
			else {
				printf("Вы отказались от игры.");
				return flag;
			}
		}
		else {
			InputHandling();
			continue;
		}
	}
}

//Функция для согласия на пополнение баланс
int AgreementForRefillingBalance() {

	int flag = 0;
	for (;;) {
		if (scanf("%d", &flag) && (flag == 1 || flag == 0)) {
			if (flag == 1) {
				printf("Вы согласились пополнить баланс!\n");
				printf("Сколько монет вы хотели бы внести?(По курсу 100 монет = 65 очков)\n");
				break;
			}
			else {
				printf("Вы отказались пополнить баланс.\n");
				return flag;
			}
		}
		else {
			InputHandling();
			continue;
		}
	}

}

//Проведение игры
void Game() {

	printf("Для согласия на игру введите цифру 1, либо 0 для отказа от игры: ");
	if (!AgreementForGame()) return 0;

	float balance = 0;

	//Основной цикл
	for (;;) {

		//Пополнение счета игрока
		while (1) {
			int balanceFlag = 1;
			float amountofCoins = 0;
			if (balance == 0) printf("У вас на счету нет очков, сколько монет вы хотите внести? (По курсу 100 монет = 65 очков)\n");
			else {
				printf("У вас на счету %.2f очков, желаете ли внести еще монет? Для согласия введите 1, для отказа введите 0: ", balance);
				if (!AgreementForRefillingBalance()) balanceFlag = 0;
			}
			if (balanceFlag) {
				if (scanf("%f", &amountofCoins)) {
					if (amountofCoins <= 0) {
						printf("Ошибка ввода. Необходимо внести положительное количество монет\n");
						continue;
					}
					printf("Вы внесли %.2f монет\n", amountofCoins);
					amountofCoins *= 0.65;
					balance += amountofCoins;
					printf("Количество очков на вашем счету = %.2f\n", balance);
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

		//Ввод диапазона значений
		int minNumber = 0;
		int maxNumber = 0;
		printf("Введите диапазон, из которого будет загадываться число\n");
		while (1) {
			printf("Введите минимум диапазона: ");
			if (scanf("%d", &minNumber)) {
				while (1) {
					printf("Введите максимум диапазона: ");
					if (scanf("%d", &maxNumber)) {
						//проверка на то, чтобы максимум диапазона не был меньше минимума
						if (maxNumber < minNumber) {
							printf("Максимум диапазона не может быть меньше минимума.\n");
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

		int chosenNumber = GenerateNumber(minNumber, maxNumber); // выбранное число

		//Ввод количества попыток игрока
		int amountofAttempts = 0;
		for (;;) {
			printf("Введите количество попыток на угадывание числа: ");
			if (scanf("%d", &amountofAttempts)) {
				if (amountofAttempts <= 0) {
					printf("Неверное число количества попыток, количество попыток не может быть отрицательно или равно нулю.\n");
					continue;
				}
				else if (amountofAttempts > 20) {
					printf("Неверное число количества попыток, максимальное количество попыток - 20.\n");
					continue;
				}
				else break;
			}
			else {
				InputHandling();
				continue;
			}
		}

		printf("Число загадано.\n");

		//Ввод ставки игрока
		float bet = 0;
		for (;;) {
			printf("Сколько очков вы хотите поставить?\n");
			if (scanf("%f", &bet)) {
				if (bet < 0) {
					printf("Ошибка ввода. Ставка не может быть отрицательным числом.\n");
					continue;
				}
				else if (bet > balance) {
					printf("Ошибка ввода. Ставка не может быть больше доступного баланса. Доступный баланс - %.2f.\n", balance);
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
		printf("Остаток на балансе - %.2f\n", balance);

		printf("/###############################################/\n");
		printf("Диапазон числа - [%d,%d]\n", minNumber, maxNumber);
		printf("Количество попыток - %d\n", amountofAttempts);
		printf("Ставка - %.2f\n", bet);
		printf("/###############################################/\n");

		//Угадывание числа
		int attempt = 1;
		int number = 0;
		printf("Игра началась!\n");
		for (attempt; attempt <= amountofAttempts; ++attempt) {
			printf("Попытка #%d: ", attempt);
			if (scanf("%d", &number)) {
				if (number < minNumber || number > maxNumber) {
					printf("Введенное число выходит за диапазон, который вы ввели ранее.\n");
					--attempt;
					continue;
				}
				if (number > chosenNumber) printf("Загаданное число меньше введенного.\n");
				else if (number < chosenNumber) printf("Загаданное число больше введенного.\n");
				else {
					printf("Поздравляем. Вы угадали число.\n");
					float wonPoints = WinCalculation(bet, minNumber, maxNumber, attempt);
					printf("Выиграно %.2f очков\n", wonPoints);
					balance += wonPoints;
					printf("Ваш баланс равен %.2f\n", balance);
					break;
				}
				if (attempt == amountofAttempts) {
					printf("К сожалению вы проиграли, вы не смогли отгадать число за %d попыток.\n", amountofAttempts);
					printf("Загаданное число - %d\n", chosenNumber);
					break;
				}
			}
			else {
				InputHandling();
				--attempt;
				continue;
			}

		}
		printf("Желаете сыграть еще раз в игру? Для согласия введите 1, для отказа введите 0: ");
		if (!AgreementForGame()) return 0;
	}
}

int main() {
	
	system("chcp 1251");

	srand(time(NULL)); // инициализация рандомайзера, используя текущее время

	printf("Привет, давайте сыграем в игру \"Угадай число\"!\n");
	Game();
	
	return 0;
}