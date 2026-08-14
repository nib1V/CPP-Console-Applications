#include "Library.h"

enum Month {                                                                    //Enumeration used to represent the months of the year in normal order
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, octo, nov, dece
};

enum Dd {                                                                       //Enumeration used to represent the days of a week
    sun = 0, mon, tue, wen, thu, fri, sat
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
    void daytoday(int num);
private:
    int   y;
    Month m;
    int   d;
};

string day_select(int day_new)                                                  //Function that takes as input a day returning the string value of that day
{
    string Dy = " ";
    switch (day_new){

        case 0: Dy = "Sunday"; break;
        case 1: Dy = "Monday"; break;
        case 2: Dy = "Tuesday"; break;
        case 3: Dy = "Wednesday"; break;
        case 4: Dy = "Thursday"; break;
        case 5: Dy = "Friday"; break;
        case 6: Dy = "Saturday"; break;
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


void Date::daytoday(int num)                                                            //Function that prints the current date.
{
    string Mm = month_select(m);                                                 //Using the functions listed before we get the name of the day and the month
    string Dy = day_select(num);                                          //along with the ordinal suffixes
    string label = label_select(d);
    cout << "Today is " << Dy << " the " << d << label << "of " << Mm << " " << y << endl;
}

bool Date::leap_year()                                                           //Function that checks if a year is leap or not.
{
    if ((y%4 == 0 && (!(y/100 == 0))) || y%400 == 0)                             //Checking if the year is divisable by 4, 100 or 400 to see if its leap or not
    {
        return true;                                                             //If it is then return true
    }
    return false;                                                               //Otherwise return false
}

Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd)                      //The main constructor for the Date Class
{
    if (mm < 1 || mm > 12) error("Invalid Input");                              //Checking if the input is correct otherwise throwing an exception
    if (dd < 1) error("Invalid Input");
    if (mm == 2 && leap_year() && dd > 29) error("Invalid Input");
    if (mm == 2 && !leap_year() && dd > 28) error("Invalid Input");
}

int Doomsdate(Date d) //Date as input not these ints
{
    switch(d.month())
    {
        case jan:
            if (d.leap_year())
            {
                return 4;
            }
            else
            {
                return 3;
            }
        case feb:
            if (d.leap_year())
            {
                return 29;
            }
            else
            {
                return 28;
            }
        case mar: return 7;
        case apr: return 4;
        case may: return 9;
        case jun: return 6;
        case jul: return 11;
        case aug: return 8;
        case sep: return 5;
        case octo: return 10;
        case nov: return 7;
        case dece: return 12; 
    }
    return 0;
}

int AnchorDay(int year)
{
    int tmp1 = year / 100;
    double tmp2 = double(tmp1) * 100;
    tmp2 /= 400;
    if ( remainder(tmp2, 1.0) == 0.25 || remainder(tmp2, 1.0) == -0.75) return sun; //IEEE 754 standard
    if ( remainder(tmp2, 1.0) == 0) return tue;
    if ( remainder(tmp2, 1.0) == 0.75 || remainder(tmp2, 1.0) == -0.25) return wen; //IEEE 754 standard
    if ( remainder(tmp2, 1.0) == 0.50 || remainder(tmp2, 1.0) == -0.5) return fri;  //IEEE 754 standard
    return -1;
}

int DoomsdayCalc(int year)
{
    //Step 1.
    int digs = year % 100;
    int whole = digs / 12;

    //Step 2.
    int prod = whole * 12;
    prod = digs - prod;

    //Step 3.
    int tim = prod / 4;

    //Step 4.
    int anchor = AnchorDay(year);

    //Step 5.
    int res = whole + prod + tim + anchor;

    //Step 6.
    int times = res / 7;
    res = res - 7 * times;

    return res;
}

void DateCalc(Date d)
{
    int doomsday = DoomsdayCalc(d.year());
    int date = Doomsdate(d);
    int dis = abs(d.day() - date);
    dis = dis / 7;
    date += 7 * dis;
    if (d.day() > date )
    {
        int diff = d.day() - date;
        if (doomsday + diff > 6)
        {
            int tmp = doomsday + diff - 6;
            doomsday = tmp - 1;
            d.daytoday(doomsday);
            return;
        }
        doomsday += diff;
        d.daytoday(doomsday);
        return;
    }
    else 
    {
        int diff = date - d.day();
        if (doomsday - diff < 0)
        {
            int tmp = doomsday - diff;
            doomsday = 7 + tmp;
            d.daytoday(doomsday);
            return;
        }
        doomsday -= diff;
        d.daytoday(doomsday);
        return;
    }
}

int main()
{
    Date d(2026, nov, 19);          //GTA 6 Release date as an example!
    DateCalc(d);
}