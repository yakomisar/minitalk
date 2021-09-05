/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:54:34 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/05 18:55:10 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	my_handler(int sign, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (sign == SIGUSR1)
	{
		ft_decrypt(1);
		kill(siginfo->si_pid, SIGUSR1);
	}
	if (sign == SIGUSR2)
	{
		ft_decrypt(0);
		kill(siginfo->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	pid_t				my_pid;
	struct sigaction	act;
	sigset_t			set;
	
	my_pid = getpid();
	ft_putstr("Please use the following pid-number: ");
	ft_putnbr(my_pid);
	ft_putstr(" in order to connect and send your message.\n");
	memset(&act, '\0', sizeof(act));
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act.sa_mask = set;
	act.sa_sigaction = &my_handler;
	//act.sa_sigaction = &my_handler;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	act.sa_flags = SA_SIGINFO;
	while (1)
	{
		// signal(SIGUSR1, my_handler);
		// signal(SIGUSR2, my_handler);
		pause();
	}
	return (0);
}
