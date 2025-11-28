#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "sort.h"

#define STRING_MAX 512ull

// Читання рядка
int32_t get_str(const char* msg, char* str, int32_t limit)
{
    printf("%s", msg);
    char c;
    size_t size = 0;

    while (size < (size_t)(limit - 1) && (c = getchar()) != EOF && c != '\n')
    {
        str[size++] = c;
    }

    str[size] = '\0';
    return (int32_t)size;
}

// Аналог strlen
size_t strlenn(const char* str)
{
    size_t cnt = 0;
    while (str[cnt] != '\0')
        cnt++;
    return cnt;
}

// Копіювання рядка
void strcopy(char* dest, const char* src, size_t until)
{
    while (until-- > 0 && (*dest++ = *src++));
}

// Порівняння рядків
int32_t strcmpp(const char* a, const char* b)
{
    while (*a && *a == *b)
    {
        a++;
        b++;
    }
    return (int32_t)((unsigned char)*a - (unsigned char)*b);
}

// Конкатенація
char* strcatt(char* fStr, const char* sStr)
{
    char* ptr = fStr + strlenn(fStr);
    while (*sStr)
    {
        *ptr++ = *sStr++;
    }
    *ptr = '\0';
    return fStr;
}

// Перевірка валідності
bool is_string_valid(char* str)
{
    bool hasString = false;
    bool hasColon = false;
    const size_t size = strlenn(str);

    for (size_t i = 0; i < size; i++)
    {
        if ((str[i] == ':' || str[i] == ';' || str[i] == ',') && i == 0)
            return false;

        if (str[i] == ':')
        {
            if (hasColon) return false;
            hasColon = true;
            continue;
        }

        if (hasColon)
        {
            if (str[i] == ',')
            {
                if (!isalpha((unsigned char)str[i - 1]) && str[i - 1] != ' ')
                    return false;
                hasString = true;
            }

            if (str[i] == ';')
            {
                if (!hasString || (!isalpha((unsigned char)str[i - 1]) && str[i - 1] != ' '))
                    return false;

                hasColon = false;
            }
        }
    }

    return true;
}

// Обробка рядка
char* process_string(char* str)
{
    const size_t length = strlenn(str);

    // +1 для '\0'
    char* result = (char*)calloc(length + 1, sizeof(char));
    result[0] = '\0';  // Ініціалізуємо пустий рядок

    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != ':')
        {
            char temp[2] = { str[i], '\0' };
            strcatt(result, temp);
            continue;
        }

        if (i + 1 >= length || str[i + 1] != ' ')
            return NULL;

        strcatt(result, ": ");

        const size_t maxWords = 100;
        char** arr = (char**)calloc(maxWords, sizeof(char*));

        for (size_t w = 0; w < maxWords; w++)
            arr[w] = (char*)calloc(STRING_MAX, sizeof(char));

        size_t wordCount = 0;

        // Зчитування слів
        for (size_t j = i + 2; j < length; j++)
        {
            if (str[j] == ',')
            {
                wordCount++;
                j++;
            }
            else if (str[j] == ';')
            {
                // Сортування
                quick_sort(arr, wordCount + 1);

                // Додавання у результат
                for (size_t k = 0; k <= wordCount; k++)
                {
                    strcatt(result, arr[k]);
                    if (k == wordCount)
                        strcatt(result, ";");
                    else
                        strcatt(result, ", ");
                }

                i = j;
                break;
            }
            else
            {
                char t[2] = { str[j], '\0' };
                strcatt(arr[wordCount], t);
            }
        }

        // Очищення
        for (size_t w = 0; w < maxWords; w++)
            free(arr[w]);
        free(arr);
    }

    return result;
}

#endif
