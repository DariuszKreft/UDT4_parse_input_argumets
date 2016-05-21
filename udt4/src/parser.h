#ifndef udt_parser_H
#define udt_parser_H

#include "msg.h"
#include "udt.h"
#include "cc.h"
#include <getopt.h>
#include <string>

using namespace std;

extern char usage_longstr[];

struct udt_test
{	
	string server_port;	
	string server_ip;
	string remote_file;
	string local_file;	
	int ai_socktype;
};

class udt_parser
{
	public:
	udt_parser();	
	int udt_parse_arguments(int argc, char* argv[], UDTSOCKET serv, udt_test* test);
	void usage_longopt();
	int arg_is_correct(char* optarg);
	void show_statistics(UDTSOCKET fhandle, UDT::TRACEINFO trace);
};

#endif