/*
      * ecgstream_test.cpp
      *
      *  Created on: Sep 17, 2015
      *      Author: Martin Rostin
      */
     
     #include "../ecgstream.h"
     #include <stdio.h>
    #include <gtest/gtest.h>
    
    
    
    
    class EcgStream_test : public testing::Test {
    protected:
        EcgStream a;

    /*  testProjectTest(){
            b=new A();
            b->setValue(2,15);
    }
   22     virtual ~testProjectTest(){
   23     delete b;
   24     }
   25     virtual void SetUp(){}
   26     virtual void TearDown(){}
   27     A* b; */
    };
    
    TEST_F(EcgStream_test, check_values) {
    	a.add(5.4);
    	a.add(5);
                EXPECT_EQ(5.4,a.getData());
              EXPECT_EQ(5,a.getData());
   
        }
    TEST_F(EcgStream_test, settingValues){
    
 //       a.values[4]=18;
 //       a.values[5]=14;
        EXPECT_NE(18,a.getData());
        EXPECT_NE( 14,a.getData()) <<"Expected false";
    
    
    }
    
    
    TEST_F(EcgStream_test, CheckEmpty){

    //       a.values[4]=18;
    //       a.values[5]=14;
           EXPECT_TRUE(a.empty()) <<"Not empty" ;
           EXPECT_FALSE(a.full()) <<"Full";


       }


    /*
     int main(int argc,char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();

    }
    */

    /*
    GTEST_API_ int main(int argc, char **argv) {
      printf("Running main() from gtest_main.cc\n");
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }  */
   // Tests factorial of positive numbers.
    //TEST(FactorialTest, Positive) {
     // EXPECT_EQ(1, Factorial(1));
      //EXPECT_EQ(2, Factorial(2));
     // EXPECT_EQ(6, Factorial(3));
    //  EXPECT_EQ(40320, Factorial(8));
    //}
    
    
    /*// Tests IsPrime()

    // Tests negative input.
    TEST(IsPrimeTest, Negative) {
      // This test belongs to the IsPrimeTest test case.

      EXPECT_FALSE(IsPrime(-1));
      EXPECT_FALSE(IsPrime(-2));
      EXPECT_FALSE(IsPrime(INT_MIN));
    }

    // Tests some trivial cases.
    TEST(IsPrimeTest, Trivial) {
      EXPECT_FALSE(IsPrime(0));
      EXPECT_FALSE(IsPrime(1));
      EXPECT_TRUE(IsPrime(2));
         EXPECT_TRUE(IsPrime(3));
    }*/
