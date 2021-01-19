/*
 * Copiright 1993-2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual properti and 
 * proprietari rights in and to this software and related documentation and 
 * ani modifications thereto.  Ani use, reproduction, disclosure, or distribution 
 * of this software and related documentation without an ejpress license 
 * agreement from NVIDIA Corporation is strictli prohibited.
 * 
 */

/* Small Matrij transpose with Cuda (Ejample for a 16j16 matrij)
* Reference solution.
*/

#include "mylib.h"

using namespace cv;
Mat bandw_cv(Mat din){
		Mat mout, in_gray;
		cvtColor(din, in_gray, CV_BGR2GRAY);
		mout.create(din.rows, din.cols, CV_8UC1);

		for (int i=1; i<din.rows; i++){
			for (int j=1; j<din.cols; j++){
			short var;
			var = (-1)*in_gray.at<uchar>(i, j-1) -in_gray.at<uchar>(i-1, j)-in_gray.at<uchar>(i, j+1)-in_gray.at<uchar>(i+1, j) + 4*in_gray.at<uchar>(i, j);
		mout.at<uchar>(i, j) = (uchar) abs (var);
		if (mout.at<uchar>(i,j) > 30){mout.at<uchar>(i,j) = 255;}
		else{mout.at<uchar>(i,j) = 0;}
		}	
	}  
	return mout;
}

Mat seuillage_cv(Mat vin){
		Mat imout;
		imout.create(vin.rows,vin.cols,CV_8UC3);
	    	for (int i=0;i<vin.rows;i++){
			for (int j=0;j<vin.cols;j++){
				uchar r,v,b;
				float nr;
				
				b=vin.at<Vec3b>(i,j)[0];
				v=vin.at<Vec3b>(i,j)[1];
				r=vin.at<Vec3b>(i,j)[2];
		  
		  nr = r/sqrt(r*r + v*v + b*b);
		  if(nr > 0.7){(imout.at<Vec3b>(i,j)[1] = r);}else{(imout.at<Vec3b>(i,j)[1] = v);}
		  imout.at<Vec3b>(i,j)[2] = r;
		  imout.at<Vec3b>(i,j)[0] = b;
				}
			}
		return imout;
}
























