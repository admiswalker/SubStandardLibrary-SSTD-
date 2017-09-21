#pragma once

#define printbm(var)\
	printf("%s = \n",(#var));bmat::printBitMatrixStore((var))

#define printbm_all(var)\
	printf("%s = \n",(#var));bmat::printBitMatrixStore_all((var))
