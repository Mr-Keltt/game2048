#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

// Выводит поле в консоль
void printField(const int* arr, int size) {
    int cellWidth = 5;

    cout << "=================================" << endl;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int index = i * size + j;
            cout << setw(cellWidth) << arr[index];
        }
        cout << endl;
    }

    cout << "=================================" << endl;
}

// Возвращает адрес случайной пустой ячейки поля. Если нет свободных ячее вернет -1
int getRandomEmptyCell(int* field, int size) {
    int* emptyCells = new int[size * size];
    int count = 0;

    for (int i = 0; i < size * size; ++i) {
        if (field[i] == 0) {
            emptyCells[count] = i;
            ++count;
        }
    }

    if (count == 0) {
        return -1;
    }

    int randomIndex = rand() % count;
    return emptyCells[randomIndex];
}

// Возвращает 2 с вероятностью 0.9 или 4 с вероятностью 0.1
int getRandomNumber() {
    
    int randomInt = rand();
    double probability = static_cast<double>(randomInt) / RAND_MAX;

    if (probability < 0.9) {
        return 2;
    }
    else {
        return 4;
    }
}

// Получает на вход массив чисел и преобразует в соответствии с правилами игры
int* calculationSubarray(int* subarray, int size) 
{
    int* res = new int[size];

    int rightPreverifiedI = 0;
    int unoccupiedI = 0;

    for (int i = 0; i < size; i++) 
    {
        res[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        if (subarray[i] != 0)
        {
            if (subarray[i] != res[rightPreverifiedI])
            {
                rightPreverifiedI = unoccupiedI;
                res[unoccupiedI++] = subarray[i];
            }
            else
            {
                res[rightPreverifiedI++] += subarray[i];
            }
        }
    }

    return res;
}

// Делает одно передвижение поля в верх
void moveUp(int* field, int size)
{
    int* tempArr = new int[size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tempArr[j] = field[i + j * size];
        }

        tempArr = calculationSubarray(tempArr, size);

        for (int j = 0; j < size; j++)
        {
            field[i + j * size] = tempArr[j];
        }
    }
}

// Делает одно передвижение поля в низ
void moveDown(int* field, int size)
{
    int* tempArr = new int[size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tempArr[j] = field[i + (size - j - 1) * size];
        }

        tempArr = calculationSubarray(tempArr, size);

        for (int j = 0; j < size; j++)
        {
            field[i + (size - j - 1) * size] = tempArr[j];
        }
    }
}

// Делает одно передвижение поля в лево
void moveLeft(int* field, int size)
{
    int* tempArr = new int[size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tempArr[j] = field[i * size + j];
        }

        tempArr = calculationSubarray(tempArr, size);

        for (int j = 0; j < size; j++)
        {
            field[i * size + j] = tempArr[j];
        }
    }
}

// Делает одно передвижение поля в право
void moveRight(int* field, int size)
{
    int* tempArr = new int[size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tempArr[j] = field[i * size + (size - j - 1)];
        }

        tempArr = calculationSubarray(tempArr, size);

        for (int j = 0; j < size; j++)
        {
            field[i * size + (size - j - 1)] = tempArr[j];
        }
    }
}

bool isWin(int* field, int size)
{
    for (int i = 0; i < size * size; i++)
    {
        if (field[i] == 2048)
        {
            return true;
        }
    }

    return false;
}

// Создает новое число в свободной ячейке и проверяет услове выигрыша/проигрыша
// Возвращает -1 при проигрыше, 1 при выгрыше, 0 при обычном ходе
int makeMove(int* field, int size, char motion)
{
    switch (motion)
    {
    case 'w':
        moveUp(field, size);
        break;
    case 's':
        moveDown(field, size);
        break;
    case 'a':
        moveLeft(field, size);
        break;
    case 'd':
        moveRight(field, size);
        break;
    }

    int i = getRandomEmptyCell(field, size);

    if (i == -1)
    {
        if (isWin(field, size))
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    field[i] = getRandomNumber();

    return 0;
}

void gameProcess(int* field, int size)
{
    int gameState = 0;

    while (gameState == 0)
    {
        char motion;
        cout << "Ваш ход : ";
        cin >> motion;

        gameState = makeMove(field, size, motion);
        printField(field, size);
    }

    if (gameState == -1)
    {
        cout << "Вы проиграли" << endl;
    }

    if (gameState == 1)
    {
        cout << "Вы выиграли" << endl;
    }
}

int main()
{
    setlocale(0, "");
    srand(static_cast<unsigned int>(time(0)));

    const int size = 4;         // Задаем размеры поля
    int field[size*size];       // Создаем поле

    // Инициализируем ячейки поля нулями
    for (int i = 0; i < size*size; i++) 
    {
        field[i] = 0;
    }

    // Заполняем две случайные клетки двойками/четверками
    for (int i = 0; i < 2; i++)
    {
        field[getRandomEmptyCell(field, size)] = getRandomNumber();
    }
 
    printField(field, size);    // Вывод поля
    gameProcess(field, size);       // Запуск игрового процесса
}