/*#include "../devicemanager.h"
    #include <stdio.h>
    #include <gtest/gtest.h>




    class DeviceManager_test : public testing::Test {
    protected:
        DeviceManager a;

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
*/
