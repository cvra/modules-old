/*
 *  Copyright Droids Corporation (2007)
 *  Olivier MATZ <zer0@droids-corp.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Revision : $Id: cirbuf.c,v 1.1.2.2 2007-09-12 17:52:20 zer0 Exp $
 *
 */

#include <string.h>

#include <cirbuf.h>


void cirbuf_init(struct cirbuf * cbuf, char * buf, cirbuf_uint start, cirbuf_uint maxlen) {
    cbuf->maxlen = maxlen;
    cbuf->len = 0;
    cbuf->start = start;
    cbuf->end = start;
    cbuf->buf = buf;
}

cirbuf_int cirbuf_add_buf_head(struct cirbuf * cbuf, const char * c, cirbuf_uint n) {
    cirbuf_uint e;

    if (!n || n > CIRBUF_GET_FREELEN(cbuf))
        return -1;

    e = CIRBUF_IS_EMPTY(cbuf) ? 1 : 0;

    if (n < cbuf->start + e) {
        memcpy(cbuf->buf + cbuf->start - n + e, c, n);
    } else {
        memcpy(cbuf->buf, c  + n - (cbuf->start + e) , cbuf->start + e);
        memcpy(cbuf->buf + cbuf->maxlen - n + (cbuf->start + e), c, n - (cbuf->start + e));
    }
    cbuf->len += n;
    cbuf->start += (cbuf->maxlen - n + e);
    cbuf->start %= cbuf->maxlen;
    return n;
}

cirbuf_int cirbuf_add_buf_tail(struct cirbuf * cbuf, const char * c, cirbuf_uint n) {
    cirbuf_uint e;

    if (!n || n > CIRBUF_GET_FREELEN(cbuf))
        return -1;

    e = CIRBUF_IS_EMPTY(cbuf) ? 1 : 0;

    if (n < cbuf->maxlen - cbuf->end - 1 + e) {
        memcpy(cbuf->buf + cbuf->end + !e, c, n);
    } else {
        memcpy(cbuf->buf + cbuf->end + !e, c, cbuf->maxlen - cbuf->end - 1 + e);
        memcpy(cbuf->buf, c + cbuf->maxlen - cbuf->end - 1 + e, n - cbuf->maxlen + cbuf->end + 1 - e);
    }
    cbuf->len += n;
    cbuf->end += n - e;
    cbuf->end %= cbuf->maxlen;
    return n;
}


static inline void  __cirbuf_add_head(struct cirbuf * cbuf, char c) {
    if (!CIRBUF_IS_EMPTY(cbuf)) {
        cbuf->start += (cbuf->maxlen - 1);
        cbuf->start %= cbuf->maxlen;
    }
    cbuf->buf[cbuf->start] = c;
    cbuf->len ++;
}

cirbuf_int cirbuf_add_head_safe(struct cirbuf * cbuf, char c) {
    if (cbuf && !CIRBUF_IS_FULL(cbuf)) {
        __cirbuf_add_head(cbuf, c);
        return 0;
    }
    return -1;
}

void cirbuf_add_head(struct cirbuf * cbuf, char c) {
    __cirbuf_add_head(cbuf, c);
}

static inline void __cirbuf_add_tail(struct cirbuf * cbuf, char c) {
    if (!CIRBUF_IS_EMPTY(cbuf)) {
        cbuf->end ++;
        cbuf->end %= cbuf->maxlen;
    }
    cbuf->buf[cbuf->end] = c;
    cbuf->len ++;
}

cirbuf_int cirbuf_add_tail_safe(struct cirbuf * cbuf, char c) {
    if (cbuf && !CIRBUF_IS_FULL(cbuf)) {
        __cirbuf_add_tail(cbuf, c);
        return 0;
    }
    return -1;
}

void cirbuf_add_tail(struct cirbuf * cbuf, char c) {
    __cirbuf_add_tail(cbuf, c);
}

static inline void __cirbuf_shift_left(struct cirbuf * cbuf) {
    cirbuf_uint i;
    char tmp = cbuf->buf[cbuf->start];

    for (i=0 ; i<cbuf->len ; i++) {
        cbuf->buf[(cbuf->start+i)%cbuf->maxlen] =
            cbuf->buf[(cbuf->start+i+1)%cbuf->maxlen];
    }
    cbuf->buf[(cbuf->start-1+cbuf->maxlen)%cbuf->maxlen] = tmp;
    cbuf->start += (cbuf->maxlen - 1);
    cbuf->start %= cbuf->maxlen;
    cbuf->end += (cbuf->maxlen - 1);
    cbuf->end %= cbuf->maxlen;
}

static inline void __cirbuf_shift_right(struct cirbuf * cbuf) {
    cirbuf_uint i;
    char tmp = cbuf->buf[cbuf->end];

    for (i=0 ; i<cbuf->len ; i++) {
        cbuf->buf[(cbuf->end+cbuf->maxlen-i)%cbuf->maxlen] =
            cbuf->buf[(cbuf->end+cbuf->maxlen-i-1)%cbuf->maxlen];
    }
    cbuf->buf[(cbuf->end+1)%cbuf->maxlen] = tmp;
    cbuf->start += 1;
    cbuf->start %= cbuf->maxlen;
    cbuf->end += 1;
    cbuf->end %= cbuf->maxlen;
}

/* XXX we could do a better algorithm here... */
void cirbuf_align_left(struct cirbuf * cbuf) {
    if (cbuf->start < cbuf->maxlen/2) {
        while (cbuf->start != 0) {
            __cirbuf_shift_left(cbuf);
        }
    }
    else {
        while (cbuf->start != 0) {
            __cirbuf_shift_right(cbuf);
        }
    }
}

/* XXX we could do a better algorithm here... */
void cirbuf_align_right(struct cirbuf * cbuf) {
    if (cbuf->start >= cbuf->maxlen/2) {
        while (cbuf->end != cbuf->maxlen-1) {
            __cirbuf_shift_left(cbuf);
        }
    }
    else {
        while (cbuf->start != cbuf->maxlen-1) {
            __cirbuf_shift_right(cbuf);
        }
    }
}

cirbuf_int cirbuf_del_buf_head(struct cirbuf * cbuf, cirbuf_uint size) {
    if (!size || size > CIRBUF_GET_LEN(cbuf))
        return -1;

    cbuf->len -= size;
    if (CIRBUF_IS_EMPTY(cbuf)) {
        cbuf->start += size - 1;
        cbuf->start %= cbuf->maxlen;
    }
    else {
        cbuf->start += size;
        cbuf->start %= cbuf->maxlen;
    }
    return 0;
}


cirbuf_int cirbuf_del_buf_tail(struct cirbuf * cbuf, cirbuf_uint size) {
    if (!size || size > CIRBUF_GET_LEN(cbuf))
        return -1;

    cbuf->len -= size;
    if (CIRBUF_IS_EMPTY(cbuf)) {
        cbuf->end  += (cbuf->maxlen - size + 1);
        cbuf->end %= cbuf->maxlen;
    }
    else {
        cbuf->end  += (cbuf->maxlen - size);
        cbuf->end %= cbuf->maxlen;
    }
    return 0;
}


static inline void __cirbuf_del_head(struct cirbuf * cbuf) {
    cbuf->len --;
    if (!CIRBUF_IS_EMPTY(cbuf)) {
        cbuf->start ++;
        cbuf->start %= cbuf->maxlen;
    }
}

cirbuf_int cirbuf_del_head_safe(struct cirbuf * cbuf) {
    if (cbuf && !CIRBUF_IS_EMPTY(cbuf)) {
        __cirbuf_del_head(cbuf);
        return 0;
    }
    return -1;
}

void cirbuf_del_head(struct cirbuf * cbuf) {
    __cirbuf_del_head(cbuf);
}

static inline void __cirbuf_del_tail(struct cirbuf * cbuf) {
    cbuf->len --;
    if (!CIRBUF_IS_EMPTY(cbuf)) {
        cbuf->end  += (cbuf->maxlen - 1);
        cbuf->end %= cbuf->maxlen;
    }
}

cirbuf_int cirbuf_del_tail_safe(struct cirbuf * cbuf) {
    if (cbuf && !CIRBUF_IS_EMPTY(cbuf)) {
        __cirbuf_del_tail(cbuf);
        return 0;
    }
    return -1;
}

void cirbuf_del_tail(struct cirbuf * cbuf) {
    __cirbuf_del_tail(cbuf);
}


cirbuf_int cirbuf_get_buf_head(struct cirbuf * cbuf, char * c, cirbuf_uint size) {
    cirbuf_uint n = (size < CIRBUF_GET_LEN(cbuf)) ? size : CIRBUF_GET_LEN(cbuf);

    if (!n)
        return 0;

    if (cbuf->start <= cbuf->end) {
        memcpy(c, cbuf->buf + cbuf->start , n);
    } else {
        memcpy(c, cbuf->buf + cbuf->start , cbuf->maxlen - cbuf->start);
        memcpy(c + cbuf->maxlen - cbuf->start, cbuf->buf, n - cbuf->maxlen + cbuf->start);
    }
    return n;
}

cirbuf_int cirbuf_get_buf_tail(struct cirbuf * cbuf, char * c, cirbuf_uint size) {
    cirbuf_uint n = (size < CIRBUF_GET_LEN(cbuf)) ? size : CIRBUF_GET_LEN(cbuf);

    if (!n)
        return 0;

    if (cbuf->start <= cbuf->end) {
        memcpy(c, cbuf->buf + cbuf->end - n + 1, n);
    } else {
        memcpy(c + cbuf->maxlen - cbuf->start, cbuf->buf, cbuf->end + 1);
        memcpy(c, cbuf->buf + cbuf->maxlen - n + cbuf->end +1, n - cbuf->end - 1);
    }
    return n;
}

char cirbuf_get_head(struct cirbuf * cbuf) {
    return cbuf->buf[cbuf->start];
}

char cirbuf_get_tail(struct cirbuf * cbuf) {
    return cbuf->buf[cbuf->end];
}

