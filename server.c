#include "minitalk.h"

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
	ft_putstr("Please use the following pid-number: ");
	ft_putnbr(my_pid);
	ft_putstr(" in order to connect to the server.\n");
	while (1)
	{
		signal(SIGUSR1, my_handler);
		signal(SIGUSR2, my_handler);
		pause();
	}
	return (0);
}