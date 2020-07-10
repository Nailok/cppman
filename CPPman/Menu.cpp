#include "Menu.h"


typedef void(*Menu_Processing_Function_Pointer)(void);


void startGame() {
	RunGame();
}

void Exit() {
	exit(0);
}

static const Menu_Option main_menu[] =
{
	{ '1', "1.Start Game", startGame },
	{ '2', "2.Exit", Exit }

};

static const size_t quantity_selections = sizeof(main_menu) / sizeof(main_menu[0]);


 void showMenu() {

	 HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_CURSOR_INFO cursorInfo;
	 GetConsoleCursorInfo(hStdout, &cursorInfo);
	 cursorInfo.bVisible = false;
	 SetConsoleCursorInfo(hStdout, &cursorInfo);


	system("@cls||clear");
	char choice;

	const char *menu_title = "------------------------------\n\tMain Menu\n------------------------------\n";
		
	while (1) {
		
		printf("%s", menu_title);

		for (size_t i = 0; i < quantity_selections; ++i)
		{
			printf("%s \n", main_menu[i].p_selection_text);
		}

		if (GetAsyncKeyState(49)) { // VK_1
			choice = '1';
		}else
		if (GetAsyncKeyState(50)) { // VK_2
			choice = '2';
		}
		else choice = 'r'; // random key for repeating menu cycle if pressed wrong button


		for (size_t i = 0; i <= quantity_selections; ++i)
		{


			if (choice == main_menu[i].choice)
			{
				system("@cls||clear");
				Menu_Processing_Function_Pointer p_function = main_menu[i].p_processing_function;
				(p_function)();
				break;
			}
		}

		system("@cls||clear");
	}
}
