#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32_FLAME_SENSOR"                         //change this
 
const char WIFI_SSID[] = "Clauro";               //change this
const char WIFI_PASSWORD[] = "bebaagua";           //change this
const char AWS_IOT_ENDPOINT[] = "a1bak7jtiod9kj-ats.iot.us-east-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAI+57n7itwtJ9bzyLyBE52dAj6n5MA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA0MjcyMDE2
NDBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC68oPKfcihjYXOHtZw
GRSGnljB9E0o/OKqkwJrI69Sr02r2EACR6K90bT40mFVEFPjwIx6j/PRL4ObP4st
+CbiiDhvB3u/Z5PD+tGMUWq/6wOWI/+ofx0FUnyb2/UPvw6+tkGEm6d04ymHeXyQ
hIKPOjHSVouhycUUTsekS8JmVlceTSC+kSsKUC3i6ooiSxVsgy//GqndeOn/LTK6
kaQ8OWGhelKrjxGIWn4YLyuOu6QeshdGDulktbWaCYaP5i8Br5zKfiSdR9xRJ/N1
9/5B0pTMXrAp5hMkCQzBoPUT0fHA62cLXqSCRHHhcOcAYnQFwEMDSoMWCxqs1x3c
zFFFAgMBAAGjYDBeMB8GA1UdIwQYMBaAFGDt3vLRIRJiUffZJf+YEl5C1Jn0MB0G
A1UdDgQWBBSq5MHv4Gw5A6Y9h2YECQkivvuC+DAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAigH9MaLud6FYs2MStNIlq7EY
rez9Xjq68owmkbUxb9lI5HsE9Jss1YrcWXlDwlegxnKs0DGVdTfznIsgMaDpoax4
/L1TDxsbSURIxkbPcnnOMannMy+F1LfvDzolXSVgOYf6CCHb86WQG0+FxN6TP7gD
yMXl/TTAGKicw79WY/rguynh1ynwr68g7gej3ngQsMrcSPQTX4tukHdYcwc/OsKX
fkuiqfJkIPg85YSDOm5ZL6TJds+yvPZNkm+g1RDHMyFMl8b0H7vFWfaP/CCwXg/q
NVEK28zt1GuxMu+A5PbdWhoIH2JVhiRDuFKFqiFQBjqyqc9stt2dX/fkFoNXbw==
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAuvKDyn3IoY2Fzh7WcBkUhp5YwfRNKPziqpMCayOvUq9Nq9hA
AkeivdG0+NJhVRBT48CMeo/z0S+Dmz+LLfgm4og4bwd7v2eTw/rRjFFqv+sDliP/
qH8dBVJ8m9v1D78OvrZBhJundOMph3l8kISCjzox0laLocnFFE7HpEvCZlZXHk0g
vpErClAt4uqKIksVbIMv/xqp3Xjp/y0yupGkPDlhoXpSq48RiFp+GC8rjrukHrIX
Rg7pZLW1mgmGj+YvAa+cyn4knUfcUSfzdff+QdKUzF6wKeYTJAkMwaD1E9HxwOtn
C16kgkRx4XDnAGJ0BcBDA0qDFgsarNcd3MxRRQIDAQABAoIBABRZndsHAjYDz9L2
LGWbdU6KIiNK0rNpg8sJobPD+KvJhWz1Z1JYNfDvyQFk9U9rLZaXOTOGRAY7Y9oc
eqwQXTs/lNURPXlCbyVgQjtCCZrGnGdVl9jhrWkM55+Xu/9wzswXzt3+i6X/rF+g
69xXcFbjANVismR0ME3bnYPW81xsTdf+gvhw4aNlu61bD9qem6vmmWBvlCuwQ4eI
w7kXQpm8hECwA+Iug/2y5AWn8wdX521sLKHxHDZSfqvE9goaH7ah0bYFpnNEqidC
Wt8xvYaEtevow+/Z2kzzW1xPoW22n4pm9cuRUVRaLiwk82GcIaXskNivIEtrNyvs
k+lEfAECgYEA7dlCAwybYLQVvYWNL4SqMFP/WQ+ta/XhUTUyFvabw8S1nBMzQZ9u
2UsM5lkYrA4XM20JFmVMriaS428DQ+/bYwinEIETOFSunfTqp8X8OvamapbcH6SA
k7puNhHy8hau7vxnrGop2QD9TM2LwRE03KXlXsbZOeGQ9Q9G+59QPsUCgYEAyTbS
Bmhm95zxe6pGRdBsovpvH9C/QIO+9E08X4VFVg97O0kVKqlt3hcEwdrvbmAGl7BP
k8jwzdC8FXpXpzUHW8VOAhC+OtZyJnbGlcTrA83/uV2tDqs57bFQeYrBQU7O2kDM
7SLaVXTzg992pBWFLRUixsQWP2zC+KWukdi08IECgYEA4DxFSc6m5gKhxG2Wb8gp
Eyr9v59SJkhHRmJaeN/CdkyL0zsexa1juiRRYxF4ey1FnkwblyuloUHoldbhQzls
oe9UYfDuh9r+TRjL6aR0abqDplXX7VUPizbmFL/TRX0xK0p3C0uDbHzMUY4vRbPN
HICiwDnELheErCTdDPhjlOkCgYB54d0iyIbmooicUi4zB+dmabB6YyYWXDeFIGvb
qIyxbrtE1CYgK3VDvEnDa2zxPPWBWOk7KdLDuRbVI8CIplSIwGFaWu4AEfofVn9A
JYH+Uf//NsEnS4zRcEDA/s3FU4l1Jx963UvHzAnd7bSd+/Mptc3U/N5FGQqZNzMh
YVVpAQKBgHe8wGl0mLejHaAQu0Fb/s9jM6tyP70YWn8jprS3B1cXRJFY2F4Hjqwd
89LE7Mpk6eU0TO3gtgfurlU9lv2eo15llIyfaS/p6Wk64Vg7ZzauGXAA1aV4ZuTT
HfwVOshPMZqj4/w/SjjQkF0x1A02uFcXXcwv17mJe10++eS0bKVJ
-----END RSA PRIVATE KEY-----

 
 
)KEY";