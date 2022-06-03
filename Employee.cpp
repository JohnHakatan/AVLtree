

#include "Employee.h"
#include <iostream>

using std::endl;
using std::ostream;

//namespace mtm{

        

            void setSalary(int salary)
            {
              
            }
     void setScore(int score)
     {

     }
int Employee::getId()const
{
return this->id;
}
    int Employee::getSalary()const
            {
                    return this->salary;
            }
       
        bool operator<(const Employee& Employee1,const Employee& Employee2 )
        {
return Employee1.id<Employee2.id;
        }
         bool operator==(const Employee& Employee1,const Employee& Employee2 )
        {
return Employee2.id==Employee1.id;
        }

bool operator!=(const Employee& Employee1,const Employee& Employee2 )
{
    return !(Employee2==Employee1);

}
bool operator>(const Employee& Employee1,const Employee& Employee2 )
{
return (!(Employee1<Employee2) && (Employee2!=Employee1));
}
bool operator<=(const Employee& Employee1,const Employee& Employee2 )
{
return !(Employee1>Employee2);
}
bool operator>=(const Employee& Employee1,const Employee& Employee2 )
{
return !(Employee1<Employee2);
}










//}