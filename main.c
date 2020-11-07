#include <stdio.h>
#include <stdlib.h>
#include "rlyres.h"
#include "conio2.h"
#include <windows.h>


int main()
{
    add_trains();
    int temp;
    Passenger *ptr;
    char ch='y';
    char arr[7];
    SetConsoleTitle((LPSTR)"Railway Reservation system");
    while (ch=='y')
    {
    switch(enterchoice())
    {
    case 1:
        view_trains();
        textcolor(WHITE);
        printf("Press any key to continue");
        getch();
        clrscr();
        break;
    case 2:
        clrscr();
        ptr=get_passenger_details();
        if (ptr==NULL) break;
        temp=book_ticket(*ptr);
        if (temp<0)
        {
            textcolor(RED);
            printf("\n\nBooking Failed");
            textcolor(YELLOW);
            getch();
            break;
        }
        else
        {
            textcolor(LIGHTGREEN);
            printf("\n\nYou ticket is successfully booked\nyour ticket is %d",temp);
            textcolor(WHITE);
            printf("\n\n\n\n\n");
            printf("Press any key to continue");
            getch();
        }
        textcolor(WHITE);
        //printf("\n\n\nDo you want to book more ticket (y or n): ");
        //fflush(stdin);
        //scanf("%c",&ch);
        break;
    case 3:
        view_ticket(accept_ticket_number());
        break;
    case 4:
        view_all_tickets(accept_mob_number());
        break;
    case 5:
        clrscr();
        view_all_bookings();
        break;
    case 6:
        view_bookings(accept_train_no());
        break;
    case 7:
        switch(cancel_ticket(accept_ticket_number()))
        {
        case 1:
            textcolor(GREEN);
            printf("Ticket has been canceled Successfully!");
            getch();
            textcolor(YELLOW);
            break;
        case -1:
            textcolor(RED);
            printf("Unable to crete tmp file!");
            getch();
            textcolor(YELLOW);
            break;
        case 0:
            textcolor(LIGHTRED);
            printf("Ticket not found!");
            getch();
            textcolor(YELLOW);
            break;
        case -2:
            break;
        }
        break;
    case 8:
        temp=0;
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
            scanf("%s",arr);

            if (strcmp(arr,"0")==0)
            {
                gotoxy(1,30);
                textcolor(LIGHTRED);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,30);
                printf("Canceling process has been canceled!");
                textcolor(YELLOW);
                getch();
                temp=1;
                break;
            }

            else if (!check_train_no(arr,'F'))
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
        if (temp==0) {
        switch(cancel_train(arr))
        {
        case 1:
            textcolor(GREEN);
            printf("Train has been canceled Successfully!");
            getch();
            textcolor(YELLOW);
            break;
        case -1:
            textcolor(RED);
            printf("Unable to create  files!");
            getch();
            textcolor(YELLOW);
            break;
        case 0:
            textcolor(LIGHTRED);
            printf("No bookings have been made for that train");
            getch();
            textcolor(YELLOW);
            break;
        }}
        break;
    case 9:
        view_canceled_bookings();
        break;
    case 10:
        exit(0);
        ch='n';
        break;
    }
    }
    return 0;
}
