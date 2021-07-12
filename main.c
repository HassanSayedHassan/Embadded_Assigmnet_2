#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct Node Node;
typedef struct student student;
typedef struct data_birth data_birth;
struct data_birth{
    int day;
    int month;
    int year;
};
struct student{
    char name[15];
    int id;
    data_birth data;
    int last_year_score;

};
struct Node{
    student item;
    Node *next;

};

//chaining
#define size_chain 7
Node *hash_array_Chain[size_chain];
void initialize_array_Chain()
{
    int i;
    for(i = 0; i < size_chain; i++)
        hash_array_Chain[i] = NULL;
}
void insert_Chain(student element)
{
    //create a new node with value
    Node *newNode = malloc(sizeof( Node));
    strcpy(newNode->item.name,element.name);
    newNode->next = NULL;

    int asci=tolower(element.name[0]);
    // printf("%d",asci);
    int value=asci-97;
    //calculate hash key
    int key = value % size_chain;

    //check if hash_array_Chain[key] is empty
    if(hash_array_Chain[key] == NULL)
        hash_array_Chain[key] = newNode;
        //collision
    else
    {
        //add the node at the end of hash_array_Chain[key].
        Node *temp = hash_array_Chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}
void Display_Chain()
{
    int i;

    for(i = 0; i < size_chain; i++)
    {
        Node *temp = hash_array_Chain[i];
        printf("hash_array_Chain[%d]-->",i);
        while(temp)
        {
            printf("%s -->",temp->item.name);
            temp = temp->next;
        }
        printf("NULL\n");
    }
} //todo
void delete_Chain(student element)
{
    int asci=tolower(element.name[0]);
    int value=asci-97;
//calculate hash key
    int key = value % size_chain;

    Node *temp = hash_array_Chain[key], *dealloc;
    if(temp != NULL)
    {
        if(!strcmp(temp->item.name , element.name))
        {
            dealloc = temp;
            temp = temp->next;
            hash_array_Chain[key]=temp;   //TODO  "correct delete "
            free(dealloc);

            printf("Node delete_Chaind !\n");
            return;
        }
        else
        {
            while(temp->next)
            {
                if(!strcmp(temp->next->item.name , element.name))
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                    printf("Node delete_Chaind !\n");
                    return;
                }
                temp = temp->next;
            }
        }
    }
    printf("Node NOT FOUND !\n");




}
void Finding_Chain(student element)
{
    int asci=tolower(element.name[0]);
    // printf("%d",asci);
    int value=asci-97;
    //calculate hash key
    int key = value % size_chain;

    Node *temp = hash_array_Chain[key];
    // printf("hash_array_Chain[%d]-->",i);
    while(temp)
    {
        // printf("%s -->",temp->data.name);
        if (!strcmp(temp->item.name , element.name)){
            printf("node found\n");
            return ;
        }
        temp = temp->next;
    }
    //printf("NULL\n");
    printf("node not found\n");
}
int get_size_chaining(){
    int sum_chain=0;
    Node *tempo;
    for(int i=0;i<size_chain;i++)
    {
        if(hash_array_Chain[i] == NULL)
        {
            sum_chain+=sizeof(hash_array_Chain[i]);
        }
        else
        {
            sum_chain+=sizeof(hash_array_Chain[i]);
            tempo=hash_array_Chain[i];
            while(tempo!=NULL)
            {
                sum_chain+=sizeof(Node);
                tempo=tempo->next;
            }
        }
    }
    return  sum_chain;
}


//linear
#define size_Linear 12
int Count_linear=0;
student hash_array_Linear[size_Linear];
void initialize_array_Linear()
{
    int i;
    for(i = 0; i < size_Linear; i++)
        strcpy(hash_array_Linear[i].name,"");
}
void Linear_Insert(student element)
{
    if(Count_linear==size_Linear){
        printf("Error.\nTable if FULL\n");
        return;
    }
    int probe=element.data.month-1;
    while(strcmp(hash_array_Linear[probe].name,""))
    {
        probe=(probe+1)%size_Linear;
    }
    hash_array_Linear[probe].id=element.id;
    strcpy(hash_array_Linear[probe].name,element.name);
    hash_array_Linear[probe].last_year_score=element.last_year_score;
    hash_array_Linear[probe].data.day=element.data.day;
    hash_array_Linear[probe].data.month=element.data.month;
    hash_array_Linear[probe].data.year=element.data.year;
    Count_linear++;
}
int Search_Linear(student element)
{
    if(Count_linear==0){
        return -1;
    }
    int probe=element.data.month-1;
    int index=0;                                    /// We use index in case we Search_Linear in full array not contain my element
    while( index<size_Linear   &&   strcmp(hash_array_Linear[probe].name,"") )  //TODO "Whey ?"
    {
        if(!strcmp(hash_array_Linear[probe].name,element.name)){
            return probe;
        }

        probe=(probe+1)%size_Linear;
        index++;
    }
    return -1;
}
void Finding_Linear(student element)
{
    if(Count_linear==0){
        printf("Error.\nTable if EMPTY\n");
        return ;
    }
    int probe=element.data.month-1;
    int index=0;                                    /// We use index in case we Search_Linear in full array not contain my element
    while( index<size_Linear   &&   strcmp(hash_array_Linear[probe].name,"") )  //TODO "Whey ?"
    {
        if(!strcmp(hash_array_Linear[probe].name,element.name)){
            printf("Found in index %d\n",probe);
            return ;
        }

        probe=(probe+1)%size_Linear;
        index++;
    }
    printf("\nElement not found.\n");
    return ;
}
void Display_Linear()
{
    int i;
    for(i=0;i<size_Linear;i++){
        if(!strcmp(hash_array_Linear[i].name,"")){
            printf("null  ");
        }else{
            printf("%s%c",hash_array_Linear[i].name,' ');
        }
    }
    printf("\n");
}
void Delete_Linear(student element)
{
    if(Count_linear==0){
        printf("Error.\nTable if EMPTY\n");
        return;
    }
    int loc=Search_Linear(element);
    if(loc!=-1)
    {
        strcpy(hash_array_Linear[loc].name,"");
        Count_linear--;
    }
}
void get_size_linear(){
    int total_size=0;
    for (int i=0;i<size_Linear;i++){
        total_size+=sizeof(student);
    }
    printf("total size array linear  %d\n",total_size);
}

//Quadratic
#define Size_Quadratic 12
int Count_Quadratic=0;
student hash_array_Quadratic[Size_Quadratic];
void initialize_array_Quadratic()
{
    int i;
    for(i = 0; i < Size_Quadratic; i++)
        strcpy(hash_array_Quadratic[i].name,"");
}
void Quadratic_insert(student element)
{
    if(Count_Quadratic==Size_Quadratic){
        printf("Error.\nTable if FULL\n");
        return;
    }
    static int i = 1;
    int probe=element.data.month-1;
    while(strcmp(hash_array_Quadratic[probe].name,""))
    {
        probe=(probe+i*i)%Size_Quadratic;
        i++;
    }
    strcpy(hash_array_Quadratic[probe].name,element.name);
    hash_array_Quadratic[probe].id=element.id;
    hash_array_Quadratic[probe].last_year_score=element.last_year_score;
    hash_array_Quadratic[probe].data.day=element.data.day;
    hash_array_Quadratic[probe].data.month=element.data.month;
    hash_array_Quadratic[probe].data.year=element.data.year;
    Count_Quadratic++;
}
void Finding_Quadratic(student element)
{
    if(Count_Quadratic==0){
        printf("Error.\nTable if EMPTY\n");
        return ;
    }
    static int i = 1;
    int probe=element.data.month-1;
    int temp=probe;
    int index=0;                                    /// We use index in case we search in full array not contain my element
    while( index<Size_Quadratic   &&   strcmp(hash_array_Quadratic[probe].name,"") )  //TODO "Whey ?"
    {
        if(!strcmp(hash_array_Quadratic[probe].name,element.name)){
            printf("Found in index %d\n",probe);
            return ;
        }

        probe=(temp+i*i)%Size_Quadratic;
        index++;
    }
    printf("\nElement not found.\n");
    return ;
}
void Display_Quadratic()
{
    int i;
    for(i=0;i<Size_Quadratic;i++){
        if(!strcmp(hash_array_Quadratic[i].name,"")){
            printf("null  ");
        }else{
            printf("%s%c",hash_array_Quadratic[i].name,' ');
        }

    }
    printf("\n");
}
void Delete_Quadratic(student element){
    if(Count_Quadratic==0){
        printf("Error.\nTable if EMPTY\n");
        return ;
    }
    static int i = 1;
    int probe=element.data.month-1;
    int temp=probe;                                /// We use index in case we search in full array not contain my element
    while(  strcmp(hash_array_Quadratic[probe].name,"") )  //TODO "Whey ?"
    {
        if(!strcmp(hash_array_Quadratic[probe].name,element.name)){
            strcpy(hash_array_Quadratic[probe].name,"");
            Count_Quadratic--;
            return ;
        }

        probe=(temp+i*i)%Size_Quadratic;
        i++;
    }
    printf("\nElement not found.\n");
    return ;
}
void get_size_Quadratic(){
    int total_size=0;
    for (int i=0;i<Size_Quadratic;i++){
        total_size+=sizeof(student);
    }
    printf("total size array Quadratic  %d\n",total_size);
}



int main() { char op;
    /// Test Time  Execution
    /// Test Time  Execution At chaining
    /*

     student s1={"aos",5,20,4,2021,2011};
     initialize_array_Chain();


    int start = clock();
     for (int i=0;i<100;i++)
         insert_Chain(s1);
    int stop = clock();
     double l1 = (double)(stop - start)/CLOCKS_PER_SEC;

     printf("The time of Chain with small N     %.9lf\n",l1);

     start = clock();
     for (int i=0;i<1000;i++)
         insert_Chain(s1);
     stop = clock();
     double l2 = (double)(stop - start)/CLOCKS_PER_SEC;

     printf("The time of Chain with medium N     %.9lf\n",l2);

     start = clock();
     for (int i=0;i<10000;i++)
         insert_Chain(s1);
     stop = clock();
     double l3 = (double)(stop - start)/CLOCKS_PER_SEC;

     printf("The time of Chain with large N    %.9lf\n",l3);

     printf("avrage time of Chain is   %.9lf\n",(l1+l2+l3)/3);



 */
    ///Test Time  Execution At  linear probling
    /*
      initialize_array_Linear();
      student s1={"aos",5,20,4,2021,2011};
      student s2={"aosss",5,20,4,2021,2011};
      student s3={"aossssss",5,20,4,2021,2011};
      student s4={"csssss",5,20,4,2021,2011};

      int start = clock();
      Linear_Insert(s1);
      int stop = clock();
      double k1 = (double)(stop - start)/CLOCKS_PER_SEC;

      printf("The time of linear with no collision %.9lf\n",k1);

      start = clock();
      Linear_Insert(s2);
      stop = clock();
      double k2 = (double)(stop - start)/CLOCKS_PER_SEC;

      printf("The time of linear with 1 collision %.9lf\n",k2);

      start = clock();
      Linear_Insert(s3);
      stop = clock();
      double k3 = (double)(stop - start)/CLOCKS_PER_SEC;

      printf("The time of linear with 2 collision %.9lf\n",k3);

      printf("avrage time of linear is %.9lf\n",(k1+k2+k3)/3);
  */
    /// Test Time  Execution Al Quadratic probling

/*   student s1={"aos",5,20,4,2021,2011};

    initialize_array_Quadratic();


   int start = clock();
    Quadratic_insert(s1);
   int stop = clock();
    double q1 = (double)(stop - start)/CLOCKS_PER_SEC;

    printf("The time of Quadratic with no collision %.9lf\n",q1);

    start = clock();
    Quadratic_insert(s1);
    stop = clock();
    double q2 = (double)(stop - start)/CLOCKS_PER_SEC;

    printf("The time of Quadratic with 1 collision %.9lf\n",q2);

    start = clock();
    Quadratic_insert(s1);
    stop = clock();
    double q3 = (double)(stop - start)/CLOCKS_PER_SEC;

    printf("The time of Quadratic with 2 collision %.9lf\n",q3);

    printf("avrage time of Quadratic is %.9lf\n",(q1+q2+q3)/3);


*/


/// Get size
/*
    student s1={"aos",5,20,4,2021,2011};
    student s2={"aooos",5,20,4,2021,2011};
    get_size_linear();
    get_size_Quadratic();

    initialize_array_Chain();
    printf("Total chain size before any insertion  %d\n",get_size_chaining());
    insert_Chain(s1);
    insert_Chain(s2);
    printf("Total chain size after insert 2 nodes  %d\n",get_size_chaining());
    for (int i=0;i<18;i++)
        insert_Chain(s1);
    printf("Total chain size after insert 20 nodes  %d\n",get_size_chaining());
*/


    int N;
    printf("enter the number of students\n");
    scanf("%d", &N);

    printf("\nwill you use Opened hashing or Closed hashing ? !\n");
    printf("press O for Opened hashing\n");
    printf("press C for Closed hashing \n");

    char method;
    scanf("%c", &method);
    scanf("%c", &method);
    if (method == 'o' || method == 'O') {
        initialize_array_Chain();

        for (int m = 0; m < N; m++) {
            printf("enter the data of student number%d  \n" ,m+1);
            student s;
            printf("enter the name of student\n");
            scanf("%s", &s.name);
            printf("enter the id of student \n");
            scanf("%d", &s.id);
            printf("enter the day of birth \n");
            scanf("%d", &s.data.day);
            printf("enter the month of birth \n");
            scanf("%d", &s.data.month);
            printf("enter the year of birth \n");
            scanf("%d", &s.data.year);
            printf("enter last_year_score \n");
            scanf("%d", &s.last_year_score);


            printf("choose operation please !\n");
            printf("press i for insertion\n");
            printf("press d for deletion\n");
            printf("press f for finding\n");
            scanf("%c",&op);
            scanf("%c",&op);
            if(op=='i'||op=='I'){insert_Chain(s);}
            else if(op=='d'||op=='D'){delete_Chain(s);}
            else if(op=='f'||op=='F'){Finding_Chain(s);}
        }
        Display_Chain();
    }
    else if (method == 'c' || method == 'C')
    {   printf("if you want to choose linear proping press L \n");
        printf("if you want to choose Quadratic proping press Q \n");
        char p;
        scanf("%c", &p);
        scanf("%c", &p);
        if(p=='l'||p=='L')
        {
            initialize_array_Linear();
            for (int m = 0; m < N; m++) {
                printf("enter the data of student number%d  \n" ,m+1);
                student s;
                printf("enter the name of student \n");
                scanf("%s", &s.name);
                printf("enter the id of student \n");
                scanf("%d", &s.id);
                printf("enter the day of birth \n");
                scanf("%d", &s.data.day);
                printf("enter the month of birth \n");
                scanf("%d", &s.data.month);
                printf("enter the year of birth \n");
                scanf("%d", &s.data.year);
                printf("enter last_year_score \n");
                scanf("%d", &s.last_year_score);

                printf("choose operation please !\n");
                printf("press i for insertion\n");
                printf("press d for deletion\n");
                printf("press f for finding\n");
                scanf("%c",&op);
                scanf("%c",&op);
                if(op=='i'||op=='I'){Linear_Insert(s);}
                else if(op=='d'||op=='D'){Delete_Linear(s);}
                else if(op=='f'||op=='F'){Finding_Linear(s);}
            }
            Display_Linear();
        }
        else if(p== 'q' || p == 'Q') {
            initialize_array_Quadratic();
            for (int m = 0; m < N; m++) {
                printf("enter the data of student number%d  \n" ,m+1);
                student s;
                printf("enter the name of student \n");
                scanf("%s", &s.name);
                printf("enter the id of student \n");
                scanf("%d", &s.id);
                printf("enter the day of birth \n");
                scanf("%d", &s.data.day);
                printf("enter the month of birth \n");
                scanf("%d", &s.data.month);
                printf("enter the year of birth \n");
                scanf("%d", &s.data.year);
                printf("enter last_year_score\n ");
                scanf("%d", &s.last_year_score);

                printf("choose operation please !\n");
                printf("press i for insertion\n");
                printf("press d for deletion\n");
                printf("press f for finding\n");
                scanf("%c",&op);
                scanf("%c",&op);
                if(op=='i'||op=='I'){Quadratic_insert(s);}
                else if(op=='d'||op=='D'){Delete_Quadratic(s);}
                else if(op=='f'||op=='F'){Finding_Quadratic(s);}

            }
            Display_Quadratic();
        }

    }
    else {
        printf("\ninvalid choice \n");
    }

    return 0;

}
