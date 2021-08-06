#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	ft_convert(char *str)
{
	int	i;

	i = 0;
}

void	my_handler(int signum)
{
	static char	msg[8];
	static int	byte;

	byte = 0;
	while (byte < 8)
	{
		if (signum == SIGUSR1)
		{
			msg[byte] = '1';
		}
		if (signum == SIGUSR2)
		{
			msg[byte] = '0';
		}
		byte++;
	}
	if (byte == 8)
	{
		msg[byte] = '\0';
		ft_convert(msg);
		byte = 0;
	}
	
}

int	main(void)
{
	int my_pid;

	my_pid = getpid();
	printf("Please use the following pid-number: %d in order to connect to the server.", my_pid);
	while (1)
	{
		signal(SIGUSR1, my_handler);
		signal(SIGUSR2, my_handler);
	}
	return (0);
}