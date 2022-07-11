#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <math.h>
#include <stdio.h>

const int sine_table[40] = { 0, 5125, 10125, 14876, 19260, 23170, 26509, 29196,
31163, 32364, 32767, 32364, 31163, 29196, 26509, 23170, 19260, 14876, 10125,
5125, 0, -5126, -10126, -14877, -19261, -23171, -26510, -29197, -31164, -32365,
-32768, -32365, -31164, -29197, -26510, -23171, -19261, -14877, -10126, -5126 };

int i = 0;
int x1 = 0;
int x2 = 0;
float y = 0;

float sin1(float phase) {
	x1 = (int)phase % 40;
	if (x1 < 0) x1 += 40;
	x2 = (x1 + 1) % 40;
	y = (sine_table[x2] - sine_table[x1])
		* ((float)((int)(40 * 0.001 * i * 100) % 4100) / 100 - x1)
		+ sine_table[x1];
	return y;
}

int main()
{
	struct ifreq ifr;			/* CAN interface info struct */
	struct sockaddr_can addr;	/* CAN adddress info struct */
	struct can_frame frame;		/* CAN frame struct */
	int s;						/* SocketCAN handle */
	double time_arr[1000], amplitude_arr[1000], phase_arr[1000];
	double pi = 3.1415926535897932384626433832795;
	int j, k;


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

	/* Disable reception filter on this RAW socket */
	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

	// TODO: Bind socket to can0 interface
	bind(s, (struct sockaddr*)&addr, sizeof(addr));

	for ( j = 0; j < 1000; j++) {
		float x = 40 * 0.001 * i;
		float radians = x * 2 * pi / 40;
		//printf("%f %f %f\n", x, sin1(x) / 32768, sin1(radians));
		time_arr[j] = x;
        	amplitude_arr[j] = sin1(x) / 32768;
        	phase_arr[j] = sin1(radians);
		i = i + 1;
	}

	while (1)
	{

		for (k = 0; k < 1000; k++)
		{



			frame.can_id = 0x34;
			frame.can_dlc = 5;
			frame.data[0] = time_arr[k];
			frame.data[1] = amplitude_arr[k];
			frame.data[2] = phase_arr[k];
			printf("%x [%d] %x %x %x\n", frame.can_id, frame.can_dlc, frame.data[0], frame.data[1], frame.data[2]);  
			write(s, &frame, sizeof(frame));
		}
	}





	close(s);

	return 0;
}
