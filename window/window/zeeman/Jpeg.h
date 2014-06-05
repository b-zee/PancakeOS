#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include <ZM/Window.hpp>
#include "jpeglib.h"

namespace zm {

class LIB_CLASS Jpeg {
public:

	enum Colorspace {
		RGB,
		Grayscale
	};
	struct Fields {
		unsigned int	width;
		unsigned int	height;
		unsigned int	stride;
		unsigned int	components;

		Colorspace		colorspace;
	} fields;

	Jpeg(const char *file_name, Colorspace cs = RGB);
	Jpeg(int width, int height, const char *file_name = 0, Colorspace cs = RGB);
	~Jpeg();

	bool Decompress();
	bool Compress(int quality = 75);

	unsigned char *GetBuffer();

private:
	const char *pFileName;
	unsigned char *pBuffer;

	unsigned char	*_CreateBuffer(int width, int height, int components = 3, bool empty = false);
	void			_DestroyBuffer(unsigned char *buffer, int width, int height, int components = 3);
};


}
