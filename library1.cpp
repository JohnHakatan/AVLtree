#include "library1.h"   
#include "City.h"
void *Init()
{
    City* new_city;
    try{
        new_city=new City();
    }catch(std::bad_alloc& e){return nullptr;}

    return (void*)new_city;
}

StatusType AddCompany(void *DS, int CompanyID, int Value)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->AddCompany(CompanyID,Value);
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->AddEmployee(EmployeeID,CompanyID,Salary,Grade);
}
StatusType RemoveCompany(void *DS, int CompanyID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->RemoveCompany(CompanyID);
}

StatusType RemoveEmployee(void *DS, int EmployeeID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->RemoveEmployee(EmployeeID);
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->GetCompanyInfo(CompanyID,Value,NumEmployees);
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->GetEmployeeInfo(EmployeeID,EmployerID,Salary,Grade);
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->IncreaseCompanyValue(CompanyID,ValueIncrease);
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->PromoteEmployee(EmployeeID,SalaryIncrease,BumpGrade);
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->HireEmployee(EmployeeID,NewCompanyID);       
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->AcquireCompany(AcquirerID,TargetID,Factor);
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->GetHighestEarner(CompanyID,EmployeeID);
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->GetAllEmployeesBySalary(CompanyID,Employees,NumOfEmployees);
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->GetHighestEarnerInEachCompany(NumOfCompanies,Employees);
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
        {
        if(!DS)
        {
            return INVALID_INPUT;
        }
        return ((City*)DS)->GetNumEmployeesMatching(CompanyID,MinEmployeeID,MaxEmployeeId,MinSalary,MinGrade,TotalNumOfEmployees,NumOfEmployees);
        }
void Quit(void** DS)
{
    if(!DS)
    {
        return;
    }
    ((City*)(*DS))->destroyCity();
    delete ((City*)*DS);
    *DS=nullptr;
}