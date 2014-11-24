#include <iostream>
#include <string>

#include "game.hpp"
#include "ow_types.hpp"

void gen_ascii(int bound);

int main(int argc, char** argv)
{
	ow::Game game;
	game.loop();

	//system("PAUSE");

    return 0;
}

/*
void gen_ascii(int bound)
{
	ow::ui16 c = 33;
	int count = 0;
	printf("{\n");
	for (c = 0; c < bound; c++) {
		if (count++ % 16 == 0) { printf("\n"); }
		if ((c == 127) |
			((c > 0) && (c < 32)))
		{
			printf(" ");
		}
		else {
			printf("%c", c);
		}
	}
	printf("\n};\n\tchars=%d\n\n", count + 1);
	system("PAUSE");
}
*/