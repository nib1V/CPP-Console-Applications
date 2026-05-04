#include "Library.h"

enum Month {                                                                    //Enumeration used to represent the months of the year in normal order
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, octo, nov, dece
};

enum Dd {                                                                       //Enumeration used to represent the days of a week
    sun = 1, mon, tue, wen, thu, fri, sat = 0
};

class Date {                                                                    //Class used to hold the data of a Date along with
public:                                                                         //a couple of functions to help with the functionality.
    Date(int yy, Month mm, int dd);                                             //There are two constructors on of which doesnt take anything as input.
    Date(){};

    int   day()   {return d;}                                                   //Functions that are used so that the user can get the values of the private members
    Month month() {return m;}                                                   //those here being the year, month and day.
    int   year()  {return y;}                                                   //The function day_name is different to the other ones since its used
    Dd    day_name();                                                           //to get the exact day of the week.

    void operator=(Date& d1);                                                   //Overloading the '=' operator in order to copy the values of one class to another.

    bool leap_year();
    int  month_code(int month);
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
    void daytoday();
    void next_workday();
    void week_of_year();
    bool has_30d();
    bool has_31d();
private:
    int   y;
    Month m;
    int   d;
};

void interface(Date&);                                                          //Declaring the interface function so that we can call it from the input

bool Date::has_30d()                                                            //Function that returns a boolean value on whether or not the month has 30 days
{
    if (m == apr || m == jun || m == sep || m == nov)
    {
        return true;                                                            //Returning true if the month has 30 days
    }
    return false;                                                               //Otherwise return false
}

bool Date::has_31d()                                                            //Function that returns a boolean value on whether or not the month has 31 days
{
    if (m == jan || m == mar || m == may || m == jul || m == aug || m == octo || m == dece)
    {
        return true;                                                            //Returning true if the month has 31 days
    }
    return false;                                                               //Otherwise return false
}

bool Date::leap_year()                                                           //Function that checks if a year is leap or not.
{
    if ((y/4 == 0 && (!(y/100 == 0))) || y/400 == 0)                             //Checking if the year is divisable by 4, 100 or 400 to see if its leap or not
    {
        return true;                                                             //If it is then return true
    }
    return false;                                                               //Otherwise return false
}

Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd)                      //The main constructor for the Date Class
{
    if (mm < 1 || mm > 12) error("Invalid Input");                              //Checking if the input is correct otherwise throwing an exception
    if (dd < 1) error("Invalid Input");
    if (dd > 30 && has_30d()) error("Invalid Input");
    if (dd > 31 && has_31d()) error("Invalid Input");
    if (mm == 2 && leap_year() && dd > 29) error("Invalid Input");
    if (mm == 2 && !leap_year() && dd > 28) error("Invalid Input");
    if (yy < 1600 || yy > 2299) error("Invalid Input");
}

int year_code(int year)                                                         //Function that returns an integer based on the year algorithm used
{
    if (year > 2000) return year - 2000;
    if (year > 1900) return year - 1900;
    if (year > 1800) return year - 1800;
    if (year > 1700) return year - 1700;
    if (year > 1600) return year - 1600;
    return -1;                                                                  //If the year is not compatible with the algorithm give a wrong value here (-1)
}

int Date::month_code(int month)                                                 //Function that returns an integer according to the month algorithm
{
    if (month == 1 && !leap_year()) return 1;
    if (month == 1 && leap_year()) return 4;
    if (month == 2 && !leap_year()) return 4;
    if (month == 2 && leap_year()) return 0;
    if (month == 3) return 4;
    if (month == 4) return 0;
    if (month == 5) return 2;
    if (month == 6) return 5;
    if (month == 7) return 0;
    if (month == 8) return 3;
    if (month == 9) return 6;
    if (month == 10) return 1;
    if (month == 11) return 4;
    if (month == 12) return 6;
    return -1;                                                                  //If the month is not compatible with the algorithm give a wrong value here (-1)
}

int cent_code(int year)                                                         //Function that returns an integer according to the century algorithm
{
    if (year < 1800) return 4;
    if (year < 1900) return 2;
    if (year < 2000) return 0;
    if (year < 2100) return 6;
    if (year < 2200) return 4;
    return -1;                                                                 //If the century is not compatible with the algorithm give a wrong value here (-1)
}

string day_select(int day_new)                                                  //Function that takes as input a day returning the string value of that day
{
    string Dy = " ";
    switch (day_new){
        case 0: Dy = "Saturday"; break;
        case 1: Dy = "Sunday"; break;
        case 2: Dy = "Monday"; break;
        case 3: Dy = "Tuesday"; break;
        case 4: Dy = "Wednesday"; break;
        case 5: Dy = "Thursday"; break;
        case 6: Dy = "Friday"; break;
    }
    return Dy;
}

string month_select(int month_new)                                             //Function that takes as input a month returning the string value of that month
{
    string Mm = " ";
    switch (month_new) {
    case 1: Mm = "January"; break;
    case 2: Mm = "February"; break;
    case 3: Mm = "March"; break;
    case 4: Mm = "April"; break;
    case 5: Mm = "May"; break;
    case 6: Mm = "June"; break;
    case 7: Mm = "July"; break;
    case 8: Mm = "August"; break;
    case 9: Mm = "September"; break;
    case 10: Mm = "Octomber"; break;
    case 11: Mm = "November"; break;
    case 12: Mm = "December"; break;
    }
    return Mm; 
}

string label_select(int day)                                                   //Function that is used to make the ordinal suffixes for the days of the month
{
    string label = " ";
    switch (day)
    {
        case 1: label = "st "; break;
        case 2: label = "nd "; break;
        case 3: label = "rd "; break;
        default: label = "th "; break;
    }
    return label;
}

Dd Date::day_name()                                                            //Using all the parts from the above algorithm we generate a number 0 - 6
{                                                                              //that is used to indicate the name of the day according to the enumeration above
    int Yy = year_code(y);
    int Mm = month_code(m);
    int Cc = cent_code(y);
    if (Yy == -1 || Mm == -1 || Cc == -1) error("Something went wrong!");      //Checking if the ouput if wrong and throwing an error if so
    int sum = Yy/4 + Yy + Mm + Cc + d;                                         //If the input is correct them the algorithm continues to find the day
    sum %= 7;
    return Dd(sum);
}

Month operator+(Month& mon, int n)                                             //Overloading the '+' operator so that i can do month calculations
{
    int temp = mon;                                                            //Giving temp the value of the month then adding n to it
    temp = temp + n;
    if(temp > 12)                                                              //If the reult is greater than 12 then we have to perform a wrap-around
    {                                                                          //subtracting 12 to find the real month
        temp -= 12;
        return Month(temp);
    }
    return Month(temp);
}

void Date::operator=(Date& date)
{
    d = date.day();                                                            //Basicly giving the private members of the class the values of the other class
    m = date.month();
    y = date.year();
}

istream& operator>>(istream& ist, Date& date)                                      //Overloading the '>>' operator in order to have custom inputs
{
    char symb1, symb2;                                                         //The symbols here are going to be used to seperate the year month and day
    int y, temp, d;
    ist >> y >> symb1 >> temp >> symb2 >> d;
    if (symb1 != '/' || symb2 != '/') error("Wrong input layout, try again...");    //If the input is not given in the exact way yy/mm/dd then i throw an exception
    Month m = Month(temp);                                                          //Making the int into a Month enumeration
    Date dtemp(y, m, d);                                                       //Initializing a "dummy" object in order to copy its contents to date
    date = dtemp;
    return ist;
}

void Date::daytoday()                                                            //Function that prints the current date.
{
    string Mm = month_select(m);                                                 //Using the functions listed before we get the name of the day and the month
    string Dy = day_select(day_name());                                          //along with the ordinal suffixes
    string label = label_select(d);
    cout << "Today is " << Dy << " the " << d << label << "of " << Mm << " " << y << endl;
}

void Date::add_day(int n)                                                        //Function that adds n days to the current date.
{
    if (n < 0) error("Can't subtract days");                                     //Checking for wrong input and throwing an exception if so
    if (has_30d())                                                               //Checking if the month has 30 days in order to make the correct calculations
    {
        int temp = 0;                                                            //Temp here is a "dummy" variable thats going to be used to store an integer
        if (n > 31) error("Too big of a number of days to add!");                //Indicating whether or not to add a month. Also here we can't add more than 31 days
        temp = (d + n)/30;
        switch ((d + n)%30)                                                      //if (d + n) modulo 30 == 0 means that we are on the 30th day of the month
        {                                                                        //So we want d to have the value 30 not 0 that is given by (d + n)%30
        case 0: d = d + n; break;                                                //But on every other case it is acceptable since it gives the month itself
        default: d = (d + n)%30; break;                                          //Although i could have done the same thing as long as i said modulo 31 so that in a 30 day
        }                                                                        //month i cant get 0 and at the same time i would have the same results
        add_month(temp);
    }
    else if (has_31d())                                                          //Doing the same as above only difference being that here we have 31 days
    {
        int temp = 0;
        if (n > 30) error("Too big of a number of days to add!");
        temp = (d + n)/31;
        switch ((d + n)%31)
        {
        case 0: d = d + n; break;
        default: d = (d + n)%31; break;
        }
        add_month(temp);
    }
    else                                                                        //Doing the same as above only difference being that here we have 28 or 29 days
    {
        int temp = 0;
        if (n > 31) error("Too big of a number of days to add!");               //Checking for incorrect values
        if (!leap_year())                                                       //Checking for leap years because february has 28 or 29 days according to the year
        {
            temp = (d + n)/28;                                                  //If it isn't a leap year treat it the same as above but for 28 days
            switch ((d + n)%28)
            {
                case 0: d = d + n; break;
                default: d = (d + n)%28; break;
            }
            add_month(temp);
        }
        else
        {
            temp = (d + n)/29;                                                  //If it is a leap year treat it the same as above but for 29 days
            switch ((d + n)%29)
            {
                case 0: d = d + n; break;
                default: d = (d + n)%29; break;
            }
            add_month(temp);
        }  
    }
}

void Date::add_month(int n)                                                      //Function that adds n months to the current date.
{
    int temp1 = m;
    m = m + n;                                                                  //Adding months using the overloaded operator '+'
    int temp2 = m;
    if(temp1 > temp2)                                                           //If the month before the addition is bigger than after that means we did a wrap around
    {                                                                           //so we have to add a year
        add_year(1);
    }
}

void Date::add_year(int n)                                                       //Function that adds n years to the current date.
{
    if (n < 0) error("Cannot subtract years!");                                  //Checking if n is correct
    y = y + n;
}

void Date::next_workday()                                                        //Function that prints the date of the next workday.
{
    Dd day_new = day_name();                                                     //day_new is initialized with a value from 0 to 6 but is an enumeration type: Dd (not an int!)
    Month month_new = m;                                                         //same thing goes for month_new and year_new
    int year_new = y;
    string Dy = " ";                                                             //Initializing the string that is going to hold the name of the day to print later
    int offset = 0;                                                              //The number of days we will have to add in order to reach the next workday
    if(day_name() == 0 || day_name() == 1 || day_name() == 6)                    //Checking the "easy" cases where the next workday is always monday
    {
        Dy = "Monday";
        if (day_name() == 0) offset = 2;                                         //According to the day we give a suitable offset
        if (day_name() == 1) offset = 1;
        if (day_name() == 6) offset = 3;
    }
    else                                                                         //Checking all other days
    {
        offset = 1;                                                              //All other days are going to have their next workday be the next day so offset is set to 1
        int temp = day_name();                                                   //Giving a "dummy" variable the integer value of the current day
        if(d + 1 > 30 && has_30d())                                              //Checking if the +1 goes over to the next month for 30 day months
        {                                                                        //If so then we can go to the next day 
            temp++;
            day_new = Dd(temp);
            month_new = m + 1;                                                   //and add a month while on the same year
        }
        else if (d + 1 > 31 && has_31d())                                        //Checking if the +1 goes over to the next month for 31 day months
        {                                                                        //If so then we can go to the next day
            temp++;
            day_new = Dd(temp);
            month_new = m + 1;                                                   //and add a month but now we have to check the case that the month is december
            if (m == dece) year_new++;                                           //In the case that it is then we increment the year otherwise it stays the same
        }
        else if ((d + 1) == 28 && !leap_year() || (d + 1) == 29 && leap_year())  //Checking if the +1 goes over to the next month for 28 or 29 day months
        {                                                                        //According to if the year is a leap year or not
            temp++;
            day_new = Dd(temp);
            month_new = m + 1;                                                   //and add a month while on the same year
        }
        else                                                                     //In the default case we can just increment the days whithout worrying about the year or month
        {
            temp++;
            day_new = Dd(temp);
        }
        if (day_new == 1 || day_new == 0) error("Something went wrong...");      //Checking if the next workday is sunday or saturday which would of course be wrong
        Dy = day_select(day_new);                                                //Getting Dy the correct string value
    }
    Date temp(y, m, d);                                                          //Creating a "dummy" object with the old values so that we dont ruin the values of our object
    temp.add_day(offset);                                                        //Adding the offset to the "dummy" object which acts like a psuedo change to the main object
    string Mm = month_select(month_new);                                         //Getting Mm the correct string value
    string label = " ";
    label = label_select(temp.day());                                            //Getting the label the correct string value
    if ((d + offset < 31 && has_30d()) || (d + offset < 32 && has_31d()))        //If adding the offset doesn't cause any issues thenyou can print the date using d + offset 
    {
        cout << "The next workday is: " << Dy
         << " the " << d + offset << label << "of " << Mm 
         << " " << year_new <<  endl;
    }
    else                                                                         //Otherwise we have to use the value of the "dummy" object which by itself
    {                                                                            //has already calculated the wrap-around if it was needed
        cout << "The next workday is: " << Dy
         << " the " << temp.day() << label << "of " << Mm 
         << " " << year_new <<  endl;
    }
}

void Date::week_of_year()                                                        //Function that uses an algorithm to find the week of the year
{
    int n = d/7 + (m - 1)*4;                                                     //To find the week of the year, i use an algorithm that gets n by using a combination of
    int sum = 0;                                                                 //the months and days of the current date to generate the number of weeks but
    if (d%7 != 0) sum += d%7;                                                    //not all day values are accounted so i get the remainder via modulo
    for(int i = m; i; i--)                                                       //and then for every month i check whether it has 30 or 31 days because 7 * 4 = 28
    {                                                                            //so we lose 2 days in a 30 day month and 3 days in a 31 day month
        if (i == 4 || i == 6 || i == 9 || i == 11)
        {
            sum += 2;
        }
        else if(i != 2)
        {
            sum += 3;
        }
    }                                                                            //After calculating the number of lost days i divide them by 7 in order to get
    n = n + sum/7 + 1;                                                           //the ammount of lost weeks and then i add them to n plus one week always because
    cout << "It is week " << n << " of the year!" << endl;                       //of the way i count them
}

void input()                                                                     //Function that is used to simplify the proccess of getting data
{
    cout << "Input the date you want below" << endl
         << "(The correct format is yy/mm/dd): ";
    Date date;                                                                               //Creating an empty shell (at least until some input is given)
    cin >> date;                                                                             //Inputting the date via the overloaded operator created above
    if (cin.fail() || cin.bad()) error("Something went wrong while inputting the date...");  //If the input stream for some reason stops working (bad input or computer problem)
    interface(date);                                                                         //i throw an error otherwise i call the interface
}

void interface(Date& date)                                                      //Function that lets the user choose what they want to do
{
    while(1)                                                                    //Always repeats until an error or bad input
    {
        int sel = 0;
        cout << "Select what you want to do with your date:" << endl
            << "1. Print the current Date" << endl
            << "2. Print the week of the year" << endl
            << "3. Print the Date of the next workday" << endl
            << "4. Enter new date" << endl
            << "5. Add n days to your current date" << endl
            << "6. Add n months to your current date" << endl
            << "7. Add n years to your current date" << endl
            << "8. Exit" << endl
            << "Enter an interger followed by ENTER: ";
        cin >> sel;
        cout << endl;
        if (sel == 1) 
        {
            date.daytoday();
            cout << endl;
        }
        else if (sel == 2)
        {
            date.week_of_year();
            cout << endl;
        }
        else if (sel == 3)
        {
            date.next_workday();
            cout << endl;

        } 
        else if (sel == 4)
        {
            input();
        }
        else if (sel == 5)
        {
            int n = 0;
            cout << endl << "Enter the ammount of days you want to add" << endl
                 << "(It has to be a number between 1 and 31 according to the month): ";
            cin >> n;
            date.add_day(n);
            cout << endl;
        }
        else if (sel == 6)
        {
            int n = 0;
            cout << endl << "Enter the ammount of months you want to add: ";
            cin >> n;
            cout << endl;
            date.add_month(n);
            cout << endl;
        }
        else if (sel == 7)
        {
            int n = 0;
            cout << endl << "Enter the ammount of years you want to add: ";
            cin >> n;
            cout << endl;
            date.add_year(n);
            cout << endl;
        }
        else if (sel == 8)
        {
            exit(0);
        }
        else
        {
            error("Unexpected input, try again...");
        }
    }
}

int main()
{
    try                                                                           //Here i have a try catch block in order to get all the exceptions thrown from above 
    {
        input();                                                                  //The input here is minimal due to the use of the input function
    }
    catch(exception& e)                                                           //Catching the exception and then printing out the message attatched to it
    {
        cerr << e.what() << endl;
    }
    catch(...)                                                                    //In every other case we print a general error message
    {
        cerr << "Something went wrong and the app had to be shut down.." << endl;
    }
}