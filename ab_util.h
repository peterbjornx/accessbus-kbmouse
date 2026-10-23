
uint16_t htons(uint16_t a) {
  uint16_t b;
  b = ( a >> 8 );
  b |= ( a & 0xFF ) << 8;
  return b;
}

uint16_t ntohs(uint16_t a) {
  return htons(a);
}

char calcXsum( const char *pkt, int len ) {
  char v = 0;
  for ( int i = 0; i < len; i++ )
    v ^= pkt[i];
  return v;
}