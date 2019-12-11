#include "File.hpp"
#ifdef WIDE
int FileHandle::end = WEOF;
#else
int FileHandle::end = EOF;
#endif
Character FileSource::nextChar() {
	int i = handle.getc();
	if(i == FileHandle::getEnd()) return Character();
	else return Character(i);
}
FileHandle::FileHandle(const std::string & filename) {
		handle = fopen(filename.c_str(), "r");
		if(handle == nullptr) {
			switch(errno) {
				case EACCES: error = FileOpenError::not_access; break;
				case ENOENT: error = FileOpenError::not_exist; break;
				default: error = FileOpenError::not_other;
			}
		}
		else error = FileOpenError::non_error;
		if(filename.empty()) error = FileOpenError::blank_path;
}

void FileHandle::printError() {
	switch(error) {
		case FileOpenError::not_access:
			printf("Nie masz uprawnień do czytania tego pliku\n");
			break;
		case FileOpenError::not_exist:
			printf("Podany plik nie istnieje\n");
			break;
		case FileOpenError::blank_path:
			printf("Podana ścieżka była pusta\n");
			break;
		case FileOpenError::not_other:
			printf("Bliżej nie określony błąd\n");
		}
}
