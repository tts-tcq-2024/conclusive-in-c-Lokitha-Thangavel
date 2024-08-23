#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    // Test cases for inferBreach function

    // Test case for TOO_LOW
    EXPECT_EQ(inferBreach(-1.0, 0.0, 35.0), TOO_LOW); // Value below lower limit
    EXPECT_EQ(inferBreach(0.0, 0.0, 35.0), NORMAL);  // Value equal to lower limit

    // Test case for NORMAL
    EXPECT_EQ(inferBreach(17.0, 0.0, 35.0), NORMAL); // Value within limits
    EXPECT_EQ(inferBreach(35.0, 0.0, 35.0), NORMAL); // Value equal to upper limit

    // Test case for TOO_HIGH
    EXPECT_EQ(inferBreach(36.0, 0.0, 35.0), TOO_HIGH); // Value above upper limit

    // Test case for a different range
    EXPECT_EQ(inferBreach(10.0, 0.0, 45.0), NORMAL); // Value within higher limits
    EXPECT_EQ(inferBreach(46.0, 0.0, 45.0), TOO_HIGH); // Value above higher limits
    EXPECT_EQ(inferBreach(-5.0, 0.0, 45.0), TOO_LOW); // Value below lower limit for higher range

    // Test case for another range
    EXPECT_EQ(inferBreach(20.0, 0.0, 40.0), NORMAL); // Value within medium active limits
    EXPECT_EQ(inferBreach(41.0, 0.0, 40.0), TOO_HIGH); // Value above medium upper limit
    EXPECT_EQ(inferBreach(-1.0, 0.0, 40.0), TOO_LOW); // Value below medium lower limit
}
