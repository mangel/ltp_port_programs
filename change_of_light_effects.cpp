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
#define LOW_OPTION 1
#define MEDIUM_OPTION 2
#define HIGH_OPTION 3
#define HIGHEST_OPTION 4
#define VARIABLE_OPTION 5
#define EXIT_OPTION 6

#define OPTIONS_RANGE_BEGIN 1
#define OPTIONS_RANGE_END 6

// THE LTP PORT ADDRESS CAN BE SYSTEM DEPENDEND BUT CHOOSING
// 0x378, 0x278 OR 0x3BC SHOULD DO THE TRICK
#define LTP_PORT_ADDRESS 0x378

#define TURN_OFF_SIGNAL 0

#define MAX_SIGNAL_VALUE 127

#define EFFECTS_DELAY_IN_MILLISECONDS 100

#define GREEN_LED_MAX_FRECUENCY  535*(10)*(1000000000000)

#define LED_MAX_ON_STATE_MILLISECONDS 1000

#define LEVELS_OF_LIGHT_CHANGE	4

#define NUMBER_OF_CYCLES 4

#define VARIABLE_SUB_CYCLES 2

void turn_off_leds(const int ltp_port);

void pre_init();
void print_menu();
void printl(const char* s);
void printl(const int i);
int get_opt();
void perform_effect(const int op);

void low_effect();
void medium_effect();
void high_effect();
void highest_effect();
void variable_effect();

void send_signal(const int signal);

void send_signal_and_interrupt(const int signal, const int on_time_in_milliseconds, const int off_time_in_milliseconds);

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
	printl("1) Bajo");
	printl("2) Medio");
	printl("3) Semi-Alto");
	printl("4) Alto");
	printl("5) Variable");
	printl("6) Salir");
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
		case LOW_OPTION:
			printl("Efecto Bajo");
			low_effect();
		break;
		case MEDIUM_OPTION:
			printl("Efecto Medio");
			medium_effect();
		break;
		case HIGH_OPTION:
			printl("Efecto Semi-Alto");
			high_effect();
		break;
		case HIGHEST_OPTION:
			printl("Efecto Alto");
			highest_effect();
		break;
		case VARIABLE_OPTION:
			printl("Efecto Variable");
			variable_effect();
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
	int vart = ltp_port_address + 1;
	vart = 0;
	printl(vart);

	#ifdef WINDOWS
	outport(ltp_port_address, TURN_OFF_SIGNAL);
	#endif

	#ifdef LINUX
	printl("LEDS TURNED OFF");
	#endif
}

void low_effect()
{
	const int TURNED_ON_MILLISECONDS  = LED_MAX_ON_STATE_MILLISECONDS * 0.25;
	const int TURNED_OFF_MILLISECONDS = LED_MAX_ON_STATE_MILLISECONDS * 0.75;
	
	int cycles = 0;
	
	do
	{
		send_signal_and_interrupt(MAX_SIGNAL_VALUE, TURNED_ON_MILLISECONDS, TURNED_OFF_MILLISECONDS);
	}
	while(++cycles < NUMBER_OF_CYCLES);
	
}

void medium_effect()
{
	const int TURNED_ON_MILLISECONDS  = LED_MAX_ON_STATE_MILLISECONDS * 0.5;
	const int TURNED_OFF_MILLISECONDS = LED_MAX_ON_STATE_MILLISECONDS * 0.5;
	
	int cycles = 0;
	
	do
	{
		send_signal_and_interrupt(MAX_SIGNAL_VALUE, TURNED_ON_MILLISECONDS, TURNED_OFF_MILLISECONDS);
	}
	while(++cycles < NUMBER_OF_CYCLES);
}

void high_effect()
{
	const int TURNED_ON_MILLISECONDS  = LED_MAX_ON_STATE_MILLISECONDS * 0.75;
	const int TURNED_OFF_MILLISECONDS = LED_MAX_ON_STATE_MILLISECONDS * 0.25;
	
	int cycles = 0;
	
	do
	{
		send_signal_and_interrupt(MAX_SIGNAL_VALUE, TURNED_ON_MILLISECONDS, TURNED_OFF_MILLISECONDS);
	}
	while(++cycles < 8);
}

void highest_effect()
{
	const int TURNED_ON_MILLISECONDS  = LED_MAX_ON_STATE_MILLISECONDS * 1;
	const int TURNED_OFF_MILLISECONDS = LED_MAX_ON_STATE_MILLISECONDS * 0;
	
	int cycles = 0;
	
	do
	{
		send_signal_and_interrupt(MAX_SIGNAL_VALUE, TURNED_ON_MILLISECONDS, TURNED_OFF_MILLISECONDS);
	}
	while(++cycles < NUMBER_OF_CYCLES);
}

void variable_effect()
{
	int cycles = 0;
	
	do
	{
		low_effect();
		medium_effect();
		high_effect();
		highest_effect();
	}
	while(++cycles < NUMBER_OF_CYCLES);
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

void send_signal_and_interrupt(const int signal, const int on_time_in_milliseconds, const int off_time_in_milliseconds)
{
		send_signal(signal);
		
		#ifdef WINDOWS
		delay(on_time_in_milliseconds);
		#endif
		
		#ifdef LINUX
		printl(on_time_in_milliseconds);
		#endif
		
		send_signal(TURN_OFF_SIGNAL);
		
		#ifdef WINDOWS
		delay(off_time_in_milliseconds);
		#endif
		
		#ifdef LINUX
		printl(off_time_in_milliseconds);
		#endif
}

