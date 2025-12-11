// What is a Socket?

/*
You make a call to the socket() system routine.
It returns the socket descriptor, and you communicate through it
using the specialized send() and recv() 
(man send, man recv) socket calls.

*/

// Two types of Internet Sockets


// Stream Sockets
/*
SOCK_STREAM 
are relable two-way connected communication streams
arrive in order and error-free

examples of services that use stream sockets:
telnet
ssh
https

Uses the protocol TCP (Transmission Control Protocol)
makes sure your data arrives sequentially and error-free

must maintain an open connection

*/





// Datagram Sockets

/*

SOCK_DGRAM
sometimes referred to as connectionless sockets
can be connect()'d 

unreliable 
it may arrive, it may arrive out of order
if it arrives the data within the packet will be error-free

uses UDP (User Datagram Protocol)

dont have to maintain an open connection <- no connection needed

examples of services that use UDP <- have their own protocol ontop of UDP
tftp
dhcpcd


ACK 
acknowledgement procedure is very important when implementing
reliable SOCK_DGRAM


know for speed

*/

// Data Encapsulation

/*
Stream Sockets

all you have to do for stream sockets is send() the data out


Datagram Sockets

All you have to do for datagram sockets is encapsulate the packet in
the method of your choosing and sendto() it out

*/