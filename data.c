#include "data.h"

//Fonction pour initialiser la table de hachage
void InitializeFrequentWordTab(FrequentWordTab *hashtab){
    hashtab->size = HASH_SIZE;
    hashtab->Elements = (Element **) malloc(sizeof(Element *)*HASH_SIZE);
    for(long long k=0;k<HASH_SIZE;k++){
        hashtab->Elements[k] = NULL;
    } 
}

//Fonction qui concatène deux entiers : ex f(12,15) -> 1215
long long Int_Concatenate(long long n1,long long n2){
    char* res = (char*) malloc(sizeof(char)*(snprintf(NULL, 0, "%lld%lld", n1, n2) + 1));
    sprintf(res, "%lld%lld", n1, n2);
    return (long long) atoi(res);
}

//Fonction de hachage qui recupère le code ASCII des 4 premières lettres 
// et concatène ces valeurs pour obtenir une clef de hachage
long long HashFunctionFeequent(char* entry){
    char word[LENGTH_WORD];
    strcpy(word,StrToUpper(entry));
    long long res = (long long) word[0];
	if(strlen(word)>=4){
        for(int k=1;k<4;k++){
            res = Int_Concatenate(res,(long long) word[k]);
        }
	}
	else {
		for(int k=1;k<strlen(word);k++){
        	res = Int_Concatenate(res,(long long) word[k]);
    	}
		for(int k=strlen(word);k<4;k++){
			res = Int_Concatenate(res,0);
            res = Int_Concatenate(res,0);
		}
	}
    if (res>HASH_SIZE){
         res =res/10;
    }
    return res;
}

// Fonction pour ajouter un élement dans la table de hachage
void InsertElement(FrequentWordTab *hashtab,char* word,bool pers){
    char mot[strlen(word)];
    strcpy(mot,StrToUpper(word));
    long long key = HashFunctionFeequent(mot);
    Element *elem = (Element*) malloc(sizeof(Element));
    strcpy(elem->word,mot);
    elem->personal = pers;
    elem->freq = 1;
    elem->time = time(NULL);
    elem->next = hashtab->Elements[key];
    hashtab->Elements[key] = elem;
}

//Fonction pour supprimer un élement de la table de hachage 
void RemoveElement(FrequentWordTab *hashtab,char* word){
    char mot[strlen(word)];
    strcpy(mot,StrToUpper(word));
    long long key = HashFunctionFeequent(mot);
    Element *curr;
    curr = hashtab->Elements[key];
    while(curr!=NULL){
        if(strcmp(curr->word,mot)==0){
            curr->personal=false;
        }
        curr = curr->next;
    }
    free(curr);
}

//Fonction pour importer les mots du dictionnaire francais dans la table de hachage
void AddAllDictionnary(FrequentWordTab *hashtab,char* dictfr){
    FILE* f;
    f = fopen(dictfr,"r");
    if(f!=NULL){
        char word[LENGTH_WORD];
        while(fscanf(f,"%s",word)==1){
            InsertElement(hashtab,StrToUpper(word),false);
        }
    }
    fclose(f);
}

//Fonction pour ajouter les mots du dictionnaire francais 
void AddPersonalDict(FrequentWordTab *hashtab,char* fichier){
    int i = 0;
    FILE *f;
    f = fopen(fichier,"r");
    if(f!=NULL){
        char word[LENGTH_WORD];
        long long value;
	    Element *element;
        while(fscanf(f,"%s",word)==1){
            char *WORD = StrToUpper(word);
            value = HashFunctionFeequent(WORD);
            element = hashtab->Elements[value];
            if(CheckExistence(hashtab,WORD)){ //Vérifie si le mot existe déjà 
                while(element!=NULL && strcmp(StrToUpper(element->word),WORD)!=0){
                    element = element->next; 
                }//Mettre à jour les statistiques du mot
                element->personal = true;
                element->freq = element->freq + 1; 
            }
            else{
                InsertElement(hashtab,word,true);
            }
        }
    }
    fclose(f);
}

//Fonction pour générer un string contenant tout les mots du dictionnaire français 
char* ShowDictionnary(FrequentWordTab *hashtab){
    char* text;
    char tmp[25];
    text = (char*) malloc(sizeof(char)*10000000000);
    Element *elem;
    elem = (Element*) malloc(sizeof(Element));
    for(int k=0;k<HASH_SIZE;k++){
        if(hashtab->Elements[k]!=NULL){
            elem = hashtab->Elements[k];
            while(elem!=NULL){
                strcpy(tmp,elem->word);
                strcat(tmp,"\n");
                strcat(text,tmp);
                strcpy(tmp,"");
                
                elem = elem->next;
            }
        }
    }
    return text;
    
}

//Fonction pour générer un string contenant tout les mots du dictionnaire personnel
char* ShowPersonalDictionnary(FrequentWordTab *hashtab){
    char* text;
    char* tmp1[5];
    char tmp[25];
    text = (char*) malloc(sizeof(char)*10000000000);
    unsigned int i = 0;
    Element *elem;
    elem = (Element*) malloc(sizeof(Element));
    for(int k=0;k<HASH_SIZE;k++){
        if(hashtab->Elements[k]!=NULL){
            elem = hashtab->Elements[k];
            while(elem!=NULL){
                if(elem->personal){
                    strcpy(tmp,elem->word);
                    strcat(tmp,"    ");
                    sprintf(tmp1, "%d", elem->freq);
                    strcat(tmp,tmp1);
                    strcat(tmp,"\n");
                    strcat(text,tmp);
                    strcpy(tmp,"");
                    i++;
                }
                elem = elem->next;
            }
        }
    }
    return text;
}

//Fonction pour mettre en majuscule un string
char* StrToUpper(char* str) {
    char* result = (char*) malloc(strlen(str) + 1);
    for (int i = 0; i < strlen(str); i++) {
        result[i] = toupper(str[i]);
    }
    result[strlen(str)] = '\0';
    return result;
}

//Fonction pour vérifier l'existence d'un mot dans le dictionnaire français
bool CheckExistence(FrequentWordTab *hashtab, char* word){
    long long value = HashFunctionFeequent(word);
    Element *elem = hashtab->Elements[value];
    bool found = false;
    while(found==false && elem!=NULL){
        found = (strcmp(StrToUpper(word),elem->word) == 0);
        elem = elem->next;
    }
    return found;
}

//Fonction pour vérifier l'existence d'un mot dans le dictionnaire personnel 
bool CheckExistencePersonal(FrequentWordTab *hashtab, char* word){
    long long value = HashFunctionFeequent(word);
    Element *elem = hashtab->Elements[value];
    bool found = false;
    while(found==false && elem!=NULL){
        found = (strcmp(StrToUpper(word),elem->word) == 0 && elem->personal==true);
        elem = elem->next;
    }
    return found;
}

//Fonction pour récuperer le dernier mot d'une phrase
char* get_last_word(char* sentence) {
    char* last_word = NULL;
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        last_word = token;
        token = strtok(NULL, " ");
    }
    return last_word;
}

//Fonction pour modifer un mot déjà existent dans le dictionnare
void modifier(FrequentWordTab *hashtab, char *word1,char *word2){
    RemoveElement(hashtab,word1);
    if(CheckExistence(hashtab,StrToUpper(word2))==false)
        InsertElement(hashtab,StrToUpper(word2),true);
}

//Fonction pour mettre un string en minuscul
void to_lower(char *str){
    while (*str != '\0') {
        *str = tolower(*str);
        str++;
    }
}




