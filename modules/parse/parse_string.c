#include <stdio.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>

#include "parse.h"
#include "parse_string.h"

struct token_ops token_string_ops = {
	.parse = parse_string,
	.complete_get_nb = complete_get_nb_string,
	.complete_get_elt = complete_get_elt_string,
	.get_help = get_help_string,
};

#define MULTISTRING_HELP "Mul-choice STRING"
#define ANYSTRING_HELP   "Any STRING"
#define FIXEDSTRING_HELP "Fixed STRING"

static uint8_t get_token_len(const char * s) {
    char c;
	uint8_t i=0;

    c = *s; 
     while (c!='#' && c!='\0') {
        i++;
        c = s[i]; 
    }
    return i;
}

static const char * get_next_token(const char * s) {
	uint8_t i;
	i = get_token_len(s);
	if (s[i] == '#')
		return s+i+1;
	return NULL;
}

int8_t parse_string(parse_token_hdr_t * tk, const char * buf, void * res) {
	struct token_string_data sd;
	uint8_t token_len;
	const char * str;

	if(*buf==0)
		return -1;

	memcpy(&sd, &((struct token_string *)tk)->string_data, sizeof(sd));
    /* fixed string */
    if (sd.str) {
	    str = sd.str;
        do {
            token_len = get_token_len(str);
                
            /* if token is too big... */
            if(token_len >= STR_TOKEN_SIZE - 1)
                continue;

            if(strncmp(buf, str, token_len))
                continue;

            if(!isendoftoken(*(buf+token_len)))
                continue;

                break;
        } while ((str = get_next_token(str))!= NULL );

		if (!str)
			return -1;
        }
        /* unspecified string */
    else {
        token_len=0;
        while(!isendoftoken(buf[token_len]) && token_len < (STR_TOKEN_SIZE-1))
            token_len++;

            /* return if token too long */
            if(token_len >= STR_TOKEN_SIZE - 1) 
                return -1;
    }
        
    if(res) {
        /* we are sure that token_len is < STR_TOKEN_SIZE-1 */
        strncpy(res, buf, token_len);
        *((char *)res + token_len) = 0;
	}

     return token_len;
}

int8_t complete_get_nb_string(parse_token_hdr_t * tk) {
	struct token_string_data sd;
	int8_t ret=1;

	memcpy(&sd, &((struct token_string *)tk)->string_data, sizeof(sd));

	if (sd.str==NULL)
        return 0;

    while((sd.str = get_next_token(sd.str)) != NULL) {
		ret++;
	}
	return ret;
}

int8_t complete_get_elt_string(parse_token_hdr_t * tk, int8_t idx, char * dstbuf, uint8_t size) {
	struct token_string_data sd;
	const char * s;
	uint8_t len;

	memcpy(&sd, &((struct token_string *)tk)->string_data, sizeof(sd));
	s = sd.str;

	while (idx-- && s)
        s = get_next_token(s);

	if (s==NULL)
		return -1;

	len = get_token_len(s);
	if (len > size - 1)
        return -1;

	memcpy(dstbuf, s, len);
	dstbuf[len] = '\0';

	return 0;
}


int8_t get_help_string(parse_token_hdr_t * tk, char * dstbuf, uint8_t size) {
	struct token_string_data sd;
	const char * s;
	
	memcpy(&sd, &((struct token_string *)tk)->string_data, sizeof(sd));
	s = sd.str;

	if (s) {
        if(get_next_token(s)) {
            strncpy(dstbuf, MULTISTRING_HELP, size);
        }
		else {
			strncpy(dstbuf, FIXEDSTRING_HELP, size);
		}
	}
	else {
		strncpy(dstbuf, ANYSTRING_HELP, size);
	}
	
	dstbuf[size-1] = '\0';

	return 0;
}
