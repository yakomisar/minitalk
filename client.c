/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:50:36 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/09 20:59:53 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	my_handler(int sig)
{
	static int	received = 0;
	
	if (sig == SIGUSR1)
		received++;
	if (sig == SIGUSR2)
	{
		ft_putnbr(received);
		ft_putstr("\nTransfer successful!!");
		exit(0);
	}
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	message_handler(int pid, char *c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 128;
	ft_putstr("Send: ");
	ft_putnbr(ft_strlen(c));
	ft_putstr("\nReceived: ");
	while (c[i] != '\0')
	{
		while (counter >= 1)
		{
			if (c[i] & counter)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(70);
			counter /= 2;
		}
		counter = 128;
		i++;
	}
	i = 8;
	while (i)
	{
		kill(pid, SIGUSR2);
		usleep(60);
		i--;
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	if (argc != 3 || !is_numeric(argv[1]))
	{
		ft_putstr("Please use the following: [PID] [messaage]\n");
		return (1);
	}
	act.sa_handler = my_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	message_handler(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
