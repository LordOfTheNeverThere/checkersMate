#include <thread>
#include <gtest/gtest.h>

#include "checkersMate/networking/GuestEngine.h"
#include "checkersMate/networking/HostEngine.h"


TEST(MethodChecking, HostEngineFailure) {
    testing::internal::CaptureStderr();
    HostEngine hEngine {"localhost", AF_INET};
    hEngine.bindListenAndAccept(1000);
    std::string err = testing::internal::GetCapturedStderr();
    EXPECT_EQ(err,"No connection from 127.0.0.1\nWaited for 1000 ms\n");
}

TEST(MethodChecking, GuestEngineFailure) {
    testing::internal::CaptureStderr();
    GuestEngine gEngine {"8.8.8.8", AF_INET};
    gEngine.connectToGameHost(2,3);
    std::string err = testing::internal::GetCapturedStderr();
    EXPECT_EQ(err,"Connection to 8.8.8.8 failed after 3 retries.\n");
}

TEST(MethodChecking, HostAndGuestEngineWorking) {
    testing::internal::CaptureStderr();
    for (int i = 0; i < 100; ++i) {
        HostEngine hEngine {"127.0.0.1", AF_INET};
        GuestEngine gEngine {"127.0.0.1", AF_INET};

        auto accepterFunc = [&hEngine]() {
            hEngine.bindListenAndAccept();
        };
        auto connecterFunc = [&gEngine]() {
            gEngine.connectToGameHost();
        };
        std::thread accepter(accepterFunc);
        std::thread connecter(connecterFunc);

        connecter.join();
        accepter.join();

        EXPECT_NE(-1, hEngine.m_socketPtr->m_socket);
        EXPECT_NE(-1, gEngine.m_socketPtr->m_socket);
    }
    std::string err = testing::internal::GetCapturedStderr();
    EXPECT_EQ(err, "");
}

TEST(MethodChecking, HostAndGuestEngineWorkingUsingLocalhost) {

    testing::internal::CaptureStderr();
    for (int i = 0; i < 100; ++i) {
        HostEngine hEngine {"localhost", AF_INET};
        GuestEngine gEngine {"localhost", AF_INET};

        auto accepterFunc = [&hEngine]() {
            hEngine.bindListenAndAccept();
        };
        auto connecterFunc = [&gEngine]() {
            gEngine.connectToGameHost();
        };
        std::thread accepter(accepterFunc);
        std::thread connecter(connecterFunc);

        connecter.join();
        accepter.join();

        EXPECT_NE(-1, hEngine.m_socketPtr->m_socket);
        EXPECT_NE(-1, gEngine.m_socketPtr->m_socket);
    }
    std::string err = testing::internal::GetCapturedStderr();
    EXPECT_EQ(err, "");
}
