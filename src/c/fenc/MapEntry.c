#include <stdlib.h>

MapEntry * MapEntry_wrapValue(int64 key, int64 value) {
    MapEntry * self = calloc(1, sizeof(MapEntry));
    self->key = key;
    self->value = value;
    return self;
}

void MapEntry_free(MapEntry * self) {
    free(self);
}

MapEntry * MapEntry_copy(MapEntry * self) {
    return MapEntry_wrapValue(self->key, self->value);
}
