#include "secrets.h"
#include <pgmspace.h>

const char* THINGNAME = "RackEm-MC-test2";
const char* WIFI_SSID = "[Your SSID Here]";
const char* WIFI_PASSWORD = "[Your Password Here]";
const char* AWS_IOT_ENDPOINT = "[Your AWS IoT Endpoint Here]";

// Root CA 1
const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
****************************************************************
-----END CERTIFICATE-----
)EOF";

// Device Certificate
const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
****************************************************************
-----END CERTIFICATE-----
)KEY";

// Device Private Key
const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
****************************************************************
-----END RSA PRIVATE KEY-----
)KEY";
