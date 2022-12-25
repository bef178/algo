#ifndef _INCLUDED_MAPENTRY
#define _INCLUDED_MAPENTRY

typedef struct MapEntry {
    int64 key;
    int64 value;
} MapEntry;

MapEntry * MapEntry_wrapValue(int64 key, int64 value);

void MapEntry_free(MapEntry * self);

MapEntry * MapEntry_copy(MapEntry * self);

#endif // _INCLUDED_MAPENTRY
