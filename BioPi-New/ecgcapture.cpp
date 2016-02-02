
#include <libFiles/bcm2835.h>
#include "ecgcapture.h"
#include <QVector>
#include <QDebug>
#include "stdio.h"
#include "meanFilter.h"

#define PIN18 RPI_GPIO_P1_18
#define PIN16 RPI_GPIO_P1_16

static float vreff = 1.8, ECG_GAIN = 1.4, RESPIRATION_gain = 1;
static unsigned int nFrames;

EcgCapture::EcgCapture()
{
    test = 0;
}

/**
 * @brief Initiate the device by configuring the registers depending on operating mode and
 * sampling frequency.
 *
 *
 */
void EcgCapture::init(OperatingMode mode, Frequency freq)
{
    if (!bcm2835_init()) {
            qDebug() << ("Could not init bcm2835 in EcgCapture") << endl;
           exit(EXIT_FAILURE);
    }

    spiInit();

    QByteArray CMREFCTL;
    CMREFCTL.resize(4);

    QByteArray FILTCTL;
    FILTCTL.resize(4);

    QByteArray FRMCTL;
    FRMCTL.resize(4);

    QByteArray ECGCTL;
    ECGCTL.resize(4);

    QByteArray RESPCTL;
    RESPCTL.resize(4);

    QByteArray TESTTONE;
    TESTTONE.resize(4);

    QByteArray LOFFCTL;
    LOFFCTL.resize(4);

    //Configure registers depending on source
    switch (mode) {
    case ecgCapture:
        //CMREFCTL is set to 0x85E0000A
        CMREFCTL[0] = 0x85;
        CMREFCTL[1] = 0xE0;
        CMREFCTL[2] = 0x00;
        CMREFCTL[3] = 0x4A; //0x0A for the first board, 0x4A for the REV_A board

        //FILTCTL is set to 0x8B000000
        FILTCTL[0] = 0x8B;
        FILTCTL[1] = 0x00;
        FILTCTL[2] = 0x00;
        FILTCTL[3] = 0x00;

        //FRMCTL is set to 0x8A1FCE00
        FRMCTL[0] = 0x8A;
        FRMCTL[1] = 0x1F;
        FRMCTL[2] = 0xC6; //CE = pace disabled, C6 = pace disabled LOFF enabled
        FRMCTL[3] = 0x00;

        LOFFCTL[0] = 0x82;
        LOFFCTL[1] = 0x00;
        LOFFCTL[2] = 0x00;
        LOFFCTL[3] = 0x15;

        //ECGCTL is set to 0x81F800AE
        ECGCTL[0] = 0x81;
        ECGCTL[1] = 0xF8;
        ECGCTL[2] = 0x00;
        ECGCTL[3] = 0xAE;

        //RESPCTL is set to 0x83002099
        RESPCTL[0] = 0x83;
        RESPCTL[1] = 0x00;
        RESPCTL[2] = 0x20;
        RESPCTL[3] = 0x99;
        break;
    case testToneSquare:
        //CMREFCTL is set to 0x8500000B
        CMREFCTL[0] = 0x85;
        CMREFCTL[1] = 0x00;
        CMREFCTL[2] = 0x00;
        CMREFCTL[3] = 0x0B;

        //TESTTONE is set to 0x88F8001D
        TESTTONE[0] = 0x88;
        TESTTONE[1] = 0xF8;
        TESTTONE[2] = 0x00;
        TESTTONE[3] = 0x1D;

        //FILTCTL is set to 0x8B000008
        FILTCTL[0] = 0x8B;
        FILTCTL[1] = 0x00;
        FILTCTL[2] = 0x00;
        FILTCTL[3] = 0x1D;

        //FRMCTL is set to 0x8A1FCE10
        FRMCTL[0] = 0x8A;
        FRMCTL[1] = 0x1F;
        FRMCTL[2] = 0xCE;
        FRMCTL[3] = 0x10;

        //ECGCTL is set to 0x81F800AE
        ECGCTL[0] = 0x81;
        ECGCTL[1] = 0xF8;
        ECGCTL[2] = 0x00;
        ECGCTL[3] = 0xAE;
        break;
    case testToneLowFreqSin:
        //CMREFCTL is set to 0x8500000B
        CMREFCTL[0] = 0x85;
        CMREFCTL[1] = 0x00;
        CMREFCTL[2] = 0x00;
        CMREFCTL[3] = 0x0B;

        //TESTTONE is set to 0x88F80005
        TESTTONE[0] = 0x88;
        TESTTONE[1] = 0xF8;
        TESTTONE[2] = 0x00;
        TESTTONE[3] = 0x05;

        //FILTCTL is set to 0x8B000008
        FILTCTL[0] = 0x8B;
        FILTCTL[1] = 0x00;
        FILTCTL[2] = 0x00;
        FILTCTL[3] = 0x08;

        //FRMCTL is set to 0x8A1FCE10
        FRMCTL[0] = 0x8A;
        FRMCTL[1] = 0x1F;
        FRMCTL[2] = 0xCE;
        FRMCTL[3] = 0x10;

        //ECGCTL is set to 0x81F800AE
        ECGCTL[0] = 0x81;
        ECGCTL[1] = 0xF8;
        ECGCTL[2] = 0x00;
        ECGCTL[3] = 0xAE;
        break;
    case testToneHighFreqSin:
        //CMREFCTL is set to 0x8500000B
        CMREFCTL[0] = 0x85;
        CMREFCTL[1] = 0x00;
        CMREFCTL[2] = 0x00;
        CMREFCTL[3] = 0x0B;

        //TESTTONE is set to 0x88F8000D
        TESTTONE[0] = 0x88;
        TESTTONE[1] = 0xF8;
        TESTTONE[2] = 0x00;
        TESTTONE[3] = 0x0D;

        //FILTCTL is set to 0x8B000008
        FILTCTL[0] = 0x8B;
        FILTCTL[1] = 0x00;
        FILTCTL[2] = 0x00;
        FILTCTL[3] = 0x08;

        //FRMCTL is set to 0x8A1FCE10
        FRMCTL[0] = 0x8A;
        FRMCTL[1] = 0x1F;
        FRMCTL[2] = 0xCE;
        FRMCTL[3] = 0x10;

        //ECGCTL is set to 0x81F800AE
        ECGCTL[0] = 0x81;
        ECGCTL[1] = 0xF8;
        ECGCTL[2] = 0x00;
        ECGCTL[3] = 0xAE;
        break;
    default:
        break;
    }

    //Set sampling frequency
    switch (freq) {
    case lowFreq:
        FRMCTL[3] = FRMCTL[3] & 0xF3;
        FRMCTL[3] = FRMCTL[3] | 0x0C;
        qDebug()<<"Low freq";
        break;
    case midFreq:
        FRMCTL[3] = FRMCTL[3] & 0xF3;
        FRMCTL[3] = FRMCTL[3] | 0x04;
        qDebug()<<"Mid freq";
        break;
    case highFreq:
        FRMCTL[3] = FRMCTL[3] & 0xF3;
        FRMCTL[3] = FRMCTL[3] | 0x00;
        qDebug()<<"High freq";
        break;
    default:
        break;
    }

    if (mode == ecgCapture) {
        setReg(CMREFCTL);
        setReg(FILTCTL);
        setReg(FRMCTL);
        setReg(ECGCTL);
        setReg(RESPCTL);
        setReg(LOFFCTL);
        leadMode = digital;
        nFrames = 7;
    } else {
        setReg(CMREFCTL);
        setReg(TESTTONE);
        setReg(FILTCTL);
        setReg(FRMCTL);
        setReg(ECGCTL);
        leadMode = electrode;
        nFrames = 6;
    }
}

/*!
 * Start the SPI communication
 */
void EcgCapture::spiInit()
{
    bcm2835_gpio_fsel(PIN18, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN18, LOW);
    delay(100);
    bcm2835_gpio_write(PIN18, HIGH);
    delay(100);
    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_512);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
    bcm2835_gpio_fsel(PIN16, BCM2835_GPIO_FSEL_INPT);
}

/*!
 * Method used to test if the device is working properly. It works by writing to a
 * register and then reading the same register.
 *
 * @deprecated Currently not in use.
 */
void EcgCapture::testDevice()
{
    QByteArray TESTIN;
    TESTIN.resize(4);

    QByteArray TESTOUT;
    TESTOUT.resize(4);

    TESTIN[0] = 0x01;
    TESTIN[1] = 0x00;
    TESTIN[2] = 0x00;
    TESTIN[3] = 0x00;

    TESTOUT[0] = 0x11;
    TESTOUT[1] = 0x11;
    TESTOUT[2] = 0x11;
    TESTOUT[3] = 0x11;

    qDebug()<<TESTOUT.toHex();

    bcm2835_spi_transfernb(TESTIN.data(), TESTOUT.data(), TESTIN.size());

    qDebug()<<TESTOUT.toHex();

    if(bcm2835_gpio_lev(PIN16)==LOW) {
        qDebug()<<"LOW";
    } else {
        qDebug()<<"HIGH";
    }

    QByteArray FRAMES;
    QByteArray DATAOUT;
    FRAMES.resize(4);
    DATAOUT.resize(4);

    FRAMES[0] = 0x00;
    FRAMES[1] = 0x00;
    FRAMES[2] = 0x00;
    FRAMES[3] = 0x00;

    DATAOUT[0] = 0x11;
    DATAOUT[1] = 0x11;
    DATAOUT[2] = 0x11;
    DATAOUT[3] = 0x11;

    qDebug()<<DATAOUT.toHex();
    bcm2835_spi_transfernb(FRAMES.data(), DATAOUT.data(), FRAMES.size());
    qDebug()<<DATAOUT.toHex();
}

/*!
 * Method to set a control register, returns true on success or false on failure.
 */
bool EcgCapture::setReg(QByteArray writeCommand)
{
    //Validate the input
    if (writeCommand.size() != 4)
        return 0;

    enableRegisterWrite();
    bcm2835_spi_transfern(writeCommand.data(), writeCommand.size());

    return 1;
}

/**
 * Enable chip select
 */
void EcgCapture::csEnable()
{
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
}

/**
 * @brief Disable chip select
 *
*/
void EcgCapture::csDisable()
{
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, HIGH);
}

/**
 * @brief Enable the ability to write to a register
 *
 * */

void EcgCapture::enableRegisterWrite()
{
    csDisable();
    csEnable();
}

/*!
 * Start sending frames
 */
void EcgCapture::start()
{
    enableRegisterWrite();

    char FRAMES1[] = {0x40,0x00,0x00,0x00};
    bcm2835_spi_transfern(FRAMES1,sizeof(FRAMES1));
}


void EcgCapture::stop()
{ 

}

/*!
 * Convert Ecg voltage
 */
double EcgCapture::ecgVoltageConversion(int ADCDecimal, leadFormat format)
{
    double ecg_voltage = 0;

    if (format == digital) {
        if(ADCDecimal> 8388608) {
            ecg_voltage = ((4*vreff*(-(16777216-ADCDecimal))/ECG_GAIN)/(16777215));
        } else {
            ecg_voltage = ((4*vreff*ADCDecimal)/ECG_GAIN)/(16777215);
        }
    } else if (format == electrode) {
        ecg_voltage = (2*ADCDecimal*(vreff/ECG_GAIN))/(16777215);
    }

    return ecg_voltage;
}

/*!
 * Convert ECG voltage
 */
double EcgCapture::respVoltageConversion(int ADCDecimal)
{
    return 4*(vreff/(1.6468*RESPIRATION_gain))*ADCDecimal/(16777215);
}

/*!
 * Reads a single frame
 *
 * \return QVector<double> singleFrame
 */
const QVector<double> EcgCapture::readFrame()
{
    unsigned int counter = 0;
    char FRAMES[] = {0x00,0x00,0x00,0x00};
    char DATAOUT[] = {0,0,0,0};
    int lead = 0;
    QVector<double> frame;
    bool ecgFlag = false;
    bool respFlag = false;
    bool loffFlag = false;

    csEnable();

    while (counter<nFrames) {
        if(bcm2835_gpio_lev(PIN16)==LOW) {
            bcm2835_spi_transfernb(FRAMES, DATAOUT, sizeof(FRAMES));

            //Uncomment theese lines to check if frames are dropped
            //NOTE: writing to the terminal is slow so for performance reasons
            //      theese code snipped is not used.
//            if (DATAOUT[0] == 0xb0) {
//                test++;
//                if (test%100 == 0) {
//                    printf("%d\n",test);
//                }
//            }

            lead = 0;

            if (DATAOUT[0] == 0x11) {
                //Lead I
                lead |= (DATAOUT[1] << 16);
                lead |= (DATAOUT[2] << 8);
                lead |= DATAOUT[3];
                ecgFlag = true;
            } else if (DATAOUT[0] == 0x12) {
                //Lead II
                lead |= (DATAOUT[1] << 16);
                lead |= (DATAOUT[2] << 8);
                lead |= DATAOUT[3];
                ecgFlag = true;
            } else if (DATAOUT[0] == 0x13) {
                //Lead III
                lead |= (DATAOUT[1] << 16);
                lead |= (DATAOUT[2] << 8);
                lead |= DATAOUT[3];
                ecgFlag = true;
            } else if (DATAOUT[0] == 27) {
                //Resp mag.
                lead |= (DATAOUT[1] << 16);
                lead |= (DATAOUT[2] << 8);
                lead |= DATAOUT[3];
                respFlag = true;
            } else if (DATAOUT[0] == 0x1D) {
                //LOFF
                int mask = 0xF0;
                int tmp = (DATAOUT[1] & mask) >> 4;
                if (tmp == 0x00) {
                    //Leads connected
                    lead = 0;
                } else {
                    //Leads disconnected
                    lead = 1;
                }
                loffFlag = true;
            }

            if (ecgFlag) {
                frame.append(ecgVoltageConversion(lead, leadMode));
                //frame.append(filterEcgVal(ecgVoltageConversion(lead)));
            } else if (respFlag) {
                frame.append(filterVal(respVoltageConversion(lead)));
            } else if (loffFlag) {
                if (lead == 0) {
                    //Leads connected
                    frame.append(0.0);
                } else {
                    //Leads disconnected
                    frame.append(1.0);
                }
            }

            ecgFlag = false;
            respFlag = false;
            loffFlag = false;
            counter++;
        }
    }

    csDisable();

    counter = 0;

    return frame;
}

