#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy

#include "mini_shell.h"


//3 Mode de parsing
typedef enum _ParsingMode {
  UNQUOTED=0,         //Pas de guillemet 
  SINGLEQUOTED,     //Entre guillemets simple
  DOUBLEQUOTED      //Entre guillemets double
} ParsingMode; 

//Pour rendre le code lisible, un enum pour les boolens VRAI/FAUX
typedef enum _BOOL
{
    FALSE=0,
    TRUE
} BOOL;


//Stucture pour nos tokens
typedef struct _token
{
    char *str;
    int size;
    int mem_size;
} Token;

//Tableau dynamique de pointeurs sur tokens
typedef struct _TokenTable
{
    Token **tokens;
    int size;
    int mem_size;
} TokenTable;

typedef struct _TokenNode
{
    TokenTable *table;
    struct _TokenNode *left;
    struct _TokenNode *right;
} TokenNode;


//Créer un token (avec un taille de 10 caractères pas défaut)
Token *createToken()
{
    Token *t=(Token *)malloc(sizeof(Token));
    t->mem_size=10;
    t->str=(char *)malloc(sizeof(char)*t->mem_size);
    t->size=0;
    return t;
}

void destroyToken(Token *t)
{
    free(t->str);
    t->size=0;
    t->mem_size=0;
}

//Ajout un caractère à un token (agrandi et réalloue si nécessaire)
void push_char(Token *t,char c)
{
    if(t->size >= t->mem_size )
    {
        char *old_str=t->str;
        t->mem_size*=2;
        t->str=(char *)malloc(sizeof(char)*t->mem_size);
        memcpy(t->str,old_str,t->size);
        free(old_str);
    }
    t->str[t->size]=c;
    t->size++;
}


TokenTable *createTokenTable()
{
    TokenTable *table=(TokenTable *)malloc(sizeof(TokenTable));
    table->mem_size=5;
    table->size=0;
    table->tokens=(Token **)malloc(sizeof(Token *)*table->mem_size);
    return table;
}


void push_token(TokenTable* table, Token *t)
{
    if(table->size >= table->mem_size )
    {
        char *old_tokens=t->str;
        table->mem_size*=2;
        table->tokens=(Token **)malloc(sizeof(Token *)*t->mem_size);
        memcpy(table->tokens,old_tokens,table->size);
        free(old_tokens);
    }

    push_char(t,'\0'); //Finalize token

    table->tokens[table->size]=t;
    table->size++;
}

void destroyTokenTable(TokenTable *table)
{
    int i=0;
    while(i<table->size)
    {
        destroyToken(table->tokens[i]);
        i++;
    }
    free(table);
}


TokenNode *createTokenNode()
{
    TokenNode *token_node=(TokenNode *)malloc(sizeof(TokenNode));
    token_node->table=createTokenTable();
    token_node->left=NULL;
    token_node->right=NULL;
    return token_node;
}


void detroyTokenNode(TokenNode *nd)
{
    if ( nd!=NULL)
    {
        destroyTokenTable(nd->table);
        detroyTokenNode(nd->left);
        detroyTokenNode(nd->right);
    }
}

BOOL is_equal(char* a,char *b)
{
    int i;
    i=0;
    while(a[i]!='\0'&&b[i]!='\0'&&a[i]==b[i])
    {
        i++;
    }
    return a[i]=='\0'&&b[i]=='\0' ? TRUE:FALSE;
}

void printTokenNode(TokenNode *nd)
{
    if(nd!=NULL)
    {
        printTokenNode(nd->left);
        printTokenNode(nd->right);
        int i=0;
        while(i<nd->table->size)
        {
            printf("%s#",nd->table->tokens[i]->str);
            i++;
        }
    }
}


void concatenateTree(TokenNode *nd,Token *result)
{
    int i;
    int j;
    if(nd!=NULL)
    {
        concatenateTree(nd->left,result);
        i=0;
        while(i<nd->table->size)
        {
            j=0;
            push_char(result,'#');
            while(j<(nd->table->tokens[i]->size-1))
            {
                push_char(result,nd->table->tokens[i]->str[j]);
                j++;
            }
            i++;
        }
        concatenateTree(nd->right,result);
    }
}



int is_special_unquote(char c)
{
    return (c==' '||c=='"'||c=='\''||c=='|'||c==';'||c=='<'||c=='>'||c=='\\'||c=='$');
}

int is_special_singlequote(char c)
{
    return (c=='\''||c=='\\');
}


int is_special_doublequote(char c)
{
    return (c=='"'||c=='\''||c=='$');
}



//Prend une ligne de commande en paramètre 
//Renvoie un tableau dynalmique de tokens 
//Les Tokens doivent être "free" ainsi que le tableau par l'appelant
TokenNode*parse_line(char *line)
{
    TokenNode *root=createTokenNode();
    TokenNode *current_node=root;

    int i=0;

    //O:UNQUOTED/1:SINGLEQUOTED/2:DOUBLEQUOTED
    // UNQUOTED : Pas de guillemet / SINGLEQUOTED : entre guillemet simple / DOUBLEQUOTED : entre guillemets double
    ParsingMode mode=UNQUOTED; 
    Token *token=NULL; //Token en cours 
    BOOL is_backslashed=FALSE; 
    while(line[i]!='\0')
    {
        char c=line[i];
        i++; 

        //Si ca n'est pas un caratère spéciale et qu'il n'a pas été baskslaché
        if ( (!is_backslashed) && (((mode==UNQUOTED) && !is_special_unquote(c)) || ((mode==SINGLEQUOTED) && !is_special_singlequote(c)) || ((mode==DOUBLEQUOTED) && !is_special_doublequote(c))))
        {
            if ( token==NULL)
            {
                token=createToken(); //Je créé le token si nécessaire
            }
            push_char(token,c); //J'ajoute le caractère courant
            is_backslashed=FALSE;
            continue;
        }

        //Traiter les caractère spéciaux
        if( c=='\\')
        {
            //Backslach est commun au 3 modes
            is_backslashed=TRUE;
            continue;
        }


        if (mode==SINGLEQUOTED) //Mode Simple Guillemets
        {
            // c=='\''
            mode=UNQUOTED;
            push_token(current_node->table,token);
            token=NULL;
            continue;
        }

        if (mode==DOUBLEQUOTED) //Mode Simple Guillemets
        {
            if( c=='$')
            {
                //TODO
            }
            else // c=='"'
            {
                mode=UNQUOTED;
                push_token(current_node->table,token);
                token=NULL;
            }
            continue;
        }

        //Mode UNQUOTED
        if ( c=='"' || c=='\'')
        {
            mode=(c=='"')? DOUBLEQUOTED : SINGLEQUOTED;
            continue;
        }

        if ( c=='$')
        {

            continue;
        }

        if ( c==' ' || c==';' || c=='|' || c=='<' || c== '\'' )
        {
            if ( token!=NULL )
            {
                push_token(current_node->table,token);
                token=NULL;
            }

            if ( 0)//c!=' ' )
            {
                current_node->left=createTokenNode();
                current_node->right=createTokenNode();

                //On permute la table entre le parent et l'enfant gauche
                TokenTable *tmp=current_node->table;
                current_node->table=current_node->left->table;
                current_node->left->table=tmp;

                //Ajout token 'c'
                token=createToken();
                push_char(token,c);
                push_token(current_node->table,token);
                token=NULL;

                current_node=current_node->right;
            }
        }
    }

    if ( token!=NULL )
    {
        push_token(current_node->table,token);
        token=NULL;
    }

    return root;
}


void test_parsing(char *commands[],char *expected_parsing[], int nb_tests)
{
    int i;
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
        printf("TEST %d\nParsing [%s]\nResult  [%s]\nExpected[%s]\n-->TEST %s\n",i+1,commands[i],result->str,expected_parsing[i], resultats[is_test_ok]);
        detroyTokenNode(root);
        destroyToken(result);
        printf("\n");
        i++;
    }
}


int main()
{
    char *commands[]={"echo toto", "      echo toto", "echo     toto", "echo 'toto   '","echo ' \" ; | < '"};
    char *expected[]={"#echo#toto#", "#echo#toto#", "#echo#toto#", "#echo#toto   #", "#echo# \" ; | < #"};

    test_parsing(commands,expected,5);
  
    return 0;
}