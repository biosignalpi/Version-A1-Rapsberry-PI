#include "ecgstream_fourchannels.h"
    #include <iostream>
    
    
    EcgStream_four::EcgStream_four() {

        //m_NumberOfChannels=numberOfChannels;
        //init(m_NumberOfChannels);
    }
    
    EcgStream_four::~EcgStream_four() {
        std::cerr << "Destroyer ECGStream" << std::endl;
    }
    int EcgStream_four::getSize(){
        std::cerr << "getSize ECGSTREAM" << streamVector.size() <<std::endl;
        return streamVector.size();
    }

    EcgStruct4 EcgStream_four::getDataD(){
 //       double val [4]={16.4,2,77,29};
    	EcgStruct4 tmp=streamVector.front();

    	    streamVector.erase(streamVector.begin());
        return tmp;
    
    }
    
    EcgStruct4 EcgStream_four::at(int i){
 //       double val [4]={16.4,2,77,29};
        EcgStruct4 tmp=streamVector.at(i);

        return tmp;

    }

    bool EcgStream_four::empty(){
    	return streamVector.empty();
    }
    void EcgStream_four::add(EcgStruct4 & data) {
//        double n=data;
        streamVector.push_back(data);
    }
    
    void EcgStream_four::add(double inTime,double inFrame1, double inFrame2, double inFrame3, double inFrame4) {
    	EcgStruct4 tmp=EcgStruct4(inTime,inFrame1,inFrame2,inFrame3,inFrame4);
    	streamVector.push_back(tmp);

    }

    void EcgStream_four::transferValues(EcgStream_four & newStream) {
    //	auto it = std::next(streamVector.begin(), streamVector.size());
    //	std::move(streamVector.begin(), it, std::back_inserter(newStream->streamVector));
    		streamVector.swap(newStream.streamVector);
    		std::cerr << streamVector.max_size()<< std::endl;
    		streamVector.clear();
    }
    void EcgStream_four::print(){


    	while (!streamVector.empty()){
    		EcgStruct4 tmp=streamVector.front();
    		streamVector.erase(streamVector.begin());
    		std::cerr << tmp.time
    				<< "  " << tmp.frame1
    				<< "  " << tmp.frame2
    				<< "  " << tmp.frame3
    				<< "  " << tmp.frame4 << std::endl;
    	}
    }

    void EcgStream_four::init(int m_numberOfChannels) {
   /*         double val [4]={16.4,2,77,29};
            std::array<double,4> myfirst = {16.4,2,77,29};
            streamVector.push_back({16.4,2,77,29});
            std::array<double,4> mysecond = {1,15.7,7,5};
            streamVector.push_back(mysecond);
            sizeValues=41;
          std::cout << sizeValues <<std::endl ;
            //values [10]={18,15,42,12,13,15,78,54,0,0};
            values[1]=4;
            for (int i=0; i<sizeValues; ++i){
                values[i]=i+3; }
    */
    
    }
