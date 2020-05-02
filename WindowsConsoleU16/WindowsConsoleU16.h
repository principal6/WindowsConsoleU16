#pragma once

#include "pch.h"

namespace fs
{
#ifndef FS_INT_TYPE_ALIASES
#define FS_INT_TYPE_ALIASES
	using int8		= int8_t;
	using int16		= int16_t;
	using int32		= int32_t;
	using int64		= int64_t;
	using uint8		= uint8_t;
	using uint16	= uint16_t;
	using uint32	= uint32_t;
	using uint64	= uint64_t;
	using byte		= uint8;
#endif // FS_INT_TYPE_ALIASES

	class WindowsConsoleU16
	{
	public:
		WindowsConsoleU16();
		virtual ~WindowsConsoleU16();

	public:
		// 콘솔에 UTF-16 문자열을 출력하는 함수입니다.
		void write(const wchar_t* content) const noexcept;

		// 콘솔에서 UTF-16 문자열을 한 줄을 읽어오는 함수입니다.
		// read()는 줄바꿈을 만나면 리턴합니다. (띄어쓰기는 상관 없습니다.)
		void read(bool shouldEcho = false) noexcept;

		// 가장 최근에 read()한 내용과 인수 문자열을 비교하는 함수입니다.
		// 동일한 경우 true를 리턴합니다.
		bool hasRead(const wchar_t* compare) const noexcept;

	protected:
		void normalizeReadBuffer() noexcept;

	protected:
		static constexpr uint32		kReadBuferSize{ MAX_PATH };
		static constexpr uint32		kConvBuferSize{ 50 };

	protected:
		mutable DWORD				_numWritten{};
		DWORD						_numRead{};
		wchar_t						_readBuffer[kReadBuferSize]{};
		wchar_t						_convBuffer[kConvBuferSize]{};

	private:
		HANDLE						_output{};
		HANDLE						_input{};
		CONSOLE_READCONSOLE_CONTROL _readControl{};
	};
}
