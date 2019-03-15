#ifndef _INCLUDED_CSV
#define _INCLUDED_CSV

#define CSV_E_ILLEGAL_FORMAT    -2
#define CSV_E_NOT_ENOUGH_SPACE  -3

/**
 * parse single value, consumes following COMMA or CR LF
 * return number of bytes written, or negative as error code
 * @nConsumedOutVar: num bytes read; valid only when succeeded
 * @lastSeparatorOutVar: EOF, COMMA or LF; valid only when succeeded
 */
int Csv_parse(byte * src, int srcSize, byte * field, int fieldCapacity,
        int * nConsumedOutVar, int * lastSeparatorOutVar);

/**
 * serialize single value with following COMMA or CR LF
 * return number of bytes written, or negative as error code
 */
int Csv_serialize(byte * field, int fieldSize, byte * dst, int dstCapacity,
        boolean endsRecord);

#endif // _INCLUDED_CSV
