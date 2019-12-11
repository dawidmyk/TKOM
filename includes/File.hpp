#pragma once
#include <cstdio>
#ifdef WIDE
#include <cwchar>
#endif
#include "Source.hpp"


enum class FileOpenError {
	non_error, not_exist, not_access, not_other, blank_path
};


class FileHandle {
	static int end;
	FILE * handle;
	FileOpenError error;
	public:
	FileHandle(const std::string & filename);
	int getc() {
		#ifdef WIDE
		return getwc(handle);
		#else
		return ::getc(handle);
		#endif
	}
	~FileHandle() {
		fclose(handle);
	}
	static int getEnd() {
		return end;
	}
	
	bool isValid() {
		return (error == FileOpenError::non_error);
	}
	void printError();
};



class FileSource : public Source {
	FileHandle & handle;
	public:
	FileSource(FileHandle & handle): handle(handle) {}
	Character nextChar();
};
