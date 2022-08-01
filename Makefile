default:
	gcc -pthread server/tcpServer.c -pthread server/utility.c -o server/tcpServer;
	gcc -pthread client/tcpClients.c -pthread client/client_det.c -o client/tcpClients
	

tcpserver:
	gcc -pthread server/tcpServer.c -pthread server/utility.c -pthread server/structures.c -o server/tcpServer;

tcpclient:
	gcc -pthread client/tcpClients.c -pthread client/client_det.c -o client/tcpClients

execserver:
	cd server && ./tcpServer
	
execclients:
	cd client && ./tcpClients