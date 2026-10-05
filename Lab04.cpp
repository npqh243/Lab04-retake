/****************
20237341
Nghiem Phu Quang Hung
****************/


#include<iostream>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;

class Employee {
    
    protected:
    
    string employeeId;
    string fullName;
    string department;
    double monthlyBonus;

    public:

    Employee() {
        this->employeeId = "Unknown";
        this->fullName = "Unnamed";
        this->department = "Unassigned";
        this->monthlyBonus = 0;
    };

    Employee(const string& employeeId, const string& fullName) : Employee() {
        if (employeeId.length() == 0) {
            cout << "ID must not be blank!" << endl;
        } else {
            this->employeeId = employeeId;
        };
        if (fullName.length() == 0) {
            cout << "Name must not be blank!" << endl;
        } else {
            this->fullName = fullName;
        };
    };

    Employee(const string& employeeId, const string& fullName, const string& department) : Employee(employeeId, fullName) {
        if (department.length() == 0) {
            cout << "Department must not be blank!" << endl;
        } else {
            this->department = department;
        };
    };

    string getEmployeeId() {
        return employeeId;
    }

    void addBonus(double amount) {
        this->monthlyBonus += amount;
    };


    void addBonus(double amount, const string& reason) {
        if (reason.length() == 0) {
            cout << "Reason for added bonus must not be blank!" << endl;
        } else {
            cout << "Reason: " << reason << "." << endl;
            this->monthlyBonus += amount;
        }
    };
    void addBonus(double rate, double referenceAmount, const string& reason) {
        if (reason.length() == 0 || rate <= 0 || rate > 0.5 || referenceAmount <= 0) {
            cout    << "Either:" << endl
                    << "Reason for added bonus must not be blank!" << endl
                    << "Rate must be between 0 and 0.5!" << endl
                    << "Reference Amount must be positive!" << endl;
        } else {
            cout << "Reason: " << reason << "." << endl;
            this->monthlyBonus += (referenceAmount * rate);
        }
    };

    virtual double calculateGrossPay() = 0;

    virtual string getEmployeeType() = 0;

    virtual void displayPayrollInfo() = 0;


};

class SalariedEmployee: public Employee {
    
    protected:

    double monthlySalary;
    double responsibilityAllowance;

    public:

    SalariedEmployee() : Employee() {
        this->monthlySalary = 0;
        this->responsibilityAllowance = 0;
    };

    SalariedEmployee(const string& employeeId, const string& fullName, const string& department, double monthlyBonus, double monthlySalary, double responsibilityAllowance) : Employee(employeeId, fullName, department) {
        if (monthlyBonus < 0) {
            cout << "Bonus must not be negative!" << endl;
        } else {
            this->monthlyBonus = monthlyBonus;
        };
        this->monthlySalary = monthlySalary;
        this->responsibilityAllowance = responsibilityAllowance;
    };

    double calculateGrossPay() {
        return monthlySalary + responsibilityAllowance + monthlyBonus;
    };

    string getEmployeeType() {
        return "Salaried";
    };

    void displayPayrollInfo() {
        cout    << "Monthly salary: " << monthlySalary << endl
                << "Responsibility allowance: " << responsibilityAllowance << endl
                << "Monthly bonus: " << monthlyBonus << endl
                << "Gross pay: " << calculateGrossPay() << endl;
    };

};

class HourlyEmployee: public Employee {
    
    protected:
    
    double hourlyRate;
    double workedHours;

    public:

    HourlyEmployee() : Employee() {
        this->hourlyRate = 0;
        this->workedHours = 0;
    };

    HourlyEmployee(const string& employeeId, const string& fullName, const string& department, double monthlyBonus, double hourlyRate, double workedHours) : Employee(employeeId, fullName, department) {
        if (monthlyBonus < 0) {
            cout << "Bonus must not be negative!" << endl;
        } else {
            this->monthlyBonus = monthlyBonus;
        };
        this->hourlyRate = hourlyRate;
        if (workedHours < 0 || workedHours > 250) {
            cout << "Worked hours must be between 0 and 250!" << endl;
        } else {
            this->workedHours = workedHours;
        };
    };

    double calculateGrossPay() {
        double basePay;
        if (workedHours <= 160) {
            basePay = workedHours * hourlyRate;
        } else {
            basePay = 160 * hourlyRate + (workedHours - 160) * hourlyRate * 1.5;
        };

        return basePay + monthlyBonus;
    };

    string getEmployeeType() {
        return "Hourly";
    };

    void displayPayrollInfo() {
        cout    << "Hourly rate: " << hourlyRate << endl
                << "Worked hours: " << workedHours << endl
                << "Monthly bonus: " << monthlyBonus << endl
                << "Gross pay: " << calculateGrossPay() << endl;
    };
};

class SalesEmployee: public Employee {

    protected:

    double baseSalary;
    double salesRevenue;
    double commissionRate;

    public:

    SalesEmployee() : Employee() {
        this->baseSalary = 0;
        this->salesRevenue = 0;
        this->commissionRate = 0;

    };

    SalesEmployee(const string& employeeId, const string& fullName, const string& department, double monthlyBonus, double baseSalary, double salesRevenue, double commissionRate) : Employee(employeeId, fullName, department) {
        if (monthlyBonus < 0) {
            cout << "Bonus must not be negative!" << endl;
        } else {
            this->monthlyBonus = monthlyBonus;
        };
        this->baseSalary = baseSalary;
        this->salesRevenue = salesRevenue;
        if (commissionRate < 0 || commissionRate > 0.3) {
            cout << "Commission rate must be between 0 and 0.3!" << endl;
        } else {
            this->commissionRate = commissionRate;
        };
    };

    double calculateGrossPay() {
        return baseSalary + salesRevenue * commissionRate + monthlyBonus;
    };

    string getEmployeeType() {
        return "Sales";
    };

    void displayPayrollInfo() {
        cout    << "Base salary: " << baseSalary << endl
                << "Sales revenue: " << salesRevenue << endl
                << "Commission rate: " << commissionRate << endl
                << "Monthly bonus: " << monthlyBonus << endl
                << "Gross pay: " << calculateGrossPay() << endl;
    };

};

class Payroll {

    private:

    string period;
    vector<Employee*> payrollList;

    public:

    void addEmployee(Employee& employee) {
        payrollList.push_back(&employee);
    };

    Employee* findEmployee(string& employeeId) {
        for (Employee* employee : payrollList) {
            if (employee->getEmployeeId() == employeeId) {
                return employee;
            };
        };
        cout << "Cannot find employee!" << endl;
        return nullptr;
    };

    double calculateTotalPayroll() {
        double totalPayroll;
        for (Employee* employee : payrollList) {
            totalPayroll += employee->calculateGrossPay();
        };
        return totalPayroll; 
    };

    double calculatePayrollByDepartment(const string& department) {
        double totalDepartment;
        for (Employee* employee : payrollList) {
            if (employee->getEmployeeType() == department) {
                totalDepartment += employee->calculateGrossPay();
            };
        };
        return totalDepartment;
    };

    Employee* findHighestPaidEmployee() {
        Employee* highEmployee;
        double highPayroll;
        for (Employee* employee : payrollList) {
            if (employee->calculateGrossPay() > highPayroll) {
                highEmployee = employee;
                highPayroll = employee->calculateGrossPay();
            };
        };
        return highEmployee;
    };

    void displayPayroll() {
        cout    << "Highest paid: " << findHighestPaidEmployee()->getEmployeeId() << " for " << findHighestPaidEmployee()->calculateGrossPay() << endl
                << "Total paid:" << calculateTotalPayroll() << endl;
    };


};

int main() {

    cout << fixed << 1000000 << setprecision(2); 

    SalariedEmployee employee1("E001", "Nguyen Minh An", "Dao tao", 1000000, 15000000, 2000000);
    employee1.displayPayrollInfo();

    HourlyEmployee employee2("E002", "Tran Thu Binh", "Ho tro", 500000, 100000, 150);
    employee2.displayPayrollInfo();

    HourlyEmployee employee3("E003", "Le Hoang Chi", "Ho tro", 0, 100000, 170);
    employee3.displayPayrollInfo();
    
    SalesEmployee employee4("E004", "Pham Quoc Dung", "Kinh doanh", 0, 8000000, 200000000, 0.05);
    employee4.addBonus(0.02, 50000000, "Some funny reason");
    employee4.displayPayrollInfo();


    
};