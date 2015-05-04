/* Extended Module Player
 * Copyright (C) 1996-2015 Claudio Matsuoka and Hipolito Carraro Jr
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "common.h"
#include "hio.h"
#include "mdataio.h"


struct hio {
	HIO_HANDLE *(*open)(void *, char *);
	int (*close)(HIO_HANDLE *);
	int (*read)(void *, int, int, HIO_HANDLE *);
	int (*write)(void *, int, int, HIO_HANDLE *);
	int (*seek)(HIO_HANDLE *, long, int);
	long (*tell)(HIO_HANDLE *);
	int (*eof)(HIO_HANDLE *);
};

static HIO_HANDLE *stdio_open(void *name, char *mode)
{
	return fopen(name, mode);
}

static int stdio_close(HIO_HANDLE *handle)
{
	return fclose((FILE *)handle);
}

static int stdio_read(void *buffer, int size, int num, HIO_HANDLE *handle)
{
	return fread(buffer, size, num, (FILE *)handle);
}

static int stdio_write(void *buffer, int size, int num, HIO_HANDLE *handle)
{
	return fwrite(buffer, size, num, (FILE *)handle);
}

static int stdio_seek(HIO_HANDLE *handle, long offset, int whence)
{
	return fseek((FILE *)handle, offset, whence);
}

static long stdio_tell(HIO_HANDLE *handle)
{
	return ftell((FILE *)handle);
}

static int stdio_eof(HIO_HANDLE *handle)
{
	return feof((FILE *)handle);
}

struct hio hio_stdio = {
	stdio_open,
	stdio_close,
	stdio_read,
	stdio_write,
	stdio_seek,
	stdio_tell,
	stdio_eof
};

static struct hio *hio = &hio_stdio;



int8 hio_read8s(HIO_HANDLE *h)
{
	int8 b;

	if (hio->read(&b, 1, 1, h) < 0) {
		return EOF;
	}

	return b;
}

uint8 hio_read8(HIO_HANDLE *h)
{
	uint8 b;

	if (hio->read(&b, 1, 1, h) < 0) {
		return EOF;
	}

	return b;
}

uint16 hio_read16l(HIO_HANDLE *h)
{
	uint32 a, b;

	a = hio_read8(h);
	b = hio_read8(h);

	return (b << 8) | a;
}

uint16 hio_read16b(HIO_HANDLE *h)
{
	uint32 a, b;

	a = hio_read8(h);
	b = hio_read8(h);

	return (a << 8) | b;
}

uint32 hio_read24l(HIO_HANDLE *h)
{
	uint32 a, b, c;

	a = hio_read8(h);
	b = hio_read8(h);
	c = hio_read8(h);

	return (c << 16) | (b << 8) | a;
}

uint32 hio_read24b(HIO_HANDLE *h)
{
	uint32 a, b, c;

	a = hio_read8(h);
	b = hio_read8(h);
	c = hio_read8(h);

	return (a << 16) | (b << 8) | c;
}

uint32 hio_read32l(HIO_HANDLE *h)
{
	uint32 a, b, c, d;

	a = hio_read8(h);
	b = hio_read8(h);
	c = hio_read8(h);
	d = hio_read8(h);

	return (d << 24) | (c << 16) | (b << 8) | a;
}

uint32 hio_read32b(HIO_HANDLE *h)
{
	uint32 a, b, c, d;

	a = read8(h);
	b = read8(h);
	c = read8(h);
	d = read8(h);

	return (a << 24) | (b << 16) | (c << 8) | d;
}

size_t hio_read(void *buf, size_t size, size_t num, HIO_HANDLE *h)
{
	return hio->read(buf, size, num, h);
}

int hio_seek(HIO_HANDLE *h, long offset, int whence)
{
	return hio->seek(h, offset, whence);
}

long hio_tell(HIO_HANDLE *h)
{
	return hio->tell(h);
}

int hio_eof(HIO_HANDLE *h)
{
	return hio->eof(h);
}

HIO_HANDLE *hio_open(void *path, char *mode)
{
	return hio->open(path, mode);
}

HIO_HANDLE *hio_open_mem(void *ptr, long size)
{
	HIO_HANDLE *h;

#if 0
	h = (HIO_HANDLE *)malloc(sizeof (HIO_HANDLE));
	if (h == NULL)
		return NULL;
	
	h->type = HIO_HANDLE_TYPE_MEMORY;
	h->handle.mem = mopen(ptr, size);
	h->size = size;
#endif

	return h;
}

HIO_HANDLE *hio_open_file(FILE *f)
{
	HIO_HANDLE *h;

#if 0
	h = (HIO_HANDLE *)malloc(sizeof (HIO_HANDLE));
	if (h == NULL)
		return NULL;
	
	h->type = HIO_HANDLE_TYPE_FILE;
	h->handle.file = f /*fdopen(fileno(f), "rb")*/;
	h->size = get_size(f);
#endif

	return h;
}

int hio_close(HIO_HANDLE *h)
{
	return hio->close(h);
}

long hio_size(HIO_HANDLE *h)
{
	long end, pos = hio->tell(h);

	if (pos < 0) {
		return -1;
	}

	if (hio->seek(h, 0, SEEK_END) < 0) {
		return -1;
	}

	end = hio->tell(h);

	hio->seek(h, pos, SEEK_SET);

	return end;
}
