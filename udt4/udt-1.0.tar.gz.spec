Name:         udt
Version:      4.0
Release:      1%{?dist}
Summary:      UDT4_tool  

Group:        Linux   
License:      BSD License
URL:          https://github.com/DariuszKreft/UDT4_parse_input_argumets/tree/master/udt4  
Source0:      %{name}-%{version}.tar.gz
 


BuildRequires:	gcc  


%description
This document describes UDT, or the UDP based Data Transfer protocol. 
   UDT is designed to be an alternative data transfer protocol for the 
   situations when TCP does not work well. One of the most common cases, 
   and also the original motivation of UDT, is to overcome TCP's 
 
 
Yunhong Gu            Expires - October 12, 2010              [Page 1] 
                                 UDT                   April 12, 2010 
 
 
   inefficiency in high bandwidth-delay product (BDP) networks. Another 
   important target use scenario is to allow networking researchers, 
   students, and application developers to easily implement and deploy 
   new data transfer algorithms and protocols. Furthermore, UDT can also 
   be used to better support firewall traversing. 
    
   UDT is completely built on top of UDP. However, UDT is connection 
   oriented, unicast, and duplex. It supports both reliable data 
   streaming and partial reliable messaging. The congestion control 
   module is an open framework that can be used to implement and/or 
   deploy different control algorithms. UDT also has a native/default 
   control algorithm based on AIMD rate control.

%prep
%setup -q 


%build
make PREFIX=/usr %{?_smp_mflags}

%install
make PREFIX=/usr DESTDIR=%{?buildroot} install

%clean	
rm -rf %{buildroot}

%files
%defattr(-,root,root)
%{_bindir}/sendfile
%{_bindir}/recvfile
%changelog
