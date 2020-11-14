//Austin Johnson

typedef struct set SET;


SET *createDataSet(int maxElts, int (*hash)());

void destroyDataSet(SET *sp);

int searchID(SET *sp, int target, int *found);

void insertion(SET *sp, int age, int id);

void deletion(SET *sp, int id);

