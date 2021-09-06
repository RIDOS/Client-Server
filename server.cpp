#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>

char message1[] = "123456789\n"; // Сообщение сервера.
unsigned int sz; // Переменная целово типа, которая будет принимать размер принемаемого адреса. 

int main() {
	int sock, listener; // Переменные сокета.
	struct sockaddr_in addr; // Структура сокета (IP, порт и внутрений адресс).
	char buf[1024]; // Буфер обмена. В него передается 
	int bytes_read, bytes_read1; // Первая переменная - длина буфера с записынами данными от клиента, вторая переменная - длина буфера с записынами данными от сервера.
	listener = socket(AF_INET, SOCK_STREAM, 0); // Создаем новый сокет. В скобках аргументы 1 - для сетевого протокола IPv4, 2 - потоковый сокет, 3 - протокол.
	if (listener < 0) { // Проверяем созданный сокет на ошибки.
		perror("socket");
		exit(1);
	}
	
	addr.sin_family = AF_INET; // Записываем в структуру Internet-домен.
	addr.sin_port = htons(3425); // Записываем в структуру порт.(Host TO Network Short)
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // Записываем в структуру адресс внутренней петли.
	
	if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) { // Присваиваем сокету имя и проверяем сам сокет на работоспособность. 
		perror("bind");
		exit(2);
	}
	
	listen(listener, 1); // Ожидание запроса от сокета.
	
	while (1) { // Бесконечный цикл, для того чтобы сервер не выключался и ждал ответ от клиента.
		sz = sizeof(addr); // Записываем размер адреса.
		sock = accept(listener, (struct sockaddr *) &addr, &sz); // Принимаем связь с сокета.
		write(1, message1, sock); // Записываем в сокет сообщение.
		printf("\n"); // 
		if (sock < 0) { // Проверяем сокет на работоспособность.
			perror("accept");
			exit(3);
		}
		
		while(1) { // Так же - бесконечный цикл.
			bytes_read = recv(sock, buf, 1024, 0); // 
			send(sock, buf, bytes_read, 0);
			/*
			 * Первый аргумент - сокет-дескриптор, в который записываются данные. 
			 * Второй и третий аргументы - соответственно, адрес и длина буфера с записываемыми данными. 
			 * Четвертый параметр - это комбинация битовых флагов, управляющих режимами записи.
			 *
			*/
			
			if (bytes_read <= 0) break; // Если длина буфера равна нулю или меньше (т.е. буфер пуст), то выходим из цикла.
			
			sz = sizeof(addr); // Записываем новый размер адреса. 
			sock = accept(listener, (struct sockaddr *) &addr, &sz); // Принимаем связь с сокета.
			
			write(1, message1, sock); // Записываем в сокет сообщение.
			if (sock < 0) // Проверям сокет на работоспособность.
			{
				perror("accept");
				exit(3);
			}
			
			bytes_read1 = recv(sock, message1, 1024, 0); // В переменную  bytes_read1 - записывается данные из сокета.
			
			if (bytes_read1 <= 0) break; // Если сокет пуст, то выходим из цикла.
			send(sock, message1, bytes_read1, 0); // Записывает данные в сокет.
		}
		close(sock); // Обрываем подключение (Закрываем сокет).
	}
	
	return 0;
}

// Create by RIDOS //
