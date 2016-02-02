/*
      * ECGmock_test.cpp
      *
      *  Created on: Sep 14, 2015
      *      Author: Martin Rostin
      */
     
    
    #include "../ecgmock.h"
    #include <stdio.h>
    #include <gtest/gtest.h>
    
    
    
    
    class EcgMock_test : public testing::Test {
    protected:
        EcgMock a;
    
    };
    
    TEST_F(EcgMock_test, check_connected) {
        EXPECT_TRUE(a.connected()) << "Mock not connected at start";
        a.close();
        EXPECT_FALSE(a.connected()) <<"Mock is still connected after close";
    
        }
    
    TEST_F(EcgMock_test, check_reconnect) {
        a.close();
                EXPECT_FALSE(a.connected()) << "Mock connected at start";
                a.reconnect();
              EXPECT_TRUE(a.connected()) <<"Mock not connected after reconnect";
    
        }
    /* TEST_F(EcgMock_test, settingValues){
    
        a.state=18;
        a.values[5]=14;
        EXPECT_EQ(18,a.values[4]);
        EXPECT_NE( 14,a.values[12]) <<"Expected false";
    
    
    } */
