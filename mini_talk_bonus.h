/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_talk_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:19:21 by slord             #+#    #+#             */
/*   Updated: 2022/08/31 12:01:33 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_BONUS_H
# define MINI_TALK_BONUS_H

# include <sys/types.h>
# include <signal.h>
# include "libft/libft.h"
# include <stdio.h>

typedef struct s_message
{
	char	binary[9];
	int		i;
}	t_message;

void	ft_binary_to_char(t_message *mess, siginfo_t *info);
#endif
