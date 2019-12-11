#include "Token.hpp"

std::string to_string(const TokenType type) {
	switch(type) {
		case TokenType::id: return "id";
		case TokenType::op: return "op";
		case TokenType::keyword: return "keyword";
		case TokenType::nume: return "nume";
		case TokenType::comment: return "comment";
		case TokenType::mistake: return "mistake";
	}
	return std::string();
}


std::string Token::to_string() const {
	std::string result;
	result = ::to_string(myType);
	result += " -> ";
	result += (std::string)content;
	return result;
}

void Token::analize() {
		if(myType == TokenType::id) {
			KeywordType type = key_filtr(content);
			/* jeśli none to nie ma takiego keywordu
			 * więc to jednak był id
			 * post parser dopiero wykryje użycie
			 * nie zadeklarowanego id */
			
			if(type != KeywordType::t_none) {
				keyword = type;
				myType = TokenType::keyword;
			}
		}
		else if(myType == TokenType::op)
			op = operator_filtr(content);
}
