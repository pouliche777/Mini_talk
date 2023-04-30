/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:11:47 by slord             #+#    #+#             */
/*   Updated: 2022/08/31 12:04:37 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

void	send_message(char *message, int pid)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		while (j < 8)
		{
			if ((message[i] & 128 >> j) != 0)
			{
				if (kill(pid, SIGUSR2) == -1)
					error("mauvais PID");
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					error("mauvais PID");
			}
			j++;
			usleep(200);
		}
		j = 0;
		i++;
	}
}

void	signal_reception(int signum, siginfo_t *info, void *context)
{
	static int	c_received;

	(void)*info;
	(void)*context;
	if (signum == SIGUSR1)
		c_received++;
	if (signum == SIGUSR2)
	{
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;
	sigset_t			block_mask;

	if (argc != 3)
	{
		ft_putstr_fd("error, wrong number of arguments", 2);
		exit(0);
	}
	if (ft_str_isdigit(argv[1]) == 0 || argv[1][0] == '\0')
	{
		ft_putstr_fd("error, pid is invalid", 2);
		exit(0);
	}
	sa.sa_sigaction = &signal_reception;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&block_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = ft_atoi(argv[1]);
	send_message(argv[2], pid);
	while (1)
		pause();
}
