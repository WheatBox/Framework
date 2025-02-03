#include "Application.h"

int main() {
	printf("main called\n");
	return CApplication {}.EntryPoint("Framework", { 800, 600 });
}