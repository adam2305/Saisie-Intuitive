#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "prediction.h"
#include <string.h>
#include <stdio.h>

//Fonction pour obtenir les trois propositions
int PropositionFreq(FrequentWordTab *hashtab,char* entry,Element* p1,Element* p2,Element* p3,int mode){
    long long value = HashFunctionFeequent(StrToUpper(entry));
    unsigned int index = 0;
    int n = CountZeros(value); //Récuperer le nombre de zero dans la clef de hashage
    Element* elem;
    Element** PossibleSolutions;
    PossibleSolutions = (Element**) malloc(1500000*sizeof(Element*));
    if(n>1){ // si il y a plus d'un zero on peut restreindre notre intervalle de sélection 
        int borneSup = 0;
        for(int k=0;k<n;k++){
            borneSup = borneSup + 9*pow(10,k);
        }
        for(int k=value;k<value+borneSup;k++){
            elem = hashtab->Elements[k];
            while(elem!= NULL){
                if(elem->personal){
                    PossibleSolutions[index] = elem;
                }
                index ++;
                elem = elem->next;
            }
        }
    }
    else{
        elem = hashtab->Elements[value];
        while(elem!=NULL){
            if(elem->personal)
                PossibleSolutions[index] = elem;
            index ++;
            elem = elem->next; 
        }
    }
    //Si il y a plus de 4 lettre a comparer on fait un tri supplementaire 
    if(strlen(entry)>4){
        SortByPrefix(PossibleSolutions,index,entry);
    }
    Element **tmp;
    Element **tmp2;
    tmp = (Element**) malloc(sizeof(Element*)*3);
    tmp2 = FindSimilarDictionnary(hashtab,entry);
    int ListSize = ListElementSize(PossibleSolutions,index);
    //On vérife le nombre de predicitons pour voir s'il faut aller en chercher dans le dictionnaire
    if(ListSize>=3){
        FindTreeLargest(PossibleSolutions,p1,p2,p3,index,mode);
    }
    else if(IsEmpty(tmp2,3)){
        free(elem);
        free(tmp2);
        return 0;
    }
    else{
        switch (ListSize){
        case 2:
            _three_not_nufirstll(PossibleSolutions,index,tmp,2);
            strcpy(p1->word,PossibleSolutions[0]->word);
            strcpy(p2->word,PossibleSolutions[1]->word);
            strcpy(p3->word,tmp2[0]->word);
            break;
        case 1:
            _three_not_nufirstll(PossibleSolutions,index,tmp,1);
            strcpy(p1->word,PossibleSolutions[0]->word);
            strcpy(p2->word,tmp2[0]->word);
            strcpy(p3->word,tmp2[1]->word);
            break;
        case 0:
            strcpy(p1->word,tmp2[0]->word);
            strcpy(p2->word,tmp2[1]->word);
            strcpy(p3->word,tmp2[2]->word);
            break;
        }
    }
    free(elem);
    //free(PossibleSolutions);
    free(tmp2);
    free(tmp);
    return 0;
}

//Fonction pour trouver tout les mots qui commencent par le paramètre word dans le dictionnaire fr
Element** FindSimilarDictionnary(FrequentWordTab *hashtab,char* word){
    int index = 0;
    int size = 0;
    Element* elem;
    Element** PSB;
    PSB = (Element**) malloc(150000*sizeof(Element*));
    for(int k=0;k<HASH_SIZE;k++){
        elem = hashtab->Elements[k];
        while(elem!=NULL){
            size = min(strlen(word),strlen(elem->word));
                if(strncmp(StrToUpper(elem->word),StrToUpper(word),size)==0 && elem->personal==false){
                    PSB[index] = elem;
                    index++;
            }
            if(index==3)
                break;
            elem = elem->next;
        }
    }
    return PSB;
}

//Fonction pour trier une liste soit en fonction de la fréquence des mots soit de leur dernière utilisation
void FindTreeLargest(Element** arr,Element* p1,Element* p2,Element* p3,unsigned int n,int mode) {
    Element **tmp;
    tmp = (Element**) malloc(sizeof(Element*)*n);
    _three_not_nufirstll(arr,n,tmp,3);
    Element* elem1;
    Element* elem2; 
    Element* elem3;
    elem1 = (Element*) malloc(sizeof(Element));
    elem2 = (Element*) malloc(sizeof(Element));
    elem2 = (Element*) malloc(sizeof(Element));
    elem1 = tmp[0];
    elem2 = tmp[1];
    elem3 = tmp[2];
    free(tmp);
    if(mode == 0){
        for (int i=1;i<n;i++){
            if(arr[i]!=NULL){
                if (arr[i]->freq > elem1->freq) {
                    elem3 = elem2;
                    elem2 = elem1;
                    elem1 = arr[i];
                }
                else if (arr[i]->freq > elem2->freq) {
                    elem3 = elem2;
                    elem2 = arr[i];
                }
                else if (arr[i]->freq > elem3->freq) {
                    elem3 = arr[i];
                }
            }
        }
    }
    else if(mode==1){
         for (int i=1;i<n;i++){
            if(arr[i]!=NULL){
                if (arr[i]->time > elem1->time) {
                    elem3 = elem2;
                    elem2 = elem1;
                    elem1 = arr[i];
                }
                else if (arr[i]->time > elem2->time) {
                    elem3 = elem2;
                    elem2 = arr[i];
                }
                else if (arr[i]->time > elem3->time) {
                    elem3 = arr[i];
                }
            }
        }
    }
    strcpy(p1->word,elem1->word);
    strcpy(p2->word,elem2->word);
    strcpy(p3->word,elem3->word);
}

//Fonction qui compte le nombre de zeros consécutis dans un intger à partir de la droite
int CountZeros(long long num){
    int count = 0;
    while (num % 10 == 0){
        count++;
        num /= 10; 
    }
    return count;
}

//Fonction qui trie les mots et garde ceux qui ressemblent à entry
void SortByPrefix(Element** list,unsigned int n,char* entry){ 
    int length_entry = strlen(entry);
    char *ENTRY = StrToUpper(entry);
    for(int k=0;k<n;k++){
        if(list[k]!=NULL){
            if(strncmp(list[k]->word,ENTRY,min(length_entry,strlen(list[k]->word)))!=0)
                list[k] = NULL; 
        }   
    }
}

//Fonction pour avoir min entre a et b
int min(int a, int b){
    return (a < b) ? a : b;
}

//Fonction pour obtenir les trois premiers élement non nuls d'un tableau
void _three_not_nufirstll(Element** arr, int size, Element** out_arr,int n) {
    int count = 0;
    for (int i = 0; i < size && count < n; i++) {
        if (arr[i] != NULL) {
            out_arr[count] = arr[i];
            count++;
        }
    }
    for(int k=0;k<n;k++){
        arr[k] = out_arr[k];
    }
}

//Fonction pour compter le nombre d'élements non nuls dans un tableau
int ListElementSize(Element** arr,long index){
    long res=0;
    for(int k=0;k<index;k++){
        if(arr[k]!=NULL)
            res++;
    }
    return res;
}

//Fonction pour vérifier si un tableau est vide
bool IsEmpty(Element** arr,long size){
    bool res = true;
    for(int k=0;k<size;k++){
        if(arr[k]!=NULL){
            res = false;
            break;
        }
    }
    return res;
}

//Fonction pour changer le dernier mot d'un string
void changeLastWord(char *str,char *newWord) {
    char *lastSpace = strrchr(str, ' '); 
    if (lastSpace == NULL){
        strcpy(str,newWord);
    } 
    else{
        char newWordBuf[strlen(newWord) + 1];
        strcpy(newWordBuf, newWord);
        int lastWordLen = strlen(lastSpace + 1);
        int newWordLen = strlen(newWord);
        if (newWordLen <= lastWordLen) {
            strcpy(lastSpace + 1, newWordBuf);
        } else {
            memmove(lastSpace + newWordLen - lastWordLen + 1, lastSpace + 1, strlen(lastSpace + 1) + 1);
            strncpy(lastSpace + 1, newWordBuf, newWordLen);
        }
    }
    
}

//Fonction pour modfier l'etat d'un element dans la table de hachage
void UpdateState(FrequentWordTab *hashtab, char *word){
    if(CheckExistencePersonal(hashtab,StrToUpper(word))){
        char mot[strlen(word)];
        strcpy(mot,StrToUpper(word));
        long long key = HashFunctionFeequent(mot);
        Element *curr;
        curr = hashtab->Elements[key];
        while(curr!=NULL){
            if(strcmp(curr->word,mot)==0){
            curr->freq = curr->freq + 1;
            curr->time = time(NULL);
            }
            curr = curr->next;
        }
    }
    else if(CheckExistence(hashtab,StrToUpper(word))){
        InsertElement(hashtab,word,true);
    }
}

//Fonction pour récupérer tous les mots d'une phrase
void read_words(FrequentWordTab *table,char *sentence) {
    char *token;
    sentence[strlen(sentence)-1] = '\0'; 
    token = strtok(sentence, " "); 
    while (token != NULL) {
        UpdateState(table,token);
        token = strtok(NULL, " "); 
    }
}


