#pragma once
#ifndef MENU_H 
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "GameStart.h"

typedef void(*Menu_Processing_Function_Pointer)(void);

struct Menu_Option
{
	char choice;
	char const *p_selection_text;
	Menu_Processing_Function_Pointer p_processing_function;
};

void startGame();

void Exit();




void showMenu();

#endif 