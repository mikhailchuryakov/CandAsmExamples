#include <stdio.h>
#include <time.h>

#define START_CHAR ' '
#define STOP_CHAR '~'

int sort (char* buf, int count, int index)
{
    char in;
    for (in = START_CHAR; in <= STOP_CHAR; in++)
    {
        buf[index] = in;
        if (index != count - 1)
        {
            if (sort (buf, count, index + 1))
                return 1;
        }
        else if (check(buf))
            return 1;
    }
    return 0;
}

int bruteforce(char *buf, unsigned n)
{
    int i;
    n--;
    for (i = n; i >= 0; i--)
        buf[i] = '\0';
    if (check(buf))
        return 1;
    for (i = 1; i <= n; i++)
        if (sort(buf, i, 0))
            return 1;
    return 0;
}

int main()
{
	char buf[20];
	unsigned t0, t1;
	t0 = (unsigned)time(NULL);
	if (bruteforce(buf, sizeof buf))
		puts(buf);
    t1 = (unsigned)time(NULL);
    printf("%u\n", t1 - t0);
	return 0;
}
