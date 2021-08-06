#include <stdio.h>
#include <unistd.h>
#include <signal.h>

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

void	send_data(int pid, char c)
{
	int counter;

	counter = 128;
	while (counter >= 1)
	{
		if (c & counter)
		{
			//printf("%d", 1);
			kill(pid, SIGUSR1);
		}
		else
		{
			//printf("%d", 0);
			kill(pid, SIGUSR2);
		}
		counter /= 2;
	}
	
}

void	message_handler(int pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		//send_data(pid, msg[i]);
		send_data(pid, msg[i]);
		i++;
	}
	//send_data(pid, msg[i]);
	send_data(pid, msg[i]);
}

int main(int argc, char **argv)
{
    if (argc < 3)
        printf ("Please use the following format: [PID] [messaage]\n");
    if (argc > 3)
        printf("Please ensure that your message has been placed in quotes \"message\"\n");
    //printf("argc1 : %s ", argv[1]);
    //signal(SIGUSR1, my_handler);
    //kill(getpid(), SIGUSR1);
    //kill(ft_atoi(argv[1]), SIGUSR1);
	message_handler(ft_atoi(argv[1]), argv[2]);
    return (0);
}
