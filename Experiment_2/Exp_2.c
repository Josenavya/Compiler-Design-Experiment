#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

FILE *fp;

char delim[14] = {
    ' ', '\t', '\n', ',', ';', '(', ')',
    '{', '}', '[', ']', '#', '<', '>'
};

char oper[7] = {
    '+', '-', '*', '/', '%', '=', '!'
};

char key[21][12] = {
    "int", "float", "char", "double", "bool",
    "void", "extern", "unsigned", "goto",
    "static", "class", "struct", "for",
    "if", "else", "return", "register",
    "long", "while", "do"
};

char predirect[2][12] = {
    "include",
    "define"
};

char header[6][15] = {
    "stdio.h",
    "conio.h",
    "malloc.h",
    "process.h",
    "string.h",
    "ctype.h"
};

void skipcomment();
void analyze();
void check(char[]);
int isdelim(char);
int isop(char);

int fop = 0, numflag = 0, f = 0;
char c, ch, sop;

int main()
{
    char fname[50];

    printf("\nEnter filename : ");
    scanf("%49s", fname);

    fp = fopen(fname, "r");

    if (fp == NULL)
    {
        printf("\nThe file doesn't exist.");
    }
    else
    {
        analyze();
        fclose(fp);
    }

    printf("\nEnd of file\n");

    getch();
    return 0;
}

void analyze()
{
    char token[50];
    int j = 0;

    while (!feof(fp))
    {
        c = getc(fp);

        if (c == '/')
        {
            skipcomment();
        }
        else if (c == '\"')
        {
            while ((c = getc(fp)) != '\"');
        }
        else if (isalpha(c))
        {
            if (f == 0)
            {
                token[j] = '\0';
                check(token);
                numflag = 0;
                j = 0;
                f = 0;
            }

            token[j] = c;
            j++;
            f = 1;
        }
        else if (isalnum(c))
        {
            token[j] = c;
            j++;
        }
        else
        {
            if (numflag == 0)
                numflag = 1;

            token[j] = c;
            j++;

            if (isdelim(c))
            {
                if (numflag == 1)
                {
                    token[j] = '\0';
                    check(token);
                    numflag = 0;
                }

                if (f == 1)
                {
                    token[j] = '\0';
                    numflag = 0;
                    check(token);
                }

                j = 0;
                f = 0;

                printf("\nDelimiter\t %c", c);
            }
            else if (isop(c))
            {
                if (numflag == 1)
                {
                    token[j] = '\0';
                    check(token);
                    numflag = 0;
                    j = 0;
                    f = 0;
                }

                if (fop == 1)
                {
                    token[j] = '\0';
                    j = 0;
                    f = 0;
                    check(token);

                    fop = 0;

                    printf("\nOperator\t %c%c", c, sop);
                }
                else
                {
                    printf("\nOperator\t %c", c);
                }
            }
            else if (c == '.')
            {
                token[j] = c;
                j++;
            }
        }
    }
}

int isdelim(char c)
{
    int i;

    for (i = 0; i < 14; i++)
    {
        if (c == delim[i])
            return 1;
    }

    return 0;
}

int isop(char c)
{
    int i, j;
    char ch1;

    for (i = 0; i < 7; i++)
    {
        if (c == oper[i])
        {
            ch1 = getc(fp);

            for (j = 0; j < 6; j++)
            {
                if (ch1 == oper[j])
                {
                    fop = 1;
                    sop = ch1;
                    return 1;
                }
            }

            ungetc(ch1, fp);
            return 1;
        }
    }

    return 0;
}

void check(char t[])
{
    int i;

    if (numflag == 1)
    {
        printf("\nNumber\t\t %s", t);
        return;
    }

    for (i = 0; i < 2; i++)
    {
        if (strcmp(t, predirect[i]) == 0)
        {
            printf("\nPreprocessor Directive\t %s", t);
            return;
        }
    }

    for (i = 0; i < 6; i++)
    {
        if (strcmp(t, header[i]) == 0)
        {
            printf("\nHeader File\t %s", t);
            return;
        }
    }

    for (i = 0; i < 21; i++)
    {
        if (strcmp(key[i], t) == 0)
        {
            printf("\nKeyword\t\t %s", key[i]);
            return;
        }
    }

    printf("\nIdentifier\t %s", t);
}

void skipcomment()
{
    ch = getc(fp);

    if (ch == '/')
    {
        while ((ch = getc(fp)) != '\n' && ch != EOF);
    }
    else if (ch == '*')
    {
        while (f == 0)
        {
            ch = getc(fp);

            if (ch == '*')
            {
                c = getc(fp);

                if (c == '/')
                    f = 1;
            }

            if (c == EOF)
                break;
        }

        f = 0;
    }
}