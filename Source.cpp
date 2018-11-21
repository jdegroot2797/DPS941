#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

//BB-UART Serial Information
#define PORT "/dev/ttyO4"
#define BAUDRATE B115200

//Configure BB-UART
struct termios options;

struct PktDef
{
	unsigned Forward : 1;
	unsigned Backwards : 1;
	unsigned Left : 1;
	unsigned Right : 1;
	unsigned ArmUp : 1;
	unsigned ArmDn : 1;
	unsigned GripOpen : 1;
	unsigned GripClose : 1;
};

void TxBytes(int &uart, PktDef *buffer, size_t Size)
{
	if (uart != -1)
	{
		int count = write(uart, buffer, Size);

		if (count < 0) {
			std::cout << "ERROR:  Failed to Tx data" << std::endl;
			
		}
	}
}

void RxBytes(int &uart, void *buffer, size_t MaxSize)
{
	if (uart != -1)
	{
		int rx_length = read(uart, buffer, MaxSize);

		if (rx_length == 0)
			std::cout << "ERROR:  An error occurred during the UART read" << std::endl;
	}
}


int main()
{
	PktDef pktdef;


	int uart_stream = -1;
	uart_stream = open(PORT, O_RDWR);

	tcgetattr(uart_stream, &options);
	options.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;//sets baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart_stream, TCIFLUSH);
	tcsetattr(uart_stream, TCSANOW, &options);

	if (uart_stream == -1)
	{
		std::cout << "Failed to open BB-UART" << std::endl;
		return(-1);
	}

	std::cout << "BB-UART Opened - 1" << std::endl;

	while (true) {

		TxBytes(uart_stream, &pktdef, sizeof(pktdef));

	}


}