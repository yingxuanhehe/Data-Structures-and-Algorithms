#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);


int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
    int index = hash(key);
    int i;
    int count=0;
    int to_insert_next;
    int link_next;

    //check for full table
    for(i=0; i<TABLESIZE; i++)
    {
        if(hashTable[i].indicator == USED)
            count++;
    }

    if(count==TABLESIZE) //full table
        return TABLESIZE+1;

    //duplicate key
    if(HashFind(key, hashTable)!=-1)
        return -1;

    if(hashTable[index].indicator == EMPTY)
    {
        hashTable[index].key = key;
        hashTable[index].indicator = USED;
        return index;
    }

    else //USED
    {
        for(i=0; i<TABLESIZE; i++)
        {
            to_insert_next = hash(index+i);
            if(hashTable[to_insert_next].indicator == EMPTY)
                break;
         }
        hashTable[to_insert_next].key = key;
        hashTable[to_insert_next].indicator = USED;

        //to link back
        while(hashTable[index].next!=-1)
        {
            index = hashTable[index].next;
        }
        hashTable[index].next = to_insert_next;

        return to_insert_next;
    }
}

int HashFind(int key, HashSlot hashTable[])
{
    int i;

    for(i=0; i<TABLESIZE; i++)
    {
        if(hashTable[i].key == key) //if duplicate
            return i;
    }
    return -1;

}
