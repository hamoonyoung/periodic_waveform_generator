/* 
* @license Moon Young Ha <https://github.com/hamoonyoung/periodic_waveform_generator_with_gnuplot>
*
* References:
* http://www.gnuplot.info/
*/

#ifndef PERIODIC_WAVEFORM_GENERATOR_WITH_GNUPLOT_H_GUARD
#define PERIODIC_WAVEFORM_GENERATOR_WITH_GNUPLOT_H_GUARD

char buffer[512];
int num_of_waves = 0;
int length = 1;
int points = 1024;
int amplitude = 1;

struct Waves{
	int type;			/* 0 Sine, 1 Cosine*/
	int frequency;
	double amplitude;
	double phase;
};

#endif