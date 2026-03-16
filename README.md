# CPP-Console-Applications
## Some small fun console applications in C++

The main purpose of this repository is to help myself and anyone<br/>
out there understand c++ a little bit more.<br/>

### Programs

1. **RatNum.cpp**<br/>
Takes as input two integers for each of the two rationals that the computation in going to be done to.<br/>
The available computations are:
- Addition
- Subtraction
- Multiplication
- Division
- Check to see if they are the same rational
<br/>
Along with these computations there are a couple of helper functions to use the result of the computation.<br/>
The Helper Functions go as follows:
- Print Result (As Rational)
- Print Rational as Double
  - Prints one of the two rationals or the result as a double
- Input new numbers
- Exit
- Save operation result
  - Saves result in a vector for future use (in a later version).

2. **Date.cpp**<br/>
Takes as input from the code (since i have no interface yet) a date inputted by the user.<br/>
Then using that date you can apply one of the many function that i have created as follows:
- add_day()
- add_month()
- add_year()
- next_workday()
- week_of_year()
<br/>
Also there is a set of helper function to help calculate the above results.<br/>
These go as follows:
- has_30d()
- has_31d()
- leap_year()
- day_name()
<br/>
There are also the functions:
- year_code()
- month_code()
- cent_code()
<br/>
These are used more for the computation of day_name() and are based on a day name algorithm.<br/>
The description of each function is going to be added later on..(In a later version).

