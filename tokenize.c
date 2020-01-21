
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "vec.h"
# include "tokenize.h"

// read_* adapted from lecture 9 class notes
char*
read_text(const char* text, int ii)
{
    int nn = 0;
    int length = strlen(text);
    char search = text[ii + nn];
    while ((isalnum(search) || ispunct(search)) && search != '<' && search != '>' && search != '|' && search != '&' && search != ';' && search != ' '  &&  nn < length ){
        ++nn;
        search = text[ii+nn];
    }    

    char* token = malloc(nn+1);
    memcpy(token, text + ii, nn);
    token[nn]= 0;
    return token;
}

char*
read_op(const char* text, int ii)
{
    int nn = 0;
    char search = text[ii + nn];
    
    // Operator can be at most 2 characters
    while((search == '<' ||search == '>' || search == '|' || search == '&' || search == ';') && nn < 2){
        ++nn;
        search = text[ii + nn];
    }

    char* token = malloc(nn+1);
    memcpy(token, text + ii, nn);
    token[nn]= 0;
    return token;
}

char*
read_symbol(const char* text, int ii)
{
    int nn = 0;
    while (!isspace(text[ii+nn])){
        ++nn;
    }

    char* token = malloc(nn+1);
    memcpy(token, text + ii, nn);
    token[nn]= 0;
    return token;
}


// Adapted from Class 9 Lecture notes
vec*
tokenize(const char* text)
{
    vec* vector = make_vec();

    int length = strlen(text);
    int ii = 0;
    while (ii < length) {
        if (isspace(text[ii])) {
            ++ii;
            continue;
        }
        // Alphanumeric character
        if (isalnum(text[ii])){
            char* token = read_text(text, ii);
            push_vec(vector, token);
            ii += strlen(token); 
            free(token);
            continue;
        }
        
        // Operator characer
        if (text[ii] == '<' || text[ii] == '>' || text[ii] == '|' || text[ii] == '&' || text[ii] == ';') {
            // see which each operator is     
            char* token = read_op(text, ii);
            push_vec(vector, token);
            ii += strlen(token);
            free(token);
            continue;
        }

        // Punctuation character
        if (ispunct(text[ii])) {
            char* token = read_symbol(text, ii);
            push_vec(vector, token);
            ii += strlen(token); 
            free(token);
            continue;
        }
    }
    return vector;
}

