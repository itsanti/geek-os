#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[2048];
    int bytes_read;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        perror("bind");
        exit(2);
    }
    printf("Начинаем слушать \n");
    listen(listener, 1);
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
	if (!fork())
		{
		close(listener);
		send(sock, "Echo server. Hello\n",19,0);
      		while(1)
      		 {
		  printf("Ожидаем сообщение...\n");	
           	 bytes_read = recv(sock, buf, 2048, 0); 
            	 if(bytes_read <= 0) break;
            	 printf("Получено %d bytes\tСообщение: %s\n", bytes_read, buf);
            	 printf("Отправляю принятое сообщение клиенту\n");
            	 send(sock, buf, bytes_read, 0);
        	 }
    
        	close(sock); 
        	exit(0);
		}
    }  
    return 0;
}
