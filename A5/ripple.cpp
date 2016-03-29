/*
 * Rafael Solorzano
 * V00838235
 * CSC205 Assignment 5
 *
 *
*/


#include <string>
#include <iostream>
#include "lodepng.h"
#include "png_canvas.h"
#include <math.h>

using namespace std;



void process_image(PNG_Canvas_BW& image){
	int width = image.get_width();
	int height = image.get_height();

	

	//Make a new image canvas for the output to avoid conflicts
	PNG_Canvas_BW transformed(width,height);
	
	double ttx = 120;
	double tty = 250;
	double ax = 10;
	double ay = 15;
	double Tx;
	double Ty;

	for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				Tx = (x + ax) * sin(((2*M_PI)*y)/ttx);
				Ty = (y+ay) * sin((((2*M_PI)*x)/tty));

				//printf("%f\n",Tx);
				//printf("%f\n",Ty);

				int x0 = floor(Tx);
				int y0 = floor(Ty);
				int x1 = ceil(Tx);
				int y1 = ceil(Ty);
				int xs = Tx - x0;
				int ys = Ty - y0;
				/*
				if(x0 > 255) x0 = 128;
				if(x1 > 255) x1 = 128;
				if (y0 > 255) y0 = 128;
				if (y1 > 255) y1 = 128;
				if(x0 < 0) x0 = 128;
				if(x1 < 0) x1 = 128;
				if (y0 < 0) y0 = 128;
				if (y1 < 0) y1 = 128;
				*/
				int dx = 1 - xs;
				int dy = 1 - ys;
				int p0 = (image.get_pixel(x0,y0)*dx)+(image.get_pixel(x1,y0)*xs);
				int p1 = (image.get_pixel(x0,y1)*dx)+(image.get_pixel(x1,y1)*xs);
				int result = (p0 * dy) + (p1 *ys);
				if (result > 255) result = 128;
				if (result < 0) result = 128;
				transformed.set_pixel(x,y,result);

			}
		}



			
			
	//Copy the result back into the provided image
	image = transformed;
}



int main(int argc, char** argv){
	if (argc < 3){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return 0;
	}
	string input_filename = argv[1];
	string output_filename = argv[2];
	
	PNG_Canvas_BW canvas;
	if (!canvas.load_image(input_filename)){
		cerr << "Unable to load " << input_filename << ". Exiting..." << endl;
		return 0;
	}
	
	process_image(canvas);
	canvas.save_image(output_filename);
	
	
}
