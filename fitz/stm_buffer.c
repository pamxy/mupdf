#include "fitz.h"

fz_buffer *
fz_new_buffer(fz_context *ctx, int size)
{
	fz_buffer *b;

	size = size > 1 ? size : 16;

	b = fz_malloc(ctx, sizeof(fz_buffer));
	b->refs = 1;
	b->data = fz_malloc(ctx, size);
	b->cap = size;
	b->len = 0;

	return b;
}

fz_buffer *
fz_keep_buffer(fz_buffer *buf)
{
	buf->refs ++;
	return buf;
}

void
fz_drop_buffer(fz_context *ctx, fz_buffer *buf)
{
	if (--buf->refs == 0)
	{
		fz_free(ctx, buf->data);
		fz_free(ctx, buf);
	}
}

void
fz_resize_buffer(fz_context *ctx, fz_buffer *buf, int size)
{
	buf->data = fz_realloc(ctx, buf->data, size);
	buf->cap = size;
	if (buf->len > buf->cap)
		buf->len = buf->cap;
}

void
fz_grow_buffer(fz_context *ctx, fz_buffer *buf)
{
	fz_resize_buffer(ctx, buf, (buf->cap * 3) / 2);
}
