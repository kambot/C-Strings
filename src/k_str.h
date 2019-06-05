#pragma once

//get the length of a string
int k_strlen(char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

//return the uppercase character
char k_chartoupper(char character) {
    int a = character;
    char charupper = a;
    if (a >= 'a' && a <= 'z') {
        charupper = a - 32;
    }
    return charupper;
}

//force a string to uppercase
void k_toupper(char *str, char *outstr) {
    int i = 0;
    for (; *str != '\0'; str++) {
        outstr[i++] = k_chartoupper(*str);
    }
    outstr[i] = '\0';
}


//copy a string into another
void k_strcopy(char *str, char *outstr) {
    int i = 0;
    for (; *str != '\0'; str++) {
        outstr[i++] = *str;
    }
    outstr[i] = '\0';
}


//compare two strings
int k_strcmp(char *str, char *str1) {
    for (; *str == *str1; ++str, ++str1) {
        if (*str == '\0') {
            return 0;
        }
    }
    return *str - *str1;
}

//concatenate two strings
void k_strappend(char *str, char *appendage, char *outstr) {
    int i = 0;
    for (; *str != '\0'; *str++)
        outstr[i++] = *str;
    for (; *appendage != '\0'; *appendage++)
        outstr[i++] = *appendage;
    outstr[i] = '\0';
}

//find and replace within a string
void k_strrep(char *str, char *find, char *replace, char *outstr) {

    int slen = k_strlen(str);
    int flen = k_strlen(find);
    int rlen = k_strlen(replace);

    if (flen == 0)
        return;

    int newpos = 0;

    for (int pos = 0; pos < slen; pos++) {

        int match = 1;
        if (str[pos] == find[0]) {

            for (int posj = pos; posj < pos + flen; posj++) {
                if (posj >= slen) {
                    match = 0;
                    break;
                }
                if (str[posj] == '\0') {
                    match = 0;
                    break;
                }
                if (str[posj] != find[posj - pos]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                for (int r = 0; r < rlen; r++) {
                    outstr[newpos++] = replace[r];
                }
                pos += (flen - 1);
                continue;
            }

        }

        outstr[newpos++] = str[pos];
    }
    outstr[newpos] = '\0';
}

//returns the number of occurences of a substring in a string
int k_strfind(char *str, char *find, int nested) {

    int slen = k_strlen(str);
    int flen = k_strlen(find);

    if (flen == 0)
        return 0;

    int matches = 0;

    for (int pos = 0; pos < slen; pos++) {

        int match = 1;
        if (str[pos] == find[0]) {

            for (int posj = pos; posj < pos + flen; posj++) {
                if (posj >= slen) {
                    return matches;
                }
                if (str[posj] == '\0') {
                    return matches;
                }
                if (str[posj] != find[posj - pos]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                matches++;
                if (!nested)
                    pos += (flen - 1);
                continue;
            }
        }
    }
    return matches;
}


//returns the starting index of a substring in a string
int k_strindex(char *str, char *find) {

    int slen = k_strlen(str);
    int flen = k_strlen(find);

    if (flen == 0)
        return -1;


    for (int pos = 0; pos < slen; pos++) {

        int match = 1;
        if (str[pos] == find[0]) {

            for (int posj = pos; posj < pos + flen; posj++) {
                if (posj >= slen) {
                    return -1;
                }
                if (str[posj] == '\0') {
                    return -1;
                }
                if (str[posj] != find[posj - pos]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return pos;
            }
        }
    }
    return -1;
}

//return a substring of a string
char *k_substr(char *str, int start, int end) {

    int slen = k_strlen(str);

    int size = 0;
    if (end >= start)
        size = end - start;
    else
        size = start - end;
    if (size < 0)
        size *= -1;
    size += 1;

    char *substr = calloc(size, sizeof(char));

    int v = end > start ? 1 : -1;

    int pos = start;
    int apos;
    int spos = 0;
    while (1) {
        apos = pos;
        if (pos >= slen) {
            apos = pos % slen;
        }
        if (pos < 0) {
            apos = pos % slen;
            if (apos < 0)
                apos += slen;
        }

        substr[spos++] = str[apos];

        if (pos == end)
            break;
        pos += v;
    }
    substr[spos] = '\0';
    return substr;
}


//string pad
char *k_strpad(char *str, char pad, int length, int side) {

    //side
    //0 = left pad
    //1 = right pad

    int slen = k_strlen(str);
    if (slen >= length)
        return str;

    char *padstr = calloc(length, sizeof(char));

    int numpads = length - slen;
    char *pads = calloc(numpads, sizeof(char));
    for (int i = 0; i < numpads; i++)
        pads[i] = pad;
    pads[numpads] = '\0';

    if (side != 1)
        k_strappend(pads, str, padstr); //left side
    else
        k_strappend(str, pads, padstr); //right side

    return padstr;

}



char** k_strsplit(char *str, char *split) {

    int slen = k_strlen(str);
    int splen = k_strlen(split);

    int matches = k_strfind(str, split, 0);

    char **result = NULL;
    result = malloc(slen - matches * splen + 2 * sizeof(char));

    if (slen == 0) {
        result[0] = calloc(1, sizeof(char));
        result[1] = NULL;
        return result;
    }


    int spos = 0; //starting position of substring
    int epos = k_strindex(str, split); //ending position of substring

    for (int i = 0; i <= matches; i++) {

        if (spos > slen)
            break;

        //get the ending position of the substring
        int epos0 = k_strindex(k_substr(str, spos, slen), split);

        if (epos0 == -1)
            epos = slen;
        else
            epos = epos0 + spos;
        
        char *buf = k_substr(str, spos, epos - 1);

        if (spos >= epos) {
            result[i] = calloc(1, sizeof(char));
            spos = epos + splen;
            continue;
        }

        if (epos0 == -1) {
            result[i] = calloc(k_strlen(buf), sizeof(char));
            k_strcopy(buf, result[i]);
        }

        result[i] = calloc(k_strlen(buf), sizeof(char));
        k_strcopy(buf, result[i]);

        spos = epos + splen;

    }
    result[matches + 1] = NULL;
    return result;
}
