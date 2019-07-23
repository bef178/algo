#ifndef _INCLUDED_MAPITERATOR
#define _INCLUDED_MAPITERATOR

#include "MapEntry.h"

typedef void MapIterator;

boolean MapIterator_hasNext(MapIterator *);

MapEntry * MapIterator_next(MapIterator *);

void MapIterator_free(MapIterator *);

#endif // _INCLUDED_MAPITERATOR
