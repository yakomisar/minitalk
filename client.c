#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        ft_putchar(str[i]);
        i++;
    }
}

int	ft_atoi(const char *str)
{
	char		*s;
	int			result;
	int			i;
	short int	sign;

	i = 0;
	sign = 1;
	result = 0;
	s = (char *)str;
	while (s[i] == '\t' || s[i] == '\r' || s[i] == '\n'
		   || s[i] == ' ' || s[i] == '\f' || s[i] == '\v')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{	
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

void	send_symbol(int pid, char s)
{
	int counter;

	counter = 128;
	while (counter >= 1)
	{
		if (s & counter)
		{
			kill(pid, SIGUSR1);
			usleep(100);
		}
		else
		{
			kill(pid, SIGUSR2);
			usleep(100);
		}
		counter /= 2;
	}
}

void	message_handler(int pid, char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		send_symbol(pid, c[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
    if (argc < 3)
        ft_putstr("Please use the following format: [PID] [messaage]\n");
    if (argc > 3)
        ft_putstr("Please ensure that your message has been placed in quotes \"message\"\n");
	message_handler(ft_atoi(argv[1]), argv[2]);
    return (0);
}
