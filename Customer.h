#ifndef Cus_h
#define Cus_h
//Constructor of customer 
struct CusData
{
    std::string CusName;
    std::string Identity;
    int Age;
    
     CusData(){};

     CusData(std::string cusName, std::string identity, int age)
     {
        CusName= cusName;
        Identity = identity;
        Age = age;
     };
};
#endif