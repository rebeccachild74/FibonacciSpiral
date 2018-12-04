// fibonacciSpiral.cpp creates a fibonacci spiral for a sequence. It uses the CImg library and displays the spiral using the built in display() function.


#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

void draw2DSpiral(CImg<unsigned char> &temp, vector<int> sequence, int x, int y, int count = 0);
vector<int> generateSequence(const int first, const int second, int index = 20); //up to user to not go out of int's range

const unsigned char white[] = { 255, 255, 255 };
const unsigned char black[] = { 0, 0, 0 };
const unsigned char red[] = { 255, 0, 0 };

int main()
{
	CImg<unsigned char> img(1000, 1000, 1, 3); // test image
	
	
	//vector<int> test = generateSequence(3, 8, 12);
	//vector<int> test = generateSequence(2, 10, 12);
	//vector<int> test = generateSequence(2, 8, 12);
	//vector<int> test = generateSequence(3, 12, 12);
	//vector<int> test = generateSequence(2, 14, 12);
	//vector<int> test = generateSequence(2, 12, 12);
	//vector<int> test = generateSequence(2, 4, 12);
	vector<int> test = generateSequence(4, 14, 12);

	/*for (int i = 0; i < test.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;*/

	draw2DSpiral(img, test, 500, 500);

	img.display();

	system("pause");
    return 0;
}

vector<int> generateSequence(const int first, const int second, int index) {
	vector<int> sequence = { first, second };
	sequence.resize(index);

	if (first > second) {
		cout << "Invalid first two elements, second must be larger than first." << endl;
		system("pause");
		exit(2);
	}

	for (int i = 2; i < index; i++) {
		sequence[i] = sequence[i - 1] + sequence[i - 2];
	}
	return sequence;
}

void draw2DSpiral(CImg<unsigned char> &temp, vector<int> sequence, int x, int y, int count) { // draws the reference squares for the fibinacci spiral
	//vector <int> sequence = { 3, 8, 11, 19, 30, 49, 79, 128, 207, 335, 542 };
	//vector <int> sequence = { 2, 10, 12, 22, 34, 56, 90, 146, 236, 382 };
	int operationCount = 0; //tell us which formula to use for each second point
	float splineMulti = 1.0;
	float progressionMulti = 2.0005f;
	float mult = 20.0;

	
	for (int i = 0; i < sequence.size() - 1; i++) {
		if (operationCount % 4 == 3) { //red
			*temp.draw_rectangle(x, y, x + sequence[i + 1], y + sequence[i + 1], white, 1, 5000); //draw empty rectangle- add new to x and y
			*temp.draw_spline(x, y, 0, 0, x + sequence[i + 1], y + sequence[i + 1], mult* splineMulti, 0, red); //curve
			x += sequence[i + 1];
			y += sequence[i + 1];
		}

		else if (operationCount % 4 == 2) { //green
			*temp.draw_rectangle(x, y, x - sequence[i + 1], y + sequence[i + 1], white, 1, 5000); //draw empty rectangle- subtract new from x, add new to y
			*temp.draw_spline(x, y, 0, 0, x - sequence[i + 1], y + sequence[i + 1], 0, mult* splineMulti, red); //curve
			x -= sequence[i + 1];
			y += sequence[i + 1];
		}

		else if (operationCount % 4 == 1) { //light blue
			*temp.draw_rectangle(x, y, x - sequence[i + 1], y - sequence[i + 1], white, 1, 5000); //draw empty rectangle- subtract new from x and
			*temp.draw_spline(x, y, 0, 0, x - sequence[i + 1], y - sequence[i + 1], -mult* splineMulti, 0, red); //curve
			x -= sequence[i + 1];
			y -= sequence[i + 1];
		}

		else if (operationCount % 4 == 0) { //dark blue
			*temp.draw_rectangle(x, y, x + sequence[i + 1], y - sequence[i + 1], white, 1, 5000); //draw empty rectangle- add new from x, subtract new to y
			*temp.draw_spline(x, y, 0, 0, x + sequence[i + 1], y - sequence[i + 1], 0, -mult* splineMulti, red); //curve
			x += sequence[i + 1];
			y -= sequence[i + 1];	
		}
		
		splineMulti *= progressionMulti;
		operationCount++;
		progressionMulti -= 0.05f;

		if (i < 5) mult -= 0.8; //highest spline multiplier on innermost curves **********possibly alter this based on the range of first 2 numbers in sequence ****************
		//(i < 5) mult -= 3.5 | 1.2.20 - bad
		//(i < 5) mult -= 3.2 | 1.4.20
		//(i < 5) mult -= 2.8 | 1.6.20
		//(i < 5) mult -= 2.4 | 1.8.20
		//(i < 5) mult -= 2.2 | 1.10.20
		//(i < 5) mult -= 2.0 | 1.12.20
		//(i < 5) mult -= 1.6 | 1.14.20
		//(1 < 5) mult -= 3.4 | 2.2.20 - bad
		//(i < 5) mult -= 3.0 | 2.4.12
		//(i < 5) mult -= 2.8 | 2.6.12
		//(i < 5) mult -= 2.4 | 2.8.12
		//(i < 5) mult -= 2.0 | 2.10.12
		//(i < 5) mult -= 1.6 | 2.12.12
		//(i < 5) mult -= 1.2 | 2.14.12
		//(i < 5) mult -= 3.2 | 3.3.12 - not too bad
		//(i < 5) mult -= 3.0 | 3.4.12
		//(i < 5) mult -= 2.6 | 3.6.12
		//(i < 5) mult -= 2.2 | 3.8.12
		//(i < 5) mult -= 2.0 | 3.10.12
		//(i < 5) mult -= 1.6 | 3.12.12
		//(i < 5) mult -= 1.0 | 3.14.12
		//(i < 5) mult -= 2.8 | 4.4.12
		//(i < 5) mult -= 2.4 | 4.6.12
		//(i < 5) mult -= 2.2 | 4.8.12
		//(i < 5) mult -= 1.8 | 4.10.12
		//(i < 5) mult -= 1.4 | 4.12.12
		//(i < 5) mult -= 0.8 | 4.14.12
		//(i < 5) mult -= 2.6 | 5.5.12
		//(i < 5) mult -= 2.4 | 5.6.12
		//(i < 5) mult -= 2.0 | 5.8.12
		//(i < 5) mult -= 1.8 | 5.10.12
		//(i < 5) mult -= 1.6 | 5.12.12
		//(i < 5) mult -= 1.4 | 5.14.12
	}
}
