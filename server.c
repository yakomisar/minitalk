/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:54:34 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/09 21:06:17 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_sigaction(int sig, siginfo_t *siginfo, void *context)
{
	static char c = 0;
	static int	i = 0;

	(void)context;
	i++;
	if (sig == SIGUSR1)
		c |= (c | 1);
	else
		c |= (c | 0);
	if (i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(siginfo->si_pid, SIGUSR2);
			return ;
		}
		write(1, &c, 1);
		kill(siginfo->si_pid, SIGUSR1);
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	pid_t				my_pid;
	struct sigaction	act;
	
	my_pid = getpid();
	ft_putstr("Please use the following pid-number: ");
	ft_putnbr(my_pid);
	ft_putstr(" in order to connect and send your message.\n");
	act.sa_sigaction = ft_sigaction;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		pause();
	return (0);
}
