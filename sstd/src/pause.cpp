#include "pause.hpp"

//===

#ifdef _WIN32
	void sstd::do_pauseIfWin32(){
		system("pause");	//system("pause > NUL");
	}
	void sstd::do_not_pauseIfWin32(){}
#else

	void sstd::do_pauseIfWin32(){}
	void sstd::do_not_pauseIfWin32(){}
#endif

//===

void sstd::do_pause(){
	printf("Press Enter to continue.\n");
	int c = getchar();
	c++; // in order to avoid a warning
}
void sstd::do_not_pause(){}

//===
