#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct truck {
    char *make;
    char *model;
    int  year;
    float  price;
};

void setPrice(struct truck *truck, float newPrice){
    truck->price = newPrice;
}


int main(){

    struct truck oldSchool = {.model="Mustang" ,.year=2024};
    oldSchool.make = "Ford";

    setPrice(&oldSchool, 1999.98);

    printf("Make:      %s\n", oldSchool.make);
    printf("Model:      %s\n", oldSchool.model); 
    printf("Year:      %d\n", oldSchool.year); 
    printf("Price:      %f\n", oldSchool.price);  

    return 0;
    


}