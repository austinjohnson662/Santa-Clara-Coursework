//Austin Johnson

typedef struct set SET;

SET *createDataSet(int maxElts);

void destroyDataSet(SET *sp);

int searchAge(SET *sp, int target, int *found);

void insertion(SET *sp, int age, int id);

void deletion(SET *sp, int id);

int maxAgeGap(SET *sp);
