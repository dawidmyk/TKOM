#include "WideToken.hpp"

std::wstring to_string(const TokenType type) {
	switch(type) {
		case TokenType::id: return L"id";
		case TokenType::op: return L"op";
		case TokenType::keyword: return L"keyword";
		case TokenType::nume: return L"nume";
		case TokenType::comment: return L"comment";
		case TokenType::mistake: return L"mistake";
	}
	return std::wstring();
}


std::wstring Token::to_string() const {
	std::wstring result;
	result = ::to_string(myType);
	result += L" -> ";
	result += (std::wstring)content;
	return result;
}

void Token::analize() {
		//patrz komentarz w Token.cpp
		if(myType == TokenType::id) {
			KeywordType type = key_filtr(content);
			if(type != KeywordType::t_none) {
				keyword = type;
				myType = TokenType::keyword;
			}
		}
		else if(myType == TokenType::op)
			op = operator_filtr(content);
}
