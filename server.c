/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:28:07 by slord             #+#    #+#             */
/*   Updated: 2022/08/31 13:10:49 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	handler_sigusr(int signalnb, siginfo_t *info, void *test)
{
	static t_message	mess = {{0}, 0};	

	(void)test;
	if (signalnb == SIGUSR1)
		mess.binary[mess.i] = '0';
	else
		mess.binary[mess.i] = '1';
	mess.i++;
	if (mess.i == 8)
	{
		ft_binary_to_char(&mess, info);
		ft_bzero(mess.binary, 9);
		mess.i = 0;
		ft_putstr_fd(mess.binary, 1);
	}
}

void	ft_binary_to_char(t_message *mess, siginfo_t *info)
{	
	int					i;
	int					nb;
	static pid_t		client_pid = 0;

	if (info->si_pid)
		client_pid = info->si_pid;
	i = 0;
	nb = 0;
	mess->binary[8] = '\0';
	while (mess->binary[i])
	{
		nb = nb * 2 + mess->binary[i] - 48;
		i++;
	}
	if ((char)nb == '\0')
	{
		kill(client_pid, SIGUSR2);
		client_pid = 0;
		return ;
	}
	ft_putchar_fd(nb, 1);
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa_signal;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_sigaction = handler_sigusr;
	pid = getpid();
	printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	while (1)
		pause();
}
