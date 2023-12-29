#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define LENGTH_WORD 25 //taille maximale d'un mot
#define HASH_SIZE 99999999 //taille de la table de hashage

//Structure décrivant un mot 
typedef struct element{
    char word[LENGTH_WORD];
    unsigned int freq;
    time_t time;
    bool personal; //oui ou non dans le dictionnaire personnel
    struct element *next;
} Element;

//Structure de la table de hashage
typedef struct frequentWordTab{
    unsigned long long size;
    Element** Elements;
;
} FrequentWordTab;

void InitializeFrequentWordTab(FrequentWordTab *hashtab);
long long HashFunctionFeequent(char* word);
long long Int_Concatenate(long long n1,long long n2);
void InsertElement(FrequentWordTab *hashtab,char* word,bool pers);
void RemoveElement(FrequentWordTab *hashtab,char* word);
char* StrToUpper(char* str);
void AddAllDictionnary(FrequentWordTab *hashtab,char* dictfr);
void AddPersonalDict(FrequentWordTab *hashtab,char* fichier);
char* ShowDictionnary(FrequentWordTab *hashtab);
char* ShowPersonalDictionnary(FrequentWordTab *hashtab);
bool CheckExistence(FrequentWordTab *hashtab, char* word);
char* get_last_word(char* sentence);
void modifier(FrequentWordTab *hashtab, char *word1,char *word2);
void to_lower(char *str);
bool CheckExistencePersonal(FrequentWordTab *hashtab, char* word);

