#include <pebble.h>

void appmsg_init(void);
void appmsg_deinit(void);


enum APPMSGKEYS {
  APPMSGKEY_MSGTYPE = 0,
  APPMSGKEY_LINENAME,
  APPMSGKEY_LINESTATUS,
  APPMSGKEY_STATUS
};

enum APPMSGTYPE {
  APPMSGTYPE_REFRESH = 0,
  APPMSGTYPE_STATUS,
  APPMSGTYPE_LINESTATUS
};
