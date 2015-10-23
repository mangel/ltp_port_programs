#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOWS

#ifdef WINDOWS
#include <conio.h>
#include <dos.h>
#else
#define LINUX
#endif

#define USE_KBHIT

#define MOTOR_1_TURN_RIGHT 2
#define MOTOR_1_TURN_LEFT  4
#define MOTOR_2_TURN_RIGHT 8
#define MOTOR_2_TURN_LEFT  16
#define MOTOR_3_TURN_RIGHT 32
#define MOTOR_3_TURN_LEFT  64
#define MOTORS_1_2_3_TURN_RIGHT MOTOR_1_TURN_RIGHT | MOTOR_2_TURN_RIGHT | MOTOR_3_TURN_RIGHT
#define MOTORS_1_2_3_TURN_LEFT  MOTOR_1_TURN_LEFT  | MOTOR_2_TURN_LEFT  | MOTOR_3_TURN_LEFT


#define NONE_OPTION -1
#define MOTOR_1_TURN_R_OPTION 49
#define MOTOR_1_TURN_L_OPTION 50
#define MOTOR_2_TURN_R_OPTION 51
#define MOTOR_2_TURN_L_OPTION 52
#define MOTOR_3_TURN_R_OPTION 53
#define MOTOR_3_TURN_L_OPTION 54
#define MOTORS_1_2_3_TURN_R_OPTION 55
#define MOTORS_1_2_3_TURN_L_OPTION 56
#define STOP_MOTORS_OPTION 57
#define EXIT_OPTION 48

#define OPTIONS_RANGE_BEGIN -1
#define OPTIONS_RANGE_END 58

// THE LTP PORT ADDRESS CAN BE SYSTEM DEPENDEND BUT CHOOSING
// 0x378, 0x278 OR 0x3BC SHOULD DO THE TRICK
#define LTP_PORT_ADDRESS 0x378

#define TURN_OFF_SIGNAL 0

#define MAX_SIGNAL_VALUE 222

//Hmmm... no sure about it... but in the datasheet the IC deals with a maximum rate of 750ns(nano secs) 60ms should be fine
#define EFFECTS_DELAY_IN_MILLISECONDS 60

void turn_off_motors(const int ltp_port);

void pre_init();
void print_menu();
void printl(const char* s);
int get_opt();
void perform_effect(const int op);

void motor_1_turn_right();
void motor_1_turn_left();
void motor_2_turn_right();
void motor_2_turn_left();
void motor_3_turn_right();
void motor_3_turn_left();
void motors_1_2_3_turn_right();
void motors_1_2_3_turn_left();
void stop_motors();

void send_signal(const int signal);

int main()
{
	int selected_option = NONE_OPTION;
	pre_init();

	do
	{
		print_menu();
		selected_option = get_opt();
		perform_effect(selected_option);
	}
	while(selected_option != EXIT_OPTION);

	return 0;
}

void pre_init()
{
	#ifdef WINDOWS
	clrscr();
	#endif
}

void print_menu()
{
	printl("MENU DE EFECTOS MOTOR (oprima la tecla para el efecto)");
	printl(" 1) Motor 1 girar a la derecha");
	printl(" 2) Motor 1 girar a la izquierda");
	printl(" 3) Motor 2 girar a la derecha");
	printl(" 4) Motor 2 girar a la izquierda");
	printl(" 5) Motor 3 girar a la derecha");
	printl(" 6) Motor 3 girar a la izquierda");
	printl(" 7) Motores 1, 2 y 3 girar a la derecha");
	printl(" 8) Motores 1, 2 y 3 girar a la izquierda");
	printl(" 9) Detener");
	printl(" 0) Salir");
	//printf("Seleccione un efecto y oprima la tecla [ENTER]:");
}

void printl(const char* s)
{
	printf("%s\n", s);
}

int get_opt()
{
	int result = -1;

	//scanf("%i", &result);

	result = getch();

	return result;
}

void perform_effect(const int op)
{
	switch(op)
	{
		case MOTOR_1_TURN_R_OPTION:
			motor_1_turn_right();
		break;
		case MOTOR_1_TURN_L_OPTION:
			motor_1_turn_left();
		break;
		case MOTOR_2_TURN_R_OPTION:
			motor_2_turn_right();
		break;
		case MOTOR_2_TURN_L_OPTION:
			motor_2_turn_left();
		break;
		case MOTOR_3_TURN_R_OPTION:
			motor_3_turn_right();
		break;
		case MOTOR_3_TURN_L_OPTION:
			motor_3_turn_left();
		break;
		case MOTORS_1_2_3_TURN_R_OPTION:
			motors_1_2_3_turn_right();
		break;
		case MOTORS_1_2_3_TURN_L_OPTION:
			motors_1_2_3_turn_left();
		break;
		case STOP_MOTORS_OPTION:
			stop_motors();
		break;
		case EXIT_OPTION:
			printl("BYE...");
		break;
		default:
			printl("BAD INPUT, Try Again");
		break;
	}
}

void stop_motors(const int ltp_port_address)
{
	#ifdef WINDOWS
	outport(ltp_port_address, TURN_OFF_SIGNAL);
	#endif

	#ifdef LINUX
	printl("MOTORS TURNED OFF");
	#endif
}

void motor_1_turn_right()
{
	do
	{
		send_signal(MOTOR_1_TURN_RIGHT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void motor_1_turn_left()
{
	do
	{
		send_signal(MOTOR_1_TURN_LEFT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void motor_2_turn_right()
{
	do
	{
		send_signal(MOTOR_2_TURN_RIGHT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void motor_2_turn_left()
{
	do
	{
		send_signal(MOTOR_2_TURN_LEFT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void motor_3_turn_right()
{
	do
	{
		send_signal(MOTOR_3_TURN_RIGHT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void motor_3_turn_left()
{
	do
	{
		send_signal(MOTOR_3_TURN_LEFT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void motors_1_2_3_turn_right()
{
	do
	{
		send_signal(MOTORS_1_2_3_TURN_RIGHT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void motors_1_2_3_turn_left()
{
	do
	{
		send_signal(MOTORS_1_2_3_TURN_LEFT);

		#ifdef WINDOWS
		delay(EFFECTS_DELAY_IN_MILLISECONDS);
		#endif
	}
	#ifdef USE_KBHIT
	while(kbhit() == 0);
	#endif
}

void send_signal(const int signal)
{
	if (signal <= MAX_SIGNAL_VALUE)
	{
	#ifdef WINDOWS
		outport(LTP_PORT_ADDRESS, signal);
	#endif

	#ifdef LINUX
		printf("%i\n", signal);
	#endif
	}
	else
	{
		printf("ERROR: Signal %i is too high to be sended\n", signal);
	}
}

