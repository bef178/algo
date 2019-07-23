#include <assert.h>
#include <stdio.h>

void testHashMap() {
    printf("testing HashMap ...\n");
    HashMap * map = HashMap_malloc(12, &Int64_compare, &Int64_hash);
    HashMap_put(map, 5, 15);
    HashMap_put(map, 12, 36);
    HashMap_put(map, 33, 99);
    assert(HashMap_size(map) == 3);
    assert(HashMap_get(map, 12) == 36);
    HashMap_remove(map, 12);
    assert(HashMap_size(map) == 2);
    assert(HashMap_containsKey(map, 12) == false);
    HashMap_free(map);
}
