#include <stdlib.h>

MapEntry * MapEntry_malloc(int64 key, void * value) {
    MapEntry * self = calloc(1, sizeof(MapEntry));
    self->key = key;
    self->value = value;
    return self;
}

void MapEntry_free(MapEntry * self) {
    free(self);
}
