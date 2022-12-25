#include <assert.h>
#include <stdio.h>
#include <string.h>

void testCsvParseDryrun() {
    printf("testing Csv parse dryrun ...\n");

    byte * src = NULL;
    int n = 0;
    int i = 0;
    int delim = 0;

    src = "go,face the";
    n = Csv_parse(src, strlen(src), NULL, 1, &i, &delim);
    assert(n == 2);
    assert(i == 3);
    assert(delim == COMMA);
}

void testCsvParse() {
    printf("testing Csv parse ...\n");

    int bufferCapacity = 1024;
    byte buffer[bufferCapacity];
    byte * src = NULL;
    int n = 0;
    int i = 0;
    int delim = 0;

    memset(buffer, 0, bufferCapacity);
    src = "a.!,\"asdf\"\r\n";
    n = Csv_parse(src, strlen(src), buffer, bufferCapacity, &i, &delim);
    assert(n == 3);
    assert(memcmp(buffer, "a.!", n) == 0);
    assert(i == 4);
    assert(delim == COMMA);
    n = Csv_parse(src + i, strlen(src) - i, buffer, bufferCapacity, &i, &delim);
    assert(n == 4);
    assert(memcmp(buffer, "asdf", n) == 0);
    assert(i == 8);
    assert(delim == LF);

    memset(buffer, 0, bufferCapacity);
    src = "\"我a\"";
    n = Csv_parse(src, strlen(src), buffer, bufferCapacity, &i, &delim);
    assert(n == strlen(src) - 2);
    assert(memcmp(buffer, "我a", n) == 0);
    assert(i == strlen(src));
    assert(delim == EOF);

    testCsvParseDryrun();
}

void testCsvSerializeDryrun() {
    printf("testing Csv serialize dryrun ...\n");

    byte * src = NULL;
    int n = 0;

    src = "a..!";
    n = Csv_serialize(src, strlen(src), NULL, 2, false);
    assert(n == 5);

    src = "\aaf";
    n = Csv_serialize(src, strlen(src), NULL, 2, true);
    assert(n == 7);
}

void testCsvSerialize() {
    printf("testing Csv serialize ...\n");

    int bufferCapacity = 1024;
    byte buffer[bufferCapacity];
    byte * src = NULL;
    int n = 0;

    memset(buffer, 0, bufferCapacity);
    src = "asdf";
    n = Csv_serialize(src, strlen(src), buffer, bufferCapacity, false);
    assert(memcmp(buffer, "asdf,", n) == 0);

    memset(buffer, 0, bufferCapacity);
    src = "as,df";
    n = Csv_serialize(src, strlen(src), buffer, bufferCapacity, false);
    assert(memcmp(buffer, "\"as,df\",", n) == 0);

    memset(buffer, 0, bufferCapacity);
    src = "a\"sdf";
    n = Csv_serialize(src, strlen(src), buffer, bufferCapacity, false);
    assert(memcmp(buffer, "\"a\"\"sdf\",", n) == 0);

    memset(buffer, 0, bufferCapacity);
    src = "a我们f";
    n = Csv_serialize(src, strlen(src), buffer, bufferCapacity, true);
    assert(memcmp(buffer, "\"a我们f\"\r\n", n) == 0);

    memset(buffer, 0, bufferCapacity);
    src = "a\tf";
    n = Csv_serialize(src, strlen(src), buffer, bufferCapacity, true);
    assert(memcmp(buffer, "\"a\tf\"\r\n", n) == 0);

    memset(buffer, 0, bufferCapacity);
    src = "\0af";
    n = Csv_serialize(src, 3, buffer, bufferCapacity, true);
    assert(memcmp(buffer, "\"\0af\"\r\n", n) == 0);

    testCsvSerializeDryrun();
}

void testCsv() {
    testCsvParse();
    testCsvSerialize();
}
