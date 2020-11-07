#include <stdio.h>
#include "conio2.h"
#include "rlyres.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int enterchoice()
{
    int choice,i;
    int flag=0;
    while(flag==0)
    {
        clrscr();
        //system("color 06");
        textcolor(YELLOW);
        gotoxy(28,1);
        printf("RAILWAY RESERVATION SYSTEM\n");
        for(i=1;i<=80;i++) printf("-");
        printf("\nSelect an option");
        printf("\n1- View Train\n2- Book Ticket\n3- View Ticket\n4- Search Ticket NO\n5- View All Bookings\n6- View");
        printf(" Train Bookings\n7- Cancel Ticket\n8- Cancel Train\n9- All Canceled bookings\n10- Quit\n");
        printf("\nEnter Choice: ");
        scanf("%d",&choice);
        if (choice > 10 || choice < 1)
        {
            textcolor(RED);
            printf("\nWrong choice try again");
            getch();
            continue;
        }
        flag=1;
    }
    return choice;
}

void add_trains()
{
    FILE *fp;
    Train alltrains[]={
    {"123","HBJ","REWA",500,300},
    {"124","BPL","DELHI",700,200},
    {"143","BPL","STA",1000,600},
    {"1230","DELHI","JAIPUR",1000,300},
    {"1234","KASH","KANYA",800,600}};
    fp=fopen(".\\alltrains.dat","rb");
    if (fp==NULL)
    {
        fp=fopen(".\\alltrains.dat","wb");
        fwrite(&alltrains,5*sizeof(Train),1,fp);
        printf("FIle created Succesfully");
        fclose(fp);
        getch();
    }
    else
    {
        printf("Trains details are already present");
        fclose(fp);
        getch();
    }
}

void view_trains()
{
    int i;
    clrscr();
    Train train;
    FILE *fp;
    fp=fopen(".\\alltrains.dat","rb");
    if (fp==NULL)
    {
        printf("alltrains.dat file is not present");
        getch();
        return;
    }
    textcolor(YELLOW);
    printf("Train no\tFROM\t\tTO\tFirst AC fare\tSecond AC fare\n");
    for(i=1;i<=80;i++) printf("-");
    printf("\n");
    while(fread(&train,sizeof(train),1,fp)==1)
    {
        printf("%s\t\t%s\t\t%s\t\t%d\t\t%d\n",train.train_no,train.from,train.to,train.fac_fare,train.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
}

int check_train_no(char *c,char clas)
{
    //printf("Passed");
    FILE *fp;
    FILE *fct;
    int flag=0;
    Train tr;
    fp=fopen(".\\alltrains.dat","rb");
    fct=fopen(".\\can_train.dat","rb");
    if (fp==NULL)
    {
        printf("alltrains.dat");
        getch();
        exit(0);
    }
    if(fct==NULL) flag=1;
    while(fread(&tr,sizeof(Train),1,fp)==1)
    {
        if (strcmp(tr.train_no,c)==0)
        {
            if (clas=='F')
            {
                fclose(fp);
                return tr.fac_fare;
            }
            else
            {
                fclose(fp);
                return tr.sac_fare;
            }
        }
    }
    fclose(fp);
    if (flag==0)
    {
    while(fread(&tr,sizeof(Train),1,fct)==1)
    {

        if (strcmp(tr.train_no,c)==0)
        {
            fclose(fct);
            return -1;
        }
    }
    }
    fclose(fct);
    //printf("Passed");
    return 0;
}

Passenger *get_passenger_details()
{
    char *c;
    char cond[2]={'0','\0'};
    //FILE *fp=fopen(".\\allbookings.dat","ab+");
    static Passenger pas;
    textcolor(GREEN);
    gotoxy(105,1);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(LIGHTMAGENTA);
    printf("Passenger Name: ");
    textcolor(YELLOW);
    fflush(stdin);
    fgets(pas.p_name,30,stdin);
    c=strchr(pas.p_name,'\n');
    *c='\0';
    if (strcmp(pas.p_name,cond)==0)
    {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("Booking Canceled!");
        textcolor(YELLOW);
        getch();
        return NULL;
    }
    textcolor(LIGHTGREEN);
    printf("Gender (M or F): ");
    textcolor(YELLOW);
    fflush(stdin);
    while(1)
    {
    fflush(stdin);
    textcolor(YELLOW);
    scanf("%c",&pas.gender);
    if (pas.gender=='M' || pas.gender=='F') break;
    else if (pas.gender=='0')
    {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,30);
        printf("Reservation Canceled!");
        textcolor(YELLOW);
        getch();
        return NULL;
    }
    else
    {
        gotoxy(1,30);
        printf("\t\t\t\t\t\t");
        gotoxy(1,30);
        textcolor(RED);
        printf("Gender should be M or F (in uppercase)!");
        getch();
        gotoxy(18,2);
        printf("\t\t\t\t\t\t\t\t\t\t\t");
        gotoxy(18,2);
    }
    }
    //to clear buttom
    gotoxy(1,30);
    printf("\t\t\t\t\t\t");
    gotoxy(1,3);

    textcolor(LIGHTCYAN);
    printf("Class First Ac 'F' or Second AC 'S': ");
    textcolor(YELLOW);
    while (1)
    {
        textcolor(YELLOW);
        fflush(stdin);
        scanf("%c",&pas.p_class);
        if (pas.p_class=='F' || pas.p_class=='S') break;
    else if (pas.p_class=='0')
    {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,30);
        printf("Reservation Canceled!");
        textcolor(YELLOW);
        getch();
        return NULL;
    }
    else
    {
        gotoxy(1,30);
        printf("\t\t\t\t\t\t");
        gotoxy(1,30);
        textcolor(RED);
        printf("Class should be F or S (in uppercase)!");
        getch();
        gotoxy(38,3);
        printf("\t");
        gotoxy(38,3);
    }
    }

    //to clear buttom
    gotoxy(1,30);
    printf("\t\t\t\t\t\t");
    gotoxy(1,4);
    //train no
    textcolor(LIGHTBLUE);
    printf("Train no: ");
    textcolor(YELLOW);
    while(1)
    {
    fflush(stdin);
    textcolor(YELLOW);
    scanf("%s",pas.train_no);
    pas.fare=check_train_no(pas.train_no,pas.p_class);
    if (strcmp(pas.train_no,cond)==0)
    {
       gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,30);
        printf("Reservation Canceled!");
        textcolor(YELLOW);
        getch();
        return NULL;
    }
    else if(pas.fare==0)
    {
        gotoxy(1,30);
        printf("\t\t\t\t\t\t");
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("Invalid Train No.");
        getch();
        gotoxy(11,4);
        printf("\t\t");
        gotoxy(11,4);
    }
    else if(pas.fare<0)
    {
        gotoxy(1,30);
        printf("\t\t\t\t\t\t");
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("Train no. %s has been canceled",pas.train_no);
        getch();
        gotoxy(11,4);
        printf("\t\t");
        gotoxy(11,4);
    }
    else break;
    }


    //to clear buttom
    gotoxy(1,30);
    printf("\t\t\t\t\t\t");
    gotoxy(1,5);

    textcolor(BROWN);
    printf("Address: ");
    textcolor(YELLOW);
    fflush(stdin);
    fgets(pas.address,30,stdin);
    c=strchr(pas.address,'\n');
    *c='\0';
    if (strcmp(pas.address,cond)==0)
    {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("Reservation Canceled!");
        textcolor(YELLOW);
        getch();
        return NULL;
    }

    //to clear buttom
    gotoxy(1,30);
    printf("\t\t\t\t\t\t");
    gotoxy(1,6);

    textcolor(LIGHTGREEN);
    printf("Age: ");
    textcolor(YELLOW);
    while(1)
    {
        fflush(stdin);
        textcolor(YELLOW);
        scanf("%d",&pas.age);
        if (pas.age>200 || pas.age < 0)
        {
            gotoxy(1,30);
        printf("\t\t\t\t\t\t");
        gotoxy(1,30);
        textcolor(RED);
        printf("Invalid Age!");
        getch();
        gotoxy(6,6);
        printf("\t\t\t");
        gotoxy(6,6);
        }
        else if (pas.age==0)
    {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,30);
        printf("Reservation Canceled!");
        textcolor(YELLOW);
        getch();
        return NULL;
    }
    else break;
    }

    //to clear buttom
    gotoxy(1,30);
    printf("\t\t\t\t\t\t");
    gotoxy(1,7);

    textcolor(LIGHTGRAY);
    printf("Mobile number: ");
    textcolor(YELLOW);
    while(1)
    {
        fflush(stdin);
        textcolor(YELLOW);
        scanf("%s",pas.mob_no);
        if (check_mob_no(pas.mob_no)==0)
        {
            gotoxy(1,30);
        printf("\t\t\t\t\t\t");
        gotoxy(1,30);
        textcolor(RED);
        printf("Invalid mobile no!");
        getch();
        gotoxy(16,7);
        printf("\t\t\t\t\t\t\t");
        gotoxy(16,7);
        }

        else if (strcmp(pas.mob_no,"0")==0)
    {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,30);
        printf("Reservation Canceled!");
        textcolor(YELLOW);
        getch();
        return NULL;
    }
    else break;
    }
    //fwrite(&pas,sizeof(Passenger),1,fp);
    return &pas;
}

int check_mob_no(char *mobno)
{
    int i;
    if (strlen(mobno)>10 || strlen(mobno)<10)
        {
            return 0;
        }
    for (i=0;i<10;i++)
    {
        if (isdigit(mobno[i])==0) return 0;
    }
    return 1;
}

int get_booked_ticket_count(char *train,char clas)
{
    FILE *fp;
    Passenger pas;
    int count=0;
    fp=fopen(".\\allbookings.dat","rb");
    if (fp==NULL)
    {
        return count;
    }
    while(fread(&pas,sizeof(Passenger),1,fp)==1)
    {
        if (strcmp(pas.train_no,train)==0 && pas.p_class==clas)
        {
            count++;
        }
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE *fp=fopen(".\\allbookings.dat","rb");
    Passenger pas;
    if (fp==NULL) return 0;
    fseek(fp,-1*sizeof(Passenger),SEEK_END);
    fread(&pas,sizeof(Passenger),1,fp);
    fclose(fp);
    if (pas.ticketno<0 || pas.ticketno> 19000)
        return 0;
    //printf("Debug: %d",pas.ticketno);
    return pas.ticketno;
}

int book_ticket(Passenger pas)
{
    FILE *fp;
    //else if (pas== NULL)
    if(get_booked_ticket_count(pas.train_no,pas.p_class)>=30)
    {
        textcolor(LIGHTRED);
        printf("all seats are booked in train no %s in %c class",pas.train_no,pas.p_class);
        textcolor(YELLOW);
        getch();
        return -1;
    }
    pas.ticketno=last_ticket_no()+1;
    fp=fopen(".\\allbookings.dat","ab+");
    if (fp==NULL)
    {
        fp=fopen(".\\allbooking.dat","wb+");
    }

    fwrite(&pas,sizeof(Passenger),1,fp);
    fclose(fp);
    return pas.ticketno;
}

void view_all_bookings()
{
    FILE *fp;
    int i;
    char *c;
    Passenger pas;
    clrscr();
    fp=fopen(".\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo ticket is booked till now!");
        textcolor(WHITE);
        printf("\n\n\n\n Press any key to continue");
        getch();
        return;
    }

    else if (last_ticket_no()==0)
    {
        textcolor(LIGHTRED);
        printf("\nAll bookings has been canceled!");
        textcolor(WHITE);
        printf("\n\n\n\n Press any key to continue");
        getch();
        return;
    }

    textcolor(YELLOW);
    for (i=0;i<80;i++) printf("-");
    printf("Ticket Number \tName\t Gender\t Age\tMobile Number \tTrain Number \tCoach \tFare \tAddress \n");
    for (i=0;i<80;i++) printf("-");
    while(fread(&pas,sizeof(Passenger),1,fp)==1)
    {
        i=strlen(pas.p_name);
        //temp=i;
        if (i<=10)
        {
            i=10-i;
            printf("\n       %d \t%s",pas.ticketno,pas.p_name);
            while (i)
            {
                printf(" ");
                i--;
            }
        }
        else
        {
            //jaha space hai uska address
            c=strchr(pas.p_name,' ');
            // uss address ko base address se minus krne me index number mil jyega uska
            c=c-pas.p_name;

            //agar first name 10 char se badha ho to
            if ((int)c>10) c=10;
            //printf("C= %d\n",c);
            printf("\n       %d \t",pas.ticketno);
            for (i=0;i<c;i++)
            {
                printf("%c",pas.p_name[i]);
            }
            i=10-(int)c;
            while (i)
            {
                printf(" ");
                i--;
            }
            //sir name printing ke liye

        }

        printf("  %c\t %d \t %s\t    %s \t  %c \t%d \t%s",pas.gender,pas.age,pas.mob_no,pas.train_no,pas.p_class,pas.fare,pas.address);
    }
    fclose(fp);
    printf("\n\n\n\n");
    textcolor(WHITE);
    printf("Press any key to continue");
    textcolor(YELLOW);
    getch();
}

int accept_ticket_number()
{
    int i;
    clrscr();
    textcolor(GREEN);
    gotoxy(105,1);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter Ticket Number: ");
    while (1)
    {
        fflush(stdin);
        scanf("%d",&i);
        gotoxy(1,30);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,2);
        if (i<0)
        {
            gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("Invalid Ticket number!");
            getch();
            gotoxy(22,1);
            printf("\t\t\t\t\t");
            textcolor(YELLOW);
            gotoxy(22,1);
            continue;
        }
        else if (i==0)
    {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,30);
        printf("Canceling process has been canceled!");
        textcolor(YELLOW);
        getch();
        return -2;
    }
        else if (i>last_ticket_no()+1000)
    {
        textcolor(LIGHTRED);
        printf("\n\t\tTicket not found!");
        getch();

        return 0;

    }
    break;
    }
    return i;
}

void view_ticket(int n)
{
    Passenger pas;
    Passenger *ptr;
    int flag=0;
    FILE *fp=fopen(".\\allbookings.dat","rb");
    if (fp==NULL)
    {
        clrscr();
        textcolor(RED);
        printf("No booking has been made!");
        getch();
        return;
    }
    clrscr();
    if (n==0)
    {
        fclose(fp);
        return;
    }
    while(fread(&pas,sizeof(Passenger),1,fp)==1)
    {
        if (pas.ticketno==n)
        {
            textcolor(GREEN);
            printf("Ticket no. %d",pas.ticketno);
            textcolor(LIGHTGREEN);
            color_label("\nName ",LIGHTGREEN);
            printf("%s",pas.p_name);
            color_label("\nGender ",LIGHTGREEN);
            printf("%c",pas.gender);
            color_label("\nAge ",LIGHTGREEN);
            printf("%d",pas.age);
            color_label("\nMobile Number: ",LIGHTGREEN);
            printf("%s",pas.mob_no);
            color_label("\nTrain Number: ",LIGHTGREEN);
            printf("%s",pas.train_no);
            color_label("\nCoach: ",LIGHTGREEN);
            printf("%c",pas.p_class);
            color_label("\nFare ",LIGHTGREEN);
            printf("%d",pas.fare);
            color_label("\nAddress: ",LIGHTGREEN);
            printf("%s",pas.address);
            //printf("\nName: %s\nGender: %c\nAge: %d\nMobile Number: %s\nTrain Number: %s\nCoach: %c\nFare: %d\nAddress: %s\n\n",pas.p_name,pas.gender,pas.age,pas.mob_no,pas.train_no,pas.p_class,pas.fare,pas.address);
            flag=1;
            break;
        }
    }
    if (flag==0)
    {
        ptr=cancel_record_r(n);
        if (ptr==NULL)
        {
           fclose(fp);
           return;
        }
        pas=*ptr;
        //else
        //{
            textcolor(RED);
            printf("Ticket has been canceled!");
            printf("\nDetails was: \n");
            textcolor(GREEN);
            printf("Ticket no. %d",pas.ticketno);
            textcolor(LIGHTGREEN);
            color_label("\nName ",LIGHTGREEN);
            printf("%s",pas.p_name);
            color_label("\nGender ",LIGHTGREEN);
            printf("%c",pas.gender);
            color_label("\nAge ",LIGHTGREEN);
            printf("%d",pas.age);
            color_label("\nMobile Number: ",LIGHTGREEN);
            printf("%s",pas.mob_no);
            color_label("\nTrain Number: ",LIGHTGREEN);
            printf("%s",pas.train_no);
            color_label("\nCoach: ",LIGHTGREEN);
            printf("%c",pas.p_class);
            color_label("\nFare ",LIGHTGREEN);
            printf("%d",pas.fare);
            color_label("\nAddress: ",LIGHTGREEN);
            printf("%s",pas.address);
        //}
    }
    printf("\n\n\n\n");
    textcolor(WHITE);
    printf("Press any key to continue");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}

void color_label(char *label,int color)
{
    textcolor(GREEN);
    printf("%s",label);
    textcolor(color);
}

void view_bookings(char *tra)
{
    FILE *fp;
    int i,flag=0;
    char *c;
    Passenger pas;
    clrscr();
    if (tra==NULL) return;
    fp=fopen(".\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(RED);
        printf("\n\nNO ticket is booked till now!");
        textcolor(YELLOW);
        getch();
        return;
    }

    textcolor(YELLOW);
    for (i=0;i<80;i++) printf("-");
    printf("Ticket Number \tName\t Gender\t Age\tMobile Number \tTrain Number \tCoach \tFare \tAddress \n");
    for (i=0;i<80;i++) printf("-");
    while(fread(&pas,sizeof(Passenger),1,fp)==1)
    {
        if (strcmp(pas.train_no,tra)==0)
        {
        i=strlen(pas.p_name);
        //temp=i;
        if (i<=10)
        {
            i=10-i;
            printf("\n       %d \t%s",pas.ticketno,pas.p_name);
            while (i)
            {
                printf(" ");
                i--;
            }
        }
        else
        {
            //jaha space hai uska address
            c=strchr(pas.p_name,' ');
            // uss address ko base address se minus krne me index number mil jyega uska
            c=c-pas.p_name;
            //agar first name 10 char se badha ho to
            if (c>10) c=10;
            //printf("C= %d\n",c);
            printf("\n       %d \t",pas.ticketno);
            for (i=0;i<c;i++)
            {
                printf("%c",pas.p_name[i]);
            }
            i=10-(int)c;
            while (i)
            {
                printf(" ");
                i--;
            }

        }

        printf("  %c\t %d \t %s\t    %s \t  %c \t%d \t%s",pas.gender,pas.age,pas.mob_no,pas.train_no,pas.p_class,pas.fare,pas.address);
        flag=1;
    }
    }
    if (flag==0)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("No booking has been made for train no ");
        textcolor(LIGHTGREEN);
        printf("%s",tra);
    }
    fclose(fp);
    printf("\n\n\n\n");
    textcolor(WHITE);
    printf("Press any key to continue");
    textcolor(YELLOW);
    getch();
}

int cancel_ticket(int n)
{
    Passenger pas;
    int flag=0;
    if (n==-2) return -2;
    FILE *fp=fopen(".\\allbookings.dat","rb");
    if (fp==NULL)
        return 0;

    FILE *fp1=fopen(".\\tmp.dat","wb");
    if (fp1==NULL)
        return -1;

    while(fread(&pas,sizeof(Passenger),1,fp)==1)
    {
        if (pas.ticketno!=n) fwrite(&pas,sizeof(Passenger),1,fp1);
        else
        {
            flag=1;
            cancel_record_w(pas);
        }
    }
    if (flag==1)
    {
        fclose(fp);
        fclose(fp1);
        remove(".\\allbookings.dat");
        rename(".\\tmp.dat",".\\allbookings.dat");
        return 1;
    }
    else
    {
        fclose(fp);
        fclose(fp1);
        remove(".\\tmp.dat");
        return 0;
    }
}

void cancel_record_w(Passenger can_pas)
{
    FILE *cp=fopen(".\\cancel_records.dat","ab");
    if (cp==NULL)
    {
        cp=fopen(".\\cancel_records.dat","wb");
        if (cp==NULL)
        {
            textcolor(RED);
            printf("Unable to create cancel_records.dat file!");
            getch();
            return;
        }
    }
    fwrite(&can_pas,sizeof(Passenger),1,cp);
    fclose(cp);
    return;
}

Passenger *cancel_record_r(int n)
{
    static Passenger can_pas;
    int flag=0;
    FILE *cp=fopen(".\\cancel_records.dat","rb");
    if (cp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No booking has been canceled till now!");
        getch();
        return NULL;
    }
    while(fread(&can_pas,sizeof(Passenger),1,cp)==1)
    {
        if (can_pas.ticketno==n)
        {
            flag=1;
            break;
        }
    }
    if (flag==1)
    {
        fclose(cp);
        return &can_pas;
    }
    else
    {
        textcolor(LIGHTRED);
        printf("Ticket not found!");
        getch();
        fclose(cp);
        //printf("return hone wala hai");
        return NULL;
    }
}

void view_canceled_bookings()
{
    FILE *fp;
    int i;
    char *c;
    Passenger can_pas;
    clrscr();
    fp=fopen(".\\cancel_records.dat","rb");
    if (fp==NULL)
    {
        textcolor(RED);
        printf("\n\nNO ticket is canceled till now!");
        getch();
        textcolor(YELLOW);
        return;
    }

    textcolor(YELLOW);
    for (i=0;i<80;i++) printf("-");
    printf("Ticket Number \tName\t Gender\t Age\tMobile Number \tTrain Number \tCoach \tFare \tAddress \n");
    for (i=0;i<80;i++) printf("-");
    while(fread(&can_pas,sizeof(Passenger),1,fp)==1)
    {

        i=strlen(can_pas.p_name);
        //temp=i;
        if (i<=10)
        {
            i=10-i;
            printf("\n       %d \t%s",can_pas.ticketno,can_pas.p_name);
            while (i)
            {
                printf(" ");
                i--;
            }
        }
        else
        {
            //jaha space hai uska address
            c=strchr(can_pas.p_name,' ');
            // uss address ko base address se minus krne me index number mil jyega uska
            c=c-can_pas.p_name;
            //agar first name 10 char se badha ho to
            if (c>10) c=10;
            //printf("C= %d\n",c);
            printf("\n       %d \t",can_pas.ticketno);
            for (i=0;i<c;i++)
            {
                printf("%c",can_pas.p_name[i]);
            }
            i=10-(int)c;
            while (i)
            {
                printf(" ");
                i--;
            }

        }

        printf("  %c\t %d \t %s\t    %s \t  %c \t%d \t%s",can_pas.gender,can_pas.age,can_pas.mob_no,can_pas.train_no,can_pas.p_class,can_pas.fare,can_pas.address);
    }

    fclose(fp);
    printf("\n\n\n\n");
    textcolor(WHITE);
    printf("Press any key to continue");
    textcolor(YELLOW);
    getch();
}

int cancel_train(char *tra)
{
    Passenger pas;
    Train tar;
    int flag=0;
    FILE *fp=fopen(".\\allbookings.dat","rb");
    if (fp==NULL)
        return 0;

    FILE *fp1=fopen(".\\tmp.dat","wb");
    if (fp1==NULL)
        return -1;

    FILE *fpt=fopen(".\\alltrains.dat","rb");
    if (fpt==NULL)
        return -1;

    FILE *fpt2=fopen(".\\tmp2.dat","wb");
    if (fpt2==NULL)
        return -1;

    FILE *fct=fopen(".\\can_train.dat","wb");
    if (fct==NULL)
        return -1;

    while(fread(&tar,sizeof(Train),1,fpt)==1)
    {
        if (strcmp(tar.train_no,tra)!=0)
        {
            fwrite(&tar,sizeof(Train),1,fpt2);
        }
        else fwrite(&tar,sizeof(Train),1,fct);
    }

    while(fread(&pas,sizeof(Passenger),1,fp)==1)
    {
        if (strcmp(pas.train_no,tra)!=0) fwrite(&pas,sizeof(Passenger),1,fp1);
        else
        {
            flag=1;
            cancel_record_w(pas);
        }
    }
    if (flag==1)
    {
        fclose(fp);
        fclose(fp1);
        fclose(fpt);
        fclose(fpt2);
        fclose(fct);
        if(remove(".\\allbookings.dat"))
        {
            printf("Unable to delete allbookings.dat");
            getch();
        }
        if(remove(".\\alltrains.dat"))
        {
            printf("Unable to delete allbookings.dat");
            getch();
        }
        rename(".\\tmp2.dat",".\\alltrains.dat");
        rename(".\\tmp.dat",".\\allbookings.dat");
        return 1;
    }
    else
    {
        fclose(fp);
        fclose(fp1);
        fclose(fpt);
        fclose(fpt2);
        fclose(fct);
        if(remove(".\\tmp.dat"))
        {
            printf("Unable to delete tmp.dat");
            getch();
        }
        if(remove(".\\alltrains.dat"))
        {
            printf("Unable to delete alltrains.dat");
            getch();
        }
        rename(".\\tmp2.dat",".\\alltrains.dat");

        return 0;
    }
}

char *accept_mob_number()
{
    static char mob[11];
    static char cond[]={'0','\0'};
    clrscr();
    textcolor(GREEN);
    gotoxy(105,1);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Mobile number: ");
    while(1)
    {
        fflush(stdin);
        textcolor(YELLOW);
        scanf("%s",mob);

        if (strcmp(mob,"0")==0)
        {
            gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("Searching Canceled");
            textcolor(YELLOW);
            getch();
            gotoxy(1,30);
            printf("\t\t\t\t");
            return cond;
        }

        else if (check_mob_no(mob)==0)
        {
            gotoxy(1,30);
        printf("\t\t\t\t\t\t");
        gotoxy(1,30);
        textcolor(RED);
        printf("Invalid mobile no!");
        getch();
        gotoxy(16,1);
        printf("\t\t\t\t\t\t\t");
        gotoxy(16,1);
        }
        else break;

    }
    return mob;
}

int search_n_print_records(int a,char *mob,int rec)
{
    FILE *fp;
    Passenger pas;
    int i;
    char *c;
    if (a!=1 && a!=2)
    {
        printf("Invalid Arguments!");
        getch();
        exit(0);
    }
    else if (a==1) fp=fopen(".\\allbookings.dat","rb");
    else if (a==2) fp=fopen(".\\cancel_records.dat","rb");
    fseek(fp,rec*sizeof(Passenger),SEEK_SET);
    if(fread(&pas,sizeof(Passenger),1,fp)!=1)
    {
        fclose(fp);
        return 1;
    }
    if (strcmp(pas.mob_no,mob)==0)
        {
            i=strlen(pas.p_name);
            if (i<=10)
        {
            i=10-i;
            printf("\n       %d \t%s",pas.ticketno,pas.p_name);
            while (i)
            {
                printf(" ");
                i--;
            }
        }
        else
        {
            //jaha space hai uska address
            c=strchr(pas.p_name,' ');
            // uss address ko base address se minus krne me index number mil jyega uska
            c=c-pas.p_name;
            //agar first name 10 char se badha ho to
            if (c>10) c=10;
            //printf("C= %d\n",c);
            printf("\n       %d \t",pas.ticketno);
            for (i=0;i<c;i++)
            {
                printf("%c",pas.p_name[i]);
            }
            i=10-(int)c;
            while (i)
            {
                printf(" ");
                i--;
            }

        }

        printf("  %c\t %d \t %s\t    %s \t  %c \t%d \t%s",pas.gender,pas.age,pas.mob_no,pas.train_no,pas.p_class,pas.fare,pas.address);
    }
    else
    {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;

}
void view_all_tickets(char *mob)
{
    FILE *fp;
    //Passenger pas;
    int flag=0;
    int i,temp=0;
    int count=0; //to store current row;
    if (strcmp(mob,"0")==0) return;
    fp=fopen(".\\allbookings.dat","rb");
    if (fp==NULL)
    {
        gotoxy(1,30);
        textcolor("LIGHTRED");
        printf("No booking has been made till now in the system!");
        getch();
        return;
    }
    fclose(fp);
    clrscr();
    textcolor(YELLOW);
    for (i=0;i<120;i++) printf("-");
    printf("Ticket Number \tName\t Gender\t Age\tMobile Number \tTrain Number \tCoach \tFare \tAddress \n");
    for (i=0;i<120;i++) printf("-");
    i=0;
    temp=0;
    while(1)
    {
        flag=search_n_print_records(1,mob,i);

        if(flag==1) break;
        if (flag==0) temp=1; //this means at least one record found having given mobile number
        i++;
    }

    //to add 3 row of - headings and -
    count=count+3;

    //extra
    count=count+1;
    i=0;
    if (temp==1)
    {
        textcolor(WHITE);
        gotoxy(1,30);
        printf("\t \t \t \t \t \t \t \t \t \t");
        gotoxy(1,30);
        printf("Do you want to search for canceled bookings (1 or 0): ");
        fflush(stdin);
        scanf("%d",&i);
        gotoxy(1,30);
        textcolor(WHITE);
        printf("\t \t \t \t \t \t \t \t \t \t");

        if (i==0)
        {
            return;
        }
        fp=fopen(".\\cancel_records.dat","rb");
        if (fp==NULL)
        {
            gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("\t \t \t \t \t \t \t \t \t \t");
            gotoxy(1,30);
            printf("No bookings has been canceled till now in the system!");
            getch();
            return;
        }
        fclose(fp);

        gotoxy(1,count+1);
        textcolor(LIGHTGREEN);
        printf("\n \n \n \n \t \t \t \t \t Canceled bookings\n");
        textcolor(YELLOW);
        i=0;
    temp=0;
    while(1)
    {
        flag=search_n_print_records(2,mob,i);

        if(flag==1) break;
        if (flag==0) temp=1; //this means at least one record found having given mobile number
        i++;
    }
    if (temp==0)
    {
        gotoxy(1,count+5);
        printf("\t \t \t \t \t \t \t \t \t \t \t \t \t");
        textcolor(LIGHTRED);
        gotoxy(1,30);
        printf("\t \t \t \t \t \t \t \t \t \t");
        gotoxy(1,30);
        printf("NO booking has been canceled having mobile number %s",mob);
        getch();
        return;
    }

    getch();
    return;
    }
    else if (temp==0)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("No Booking found having given mobile no");
        printf("\n\n\n\n");
        textcolor(WHITE);
        printf("Do you want to search for canceled bookings (1 or 0): ");
        fflush(stdin);
        scanf("%d",&i);
        if (i==0) return;
    }
    fp=fopen(".\\cancel_records.dat","rb");
    if (fp==NULL)
        {
            gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("\t \t \t \t \t \t \t \t \t \t");
            gotoxy(1,30);
            printf("No bookings has been canceled till now in the system!");
            getch();
            return;
        }
    fclose(fp);
    clrscr();
    printf("\t \t \t \t \t Canceled tickets for mobile no. %s\n",mob);
    textcolor(YELLOW);
    for (i=0;i<120;i++) printf("-");
    printf("Ticket Number \tName\t Gender\t Age\tMobile Number \tTrain Number \tCoach \tFare \tAddress \n");
    for (i=0;i<120;i++) printf("-");
    i=0;
    temp=0;
    while(1)
    {
        flag=search_n_print_records(2,mob,i);

        if(flag==1) break;
        if (flag==0) temp=1; //this means at least one record found having given mobile number
        i++;
    }
    if (temp==0)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("NO booking has been canceled having mobile number %s",mob);
        getch();
        return;
    }
    getch();
    return;
}

char *accept_train_no()
{
    static char trno[6];
    clrscr();
    textcolor(GREEN);
    gotoxy(105,1);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter Train number: ");

        while(1)
        {
            fflush(stdin);
            scanf("%s",trno);
            if (strcmp(trno,"0")==0)
            {
                gotoxy(1,30);
                textcolor(LIGHTRED);
                printf("Train canceling has been canceled");
                textcolor(YELLOW);
                getch();
                return NULL;
            }
            else if (!check_train_no(trno,'F'))
            {
                gotoxy(1,30);
                textcolor(LIGHTRED);
                printf("Train not found!");
                getch();
                textcolor(YELLOW);
                gotoxy(21,1);
                printf("\t\t\t\t\t\t\t");
                gotoxy(21,1);
                continue;
            }
            break;
        }
    return &trno;
}

