#include <pebble.h>

void appmsg_init(void);
void appmsg_deinit(void);
void appmsg_refreshstatus(void);

enum APPMSGKEYS {
  APPMSGKEY_MSGTYPE = 0,
  APPMSGKEY_LINENAME,
  APPMSGKEY_LINESTATUS,
  APPMSGKEY_STATUS,
  APPMSGKEY_NUMLINES,
};

enum APPMSGTYPE {
  APPMSGTYPE_REFRESH = 0,
  APPMSGTYPE_STATUS,
  APPMSGTYPE_LINESTATUS,
  APPMSGTYPE_PKJSREADY
};

