#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef WINDOWS
#include <conio.h>
#include <dos.h>
#else
#define LINUX
#endif

#define NONE_OPTION 0
#define SIMPLE_OPTION 1
#define DOUBLE_OPTION 2
#define X_OPTION 3
#define SHADOW_OPTION 4
#define KITT_OPTION 5
#define RANDOM_OPTION 6
#define OTHER_OPTION 7
#define EXIT_OPTION 8

#define OPTIONS_RANGE_BEGIN 1
#define OPTIONS_RANGE_END 8

// THE LTP PORT ADDRESS CAN BE SYSTEM DEPENDEND BUT CHOOSING
// 0x378, 0x278 OR 0x3BC SHOULD DO THE TRICK
#define LTP_PORT_ADDRESS 0x378

#define TURN_OFF_SIGNAL 0

#define MAX_SIGNAL_VALUE 128


void turn_off_leds(const int ltp_port);

void pre_init();
void print_menu();
void printl(const char* s);
void printl(const int i);
int get_opt();
void perform_effect(const int op);

void perform_simple_effect();
void perform_double_effect();
void perform_x_effect();
void perform_shadow_effect();
void perform_kitt_effect();
void perform_random_effect();
void perform_other_effect();

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
	
	srand( time( NULL ));
}

void print_menu()
{
	printl("MENU DE EFECTOS LED");
	printl("1) Simple");
	printl("2) Doble");
	printl("3) Equis");
	printl("4) Sombra");
	printl("5) Auto-fantastico");
	printl("6) Aleatorio");
	printl("7) Otro");
	printl("8) Salir");
	printf("Seleccione un efecto y oprima la tecla [ENTER]:");
}

void printl(const char* s)
{
	printf("%s\n", s);
}

void printl(const int i)
{
	printf("%i\n", i);
}

int get_opt()
{
	int result = -1;

	scanf("%i", &result);

	return result;
}

void perform_effect(const int op)
{
	switch(op)
	{
		case SIMPLE_OPTION:
			printl("Efecto Simple");
			perform_simple_effect();
		break;
		case DOUBLE_OPTION:
			perform_double_effect();
		break;
		case X_OPTION:
			perform_x_effect();
		break;
		case SHADOW_OPTION:
			perform_shadow_effect();
		break;
		case KITT_OPTION:
			perform_kitt_effect();
		break;
		case RANDOM_OPTION:
			perform_random_effect();
		break;
		case OTHER_OPTION:
			perform_other_effect();
		break;
		case EXIT_OPTION:
			printl("BYE...");
		break;
		default:
			printl("BAD INPUT, Try Again");
		break;
	}
}

void turn_off_leds(const int ltp_port_address)
{
	#ifdef WINDOWS
	outport(ltp_port_address, TURN_OFF_SIGNAL);
	#endif

	#ifdef LINUX
	printl("LEDS TURNED OFF");
	#endif
}

void perform_simple_effect()
{	
	int signal = 1;
	int prev_signal = 0;
	
	do
	{
		send_signal(signal);

		prev_signal = signal;

		signal = (signal << 1) | prev_signal;
	} 
	while(signal <= MAX_SIGNAL_VALUE);
}

void perform_double_effect()
{
	printl("Efecto Doble");

	int signal = 3;

	do
	{
		send_signal(signal);

		signal = signal * 2;
	} 
	while(signal <= MAX_SIGNAL_VALUE);
}

void perform_x_effect()
{
	const int X_EFFECT_MIN = 1;
	const int X_EFFECT_MAX = 64;
	const int X_EFFECT_MID = 8;

	printl("Efecto X");

	int signal = 0;

	int a = X_EFFECT_MIN;
	int b = X_EFFECT_MAX;

	int half_cycles = 0;

	do
	{
		signal = a | b;

		if (a == b)
			signal = 8;

		send_signal(signal);

		a = a << 1;
		b = b >> 1;
	} 
	while (a <= X_EFFECT_MAX && b >= X_EFFECT_MIN);
}

void perform_shadow_effect()
{
	const int SHADOW_EFFECT_MIN_SIGNAL = 63;

	printl("Efecto Sombra");

	int signal = 127;
	int temp   = 1;

	do
	{
		send_signal(signal);

		temp = temp * 2;

		signal = (MAX_SIGNAL_VALUE-1) ^ temp;
	}
	while(signal <= MAX_SIGNAL_VALUE);
}

void perform_kitt_effect()
{
	const int KITT_EFFECT_MIN_SIGNAL_VALUE = 1;
	const int KITT_EFFECT_MAX_CYCLES = 3;
	
	printl("Efecto KITT (El auto fantastico)");

	int signal  = 1;
	int cycles  = 0;
	int reverse = 0;
	
	do
	{
		send_signal(signal);

		if (reverse == 0)
			signal = signal << 1;
		else
			signal = signal >> 1;

		if (signal >= MAX_SIGNAL_VALUE)
			reverse = 1;
		else if (reverse == 1 && signal == KITT_EFFECT_MIN_SIGNAL_VALUE)
		{
			reverse = 0; 
			cycles++;
		}

	} 
	while(cycles < KITT_EFFECT_MAX_CYCLES);
}

void perform_random_effect()
{
	const int RANDOM_EFFECT_MAX_CYCLES = 8;
	
	printl("Efecto Aleatorio");
	
	int cycles = 0;
	
	int signal = 0;
	
	do
	{
		signal = rand() % MAX_SIGNAL_VALUE + 1;
		
		send_signal(signal);
	}
	while(++cycles < RANDOM_EFFECT_MAX_CYCLES);
}

void perform_other_effect()
{	
	printl("El Otro Efecto");
	
	const int X_EFFECT_MIN = 1;
	const int X_EFFECT_MAX = 64;
	const int X_EFFECT_MID = 8;

	printl("Efecto X");

	int signal = 0;

	int a = X_EFFECT_MIN;
	int b = X_EFFECT_MAX;

	int half_cycles = 0;

	do
	{
		signal = a | b;

		if (a == b)
		{
			signal = 8;
			send_signal(signal);
			break;
		}
			
		send_signal(signal);

		a = a << 1;
		b = b >> 1;
	} 
	while (a <= X_EFFECT_MAX && b >= X_EFFECT_MIN);
}

void send_signal(const int signal)
{
	if (signal <= MAX_SIGNAL_VALUE)
	{
	#ifdef WINDOWS
		outport(ltp_port_address, signal);
	#endif

	#ifdef LINUX
		printl(signal);
	#endif
	}
	else
	{
		printf("ERROR: Signal %i is too high to be sended\n", signal);
	}
}

