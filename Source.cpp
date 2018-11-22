#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <string.h>

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

void TxBytes(int &uart, void *buffer, size_t Size)
{	
	
	if (uart != -1)
	{
		//std::cout << "Enter forward value: " << std::endl;

		//std::cin >> i;

		//buffer->Forward = i;

		int count = write(uart, buffer, Size);

		if (count < 0) {
			std::cout << "ERROR:  Failed to Tx data" << std::endl;
		}
		else {
			std::cout << "Send data!" << std::endl;
		}
		/*int count = write(uart, buffer, Size);

		std::cout << "enter i " << std::endl;
		std::cin >> i;

		std::cout << "i in TxBytes() is: " << i << std::endl;

		if (count < 0) {
			std::cout << "ERROR:  Failed to Tx data" << std::endl;
			
		}*/
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
	int forward_flag = 0;
	int backward_flag = 0;
	int right_flag = 0;
	int left_flag = 0;
	int armup_flag = 0;
	int armdwn_flag = 0;
	int gripopen_flag = 0;
	int gripclose_flag = 0;

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

	//TxBytes(uart_stream, &pktdef, sizeof(pktdef));
	//std::cin >> i;

	//TxBytes(uart_stream, &i, sizeof(i));
	char str;
	char sendStr;

	while (true) {
		//RxBytes(uart_stream, &str, sizeof(str));

		//std::cout <<"str is: " <<  str << std::endl;

		std::cout << "enter send str, type 'x' to end: " << std::endl;
		std::cin >> sendStr;

		if (sendStr == 'x')
		{
			return 1;
		}

		TxBytes(uart_stream, &sendStr, sizeof(sendStr));
	}

	/*while (true) {
		std::cout << "Enter packet data" << std::endl;
		std::cout << "__________________" << std::endl;
		std::cout << "Enter forward flag:" << std::endl;
		std::cin >> forward_flag;
		std::cout << "Enter backward flag:" << std::endl;
		std::cin >> backward_flag;
		std::cout << "Enter right flag:" << std::endl;
		std::cin >> right_flag;
		std::cout << "Enter left flag:" << std::endl;
		std::cin >> left_flag;
		std::cout << "Enter Arm up flag:" << std::endl;
		std::cin >> armup_flag;
		std::cout << "Enter Arm down flag:" << std::endl;
		std::cin >> armdwn_flag;
		std::cout << "Enter grip open flag:" << std::endl;
		std::cin >> gripopen_flag;
		std::cout << "Enter grip close flag:" << std::endl;
		std::cin >> gripclose_flag;

		pktdef.Forward = forward_flag;
		pktdef.Backwards = backward_flag;
		pktdef.Right = right_flag;
		pktdef.Left = left_flag;
		pktdef.ArmUp = armup_flag;
		pktdef.ArmDn = armdwn_flag;
		pktdef.GripOpen = gripopen_flag;
		pktdef.GripClose = gripclose_flag;


		TxBytes(uart_stream, &pktdef, sizeof(pktdef));

		std::cout << "________________________________" << std::endl;
	}*/


}