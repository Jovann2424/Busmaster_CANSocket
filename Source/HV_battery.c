#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main()
{
	struct ifreq ifr;				/* CAN interface info struct */
	struct sockaddr_can addr;		/* CAN adddress info struct */
	struct can_frame frame, frame_send;			/* CAN frame struct */
	struct can_filter rfilter[2];	/* CAN reception filter */
	int s;							/* SocketCAN handle */
	int pom;
	
	
	memset(&ifr, 0, sizeof(ifr));
	memset(&addr, 0, sizeof(addr));
	memset(&frame, 0, sizeof(frame));
	
	// TODO: Open a socket here
	
	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

	/* Convert interface string "can0" to index */
	strcpy(ifr.ifr_name, "can0");
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	/* Setup address for binding */  
	addr.can_ifindex = ifr.ifr_ifindex;
	addr.can_family = AF_CAN;
	
	// TODO: Set the reception filter on this RAW socket
	
	rfilter[0].can_id   = 0x123;
	rfilter[0].can_mask = CAN_SFF_MASK;

	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, rfilter,2*sizeof(rfilter));
	
	// TODO: Bind socket to can0 interface
		
		bind(s, (struct sockaddr *)&addr, sizeof(addr));
		
	while(1)
	{
		// TODO: Read received frame and print on console
		read(s, &frame, sizeof(frame));
		
	printf("can0\t\t\t%x\t[%d]\t%x %x %x %x %x %x %x %x\n",frame.can_id,frame.can_dlc,frame.data[0],frame.data[1],frame.data[2],frame.data[3],frame.data[4], frame.data[5],frame.data[6],frame.data[7]);
		frame.can_id=0x80000123;
		frame.can_dlc = 1;
		frame.data[0]=1;
		write(s, &frame, sizeof(frame));
	}
	
	close(s);
	
	return 0;
}
