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
static void ft_send_msg(pid_t pid, char *msg);

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
	if (sig == SIGUSR1)
		ft_printf("%sACK signal received!%s\n", YEL, NC);
	else if (sig == SIGUSR2)
		ft_perror_exit("EOF signal received!\n");
}

static void ft_send_msg(pid_t pid, char *msg)
{

}
