//this file works as API to reasource component

typedef enum resourceType{
    food = 0,
    wood,
    stone
}resourceType;

//initializese resources data structures
void initReasources(void);

//this function is used for requesting reasources, returns amount of requested resources
float getResource(resourceType type, float request);

//this function is uesd for creating resources
void createResource(resourceType type, float amount);

//this function is used to change storage capacity of certain resource
void setResourceCap(resourceType type, int value);

float resourceState(resourceType type);
int resourceCap(resourceType type);

