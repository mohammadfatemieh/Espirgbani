#ifndef WIFI_STARTUP_H
#define WIFI_STARTUP_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "libesphttpd/esp.h"
#include "libesphttpd/httpd.h"
#include "cJSON.h"
#include "lwip/inet.h"

#define N_WIFI_TRYS		6
#define N_HOSPOT_LOOPS  50
#define WIFI_DELAY		10000	//[ms]
#define DNS_TIMEOUT 	10000 	//[ms]

#define GET_HOSTNAME() jGetS(getSettings(), "hostname", "espirgbani")

#define CONNECTED_BIT 	BIT0
#define STA_START_BIT	BIT1

typedef enum {
    WIFI_CON_TO_AP_MODE,
    WIFI_CONNECTED,
    WIFI_START_HOTSPOT_MODE,
    WIFI_HOTSPOT_RUNNING,
    WIFI_OFF_MODE,
    WIFI_IDLE
}wifiState_t;

extern EventGroupHandle_t wifi_event_group;
extern wifiState_t wifiState;

extern void wifi_conn_init(void);
extern void wifi_disable();

// The webserver callbakc
CgiStatus cgiReloadSettings(HttpdConnData *connData);

// Resolve a hostname
ip4_addr_t dnsResolve(const char *dnsRequestBuffer);

// Ping a host. Blocks. Returns 1 on success.
uint32_t isPingOk(ip4_addr_t *ip, uint32_t timeout_ms);

void setLogLevel(char c);

#endif
