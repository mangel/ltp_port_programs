#include <stdio.h>

#define MOTOR_1_TURN_RIGHT_LOW_SPEED 1
#define MOTOR_1_TURN_RIGHT_MID_SPEED 2
#define MOTOR_1_TURN_RIGHT_HIGH_SPEED 3
#define MOTOR_1_TURN_LEFT_LOW_SPEED 4
#define MOTOR_1_TURN_LEFT_MID_SPEED 5
#define MOTOR_1_TURN_LEFT_HIGH_SPEED 6

#define MOTOR_2_TURN_RIGHT_LOW_SPEED 7
#define MOTOR_2_TURN_RIGHT_MID_SPEED 8
#define MOTOR_2_TURN_RIGHT_HIGH_SPEED 9
#define MOTOR_2_TURN_LEFT_LOW_SPEED 10
#define MOTOR_2_TURN_LEFT_MID_SPEED 11
#define MOTOR_2_TURN_LEFT_HIGH_SPEED 12

#define MOTOR_1_2_TURN_RIGHT_LOW_SPEED 13
#define MOTOR_1_2_TURN_RIGHT_MID_SPEED 14
#define MOTOR_1_2_TURN_RIGHT_HIGH_SPEED 15
#define MOTOR_1_2_TURN_LEFT_LOW_SPEED 16
#define MOTOR_1_2_TURN_LEFT_MID_SPEED 17
#define MOTOR_1_2_TURN_LEFT_HIGH_SPEED 18

#define EXIT 19

#define MOTOR_1 1
#define MOTOR_2 8

#define MOTOR_1_TURN_LEFT 4
#define MOTOR_1_TURN_RIGHT 2
#define MOTOR_2_TURN_LEFT 32
#define MOTOR_2_TURN_RIGHT 16


#define MAX_VALUE 10

#define LOW 0.25
#define MID 0.5
#define HIGH 0.75

#define PORT_ADDR 0x278

void print_menu();
int get_command();
void send_signal_with_delay(int signal, int delay);
int get_signal_from_command(int command, int* speed);
void send_signal(int port_addr, int signal);

int main()
{
	int exit = 0;
	int unrecognized_option = 0;

	int command = 0;

	int speed = 0;
	int signal = 0;

	int *speedPTR = &speed;

	while(exit == 0)
	{
		print_menu();
		
		command = get_command();

		if (command == -1)
		{
			exit = 1;
		}
		else if (command != 0)
		{
			signal = get_signal_from_command(command, speedPTR);

			printf("Signal: %d, Speed: %d\n", signal, speed);

			send_signal_with_delay(signal, speed);

			exit = 1;
		}
	}

	return 0;
}

void print_menu()
{
	printf("MENU\n");
	printf("1) Motor 1 Girar DERECHA Velocidad BAJA\n");
	printf("2) Motor 1 Girar DERECHA Velocidad MEDIA\n");
	printf("3) Motor 1 Girar DERECHA Velocidad ALTA\n");
	printf("4) Motor 1 Girar IZQUIERDA Velocidad BAJA\n");
	printf("5) Motor 1 Girar IZQUIERDA Velocidad MEDIA\n");
	printf("6) Motor 1 Girar IZQUIERDA Velocidad ALTA\n");

	printf("7) Motor 2 Girar DERECHA Velocidad BAJA\n");
	printf("8) Motor 2 Girar DERECHA Velocidad MEDIA\n");
	printf("9) Motor 2 Girar DERECHA Velocidad ALTA\n");
	printf("10) Motor 2 Girar IZQUIERDA Velocidad BAJA\n");
	printf("11) Motor 2 Girar IZQUIERDA Velocidad MEDIA\n");
	printf("12) Motor 2 Girar IZQUIERDA Velocidad ALTA\n");

	printf("13) Motor 1 y 2 Girar DERECHA Velocidad BAJA\n");
	printf("14) Motor 1 y 2 Girar DERECHA Velocidad MEDIA\n");
	printf("15) Motor 1 y 2 Girar DERECHA Velocidad ALTA\n");
	printf("16) Motor 1 y 2 Girar IZQUIERDA Velocidad BAJA\n");
	printf("17) Motor 1 y 2 Girar IZQUIERDA Velocidad MEDIA\n");
	printf("18) Motor 1 y 2 Girar IZQUIERDA Velocidad ALTA\n");

	printf("19) SALIR\n");
}

int get_command()
{
	int command = -1;

	scanf("%d", &command);

	return command;
}


void send_signal_with_delay(int signal, int delay)
{
	//KBHIT code
	send_signal(PORT_ADDR, signal);
	//wait delay
	send_signal(PORT_ADDR, 0);
	//wait MAX_VALUE - delay
	
}

int get_signal_from_command(int command, int *speed)
{
	int signal = 0;

	switch(command)
	{
		case MOTOR_1_TURN_RIGHT_LOW_SPEED:
			signal = MOTOR_1 | MOTOR_1_TURN_RIGHT;
			*speed = MAX_VALUE * LOW;
		break;
		case MOTOR_1_TURN_RIGHT_MID_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_RIGHT;
			*speed = MAX_VALUE * MID;
		break;
		case MOTOR_1_TURN_RIGHT_HIGH_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_RIGHT;
			*speed = MAX_VALUE * HIGH;
		break;
		case MOTOR_1_TURN_LEFT_LOW_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_LEFT;
			*speed = MAX_VALUE * LOW;
		break;
		case MOTOR_1_TURN_LEFT_MID_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_LEFT;
			*speed = MAX_VALUE * MID;
		break;
		case MOTOR_1_TURN_LEFT_HIGH_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_LEFT;
			*speed = MAX_VALUE * HIGH;
		break;

		case MOTOR_2_TURN_RIGHT_LOW_SPEED:
			signal |= MOTOR_2 | MOTOR_2_TURN_RIGHT;
			*speed = MAX_VALUE * LOW;
		break;
		case MOTOR_2_TURN_RIGHT_MID_SPEED:
			signal |= MOTOR_2 | MOTOR_2_TURN_RIGHT;
			*speed = MAX_VALUE * MID;
		break;
		case MOTOR_2_TURN_RIGHT_HIGH_SPEED:
			signal |= MOTOR_2 | MOTOR_2_TURN_RIGHT;
			*speed = MAX_VALUE * HIGH;
		break;
		case MOTOR_2_TURN_LEFT_LOW_SPEED:
			signal |= MOTOR_2 | MOTOR_2_TURN_LEFT;
			*speed = MAX_VALUE * LOW;
		break;
		case MOTOR_2_TURN_LEFT_MID_SPEED:
			signal |= MOTOR_2 | MOTOR_2_TURN_LEFT;
			*speed = MAX_VALUE * MID;
		break;
		case MOTOR_2_TURN_LEFT_HIGH_SPEED:
			signal |= MOTOR_2 | MOTOR_2_TURN_LEFT;
			*speed = MAX_VALUE * HIGH;
		break;
		case MOTOR_1_2_TURN_RIGHT_LOW_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_RIGHT;
			signal |= MOTOR_2 | MOTOR_2_TURN_RIGHT;
			*speed = MAX_VALUE * LOW;
		break;
		case MOTOR_1_2_TURN_RIGHT_MID_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_RIGHT;
			signal |= MOTOR_2 | MOTOR_2_TURN_RIGHT;
			*speed = MAX_VALUE * MID;
		break;
		case MOTOR_1_2_TURN_RIGHT_HIGH_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_RIGHT;
			signal |= MOTOR_2 | MOTOR_2_TURN_RIGHT;
			*speed = MAX_VALUE * HIGH;
		break;
		case MOTOR_1_2_TURN_LEFT_LOW_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_LEFT;
			signal |= MOTOR_2 | MOTOR_2_TURN_LEFT;
			*speed = MAX_VALUE * LOW;
		break;
		case MOTOR_1_2_TURN_LEFT_MID_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_LEFT;
			signal |= MOTOR_2 | MOTOR_2_TURN_LEFT;
			*speed = MAX_VALUE * MID;
		break;
		case MOTOR_1_2_TURN_LEFT_HIGH_SPEED:
			signal |= MOTOR_1 | MOTOR_1_TURN_LEFT;
			signal |= MOTOR_2 | MOTOR_2_TURN_LEFT;
			*speed = MAX_VALUE * HIGH;
		break;
	}

	return signal;
}

void send_signal(int port_addr, int signal)
{
	//outportb code
}
