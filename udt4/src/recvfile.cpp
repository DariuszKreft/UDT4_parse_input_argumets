#ifndef WIN32
   #include <arpa/inet.h>
   #include <netdb.h>
#else
   #include <winsock2.h>
   #include <ws2tcpip.h>
#endif
#include "parser.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <udt.h>


using namespace std;

int main(int argc, char* argv[])
{
   udt_parser* parser = new udt_parser;
   udt_test* test = new udt_test; 

   // use this function to initialize the UDT library
   UDT::startup();

   struct addrinfo hints, *peer;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_flags = AI_PASSIVE;
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   parser->udt_parse_arguments(argc, argv, NULL, test);
   UDTSOCKET fhandle = UDT::socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
   
   parser->udt_parse_arguments(argc, argv, fhandle, test);
   if (0 != getaddrinfo(test->server_ip.c_str(), test->server_port.c_str(), &hints, &peer))
   {
      cout << "incorrect server/peer address. " << test->server_ip << ":" << test->server_port << endl;
      return -1;
   }

   // connect to the server, implict bind
   if (UDT::ERROR == UDT::connect(fhandle, peer->ai_addr, peer->ai_addrlen))
   {
      cout << "connect: " << UDT::getlasterror().getErrorMessage() << endl;
      return -1;
   }

   freeaddrinfo(peer);


   // send name information of the requested file
   int len = strlen(test->local_file.c_str());

   if (UDT::ERROR == UDT::send(fhandle, (char*)&len, sizeof(int), 0))
   {
      cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
      return -1;
   }

   if (UDT::ERROR == UDT::send(fhandle, test->local_file.c_str(), len, 0))
   {
      cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
      return -1;
   }

   // get size information
   int64_t size;

   if (UDT::ERROR == UDT::recv(fhandle, (char*)&size, sizeof(int64_t), 0))
   {
      cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
      return -1;
   }

   if (size < 0)
   {
      cout << "no such file " << test->local_file << " on the server\n";
      return -1;
   }

   // receive the file
   fstream ofs(test->remote_file.c_str(), ios::out | ios::binary | ios::trunc);
   int64_t recvsize; 
   int64_t offset = 0;

   if (UDT::ERROR == (recvsize = UDT::recvfile(fhandle, ofs, offset, size)))
   {
      cout << "recvfile: " << UDT::getlasterror().getErrorMessage() << endl;
      return -1;
   }

   UDT::close(fhandle);

   ofs.close();

   // use this function to release the UDT library
   UDT::cleanup();

   return 0;
}