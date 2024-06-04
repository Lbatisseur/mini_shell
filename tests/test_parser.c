#include "../parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy




int test_parsing(char *commands[],char *expected_parsing[], int nb_tests)
{
    int i;
    int nb_test_success=0;
    TokenNode *root=NULL;
    Token *result=NULL;
    i=0;

    char *resultats[2]={"KO","OK"};
    BOOL is_test_ok=FALSE;

    while (i<nb_tests)
    {
        root=parse_line(commands[i]);
        result=createToken();
        concatenateTree(root,result);
        push_char(result,'#');
        push_char(result,'\0');
        is_test_ok=is_equal(result->str,expected_parsing[i]);
        if ( is_test_ok )
        {
            nb_test_success++;
        }
        printf("TEST %d\nParsing [%s]\nResult  [%s]\nExpected[%s]\n-->TEST %s\n",i+1,commands[i],result->str,expected_parsing[i], resultats[is_test_ok]);
        detroyTokenNode(root);
        destroyToken(result);
        printf("\n");
        i++;
    }

    return nb_test_success;
}



BOOL jeu_de_test1()
{
    printf("==============JEU DE TEST 1==============\n");
    int nb_success;
    char *commands[]={"echo toto", "      echo toto", "echo     toto", "echo 'toto   '","echo ' \" ; | < '"};
    char *expected[]={"#echo#toto#", "#echo#toto#", "#echo#toto#", "#echo#toto   #", "#echo# \" ; | < #"};
    nb_success=test_parsing(commands,expected,5);
    printf("==============%d/%d==============\n",nb_success,5);
    return !(nb_success==5);
}

int main()
{
    BOOL success=FALSE;

    success=jeu_de_test1()&&success;

    return !success;
}