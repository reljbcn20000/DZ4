#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ScanString(void){
    int n=1;
    char *arr,c;
    arr = calloc(n+1, sizeof(char));

    int i = 0;
    while((c=getchar()) != ' '){
        if( ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')){ //[a-zA-Z0-9]
            char *temp_arr;
            temp_arr = calloc(n+1, sizeof(char));
            
            for(int j = 0; j < n; j++){
                temp_arr[j] = arr[j];
            }
            
            arr[n-1]=c;
            n++;
            i++;
        }
        else if(c == '\n'){
            return arr;
            
        }
    }
    arr[n-1]='\0';
    return arr;
}

int main(){
    printf("Kol-vo vershin: "); //string1
    int kolvo;
    scanf("%d",&kolvo);
    if (kolvo <= 0){
        printf("R U FUCKING SERIOUS?\n");
        exit(9);
    }
    
    char *name_elements[kolvo];
    int conn_elements[kolvo][kolvo];
    for(int i=0; i<kolvo; i++){
        for(int j=0; j<kolvo; j++){
            conn_elements[i][j] = 0;
        }
    }
    
    printf("Enter names of elements separated by spaces:\n"); //string2
    getchar();
        
    for(int i=0; i<kolvo; i++){
        name_elements[i] = ScanString();
        
        for (int j=0; j<i; j++){
            if( strcmp(name_elements[i], name_elements[j]) == 0){
                exit(9);
            }
        }
    }
            
    printf("Enter for each one connection separated by spaces\n"); // tut ne zabit' v konce problel!!!  //string3
    for(int i=0; i<kolvo; i++){
        printf("%d: ",i);
        _Bool flag=1;
        while(flag){
            char *compare;
            compare = ScanString();
            
            for(int j=0; j<kolvo; j++){
                if( strcmp(compare, name_elements[j]) == 0){
                    conn_elements[i][j]++;
                }
            }

            if(strcmp(compare, "") == 0){
                flag = 0;
            }
        }
    }
    
    printf("\n");  //string4
    _Bool relat_graph = 1;
    for(int i=0; i<kolvo; i++){
        _Bool temp_relat_graph = 0;
        for(int j=0; j<kolvo; j++){
            if(conn_elements[i][j] == 1)
                temp_relat_graph = 1;
            
            if(conn_elements[j][i] == 1)
                temp_relat_graph = 1;
        }
        if(temp_relat_graph == 0)
            relat_graph=0;
    }
    if(relat_graph == 0){
        printf("unrelated graph\n"); //string5
    } else {
        printf("related graph\n"); //string6

    }

    for(int i=0; i<kolvo; i++) {
        printf("%s\t", name_elements[i]);
        for (int j=0; j<kolvo; j++) {
            printf("%d ", conn_elements[i][j]);
        }
        printf("\n");
    }
    
    int addr = -1;
    _Bool flag=1;
    while(flag){
        printf("Enter name of element which you want to delete:\n"); //string10
        char *compare;
        compare = ScanString();
        for(int i=0; i<kolvo; i++){
            if( strcmp(compare, name_elements[i]) == 0){
                addr = i;
                i = kolvo;
            }
        }
        if(addr == -1){
            printf("[!] Couldn't find any element with this name, try one more time\n"); //string11
        } else {
            flag = 0;
        }
    }
    if(kolvo-1 < 1){
        printf("FUCK U DELETE ALL!!!\n");                   //string12
        printf("U DONT NEED ME ANYMORE!!!\n");              //string13
        printf("I GONNA SHUTDOWN!!!\n");                    //string14
        printf("GOODBYE THIS FUCKING CRUEL WORLD!!!\n");    //string15
        exit(0);
    }
    char *new_name_elements[kolvo-1];
    int **new_conn_elements= calloc(kolvo-1, sizeof(int*));
    for(int i=0; i<kolvo; i++){
        new_conn_elements[i] = calloc(kolvo-1, sizeof(int));
    }
    
    for(int i=0; i<kolvo; i++){
        if(i < addr){
            new_name_elements[i] = name_elements[i];
            for(int j=0; j<kolvo; j++){
                if(j < addr){
                    new_conn_elements[i][j] = conn_elements[i][j];
                } else if(j > addr){
                    new_conn_elements[i][j-1] = conn_elements[i][j];
                }
            }
        } else if(i > addr){
            new_name_elements[i-1] = name_elements[i];
            for(int j=0; j<kolvo; j++){
                if(j < addr){
                    new_conn_elements[i-1][j] = conn_elements[i][j];
                } else if(j > addr){
                    new_conn_elements[i-1][j-1] = conn_elements[i][j];
                }
            }
        }
    }
    kolvo--;
    
    int stepen_elements[kolvo];
    for(int i=0 ;i<kolvo; i++){
        stepen_elements[i] = 0;
        for(int j=0; j<kolvo; j++){
            stepen_elements[i] += new_conn_elements[i][j];
            stepen_elements[i] += new_conn_elements[j][i];
        }
    }
    
    // bble_sort
    for (int i=0; i<kolvo-1; i++){
        for (int j=0; j<kolvo-i-1; j++){
            if (stepen_elements[j] > stepen_elements[j+1]){
                int temp = stepen_elements[j];
                stepen_elements[j] = stepen_elements[j+1];
                stepen_elements[j+1] = temp;
                
                char *temp1 = new_name_elements[j];
                new_name_elements[j] = new_name_elements[j+1];
                new_name_elements[j+1] = temp1;
                
                int *temp2 = new_conn_elements[j];
                new_conn_elements[j] = new_conn_elements[j+1];
                new_conn_elements[j+1] = temp2;
                
                for(int k=0; k<kolvo; k++){
                    int temp3 = new_conn_elements[k][j];
                    new_conn_elements[k][j] = new_conn_elements[k][j+1];
                    new_conn_elements[k][j+1] = temp3;
                }
            }
        }
    }
    // end

    for(int i=0; i<kolvo; i++) {
        printf("%s\t", new_name_elements[i]);
        for (int j=0; j<kolvo; j++) {
            printf("%d ", new_conn_elements[i][j]);
        }
        printf("\n");
    }
    
    kolvo++;
    char *string;
    string = calloc(2048, sizeof(char));
    char arrow[3] = "->";
    strcat(string, "echo digraph G{ '");
    for(int i=0; i<kolvo; i++){
        strcat(string, name_elements[i]);
        strcat(string, "; ");
    }
    for(int i=0; i<kolvo; i++){
        for(int j=0; j<kolvo; j++){
            for(int k=0; k<conn_elements[i][j]; k++){
                strcat(string, name_elements[i]);
                strcat(string, arrow);
                strcat(string, name_elements[j]);
                strcat(string, "; ");
            }
        }
    }
    strcat(string, "}' | dot -Tpng > ./graph.png"); //string8

    
    kolvo--;
    char *string2;
    string2 = calloc(2048, sizeof(char));
    strcat(string2, "echo digraph G{ '");
    for(int i=0; i<kolvo; i++){
        strcat(string2, new_name_elements[i]);
        strcat(string2, "; ");
    }
    for(int i=0; i<kolvo; i++){
        for(int j=0; j<kolvo; j++){
            for(int k=0; k<new_conn_elements[i][j]; k++){
                strcat(string2, new_name_elements[i]);
                strcat(string2, arrow);
                strcat(string2, new_name_elements[j]);
                strcat(string2, "; ");
            }
        }
    }
    strcat(string2, "}' | dot -Tpng > ./graph_after_delete.png"); //string9
    

    system(string);
    system(string2);
    system("open ./graph.png");
    system("open ./graph_after_delete.png");

    
    return 0;
}
