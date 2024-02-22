/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:05:05 by passunca          #+#    #+#             */
/*   Updated: 2024/02/18 12:05:10 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_sighandler(int sig, siginfo_t *info, void *context);
static void	ft_set_sigaction(struct sigaction *sa);
static void	ft_strlen_received(t_protocol *server);
static void	ft_msg_received(t_protocol *server, int *i, pid_t pid);
static void	ft_send_bit(pid_t pid, char bit, char pause_flag);

/*	Prints the server PID;
 *	Handles SIGUSR1 and SIGUSR2 changing the default behaviour of their signal
 *	handlers to receive and message bit by bit and print it to stdout;
 *		SIGUSR1: when received sends
 *		This is achieved by using the sigaction() function;
 *	*/
int	main(void)
{
	struct sigaction	sa;
	// sigset_t			block_mask;
	pid_t				pid;

	pid = getpid();
	sigemptyset(&sa.sa_mask);
    // sigaddset(&sa.sa_mask, SIGUSR1);
    // sigaddset(&sa.sa_mask, SIGUSR2);
	// sigemptyset(&block_mask);
 //    sigaddset(&block_mask, SIGUSR1);
 //    sigaddset(&block_mask, SIGUSR2);
	sa.sa_sigaction = ft_sighandler;
    // sa.sa_mask = block_mask;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	// sigaction(SIGUSR1, &sa, NULL);
	// sigaction(SIGUSR2, &sa, NULL);
	ft_set_sigaction(&sa);
	ft_sep_color('0', '=', 20, GRN);
	ft_printf("Server PID: %s%d%s\n", YEL, pid, NC);
	ft_sep_color('0', '=', 20, GRN);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

void	ft_set_sigaction(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
		ft_perror_exit("sigaction() failed to handle SIGUSR1");
	if (sigaction(SIGUSR2, sa, NULL) < 0)
		ft_perror_exit("sigaction() failed to handle SIGUSR2");
}

/*	Bits to character
 *	Receives a character bit by bit and the prints it to stdout
 *	*/
static void	ft_sighandler(int sig, siginfo_t *info, void *context)
{
	static t_protocol	server;
	static int			i;

	(void)context;
	if (!server.bits)
		server.data = 0;
	if ((sig == SIGUSR2) && !server.received)
		server.data |= (((sizeof(int) * 8) - 1) - server.bits);
	else if ((sig == SIGUSR2) && server.received)
		server.data |= (((sizeof(char) * 8) - 1) - server.bits);
	++server.bits;
	ft_strlen_received(&server);
	ft_msg_received(&server, &i, info->si_pid);
	ft_send_bit(info->si_pid, 0, 0);
}

static void	ft_strlen_received(t_protocol *server)
{
	if ((server->bits == (sizeof(int) * 8)) && !server->received)
	{
		server->received = 1;
		ft_printf("%sMessage of len %d received!%s\n", GRN, server->data, NC);
		server->msg = ft_calloc((server->data + 1), sizeof(char));
		if (!server->msg)
			ft_perror_exit("ft_calloc() failed\n");
		server->msg[server->data] = '\0';
		server->bits = 0;
	}
}

static void	ft_msg_received(t_protocol *server, int *i, pid_t pid)
{
	if ((server->bits == 8) && server->received)
	{
		server->msg[*i] = server->data;
		++(*i);
		if (server->data == '\0')
		{
			ft_printf("[%sMessage received!%s]\n", MAG, NC);
			ft_printf("%s%s%s\n", GRN, server->msg, NC);
			free(server->msg);
			server->msg = NULL;
			server->received = 0;
			*i = 0;
			ft_send_bit(pid, 1, 0);
		}
		server->bits = 0;
	}
}

static void	ft_send_bit(pid_t pid, char bit, char pause_flag)
{
	(void)pause_flag;
	if (!bit)
	{
		if (kill(pid, SIGUSR1) < 0)
			ft_perror_exit("kill() failed sending SIGUSR1\n");
	}
	else if (bit)
		if (kill(pid, SIGUSR2) < 0)
			ft_perror_exit("kill() failed sending SIGUSR2\n");
	if (pause_flag)
		pause();
}
