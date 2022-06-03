#include "City.h"

    AVLNode<shared_ptr<Company>,CompanyCompareByID>* City::getCompanyById(int id)
    {
       shared_ptr<Company> company_to_check=make_shared<Company>(id);
       AVLNode<shared_ptr<Company>,CompanyCompareByID>*  toRTN = tree_of_companies.find(tree_of_companies.getRoot(),company_to_check);
    
       return toRTN;

    }

    AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* City::getEmployeeById(int id)
    {
        shared_ptr<Employee>employee_to_check=make_shared<Employee>(id);
        return this->employees_by_id.find(employees_by_id.getRoot(),employee_to_check);
    }
    
    AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* City::GetEmployeeBySalry(int id,int salary)
    {
        shared_ptr<Employee>employee_to_check=make_shared<Employee>(id,0,salary);
        return this->employees_by_salary.find(this->employees_by_salary.getRoot(),employee_to_check);
    }

    void City::updateEmployee(int EmployeeID,int SalaryIncrease,int BumpGrade)
    {

        AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* old_data_id=getEmployeeById(EmployeeID);
        
        int new_salary=old_data_id->getData()->getSalary()+SalaryIncrease;
        int new_grade=old_data_id->getData()->getGrade();
        if(BumpGrade>0)
        {
            new_grade+=1;
        }
        shared_ptr<Employee> new_by_id;
        try{
            new_by_id =make_shared<Employee>(EmployeeID,new_grade,new_salary,old_data_id->getData()->getCompanyId(),old_data_id->getData()->getCompany());
        }catch(std::bad_alloc& e)
        {
            throw;
        }

        shared_ptr<Employee> ptr=old_data_id->getData();
        employees_by_salary.AVLRemoveVal(ptr);
        employees_by_id.AVLRemoveVal(ptr);
        shared_ptr<Employee> new_by_id1=new_by_id;
        employees_by_id.AVLInsert(new_by_id);
        employees_by_salary.AVLInsert(new_by_id1);
        

    }


    City::City(){

        tree_of_companies=  AVLTree<shared_ptr<Company>,CompanyCompareByID>();
        employees_by_salary=AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>();
        employees_by_id= AVLTree<shared_ptr<Employee>,EmployeeComparebyID>();
   this->num_of_employees=0;
    }



    StatusType City::AddCompany(int CompanyID, int Value)
    {
        //check conditions are valid
        if(Value<=0 || CompanyID<=0)
        {
            return INVALID_INPUT;
        }

     
           shared_ptr<Company> new_company=make_shared<Company>(CompanyID,Value);
       

        int val = tree_of_companies.AVLInsert(new_company);//INSERT CHECKS IF DATA EXIST OR NOT
        if(val==MEMORY_ERROR)return ALLOCATION_ERROR;
        if(val==DATA_EXIST)return FAILURE;
        return SUCCESS;
    }





    StatusType City::RemoveCompany(int CompanyID)
    {
        if(CompanyID<=0)
        {
            return INVALID_INPUT;
        }

        AVLNode<shared_ptr<Company>,CompanyCompareByID>* to_remove=getCompanyById(CompanyID);

        if(!(to_remove))
        {
            return FAILURE;
        }
            
       
         if(to_remove)
        if(to_remove->getData()->employees_by_id.getNum_of_nodes()!=0)
        {
            return FAILURE;
        }
        if(!to_remove)
        {
            return FAILURE;
        }
       

        tree_of_companies.AVLRemoveVal(to_remove->getData());
      
        to_remove=NULL;
        
        return SUCCESS;
    }

    StatusType City::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
    {
        //check conditions are valid
        if(CompanyID<=0 ||  EmployeeID<=0 || Salary<=0 || Grade<0)
        {
            return INVALID_INPUT;
        }
if(!getCompanyById(CompanyID))return FAILURE;
        //check the company is exist in the system
        shared_ptr<Company> company_to_update = getCompanyById(CompanyID)->getData();
        if(!company_to_update)
        {
            return FAILURE;
        }
        if(getEmployeeById(EmployeeID))return FAILURE;
        // employee_to_check(nullptr);
  

   
         shared_ptr<Employee>   employee_to_check=make_shared<Employee>(EmployeeID,Grade,Salary,CompanyID,company_to_update);
            
     
        

        int val = employees_by_id.AVLInsert(employee_to_check);
        if(val==MEMORY_ERROR || val==DATA_EXIST)
        {
            return FAILURE;
        }

        val= employees_by_salary.AVLInsert(employee_to_check);
         if(val==MEMORY_ERROR || val==DATA_EXIST)
        {//maybe we must delete what we have inserted
            return FAILURE;
        }
   
        this->num_of_employees++;
        try{
        company_to_update->addEmployeeToCompany( employee_to_check);
        }catch(std::bad_alloc& e){
        throw;
        }
        return SUCCESS;

     
        

    }
    StatusType City::RemoveEmployee(int EmployeeID)
    {
        if(EmployeeID<=0)
        {
            return INVALID_INPUT;
        }

        // check if is there an employee with the same id in the city
    AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* employee_to_remove= getEmployeeById(EmployeeID);
     if(!employee_to_remove)
        {
            return FAILURE;
        }
    AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* employee_to_remove1= GetEmployeeBySalry(EmployeeID,employee_to_remove->getData()->getSalary());
       
      //if(!employee_to_remove1)cout<<"slkajfdlkajs"<<endl;
        employee_to_remove->getData()->getCompany()->RemoveEmployee(EmployeeID);
        employees_by_id.AVLRemoveVal(employee_to_remove->getData());
        employees_by_salary.AVLRemoveVal(employee_to_remove1->getData());
        this->num_of_employees--;
        return SUCCESS;

    }
    
    StatusType City::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees)
    {
        //check constions are valid
        if(!Value||!NumEmployees||CompanyID<=0)
        {
            return  INVALID_INPUT;
        }
        
        //check if company exist
        AVLNode<shared_ptr<Company>,CompanyCompareByID>* company_to_get=getCompanyById(CompanyID);
        // if(!company_to_get || company_to_get->getData()->is_sold())
        // {
        //     return FAILURE;
        // }
               if(!company_to_get )
        {
            return FAILURE;
        }

        *Value = company_to_get->getData()->getValue();
        *NumEmployees = company_to_get->getData()->employees_by_id.getNum_of_nodes();
        return SUCCESS;
    }

    StatusType City::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade)
    {
        //check constions are valid
        if(!EmployerID||!Salary||!Grade||EmployeeID<=0)
        {
            return INVALID_INPUT;
        }
        AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* employee_to_get=getEmployeeById(EmployeeID);
        if(!employee_to_get)
        {
            return FAILURE;
        }
        *EmployerID=employee_to_get->getData()->getCompanyId();
        *Salary=employee_to_get->getData()->getSalary();
        *Grade=employee_to_get->getData()->getGrade();
         return SUCCESS;
    }

    StatusType City::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
    {
        if(CompanyID<=0||ValueIncrease<=0)
        {
            return INVALID_INPUT;
        }
        AVLNode<shared_ptr<Company>,CompanyCompareByID>* company_to_update=getCompanyById(CompanyID);
        if(!company_to_update)
        {
            return FAILURE;
        }
        company_to_update->getData()->increaseValue(ValueIncrease);  
        return SUCCESS;
    }

    StatusType City::PromoteEmployee( int EmployeeID, int SalaryIncrease, int BumpGrade)
    {
        if(EmployeeID<=0 || SalaryIncrease<=0)
        {
            return INVALID_INPUT;
        }

        AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* to_update=getEmployeeById(EmployeeID);
        if(!to_update)
        {
            return FAILURE;
        }
       // cout<<"-----------------------------------------"<<to_update->getData()->getCompanyId()<<endl;
         shared_ptr<Company> company_of_employee=to_update->getData()->getCompany();
      //  cout<<company_of_employee->getData()->getID();
          try{
            updateEmployee(EmployeeID,SalaryIncrease,BumpGrade);
         }catch(std::bad_alloc& e)
        {
            return FAILURE;
        }
to_update=getEmployeeById(EmployeeID);
        try{
            company_of_employee->updateEmployee(to_update->getData());
         }catch(std::bad_alloc& e)
        {
            return FAILURE;
        }

      

        return SUCCESS;
    }

    StatusType City::HireEmployee(int EmployeeID, int NewCompanyID)
    {
        if(EmployeeID <=0 || NewCompanyID <=0)return INVALID_INPUT;
 AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* ptr =getEmployeeById(EmployeeID);
  if(!ptr)return FAILURE;
        AVLNode <shared_ptr<Company>,CompanyCompareByID>* ccc= getCompanyById(NewCompanyID);
        if((ccc==NULL) || ((ptr->getData()->getCompanyId())==NewCompanyID) )return FAILURE;

         shared_ptr<Company> company_ptr=ccc->getData();


shared_ptr<Employee>  employee_ptr=make_shared<Employee>(EmployeeID,ptr->getData()->getGrade(),ptr->getData()->getSalary()
,NewCompanyID,company_ptr);

     RemoveEmployee(EmployeeID);
    //  return AddEmployee(EmployeeID,NewCompanyID,)
     
  try{
        int val = employees_by_id.AVLInsert(employee_ptr);
        if(val==MEMORY_ERROR || val==DATA_EXIST)
        {
            return FAILURE;
        }

        val= employees_by_salary.AVLInsert(employee_ptr);
         if(val==MEMORY_ERROR || val==DATA_EXIST)
        {
            return FAILURE;
        }
      }catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }

        this->num_of_employees++;
        try{
        company_ptr->addEmployeeToCompany(employee_ptr);
        }catch(std::bad_alloc& e){
        throw;
        }
        return SUCCESS;


        
    }

    StatusType City::AcquireCompany(int AcquirerID, int TargetID, double Factor)
    {
          if(AcquirerID<=0 || TargetID<=0 || AcquirerID==TargetID || Factor< 1.0)return INVALID_INPUT;
        if(!getCompanyById(AcquirerID) || !getCompanyById(TargetID))return FAILURE;
          shared_ptr<Company> Acquirer_ptr=getCompanyById(AcquirerID)->getData();

          if(!Acquirer_ptr)return FAILURE;
          shared_ptr<Company>Target_ptr=getCompanyById(TargetID)->getData();
          if(!Target_ptr)return FAILURE;
          if(((Acquirer_ptr->getValue())/10)<(Target_ptr->getValue()))return FAILURE;
          int newVAL=((Acquirer_ptr->getValue())+(Target_ptr->getValue()))*Factor;
          Acquirer_ptr->setValue(newVAL);
          
    if(!Acquirer_ptr->moveEmployees(Target_ptr->employees_by_salary,Target_ptr->employees_by_id,Acquirer_ptr))return FAILURE;
    tree_of_companies.AVLRemoveVal(Target_ptr);

    return SUCCESS;

    
          

          


    }

    StatusType City::GetHighestEarner(int CompanyID, int *EmployeeID)
    {
        if(EmployeeID==nullptr || CompanyID==0)
        {
            return INVALID_INPUT;
        }
        if(CompanyID<0) 
        {
            if(employees_by_salary.getNum_of_nodes()==0)
            {
                return FAILURE;
            }
            *EmployeeID=employees_by_salary.getMaxNode()->getData()->getId();
            return SUCCESS;
        }
        AVLNode<shared_ptr<Company>,CompanyCompareByID>* company_of_employee=getCompanyById(CompanyID);
        if(!company_of_employee || !company_of_employee->getData()->employees_by_salary.getMaxNode())
        {
            return FAILURE;
        }

        *EmployeeID=company_of_employee->getData()->employees_by_salary.getMaxNode()->getData()->getId();
        return SUCCESS;
    }
    
    StatusType City::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
    {
       if( CompanyID==0  || Employees==nullptr || NumOfEmployees==nullptr)
        {
            return INVALID_INPUT;
        }

         *NumOfEmployees=0;
       int* arr;
       
        if(CompanyID<0) 
        {
             if(employees_by_salary.getNum_of_nodes()==0)
            {
                
                return FAILURE;
            }
            *NumOfEmployees=this->num_of_employees;
           
            arr=((int*)malloc(sizeof(int) * (*NumOfEmployees)));
             AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* ptr=employees_by_salary.getMaxNode();
            for(int i=0;i<*NumOfEmployees ;i++  )
            {
                if(!ptr)break;
                arr[i]=0;
                arr[i]=ptr->getData()->getId();
                ptr=employees_by_salary.the_next_node_iterating(ptr);
            }
            
            
        }else{

             AVLNode<shared_ptr<Company>,CompanyCompareByID>* company=getCompanyById(CompanyID);
             
        if(!company  )
        {
            return FAILURE;
        }
        
 AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* ptr_employee=company->getData()->employees_by_salary.getMaxNode();
 *NumOfEmployees=company->getData()->employees_by_id.getNum_of_nodes();
 if(*NumOfEmployees==0)
            {
                
                return FAILURE;
            }
arr=((int*)malloc(sizeof(int) * (*NumOfEmployees)));
        for(int i=0;i<*NumOfEmployees;i++)
        {
            
            arr[i]=0;
             arr[i]=ptr_employee->getData()->getId();
             ptr_employee=company->getData()->employees_by_salary.the_next_node_iterating(ptr_employee);
        }

        }

        
        (*Employees)= arr;
        return SUCCESS;

       
   }

    StatusType City::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
    {
       if(NumOfCompanies <1 || Employees==nullptr)return INVALID_INPUT;

    int* arr = ((int*)malloc(sizeof(int)*NumOfCompanies));
    if(!(arr))return ALLOCATION_ERROR;
     AVLNode<shared_ptr<Company>,CompanyCompareByID>* company= (this->tree_of_companies).getMaxNode();
     AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>*  ptr_employee;
       
     if(company)ptr_employee=company->getData()->employees_by_salary.getMaxNode();
        for(int i=0;i<NumOfCompanies;i++)
        {
            if(!company )
            {free(arr);
                return FAILURE;

            }
           
          
             if(company && ptr_employee)
             {arr[i]=ptr_employee->getData()->getId();
             }
             else
             {
i--;
             }
                 company = this->tree_of_companies.the_next_node_iterating(company);
             
             if(company)ptr_employee=company->getData()->employees_by_salary.getMaxNode();
             //ptr_employee=company->getData()->employees_by_salary.the_next_node_iterating(ptr_employee);

        }

        (*Employees)=arr;
        return SUCCESS;


    }

    /*static AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* biggest_one(  AVLTree<shared_ptr<Employee>,EmployeeComparebyID>* tree,int id)
    {
        shared_ptr<Employee> e = make_shared<Employee>(id);
      AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* toRtn= tree->find_max_min_than(tree->getRoot(),e);

        return toRtn;
    }*/

    StatusType City::GetNumEmployeesMatching( int CompanyID, int MinEmployeeID, int MaxEmployeeId,
             int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
            {
                if(CompanyID==0 || TotalNumOfEmployees==nullptr || NumOfEmployees==nullptr || MinEmployeeID<0 
                || MaxEmployeeId<0|| MinSalary<0 || MinGrade<0  ||(MinEmployeeID>MaxEmployeeId))return INVALID_INPUT;

*TotalNumOfEmployees=*NumOfEmployees=0;

               AVLTree<shared_ptr<Employee>,EmployeeComparebyID>* tree;
AVLNode<shared_ptr<Company>,CompanyCompareByID>* company;
                if(CompanyID<0)
                {
                    if(this->employees_by_id.getNum_of_nodes()==0)return FAILURE;
                    tree=&(this->employees_by_id); 
                }
                else
                {
                   company=getCompanyById(CompanyID);
                    if(!company )return FAILURE;
                    if(company->getData()->employees_by_id.getNum_of_nodes()==0)return FAILURE;
                    tree=&(company->getData()->employees_by_id);
                }
       
      // cout<<tree->getMaxNode()<<endl;
    AVLNode <shared_ptr<Employee>,EmployeeComparebyID>* ptr_employee=tree->getMaxNode();
       for(;(ptr_employee);)
        { 
            //if(!ptr_employee->getData)
                 
        int id =ptr_employee->getData()->getId();
        int grade=ptr_employee->getData()->getGrade();
        int salary=ptr_employee->getData()->getSalary();
            if(id>=MinEmployeeID && id<=MaxEmployeeId)
            {
                (*TotalNumOfEmployees)++;
                if(salary>=MinSalary && grade>=MinGrade)(*NumOfEmployees)++;
            }
           

          ptr_employee=tree->the_next_node_iterating(ptr_employee);
     
        }


                return SUCCESS;


            }
    
    void City::destroyCity()
    {
  
    }
    City::~City()
    {
       
    }