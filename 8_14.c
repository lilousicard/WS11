#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ContactNode {
    struct ContactNode* next;
    char * contactName;
    char * contactPhoneNumber;
} ContactNode;

static ContactNode* queue = NULL;

void printContactNode(ContactNode *nod) {
    printf("Name: %s\nPhone number: %s\n", nod->contactName, nod->contactPhoneNumber);
}

void pushNode(char * name, char * phone){
    struct ContactNode* newNode = (ContactNode*) malloc(sizeof (ContactNode));
    newNode->contactName = strdup(name);
    newNode->contactPhoneNumber = strdup(phone);
    newNode->next=NULL;
    if (queue == NULL){
        queue = newNode;
    } else{
        struct ContactNode* t = queue;
        while (t->next!=NULL){
            t = t->next;
        }
        t->next = newNode;
    }
}

void printContact(){
    struct ContactNode* temp = queue;
    printf("CONTACT LIST\n");
    while(temp!=NULL){
        printContactNode(temp);
        temp = temp->next;
    }
}

void freeNode(struct ContactNode* node){
    free(node->contactName);
    free(node->contactPhoneNumber);
    free(node);
}

void freeLLHelper(struct ContactNode* node){
    if (node->next!=NULL){
        freeLLHelper(node->next);
    }
    freeNode(node);
}

void freeLinkedList(){
    freeLLHelper(queue);
}


int main(void) {

    size_t buf = 100;
    char * input = (char*) malloc (sizeof (char) *buf);
    char * name = (char*) malloc (sizeof (char) *buf);
    char * phone = (char*) malloc (sizeof (char) *buf);
    int index = 0;
    while (getline(&input,&buf,stdin)!=-1 && index<6){
        input[strlen(input)-1]=0;//remove new line symbol

        if (index%2==1){
            phone = strdup(input);
            pushNode(name,phone);
        }else{
            name = strdup(input);
        }

        index++;
    }

    printContact();

    freeLinkedList();
    free(input);
    free(name);
    free(phone);

    return 0;
}
