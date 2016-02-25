/**
 *     Filename: leet_8_string_to_integer_atoi.c
 *  Description: 8. String to Integer (atoi)
 *      Version: 1.0
 *      Created: 15:51:19 02-25-2016
 *     Revision: none
 *     Compiler: gcc
 *       Author: Danny Jiang
 */

#include "leet_header.h"
#include "leet_8_string_to_integer_atoi.h"
#include <string.h>
#include <limits.h>

/**
 * @brief validate if the string is leagal to represent an integer.
 *
 * @param str
 *
 * @return 0, no leading sign;
 *         1, with leading sign;
 *         -1, invalidate string.
 */
static int valid_string(char* str)
{
    int i;
    int sz;
    int sign = 0;

    sz = strlen(str);
    if(str[0] == '-')
    {
        sign = 1;
    }
    else if(str[0] == '+')
    {
        sign = 1;
    }
    for (i = sign; i < sz; i++)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            return -1;
        }
    }
    return sign;
}

static void preprocess_str(char* s, char* t)
{
    int leading_number = 0;
    while(*s != 0)
    {
        if(*s == '+' || *s == '-')
        {
            *t = *s;
            s++;
            t++;
            continue;
        }
        while(*s == ' ')
        {
            s++;
        }
        while(leading_number == 0)
        {
            if(*s == '0')
            {
                s++;
            }
            else
            {
                leading_number = 1;
            }
        }
        *t = *s;
        s++;
        t++;
    }
}
int myAtoi(char* str)
{
    int neg;
    int sign;
    int adder;
    int sz;
    int ret = 0;
    int i;
    char* copy_str;

    sz = strlen(str);
    copy_str = (char*)malloc(sizeof(char) * sz);
    memset(copy_str, 0, sizeof(char) * sz);
    preprocess_str(str, copy_str);

    sign = valid_string(copy_str);
    if(sign == -1)
    {
        return 0;
    }
    if(copy_str[0] == '-')
    {
        neg = 1;
    }

    sz = strlen(copy_str);
    for (i = sign; i < sz; i++)
    {
        if((ret * 10) < ret)
        {
            return (neg == 1) ? INT_MIN : INT_MAX;
        }
        adder = copy_str[i] - '0';
        ret = ret * 10 + adder;
        if(ret < 0)
        {
            if(adder >= 8 && neg == 1)
            {
                return INT_MIN; 
            }
            else if(adder == 7 && neg == 0)
            {
                return INT_MAX;
            }
            else
            {
                return (neg == 1) ? INT_MIN : INT_MAX;
            }
        }
    }
    return (neg == 1)? (0 - ret) : ret;
}

static void test1(void)
{
    printf("%d\n", 0x7fffffff);
    printf("%d\n", 0x80000000);
}

static void test2(void)
{
    char a[] = "     010";
    char b[10] = {0};

    preprocess_str(a, b);
    printf("[%s], [%s]\n", a, b);
    printf("%d\n", myAtoi(a));
    printf("%d\n", myAtoi(b));
}
static void test3(void)
{
    char a[] = "1000";

    printf("%d\n", myAtoi(a));
}
static void test4(void)
{
    char a[] = "    -12a48";

    printf("%d\n", myAtoi(a));
    printf("%d\n", atoi(a));
}
int leet_8_string_to_integer_atoi_test(void)
{
    printf("%s\n", __FILE__);
    test1();
    test2();
    test3();
    test4();
    return 0;
}

