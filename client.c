/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:50:36 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/05 19:24:54 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	my_handler()
{
	return ;
}

void	send_symbol(int pid, char s)
{
	int	counter;

	struct sigaction	act;
	sigset_t			set;
	
	memset(&act, '\0', sizeof(act));
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	act.sa_mask = set;
	act.sa_sigaction = &my_handler;
	sigaction(SIGUSR1, &act, 0);
	
	counter = 128;
	while (counter >= 1)
	{
		if (s & counter)
		{
			kill(pid, SIGUSR1);
			usleep(60);
		}
		else
		{
			kill(pid, SIGUSR2);
			usleep(60);
		}
		counter /= 2;
		sigsuspend(&set);
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
	ft_putstr("Message has been sent.");
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		ft_putstr("Please use the following format: [PID] [messaage]\n");
	if (argc > 3)
	{
		ft_putstr("Please ensure that your message has been placed in quotes");
		ft_putstr("\"message\"\n");
	}
	if (argc == 3)
		message_handler(ft_atoi(argv[1]), argv[2]);
	return (0);
}
