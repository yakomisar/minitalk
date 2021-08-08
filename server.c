#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// void	ft_putstr(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		write(1, &str[i], 1);
// 		i++;
// 	}
// }

// void	ft_putnbr(int n)
// {
// 	if (n < 0)
// 	{
// 		n = n * -1;
// 		ft_putchar('-');
// 	}
// 	if (n < 10)
// 	{
// 		ft_putchar(n + '0');
// 		return ;
// 	}
// 	ft_putnbr(n / 10);
// 	ft_putchar((n % 10) + '0');
// 	return ;
// }

// int	ft_convert(char *str)
// {
// 	int		i;
// 	int		result;
// 	char	msg;

// 	i = 0;
// 	result = 0;
// 	printf("I am here");
// 	while (str[i] != '\0')
// 	{
// 		result = result * 2 + (msg - '0');
// 	}
// 	return (result);
// }

// void	my_handler(int signum)
// {
// 	static char	msg[9];
// 	static int	i;
// 	int			result;
	
// 	if (i < 8)
// 	{
// 		if (signum == SIGUSR1)
// 		{
// 			msg[i] = '1';
// 		}
// 		if (signum == SIGUSR2)
// 		{
// 			msg[i] = '0';
// 		}
// 		i++;
// 	}
// 	if (i > 7)
// 	{
// 		msg[i] = '\0';
// 		i = 0;
// 		//result = ft_convert(msg);
// 		printf("Result\n");
// 	}
// }

void	ft_decrypt(int val)
{
	static int	i;
	static char	c;

	i++;
	c = c << 1;
	c = c | (c | val);
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

void	my_handler(int sign)
{
	if (sign == SIGUSR1)
		ft_decrypt(1);
	if (sign == SIGUSR2)
		ft_decrypt(0);
}

int	main(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("Please use the following pid-number: %d in order to connect to the server.\n", my_pid);
	while (1)
	{
		signal(SIGUSR1, my_handler);
		signal(SIGUSR2, my_handler);
		pause();
	}
	return (0);
}