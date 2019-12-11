#include "Source.hpp"
int Source::tabWidth;

const int Source::critical = 30;
Character Source::getNextChar() {
	Character current = nextChar();
	readed++;
	if(current.isVertical()) {
		height++;
		tabs = 0;
		width = 0;
	}
	else if(current.isOneHorizontal()) width++;
	else if(current.isTab()) tabs++;
	return current;
}

void Source::printError(const Token & mistake) {
	fputs("Error>\n", stderr);
	fprintf(stderr, "Line: %d\n", height);
	fprintf(stderr, "Column: %d\n", width + tabs*tabWidth);
	#ifdef WIDE
	freopen(nullptr, "w", stderr);
	fwprintf(stderr, L"%ls", (mistake.to_string() + (wchar_t)'\n').c_str());
	freopen(nullptr, "w", stderr);
	#else
	fprintf(stderr, "%s", (mistake.to_string() + '\n').c_str());
	#endif
	fprintf(stderr, "<Error\n");
}




	



			
					
				
		
