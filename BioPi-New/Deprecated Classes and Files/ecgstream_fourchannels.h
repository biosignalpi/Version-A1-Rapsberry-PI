#ifndef ECGSTREAM_H_
     #define ECGSTREAM_H_
    
    #include "datastream.h"
    #include <vector>
	#include "ecgstruct4.h"
    
/**
     * @brief DataStream used for storing of 5-lead ECG-Data
     * @deprecated not used anymore
    */
    struct EcgStream_four: public DataStream {
    public:
        EcgStream_four();
        virtual ~EcgStream_four();
        virtual int getSize();///< \brief returns size of streamVector \return size
        virtual bool full(){ return false;}///< Returns state of streamVector \return full?
        virtual double getData(){return 0;}
        virtual EcgStruct4 at(int i); ///< Returns the element from position i. Doesn't delete the element.
        virtual EcgStruct4 getDataD(); ///< Returns first element in streamVector, also deletes the element from streamVector \return [double] first element
        void transferValues(EcgStream_four &);
        virtual bool empty(); ///< Return empty if streamVector is empty \return empty?
        virtual void add(EcgStruct4 &); ///< adds the element to the end of streamVector \param[in] value
        virtual void add(double time,double frame1,double frame2,double frame3,double frame4);
        virtual void add(double){};
        virtual void print();
    private:
        double test[4];
        int m_NumberOfChannels;
        // std::vector<double> streamVector;
        std::vector<EcgStruct4> streamVector;
       int sizeValues;
        void init(int m_numberOfChannels);
    
    };
    
    #endif /* ECGSTREAM_H_ */
