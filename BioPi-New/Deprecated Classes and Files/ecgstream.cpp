#include "ecgstream.h"
#include <iostream>
#include <utility>


EcgStream::EcgStream(){
	std::cerr << "Constructor ECGStream" << std::endl;
    init();
}

EcgStream::~EcgStream() {

    std::cerr << "Destroyer ECGStream" << std::endl;
}
int EcgStream::getSize(){
    std::cerr << "getSize ECGSTREAM" << streamVector.max_size() <<std::endl;
    return streamVector.size();
}

void EcgStream::hej(){
	if (!streamVector.empty())
    std::cerr << streamVector.front() <<std::endl ;
}

bool EcgStream::empty(){
    return streamVector.empty();
}

double  EcgStream::getData(){
	double tmp=0;
	if (!streamVector.empty()) {
    tmp=streamVector.front();
    streamVector.erase(streamVector.begin());
	}
    return tmp;

}

void EcgStream::transferValues(EcgStream & newStream) {
//	auto it = std::next(streamVector.begin(), streamVector.size());
//	std::move(streamVector.begin(), it, std::back_inserter(newStream->streamVector));
		streamVector.swap(newStream.streamVector);
		std::cerr << streamVector.max_size();
		streamVector.clear();
}


void EcgStream::add(double n) {

    streamVector.push_back(n);
}

void EcgStream::init() {

    std::cerr << streamVector.size() <<std::endl ;

    //values [10]={18,15,42,12,13,15,78,54,0,0};

//    for (int i=0; i<20; ++i){
//        streamVector.push_back(i+3); }


}
