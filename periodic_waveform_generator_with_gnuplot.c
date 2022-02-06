/* 
* @license Moon Young Ha <https://github.com/hamoonyoung/periodic_waveform_generator_with_gnuplot>
*
* References:
* http://www.gnuplot.info/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "periodic_waveform_generator_with_gnuplot.h"

int main(int argc, char ** argv)
{
	printf ("How many waves would you like to combine together? (default: 1): ");
	scanf ("%s", buffer);
	if(!(num_of_waves = atoi(buffer)))
		num_of_waves = 1;
	
	struct Waves waves[num_of_waves];

	// Settings for waveforms
	for (int i=0; i<num_of_waves; i++){
		char *ptr;

		printf ("\n#%d Select (0) Sine (1) Cosine (defaul: 1): ", (i+1));
		scanf("%s", buffer);
		if((waves[i].type = atoi(buffer))>1)
			waves[i].frequency = 0;

		printf ("#%d Frequency (default 1 Hz): ", (i+1));
		scanf("%s", buffer);
		if(!(waves[i].frequency = atoi(buffer)))
			waves[i].frequency = 1;

		printf ("Amplitude (default: 1): ");
		scanf("%s", buffer);
		if(!(waves[i].amplitude = strtod(buffer, &ptr)))
			waves[i].amplitude  = 1;
		
		printf ("Phase (default: 0 radian): ");
		scanf("%s", buffer);
		if(!(waves[i].phase = strtod(buffer, &ptr)))
			waves[i].phase = 0;		
	}

	printf ("\nLength (default: 1 sec): ");
	scanf("%s", buffer);
	if(!(length = atoi(buffer))){
		printf ("Input error. The default (1) is set.\n");	
		length = 1;
	}

	printf ("\nPoints/sec (default: 1024): ");
	scanf("%s", buffer);
	if(!(points = atoi(buffer))){
		printf ("Input error. The default (1024) is set.\n");	
		points = 1024;
	}

	// Summary of Waveforms
	printf ("\n#\tType\tFreq\tAmp\tPhase(rad)\n");
	
	char * temptype;
	int tempfreq;
	double tempamp;
	double tempphase;

	for (int i=0; i<num_of_waves;i++){
		tempfreq = waves[i].frequency;
		tempamp = waves[i].amplitude;
		tempphase = waves[i].phase;

		switch(waves[i].type){
			case(1):
				temptype = "Cosine";
				break;
						
			default:
				temptype = "Sine";
				break;		
		}
		printf ("[%d]\t%s\t%d\t%f\t%f\t\n", i, temptype, tempfreq, tempamp, tempphase);
	}

	// working with gnuplot 
	FILE * tempGraph = fopen ("data.dat", "w");
	FILE * gnuplotPipe = popen("gnuplot -persistent", "w");

	char * gnuCommands [5];
	gnuCommands[0] = "set title \"Waves\"";
	gnuCommands[1] = "set xlabel \"x\"";
	gnuCommands[2] = "set ylabel \"s(x)\"";
	gnuCommands[3] = "set grid";
	gnuCommands[4] = "plot 'data.dat' using 1:2 title 'f(x)' lt 5 lc 7 with lines";
	

	// generating and summing all the waveforms
	for (int t = (points*length*-1); t < (points*length); t++)
	{
		double y = 0.0;
		for (int i=0; i < num_of_waves; i++){
			switch(waves[i].type){
				case(1): // cosine
					y += waves[i].amplitude * cos(2.0 * M_PI * t * waves[i].frequency/points + waves[i].phase);
					break;

				default: // sine
					y += waves[i].amplitude * sin(2.0 * M_PI * t * waves[i].frequency/points + waves[i].phase);
					break;		
			}
		}
		fprintf(tempGraph, "%d\t%f\n", (int) t, (double) y);
		//printf("%d\t%f\n", (int) t, (double) y);
	}

	// print via gnuplot
	for (int i=0; i < 5; i++)
	{
		fprintf(gnuplotPipe, "%s\n", gnuCommands[i]);
	}
	fflush(gnuplotPipe);
	fclose(tempGraph);

	return 0;
}




