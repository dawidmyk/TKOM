#pragma once
#include <string>
#include <cctype>
class Character {
	char internal;
	bool eof;
	public:
	Character(): internal('\0'), eof(true) {}
	Character(char i): internal(i), eof(false) {}
	char getChar() const {
		return internal;
	}
	bool isEnd() const {
		return eof;
	}
	bool isSpace() const {
		return isspace(internal);
	}
	bool isOp() const {
		return ispunct(internal);
	}
	bool isDigit() const {
		return isdigit(internal);
	}
	
	bool isLetter() const {
		return isalpha(internal);
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
class Chain : public std::string {
	public:
	Chain() {}
	Chain(const char i) { operator += (i); }
	Chain(const char * i): std::string(i) {}
	Chain(const std::string & str): std::string(str) {}
	void append(Character current) {
		std::string::operator += (current.getChar());
	}
};
