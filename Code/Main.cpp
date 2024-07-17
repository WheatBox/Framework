#include "DiaryApplication.h"

int main() {
	printf("main called\n");
	return CDiaryApplication {}.EntryPoint("Framework", { 800, 600 });
}