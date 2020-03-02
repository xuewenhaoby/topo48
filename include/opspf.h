#define COMMON_IPHDR_LEN 5
#define IP_VERSION 4
#define DEFAULT_OPSPF_TOS 0xc0
#define DEFAULT_OPSPF_TTL 1

#ifndef  IPPROTO_OPSPF
#define  IPPROTO_OPSPF 200
#endif
#define  OPSPF_VERSION 2

#define OPSPF_HELLO_INTERVAL 1
#define OPSPF_PORT_TTL 4

// #define SINF_NUM 128
// #define SAT_NUM 48
#define MaxInterfaceNum 6

#define BUF_STR_SIZE 100
#define PCKT_LEN 1500

enum OpspfPacketType
{
    OPSPF_HELLO_PACKET =1,
    OPSPF_LSU_PACKET   =2
};

enum OpspfPortStatusType
{
    OPSPF_PORT_ALIVE =0,
    OPSPF_PORT_UNREACHABLE =1,
    OPSPF_PORT_DOWN =2
};

enum OpspfPortChangeStatType
{
    OPSPF_PORT_LINKDOWN =0,
    OPSPF_PORT_RELINK =1,
    OPSPF_PORT_NOCHANGE =2
};

typedef struct OpspfInterfaceData
{
    int type;
    in_addr_t ip;
    in_addr_t netmask;
    int sock;
    int ttl;
    int satelliteId;
    int portId;
    OpspfPortChangeStatType changeStat;
    OpspfPortStatusType status;
    int if_index;
    unsigned char if_mac[6];
}OpspfInfData;


typedef struct _opspfhdr
{
    OpspfPacketType packetType;
    u_int16_t pktlen;
    int dst_addr;

}OPSPF_Header;

typedef struct opspf_hello_info
{
    int satelliteId;
    int portId;
}OpspfHelloInfo;

typedef struct opspf_lsu_info
{
    int srcSatelliteId;
    int srcPortId;
    int dstSatelliteId;
    int dstPortId;
}OpspfLsuInfo;

unsigned short csum(unsigned short *buf, int nwords);
void network_init();

OpspfInfData interface_init(int satelliteId,int portId);

void OpspfSendProtocolPacket(OpspfInfData inf,OpspfPacketType packetType,in_addr_t dstAddr);
void recv_opspf();
void *recv_opspf(void *ptr);
void *encapsulate_and_send_opspf(void *ptr);
void analyseIP(struct iphdr *ip);
void analyseOPSPF(OPSPF_Header* opspfhdr);

void Opspf_Handle_LsuPacket(const OpspfLsuInfo* lsuInfo);

void Opspf_Handle_HelloPacket(const OpspfHelloInfo* helloInfo);