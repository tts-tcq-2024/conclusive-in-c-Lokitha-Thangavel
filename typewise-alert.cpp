#include "typewise-alert.h"
#include <stdio.h>

#define LOWER_LIMIT_PASSIVE_COOLING 0
#define UPPER_LIMIT_PASSIVE_COOLING 35
#define LOWER_LIMIT_MED_ACTIVE_COOLING 0
#define UPPER_LIMIT_MED_ACTIVE_COOLING 40
#define LOWER_LIMIT_HI_ACTIVE_COOLING 0
#define UPPER_LIMIT_HI_ACTIVE_COOLING 45

// Function to infer the breach type based on the temperature value compared to limits
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) {
    return TOO_LOW;
  }
  if (value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

// Function to set temperature limits based on cooling type
void getCoolingLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit) {
  switch (coolingType) {
    case PASSIVE_COOLING:
      *lowerLimit = LOWER_LIMIT_PASSIVE_COOLING;
      *upperLimit = UPPER_LIMIT_PASSIVE_COOLING;
      break;
    case MED_ACTIVE_COOLING:
      *lowerLimit = LOWER_LIMIT_MED_ACTIVE_COOLING;
      *upperLimit = UPPER_LIMIT_MED_ACTIVE_COOLING;
      break;
    case HI_ACTIVE_COOLING:
      *lowerLimit = LOWER_LIMIT_HI_ACTIVE_COOLING;
      *upperLimit = UPPER_LIMIT_HI_ACTIVE_COOLING;
      break;
  }
}

// Function to classify temperature breaches based on the battery cooling type
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit, upperLimit;
  getCoolingLimits(coolingType, &lowerLimit, &upperLimit);
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

// Function to check the temperature and send alerts based on battery characteristics
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  switch (alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

// Function to send breach type information to the controller
void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

// Function to send email alerts based on the breach type
void sendToEmail(BreachType breachType) {
  const char* recipient = "a.b@c.com";
  switch (breachType) {
    case TOO_LOW:
      printf("To: %s\n", recipient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recipient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
    default:
      // No action for normal state
      break;
  }
}
