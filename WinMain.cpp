#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include <Windows.h>
#include "resource.h"
#include <iostream>

using namespace std;
INT_PTR CALLBACK dialog_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
	)
{ 


	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, dialog_proc, NULL);


	return 0;
}


byte crypt_byte(byte b_val)
{
	__asm
	{
		mov al, b_val;
		ROR al, 4;
		mov b_val, al;
	}
	return b_val;
}


string crypt_text(string text)
{
	DWORD len = text.length();

	string ret;

	for (int i = 0; i < len; i++)
	{
		char hex[20];

		sprintf(hex, "0x%02X, ", crypt_byte(text[i]));

		ret += hex;
	}

	ret += "0x00";

	return ret;
}


INT_PTR CALLBACK dialog_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG) // сообщение о создании диалога
		return 0;



	if (uMsg == WM_PAINT)
		return DefWindowProc/*DefDlgProc*/(hWnd, uMsg, wParam, lParam);

	if (uMsg == WM_CLOSE ||
		uMsg == WM_DESTROY)
		EndDialog(hWnd, NULL); // закрытие приложения




	if (uMsg == WM_COMMAND)
	{
		if (wParam == IDC_BUTTON1) // кнопочка
		{
			char text[10000];

			GetDlgItemText(hWnd, IDC_EDIT2, text, 10000);

			string ret = crypt_text(text);

			SetDlgItemText(hWnd, IDC_EDIT1, ret.c_str());

			return 0;
		}
	}


	return 0;
}
