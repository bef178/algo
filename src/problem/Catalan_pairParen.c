/**
 * 括号匹配
 * n对括号有哪些合适的匹配方式
 */

#include <assert.h>
#include <stdio.h>

static void printParen(Deque * deque) {
    for (int last = 0, i = 0; i < Deque_size(deque); i++) {
        int nOpening = Deque_get(deque, i);
        if (nOpening - last > 0) {
            // increased: opening parenthesis
            printf("(");
        } else {
            // no change: closing parenthesis
            assert(nOpening == last);
            printf(")");
        }
        last = nOpening;
    }
    printf("\n");
}

// branch and bound
static int pairParen_bb(Deque * deque, int n) {
    assert(deque != NULL);
    int count = 0;
    int size = Deque_size(deque);
    int nOpening = size == 0 ? 0 : Deque_peekTail(deque);
    int nClosing = size - nOpening;
    if (nClosing > nOpening) {
        return count;
    }
    if (nOpening - nClosing > n - size) {
        return count;
    }
    if (size == n && nOpening == nClosing) {
        // printParen(deque);
        count++;
    }
    if (size < n) {
        Deque_pushTail(deque, nOpening + 1);
        count += pairParen_bb(deque, n);
        Deque_pullTail(deque);
        Deque_pushTail(deque, nOpening);
        count += pairParen_bb(deque, n);
        Deque_pullTail(deque);
    }
    return count;
}

int Catalan_pairParen(int n) {
    Deque * deque = Deque_malloc();
    int count = pairParen_bb(deque, n * 2);
    Deque_free(deque);
    return count;
}

void testPairParen() {
    printf("testing Catalan_pairParen ...\n");
    assert(Catalan_pairParen(1) == 1);
    assert(Catalan_pairParen(3) == 5);
    assert(Catalan_pairParen(5) == 42);
}
