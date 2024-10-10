#pragma once
#ifndef DELIVERY_SCHEDULER_H
#define DELIVERY_SCHEDULER_H

#include "mapping.h"

#define MAX_WEIGHT 1200
#define MAX_VOLUME 50

// Represents the status of a truck in terms of available weight and volume.
struct TruckStatus {
  double availableWeight;
  double availableVolume;
};

// Represents the package to be delivered.
struct Package {
  double weight;
  double volume;
  struct Point destination;
};

// Represents the overall status of the delivery operation.
struct DeliveryStatus {
  struct TruckStatus blueTruckStatus;
  struct TruckStatus greenTruckStatus;
  struct TruckStatus yellowTruckStatus;
  int blueTruckDistance;
  int greenTruckDistance;
  int yellowTruckDistance;
};

/**
 * Initialize the truck statuses with the maximum weight and volume.
 */
struct DeliveryStatus initializeDeliveryStatus();

/**
 * Process user input and return a package object.
 * @returns - the package with user specified weight, volume, and destination.
 */
struct Package processUserInput();

/**
 * Validate the destination of the package.
 * @param destination - the destination point to validate
 * @returns - true if the destination is valid, false otherwise.
 */
int validateDestination(const struct Point destination);

/**
 * Decide which truck should deliver the package.
 * @param package - the package to deliver
 * @param status - the current delivery status
 * @returns - the index of the truck that should deliver the package (0 for
 * blue, 1 for green, 2 for yellow).
 */
int decideTruckForDelivery(const struct Package package,
                           struct DeliveryStatus status);

/**
 * Update the truck status based on the package to be delivered.
 * @param truckIndex - the index of the truck (0 for blue, 1 for green, 2 for
 * yellow)
 * @param package - the package that is being added to the truck
 * @param status - the current delivery status
 */
void updateTruckStatus(int truckIndex, const struct Package package,
                       struct DeliveryStatus *status);

/**
 * Print the delivery route for a package.
 * @param truckIndex - the index of the truck (0 for blue, 1 for green, 2 for
 * yellow)
 * @param package - the package that is being delivered
 * @param status - the current delivery status
 */
void printDeliveryRoute(int truckIndex, const struct Package package,
                        const struct DeliveryStatus status);

/**
 * Prints a message indicating that the package will be shipped the next day.
 */
void printShipsTomorrow();

#endif
