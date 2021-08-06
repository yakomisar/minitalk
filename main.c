#include <stdio.h>


void ft_change(char *c)
{
    c[0] = 'A';
    //printf("%s", x);
}

int main(void)
{
    char msg[3] = {'H', 'E', '\0'};

    printf("%s\n", msg);

    ft_change(msg);

    printf("%s", msg);
}