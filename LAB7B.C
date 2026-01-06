#include <stdio.h>
#include <stdbool.h>

int rs[100], count = 0;

struct max
{
    int f[10];
    bool lu[10];
} s;

struct min
{
    int buf[10];
    int mat[10];
} nat;

bool dataavi(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (rs[count] == s.f[i])
            return 1;
    }
    return 0;
}

int check(int n, int m)
{
    int i, j = 0;

    for (j = 0; j < n; j++)
    {
        int x = 0;
        for (i = count + 1; i < m; i++)
        {
            if (s.f[j] == rs[i])
            {
                nat.buf[j] = i;
                nat.mat[j] = j;
                i = m + 1;
                x = 1;
            }
        }
        if (x == 0 && s.lu[j] == 0)
            return j;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (nat.buf[j] < nat.buf[j + 1])
            {
                int temp = nat.buf[j];
                nat.buf[j] = nat.buf[j + 1];
                nat.buf[j + 1] = temp;

                temp = nat.mat[j];
                nat.mat[j] = nat.mat[j + 1];
                nat.mat[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (s.lu[nat.mat[i]] == 0)
        {
            return nat.mat[i];
        }
    }
}

void lru(int n, int m)
{
    int fs = 0, i = 0, in = 0, kom = 0;

    for (i = 0; i < n; i++)
        s.lu[i] = false;

    s.lu[n - 1] = true;

    while (count < m)
    {
        if (in < n)
        {
            if (dataavi(n) && in > 0)
            {
                count++;
                kom = 0;
            }
            else
            {
                s.f[in++] = rs[count];
                kom = 1;
                fs++;
                count++;
            }
        }
        else
        {
            if (dataavi(n))
            {
                count++;
                kom = 0;
            }
            else
            {
                int j = check(n, m);
                s.f[j] = rs[count++];
                fs++;
                kom = 1;

                for (i = 0; i < n; i++)
                    s.lu[i] = false;

                s.lu[j] = true;
            }
        }

        if (kom == 1)
            printf(" Page Fault :");
        else
            printf(" :");

        for (i = 0; i < n; i++)
            printf(" %d", s.f[i]);

        printf("\n");
    }

    printf("\n\npage faults =%d", fs);
}

int main()
{
    int n, m, i;

    printf("ENTER THE NO OF FRAME AND REFERENCE STREAM\n");
    scanf("%d%d", &n, &m);

    printf("ENTER THE REFERENCE STREAM \n");
    for (i = 0; i < m; i++)
        scanf("%d", &rs[i]);

    lru(n, m);

    return 0;
}
