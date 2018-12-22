#include <assert.h>
#include <stdio.h>

static int compare(int64 key1, int64 key2) {
    return key1 - key2;
}

static int hash(int64 key) {
    return key;
}

void testHashMap() {
    printf("testing HashMap ...\n");
    HashMap * map = HashMap_malloc(12, &compare, &hash);
    HashMap_put(map, 5, (void *) 15);
    HashMap_put(map, 12, (void *) 36);
    HashMap_put(map, 33, (void *) 99);
    assert(HashMap_size(map) == 3);
    assert(HashMap_get(map, 12) == (void *) 36);
    HashMap_remove(map, 12);
    assert(HashMap_size(map) == 2);
    assert(HashMap_contains(map, 12) == false);
    HashMap_free(map);
}
