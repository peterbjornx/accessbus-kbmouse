#include <Wire.h>


int hndl = 0;

char lcl_Addr = 0x6E;
char src_Addr;
int  pkt_P;
int  pkt_Len;
char pkt_Buf[128];

#include "ab_util.h"
#include "ab_defs.h"
#include "ab_llio.h"
#include "ab_send.h"
#include "ab_recv.h"