/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:04:30 by passunca          #+#    #+#             */
/*   Updated: 2024/02/18 12:04:50 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int			ft_isstrnum(char *str);
static char	*ft_atob(char *str, int i, int j);
static void	ft_send_bits(int pid, char *bits);

int	main(int argc, char **argv)
{
	int		pid;
	char	*bits;

	if ((argc != 3) || !ft_isstrnum(argv[1]))
		return (ft_printf("%sUsage: ./server [PID] [message]%s\n", RED, NC));
	pid = ft_atoi(argv[1]);
	bits = ft_atob(argv[2], 0, 0);
	if (!bits)
		ft_perror("Error\n");
	ft_send_bits(pid, bits);
	free(bits);
	return (0);
}

int	ft_isstrnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

static char	*ft_atob(char *str, int i, int j)
{
	(void)str;
	(void)i;
	(void)j;
	return (NULL);
}

static void	ft_send_bits(int pid, char *bits)
{
	while (*bits)
	{
		if (*bits == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		++bits;
	}
	usleep(60);
}
