default:
	gcc -pthread server/tcpServer.c -pthread server/utility.c -pthread server/structures.c -o server/tcpServer;
	gcc -pthread client/tcpClients.c -pthread client/client_det.c -o client/tcpClients
	

tcpserver:
	g++ -pthread server/main.cpp -pthread server/utils.cpp  -o server/main;

tcpclient:
	gcc -pthread client/tcpClients.c -pthread client/client_det.c -o client/tcpClients

execserver:
	cd server && ./main
	
execclients:
	cd client && ./tcpClients