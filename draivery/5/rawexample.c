#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

int main(void)
{
	int sock;
	struct sockaddr_ll addr;
	struct ifreq ifr;
	unsigned char packet[64];
	int if_index;

	sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock < 0) {
		perror("socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "practice5");
	if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
		perror("ioctl");
		close(sock);
		return 1;
	}
	if_index = ifr.ifr_ifindex;

	memset(&addr, 0, sizeof(addr));
	addr.sll_family = AF_PACKET;
	addr.sll_ifindex = if_index;
	addr.sll_halen = ETH_ALEN;

	memset(packet, 0, sizeof(packet));
	memcpy(packet, "\x00\x12\x34\x56\x78\x90\x00\x00\x00\x00\x00\x00\x12\x34", 14);
	strcpy((char *)packet + 14, "hello world");

	if (sendto(sock, packet, 25, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("sendto");
		close(sock);
		return 1;
	}

	printf("Success!\n");
	close(sock);
	return 0;
}
