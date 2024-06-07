#ifndef _PARSER_H
#define _PARSER_H

//3 Mode de parsing
typedef enum _ParsingMode 
{
  UNQUOTED = 0,         //Pas de guillemet 
  SINGLEQUOTED,     //Entre guillemets simple
  DOUBLEQUOTED      //Entre guillemets double
} ParsingMode; 

//Pour rendre le code lisible, un enum pour les boolens VRAI/FAUX
typedef enum _BOOL
{
    FALSE = 0,
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
    int size; //Nombre de tokens
    int mem_size; // Taille du tableau
} TokenTable;

typedef struct _TokenNode
{
    TokenTable *table; 
    struct _TokenNode *left; 
    struct _TokenNode *right;
} TokenNode;

/**
 * Manipuler les tokens
 * 
*/

//Créer un token (avec un taille de 10 caractères pas défaut)
Token *createToken();

//Détruit un token
void destroyToken(Token *t);

//Ajout un caractère à un token (agrandi et réalloue si nécessaire)
void push_char(Token *t,char c);

//Renvoie TRUE si 2 chaine sont identiques
BOOL is_equal(char* a,char *b);

/**
 * Manipuler les arbres d'évaluation
 * 
*/

//Créer un arbre à  évaluation 
TokenNode *createTokenNode();

//Détruire un arbre d'évalutation
void detroyTokenNode(TokenNode *nd);

//Afficher sur la console l'arbre d'évaluation
void printTokenNode(TokenNode *nd);

//Concatène les tokens 
void concatenateTree(TokenNode *nd,Token *result);


//Prend une ligne de commande en paramètre 
//Renvoie un tableau dynalmique de tokens 
//Les Tokens doivent être "free" ainsi que le tableau par l'appelant
TokenNode*parse_line(char *line);

#endif
