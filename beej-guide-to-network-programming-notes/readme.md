# 📡 Beej's Guide to Network Programming - Notes & Labs

![Focus](https://img.shields.io/badge/Focus-Network%20Programming-blue?style=for-the-badge)
![Topic](https://img.shields.io/badge/Topic-Sockets%20%26%20Protocols-red?style=for-the-badge)

This directory contains my code labs, exercises, and study notes from following **[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/)**. Building on C fundamentals, this section focuses on how to communicate over networks at the socket level.

> **🎯 Learning Goal:** Master low-level network programming to build custom **Command & Control (C2) implants**, reverse shells, and network reconnaissance tools. Understanding sockets is fundamental to Red Team operations.

## 🧪 Code Labs

| Exercise | Description | Status |
|:---|:---|:---|
| **[`sockets.c`](file:///Users/jbrown/C-Dev-Sandbox/beej-guide-to-network-programming-notes/sockets.c)** | Socket fundamentals: SOCK_STREAM vs SOCK_DGRAM, TCP vs UDP concepts. | 🟡 In Progress |

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

*Notes maintained by [J Brown](https://github.com/J-c0d3-4Fun)*
*These notes and labs are adapted from [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) for educational purposes.*
