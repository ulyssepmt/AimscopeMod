#include <windows.h>
#include <stdio.h>
#include <stdbool.h>


void CreateCrosshair(char* gameTarget)
{
	DWORD ProcessID = 0;

	HWND gamehwnd = FindWindowA(0, gameTarget);
	GetWindowThreadProcessId(gamehwnd, &ProcessID);

	if (gamehwnd) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("Target game is running with the %d tPID\n", ProcessID);
	}

	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("[WARNING] Windows game not found !");
	}

	HDC gamehdc = GetDC(0);

	RECT rect;
	int pXc = 8;
	int pYc = 8;

	int xPos = ((GetSystemMetrics(SM_CXSCREEN) / 2) - (pXc / 2));
	int yPos = ((GetSystemMetrics(SM_CYSCREEN) / 2) - (pYc / 2));

	HBRUSH redColor = CreateSolidBrush(RGB(255, 0, 0)); ;

	while (true) {
		if (GetAsyncKeyState(0x57) & 0x8000) {
			SelectObject(gamehdc, redColor);
			PatBlt(gamehdc, xPos, yPos, pXc, pYc, PATCOPY);

			//GetWindowRect(gamehwnd, &rect);
		}
	}

	DeleteObject(redColor);
	ReleaseDC(0, gamehdc);
}

int main()
{
	char* gameWindowsName = ""; //Le nom de la fen�tre cible du jeu | Windows game target name here

	SetConsoleTitleA("Aimscope"); // le titre de la fenêtre 

	HWND hwnd = GetConsoleWindow();// le handle de la console
	MoveWindow(hwnd, 0, 0, 500, 220, TRUE); // redimmensionnement de la console

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // (bleu foncé)
	printf("=========================================================");
	printf("//                       Aimscope                      //");
	printf("=========================================================\n\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16);
	printf("Press [W] Key to display the crosshair !\n\n");

	CreateCrosshair(gameWindowsName);

	return 0;

}
