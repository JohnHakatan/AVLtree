#include "Company.h"
   

   shared_ptr<Company> Employee::getCompany()const
    {
      shared_ptr<Company> tortn= static_pointer_cast<Company>((this->company).lock());
        return tortn;
    }

//Company::~Company()
   /* AVLNode <Employee*,EmployeeComparebyID>* ptr=this->employees_by_id.getMaxNode();
     AVLNode <Employee*,EmployeeComparebyID>* ptr1=this->employees_by_id.the_next_node_iterating(ptr);
         while(ptr1)
         {    
        //RemoveEmployee(ptr->getData()->getId());
        delete (ptr->getData());
        ptr=ptr1;
         ptr1= this->employees_by_id.the_next_node_iterating(ptr);
        //ptr=NULL;
        }
      //if(ptr)if(ptr->getData()) RemoveEmployee(ptr->getData()->getId());
       if(ptr) delete (ptr->getData());
        
         AVLNode <Employee*,EmployeeComparebySalary>* ptr5=this->employees_by_salary.getMaxNode();
         AVLNode <Employee*,EmployeeComparebySalary>* ptr6=this->employees_by_salary.the_next_node_iterating(ptr5);
         while(ptr6)
         {    
       // RemoveEmployee(ptr5->getData()->getId());
        delete (ptr5->getData());
        ptr5=ptr6;
         ptr6= this->employees_by_salary.the_next_node_iterating(ptr5);
        //ptr=NULL;
        }
      //if(ptr5)if(ptr5->getData()) RemoveEmployee(ptr5->getData()->getId());
       if(ptr5) delete (ptr5->getData());
        */


int Company::increaseValue(int value_to_add)
{
    return this->value+=value_to_add;
}

int Company::getNumOfEmployees() const
{
    return this->num_of_employees;
}
int Company::getValue() const
{
    return this->value;
}
void Company::RemoveEmployee(int EmployeeID)
{

AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* to_remove=GetEmployeeById(EmployeeID);
AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* to_remove1=GetEmployeeBySalry(EmployeeID,to_remove->getData()->getSalary());

   
    // assert(to_remove1);
   // Employee *e=to_remove->getData();
   // Employee *e1=to_remove1->getData();

    employees_by_id.AVLRemoveVal(to_remove->getData());
    employees_by_salary.AVLRemoveVal(to_remove1->getData());

   // delete e;
    //delete e1;
    //delete to_remove1;
    //delete to_remove;
  this->num_of_employees--;

}


int Company::getID()const
{
return this->id;
}

void Company::addEmployeeToCompany( shared_ptr<Employee> employee)
{
    
   shared_ptr<Employee> employee1=employee;
   shared_ptr<Employee>employee2=employee;

    
   
    employees_by_id.AVLInsert(employee1);
    employees_by_salary.AVLInsert(employee2);
    this->num_of_employees++;
}

void Company::updateEmployee( shared_ptr<Employee> employee)
{

    /*AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>*  ptr1=employees_by_salary.getMaxNode();
    while (ptr1!=NULL)
    {
       cout<<ptr1->getData()->getId()<<endl;
       ptr1=employees_by_salary.the_next_node_iterating(ptr1);
    }*/
   RemoveEmployee(employee->getId());
 // employees_by_salary.AVLRemoveVal(employee);
  //employees_by_id.AVLRemoveVal(employee);

/*cout<<employee->getId()<<"__________________"<<endl;
    AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>*  ptr2=employees_by_salary.getMaxNode();
    while (ptr2!=NULL)
    {
       cout<<ptr2->getData()->getId()<<endl;
       ptr2=employees_by_salary.the_next_node_iterating(ptr2);
    }*/
  shared_ptr<Employee> new_by_id=employee;
  shared_ptr<Employee> new_by_salary=employee;

  employees_by_id.AVLInsert(new_by_id);
  employees_by_salary.AVLInsert(new_by_salary);


    /*AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>*  ptr=employees_by_salary.getMaxNode();
    while (ptr!=NULL)
    {
       cout<<ptr->getData()->getId()<<endl;
       ptr=employees_by_salary.the_next_node_iterating(ptr);
    }*/
   this->num_of_employees++;

   
}
void Company::setValue(int value)
{
    this->value=value;
}

AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* Company::GetEmployeeById(int id)
{
  //  Employee to_find(id);
    shared_ptr<Employee>to_find=make_shared<Employee>(id);
    return employees_by_id.find(employees_by_id.getRoot(),to_find);
}

AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* Company::GetEmployeeBySalry(int id,int salary)
{
   // Employee to_find(id,0,salary);
       shared_ptr<Employee>to_find=make_shared<Employee>(id,0,salary);
    return employees_by_salary.find(employees_by_salary.getRoot(),to_find);
}

void Employee::setCompanyId(int id)
    {
       this->company_id=id;
    }
bool Company::moveEmployees(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>& employees_by_salary1,AVLTree<shared_ptr<Employee>,EmployeeComparebyID>& employees_by_id1,
 shared_ptr<Company> company)
{
    int num=employees_by_salary1.getNum_of_nodes();
   
       AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>*  ptr=employees_by_salary1.getMaxNode();
    while (ptr!=NULL)
    {
        //cout<<ptr->getData()->getId()<<endl;
        ptr->getData()->setCompanyId(this->id);
        ptr->getData()->setCompany(company);
     
        ptr=employees_by_salary1.the_next_node_iterating(ptr);
      //  ptr1=this->employees_by_id.the_next_node_iterating(ptr1);
    }
    if(!this->employees_by_id.moveTree(employees_by_id1,this->employees_by_id))return false;
    if(!this->employees_by_salary.moveTree(employees_by_salary1,this->employees_by_salary))return false;
 
    this->num_of_employees+=num;
    

    return true;

}
void Employee::setCompany(shared_ptr<Company>  company1)
{
    this->company=static_cast<weak_ptr<Company>>(company1);
}
void Employee::setSalary(int salary)
{
        this->salary=salary;
}
void Employee::setGrade(int grade)
{
        this->grade=grade;
}
int Employee::getId()const
{
        return this->id;
}
int Employee::getCompanyId()const
{
        return this->company_id;
}
int Employee::getSalary()const
{
        return this->salary;
}

int Employee::getGrade() const
{
       return this->grade;
}
// bool operator<(const Employee& Employee1,const Employee& Employee2 )
// {
//         return Employee1.getId()<Employee2.getId();
// }
//         bool operator==(const Employee& Employee1,const Employee& Employee2 )
// {
//         return Employee2.getId()==Employee1.getId();
// }

// bool operator!=(const Employee& Employee1,const Employee& Employee2 )
// {
//         return !(Employee2==Employee1);
// }
// bool operator>(const Employee& Employee1,const Employee& Employee2 )
// {
//         return (!(Employee1<Employee2) && (Employee2!=Employee1));
// }
// bool operator<=(const Employee& Employee1,const Employee& Employee2 )
// {
//         return !(Employee1>Employee2);
// }
// bool operator>=(const Employee& Employee1,const Employee& Employee2 )
// {
//         return !(Employee1<Employee2);
// }


bool Employee::operator==(const Employee& to_compare)const
{
  if((this->id==to_compare.id) && (this->salary==to_compare.salary))
  {
    return true;
  }
  else{
    return false;
  }
}
bool Employee::operator!=(const Employee& to_compare)const
{
  return (!((*this)==to_compare));
}

bool Employee::operator<(const Employee& to_compare)const
{
  if(this->salary<to_compare.salary)
  {
    return true;
  }
  else if(this->salary==to_compare.salary)
  {
    return this->id>to_compare.id;
  }
  else{
    return false;
  }
}

bool Employee::operator<=(const Employee& to_compare)const
{
  return (*this<to_compare)||(*this==to_compare);
}
bool Employee::operator>(const Employee& to_compare)const
{
  return !(*this<=to_compare);
}
bool Employee::operator>=(const Employee& to_compare)const
{
  return !(*this<to_compare);
}

