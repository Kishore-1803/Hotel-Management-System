#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
struct hotel
{
    char room_type[50],vacancy[10]; //Vacancy indicates whether room is available for customer to occupy(yes/no)
    int room_number,room_rent;
};
struct user_cred
{
    char user_name[20],password[20];
};
struct booking{
    char customerName[50],customerAddress[500],active[10];
    int checkInDate,checkInMonth,checkInYear,checkOutDate,checkOutMonth,checkOutYear,roomNumber,customerId,food_price;
    long long int customerMobile;
};
//Struct Room Service
struct room_service{
	int custid;
	char active[10];
	float rsbill;
	int extrabeds;
	float extrabed_bill;
	char vehicle[20];
	float vehicle_bill;
	int vehicle_days;
};
//Restaurant structure
struct food
{
    char food_name[40];
    int price;
};
struct food_bill{
  char food_name[40];
  int price;
  int qty;
};
struct membership{
    char name[50];
    long int phonenumber;
    int id;
};
struct date
{
	int years;
	int months;
	int days;
};
int days_on_month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
void DisplayMenu();
void staff();

void add_room();
void view_room();
void search_room();
void modify_room();
void delete_room_record();

void sort_rent();
void sort_room_type();
void sort_room_vacancy();
void sort_room_numbers();
void login();
void add_user();
void view_customer_records();
void search_customer_records();
void displayRoomHeader();
void displayRoom(struct hotel room);
void displaySortOptions();

void booking();
int dateValidator(struct booking *tempCustomerDetails,int date,int month,int year,int flag);

void existing_customer();
void restaurant();
void view_customer_food_bill();

void room_services();
void rent_bed(int id, int roomno);
void rent_vehicle(int id);
int days_cal(int id);

//checkout
void checkout();
int payment(float total);
int diff(struct date s1, struct date s2);
int days_date(struct date s);
float offer(int);
int main()
{
  int choice;
  while (1) {
    printf("\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~\n");
    printf("                                            \e[1;31mWELCOME TO ASTRA GRANDE\e[0m\n                                   ");
    printf("\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n");


    printf(" ------------------------ \n");
    printf("|| 1.Staff              ||\n");
    printf("|| 2.New Customer       ||\n");
    printf("|| 3.Existing Customer  ||\n");
    printf("|| 4.Exit               ||\n");
    printf(" ------------------------ \n\n");
    printf("Enter Your Choice :- \n");
    scanf("%d",&choice);
    if(choice == 1)
    {
      login();
      staff();
    }
    else if(choice == 2){
      booking();
    }
    else if(choice==3)
    {
      existing_customer();
    }
    else if(choice==4)
    {
      exit(0);
    }
    }
  return 0;
}

void clearScreen() {
    system("cls");
}

int checkUsername(FILE *fp, const char *username) {
    struct user_cred u;
    rewind(fp);

    while (fread(&u, sizeof(struct user_cred), 1, fp)) {
        if (strcmp(u.user_name, username) == 0) {
            return 1;  // Username found
        }
    }

    return 0;  // Username not found
}

int checkPassword(FILE *fp, const char *username, const char *password) {
    struct user_cred u;
    rewind(fp);

    while (fread(&u, sizeof(struct user_cred), 1, fp)) {
        if (strcmp(u.user_name, username) == 0 && strcmp(u.password, password) == 0) {
            return 1;  // Password matches
        }
    }

    return 0;  // Password does not match
}

void login() {
    clearScreen();

    FILE *fp = fopen("user_credentials.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char retry;

    while (1) {
        char username[50];
        printf("Enter Username: ");
        fflush(stdin);
        scanf("%[^\n]s", username);

        if (checkUsername(fp, username)) {
            char password[50];
            printf("Enter password: ");
            fflush(stdin);
            scanf("%[^\n]s", password);

            if (checkPassword(fp, username, password)) {
                printf("\n\nVALIDATION SUCCESSFUL!\n\n");
                printf("Enter any char to continue: ");
                fflush(stdin);
                scanf(" %c", &retry);
                break;
            } else {
                printf("Incorrect Password!\n");
            }
        } else {
            printf("Username doesn't exist!\n");
        }

        printf("Do you want to try again? (y/n): ");
        fflush(stdin);
        scanf(" %c", &retry);

        if (retry != 'y') {
            break;
        }
    }

    fclose(fp);
}
void displayMenu() {
    printf(" ------------------------------- \n");
    printf("|| 1. ADD A ROOM               ||\n");
    printf("|| 2. VIEW ROOM RECORDS        ||\n");
    printf("|| 3. MODIFY ROOM RECORD       ||\n");
    printf("|| 4. SEARCH ROOM RECORD       ||\n");
    printf("|| 5. DELETE ROOM RECORD       ||\n");
    printf("|| 6. VIEW CUSTOMER RECORDS    ||\n");
    printf("|| 7. VIEW CUSTOMER FOOD BILL  ||\n");
    printf("|| 8. SEARCH CUSTOMER RECORDS  ||\n");
    printf("|| 9. ADD NEW STAFF CREDENTIALS||\n");
    printf("|| 10. EXIT                    ||\n");
    printf(" ------------------------------- \n\n");
}

void staff() {
    int choice;

    while (1) {
        system("cls");
        displayMenu();
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                add_room();
                break;
            case 2:
                view_room();
                break;
            case 3:
                modify_room();
                break;
            case 4:
                search_room();
                break;
            case 5:
                delete_room_record();
                break;
            case 6:
                view_customer_records();
                break;
            case 7:
                view_customer_food_bill();
                break;
            case 8:
                search_customer_records();
                break;
            case 9:
                add_user();
                break;
            case 10:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}
void add_user()
{
      printf("\n\n\t\t\t\t\tAdd New Staff Credentials\n\n\n\n");
      FILE *fp = fopen("user_credentials.txt","a+");
      int curr_posn = ftell(fp),verify;
      char ch;
      struct user_cred u1,u2;
      enter_username:
      printf("Enter New Username :-");
      fflush(stdin);
      scanf("%[^\n]s",u1.user_name);
      rewind(fp);
      while(fread(&u2,sizeof(struct user_cred),1,fp))
      {
          verify=strcmp(u1.user_name,u2.user_name);
          if(verify==0)
          {
              printf("username already exists!!!\n");
              printf("Do You Want To Enter Again(y/n) :- ");
              fflush(stdin);
              scanf("%c",&ch);
              if(ch=='y')
              {
                  goto enter_username;
              }
              else
              {
                  staff();
              }
          }
      }
      printf("Enter new password :- ");
      fflush(stdin);
      scanf("%[^\n]s",u1.password);
      fseek(fp,curr_posn,SEEK_SET);
      fwrite(&u1,sizeof(struct user_cred),1,fp);
      fclose(fp);
}
void add_room()
{
    FILE *fp = fopen("room.txt","ab+");
    if(fp==NULL)
    {
      printf("Error!");
    }
    struct hotel room,room1;
    char repeat,sure,pass;
    int room_type_num,curr_posn,roomnumber;
    add_another:
        system("cls");
    pass='n';
    curr_posn=ftell(fp);
    rewind(fp);
enter_room_no:
    printf("%-26s%s","Enter Room Number ",":- ");
    scanf("%d",&roomnumber);
           while(fread(&room1,sizeof(struct hotel),1,fp))
            {
              if(roomnumber==room1.room_number)
              {
                pass='y';
                printf("Room number already exists!\n");
                break;
              }
              else{
                pass='n';
              }
            }
            rewind(fp);
            if(pass=='y')
                goto enter_room_no;

      fseek(fp,curr_posn,SEEK_CUR);
    room.room_number=roomnumber;
    enter_room_type:
    printf("%-26s%s","Choose Room Type (1-4) ",":- \n");
    printf(" ------------------------ \n");
    printf("|| 1.Double Bed         ||\n");
    printf("|| 2.Single Bed         ||\n");
    printf("|| 3.Family             ||\n");
    printf("|| 4.King Size          ||\n");
    printf(" ------------------------ \n");
    scanf("%d",&room_type_num);
    if(room_type_num==1)
    {
      strcpy(room.room_type,"Double Bed");
    }
    else if(room_type_num==2)
    {
      strcpy(room.room_type,"Single Bed");
    }
    else if(room_type_num==3)
    {
       strcpy(room.room_type,"Family");
    }
    else if(room_type_num==4)
    {
      strcpy(room.room_type,"King Size");
    }
    else
    {
        printf("Invalid Choice!Enter Again");
        goto enter_room_type;
    }
    printf("%-26s%s","Enter Room Rent ",":- ");
    scanf("%d",&room.room_rent);

    fflush(stdin);
    printf("Are You Sure to Add Room (y/n) ");
    scanf("%c",&sure);
    if(sure=='y')
    {
        system("cls");
        strcpy(room.vacancy,"yes");
        fwrite(&room,sizeof(struct hotel),1,fp);
        printf("Room Has Been Added Successfully ! \n");
            printf("Details of Room :- \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy |                \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("| %-11d | %-15s | $%-9d | %-12s |\n",room.room_number,room.room_type,room.room_rent,room.vacancy);
            printf(" -----------------------------------------------------------                 \n");
    }
    else
    {
        printf("Room Has Not Been Added :( \n");
    }
    fflush(stdin);
    printf("Do You Want to Add Another Room (y/n) ");
    scanf("%c",&repeat);
    if(repeat=='y')
    {
     goto add_another;
    }
    fclose(fp);
    printf("File Closed");

}
void displayRoomHeader() {
    printf(" -----------------------------------------------------------\n");
    printf("| Room Number | Room Type        | Room Rent  | Room Vacancy |\n");
    printf(" -----------------------------------------------------------\n");
}

void displayRoom(struct hotel room) {
    printf("| %-11d | %-15s | %-9d | %-12s |\n", room.room_number, room.room_type, room.room_rent, room.vacancy);
}

void displaySortOptions() {
    printf(" ---------------------------\n");
    printf("|| 1. Sort By Rent         ||\n");
    printf("|| 2. Sort By Room Type    ||\n");
    printf("|| 3. Sort By Room Vacancy ||\n");
    printf("|| 4. Sort By Room Numbers ||\n");
    printf("|| 5. BACK                 ||\n");
    printf(" ---------------------------\n");
}

void view_room() {
    FILE *fp = fopen("room.txt", "rb");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(struct hotel);

    if (n < 1) {
        printf("No Rooms Added Till Now!\n");
        fclose(fp);
        printf("Press Any Key To Go Back!");
        getchar();  // Use getchar to pause until a key is pressed
        return;
    }

    rewind(fp);
    displayRoomHeader();

    struct hotel room;
    for (int i = 0; i < n; i++) {
        fread(&room, sizeof(struct hotel), 1, fp);
        displayRoom(room);
        printf(" -----------------------------------------------------------\n");
    }

    fclose(fp);

    displaySortOptions();

    int choice;
    printf("Choose To See In Sorted Manner: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sort_rent();
            break;
        case 2:
            sort_room_type();
            break;
        case 3:
            sort_room_vacancy();
            break;
        case 4:
            sort_room_numbers();
            break;
        case 5:
            return;
        default:
            printf("Invalid choice! Going back to staff menu.\n");
    }
}
void sort_rent()
{
	int i,j;
    char any;
    system("cls");
    printf("Results Shown By Filtering Based on Rent :- \n\n");
        struct hotel *s, s1;
        FILE *fp;
        fp = fopen("room.txt","rb");
        fseek(fp,0,SEEK_END);
        int n = ftell(fp)/sizeof(struct hotel);
        s = (struct hotel*)malloc(n*sizeof(struct hotel));
        rewind(fp);
        for(i=0;i<n;i++)
        {
           fread(&s[i],sizeof(struct hotel),1,fp);
        }
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                if(s[i].room_rent<s[j].room_rent){
                    s1 = s[i];
                    s[i] = s[j];
                    s[j] = s1;
                }
            }
        }

        printf("Details of Room :- \n");
        printf(" -----------------------------------------------------------  \n");
        printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy | \n");
        printf(" -----------------------------------------------------------  \n");
        for(i=0;i<n;i++){
            printf("| %-11d | %-15s | $%-9d | %-12s |\n",s[i].room_number,s[i].room_type,s[i].room_rent,s[i].vacancy);
            printf(" ----------------------------------------------------------- \n");
        }
        fflush(stdin);
        fclose(fp);
    fflush(stdin);
    printf("Enter Any Key to Go Back ");
    fflush(stdin);
    scanf("%c",&any);
}
void sort_room_numbers()
{
	int i,j;
char any;
    system("cls");
    printf("Results Shown By Filtering Based on Room Numbers :- \n\n");
        struct hotel *s, s1;
        FILE *fp;
        fp = fopen("room.txt","rb");
        fseek(fp,0,SEEK_END);
        int n = ftell(fp)/sizeof(struct hotel);
        s = (struct hotel*)malloc(n*sizeof(struct hotel));
        rewind(fp);
        for(i=0;i<n;i++)
        {
           fread(&s[i],sizeof(struct hotel),1,fp);
        }
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                if(s[i].room_number>s[j].room_number){
                    s1 = s[i];
                    s[i] = s[j];
                    s[j] = s1;
                }
            }
        }

        printf("Details of Room :- \n");
        printf(" -----------------------------------------------------------  \n");
        printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy | \n");
        printf(" -----------------------------------------------------------  \n");
        for(i=0;i<n;i++){
            printf("| %-11d | %-15s | %-9d | %-12s |\n",s[i].room_number,s[i].room_type,s[i].room_rent,s[i].vacancy);
            printf(" ----------------------------------------------------------- \n");
        }
        fflush(stdin);
        fclose(fp);
    fflush(stdin);
    printf("Enter Any Key to Go Back ");
    fflush(stdin);
    scanf("%c",&any);
}
void filterAndDisplayRooms(FILE *fp, const char *filterType) {
    int i, n;
    struct hotel *rooms;
    fseek(fp, 0, SEEK_END);
    n = ftell(fp) / sizeof(struct hotel);

    if (n < 1) {
        printf("No Rooms Added Till Now!\n");
        return;
    }

    rooms = (struct hotel*)malloc(n * sizeof(struct hotel));
    rewind(fp);

    for (i = 0; i < n; i++) {
        fread(&rooms[i], sizeof(struct hotel), 1, fp);
    }

    int verify;
    displayRoomHeader();

    for (i = 0; i < n; i++) {
        verify = strcmp(rooms[i].room_type, filterType);
        if (verify == 0){
            displayRoom(rooms[i]);
        }
    }

    free(rooms);
}

void sort_room_type() {
    char any;
    FILE *fp = fopen("room.txt", "rb");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    printf("Results Shown By Filtering Based on Room Type:\n\n");
    filterAndDisplayRooms(fp, "Double Bed");
    filterAndDisplayRooms(fp, "Single Bed");
    filterAndDisplayRooms(fp, "Family");
    filterAndDisplayRooms(fp, "King Size");

    fclose(fp);

    printf("Enter Any Key to Go Back ");
    fflush(stdin);
    scanf("%c", &any);
}
void sort_room_vacancy()
{
    char any;
    int i;
        system("cls");
        printf("Results Shown By Filtering Based on Room Vacancy :- \n\n");
        struct hotel *s;
        FILE *fp;
        fp = fopen("room.txt","rb");
        fseek(fp,0,SEEK_END);
        int n = ftell(fp)/sizeof(struct hotel);
        s = (struct hotel*)malloc(n*sizeof(struct hotel));
        rewind(fp);
        for(i=0;i<n;i++)
        {
           fread(&s[i],sizeof(struct hotel),1,fp);
        }
        int verify;
         printf("Details of Room :- \n");
        printf(" -----------------------------------------------------------  \n");
        printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy | \n");
        printf(" -----------------------------------------------------------  \n");
        for(i=0;i<n;i++){
            verify=strcmp(s[i].vacancy,"yes");
            if(verify==0)
            {
               printf("| %-11d | %-15s | $%-9d | %-12s |\n",s[i].room_number,s[i].room_type,s[i].room_rent,s[i].vacancy);
               printf(" ----------------------------------------------------------- \n");
            }
        }
        for(i=0;i<n;i++){
            verify=strcmp(s[i].vacancy,"no");
            if(verify==0)
            {
               printf("| %-11d | %-15s | $%-9d | %-12s |\n",s[i].room_number,s[i].room_type,s[i].room_rent,s[i].vacancy);
               printf(" ----------------------------------------------------------- \n");
            }
        }
        fflush(stdin);
        fclose(fp);
        fflush(stdin);
    printf("Enter Any Key to Go Back ");
    fflush(stdin);
    scanf("%c",&any);
}
void search_room()
{
    int roomno;
    char choice,flag;
    struct hotel room;
    FILE *fp=fopen("room.txt","rb");
    repeat:
    rewind(fp);
    printf("Enter Room Number To Get Its Details :-");
    scanf("%d",&roomno);
    flag='n';
    while(fread(&room,sizeof(struct hotel),1,fp))
    {
        if(room.room_number==roomno)
        {
            flag='y';
            printf("Details of Room :- \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy |                \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("| %-11d | %-15s | $%-9d | %-12s |\n",room.room_number,room.room_type,room.room_rent,room.vacancy);
            printf(" -----------------------------------------------------------                 \n");
        }
    }
    if(flag=='n')
    {
        printf("Room Number Not Found !! \n");
    }
    printf("Do You Want To Search Any other Room :- ");
    fflush(stdin);
    scanf("%c",&choice);
    if(choice=='y')
        goto repeat;
    fclose(fp);
}
void modify_room()
{
   int roomno,modify_choice,roomnumber,roomrent,room_type_num,verify,verify1;
   struct hotel room,room1,room2;
   char choice,flag,vacancy[10],pass;
   FILE *fp,*fp1;
   repeat:
   flag='n';
   fp=fopen("room.txt","rb");
   fp1 = fopen("temp.txt","wb+");
   printf("Enter RoomNo To change Its Details :-");
   scanf("%d",&roomno);
    while(fread(&room,sizeof(struct hotel),1,fp))
    {
        verify=strcmp(room.vacancy,"yes");
        if(room.room_number==roomno && verify==0)
        {
            flag='y';
            room1.room_number=room.room_number;
            room1.room_rent=room.room_rent;
            strcpy(room1.room_type,room.room_type);
            strcpy(room1.vacancy,room.vacancy);
            printf("Details of Room :- \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy |                \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("| %-11d | %-15s | $%-9d | %-12s |\n",room.room_number,room.room_type,room.room_rent,room.vacancy);
            printf(" -----------------------------------------------------------                 \n");
            printf("Enter Which Information Do You Like To Modify :- \n");
            printf("1.Room Number\n2.Room Rent\n3.Room Type\n4.Vacancy\n");
            scanf("%d",&modify_choice);
            if(modify_choice==1)
            {
              //Making sure that room number remains unique
              int curr_posn=ftell(fp);
              rewind(fp);
              enter_room_no:
              printf("Enter New Room Number :- ");
              scanf("%d",&roomnumber);
              while(fread(&room2,sizeof(struct hotel),1,fp))
              {
                 if(roomnumber==room2.room_number)
                 {
                   pass='y';
                   printf("Room number already exists!\n");
                   break;
                 }
                 else{
                      pass='n';
                  }
               }
              rewind(fp);
              if(pass=='y')
              goto enter_room_no;

              fseek(fp,curr_posn,SEEK_SET);
              //
              room1.room_number=roomnumber;
            }
            else if(modify_choice==3)
            {

                enter_room_type:
                printf("Choose Room Type (1-4) :-\n");
                printf("1.Double Bed\n2.Single Bed\n3.Family\n4.King Size\n");
                scanf("%d",&room_type_num);
                if(room_type_num==1)
                {
                  strcpy(room1.room_type,"Double Bed");
                }
                else if(room_type_num==2)
                {
                  strcpy(room1.room_type,"Single Bed");
                }
                else if(room_type_num==3)
                {
                  strcpy(room1.room_type,"Family");
                }
                else if(room_type_num==4)
                {
                   strcpy(room1.room_type,"King Size");
                }
                else
                {
                   printf("Invalid Choice!Enter Again");
                   goto enter_room_type;
                 }
            }
            else if(modify_choice==2)
            {
                printf("Enter New Room Rent :-");
                scanf("%d",&roomrent);
                room1.room_rent=roomrent;
            }
            else if(modify_choice==4)
            {
                enter_vacancy:
                 printf("Enter Vacancy :-");
                 fflush(stdin);
                 scanf("%s",vacancy);
                 fflush(stdin);
                 verify=strcmp(vacancy,"yes");
                 verify1=strcmp(vacancy,"no");
                 if(!(verify==0 || verify1==0))
                 {
                     printf("Invalid Entry! Enter Again \n");
                     goto enter_vacancy;
                 }

                 strcpy(room1.vacancy,vacancy);
            }
            printf("Are You Sure To Modify (y/n) :- ");
            fflush(stdin);
            scanf("%c",&choice);
            system("cls");
            if(choice=='y')
            {
              printf("Room Details Updated ! \n");
              fwrite(&room1,sizeof(struct hotel),1,fp1);
            }
            else
            {
              printf("Room Details Modifcation Failed !\n");
              fwrite(&room,sizeof(struct hotel),1,fp1);
            }

         }
         else
         {
             fwrite(&room,sizeof(struct hotel),1,fp1);
         }

    }

    if(flag=='n')
    {
        printf("Room Number Doesn't Exist or It would have been Occupied Currently !!!!! \n");
    }

    fclose(fp);
    fclose(fp1);
    remove("room.txt");
    rename("temp.txt","room.txt");

    printf("Do You Want To Modify Any Other Room (y/n) :-");
    fflush(stdin);
    scanf("%c",&choice);
    if(choice=='y')
    {
        goto repeat;
    }

}
void delete_room_record()
{
    int roomnumber;
    char choice,flag,sure;
    struct hotel room;
    repeat:
    flag='n';
    FILE *fp=fopen("room.txt","rb");
    FILE *fp1=fopen("temp.txt","wb+");
    system("cls");
    rewind(fp);
    printf("Enter Room Number To Be Deleted :-");
    scanf("%d",&roomnumber);

    while(fread(&room,sizeof(struct hotel),1,fp))
    {
        if(room.room_number==roomnumber)
        {
            flag='y';
            printf("Details of Room :- \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy |                \n");
            printf(" -----------------------------------------------------------                 \n");
            printf("| %-11d | %-15s | $%-9d | %-12s |\n",room.room_number,room.room_type,room.room_rent,room.vacancy);
            printf(" -----------------------------------------------------------                 \n");
            printf("Are You Sure You Want to Delete The Room Details ! (y/n)");
            fflush(stdin);
            scanf("%c",&sure);
            fflush(stdin);
            if(sure=='y')
            {
              printf("Room Successfully Deleted !\n");
            }
            else
            {
              printf("Room Deletion Failed !\n");
              fwrite(&room,sizeof(struct hotel),1,fp1);
            }
        }
        else
        {
            fwrite(&room,sizeof(struct hotel),1,fp1);
        }

    }
    if(flag=='n')
    {
        printf("Room Number Not Found !! \n");
    }
    fclose(fp);
    fclose(fp1);
    remove("room.txt");
    rename("temp.txt","room.txt");
    printf("Do You Want To Delete Any other Room :- ");
    fflush(stdin);
    scanf("%c",&choice);
    if(choice=='y')
        goto repeat;
}
void view_customer_records()
{
    char any;
   FILE *customerDataFilePointer = fopen("customerDataFile.txt","rb");
    struct booking rec;
    printf("\n\n\t\t\t\t\t\t\t C u s t o m e r  r e c o r d s \n\n");
    printf("\t%-127s\n","------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\t| %-20s | %-30s | %-12s | %-12s | %-12s | %-5s | %-15s|%-11s|\n","Name","Address","CheckIn","CheckOut","Phone","Id","Check In Status","Room Number");
    printf("\t%-127s\n","------------------------------------------------------------------------------------------------------------------------------------------");
    while(fread(&rec,sizeof(struct booking),1,customerDataFilePointer))
     {
     printf("\t| %-20s | %-30s | %-2d/%-2d/%-4d%-2s | %-2d/%-2d/%-4d%-2s | %lld | %-5d | %-15s|%-11d|\n",rec.customerName,rec.customerAddress,rec.checkInDate,rec.checkInMonth,rec.checkInYear,"",rec.checkOutDate,rec.checkOutMonth,rec.checkOutYear,"",rec.customerMobile,rec.customerId,rec.active,rec.roomNumber);
     printf("\t%-127s\n","------------------------------------------------------------------------------------------------------------------------------------------");
    }
    printf("Enter Any To Proceed ! ");
    fflush(stdin);
    scanf("%c",&any);
    fclose(customerDataFilePointer);
}

void search_customer_records()
{
   int cust_id;
   char flag='n',again;
    FILE *cp=fopen("customerDataFile.txt","rb");
       struct booking rec;
    search_rec:
    rewind(cp);
    printf("Enter Customer Id To display his record :- ");
   scanf("%d",&cust_id);
   system("cls");
    while(fread(&rec,sizeof(struct booking),1,cp))
    {
        if( (cust_id==rec.customerId))
        {
            flag='y';
            break;
        }
    }
    if(flag=='y')
    {
       printf("%-127s\n","-------------------------------------------------------------------------------------------------------------------------------");
       printf("| %-20s | %-30s | %-12s | %-12s | %-12s | %-5s | %-15s |\n","Name","Address","CheckIn","CheckOut","Phone","Id","Check In Status");
       printf("%-127s\n","-------------------------------------------------------------------------------------------------------------------------------");
       printf("| %-20s | %-30s | %-2d/%-2d/%-4d%-2s | %-2d/%-2d/%-4d%-2s | %lld | %-5d | %-15s |\n",rec.customerName,rec.customerAddress,rec.checkInDate,rec.checkInMonth,rec.checkInYear,"",rec.checkOutDate,rec.checkOutMonth,rec.checkOutYear,"",rec.customerMobile,rec.customerId,rec.active);
       printf("%-127s\n","-------------------------------------------------------------------------------------------------------------------------------");
    }
    else
    {
        printf("Customer Not Found ! ");
    }
    printf("Do You Want To Search again(y/n) :- ");
    fflush(stdin);
    scanf("%c",&again);
    if(again=='y')
    {
        goto search_rec;
    }

}

void view_customer_food_bill()
{
char any;
   FILE *customerDataFilePointer = fopen("customerDataFile.txt","rb");
    struct booking rec;
    printf("\n\n\t\t\t\t C u s t o m e r  F o o d B i l l   P e n d i n g\n\n");
     printf("\t---------------------------------------------------\n");
     printf("\t| %-20s | %-12s | %-10s |\n","Name","Room Number","Food Bill");
     printf("\t---------------------------------------------------\n");
    while(fread(&rec,sizeof(struct booking),1,customerDataFilePointer))
    {
       if(rec.food_price>0)
       {
           printf("\t| %-20s | %-12d | %-10d |\n",rec.customerName,rec.roomNumber,rec.food_price);
     printf("\t---------------------------------------------------\n");
       }

    }
    printf("Enter Any To Proceed ! ");
    fflush(stdin);
    scanf("%c",&any);
     fclose(customerDataFilePointer);
}
//
// booking details
void booking(){

    // booking program

    int inputDate,inputMonth,inputYear,flag,inputRoomNumber,verify,inputcustomerId;
    char choice,valid,sure,any;
    struct booking customerDetails,customerDetails1;

    printf(" ------------------------------ \n");
    printf(" |  WELCOME TO BOOKING SECTION  |\n");
    printf(" ------------------------------ \n\n");

    printf("Please Provide Your Details\n");

    Details:
    fflush(stdin);
    printf("\nEnter Your Name: ");
    scanf("%[^\n]s",customerDetails.customerName);

    printf("\nEnter Your Address: ");
    fflush(stdin);
    scanf("%[^\n]s",customerDetails.customerAddress);

    printf("\nEnter The Check-In date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &inputDate,&inputMonth,&inputYear);
    dateValidator(&customerDetails,inputDate,inputMonth,inputYear,flag=0);

    checkOut:
    printf("\nEnter The Check-Out Date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &inputDate,&inputMonth,&inputYear);

    if (customerDetails.checkInDate <= inputDate && customerDetails.checkInMonth <= inputMonth && customerDetails.checkInYear <= inputYear ){

        dateValidator(&customerDetails,inputDate,inputMonth,inputYear,flag=1);
    }
    else{
        printf("The Check Out Date Is Lower Then Check In Date\n\n");
        printf("Enter The Check-Out Date Again:\n\n");
        goto checkOut;
    }

    printf("\nEnter Your Mobile Number: ");
    scanf("%lld",&customerDetails.customerMobile);
    system("cls");
    printf("Details Entered Successfully!\n");
    printf("\nThe Provided Details are: \n");

    printf("Name\t\t: %s\n\n",customerDetails.customerName);
    printf("Address \t: %s\n\n",customerDetails.customerAddress);
    printf("Check_In Date   : %d/%d/%d\n\n",customerDetails.checkInDate,customerDetails.checkInMonth,customerDetails.checkInYear);
    printf("Check_Out Date  : %d/%d/%d\n\n",customerDetails.checkOutDate,customerDetails.checkOutMonth,customerDetails.checkOutYear);
    printf("Mobile Number   : %lld\n\n",customerDetails.customerMobile);
    printf("Enter any To Proceed!");
    fflush(stdin);
    scanf("%c",&any);
    printf("Is There Any Changes To Do In The Above Entered Data (Y/N)");
    scanf("%c",&choice);
    if (choice == 'Y' || choice == 'y'){
        printf("\nEnter The Details:");
        goto Details;
    }

    system("cls");
//changed
    FILE *fp = fopen("room.txt","rb");
    FILE *tempFilePointer = fopen("temp.txt","wb+");
    FILE *customerDataFilePointer = fopen("customerDataFile.txt","ab+");
    struct hotel room,room1;
    rewind(fp);
    printf("Available Rooms are \n");
    printf(" -----------------------------------------------------------                 \n");
    printf("|Room Number  |Room Type        | Room Rent  | Room Vacancy |                \n");
    printf(" -----------------------------------------------------------                 \n");
    while(fread(&room,sizeof(struct hotel),1,fp))
    {
           printf("| %-11d | %-15s | $%-9d | %-12s |\n",room.room_number,room.room_type,room.room_rent,room.vacancy);
           printf(" -----------------------------------------------------------                 \n");
    }
    enterRoom:
        fclose(tempFilePointer);
        remove("temp.txt");
        tempFilePointer = fopen("temp.txt","wb+");
        printf("Enter The Room Number You Wanted To Book :");
        scanf("%d",&inputRoomNumber);
        rewind(fp);
        //roomnumber not exist condn , vacancy condn , equals condn
        while(fread(&room,sizeof(struct hotel),1,fp)){
            room1=room;
            if(inputRoomNumber==room.room_number)
            {
                verify=strcmp(room.vacancy,"yes");
                if(verify!=0)
                {
                    printf("Selected Room has Been Occupied already ! \n");
                    printf("Do You Want To Enter Again (y/n) ");
                    fflush(stdin);
                    fflush(stdin);
                    scanf("%c",&choice);
                    if(choice=='y')
                    {
                        goto enterRoom;
                    }
                    else{
                            system("cls");
                    printf("You have exited!!\n");
                    exit(0);
                    }
                }
                valid='y';
                printf("Are You Sure To Book A Room (y/n) ");
                fflush(stdin);
                scanf("%c",&sure);
                system("cls");
                if(sure=='y')
                {
                printf("Room Successfully Booked!\n");
                strcpy(customerDetails.active,"yes");
                strcpy(room1.vacancy,"no");
                fwrite(&room1,sizeof(struct hotel),1,tempFilePointer);
                customerDetails.roomNumber = inputRoomNumber;

                int last_posn = ftell(customerDataFilePointer);
                customerID:
                rewind(customerDataFilePointer);
                inputcustomerId = rand() % 100 + 1;
                while (fread(&customerDetails1,sizeof(struct booking),1,customerDataFilePointer)){

                    if(inputcustomerId == customerDetails1.customerId){
                        goto customerID;
                    }
                }
                customerDetails.customerId = inputcustomerId;
                customerDetails.food_price = 0;
                 printf("%-127s\n","-------------------------------------------------------------------------------------------------------------------------------");
                printf("| %-20s | %-30s | %-12s | %-12s | %-12s | %-5s | %-15s |\n","Name","Address","CheckIn","CheckOut","Phone","Id","Check In Status");
                printf("%-127s\n","-------------------------------------------------------------------------------------------------------------------------------");
                printf("| %-20s | %-30s | %-2d/%-2d/%-4d%-2s | %-2d/%-2d/%-4d%-2s | %lld | %-5d | %-15s |\n",customerDetails.customerName,customerDetails.customerAddress,customerDetails.checkInDate,customerDetails.checkInMonth,customerDetails.checkInYear,"",customerDetails.checkOutDate,customerDetails.checkOutMonth,customerDetails.checkOutYear,"",customerDetails.customerMobile,customerDetails.customerId,customerDetails.active);
                printf("%-127s\n","-------------------------------------------------------------------------------------------------------------------------------");
                rewind(customerDataFilePointer);
                fseek(customerDataFilePointer,last_posn,SEEK_SET);
                fwrite(&customerDetails,sizeof(struct booking),1,customerDataFilePointer);

                }
                else
                {
                fwrite(&room,sizeof(struct hotel),1,tempFilePointer);
                printf("Room Booking Cancelled !!");
                }

            }
            else{
                if(valid!='y')
                {
                    valid='f';
                }
            fwrite(&room,sizeof(struct hotel),1,tempFilePointer);
            }


        }
        if(valid=='f')
        {
            printf("Invalid Room Number !!!\n");
            printf("Do You Want To Enter Again (y/n) :- ");
            fflush(stdin);
            scanf("%c",&choice);
            if(choice=='y')
            {

            goto enterRoom;
            }
            else{
                    system("cls");
                    printf("You have exited!!\n");
                    exit(0);
            }
        }
        rewind(customerDataFilePointer);
        fclose(customerDataFilePointer);
        fclose(fp);
        fclose(tempFilePointer);
        remove("room.txt");
        rename("temp.txt","room.txt");
        printf("Press Any Key To Continue :- ");
        fflush(stdin);
        scanf("%c",&any);
        printf("\n\nYour Session Expired");
        exit(0);
}

int dateValidator(struct booking *tempCustomerDetails,int date,int month,int year,int flag){
    if(year % 4 == 0){
        if(date >= 1 && date <= 29){
            if(month >= 1 && month <=12){
                if (flag == 0){
                    tempCustomerDetails->checkInDate = date;
                    tempCustomerDetails->checkInMonth = month;
                    tempCustomerDetails->checkInYear = year;
                    return 0;
                }
                else{
                    tempCustomerDetails->checkOutDate = date;
                    tempCustomerDetails->checkOutMonth = month;
                    tempCustomerDetails->checkOutYear = year;
                    return 0;
                }
            }
            else{
                printf("\nThe Inputed Month Is Incorrect");
            }
        }
        else{
            printf("\nThe Inputed Date Is Incorrect");
        }
    }
    else if (date >=1 && date <=31){
        if(month >= 1 && month <=12){
            if (flag == 0){
                tempCustomerDetails->checkInDate = date;
                tempCustomerDetails->checkInMonth = month;
                tempCustomerDetails->checkInYear = year;
                return 0;
            }
            else{
                tempCustomerDetails->checkOutDate = date;
                tempCustomerDetails->checkOutMonth = month;
                tempCustomerDetails->checkOutYear = year;
                return 0;
            }
        }
        else{
            printf("\nThe Inputed Month Is Incorrect");
        }
    }
    else{
        printf("\nThe Inputed Date Is Incorrect");
    }
    return 0;
}

void existing_customer()
{
    int choice;
    choices:
        system("cls");

    printf("1.Room Service\n2.Restaurant\n3.Check Out\n4.Exit");
    printf("\nEnter Your choice :- \n");
    fflush(stdin);
    scanf("%d",&choice);
    if(choice==1)
    {
    	room_services();
	}
    else if(choice==2)
    {
        restaurant();
    }
    else if(choice==3)
    {
      checkout();
    }
    else if(choice==4)
    {
        exit(0);
    }
    else
    {
        printf("Invalid Choice !!");
        goto choices;
    }
}
void restaurant(){
    int i,j,choice,qty,cont,cust_id,verify,n=1,k,total,total_present=0;
    char choice1,flag,any,more,valid,sure;
    struct food f1;
    struct food_bill *bill;
    struct booking b1,b2;
    bill = (struct food_bill *)malloc(n*sizeof(struct food_bill));
    FILE *cp=fopen("customerDataFile.txt","rb");
    FILE *tp=fopen("tempcustomerDataFile.txt","wb");
    enter_cust_id:
    system("cls");
    rewind(cp);
    flag='n';
    printf("Enter Your Customer Id :-");
    scanf("%d",&cust_id);
    system("cls");
    while(fread(&b1,sizeof(struct booking),1,cp))
    {
        verify=strcmp(b1.active,"yes");
        if( (cust_id==b1.customerId) && (verify==0) )
        {
            total=b1.food_price;
            printf("\n\n\nYour Details :- \n\n");
            flag='y';
            printf("%-15s :- %-20s \n%-15s :- %-20d","Name",b1.customerName,"Room Number",b1.roomNumber);
        }
    }
    if(flag=='n')
    {
        printf("Customer Id Doesn't Exist or else would have vacated !! Do You Want To Try again (y/n) ");
        fflush(stdin);
        scanf("%c",&choice1);
        if(choice1=='y')
        {
           goto enter_cust_id;
        }
        else
        {
            goto end_fn;
        }
    }

    printf("\n\nTo display menu Press any key :-");
    fflush(stdin);
    scanf("%c",&any);
    system("cls");
    FILE *fp=fopen("food.txt","rb");
    printf("\t\t\t\t\t\t FOOD MENU\n\n");
    i=0;
    while(fread(&f1,sizeof(struct food),1,fp))
    {
        i++;
        printf("%2d. %-30s %-10d\n",i,f1.food_name,f1.price);
    }
    order:
    printf("\nEnter Your Choice To Order :-");
    scanf("%d",&choice);
    if( (choice>0) && (choice<=i) )
    {
      rewind(fp);
      k=0;
      while(fread(&f1,sizeof(struct food),1,fp))
       {
        k++;
        if(k==choice)
        {
          printf("%-30s $%-10d\n",f1.food_name,f1.price);
          break;
        }

       }
       rewind(fp);
       printf("Enter How Much Quantity :-");
       scanf("%d",&qty);
       strcpy( (bill+n-1)->food_name,f1.food_name);
       (bill+n-1)->price=f1.price;
       (bill+n-1)->qty=qty;
       valid='y';
       total+=((bill+n-1)->price)*(bill+n-1)->qty;
       total_present+=((bill+n-1)->price)*(bill+n-1)->qty;
       printf("Do You Want To Order more (y/n) :- ");
       fflush(stdin);
       scanf("%c",&more);
       if(more=='y')
       {
           n++;
           bill = (struct food_bill *)realloc(bill,n*sizeof(struct food_bill));
           goto order;
       }
       else
       {
           //Bill over bz he stopped ordering case

            goto bill_details;
       }


    }
    else
    {
        printf("Invalid Entry!");
        printf("Press your choice \n1.Order More \n2.Finish order \n3.Cancel\n ");
        scanf("%d",&cont);
        if(cont==1)
        {
           goto order;
        }
        else if(cont==2){
           if(valid=='y')
           {
               goto bill_details;
           }
            else
            {
                system("cls");
                printf("You Haven't ordered anything!!\n");
                goto cancel;
            }
        }
        else if(cont==3)
        {
            goto cancel;
            //cancel his bill details
        }
    }
    bill_details:
           system("cls");
           printf("Your Order details :-\n\n\n");
           printf("\t\t\t Y O U R  B I L L \n\n\n");
           printf("%-30s %-10s %-10s\n","Food","Price","Quantity");
           for(j=0;j<n;j++)
           {
              printf("%-30s %-10d %-10d\n",(bill+j)->food_name,(bill+j)->price,(bill+j)->qty);
           }
           printf("%-50s\n","--------------------------------------------------");
           printf("%-30s %-10d\n","Total",total_present);
           printf("%-50s\n","--------------------------------------------------");

           printf("Are You Sure You Want To Order (y/n) ");
           fflush(stdin);
           scanf("%c",&sure);
           if(sure=='y')
           {
                rewind(cp);
                //Writing total price for customer
                while(fread(&b1,sizeof(struct booking),1,cp))
                {
                  b2=b1;
                  if((cust_id==b1.customerId))
                  {
                    b2.food_price=total;
                    fwrite(&b2,sizeof(struct booking),1,tp);
                  }
                  else
                  {
                    fwrite(&b1,sizeof(struct booking),1,tp);
                  }
                }
            fclose(cp);
            fclose(tp);
            remove("customerDataFile.txt");
            rename("tempcustomerDataFile.txt","customerDataFile.txt");
            printf("\n\nOrder Successfully Placed!\n");
            printf("Order Will Be Serviced Shortly To your room and You can pay at the time of check out!!\n");
           }
           else{
            goto cancel;
           }

           goto end_fn;

    cancel:
        printf("Order cancelled!!");
    end_fn:
        printf("Your Session has expired!!\n");
        printf("Enter any character to continue!");
        fflush(stdin);
        scanf("%c",&any);
    fclose(fp);
    exit(0);
}

//Room Services
void room_services()
{
    FILE *fp, *rsptr;
    struct booking cust;
    struct room_service rs;
    int id, verify, roomno;
    char correct, flag = 'f', choice;

    fp = fopen("customerDataFile.txt", "rb");
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(struct booking); // Getting Total No.of Room Records

    if (n < 1)
    {
        printf("No Rooms Booked Till Now!\n");
        fclose(fp);
        printf("Press Any Key To Go Back!");
        fflush(stdin);
        scanf("%c", &choice);
        existing_customer();
    }

    rewind(fp);

    printf("Welcome to Room Services!\n\n");

verify:
    printf("Enter your Customer ID:- ");
    scanf("%d", &id);

    while (fread(&cust, sizeof(struct booking), 1, fp))
    {
        verify = strcmp(cust.active, "yes");

        if ((id == cust.customerId) && (verify == 0))
        {
            flag = 't';
            printf("\n\nYour Details :- \n\n");
            printf("Customer Name: %s\n", cust.customerName);
            printf("Room Number: %d\n\n", cust.roomNumber);
            roomno = cust.roomNumber;
            printf("Correct? (y/n):- ");
            fflush(stdin);
            correct = getchar();

            if (correct == 'y' || correct == 'Y')
                goto re;
            else
            {
                system("cls");
                printf("Please Enter Room Number Again!\n\n");
                rewind(fp);
                flag = 'f';
                goto verify;
            }
        }
    }

    if (flag != 't')
    {
        system("cls");
        printf("Room Not Found! Please Enter again.\n");
        rewind(fp);
        goto verify;
    }

re:
    rsptr = fopen("roomservice.txt", "ab+");
    fseek(rsptr, 0, SEEK_END);
    n = ftell(rsptr) / sizeof(struct room_service);

    if (n < 1)
    {
        rewind(rsptr);
        rs.custid = id;
        strcpy(rs.active, "yes");
        rs.extrabeds = 0;
        rs.extrabed_bill = 0.0;
        rs.rsbill = 0.0;
        strcpy(rs.vehicle, "null");
        rs.vehicle_bill = 0.0;
        rs.vehicle_days = 0;
        fwrite(&rs, sizeof(struct room_service), 1, rsptr);
    }
    else
    {
        flag = 'f';
        rewind(rsptr);

        while (fread(&rs, sizeof(struct room_service), 1, rsptr))
        {
            verify = strcmp(rs.active, "yes");

            if (id == rs.custid && verify == 0)
            {
                flag = 't';
                break;
            }
        }

        if (flag == 'f')
        {
            rs.custid = id;
            strcpy(rs.active, "yes");
            rs.extrabeds = 0;
            rs.extrabed_bill = 0.0;
            rs.rsbill = 0.0;
            strcpy(rs.vehicle, "null");
            rs.vehicle_bill = 0.0;
            rs.vehicle_days = 0;
            fwrite(&rs, sizeof(struct room_service), 1, rsptr);
        }
    }

    fclose(fp);
    fclose(rsptr);

    int choice1;

repeat:
    printf("\n ------------------------ \n");
    printf("|| 1.Add Extra Bed      ||\n");
    printf("|| 2.Rent Vehicles      ||\n");
    printf("|| 3.Exit               ||\n");
    printf("|| 4.Go Back            ||\n");
    printf(" ------------------------ \n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice1);

    if (choice1 == 1)
    {
        rent_bed(id, roomno);
    }
    else if (choice1 == 2)
    {
        rent_vehicle(id);
    }
    else if (choice1 == 3)
    {
        exit(0);
    }
    else if (choice1 == 4)
    {
        existing_customer();
    }
    else
    {
        system("cls");
        printf("Wrong Choice! Please enter again:\n\n");
        goto repeat;
    }
}

void rent_bed(int id, int roomno)
{
    struct rent
    {
        int beds;
        int price;
    } b[3] = {{1, 499}, {2, 749}, {3, 999}};

    system("cls");
    int beds, i;
    float extrabed_bill, rsbill;
    char correct, flag;

    FILE *rsptr, *rsptr1;
    struct room_service rs, rs1;

    int extrabed = 0;  // Declare extrabed outside the if block

extra_bed:
    printf("\n  -------------- \n");
    printf("| Beds | Price |\n");
    for (i = 0; i < 3; i++)
    {
        printf("  -------------- \n");
        printf("|  %d   | $%d  |\n", b[i].beds, b[i].price);
    }
    printf("  -------------- \n\n");
    printf("Select the number of beds:- ");
    scanf("%d", &beds);
    flag = 'f';
    for (i = 0; i < 3; i++)
    {
        if (beds == b[i].beds)
        {
            flag = 't';
            printf("You have selected %d extra beds at an extra charge of: $%d\n", b[i].beds, b[i].price);
            printf("Do you want to continue? (y/n): ");
            fflush(stdin);
            correct = getchar();
            if (correct == 'y' || correct == 'Y')
            {
                extrabed = b[i].beds;
                extrabed_bill = b[i].price; // Call these variables for payment()/
            }
            else
            {
                goto extra_bed;
            }
        }
    }

    if (flag != 't')
    {
        system("cls");
        printf("Invalid entry! Please enter again.");
        goto extra_bed;
    }

    printf("Do you want to pay your bill now?(y/n): ");
    fflush(stdin);
    correct = getchar();

    if (correct == 'y' || correct == 'Y')
    {
        printf("Make your payment to complete your order.\n");
        // call payment
        payment(extrabed_bill);
        printf("Thanks for your order....The bed will be delivered to your room - %d\n", roomno);
        rsbill = 0.0;
    }
    else
    {
        printf("Please pay your room services bill during checkout.\n");
        printf("Thanks for your order....The bed will be delivered to your room - %d\n", roomno);
        rsbill = extrabed_bill;
    }

    rsptr = fopen("roomservice.txt", "rb");
    rsptr1 = fopen("temp.txt", "wb+");

    while (fread(&rs, sizeof(struct room_service), 1, rsptr))
    {
        int verify = strcmp(rs.active, "yes");

        if (rs.custid == id && verify == 0)
        {
            rs1.custid = rs.custid;
            strcpy(rs1.active, rs.active);
            rs1.extrabeds = rs.extrabeds + extrabed;
            rs1.extrabed_bill = rs.extrabed_bill + extrabed_bill;
            rs1.rsbill = rs.rsbill + rsbill;
            strcpy(rs1.vehicle, "null");
            rs1.vehicle_bill = rs.vehicle_bill;
            rs1.vehicle_days = rs.vehicle_days;
            fwrite(&rs1, sizeof(struct room_service), 1, rsptr1);
        }
        else
        {
            fwrite(&rs, sizeof(struct room_service), 1, rsptr1);
        }
    }

    fclose(rsptr);
    fclose(rsptr1);
    remove("roomservice.txt");
    rename("temp.txt", "roomservice.txt");
}

void rent_vehicle(int id)
{
    struct rent
    {
        char vehicle[10];
        float rpd;
    } b[3] = {{"Cycle", 99.89}, {"Bike", 499.45}, {"Car", 1399.78}};

    system("cls");
    int i, opt, days, tdays, verify;
    float vbill = 0.0, rsbill;
    char correct, vehicle[20];

vehicle:
    printf("\n--------------------------------- \n");
    printf("| S.No | Vehicle Type | Rent/Day |\n");
    for (i = 0; i < 3; i++)
    {
        printf("  ------------------------------ \n");
        printf("|  %-1d   | %-11s  | %0.2f |\n", i + 1, b[i].vehicle, b[i].rpd);
    }
    printf("  ------------------------------ \n");
    printf("\nEnter a Vehicle type(1-3):- ");
    scanf("%d", &opt);

    if (opt >= 1 && opt <= 3)
    {
        vbill = b[opt - 1].rpd;
        strcpy(vehicle, b[opt - 1].vehicle);
        goto days;
    }
    else
    {
        system("cls");
        printf("You have entered a wrong choice! Please enter again.\n\n");
        goto vehicle;
    }

days:
    printf("\nEnter Number of days for rent:- ");
    scanf("%d", &days);
    tdays = days_cal(id);

    if (days <= 0 || days > tdays)
    {
        printf("\n\nYou have entered a day which exceeds your number of staying days or an invalid day! Please enter again.\n");
        goto days;
    }
    vbill *= days;

    printf("Do you want to pay your bill now?(y/n): ");
    fflush(stdin);
    correct = getchar();

    if (correct == 'y' || correct == 'Y')
    {
        printf("Make your payment to complete your order.\n");
        // call payment
        payment(vbill);
        rsbill = 0.0;
    }
    else
    {
        printf("Please pay your room services bill during checkout.\n");
        rsbill = vbill;
    }

    FILE *rsptr, *rsptr1;
    struct room_service rs, rs1;
    rsptr = fopen("roomservice.txt", "rb");
    rsptr1 = fopen("temp.txt", "wb+");
    fseek(rsptr, 0, SEEK_END);

    rewind(rsptr);

    while (fread(&rs, sizeof(struct room_service), 1, rsptr))
    {
        verify = strcmp(rs.active, "yes");
        if (rs.custid == id && verify == 0)
        {
            rs1.custid = rs.custid;
            strcpy(rs1.active, rs.active);
            rs1.extrabeds = rs.extrabeds;
            rs1.extrabed_bill = rs.extrabed_bill;
            rs1.rsbill = rs.rsbill + rsbill;
            rs1.vehicle_bill = rs.vehicle_bill + vbill;
            strcpy(rs1.vehicle, vehicle);
            rs1.vehicle_days = rs.vehicle_days + days;
            fwrite(&rs1, sizeof(struct room_service), 1, rsptr1);
        }
        else
        {
            fwrite(&rs, sizeof(struct room_service), 1, rsptr1);
        }
    }

    fclose(rsptr);
    fclose(rsptr1);
    remove("roomservice.txt");
    rename("temp.txt", "roomservice.txt");
}

int days_cal(int id)
{
	int tdays=0;
	FILE *fp=fopen("customerDataFile.txt","rb");
	struct booking cust;

	while(fread(&cust,sizeof(struct booking),1,fp))
	{
		if(id==cust.customerId)
		{
			tdays+=(cust.checkOutYear-cust.checkInYear)*365;
			tdays+=(cust.checkOutMonth-cust.checkInMonth)*31;
			tdays+=(cust.checkOutDate-cust.checkInDate);
			break;
		}
	}
	return tdays;
}


void checkout()
{
    char flag,choice1;
    int verify,room_rent_per_day,checkInDate,checkInMonth,checkInYear,checkOutDate,checkOutMonth,checkOutYear,cust_id,roomno,ID,discount;
    float cost1=0,cost2=0,cost3=0,SGST,CGST,extra_cost,total;
    int days;
    char choice,mem1,mem2;
    struct membership member;
    struct date s1, s2;
    struct booking b1,b2;
    struct hotel room,room1;
    struct room_service r1;
    FILE *fp=fopen("room.txt","rb");
    FILE *cp=fopen("customerDataFile.txt","rb");
    FILE *rp=fopen("roomservice.txt","rb");
    printf("\nYou have opted to checkout\n");
    printf("\nDo you want to proceed(y/n)\n");
    fflush(stdin);
    scanf("%c",&choice);

    if(choice=='y')
    {
        enter_cust_id:
         system("cls");
         rewind(cp);
         flag='n';
         printf("Enter Your Customer Id :-");
         scanf("%d",&cust_id);
         system("cls");
         while(fread(&b1,sizeof(struct booking),1,cp))
           {
             verify=strcmp(b1.active,"yes");

             if( (cust_id==b1.customerId) && (verify==0) )
               {
                 roomno=b1.roomNumber;
                 printf("\n\n\nYour Details :- \n\n");
                 flag='y';
                 printf("%-15s :- %-20s \n%-15s :- %-20d","Name",b1.customerName,"Room Number",b1.roomNumber);
                 checkInDate=b1.checkInDate;
                 checkInMonth=b1.checkInMonth;
                 checkInYear=b1.checkInYear;
                 checkOutDate=b1.checkOutDate;
                 checkOutMonth=b1.checkOutMonth;
                 checkOutYear=b1.checkOutYear;
                 cost2=b1.food_price;  //Customer's food price
               }
           }
           rewind(cp);
         if(flag=='n')
           {
              printf("Customer Id Doesn't Exist or else would have vacated !! Do You Want To Try again (y/n) ");
              fflush(stdin);
              scanf("%c",&choice1);
              if(choice1=='y')
              {
                goto enter_cust_id;
              }
              else
              {
                goto end_fn;
               }
            }
            //Now we got cust id so with that room no we are gng to get rent and room type
            rewind(fp);
             while(fread(&room,sizeof(struct hotel),1,fp))
              {
                 if(room.room_number==roomno)
                 {
                 printf("\nDetails of Room :- \n");
                 printf(" ---------------------------------------------                \n");
                 printf("|Room Number  |Room Type        | Room Rent  |                \n");
                 printf(" ---------------------------------------------                 \n");
                 printf("| %-11d | %-15s | $%-9d |\n",room.room_number,room.room_type,room.room_rent);
                 printf(" ---------------------------------------------                \n");
                 room_rent_per_day=room.room_rent;
               }
            }
            rewind(rp);
            while(fread(&r1,sizeof(struct room_service),1,rp))
             {
               if(cust_id == r1.custid)
               {
                   cost3=r1.rsbill;

               }
             }
        s1.years=checkInYear;
        s1.months=checkInMonth;
        s1.days=checkInDate;
        s2.years=checkOutYear;
        s2.months=checkOutMonth;
        s2.days=checkOutDate;
        days=diff( s1,  s2);
        if(days==0)
            days+=1;
        //printf("\n%d --> %d\n",room_rent_per_day,days);
        cost1=room_rent_per_day*days;
        CGST= ( 0.07 *(cost1) )+(0.03)*(cost2);
        SGST= (0.07)*(cost1);
        //printf("\n---> %f and %f <---\n",CGST,SGST);
        printf("\nDo you have our hotel's membership card?(y/n)\n");
        fflush(stdin);
        scanf("%c",&mem1);
        if(mem1=='y')
        {
        	int i;
         printf("\nEnter your 3 digit membership ID\n");
         scanf("%d",&ID);
         extra_cost=0;
         int* ptr;
         int n=12;
         ptr = (int*)malloc(n * sizeof(int));
         for(i=0;i<12;i++)
         {
            if((i==3)||(i==9)||(i==10)||(i==11))
            {
                printf("sfsfs");
            *(ptr+i)=1000;

            }
            else
            {
             *(ptr+i)=700;
            }

         }
         discount=*(ptr+checkOutMonth);
         //printf("\n%d and %d",discount,*(ptr+checkOutMonth));
        }
        else
        {
            printf("\nDo you want to avail our hotel's membership card to enjoy special discounts?(y/n)\n");
            fflush(stdin);
            scanf("%c",&mem2);
            if(mem2=='y')
            {
              printf("\nEnter your name\n");
              fflush(stdin);
              scanf("%[^\n]%*c",member.name);
              printf("\nEnter your phone number\n");
              scanf("%ld",&member.phonenumber);
              printf("\nYou will be charged an extra amount of 1000 RS\n");
              printf("\n Please note down your id\n");
              srand(time(NULL));
              int id = rand()%1000 + 1;
              printf("Your membership ID is %d",id);
              extra_cost=1000;
              discount=0;
            }
            else
            {
                extra_cost=0;
                discount=0;
            }
        }
        total=cost1+cost2+cost3+CGST+SGST+extra_cost-discount;
        printf("\nPrinting Receipt..\n");
        printf("          ROOM RENT     :        %-4f\n",cost1);
        printf("          ROOM SERVICE  :        %-4f\n",cost3);
        printf("          RESTAURANT    :        %-4f\n",cost2);
        printf("          CGST          :        %-4f\n",CGST);
        printf("          SGST          :        %-4f\n",SGST);
        printf("          MEMBERSHIP    :        %-4f\n",extra_cost);
        printf("          DISCOUNT      :        %-4d\n",discount);
        printf("          TOTAL         :        %-4f\n",total);
        payment(total);
        fclose(fp);
        fclose(cp);
        fclose(rp);
        //Customer file active --> no
         FILE *cp=fopen("customerDataFile.txt","rb");
         FILE *tcp=fopen("temp_checkout_customerDataFile.txt","wb");
         while(fread(&b1,sizeof(struct booking),1,cp))
         {
             b2=b1;
             if(cust_id==b1.customerId)
             {
                 strcpy(b2.active,"no");
                 b2.food_price=0;
                 fwrite(&b2,sizeof(struct booking),1,tcp);
             }
             else
             {
                 fwrite(&b1,sizeof(struct booking),1,tcp);
             }

         }
         fclose(cp);
         fclose(tcp);
         remove("customerDataFile.txt");
         rename("temp_checkout_customerDataFile.txt","customerDataFile.txt");
         //vacancy to yes
          FILE *rp=fopen("room.txt","rb");
          FILE *trp=fopen("temp_room.txt","wb");
         while(fread(&room,sizeof(struct hotel),1,rp))
         {
             room1=room;
             if(roomno==room.room_number)
             {
                 strcpy(room1.vacancy,"yes");
                 fwrite(&room1,sizeof(struct hotel),1,trp);
             }
             else
             {
                 fwrite(&room,sizeof(struct hotel),1,trp);
             }

         }
         fclose(rp);
         fclose(trp);
         remove("room.txt");
         rename("temp_room.txt","room.txt");
         //rs files
         FILE *rsptr,*rsptr1;
        struct room_service rs;
        rsptr=fopen("roomservice.txt","rb");
        rsptr1=fopen("temp.txt","wb+");
        while(fread(&rs,sizeof(struct room_service),1,rsptr))
        {
        if(rs.custid==cust_id)
        {
        continue;
        }
        else
        {
        fwrite(&rs,sizeof(struct room_service),1,rsptr1);
        }
        }
        fclose(rsptr);
        fclose(rsptr1);
        remove("roomservice.txt");
        rename("temp.txt","roomservice.txt");
    }
    else{
        goto end_fn;
    }
    end_fn: ;

}

int days_date(struct date s)
{
    int i, k;
    int sum = 0;
    for (i = 1; i < s.years; i++)
    {
        if ((s.years % 4 == 0) && ((s.years % 100 != 0) || (s.years % 400 == 0)))
            sum += 366;
        else
            sum += 365;
    }

    for (k = 1; k < s.months; k++)
        sum += days_on_month[k];

    return sum + s.days;
}
int diff(struct date s1, struct date s2)
{

    if(days_date(s1)>days_date(s2))
    {
        return days_date(s1)-days_date(s2);
    }
    else
    {
          return days_date(s2)-days_date(s1);
    }

}
int payment(float total)
{
    int n;
    struct Debitcard{
        int card_number;
        int month;
        int year;
        int cvv;
        int otp;
    } pay_debit;
    struct Creditcard{
        int card_number;
        int code;
        int month;
        int year;
        int otp;
    } pay_credit;
    struct UPI{
        char upi_id;
        int upicode;
    } pay_upi;
    printf("total amount to be paid is %f\n",total);
    printf("\nChoose any of the following payment methods:\n");
    printf("\n_____________________________________________\n");
    printf("\n               1.DEBIT CARD                 \n");
    printf("\n               2.CREDIT CARD                \n");
    printf("\n               3.UPI                        \n");
    printf("\n_____________________________________________\n");
    printf("\nEnter your choice (1 or 2 or 3)\n");
    scanf("%d", &n);
    if (n==1){
        printf("\nEnter debit card number\n");
        scanf("%d", &pay_debit.card_number);
        printf("\nEnter expiry month\n");
        scanf("%d", &pay_debit.month);
        printf("\nEnter expiry year\n");
        scanf("%d", &pay_debit.year);
        printf("\nEnter cvv\n");
        scanf("%d", &pay_debit.cvv);
        printf("\nEnter otp\n");
        scanf("%d", &pay_debit.otp);
        printf("\nPayment Successful\n");
        printf("\nThank you for choosing us\n");
    }else if (n==2){
        printf("\nEnter credit card number\n");
        scanf("%d", &pay_credit.card_number);
        printf("\nEnter expiry month\n");
        scanf("%d", &pay_credit.month);
        printf("\nEnter expiry year\n");
        scanf("%d", &pay_credit.year);
        printf("\nEnter cvv\n");
        scanf("%d", &pay_credit.code);
        printf("\nEnter otp\n");
        scanf("%d", &pay_credit.otp);
        printf("\nPayment Successful\n");
        printf("\nThank you for choosing us\n");
    }else if (n==3){
        printf("\nEnter upi id\n");
        scanf("%12s", &pay_upi.upi_id);
        printf("\nEnter upicode\n");
        scanf("%d", &pay_upi.upicode);
        printf("\nPayment Successful\n");
        printf("\nThank you for choosing us\n");
    }else{
        printf("\nInvalid choice\n");
    }    
    return 0;
}