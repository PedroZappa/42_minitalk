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

static void	ft_client_sighandler(int sig, siginfo_t *info, void *context);
static void	ft_send_msg(pid_t pid, char *msg);
static void	ft_send_int(pid_t pid, int num);
static void	ft_send_char(pid_t pid, char c);

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = ft_atoi(argv[1]);
	if (argc != 3)
		ft_perror_exit("Usage: ./client [PID] [message]\n");
	else if (kill(pid, 0) < 0)
		ft_perror_exit("PID does not exist\n");
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = ft_client_sighandler;
	sa.sa_flags = SA_RESTART;
	ft_set_sigaction(&sa);
	ft_sep_color('0', '=', 20, GRN);
	ft_printf("%sClinet PID: %d%s\n", YEL, pid, NC);
	ft_sep_color('0', '=', 20, GRN);
	ft_send_msg(pid, argv[2]);
	return (EXIT_SUCCESS);
}

static void	ft_client_sighandler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
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
	msglen = ft_strlen(msg);
	ft_printf("%sSending msg's length = %d%s\n", YEL, msglen, NC);
	ft_send_int(pid, msglen);
	ft_printf("%sSending msg%s\n", GRN, msglen, NC);
	while (msg[i])
		ft_send_char(pid, msg[i++]);
	ft_printf("%sSending NULL Terminator\n", MAG, NC);
	ft_send_char(pid, '\0');
}


static void	ft_send_int(pid_t pid, int num)
{
	int		bitshift;
	char	bit;

	bitshift = ((sizeof(int) * 8) - 1);
	while (bitshift >= 0)
	{
		bit = (num >> bitshift) & 1;
		ft_send_bit(pid, bit, 1);
		--bitshift;
	}
}

static void		ft_send_char(pid_t pid, char c)
{
	int		bitshift;
	char	bit;

	bitshift = ((sizeof(int) * 8) - 1);
	while (bitshift >= 0)
	{
		bit = (c >> bitshift) & 1;
		ft_send_bit(pid, bit, 1);
		--bitshift;
	}
}
