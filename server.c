#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// void	ft_convert(char *str)
// {
// 	int		i;
// 	int		result;
// 	char	msg;

// 	i = 0;
// 	result = 0;
// 	while (str[i] != '\0')
// 	{
// 		result = result * 2 + (msg - '0');
// 	}
// 	printf("Result: %d\n", result);	
// }

// void	my_handler(int signum)
// {
// 	static char	msg[8];
// 	static int	byte;

// 	//byte = 0;
// 	while (byte < 8)
// 	{
// 		if (signum == SIGUSR1)
// 		{
// 			msg[byte] = '1';
// 		}
// 		if (signum == SIGUSR2)
// 		{
// 			msg[byte] = '0';
// 		}
// 		byte++;
// 	}
// 	if (byte == 8)
// 	{
// 		msg[byte] = '\0';
// 		ft_convert(msg);
// 		byte = 0;
// 	}
// }

// void	my_handler(int signum)
// {
// 	static char	msg[9];
// 	static int	bty;
// 	int			i;

// 	printf("%d ", bty);
// 	if (bty < 8)
// 	{
// 		if (signum == SIGUSR1)
// 		{
// 			msg[bty] = '1';
// 			printf("dmmdv;v 1");
// 			bty++;
// 			//usleep(50);
// 		}
// 		if (signum == SIGUSR2)
// 		{
// 			msg[bty] = '0';
// 			printf("afafwefwekn0");
// 			bty++;
// 			//usleep(50);
// 		}
// 	}
// }

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	my_handler(int signum)
{
	static char	msg[9];
	static int	i;
	
	if (i < 8)
	{
		//printf("%d - ", i);
		
		if (signum == SIGUSR1)
		{
			//printf("Catch SIGUSR1\n");
			msg[i] = '1';
			ft_putchar(msg[i]);
			usleep(50);
		}
		if (signum == SIGUSR2)
		{
			//printf("Catch SIGUSR2\n");
			msg[i] = '0';
			ft_putchar(msg[i]);
			usleep(50);
		}	
		i++;
	}
	if (i > 7)
	{
		i = 0;
	}
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