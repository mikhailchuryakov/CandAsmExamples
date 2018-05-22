#include <stdio.h>

int check(char *s)
{
    int i;
    char sign;
    for (i = 0; s[i]; i++); //strlen(buf)
    if (i)
        i--;
    if (i == 0 && s[i] >= 'A' && s[i] <= 'Z')
        return 1;
    if (s[i] >= 'A' && s[i] <= 'Z')
    {
        sign = s[i];
        for (i-- ; i >= 0; i--)
            if (s[i] == sign)
                return 0;
        return 1;
    }
    return 0;
}

void rule1(char *s)
{
    int i;
    for (i = 0; s[i]; i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 'a' - 'A';
}

void rule2(char *s)
{
    int i, j;
    for (i = 0; s[i]; i++)
        if (s[i] >= '0' && s[i] <= '9')
            for (j = i; j > 0; j--)
                if (s[j - 1] > '9' || s[j - 1] < '0')
                {
                    char t;
                    t = s[j];
                    s[j] = s[j - 1];
                    s[j - 1] = t;
                }
                else
                    break;
}

const char *test(int i)
{
    switch (i)
    {
    case 1:
        return "qwe123rtY";
    case 2:
        return "QWE011rty";
    case 3:
        return "ABqwe911-0YZ";
    default:
        return "";
    }
}

int main()
{
    char s[102];
    int n;
    fgets(s, sizeof s, stdin);
    for (n = 0; s[n]; n++); //n = strlen(s);
    while (n > 0 && (s[n-1] == '\r' || s[n-1] == '\n'))
        s[--n] = '\0';
    puts(s);
    if (check(s))
        rule1(s);
    else
        rule2(s);
    puts(s);
    return 0;
}
