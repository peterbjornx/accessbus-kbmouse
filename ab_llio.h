int AB_Active = 0;

void AB_SetAddress( char addr ) {
  lcl_Addr = addr;
  if ( AB_Active )
    Wire.end();
  AB_Active = 1;
  Wire.begin( lcl_Addr >> 1 );
}

void AB_SendPacket( char dst, int len, int p, const char *pkt )
{
  unsigned char lenB;
  lenB = p << 7 | len;
  /*
  Serial.print("going to send to ");
  Serial.print((int)dst);
  Serial.print("with lb: ");
  Serial.print((unsigned int)len);
  Serial.println();
  Serial.flush();
  */
  uint8_t xsum = calcXsum( pkt, len ) ^ lenB ^ lcl_Addr ^ dst;
  Wire.beginTransmission( dst >> 1 );
  Wire.write( lcl_Addr );
  Wire.write( lenB );
  Wire.write( pkt, len );
  Wire.write( xsum );
  Wire.endTransmission();
  //Serial.println((int)xsum);
}

void receiveEvent(int howMany)
{
  src_Addr = Wire.read();
  char len_P = Wire.read();
  int p_flag = (len_P >> 7)&1;
  pkt_Len = len_P & 0x7F;
  for ( int i = 0; i < pkt_Len; i++ ) {
    pkt_Buf[i] = Wire.read();
  }
  char xsum = Wire.read();
  if ( !p_flag) {
  Serial.print("Packet from ");
  Serial.print((int)src_Addr);
  Serial.print(" with proto ");
  Serial.print((int)p_flag);
  Serial.print(", xsum: ");
  Serial.print((int)xsum);
  Serial.print(", data: ");
  for ( int i = 0; i < pkt_Len; i++ )
    Serial.print((int) pkt_Buf[i]);
  Serial.println();
  }
  //TODO: Verify checksum.
  
  pkt_P = p_flag;
  hndl = 1;

}
void handleControlStatus();

void handle() {
  if ( hndl == 1 ) {
     if( pkt_P )
      handleControlStatus();
     hndl = 0;
  }
}