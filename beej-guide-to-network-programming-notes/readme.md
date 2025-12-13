# 📡 Beej's Guide to Network Programming - Notes & Labs

![Focus](https://img.shields.io/badge/Focus-Network%20Programming-blue?style=for-the-badge)
![Topic](https://img.shields.io/badge/Topic-Sockets%20%26%20Protocols-red?style=for-the-badge)

This directory contains my code labs, exercises, and study notes from following **[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/)**. Building on C fundamentals, this section focuses on how to communicate over networks at the socket level.

> **🎯 Learning Goal:** Master low-level network programming to build custom **Command & Control (C2) implants**, reverse shells, and network reconnaissance tools. Understanding sockets is fundamental to Red Team operations.

## 🧪 Code Labs

| Exercise | Description | Status |
|:---|:---|:---|
| **[`sockets.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-network-programming-notes/sockets.c)** | Socket fundamentals: SOCK_STREAM vs SOCK_DGRAM, TCP vs UDP concepts. | ✅ Completed |
| **[`IPaddrsStructsDataMunging.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-network-programming-notes/IPaddrsStructsDataMunging.c)** | IP addresses, socket structs, byte order, and `inet_pton()`. | 🟡 In Progress |

---

## 📝 Study Notes

### 🔌 What is a Socket?
A socket is a way to communicate with other programs using standard Unix file descriptors. You make a call to the `socket()` system routine, which returns a **socket descriptor**. You then communicate through it using specialized `send()` and `recv()` calls.

> **🕵️‍♂️ Red Team Note:**
> Sockets are the foundation of all network-based implants. Every reverse shell, C2 beacon, and data exfiltration tool uses sockets under the hood. Understanding raw socket programming lets you build custom protocols that evade signature-based detection.

---

### 🌊 Stream Sockets (`SOCK_STREAM`)
Reliable, two-way, connection-oriented communication.

| Property | Description |
|:---|:---|
| **Protocol** | TCP (Transmission Control Protocol) |
| **Reliability** | Data arrives in order, error-free |
| **Connection** | Must maintain an open connection |

#### Services That Use Stream Sockets
*   Telnet
*   SSH
*   HTTPS

> **🕵️‍♂️ Red Team Note:**
> *   **Reverse Shells**: Most reverse shells use TCP (`SOCK_STREAM`) because you need reliable, ordered communication for interactive sessions.
> *   **C2 Over HTTPS**: Wrapping your C2 traffic in TLS over TCP lets you blend in with legitimate web traffic—one of the most effective evasion techniques.

---

### 📨 Datagram Sockets (`SOCK_DGRAM`)
Fast, connectionless, "fire and forget" communication. Sometimes called "connectionless sockets" (though they can be `connect()`'d if desired).

| Property | Description |
|:---|:---|
| **Protocol** | UDP (User Datagram Protocol) |
| **Reliability** | Unreliable—packets may arrive out of order or not at all |
| **Data Integrity** | If it arrives, the data within the packet will be error-free |
| **Connection** | No connection needed |
| **Speed** | Known for speed |

#### Services That Use Datagram Sockets
These have their own protocol on top of UDP:
*   TFTP
*   DHCPCD

#### ACK (Acknowledgement)
When implementing reliable `SOCK_DGRAM` communication, the acknowledgement procedure is very important.

> **🕵️‍♂️ Red Team Note:**
> *   **DNS Tunneling**: UDP port 53 is almost always allowed through firewalls. Encoding C2 commands in DNS queries is a classic exfiltration technique.
> *   **UDP Scanning**: `SOCK_DGRAM` is used for UDP port scanning. Send a packet, no response = open|filtered, ICMP unreachable = closed.
> *   **Speed**: When you need to spray packets quickly (port scanning, DoS), UDP's lack of handshake overhead is advantageous.

---

### 📦 Data Encapsulation

#### Stream Sockets
All you have to do is `send()` the data out—TCP handles the rest.

#### Datagram Sockets
Encapsulate the packet in the method of your choosing and `sendto()` it out.

> **🕵️‍♂️ Red Team Note:**
> Understanding encapsulation lets you design custom C2 protocols. You control what goes in the application layer—use it for encryption, compression, or mimicking legitimate traffic.

---

### 🌐 IP Addresses & Loopback

#### Loopback Addresses
| Version | Address | Description |
|:---|:---|:---|
| IPv4 | `127.0.0.1` | Localhost |
| IPv6 | `::1` | Localhost |

#### Port Numbers
A port number is a **16-bit number** that acts like a local address for the connection. It identifies which application/service should receive the data.

---

### 🔄 Byte Order: Host vs Network

| Type | Description |
|:---|:---|
| **Network Byte Order** | Big-Endian—stores the "big end" (most significant byte) first. This is the standard for network protocols. |
| **Host Byte Order** | Whatever your computer uses internally (often Little-Endian on x86). |

#### Conversion Functions
You can convert `short` (2 bytes) and `long` (4 bytes) between host and network order:

| Function | Description |
|:---|:---|
| `htons()` | Host to Network Short |
| `htonl()` | Host to Network Long |
| `ntohs()` | Network to Host Short |
| `ntohl()` | Network to Host Long |

> **🕵️‍♂️ Red Team Note:**
> Forgetting byte order conversion is a classic bug. Your implant connects to the wrong port, packets get malformed, and you waste hours debugging. Always use `htons()` for ports!

---

### 🏗️ Socket Structs

A socket descriptor is of type `int`.

#### `struct addrinfo`
Used for host name lookups and service name lookups (DNS).
```c
struct addrinfo {
    int ai_flags;             // AI_PASSIVE, AI_CANONNAME, etc.
    int ai_family;            // AF_INET, AF_INET6, AF_UNSPEC
    int ai_socktype;          // SOCK_STREAM, SOCK_DGRAM
    int ai_protocol;          // use 0 for "any"
    size_t ai_addrlen;        // size of ai_addr in bytes
    struct sockaddr *ai_addr; // struct sockaddr_in or _in6
    char *ai_canonname;       // full canonical hostname
    struct addrinfo *ai_next; // linked list, next node
};
```

#### `struct sockaddr`
Generic struct that holds socket address information for many types of sockets.
```c
struct sockaddr {
    unsigned short sa_family; // address family, AF_xxx
    char sa_data[14];         // 14 bytes of protocol address
};
```

#### `struct sockaddr_in` (IPv4)
**Important:** A pointer to `struct sockaddr_in` can be cast to a pointer to `struct sockaddr` and vice-versa. This makes it easy to reference elements of the socket address.
```c
struct sockaddr_in {
    short int sin_family;         // Address family, AF_INET
    unsigned short int sin_port;  // Port number
    struct in_addr sin_addr;      // Internet address
    unsigned char sin_zero[8];    // Padding—same size as struct sockaddr
};

struct in_addr {
    uint32_t s_addr;  // 32-bit int (4 bytes)
};
```

#### `struct sockaddr_in6` (IPv6)
```c
struct sockaddr_in6 {
    u_int16_t sin6_family;     // AF_INET6
    u_int16_t sin6_port;       // Port, Network Byte Order
    u_int32_t sin6_flowinfo;   // IPv6 flow information
    struct in6_addr sin6_addr; // IPv6 address
    u_int32_t sin6_scope_id;   // Scope ID
};

struct in6_addr {
    uint8_t s6_addr[16];  // 128 bits (16 bytes)
};
```

#### `struct sockaddr_storage`
Designed to be large enough to hold both IPv4 and IPv6 structures. Use this when you don't know ahead of time which address family you'll be dealing with.
```c
struct sockaddr_storage {
    sa_family_t ss_family;  // address family
    // padding and alignment...
};
```

> **🕵️‍♂️ Red Team Note:**
> *   **Casting Trick**: The ability to cast between `sockaddr_in` and `sockaddr` is how all socket functions work. You fill in the specific struct, then cast it to the generic type.
> *   **IPv6 Evasion**: Many security tools still focus on IPv4. Using `sockaddr_in6` for C2 can sometimes bypass monitoring.

---

### 🔀 `inet_pton()` - Presentation to Network
Converts an IP address from human-readable string ("numbers-and-dots") notation into binary form.

```c
struct sockaddr_in sa;
inet_pton(AF_INET, "10.10.10.1", &(sa.sin_addr));
```

| Function | Description |
|:---|:---|
| `inet_pton(AF, src, dst)` | String → Binary (e.g., "192.168.1.1" → bytes) |
| `inet_ntop(AF, src, dst, size)` | Binary → String (the reverse) |

> **🕵️‍♂️ Red Team Note:**
> *   **Hardcoded IPs**: Using `inet_pton()` lets you embed C2 server IPs directly in your implant without DNS lookups—reduces network IOCs.
> *   **Dynamic Config**: Parse IP strings from config files or environment variables at runtime for flexibility.



---

*Notes maintained by [J Brown](https://github.com/J-c0d3-4Fun)*
*These notes and labs are adapted from [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) for educational purposes.*
