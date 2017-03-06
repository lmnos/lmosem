/****************************************************************
*		8254时钟控制器源文件8254.c			*
*****************************************************************
*				彭东 ＠ 2011.12.19.10.40	*
****************************************************************/

//#include "types.h"
//#include "mcontrol.h"

#include "lmosemtypes.h"
#include "lmosemmctrl.h"

PUBLIC LKINIT void  init_8254()
{
	
	out_u8_p(PTIPROTM,TIMEMODE);

	
	out_u8_p(PTIPROT1,HZLL);
	
	out_u8_p(PTIPROT1,HZHH);	
	
	
	return;
}
