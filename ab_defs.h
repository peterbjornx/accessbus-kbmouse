
typedef struct {
  char opcode;
  char prot_rev;
  char mod_rev[7];
  char vendor_name[8];
  char module_name[8];
  uint32_t dev_id;
} ident_rply;

typedef struct {
  char opcode;
  char prot_rev;
  char mod_rev[7];
  char vendor_name[8];
  char module_name[8];
  uint32_t dev_id;
  char new_Addr;
} assign_addr;

typedef struct {
  char opcode;
  uint16_t offset;
} cap_req;

typedef struct {
  char opcode;
  uint16_t offset;
  uint8_t data[32];
} cap_rply;

