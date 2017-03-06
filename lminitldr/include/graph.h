#ifndef _GRAPH_H
#define _GRAPH_H


void init_graph(machbstart_t* mbsp);
void graph_t_init(graph_t* initp);
u32_t vfartolineadr(u32_t vfar);
void init_kinitfvram(machbstart_t* mbsp);
void get_vbemode(machbstart_t* mbsp);
void get_vbemodeinfo(machbstart_t* mbsp);
void set_vbemodeinfo();
void bga_write_reg(u16_t index, u16_t data);
u16_t bga_read_reg(u16_t index);
u32_t get_bgadevice();
u32_t chk_bgamaxver();
void init_bgadevice(machbstart_t* mbsp);
u32_t utf8_to_unicode(utf8_t* utfp,int* retuib);
/*kprint("vbe vbestuc:%s\n",(char*)vbeinfoptr->vbesignature);
 kprint("vbe vbever:%x\n",vbeinfoptr->vbeversion);
 kprint("vbe oemstrptr:%s\n",vbeinfoptr->oemstringptr);
 kprint("vbe capabili:%x\n",vbeinfoptr->capabilities);
 kprint("vbe voidmptr:%x\n",vbeinfoptr->videomodeptr);
 kprint("vbe totamm:%x\n",vbeinfoptr->totalmemory);
 kprint("vbe oemsoftver:%x\n",vbeinfoptr->oemsoftwarerev);
 kprint("vbe oemven:%x\n",vbeinfoptr->oemvendornameptr);
 kprint("vbe oempronm:%x\n",vbeinfoptr->oemproductnameptr);
 kprint("vbe oemprove:%x\n",vbeinfoptr->oemproductrevptr);

    pixcl_t cl[3];
    cl[0].cl_r=0xff;
    cl[0].cl_g=0;
    cl[0].cl_b=0;
    cl[1].cl_r=0;
    cl[1].cl_g=0xff;
    cl[1].cl_b=0;
    cl[2].cl_r=0;
    cl[2].cl_g=0;
    cl[2].cl_b=0xff;
    int xy=0;

    for(int c=0;c<3;c++)
    {
        for(int i=0;i<(x*y);i++)
        {
            phybass[i]=*((u32_t*)(&cl[c]));
        }
        die(0x300);
    }

    for(int xj=0;xj<(1024*768);xj++)
    {
        phybass[xj]=xj;
    }
    for(;;);

*/

#endif
