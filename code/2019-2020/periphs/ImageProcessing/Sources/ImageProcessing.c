/*
 * ImageProcessing.c
 *
 *  Created on: Jan 22, 2020
 *      Author: User
 */
#include "ImageProcessing.h"

int img_diffData[128];
int img_ProcData[128];
#define G_size 3
int Diffcoeffs[G_size]={3,5,9};
void img_differentiate(int mode){
	switch(mode){
	case 1:
		break;
	default:
		img_diffData[0]=0;
		img_diffData[127]=0;
		for(int i=1;i<127;i++){
			img_diffData[i]=(camera_getRawData(i+1)-camera_getRawData(i-1))/2;
		}
		break;
	}
}
void img_getEdges(int mode){
	switch(mode){
		case 1:
			break;
		default:
			
			break;
		}
}
void img_process(int mode){
	switch(mode){
		case 1:
			break;
		default:
			for(int i=0;i<128;i++){
				if(i<G_size || i>(127-G_size)){
					img_ProcData[i]=0;
				}else{					
					img_ProcData[i]=0;//camera_getRawData(i)/Diffcoeffs[0];
					for(int j=1;j<G_size+1;j++){
						img_ProcData[i]-=camera_getRawData(i-j)/Diffcoeffs[j-1];
						img_ProcData[i]+=camera_getRawData(i+j)/Diffcoeffs[j-1];
					}
				}
			}
			break;
		}
}


int img_getDiffData(int index){
	return 13*abs(img_diffData[index]);
}
int img_getProcData(int index){
	return 10*abs(img_ProcData[index]);
}
