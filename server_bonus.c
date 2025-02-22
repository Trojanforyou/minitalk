/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:53 by msokolov          #+#    #+#             */
/*   Updated: 2025/02/22 17:56:55 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>

static void	ft_get_pid(void)
{
	ft_printf("Server PID: %d\n", getpid());
}

static void	sig_handler(int sign, siginfo_t *info, void *context)
{
	static unsigned char	data = 0;
	static int				i = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (client_pid != info->si_pid)
		client_pid = info->si_pid;
	data = data << 1;
	if (sign == SIGUSR2)
		data = data | 1;
	if (++i == 8)
	{
		if (data == '\0')
		{
			write (1, "\n", 1);
			kill(client_pid, SIGUSR2);
		}
		else
			write (1, &data, 1);
		i = 0;
		data = 0;
	}
	kill(client_pid, SIGUSR1);

}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_get_pid();
	s_sigaction.sa_sigaction = sig_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
