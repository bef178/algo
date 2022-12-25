#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void test_get() {
    HashMap * map = HashMap_malloc(640, &Int64_compare, &Int64_hash);

    int value = HashMap_getOrDefault(map, 5, 15);
    assert(value == 15);
    assert(HashMap_size(map) == 0);

    value = HashMap_getOrPut(map, 5, 25);
    assert(value == 25);
    assert(HashMap_get(map, 5) == 25);
    assert(HashMap_size(map) == 1);

    HashMap_free(map);
}

static void test_put() {
    HashMap * map = HashMap_malloc(640, &Int64_compare, &Int64_hash);

    assert(!HashMap_containsKey(map, 5));
    assert(HashMap_get(map, 5) == 0);

    HashMap_put(map, 5, 15);
    assert(HashMap_containsKey(map, 5));
    assert(HashMap_get(map, 5) == 15);

    int old = HashMap_put(map, 5, 25);
    assert(old == 15);
    assert(HashMap_containsKey(map, 5));
    assert(HashMap_get(map, 5) == 25);

    HashMap_remove(map, 5);
    assert(!HashMap_containsKey(map, 5));
    assert(HashMap_get(map, 5) == 0);

    HashMap_free(map);
}

static void test_size() {
    HashMap * map = HashMap_malloc(640, &Int64_compare, &Int64_hash);
    assert(HashMap_size(map) == 0);

    srand(time(NULL));

    int size = 0;
    for (int i = 0; i < 1000000; i++) {
        boolean op = rand() % 2 == 1;
        int key = rand() % 2048;
        if (op) {
            // insert
            int value = rand();
            if (!HashMap_containsKey(map, key)) {
                size++;
            }
            HashMap_put(map, key, value);
        } else {
            // remove
            if (HashMap_containsKey(map, key)) {
                size--;
            }
            HashMap_remove(map, key);
        }
        assert(HashMap_size(map) == size);
    }

    HashMap_free(map);
}

void testHashMap() {
    printf("testing HashMap ...\n");
    test_get();
    test_put();
    test_size();
}
