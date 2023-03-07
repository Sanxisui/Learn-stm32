# TAR = client
# OBJ =  client.o
# TAR = server_socket_pthread
# OBJ =  server_socket_pthread.o
# TAR = client_udp
# OBJ =  client_udp.o
# TAR = srever_udp
# OBJ =  srever_udp.o
CC := gcc
RMRF := rm 
$(TAR):$(OBJ)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $^ -o $@
.PHONY:
 clean: 
	$(RMRF)  *.o 


# TAR = test
# OBJ = 214text1.o
# CC := gcc
# RMRF := rm 

