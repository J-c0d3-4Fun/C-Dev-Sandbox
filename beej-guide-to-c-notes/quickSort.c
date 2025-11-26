#include <stdio.h>
#include <stdlib.h>


struct transportation {
    char *type;
    int numOfWheels;
    int numOfSeats;

};


int getComparison( const void *element1, const void *element2){
    const struct transportation *trans1 = element1;
    const struct transportation *trans2 = element2;


    if (trans1->numOfWheels > trans2->numOfWheels) {
        return 1;
    }else if (trans2->numOfWheels > trans1->numOfWheels) {
        return -1;
    }
    return 0;
}

int main(){

    struct transportation t[5] = {
        {.type="Car", .numOfWheels=4},
        {.type="Motorcycle", .numOfWheels=2},
        {.type="Airplane", .numOfWheels=4},
        {.type="Spaceship", .numOfWheels=0},
        {.type="Truck", .numOfWheels=4}
    };
    // qsort compares two items that you have in your array to be sorted.
    // it does this without needing to have the types of items hardcoded in there anywhere
    qsort(t, 5, sizeof(struct transportation), getComparison);

    unsigned int i;
    // Divide total count sizeof(t) by the size f a single element to get the count. <- counting elements in array
    for (i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
        printf("%d: %s\n", t[i].numOfWheels, t[i].type);
    }

    return 0;
}