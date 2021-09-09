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

// static void	ft_sigaction(int sig, siginfo_t *siginfo, void *context)
// {
// 	static int				i;
// 	static unsigned char	c;

// 	(void)context;
// 	i = 0;
// 	c = 0;
// 	if (sig == SIGUSR1)
// 	{
// 		//write(1, "1", 1);
// 		kill(siginfo->si_pid, SIGUSR1);
// 	}
// 	if (sig == SIGUSR2)
// 	{
// 		//write(1, "0", 1);
// 		kill(siginfo->si_pid, SIGUSR1);
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

static void	ft_sigaction(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	
	if (sig == SIGUSR1)
	{
		ft_decrypt(1);
		kill(siginfo->si_pid, SIGUSR1);
		usleep(10);
	}
	if (sig == SIGUSR2)
	{
		ft_decrypt(0);
		kill(siginfo->si_pid, SIGUSR2);
		usleep(10);
	}
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
