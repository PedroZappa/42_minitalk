define rfr
	refresh
end

### Debug Client
define main
	display argc
	display sa
	display pid
end

define ft_client_sighandler
	display sig
	display info
	display context
end

define ft_set_sigaction
	display sa
end

define ft_send_msg
	display pid
	display msg
	display msglen
	display i
end

define ft_send_int
	display pid
	display num
	display bitshift
	display bit
end

define ft_send_bit
	display pid
	display bit
	display pause_flag
end

### Start client DBG @ main
# fs cmd
# break main
# run 1841034 "Z!"
# main

### Start client DBG @ ft_send_msg
fs cmd
break ft_send_msg
run 2301623 "Z!"
ft_send_msg
