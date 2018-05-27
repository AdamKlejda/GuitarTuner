#include "toneContainer.h"

int low ;
int tone;
int up;

#include "stm32_tm1637.h"
#include "FFT.h"

void charCopy(unsigned int n, char new[], char orig[])
{
	for(unsigned int i=0; i<n; i++)
	{
		new[i]=orig[i];
	}
}

toneContainer tc;

void TC_append(int Tone, char* disp)
{
	unsigned int size = tc.size;
	if(size < TC_size)
	{
		tc.container[size].toneFrequency = (double)Tone;
		tc.container[size].upperBound = (double)TC_MAX_FREQUENCY;
		charCopy(3,tc.container[size].display, disp);

		if(tc.size==0)
		{
			tc.container[size].lowerBound = (double)TC_MIN_FREQUENCY;
		}
		else
		{
			double lowerTone = tc.container[size-1].toneFrequency;
			double currentTone = tc.container[size].toneFrequency;
			double temp = (lowerTone+currentTone)/2;

			tc.container[size-1].upperBound = temp;
			tc.container[size].lowerBound = temp;
		}

		tc.size++;
	}
}

void TC_find(int f, char disp[4])
{
	double Frequency = (double)f;
	for(int i=0;i<TC_size;i++)
	{
		if((tc.container[i].lowerBound <= Frequency) && (Frequency < tc.container[i].upperBound))
		{
			charCopy(3, disp, tc.container[i].display);

			if(Frequency < (tc.container[i].toneFrequency - TC_TuneMargin))
			{
				disp[3] = '-';
				RGB_Red();
			}
			else if(Frequency > (tc.container[i].toneFrequency + TC_TuneMargin))
			{
				if(disp[2]==' ')
				{
					disp[2]='+';
					disp[3]='-';
				}
				else
				{
					disp[3]='+';
				}
				RGB_Red();
			}
			else
			{
				disp[3]=' ';
				RGB_Green();
			}
			return;
		}
	}
	charCopy(4, disp, "none");
}

void TC_init()
{
	tc.size = 0;
}

void TC_fill()
{
	TC_init(tc);

	TC_append( 192.43, "g   ");
	TC_append( 203.88, "ab  ");
	TC_append( 216.00, "a   ");
	TC_append( 228.33, "b   ");
	TC_append( 242.45, "h   ");

	TC_append(256.87, "c1  ");
	TC_append(272.14, "db1 ");
	TC_append(288.33, "d1  ");
	TC_append(305.47, "eb1 ");
	TC_append(323.63, "e1  ");
	TC_append(342.88, "f1  ");
	TC_append(363.27, "gb1 ");
	TC_append(384.87, "g1  ");
	TC_append(407.75, "ab1 ");
	TC_append(432.00, "a1  "); //432
	TC_append(457.69, "b1  ");
	TC_append(484.90, "h1  ");

	TC_append(513.74, "c2  ");
	TC_append(544.29, "db2 ");
	TC_append(576.65, "d2  ");
	TC_append(610.94, "eb2 ");
	TC_append(647.27, "e2  ");
	TC_append(685.76, "f2  ");
	TC_append(726.53, "gb2 ");
	TC_append(769.74, "g2  ");
	TC_append(815.51, "ab2 ");
	TC_append(864.33, "a2  ");
	TC_append(915.38, "b2  ");
	TC_append(969.81, "h2  ");

	TC_append(1027.47, "c3  ");
	TC_append(1088.57, "db3 ");
	TC_append(1153.30, "d3  ");

}

void TC_show()
{
	for(int i=0;i<tc.size;i++)
		{
			low = tc.container[i].lowerBound;
			tone = tc.container[i].toneFrequency;
			up = tc.container[i].upperBound;
			USART_send_array("\n\nlow:",5);
			USART_send_int(&low,1);
			USART_send_array("\ntone:",6);
			USART_send_int(&tone,1);
			USART_send_array("  ",2);
			USART_send_array(tc.container[i].display,3);
			USART_send_array("\nup:",4);
			USART_send_int(&up,1);
		}
}
