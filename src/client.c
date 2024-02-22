/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:04:30 by passunca          #+#    #+#             */
/*   Updated: 2024/02/22 16:15:14 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_client_sighandler(int sig);
static void	ft_send_msg(pid_t pid, char *msg);

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				*msg;

	if (argc != 3)
		ft_perror_exit("Usage: ./client [PID] [message]\n");
	else if (kill(ft_atoi(argv[1]), 0) < 0)
		ft_perror_exit("PID does not exist\n");
	msg = argv[2];
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_client_sighandler;
	sa.sa_flags = SA_RESTART;
	ft_set_sigaction(&sa);
	ft_sep_color('0', '=', 20, GRN);
	ft_printf("%sClient PID: %d%s\n", YEL, ft_atoi(argv[1]), NC);
	ft_sep_color('0', '=', 20, GRN);
	ft_send_msg(ft_atoi(argv[1]), msg);
	return (EXIT_SUCCESS);
}

static void	ft_client_sighandler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("%sACK signal received!%s\n", YEL, NC);
	else if (sig == SIGUSR2)
		ft_perror_exit("EOF signal received!\n");
}

static void ft_send_msg(pid_t pid, char *msg)
{
	int		i;
	int		msglen;

	i = 0;
	{
		msglen = ft_strlen(msg);
		ft_printf("%sOutbound msg's length = %d%s\n", YEL, msglen, NC);
		ft_send_int(pid, msglen);
		ft_printf("%sSending msg%s\n", GRN, msglen, NC);
		while (msg[i] != '\0')
			ft_send_char(pid, msg[i++]);
		ft_printf("%sSending NULL Terminator\n", MAG, NC);
		ft_send_char(pid, '\0');
	}
}
