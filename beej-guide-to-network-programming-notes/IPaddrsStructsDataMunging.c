#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



// IPv4 loopback address
// 127.0.0.1

// IPv6 loopback address
// ::1 

// Port number is a 16 bit number thats 
// like the local address for the connection

// Host Byte Order Vs Network Byte Order
/*
Network Byte
storing two sequential bytes with the big 
end first is called Big-Endian

Host Byte
computer stores numbers in host byte order

Conversions
can convert short(two bytes) and long(4 bytes)


*/


// Structs
/*
a socket descriptor is of type int

struct addrinfo
used for host name lookups and service name lookups (DNS)

struct sockaddr 
holds socket address information for many types of sockets


struct sockaddr_in
in = Internet to be used with IPv4
IMPORTANT: a pointer to a struct sockaddr_in can be cast
to apointer a struct sockaddr and vice-versa
makes it easy to reference elements of the socket address


struct sockaddr_storage
designed to be large enough to hold both IPv4 and IPv6 structures

*/

// pton
/*

stands for presentation to network
inet_pton() - converts an IP address in numbers-and-dots
notation into either a struct in_addr or a struct in6_addr


*/

struct addrinfo {
    int ai_flags; // AI_PASSIVE, AI_CANONNAME,etc.
    int ai_family; // AF_INET, AF_INET6, AF_UNSPEC
    int ai_socktype; // SOCK_STREAM, SOCK_DGRAM
    int ai_protocol; // use 0 for "any"
    size_t ai_addrlen; // size of ai_addr in bytes
    struct sockaddr *ai_addr; // struct sockaddr_in or _in6
    char *ai_canonname; // full canonical hostname

    struct addrinfo *ai_next; // linked list, next node
};


struct sockaddr{
    unsigned short sa_family; // address family, AF_xxx
    char sa_data[14]; // 14 bytes of protocol address
};

struct sockaddr_in{
    short int sin_family; // Address family, AF_INET
    unsigned short int sin_port; // Port number
    struct in_addr sin_addr; // Internet address
    unsigned char sin_zero[8]; // Same size as struct sockaddr
};

struct in_addr{
    uint32_t s_addr; // that's a 32-bit int (4 bytes)
};

struct sockaddr_in6{
    u_int16_t sin6_family; // Address family, AF_INET6
    u_int16_t  sin6_port; // Port, Network Byte Order
    u_int32_t sin6_flowinfo; // IPv6 flow information
    struct in6_addr sin6_addr; // IPv6 address
    u_int32_t sin6_scope_id; // Scope ID
};

struct in6_addr{
    uint32_t s6_addr[16]; // that's a 32-bit int (4 bytes)
};

struct sockaddr_storage {
    sa_family_t ss_family;

    char __ss_pad1[_SS_PAD1SIZE];
    int64_t __ss_align;
    char __ss_pad2[_SS_PAD2SIZE];
};

struct sockaddr_in sa;



int main(void){
    
inet_pton(AF_INET, "10.10.10.1", &(sa.sin_addr));
    
}