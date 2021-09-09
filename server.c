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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_sigaction(int sig, siginfo_t *siginfo, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)context;
	// c |= (sig == SIGUSR2);
	c = c | (c | sig);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(siginfo->si_pid, SIGUSR2);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(siginfo->si_pid, SIGUSR1);
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
