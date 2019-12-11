#pragma once
#include <cwctype>
#include <string>
class Character {
	wchar_t internal;
	bool eof;
	public:
	Character(): internal('\0'), eof(true) {}
	Character(wchar_t i): internal(i), eof(false) {}
	wchar_t getChar() const {
		return internal;
	}
	bool isEnd() const {
		return eof;
	}
	bool isSpace() const {
		return iswspace(internal);
	}
	bool isOp() const {
		return iswpunct(internal);
	}
	bool isDigit() const {
		return iswdigit(internal);
	}
	
	bool isLetter() const {
		return iswalpha(internal);
	}
	bool isVertical() const {
		return (internal == '\n');
		//ale to może się zmienić
	}
	bool isOneHorizontal() const {
		return isOp() || isDigit() || isLetter() || internal == ' ';
	}
	bool isTab() const {
		return (internal == '\t');
		//ale to może się zmienić
	}
	bool operator < (const Character & other) const {
		if(eof && !other.eof) return true;
		if(!eof && other.eof) return false;
		return (internal < other.internal);
	}
	bool operator == (const Character & other) const {
		return (internal == other.internal && eof == other.eof);
	}
};

inline bool isWhite(const Character & current) {
	return (current.isEnd() || current.isSpace());
}
class Chain : public std::wstring {
	public:
	Chain() {}
	Chain(const char i): std::wstring() { operator += ((wchar_t)i); } 
	Chain(const wchar_t i): std::wstring() { operator += (i); }
	Chain(const wchar_t * i): std::wstring(i) {}
	void append(const Character & current) {
		std::wstring::operator += (current.getChar());
	}
};
