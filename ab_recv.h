void handleResetReq() {
  Serial.println("Reset request!");
  AB_SetAddress(0x6E);
}

void handleAttnReq() {
  Serial.println("Attention request!");
}

void handleIdentReq() {
  //Serial.println("Identification request!");
  sendIdentification( src_Addr );
}

void handleAssignAddr() {
  assign_addr req;
  memcpy( &req, pkt_Buf, sizeof req );
  
  Serial.println("Assign address!");
  Serial.flush();
  

  if ( req.dev_id != dev_Id )
    goto bad_Id;

  if ( req.prot_rev != 'B' )
    goto bad_Id;
  
  if ( memcmp( req.vendor_name, vnd_Name, 8 ) != 0 )
    goto bad_Id;

  if ( memcmp( req.module_name, dev_Name, 8 ) != 0 )
    goto bad_Id;

  if ( memcmp( req.mod_rev, dev_Ver, 7 ) != 0 )
    goto bad_Id;

  AB_SetAddress( req.new_Addr );

  Serial.print("Got address ");
  Serial.print((int)lcl_Addr);
  Serial.println();
  Serial.flush();
  


  return;
bad_Id:
  Serial.println("Got bad addr set!");
  Serial.flush();
  return;
}


void handleCapRequest() {
  cap_req req;
  memcpy(&req, pkt_Buf, sizeof req);

  req.offset = ntohs(req.offset);
  
  Serial.print("Cap request for ");
  Serial.println((int)req.offset);
  
  sendCapabilitiesReply( src_Addr, req.offset );
}
void handleControlStatus() {
  unsigned char opcode = pkt_Buf[0];
  if ( opcode & 0x80 ) {
    // Pre defined
    switch( opcode ) {
      case 0xF0: 
        handleResetReq();
        return;
      case 0xE0:
        handleAttnReq();
        return;
      case 0xF1: 
        handleIdentReq();
        return;
      case 0xF2: 
        handleAssignAddr();
        return;
      case 0xF3:      
        handleCapRequest();
        return;
      default:
        Serial.print("Unknown protocol req: ");
        Serial.println((int)opcode);
        return;

    }
  } else {
       // Serial.print("Unknown data def'd req: ");
       // Serial.println((int)opcode);
  }
}