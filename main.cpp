/*
 * Daniel Winkler
 * daniel.winkler3@gmail.com
 * Lab 5 - Payroll
 */

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void input(string&, double&, double&, double&, char&, double&);
void output(string, double, double, double, double, double);
void calculations(double, double, double&, double&, double&, double, char, double&, double&);
void calcTaxes(double, double, double&, double&, double, char);
void signature();

int main() {
    // Declaring variables.
    string name;
    double wage;
    double hours;
    double allowances;
    char status;
    double yearToDateEarnings;
    double fica;
    double federalTax;
    double amountOfCheck;
    double currentEarnings;

    //Calling the input function with references to the input variables.
    input(name, wage, hours, allowances, status, yearToDateEarnings);

    //Converting the martial status into upper case so it won't be case sensitive.
    toupper(status);

    //Calling the calculation function and passing all of the variables.
    //Variables that need to be updates are passed as references.
    calculations(wage, hours, yearToDateEarnings, fica, federalTax, allowances, status, amountOfCheck, currentEarnings);

    //Calling the output function and passing the necessary variables.
    output(name, currentEarnings, yearToDateEarnings, fica, federalTax, amountOfCheck);

    //My signature.
    signature();
    return 0;
}

/*
 * Pre - Reference to all of the following variables:
 *       name: Name of the Employee.
 *       wage: Hourly wage.
 *       hours: Hours worked.
 *       allowances: Number of withholding allowances.
 *       status: Martial status.
 *       yearToDateEarnings: Year to date earnings.
 *
 * Post - Returning nothing.
 *        Passing values into these variables.
 *
 * Purpose - Store the inputs in local variables of the main function.
 */
void input(string& name, double& wage, double& hours, double& allowances, char& status, double& yearToDateEarnings){
    //Asking the user for the information.
    //Passing the information into the local variables of the main function with references.
    cout << "Enter the employee's name: " << endl;
    getline(cin, name);
    cout << "Enter the hourly wage: " << endl;
    cin >> wage;
    cout << "Enter the hours worked: " << endl;
    cin >> hours;
    cout << "Enter the amount of withholding allowances: " << endl;
    cin >> allowances;
    cout << "Enter the martial status (M for marries / S for single):" << endl;
    cin >> status;
    cout << "Enter the year to date earnings:" << endl;
    cin >> yearToDateEarnings;
}

/*
 * Pre - wage: Hourly wage.
 *       hours: Hours worked.
 *       Reference to yearToDateEarnings: Year to date earnings.
 *       Reference to fica: FICA tax.
 *       Reference to federalTax: income tax.
 *       allowances: Number of withholding allowances.
 *       status: Martial status.
 *       Reference to amountOfCheck: Income after taxes.
 *       Reference to currentEarnings: Gross income (hours times wage).
 *
 * Post - Returning nothing.
 *        Updating the following variables -
 *        yearToDateEarnings: Adding the current wage.
 *        currentEarnings: Wage times Hours worked, after 40 hours, wage is 1.5 bigger.
 *        fica: passing fica reference to calcTaxes function.
 *        federalTax: passing federalTax reference to calTaxes function.
 *        amountOfCheck: currentEarnings minus the fica (FICA tax) and the federalTax (income tax).
 *
 * Purpose - Calculate the currentEarnings, yearToDateEarnings, call the calcTaxes function, and calculate the amountOfCheck.
 */
void calculations(double wage, double hours, double& yearToDateEarnings, double& fica, double& federalTax, double allowances, char status, double& amountOfCheck, double& currentEarnings){
    //Calculating earnings, over 40 hours is 1.5 times wage.
    if (hours > 40){
        currentEarnings = (wage * 40) + ((hours - 40) * (wage * 1.5));

    } else {
        currentEarnings = wage * hours;
    }

    //Adding current earnings to year-to-date earnings.
    yearToDateEarnings += currentEarnings;

    //Calling the CalcTaxes function to calculate the FICA tax and the federal income tax.
    calcTaxes(currentEarnings, yearToDateEarnings, fica, federalTax, allowances, status);

    //Rounding fica and federalTax to 2 decimal places.
    fica = round(fica * 100);
    fica = fica / 100;
    federalTax = round(federalTax * 100);
    federalTax = federalTax / 100;

    //Calculating the salary after taxes.
    amountOfCheck = currentEarnings - fica - federalTax;
}


/*
 * Pre - currentEarnings: Gross income (hours times wage).
 *       yearToDateEarnings: Year to date earnings.
 *       Reference to fica: FICA tax.
 *       Reference to federalTax: Federal income tax.
 *       allowances: Number of withholding allowances.
 *       status: Martial status.
 *
 * Post - Returning nothing.
 *        Passing values into -
 *        fica: Calculating fica tax.
 *        federalTax: Calculating the federalTax.
 *
 */
void calcTaxes(double currentEarnings, double yearToDateEarnings, double& fica, double& federalTax, double allowances, char status){
    //Calculating FICA tax.
    if(yearToDateEarnings < 132900){
        fica = currentEarnings * 0.062;
    } else {
        fica = 0.0;
    }

    //Declaring a local variable for wage and calculating wage.
    double wages;
    wages = (currentEarnings - allowances * 80.60);

    //Calculating federal income tax. (S for Single, M for Married)
    if(status == 'S') {
        if (wages <= 73) {
            federalTax = 0.0;
        } else if (wages > 73 && wages <= 260) {
            federalTax = (wages - 73) * .1;
        } else if (wages > 260 && wages <= 832) {
            federalTax = 18.7 + (wages - 260) * .12;
        } else if (wages > 832 && wages <= 1692) {
            federalTax = 87.34 + (wages - 832) * .22;
        } else if (wages > 1692 && wages <= 3164) {
            federalTax = 276.54 + (wages - 1692) * .24;
        } else if (wages > 3164 && wages <= 3998) {
            federalTax = 629.82 + (wages - 3164) * .32;
        } else if (wages > 3998 && wages <= 9887) {
            federalTax = 896.7 + (wages - 3998) * .35;
        } else if (wages > 9887) {
            federalTax = 2957.85 + (wages - 9887) * .37;
        }
    } else if (status == 'M'){
        if(wages <= 227){
            federalTax = 0.0;
        } else if (wages > 227 && wages <= 600){
            federalTax = (wages - 227) * .1;
        } else if (wages > 600 && wages <= 1745){
            federalTax =  37.3 + (wages - 600) * .12;
        } else if (wages > 1745 && wages <= 3465){
            federalTax = 174.7 + (wages - 1745) * .22;
        } else if (wages > 3465 && wages <= 6409){
            federalTax = 553.1 + (wages - 3465) * .24;
        } else if (wages > 6409 && wages <= 8077){
            federalTax = 1259.66 + (wages - 6409) * .32;
        } else if(wages > 8077 && wages <= 12003){
            federalTax = 1793.42 + (wages - 8077) * .35;
        } else if (wages > 12003){
            federalTax = 3167.52 + (wages - 12003) * .37;
        }
    }
}

/*
 * Pre - name: Employee's name.
 *       currentEarnings: Gross income (hours times wage).
 *       yearToDate: Year-to-date earnings.
 *       fica: FICA tax.
 *       federalTax: Federal income tax.
 *       amountOfCheck: Income after taxes.
 *
 * Post - Returning nothing.
 *        Printing out the information.
 *
 * Purpose - Print out the information.
 */

void output(string name, double currentEarnings, double yearToDate, double fica, double federalTax, double amountOfCheck){
    //Formatting and printing to the console.
    cout << setprecision(2) << fixed << endl;
    cout << left << name << endl;
    cout << left << setw(20) << "Current Earnings" << right << setw(10) << currentEarnings << endl;
    cout << left << setw(20) << "Year-to-date" << right << setw(10) << yearToDate << endl;
    cout << left << setw(20) << "FICA tax" << right << setw(10) << fica << endl;
    cout << left << setw(20) << "Income Tax Withheld" << right << setw(10) << federalTax << endl;
    cout << left << setw(20) << "Amount of check" << right << setw(10) << amountOfCheck << endl;
}

//My signature
void signature(){
    cout << endl << "Daniel Winkler" << endl;
    cout << "daniel.winkler3@gmail.com" << endl;
    cout << "Lab 5 - Payroll" << endl;
}

/*
    /Users/DanielWinkler/CLionProjects/Lab5/cmake-build-debug/Lab5
    Enter the employee's name:
    Al Clark
    Enter the hourly wage:
    48.5
    Enter the hours worked:
    38
    Enter the amount of withholding allowances:
    2
    Enter the martial status (M for marries / S for single):
    M
    Enter the year to date earnings:
    88600

    Al Clark
    Current Earnings       1843.00
    Year-to-date          90443.00
    FICA tax                114.27
    Income Tax Withheld     167.12
    Amount of check        1561.61

    Daniel Winkler
    daniel.winkler3@gmail.com
    Lab 5 - Payroll

    Process finished with exit code 0
 */

/*
    /Users/DanielWinkler/CLionProjects/Lab5/cmake-build-debug/Lab5
    Enter the employee's name:
    Keren Chen
    Enter the hourly wage:
    44
    Enter the hours worked:
    35
    Enter the amount of withholding allowances:
    3
    Enter the martial status (M for marries / S for single):
    M
    Enter the year to date earnings:
    68200

    Keren Chen
    Current Earnings       1540.00
    Year-to-date          69740.00
    FICA tax                 95.48
    Income Tax Withheld     121.08
    Amount of check        1323.44

    Daniel Winkler
    daniel.winkler3@gmail.com
    Lab 5 - Payroll

    Process finished with exit code 0
 */

/*
    /Users/DanielWinkler/CLionProjects/Lab5/cmake-build-debug/Lab5
    Enter the employee's name:
    Nathan Chan
    Enter the hourly wage:
    25.5
    Enter the hours worked:
    50
    Enter the amount of withholding allowances:
    1
    Enter the martial status (M for marries / S for single):
    S
    Enter the year to date earnings:
    36295.5

    Nathan Chan
    Current Earnings       1402.50
    Year-to-date          37698.00
    FICA tax                 86.96
    Income Tax Withheld     195.12
    Amount of check        1120.42

    Daniel Winkler
    daniel.winkler3@gmail.com
    Lab 5 - Payroll

    Process finished with exit code 0

 */