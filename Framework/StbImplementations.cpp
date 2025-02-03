#ifdef _MSC_VER
#pragma warning(disable: 4244)
#else
// #pragma GCC diagnostic ignored "???" // TODO - GCC & Clang
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

struct __StbInit {
	__StbInit() {
		stbi_set_flip_vertically_on_load(true);
	}
} __stbinit {};
