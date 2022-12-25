const char * E_INVALID_ARGUMENT = "E: invalid argument";
const char * E_OUT_OF_MEMORY = "E: out of memory";

void log2file(const char * category, const char * message,
        const char * filepath, const int fileline, FILE * fp) {
    int len = (category != NULL) ? fprintf(fp, "%s", category) : 0;
    if (len < 8) {
        fputc('\t', fp);
    }
    fprintf(fp, "\t%s:%d\t%s\n", filepath, fileline, message);
}
