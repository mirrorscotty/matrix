/**
 * @file xstrtok.c
 * Contains a modified version of the strtok function used when loading
 * CSV files and converting them to matricies.
 */

#include <string.h>

/**
 * Revised version of the strtok function.
 * This version returns "" if there are two deliminaters right next to each
 * other.
 * Code from: http://www.tek-tips.com/viewthread.cfm?qid=294161
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

