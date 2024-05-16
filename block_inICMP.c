/* block_inICMP.c

   Program to block all incoming packets except ICMP echo reply packets in response to outgoing ICMP request packets in the past 1 minute using divert socket in FreeBSD VM.

  Anmol Tripathi Feb 2024
*/

#include "divertlib.h"
#include <netinet/ip_icmp.h>
#include <time.h>

#define DEBUG

#define MAX_PACKET_HISTORY 100
#define ICMP_ECHO_REQUEST 8
#define ICMP_ECHO_REPLY 0

struct PHistory {
    struct in_addr src_ip;
    time_t timestmp;
};

int main(int argc, char *argv[]) {
    int i, divsock, len;
    struct sockaddr_in sin;
    int udpsock, DivPort;
    unsigned char buf[maxbuflen + 1];
    struct ip *iph;
    struct icmphdr *icmp;
    struct PHistory history[MAX_PACKET_HISTORY] = {0};
    int numOfPackets = 0;
   
    if (argc!=2){
     puts("usage : divert-loop [div port]");
     return 1;
     };

     DivPort=atoi(argv[1]);
     printf("DivPort=%d\n", DivPort);

    // Initialize divert socket
    if ((divsock = initDivSock(DIVERT_PORT)) <= 0) {
         printf("can not get divert socket for port %d, divsock=%d\n",
         DivPort, divsock);
         exit(1);
    }

    // loop to receive and process packets
    for (;;) {
        // Receive packet
        if ((len = recvfrom(divsock, buf, maxbuflen, 0, (struct sockaddr *)&sin, &addrsize)) > 0) {
            iph = (struct ip *)buf;

            // Check if the packet is an ICMP packet
            if (iph->ip_p == 1) {
                icmp = (struct icmphdr *)(buf + iph->ip_hl * 4);

                // Check if it's an ICMP echo reply packet as icmp echo reply packet is 0
                if (icmp->icmp_type == ICMP_ECHO_REPLY) {
                    // Check if it's in response to an outgoing ICMP echo request packet sent in the past minute
                    for (i = 0; i < numOfPackets; i++) {
                        if (history[i].src_ip.s_addr == iph->ip_src.s_addr &&time(NULL) - history[i].timestmp <= 60) {
                            // Allow the packet to pass through
                            sendto(divsock, buf, len, 0, (struct sockaddr *)&sin, sizeof(struct sockaddr));
                            break;
                        }
                    }
                }
            }

            // Add packet to history
            if (numOfPackets < MAX_PACKET_HISTORY) {
                history[numOfPackets].src_ip = iph->ip_src;
                history[numOfPackets].timestmp = time(NULL);
                numOfPackets++;
            }

#ifdef DEBUG
            // Debug output
            printf("Received packet from %s\n", inet_ntoa(iph->ip_src));
            printf("\tdst IP:%s\n", inet_ntoa(iph->ip_dst));
            printf("\tprotocol :%d\n", iph->ip_p);
#endif
        }
    }

    return 0;
}
