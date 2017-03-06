#ifndef INITHEAD_H
#define INITHEAD_H



void inithead_entry();
void write_shellfile();
void write_kernelfile();
void write_realintsvefile();
fhdsc_t* find_file(char_t* fname);
void write_ldrkrlfile();
void error(char_t* estr);
int strcmpl(const char *a,const char *b);
#endif // INITHEAD_H
