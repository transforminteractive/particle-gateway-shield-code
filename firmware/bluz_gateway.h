#define SLAVE_PTS_PIN TX
#define MASTER_READY_PIN RX

//Core
#if PLATFORM_ID==0
#define SLAVE_ALERT_PIN 16
#define SLAVE_SELECT A2
#endif

//Photon
#if PLATFORM_ID==6
#define SLAVE_ALERT_PIN 16
#define SLAVE_SELECT A2
#endif

//P1
#if PLATFORM_ID==8
#define SLAVE_ALERT_PIN A0
#define SLAVE_SELECT DAC
#endif

//Electron
#if PLATFORM_ID==10
#define SLAVE_ALERT_PIN 16
#define SLAVE_SELECT A2
#endif

#define CLOUD_DOMAIN "device.spark.io"
// #define CLOUD_DOMAIN "10.1.10.175"
#define RX_BUFFER 1024
#define TX_BUFFER RX_BUFFER
#undef TCPCLIENT_BUF_MAX_SIZE
#define TCPCLIENT_BUF_MAX_SIZE TX_BUFFER
#define MAX_CLIENTS 4
#define SPI_HEADER_SIZE 3
#define BLE_HEADER_SIZE 2

#define NRF51_SPI_BUFFER_SIZE 255

#include "application.h"

/**@brief Gateway Protocol states. */
typedef enum
{
    SOCKET_DATA_SERVICE=1,
    INFO_DATA_SERVICE,
    RESERVED_DATA_SERVICE,
    CUSTOM_DATA_SERVICE
} gateway_service_ids_t;

typedef enum
{
    SOCKET_DATA,
    SOCKET_CONNECT,
    SOCKET_DISCONNECT
} gateway_socket_function_t;

typedef struct
{
    TCPClient socket;
    bool connected = false;
} client_t;

class bluz_gateway {
    
    public:
        bluz_gateway();
        void init();
        void registerDataCallback(void (*data_callback)(uint8_t *data, uint16_t length));
        void loop();
        
    private:
        void parseID(char *destination, uint8_t *buffer);
        char hexToAscii(uint8_t byte);
        void requestID();
        void handle_custom_data(uint8_t *data, int length);
        void debugPrint(String msg);
        void spi_data_process(uint8_t *buffer, uint16_t length, uint8_t clientId);
        void spi_retreive();
        void spi_send(uint8_t *buf, int len);
        
        client_t m_clients[MAX_CLIENTS];
        String gatewayID = "No gateway detected yet.";
        int timeGatewayConnected;
        bool gatewayIDDiscovered;
};
