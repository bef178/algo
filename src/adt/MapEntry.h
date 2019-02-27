#ifndef _INCLUDED_MAPENTRY
#define _INCLUDED_MAPENTRY

typedef struct MapEntry {
    int64 key;
    void * value;
} MapEntry;

MapEntry * MapEntry_malloc(int64 key, void * value);

void MapEntry_free(MapEntry * self);

MapEntry * MapEntry_copy(MapEntry * self);

#endif // _INCLUDED_MAPENTRY
