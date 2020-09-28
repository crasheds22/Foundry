#include <iostream>

#include "Theatre.h"

int main()
{
	Theatre* theatre = &Theatre::Instance();

	theatre->PreShow();

	theatre->PlayShow();

	theatre->EndShow();

	return 0;
}
