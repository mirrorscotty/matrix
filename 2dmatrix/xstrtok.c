#include <string.h>

/* Code from: http://www.tek-tips.com/viewthread.cfm?qid=294161 */
/*
 * strtok version that handles null fields
 */
char *xstrtok(line, delims)
char *line, *delims;
{
    static char *saveline = NULL;
    char *p;
    int n;

    if(line != NULL)
        saveline = line;

    /*
     *see if we have reached the end of the line
     */
    if(saveline == NULL || *saveline == '\0')
    return(NULL);
    /*
     *return the number of characters that aren't delims
     */
    n = strcspn(saveline, delims);
    p = saveline; /*save start of this token*/

    saveline += n; /*bump past the delim*/

    if(*saveline != '\0') /*trash the delim if necessary*/
        *saveline++ = '\0';

    return(p);
}

