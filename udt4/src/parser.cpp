#include <iostream>
#include "parser.h"
#include "udt.h"
#include "msg.h"
#include <cstdlib>
#include <getopt.h>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

udt_parser::udt_parser()
{
}

int udt_parser::udt_parse_arguments(int argc, char* argv[], UDTSOCKET serv, udt_test* test)
{
	int flag;
	int size = sizeof(int);
	int option_value_set = 0;
	int option_value_get = 0;
	static struct option longopts[] =
	{
		{ "server_ip", required_argument, NULL, 's' },            //Server Ip
		{ "server_port", required_argument, NULL, 'p' },          //Server Port
		{ "MTU", required_argument, NULL, 'm' }, 		   		  //Maximum Transfer Unit
		{ "UDT_RCVBUF", required_argument, NULL, 'e' },           //UDT receiving buffer size
		{ "window_size", required_argument, NULL, 'w' },          //Flight flag size (window size)
		{ "UDP_SNDBUF", required_argument, NULL, 'f' },	          //UDP sending buffer size
		{ "UDP_RCVBUF", required_argument, NULL, 't' },	          //UDP receiving buffer size
		{ "UDT_MAXMSG", required_argument, NULL, 'y' },           //Maximum datagram message size
		{ "UDT_SNDBUF", required_argument, NULL, 'o' },           //Maximum buffer in sending queue
		{ "UDT_MAXBW", required_argument, NULL, 'b' },            //Maximum bandwidth (bytes per second) that the connection can use
		{ "UDT_SNDDATA", required_argument, NULL, 'u' },          //Size of data in the sending buffer
	    { "UDT_CC", no_argument, NULL, 'k' },                     //custom congestion control algorithm
		{ "UDT_RCVDATA", required_argument, NULL, 'i' },          //Size of data available for recv
		{ "SOCK_DGRAM", no_argument, NULL, 'd' },
		{ "help", no_argument, NULL, 'h'},
		{ NULL, 0, NULL, 0 }
	};

	while ((flag = getopt_long(argc, argv, "s:p:m:e:w:f:t:y:o:b:u:i:h::l:r:k::d::", longopts, NULL)) != -1)
	{
		switch (flag)
		{
			case 'm':
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				cout << "m:" << option_value_set << endl;
				UDT::setsockopt(serv, 0, UDT_MSS, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDT_MSS, &option_value_get, &size);
				cout << "UDT_MSS set value:" << option_value_get << endl;
			break;
			case 'e':
				cout << "e:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDT_RCVBUF, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDT_RCVBUF, &option_value_get, &size);
				cout << "UDT_RCVBUF set value:" << option_value_get << endl;
			break;
			case 'o':
				cout << "o:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDT_SNDBUF, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDT_SNDBUF, &option_value_get, &size);
				cout << "UDT_SNDBUF set value:" << option_value_get << endl;
			break;
			case 'f':
				cout << "f:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDP_SNDBUF, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDP_SNDBUF, &option_value_get, &size);
				cout << "UDP_SNDBUF set value:" << option_value_get << endl;
			break;
			case 't':
				cout << "t:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDP_RCVBUF, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDP_RCVBUF, &option_value_get, &size);
				cout << "UDP_RCVBUF set value:" << option_value_get << endl;
			break;
			case 'b':				
				cout << "b:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDT_MAXBW, &option_value_set, sizeof(int));					
				UDT::getsockopt(serv, 0, UDT_MAXBW, &option_value_get, &size);
				cout << "UDT_MAXBW set value:" << option_value_get << endl;
			break;
			case 'u':
				cout << "u:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDT_SNDDATA, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDT_SNDDATA, &option_value_get, &size);
				cout << "UDT_SNDDATA set value:" << option_value_get << endl;
			break;
			case 'i':
				cout << "i:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDT_RCVDATA, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDT_RCVDATA, &option_value_get, &size);
				cout << "UDT_RCVDATA set value:" << option_value_get << endl;
			break;
			case 'p':
				cout << "p:" << optarg << endl;
				arg_is_correct(optarg);
				test->server_port = optarg;					
			break;
			case 's':
				cout << "s:" << optarg << endl;
				test->server_ip = optarg;					
			break;
			case 'r':
				cout << "r:" << optarg << endl;
				test->remote_file = optarg;					
			break;
			case 'l':
				cout << "l:" << optarg << endl;
				test->local_file = optarg;					
			break;
			case 'w':
				cout << "w:" << optarg << endl;
				arg_is_correct(optarg);
				option_value_set = atoi(optarg);
				UDT::setsockopt(serv, 0, UDT_FC, &option_value_set, sizeof(int));
				UDT::getsockopt(serv, 0, UDT_FC, &option_value_get, &size);
				cout << "UDT_FC set value:" << option_value_get << endl;
			break;		
			case 'k':
				cout << "k" << endl;			
				UDT::setsockopt(serv, 0, UDT_CC, new CCCFactory<CUDPBlast>, sizeof(CCCFactory<CUDPBlast>));
			break;
				case 'd':
				cout << "d:" << SOCK_DGRAM <<endl;
				test->ai_socktype = SOCK_DGRAM;				
			break;
			case 'h':
			cout << "h:" << endl;
				usage_longopt();
				exit(1);
			break;		
		   	case '?':				
				usage_longopt();
				exit(1);
			break;
		}		
	}
	return 0;
}

void udt_parser::usage_longopt()
{
	cout << usage_longstr << endl;
}

int udt_parser::arg_is_correct(char* optarg)
{
	if(0 == (atoi(optarg)))
	{
		cout << "Wrong parameter:" << optarg << endl;
		usage_longopt();
		exit(1);
	}
	
	return 0;
}

void udt_parser::show_statistics(UDTSOCKET fhandle, UDT::TRACEINFO trace)
{
   int block;
   int size_block = sizeof(int);
   
   cout << "---------------------UDT parameters after performance---------------------\n";
   UDT::getsockopt(fhandle, 0, UDT_MSS, &block, &size_block);
   cout << "(m)-> UDT_MSS get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDT_MAXBW, &block, &size_block);
   cout << "(b)-> UDT_MAXBW get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDT_RCVBUF, &block, &size_block);
   cout << "(e)-> UDT_RCVBUF get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDT_SNDBUF, &block, &size_block);
   cout << "(o)-> UDT_RCVBUF get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDP_SNDBUF, &block, &size_block);
   cout << "(f)-> UDP_SNDBUF get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDP_RCVBUF, &block, &size_block);
   cout << "(t)-> UDP_RCVBUF get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDT_SNDDATA, &block, &size_block);
   cout << "(u)-> UDT_SNDDATA get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDT_RCVDATA, &block, &size_block);
   cout << "(i)-> UDT_RCVDATA get value:" << block << endl;
   
   UDT::getsockopt(fhandle, 0, UDT_FC, &block, &size_block);
   cout << "(w)-> UDT_FC get value:" << block << endl;
   
   cout << "\n---------------------Performance global statistic---------------------\n";
   cout << "Total number of sent data packets, including retransmissions = " << trace.pktSentTotal << endl;
   cout << "Total number of received packets = " << trace.pktRecvTotal << endl;
   cout << "Total number of lost packets (sender side) = " << trace.pktSndLossTotal << endl;
   cout << "Total number of lost packets (receiver side) = \n" << trace.pktRcvLossTotal << endl;   
   
   cout << "---------------------Performance local statistic---------------------\n";
   cout << "Sending rate speed = " << trace.mbpsSendRate << "Mbits/sec" << endl;
   cout << "Number of sent data packets, including retransmissions = " << trace.pktSent << endl;
   cout << "Number of lost packets (sender side) = " << trace.pktSndLoss << endl;						   
} 