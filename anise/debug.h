#ifndef DEBUG_H
#define DEBUG_H

//#define DEBUG

#ifdef DEBUG
	#include <stdio.h>
	#define PRINT				printf
	#define PAUSE				{char ch; scanf("%c", &ch);}
#else
	#ifdef _WIN32
		#define PRINT			/##/
	#else
		//HACK: for gcc
		#define PRINT(args...)
	#endif
	#define PAUSE
#endif

#define PRINT_ERROR				printf

#endif
