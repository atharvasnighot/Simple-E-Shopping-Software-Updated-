//Online Shopping System

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

FILE *fp, *fptr;
int totalBill = 0, productNum=0, categoryNum=0, flagUser=0;


struct ProductsOfSameCategory{
    char productName[15];
    int price;
    //int quantity;
};

struct ProductCategories{
    char categoryName[15];
    struct ProductsOfSameCategory products[10];
}category[10];

struct customerBill{
    char customerName[15];
    char customerEmail[15];
}bill;

typedef struct SinglyLinkedList{
    int productPrice;
    char* product;
    struct SinglyLinkedList* next;   
}*Cart;


Cart getnode(){
    Cart new1= NULL;
    new1 = malloc(sizeof(struct SinglyLinkedList));
    if(new1 ==NULL){
        printf("\n Memory not availble");
        exit(0);
    }
    new1->next =NULL;
    return new1;
}


void getDetails(){
    system("cls");

    printf("Enter your name: ");
    scanf("%s", &bill.customerName);
    printf("Enter your email-id: ");
    scanf("\n\n\n%s", &bill.customerEmail);
    printf("Welcome %s", bill.customerName);

    fp = fopen("UserData.txt","r");

    if(fp == NULL){
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else{
        int i=0, j=0;
        char tempName[15], tempId[15];

        while(fscanf(fp, "%s\t%s", &tempName, &tempId)!=EOF){
                if(strcmp(tempName, bill.customerName) == 0){
                    flagUser = 1;
                    break;
                }
        }
        fclose(fp);
    }
    if(flagUser == 0){
        fp = fopen("UserData.txt","a");
        fprintf(fp, "%s\t%s\n", bill.customerName, bill.customerEmail);
        fclose(fp);
    }
}


int welcome(){
    system("cls");
    printf("Welcome to Camera Store");
    printf("\nSelect Mode: \n1.Admin\n2.Customer\nEnter (1/2):\t");
    int choice;
    scanf("%d", &choice);
    return choice;
}


void printCategories(){
    for(int i=0;i<categoryNum;i++){
        printf("\n\nName of Category: ");
        printf("%d. %s", i+1, category[i].categoryName);
    }
    printf("\nWhich category would you like to shop?: ");
}


void printProducts(int i){
        printf("\n\nName of Category: ");
        printf("%s", category[i].categoryName);
        printf("\n Products of this category: ");
        for(int j=0; j<productNum; j++){
            printf("\n\t%d. Name of Product: ",j+1);
            printf("%s", category[i].products[j].productName);
            printf("\n\tPrice of Product: ");
            printf("%d", category[i].products[j].price);
        }
        printf("\nWhich Product would you like to buy?: ");

}


void printList(Cart temp){
    system("cls");
    printf("\nYour Cart: ");
    while(temp != NULL){
        printf("\nProduct: %s", temp->product);
        printf("\t\t\tPrice: %d", temp->productPrice);
        temp = temp->next;
    }
    printf("\n");
    printf("--------------------------------------------------------");
    printf("\nCustomer Name:\t\t\t\t%s\nCustomer E-mail:\t\t\t%s\nYour Total Bill:\t\t\t%d", bill.customerName, bill.customerEmail ,totalBill);
    
}


void coupon(Cart head){

    system("cls");
    char coupon[15];
    Cart temp= head;

    printf("Enter Coupon Code: ");
    scanf("%s", &coupon);

    char couponOne[15] = "GET10", couponTwo[15] = "NEWYEAR23";

    if(strcmp(coupon, couponOne) == 0){

        system("cls");
        printf("CONGRATULATIONS!\nYou got a 10 Per Cent Discount on your Total Bill.\n");
        printf("\nYour Cart: ");
        while(temp != NULL){
            printf("\nProduct: %s", temp->product);
            printf("\t\t\tPrice: %d", temp->productPrice);
            temp = temp->next;
        }
        float totalDiscount = totalBill * 10/100;
        totalBill = totalBill - (int) totalDiscount;
        printf("\n");
        printf("--------------------------------------------------------");
        printf("\nCustomer Name:\t\t\t\t%s\nCustomer E-mail:\t\t\t%s\nTotal Discount:\t\t\t\t%.2f\nYour Total Bill:\t\t\t%d", bill.customerName, bill.customerEmail ,totalDiscount, totalBill);
    }
    else if(strcmp(coupon, couponTwo) == 0){
        system("cls");
        printf("CONGRATULATIONS!\nYou'll get a free UV lens filter worth 500.\n");
        printf("\nYour Cart: ");
        while(temp != NULL){
            printf("\nProduct: %s", temp->product);
            printf("\t\t\tPrice: %d", temp->productPrice);
            temp = temp->next;
        }
        printf("\nProduct: UV Filter");
        printf("\t\t\tPrice: FREE");

        printf("\n");
        printf("--------------------------------------------------------");
        printf("\nCustomer Name:\t\t\t\t%s\nCustomer E-mail:\t\t\t%s\nYour Total Bill:\t\t\t%d", bill.customerName, bill.customerEmail, totalBill);

    }
    else{
        system("cls");
        printf("INVALID COUPON CODE");
        printList(head);
        printf("\n\n\nThank You for Shopping. Visit Again.");
    }
    
}


void customer(){
    Cart head=NULL, temp, new1;
    char res;
    system("cls");
    getDetails();

    do{   
        system("cls");
        printf("Hello %s!", bill.customerName);
        if(flagUser == 1){
            printf("\n---------WELCOME BACK---------");
        }
        else if(flagUser == 0){
            printf("\n---------NEW USER---------");
        }
        printf("\nWhat would you like to buy?");
        printCategories();
        int choice;
        scanf("%d", &choice);

        printProducts(choice-1);
        int prodChoice;
        scanf("%d", &prodChoice);


        if(head ==NULL){
            head =getnode();
            head->product = category[choice-1].products[prodChoice-1].productName;
            head->productPrice = category[choice-1].products[prodChoice-1].price;
            temp =head;
        }
        else{
            new1 = getnode();
            new1->product = category[choice-1].products[prodChoice-1].productName;
            new1->productPrice = category[choice-1].products[prodChoice-1].price;
            temp->next = new1;
            temp = new1;
        }
        totalBill += category[choice-1].products[prodChoice-1].price;

        printf("Want to buy another product? (y/n): ");
        scanf(" %c", &res);
    }while(res == 'y');
    printList(head);

    char couponCode = 'n';
    printf("\nDo you have a coupon code? (y/n): ");
    scanf(" %c", &couponCode);

    if(couponCode == 'y'){
        coupon(head);
    }
    else{
        system("cls");
        printList(head);
        
    }
    if(flagUser == 1){
        printf("\n------YOU GET A FREE DELIVERY------\n");
    }
    else if(flagUser == 0){
        printf("\n\n\n\nDelivery Charges:\t\t\t100");
        totalBill += 100;
        printf("\nTotal Bill:\t\t\t\t%d", totalBill);
        printf("\n\n\t\t---Shop again to Get FREE Delivery---");
    }
    printf("\n\n\nThank You for Shopping. Visit Again.");

}


void readFile(){
       fp = fopen("shopping.txt","r");
            
        if(fp == NULL){
            printf("\n\t\tFile opening error");
            exit(0);
        }
        else{

            fscanf(fp, "%d\t", &categoryNum);
            fscanf(fp, "%d\t", &productNum);

            int i=0, j=0;
            while(fscanf(fp, "%d", &category[i].products[j].price)!=EOF){
                for( i=0;i<categoryNum;i++){
                fscanf(fp, "%s\t", &category[i].categoryName);
                    for( j=0; j<productNum; j++){
                        fscanf(fp, "%s\t", &category[i].products[j].productName);
                        fscanf(fp, "%d\t", &category[i].products[j].price);
                    }
                }
            }
        }
}


void printStruct(){
    system("cls");
    readFile();
    for(int i=0;i<categoryNum;i++){
        printf("\n\nName of Category: ");
        printf("%s", category[i].categoryName);
        printf("\nProducts of this category: ");
        for(int j=0; j<productNum; j++){
            printf("\n\n\tName of Product: ");
            printf("%s", category[i].products[j].productName);
            printf("\t\tPrice of Product: ");
            printf("%d", category[i].products[j].price);
        }
    }
}


void adminCreate(){

    system("cls");
    printf("-----------------CREATE DATABASE-----------------");
    printf("\nEnter the Number of Categories: ");
    scanf("%d", &categoryNum);
    printf("Enter the Number of Products: ");
    scanf("%d", &productNum);

    fp = fopen("shopping.txt","w");
    if(fp == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else{  

        fprintf(fp, "%d\t", categoryNum);
        fprintf(fp, "%d\t", productNum);

        for(int i=0;i<categoryNum;i++){
            printf("\nName of Category: ");
            scanf("%s", &category[i].categoryName);
            fprintf(fp, "%s\t", category[i].categoryName);
            printf("Enter the products of this category: \n");

            for(int j=0; j<productNum; j++){
                printf("\nEnter Name of Product: ");
                scanf("%s", &category[i].products[j].productName);
                fprintf(fp, "%s\t", category[i].products[j].productName);

                printf("Enter Price of Product: ");
                scanf("%d", &category[i].products[j].price);
                fprintf(fp, "%d\t", category[i].products[j].price);
            }
        }
    }
    fclose(fp);
}


void adminUpdate(){

    int catUpdate, prodUpdate;

        int i=0, flag =0;

        readFile();
        for(int j=0;j<categoryNum;j++){
            printf("\n\nName of Category: ");
            printf("%d. %s", j+1, category[j].categoryName);
        }
        printf("\n\t\tWhich Category do you want to update?: ");
        scanf("%d",&catUpdate);

        system("cls");

        printf("\n\nName of Category: ");
        printf("%s", category[catUpdate-1].categoryName);
        printf("\n Products of this category: ");
        for(int j=0; j<productNum; j++){
            printf("\n\n\t%d. Name of Product: ",j+1);
            printf("%s", category[catUpdate-1].products[j].productName);
            printf("\n\tPrice of Product: ");
            printf("%d", category[catUpdate-1].products[j].price);
        }
        printf("\n\t\tWhich Product do you want to update?: ");
        scanf("%d",&prodUpdate);
        
        readFile();

        printf("\nEnter New Product Name: ");
        scanf("%s", &category[catUpdate-1].products[prodUpdate-1].productName);
        printf("\nEnter New Price: ");
        scanf("%d", &category[catUpdate-1].products[prodUpdate-1].price);
    

    fp = fopen("shopping.txt","w");
    //fptr = fopen("temp.txt", "w"); //temporary file


    fprintf(fp, "%d\t", categoryNum); //Write contents of structure into file
    fprintf(fp, "%d\t", productNum);
    if(fp == NULL && fptr ==NULL){
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else{
        for(int i=0;i<categoryNum;i++){
            fprintf(fp, "%s\t", category[i].categoryName);
            for(int j=0; j<productNum; j++){
                fprintf(fp, "%s\t", category[i].products[j].productName);
                fprintf(fp, "%d\t", category[i].products[j].price);
            }
        }
    }
    fclose(fp);
   // fclose(fptr);
    
}


void admin(){

    system("cls");
    printf("----------------ADMIN MODE----------------\n1.Create New Database of Products\n2.Update Current Database\n3.Print Database\n\tEnter your choice (1/2/3):  ");
    int choice;
    scanf("%d", &choice);

    if(choice == 1)
        adminCreate();
    else if(choice == 2)
        adminUpdate();
    else if(choice == 3)
        printStruct();  
    else{
        printf("Enter Valid Choice\nProgram Exit");
        return;
    }

    printf("\nProducts Added.\nPress 1 to continue as customer.\nPress 2 to exit.");
    int res;
    scanf("%d", &res);
    if(res == 1){
        customer();
    }
    else{
        system("cls");
        printf("\t\t\tThank You");
    }
}


////////////////////////////MAIN////////////////////////////////


int main(){

    int choice = welcome();
    switch (choice){
        case 1:
            admin();
            break;
        case 2:
            readFile();
            customer();
            break;

         default:
            printf("Select valid choice");
            //printStruct();
            break;
    }
}