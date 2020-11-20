// слова-буковки.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int N = 100;
int begunok = 0;
int skolko_bukavok = 0;
int zapolneno = 0;
bool try_find_answer(bool* used_or_not_cifry, short int* tablica, bool success, int skolko_bukavok_isp, char* str);
short int find_unused_letter(short int* tablica);
bool check_this_answer(short int* tablica, char* str);
int main()
{
    char* str = NULL;
    str = (char*)calloc(N, sizeof(char));
    scanf("%s", str);
    //bool has_end = false;
    int skolko_bukavok_was_isp = 0;
    bool success = false;
    bool used_or_not_cifry[10] = { false };
    short int tablica[26] ;        // -2 значит там нет числа -1 не определено
    for (int i = 0; i < 25; i += 5)
    {
        tablica[i] = -2;
        tablica[i + 1] = -2;//развертка цикла
        tablica[i + 2] = -2;
        tablica[i + 3] = -2;
        tablica[i + 4] = -2;
    }
    for (int i = 0; i < N && str[i] != '\n'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            short int a = str[i] - 65;
            if (tablica[a] != -1) {
                tablica[a] = -1;
                skolko_bukavok++;
            }
        }
        else if (str[i] != '=' && str[i] != '\n' && str[i] != '+' && str[i] !=0)
        {
            printf("Error\n");
            goto end_prog;
        }
    }
    skolko_bukavok_was_isp = 0;
    if (try_find_answer(used_or_not_cifry, tablica, success, skolko_bukavok_was_isp,str) == true)
    {
        
    }
    else {
        printf("no solution\n");
    }
    end_prog:
    return 0;
}
bool try_find_answer(bool* used_or_not_cifry, short int* tablica, bool success, int skolko_bukavok_isp, char* str)
{
    int pos = find_unused_letter(tablica);// нашли не использованную букву
    bool suc_here = false;
    for (int i = 0; i < 10; i++)
    {
       
        if (used_or_not_cifry[i] == false) // нашли не использованную цифру
        {
            used_or_not_cifry[i] = true;
            tablica[pos] = i;
            skolko_bukavok_isp++;
            if (skolko_bukavok_isp == skolko_bukavok)//максимально заполнено
            {
                suc_here = check_this_answer(tablica, str);
                if (suc_here == true)
                {
                    //вынесение инварианта
                    for (int j = 0; j < N && str[j] != 0 && str[j] != '/n'; j++)
                    {
                        char ch = str[j];
                        if (ch == '=' || ch == '+')
                            printf("%c", ch);
                        else {
                            int temp = (int)ch;
                            temp -= 65;
                            temp = tablica[temp];
                            printf("%d", temp);
                        }
                    }
                    return true;
                }
            }
            else {
                suc_here=try_find_answer(used_or_not_cifry, tablica, success, skolko_bukavok_isp, str);
                if (suc_here == true)
                    return true;
               
            }
            used_or_not_cifry[i] = false; skolko_bukavok_isp--; tablica[pos] = -1;
        }
    }
    return false;
}
short int find_unused_letter( short int* tablica)
{
    int j = 0;
    for (j = 0; j < 26 && tablica[j] != -1; j++);
    return j;
}
bool check_this_answer(short int* tablica, char* str)
{
    long long int left_side = 0, next_plus = 0, right_side = 0;
    int mnoj = 1;
    int i = 0;
    for (i = 0; i < N && str[i] != '\n'; i++)
    {
        //вынесение инварианта
        char ch = str[i];
        if (ch == '+')
        {
            mnoj = 1;
            left_side += next_plus;
            next_plus = 0;
        }
        else if (ch == '=')
        {
            left_side += next_plus;
            next_plus = 0;
            break;
        }
        else {
            int temp = (int)ch;
            temp -= 65;
            temp = tablica[temp];
            if ((temp == 0 && mnoj == 1 && str[i + 1] >= 65 && str[i + 1] <= 90) || ch < 65 || ch >90)
            {
                return false;
            }
            next_plus *= 10;
            next_plus += temp;
            mnoj += 1;
        }
    }


    i++;
    for (; i < N && str[i] != '\n' && str[i] != 0; i++)
    {
        
            int temp = (int)str[i];
            temp -= 65;
            temp = tablica[temp];
            if ((temp == 0 && mnoj == 1) || str[i] < 65 || str[i] >90)
            {
                return false;
            }
            right_side *= 10;
            right_side += temp;
            mnoj += 1;
    }
    //оптимизация перехода
     /*if (right_side == left_side)
         return true;
     else return false;*/
    return (right_side == left_side);
}