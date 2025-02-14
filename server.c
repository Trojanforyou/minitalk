/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:17:09 by msokolov          #+#    #+#             */
/*   Updated: 2025/02/14 18:17:16 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	void ft_get_pid(void)
{
	ft_printf("pid: %d\n", getpid());
}
static	void sig_handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char data = 0;
	static int	count = 0;
	static __pid_t	client_pid;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (signo == SIGUSR2)
		data|= 1;
	if (++count == 8)
	{
		count = 0;
		if (data == 0)
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		ft_printf("%c", data);
		data = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		data <<= 1;
}
int main (void)
{
	struct sigaction	s_sigaction;
	ft_get_pid();
	s_sigaction.sa_sigaction = sig_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while(1)
		pause();
	return 0;
}
