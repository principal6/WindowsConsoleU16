#include "../WindowsConsoleU16/WindowsConsoleU16.h"

int main()
{
	fs::WindowsConsoleU16 console{};

	console.write(L"WindowsConsoleU16을 테스트하는 프로그램입니다.\n");

	while (true)
	{
		console.write(L"> ");
		console.read();

		if (console.hasRead(L"quit"))
		{
			break;
		}
	}

	return 0;
}
