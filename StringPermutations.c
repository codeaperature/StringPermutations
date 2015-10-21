//
//  https://www.codeeval.com/open_challenges/14/
//  StringPermutations
//
//  Created by Stephan Warren on 4/11/15.
//  Copyright (c) 2015 Stephan Warren. All rights reserved.
//

/*
 
 Challenge Description:
 
 Write a program which prints all the permutations of a string in alphabetical order. We consider that digits < upper case letters < lower case letters. The sorting should be performed in ascending order.
 Input sample:
 
 Your program should accept a file as its first argument. The file contains input strings, one per line.
 
 For example:
 
 hat
 abc
 Zu6
 
 
 Output sample:
 
 Print to stdout the permutations of the string separated by comma, in alphabetical order.
 
 For example:
 
 aht,ath,hat,hta,tah,tha
 abc,acb,bac,bca,cab,cba
 6Zu,6uZ,Z6u,Zu6,u6Z,uZ6
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char comma[] = ",";

void res(char * r, char s, char e)
{
    char a, b;
    for(a = s, b = e; a < b; a++, b--) {
        char temp = r[a];
        r[a] = r[b];
        r[b] = temp;
    }
}


void permute(char * str)
{
    printf("%s%s", comma, str);
    comma[0] = ',';
    char  len = (char) strlen(str);
    
    //find k
    char m = -1;
    char k = -1;
    for (char i = len - 2; i >= 0; i--) {
        if(str[i] < str[i + 1]) {
            k = i;
            break;
        }
    }
    
    //k found? if no, stop
    if(k != -1) {
        //find m
        for(char i = len - 1; i > k; i--) {
            if(str[i] > str[k]){
                m = i;
                break;
            }
        }
        
        //swap
        char tmp = str[k];
        str[k] = str[m];
        str[m] = tmp;
        
        //reverse from k + 1 to n
        res(str, k + 1, len - 1);
        permute(str);
    }
}



int compare(const void *a, const void *b)
{
    return *(const char *)a - *(const char *)b;
}

int main(int argc, const char * argv[])
{
    char str[10];
    FILE *file = fopen(argv[1], "r");
    while(fgets(str, 10, file)) {
        comma[0] = '\0';
//        printf("%s", str);
        
        char slen = strlen(str) - 1;
//        printf("Unsorted (len = %d): %s\n", slen, str);
        str[slen] = '\0';
        qsort(str, slen, sizeof(char), compare);
        
//        printf("Sorted: %s\n", str);
        //        permute(str, 0, slen );
        permute(str);
        printf("\n");

    }
    return 0;
}
