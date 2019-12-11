#include "scan.hpp"
#include "File.hpp"
#include "Locale.hpp"
#include "Operators.hpp"
int main(int count, char * args[]) {
	
	if(count != 2) {
		fputs("Błędne wywołanie\n", stderr);
		exit(1);
	}
	#ifdef WIDE
	setLocale();
	#endif
	Source::setTabWidth(4);
	/* dobrze jest to wyrzucić do funkcji w mainie
	 * bo może często to trzeba będzie zmieniać */
	Operators::start();
	FileHandle handle(args[1]);
	if(!handle.isValid()) {
		handle.printError();
		exit(1);
	}
	FileSource source(handle);
	TokenList list;
	bool result = scan(source, list);
	if(!result) source.printError(list.last());
	list.printTokens();
}
	
