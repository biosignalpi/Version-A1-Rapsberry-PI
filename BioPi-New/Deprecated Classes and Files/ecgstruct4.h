/*
 * EcgStruct4.h
 *
 *  Created on: Oct 28, 2015
 *      Author: martin
 */

#ifndef ECGSTRUCT4_H_
#define ECGSTRUCT4_H_

struct EcgStruct4 {
public:
	EcgStruct4(double,double,double,double,double);
	virtual ~EcgStruct4();
	double time,frame1,frame2,frame3,frame4;

};

#endif /* ECGSTRUCT4_H_ */
