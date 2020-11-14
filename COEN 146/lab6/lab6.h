typedef struct {
	int seq_ack;
	int len;
	int cksum;
} Header;

typedef struct {
	Header header;
	char data[10];
} Packet;

#define PBADCKSUM 5;
