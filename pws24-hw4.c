/*
 * pws24-hw4.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Patrick Stevens
 */
 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct Item {
    char item[30];
    int quan;
    float price;
    float total;
};

struct Customer {
    char name[30];
    int quan;
    struct Item items[10];
    float total;
};

int sortItems(struct Customer *customer);
int sortCust(struct Customer *customer, int customerOrder);
int ArrangeCust(struct Customer *customer1, struct Customer *customer2);
int ArrangeItem(struct Item *item1, struct Item *item2);


int getOrder(struct Customer *customer, int customerOrder) {
    int i = 0, j = 0;

    while(i < customerOrder){
        printf("\ncustomer:<%s><%.2f>\n", customer[i].name, customer[i].total);
        for (j = 0; j < customer[i].quan; j++) {
            printf("          items:<%s><%d><%.2f><%.2f>\n",
                    customer[i].items[j].item,
                    customer[i].items[j].quan,
                    customer[i].items[j].price,
                    customer[i].items[j].total
                    );
        }
        i++;
    }
    return 0;
}

int init(struct Customer *customer) {
    int i = 0, j = 0;
    for (i = 0; i < 20; i++) {
        customer[i].quan = 0;
        while (j < 10) {
            customer[i].items[j].quan = 0;
            customer[i].items[j].price = 0.0;
            j++;
        }
    }
    
    return 0;
}

int readFile(struct Customer *customer, int *customerNum) {
    FILE * file;
    if ((file = fopen("hw4input.txt", "rt")) == NULL) {
        printf("Can't open");
        return -1;
    }
    int i = 0;
    struct Customer *temp = (struct Customer*) malloc(sizeof (struct Customer));
    char p;
    int stop = 0;
    while (1) {
        stop = fscanf(file, "%s %d %s %c%f",
                (temp->name),
                &(temp->items[temp->quan].quan),
                (temp->items[temp->quan].item),
                &(p),
                &(temp->items[temp->quan].price));
        if (stop < 0)
            break;
        
        for (i = 0; i < *customerNum; i++) {
            if (strcmp(customer[i].name, temp->name) == 0) {
                customer[i].items[customer[i].quan].quan = temp->items[temp->quan].quan;
                strcpy(customer[i].items[customer[i].quan].item, temp->items[temp->quan].item);
                customer[i].items[customer[i].quan].price = temp->items[temp->quan].price;
                customer[i].quan++;
                break;
            }
        }
        if (i == *customerNum) {
            strcpy(customer[i].name, temp->name);
            customer[i].items[customer[i].quan].quan = temp->items[temp->quan].quan;
            strcpy(customer[i].items[customer[i].quan].item, temp->items[temp->quan].item);
            customer[i].items[customer[i].quan].price = temp->items[temp->quan].price;
            customer[i].quan++;
            (*customerNum)++;
        }
    }
    return 0;
}

int outfileTime(struct Customer *customer, int customerOrder) {
    int i = 0, j = 0;
    FILE * file = fopen("hw4time.txt", "w");
 
    while(i < customerOrder){
        fprintf(file, "\n%s\n", customer[i].name);
        for (j = 0; j < customer[i].quan; j++) {
            fprintf(file, "%s %d $%.2f\n",
                    customer[i].items[j].item,
                    customer[i].items[j].quan,
                    customer[i].items[j].price
                    );
        }
        i++;
    }
    return 0;
}

int OutfileMoney(struct Customer *customer, int customerOrder) {
    int i = 0, j = 0;
    FILE * file = fopen("hw4money.txt", "w");
    
    while(i < customerOrder){
        fprintf(file, "\n%s, Total Order = $%.2f\n",
                customer[i].name, customer[i].total);
        for (j = 0; j < customer[i].quan; j++) {
            fprintf(file, "%s %d $%.2f, Item Value = $%.2f\n",
                    customer[i].items[j].item,
                    customer[i].items[j].quan,
                    customer[i].items[j].price,
                    customer[i].items[j].total
                    );
        }
        i++;
    }
    return 0;
}

int sort(struct Customer *customer, int customerOrder) {
    int i = 0, j = 0;
    for (i = 0; i < customerOrder; i++) {
        customer[i].total = 0;
        for (j = 0; j < customer[i].quan; j++) {
            customer[i].items[j].total =
                    customer[i].items[j].quan * customer[i].items[j].price;
            customer[i].total += customer[i].items[j].total;
        }
    }
    for (i = 0; i < customerOrder; i++) {
        sortItems(&customer[i]);
    }
    sortCust(customer, customerOrder);
    return 0;
}

int sortItems(struct Customer *customer) {
    int i = 0, j = 0;

    while(i < customer->quan){
        for (j = customer->quan - 1; j > i; j--) {
            if (customer->items[j].total > customer->items[i].total) 
                ArrangeItem(&(customer->items[j]), &(customer->items[i]));
            
        }
        i++;
    }
    return 0;
}

int sortCust(struct Customer *customer, int customerOrder) {
    int i = 0, j = 0;
        while(i<customerOrder){
        for (j = customerOrder - 1; j > i; j--) {
            if (customer[j].total > customer[i].total) {
                ArrangeCust(&customer[i], &customer[j]);
            }
        }
        i++;
    }
    return 0;
}

int ArrangeCust(struct Customer *customer1, struct Customer *customer2) {
    int i = 0;
    struct Customer *customer = (struct Customer*) malloc(sizeof (struct Customer));
    
    strcpy(customer->name, customer1->name);
    customer->quan = customer1->quan;
    customer->total = customer1->total;
    
    for (i = 0; i < customer->quan; i++) {
        ArrangeItem(&(customer->items[i]), &(customer1->items[i]));
    }
    strcpy(customer1->name, customer2->name);
    customer1->quan = customer2->quan;
    customer1->total = customer2->total;
    
    for (i = 0; i < customer1->quan; i++) {
        ArrangeItem(&(customer1->items[i]), &(customer2->items[i]));
    }
    strcpy(customer2->name, customer->name);
    customer2->quan = customer->quan;
    customer2->total = customer->total;
    
    for (i = 0; i < customer2->quan; i++) {
        ArrangeItem(&(customer2->items[i]), &(customer->items[i]));
    }

    return 0;
}

int ArrangeItem(struct Item *item1, struct Item *item2) {
    struct Item *item = (struct Item*) malloc(sizeof (struct Item));

    strcpy(item->item, item1->item);
    item->quan = item1->quan;
    item->price = item1->price;
    item->total = item1->total;

    strcpy(item1->item, item2->item);
    item1->quan = item2->quan;
    item1->price = item2->price;
    item1->total = item2->total;

    strcpy(item2->item, item->item);
    item2->quan = item->quan;
    item2->price = item->price;
    item2->total = item->total;

    return 0;
}



int main(void) {

    struct Customer customer[20];
    int customerNum = 0;
    init(customer);
    if (readFile(customer, &customerNum) < 0)
        return 0;
    outfileTime(customer, customerNum);
    sort(customer, customerNum);
    OutfileMoney(customer, customerNum);

    return 0;
}
