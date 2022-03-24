#ifndef Car_h
#define Car_h
// Car data 
struct CarData
{
    std::string Type;
    std::string Name;
    std::string Model;
    int Year;
    double Money;
  
    
    CarData(){};
    
    CarData(std::string type, std::string name, std::string model,int year, double money)
    {
        Type = type;
        Name = name;
        Model = model;
        Year = year;
        Money = money;
     
    };
};
#endif