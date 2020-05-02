#include "pch.h"
#include "WindowsConsoleU16.h"

#include <cstdlib>


namespace fs
{
	WindowsConsoleU16::WindowsConsoleU16()
	{
		_input = GetStdHandle(STD_INPUT_HANDLE);
		_readControl.nLength = sizeof(CONSOLE_READCONSOLE_CONTROL);
		_readControl.nInitialChars = 0;
		_readControl.dwCtrlWakeupMask = '\n';
		_readControl.dwControlKeyState = 0;

		_output = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	WindowsConsoleU16::~WindowsConsoleU16()
	{
		__noop;
	}

	void WindowsConsoleU16::write(const wchar_t* content) const noexcept
	{
		if (content == nullptr) return;
		const DWORD length{ static_cast<DWORD>(wcslen(content)) };
		if (length == 0) return;
		WriteConsoleW(_output, content, length, &_numWritten, nullptr);
	}

	void WindowsConsoleU16::read(bool shouldEcho) noexcept
	{
		ReadConsoleW(_input, _readBuffer, kReadBuferSize, &_numRead, &_readControl);
		normalizeReadBuffer();

		if (_numRead == kReadBuferSize)
		{
			write(L" [WindowsConsole] 입력의 길이가 최대치(");
			_itow_s(_numRead, _convBuffer, 10);
			write(_convBuffer);
			write(L")를 초과하여 잘립니다.\n");

			_readBuffer[kReadBuferSize - 1] = 0;
		}
		if (_numRead > 0 && shouldEcho == true)
		{
			write(_readBuffer);
		}
	}

	bool WindowsConsoleU16::hasRead(const wchar_t* compare) const noexcept
	{
		if (compare == nullptr) return false;
		return (wcscmp(_readBuffer, compare) == 0) ? true : false;
	}

	void WindowsConsoleU16::normalizeReadBuffer() noexcept
	{
		if (_readBuffer[_numRead - 1] == L'\n')
		{
			_readBuffer[_numRead - 1] = 0;
			--_numRead;
		}
		if (_readBuffer[_numRead - 1] == L'\r')
		{
			_readBuffer[_numRead - 1] = 0;
			--_numRead;
		}
	}
}
