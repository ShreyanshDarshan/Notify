#include "pch.h"
/*wav_read_write.cpp
Author: K. L. Srinivas
Problem statement :
1. opens a wav file for reading; opens another wav file for writing
2. detects the samp. rate and #samples from the header of input wav

Next, we wish to read in sequentially blocks of data from the wav file
for processing one block ("frame") at a time.

In the loop (until last frame):
 3. reads in the data (16-bit integers) in blocks of BUFSIZE samples
 4. dummy processing()
 5. writes out BUFSIZE output samples in the output wav file
end loop
*/


#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
//#include <unsupported/Eigen/FFT>
#include "render.h"
#include <fft.h>
#include <fft_settings.h>
#include <conio.h>
#include <complex>
#include <cmath>

#define SAMP 4096
#define height 1080
#define width 1920
#define hscale 3 * SAMP / 2048
#define vscale 0.2



using namespace simple_fft;

//using std::vector;
using std::cin;
//using namespace Eigen;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

Screen S(width, height);

//Eigen::FFT<float> fft;
//
//FFT hi;


//fft[]

//vector<float> timevec;
//vector<std::complex<float> > freqvec;
//
//fft.fwd(freqvec, timevec);
//// manipulate freqvec
//fft.inv(timevec, freqvec);

void plot(double x, double y)
{
	S.draw_circle_solid(x * hscale, height / 2 + y * vscale, 1, 200, 200, 200);
}
void plot(double x, double y, unsigned char R, unsigned char G, unsigned char B)
{
	S.draw_circle_solid(x * hscale, height / 2 + y * vscale, 1, R, G, B);
}

void plot(double x, double y, double ex, double ey)
{
	S.draw_path(x * hscale, height / 2 + y * vscale, ex * hscale, height / 2 + ey * vscale, 200, 200, 200);
}

void plot(double x, double y, double ex, double ey, unsigned char R, unsigned char G, unsigned char B)
{
	S.draw_path(x * hscale, height / 2 + y * vscale, ex * hscale, height / 2 + ey * vscale, R, G, B);
}

int showWav(int val)
{
	static long long count=0;
	plot((count) % int(width / hscale), val, 100+100*(count%2), 200, 200);
	return count++;
}

typedef struct header_file
{
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate;			// sample_rate denotes the sampling rate.
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;

int main()
{
	//vector <complex_type> B;
	//real_type *A;
	//const char *n;
	//int si;
	//FFT(A, B, si, n);

	const char *c;

	FILE * infile = fopen("piano.wav", "rb");		// Open wave file in read mode
	FILE * outfile = fopen("Output.wav", "wb");		// Create output ( wave format) file in write mode

	const int BUFSIZE = SAMP*2;					// BUFSIZE can be changed according to the frame size required (eg:512)
	int count = 0;						// For counting number of frames in wave file.
	short int buff16[BUFSIZE];				// short int used for 16 bit as input data format is 16 bit PCM audio
	short int channel1[BUFSIZE / 4];
	//float channel3[BUFSIZE / 2];
	complex_type fft_out[BUFSIZE / 4];			//will store the output of fft on buff16[]
	float fft_prev_out[BUFSIZE / 4];
	header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
	int nb;							// variable storing number of byes returned
	if (infile)
	{
		fread(meta, 1, sizeof(header), infile);
		fwrite(meta, 1, sizeof(*meta), outfile);
		cout << " Size of Header file is " << sizeof(*meta) << " bytes" << endl;
		cout << " Sampling rate of the input wave file is " << meta->sample_rate << " Hz" << endl;
		cout << " Number of samples in wave file are " << meta->subchunk2_size << " samples" << endl;

		for (int i = 0; i < BUFSIZE / 4; i++)
		{
			fft_prev_out[i] = 0;
		}

		while (!feof(infile))
		{
			//int cursor = ftell(infile);
			nb = fread(buff16, 1, BUFSIZE, infile);		// Reading data in chunks of BUFSIZE

			//cout << nb <<endl;
			count++;					// Incrementing Number of frames

			/* Insert your processing code here*/


			for (int i = 0; i < BUFSIZE/4; i++)
			{
				channel1[i] = buff16[i * 2];
				//channel1[i] = 100 * sin(2 * 3.14159 * 100 * float(i) / 512);
				//if ((i / 20) % 2 == 0)
				//	channel1[i] = 100;// 100 * sin(float(i) / 10);//buff16[i*2];
				//else
				//	channel1[i] = -100;
			}
			FFT(channel1, fft_out, BUFSIZE/4, c);
			
			for (int i = 0; i < BUFSIZE/4; i++)
			{
				plot(i, (sqrt(abs(fft_out[i])) + fft_prev_out[i])/2);
				fft_prev_out[i] = (sqrt(abs(fft_out[i])) + fft_prev_out[i]) / 2;
				plot(i, 0);
				//plot(i, channel1[i]);
				//plot(13, fft_prev_out[13], 255, 0, 0);
				//if (buff16[i] != -13108 && buff16[i] != 0)
				//{
				//	count = showWav(buff16[i]);
				//	S.Draw();
				//}
				//if (count % (int)(width / hscale) == 0)
				//{
				//	//S.clear();
				//}
			}
			for (int i = 1; i < BUFSIZE / 4; i++)
			{
				plot(i, fft_prev_out[i], i-1, fft_prev_out[i-1]);
			}
			//_getch();
			//for (int i = 1; i < BUFSIZE / 4 - 1; i++)
			//{
			//	if (fft_prev_out[i] > fft_prev_out[i-1]+100 && fft_prev_out[i] > fft_prev_out[i+1]+100)
			//	{
			//		
			//		//cout << fft_prev_out[13] << endl;
			//	}
			//}

			//system("cls");
			S.Draw();
			S.clear();
			//cout << count;

			//fseek(infile, cursor, 0);
			//fread11111111111111111111111111111111111111111111111111111111111111111111(buff16, 1, 1, infile);
			fwrite(buff16, 1, nb, outfile);			// Writing read data into output file
		}
		cout << " Number of frames in the input wave file are " << count << endl;
	}
	return 0;
}
