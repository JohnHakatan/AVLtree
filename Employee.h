#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <string>

#include <iostream>
#include<memory>

//namespace mtm{

    class Employee
    {
        
        int id;
        int salary ;

        public : 
        int getSalary() const;
        void setSalary(int salary);
        void setScore(int score);
        Employee(int id ): id(id),salary(0){}
        // employee and company must have costructor with 0 parameter
        Employee(const Employee& Employee)=default;
        Employee& operator=(const Employee& Employee)=default;
        virtual ~Employee()=default;
        int getId()const;
        friend bool operator<(const Employee& ,const Employee& );
        friend bool operator==(const Employee& ,const Employee& );
      //  virtual Employee* clone()const=0 ; 
    
    };
    

bool operator>(const Employee& , const Employee&);
bool operator<=(const Employee& , const Employee&);
bool operator>=(const Employee& , const Employee&);
bool operator!=(const Employee&  , const Employee& );




//}
#endif