#ifndef CITY_H_
#define CITY_H_

#include "library1.h"
#include "avl_tree.h"
#include "Company.h"
//#include "Employee.h"
#include<memory>
#ifdef __cplusplus
extern "C" {
#endif

class City
{
    AVLTree<shared_ptr<Company>,CompanyCompareByID> tree_of_companies;
    AVLTree<shared_ptr<Employee>,EmployeeComparebySalary> employees_by_salary;
    AVLTree<shared_ptr<Employee>,EmployeeComparebyID> employees_by_id;
      
    public:
    int num_of_employees;
    City();
    ~City();
    City(const City& city)=default;
    AVLNode<shared_ptr<Company>,CompanyCompareByID>* getCompanyById(int id);
    AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* getEmployeeById(int id);
    AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* GetEmployeeBySalry(int id,int salary);
    void updateEmployee(int EmployeeID,int SalaryIncrease,int BumpGrade);
    StatusType AddCompany(int CompanyID, int Value);
    StatusType RemoveCompany(int CompanyID);
    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);
    StatusType RemoveEmployee(int EmployeeID);
    StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
    StatusType GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);
    StatusType IncreaseCompanyValue(int CompanyID, int ValueIncrease);
    StatusType PromoteEmployee( int EmployeeID, int SalaryIncrease, int BumpGrade);
    StatusType HireEmployee(int EmployeeID, int NewCompanyID);
    StatusType AcquireCompany(int AcquirerID, int TargetID, double Factor);
    StatusType GetHighestEarner(int CompanyID, int *EmployeeID);
    StatusType GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);
    StatusType GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);
    StatusType GetNumEmployeesMatching( int CompanyID, int MinEmployeeID, int MaxEmployeeId,
    int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
    void destroyCity();
};


#ifdef __cplusplus
}
#endif

#endif