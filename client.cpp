#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>

char message[] = "Hello there!\n"; // Сообщение пользователя.
char buf1[sizeof(message)]; // Буфер куда попадает сообщение от пользователя.
int fs, fr; // Переменные, в которые будут записываться результаты вызванных методов send и recv.

int main() {
	int sock; // Переменная сокета.
	struct sockaddr_in addr; // Структура адреса клиента и сервера.
	sock = socket(AF_INET, SOCK_STREAM, 0); // Вызываем функцию socket для получения информации о домене и типе сокета.
	
	if (sock < 0) { // Проверка на ошибки. (При 0 - ошибка)
		perror("socket");
		exit(1);
	}
	
	addr.sin_family = AF_INET; // Записываем в структуру Internet-домен.
	addr.sin_port = htons(3425); // Записываем в структуру порт.(Host TO Network Short)
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Записываем в структуру адресс внутренней петли.
	
	if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) { // Пытаемся соединится с сервером. При ошибке выводим ошибку, иначе идем далее.
		perror("connect");
		exit(2);
	}
	
	fs = send(sock, message, sizeof(message), 0); // 
	fr = recv(sock, buf1, sizeof(message), 0); // 
	
	printf("B\n"); // Выводим переменную B и переходим на новую строку.
	printf("\n %s\n\n\n",buf1); // ***Здесь была ошибка. [format not a string literal and no format arguments]. Исправил с помощью %s - строка символов.
	close(sock); // Закрываем подключение.
	
	return 0; // Метод Main выводит 0.
}

// Created by RIDOS 
	
