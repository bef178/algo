/**
 * SkipList
 *
 * +---+                         +---+                                   +---+
 * | x | ----------------------> | x | --------------------------------> | x |
 * +---+     +---+               +---+     +---+                         +---+
 * | x | --> | x | ------------> | x | --> | x | ----------------------> | x |
 * +---+     +---+     +---+     +---+     +---+     +---+     +---+     +---+
 * | x | --> | x | --> | x | --> | x | --> | x | --> | x | --> | x | --> | x |
 * +---+     +---+     +---+     +---+     +---+     +---+     +---+     +---+
 */

#include <stdlib.h>
#include <time.h>

static const int PROBABILITY_PERCENTAGE = 50;

typedef struct SkipListNode {
    struct SkipListNode ** nexts;
    int height;
    int64 value;
} SkipListNode;

static
SkipListNode * SkipListNode_malloc(int64 value, int height) {
    SkipListNode * self = calloc(1, sizeof(SkipListNode));
    self->nexts = calloc(height, sizeof(SkipListNode *));
    self->height = height;
    self->value = value;
}

static
void SkipListNode_free(SkipListNode * self) {
    free(self->nexts);
    free(self);
}

public
typedef struct SkipList {
    SkipListNode * head;
    int height;
} SkipList;

public
SkipList * SkipList_malloc(int height) {
    SkipList * self = calloc(1, sizeof(SkipList));
    self->head = SkipListNode_malloc(0, height);
    self->height = height;
    return self;
}

public
void SkipList_free(SkipList * self) {
    SkipListNode_free(self->head);
    free(self);
}

static
int SkipList_randomHeight(SkipList * self) {
    srand(time(NULL));
    int height = 1;
    while (height <= self->height && rand() % 100 < PROBABILITY_PERCENTAGE) {
        height++;
    }
    return height;
}

/**
 * for each level, find the last node p where p->next == HEAD or p->next->value < value
 */
static
SkipListNode ** SkipList_getLowerBounds(SkipList * self, int64 value) {
    SkipListNode ** lowerBounds = calloc(self->height, sizeof(SkipListNode *));
    SkipListNode * p = self->head;
    for (int i = self->height - 1; i >= 0; i--) {
        SkipListNode * next = p->nexts[i];
        while (next != NULL && next->value < value) {
            p = next;
        }
        lowerBounds[i] = p;
    }
    return lowerBounds;
}

public
int SkipList_insert(SkipList * self, int64 value) {
    int height = SkipList_randomHeight(self);
    SkipListNode * newNode = SkipListNode_malloc(value, height);
    SkipListNode ** lowerBounds = SkipList_getLowerBounds(self, value);
    for (int i = 0; i < height; i++) {
        newNode->nexts[i] = lowerBounds[i]->nexts[i];
        lowerBounds[i]->nexts[i] = newNode;
    }
    free(lowerBounds);
}

public
void SkipList_remove(SkipList * self, int64 value) {
    SkipListNode ** lowerBounds = SkipList_getLowerBounds(self, value);
    SkipListNode * targetNode = lowerBounds[0]->nexts[0];
    if (targetNode == NULL || targetNode->value != value) {
        return;
    }
    for (int i = 0; i < self->height; i++) {
        SkipListNode * p = lowerBounds[i];
        if (p->nexts[i] == targetNode) {
            p->nexts[i] = targetNode->nexts[i];
        }
    }
    SkipListNode_free(targetNode);
}

public
boolean SkipList_contains(SkipList * self, int64 value) {
    SkipListNode ** lowerBounds = SkipList_getLowerBounds(self, value);
    SkipListNode * targetNode = lowerBounds[0]->nexts[0];
    if (targetNode == NULL || targetNode->value != value) {
        return false;
    }
    return true;
}
