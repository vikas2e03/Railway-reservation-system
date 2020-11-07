#ifndef RLYRES_H_INCLUDED
#define RLYRES_H_INCLUDED

struct Train
{
    char train_no[10];
    char from[10];
    char to[10];
    int fac_fare;
    int sac_fare;
};

struct fare
{
    int sec_fare;
    int fir_fare;
};

struct Passenger
{
    char p_name[30];
    char gender;
    char train_no[10];
    char p_class;
    char address[30];
    int age;
    int ticketno;
    char mob_no[11];
    int fare;
};



typedef struct Train Train;
typedef struct Passenger Passenger;
typedef struct fare fare;

int enterchoice();
void add_trains();
void view_trains();
int *get_ticket_no(char *);
void view_ticket(int);
void view_all_bookings();
void view_bookings(char *);
int cancel_ticket(int);
int cancel_train(char *);

Passenger *get_passenger_details();
int check_train_no(char *,char);
int check_mob_no(char *);
int get_booked_ticket_count(char *,char);
int last_ticket_no();
int book_ticket(Passenger);
int accept_ticket_number();

char *accept_mob_number();
int *get_ticket_no(char *); //didn't used it
//void view_all_tickets(char*,int*); //didn't used it

//my functions
void color_label(char *,int); //to color labels like name age etc
void cancel_record_w(Passenger); //to write cancel records
Passenger *cancel_record_r(int); // to read cancel records
void view_canceled_bookings();
char *accept_train_no();
void view_all_tickets(char *);
int search_n_print_records(int ,char *,int); /* first argument: 1 for booking records 2 for cancel records
second argument: mobile number
third argument: record number
returns 1 when no records found for given record number, 0 when a record found having given mobile number
else return -1
    */



#endif // RLYRES_H_INCLUDED
