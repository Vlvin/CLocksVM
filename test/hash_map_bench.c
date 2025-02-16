#include <time.h>
#include <oneFileSTD.h>

#include <loxVM.h>
#include <loxHashMap.h>
#include <loxObject.h>
#include <loxMemory.h>

#define NUM_ENTRIES 100000

/*LoxVM vm; // dummy VM to enable memory.c compilation*/

static int benchmarkTable() {
    LoxHashMap table;
    LoxHashMap_init(&table);

    // Measure insertion time
    clock_t start = clock();
    for (int i = 0; i < NUM_ENTRIES; i++) {
        char key[32];
        snprintf(key, sizeof(key), "key%d", i);
        LoxString *objKey = copyString(&vm, key, strlen(key));
        LoxHashMap_set(&table, objKey, LOX_NUMBER_VAL(i));
    }

    clock_t end = clock();
    double insertionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Insertion time for %d entries: %f seconds\n", NUM_ENTRIES, insertionTime);

    // Measure lookup time
    start = clock();
    for (int i = 0; i < NUM_ENTRIES; i++) {
        char key[32];
        snprintf(key, sizeof(key), "key%d", i);
        LoxString *objKey = copyString(&vm, key, strlen(key));
        LoxValue value;

        if (!LoxHashMap_get(&table, objKey, &value)) {
            printf("ERROR: Key not found: %s\n", key);
            return -1;
        }

        if ((int) AS_LOX_NUMBER(value) != i) {
            printf("ERROR: Invalid value for key %d: %f\n",
                i, AS_LOX_NUMBER(value));
            return -2;
        }
    }

    end = clock();
    double lookupTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Lookup time for %d entries: %f seconds\n", NUM_ENTRIES, lookupTime);

    LoxHashMap_free(&table);
    return 0;
}

int main(void) {
    int result;
    LoxHashMap_init(&vm.strings);
    result = benchmarkTable();
    LoxHashMap_free(&vm.strings);
    return result;
}
