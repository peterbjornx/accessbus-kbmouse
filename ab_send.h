void sendIdentification( char dst ) {
  ident_rply rply;
  rply.opcode      = 0xE1;
  rply.prot_rev    = 'B';
  memcpy(rply.mod_rev,      dev_Ver, 7);
  memcpy(rply.vendor_name,  vnd_Name, 8);
  memcpy(rply.module_name,  dev_Name, 8);
  rply.dev_id      = dev_Id; 
  AB_SendPacket( dst, sizeof rply, 1, (const void *) &rply );
}
#define capmax 24
void sendCapabilitiesReply( char dst, int offset ) {
  cap_rply rply;
  int size = 32;
  size = strlen(cap_String) - offset;
  if ( size < 0 )
    size = 0;
  if ( size > capmax )
    size = capmax;
  rply.opcode = 0xE3;
  rply.offset = htons(offset);
  memcpy(rply.data,cap_String + offset,size);
  AB_SendPacket( dst, size+3, 1, (const void *) &rply );
}
void sendKeyList( char dst, char *list, int len ) {
  char a[1];
  if ( len == 0 ) {
    a[0] = 0;
    AB_SendPacket( dst, 1, 0, (const void *) a );
  } else
    AB_SendPacket( dst, len, 0, list );
}

void sendKey( char dst, char key ) {
  char keys[2];
  keys[0] = key;
  keys[1] = 0;
  sendKeyList( dst, keys, 1 );
}


void sendLocator( char dst, uint16_t btns, short *list, int len ) {
  char a[1];
  short pkt[8];
  pkt[0] = htons(btns);
  for ( int i = 0; i < len; i++ )
    pkt[i+1] = htons(list[i]);
  AB_SendPacket( dst, len*2 + 2, 0, (void *) pkt );
}
