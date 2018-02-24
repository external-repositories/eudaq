#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>
#include <string>
#include <vector>

#include <sys/types.h>

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/time.h>
typedef int SOCKET;
#endif


// the port client will be connecting to
#define PORT_CONFIG 49248
#define PORT_DATATRANSF 49250
// max number of bytes we can get at once
#define MAXDATASIZE 300
#define MAXHOSTNAME 80

#define START 0x1254
#define STOP 0x1255

class NiController {

public:
  void GetProducerHostInfo();
  void Start();
  void Stop();
  void DatatransportClientSocket_Open(const std::string& addr, uint16_t port);
  void DatatransportClientSocket_Close();
  bool DataTransportClientSocket_Select();
  unsigned int DataTransportClientSocket_ReadLength();
  std::vector<unsigned char> DataTransportClientSocket_ReadData(int datalength);

  void ConfigClientSocket_Open(const std::string& addr, uint16_t port);
  void ConfigClientSocket_Close();
  bool ConfigClientSocket_Select();
  void ConfigClientSocket_Send(unsigned char *text, size_t len);
  unsigned int ConfigClientSocket_ReadLength();
  std::vector<unsigned char> ConfigClientSocket_ReadData(int datalength);

private:
  struct hostent *hconfig, *hdatatransport;
  struct sockaddr_in config;
  struct sockaddr_in datatransport;
  SOCKET sock_config;
  SOCKET sock_datatransport;

  unsigned char conf_parameters[10];
  char Buffer_data[7000];
  char Buffer_length[7000];
};
