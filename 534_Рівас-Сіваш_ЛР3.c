/*
    Лабораторна робота № 3
    Рівас Сіваш Максим
    534 група

    Варіянт 12:
    Написати програму для секундоміра. Виводити на індикатори кількість хвилин і секунд у
    форматі ММ.СС:
*/

#include <avr/io.h>
#include <avr/delay.h>
#include <stdbool.h>

uint8_t Ni = 0;
uint8_t ticks = 0;
uint8_t IND[4] = {0, 0, 0, 0};

// Змінює масив IND відповідно до нових значень
void recalculateOutput();

// Додає одну секунду до секундоміра
void addOneSecond();

// Переходить до наступного індикатора
void nextIndicator();

// Відображає поточний індикатор
void showCurrentIndicator();

void main()
{
    DDRD = 0x7F;
    while (true)
    {
        showCurrentIndicator();
        nextIndicator();
        if (ticks > 200)
        {
            addOneSecond();
            recalculateOutput();
        }
    }
}

void recalculateOutput()
{
    if (IND[3] > 9)
    {
        IND[3] = 0;
        IND[2]++;
    }

    if (IND[2] > 6)
    {
        IND[2] = 0;
        IND[1]++;
    }

    if (IND[1] > 9)
    {
        IND[1] = 0;
        IND[0]++;
    }

    if (IND[0] > 9)
    {
        IND[0] = 0;
        IND[1] = 0;
        IND[2] = 0;
        IND[3] = 0;
    }
}

void addOneSecond()
{
    ticks = 0;
    IND[3]++;
}

void nextIndicator()
{
    Ni = (Ni + 1) & 3;

    ticks++;
}

void showCurrentIndicator()
{
    PORTD = IND[Ni] | (Ni << 4);
    if (Ni == 1)
        PORTD |= PD6;

    _delay_ms(5);
}