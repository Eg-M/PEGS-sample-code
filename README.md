# Paper Gas Sensors Data Acquisition with MBED

## Project Description
This MBED project focuses on reading signals from six paper sensors. The key feature is the implementation of a pseudo median filter and reducing average to filter the signal, enhancing the accuracy and reliability of the measurements.

## Code Implementation
- The code employs `AnalogIn` objects for each sensor.
- A timer object is used to manage the reading intervals.
- The ADC internal channels raw values are read and filtered using a pseudo median filter.
- Vref calibration for accurate voltage measurement.

## Hardware Setup
- Six analog paper sensors connected to the MBED board.

## Software Dependencies
- mbed.h
- Other MBED-specific libraries for ADC and serial communication.

## Operation
- The system reads and processes the sensor data every 10 minutes.
- Sensor values are filtered and converted to resistance values.
- Serial communication is used for data output.

## Extension Opportunities
- Integrate with a wireless module for remote data transmission.
- Implement data analysis algorithms for predictive analytics.

This README provides an overview of the MBED project for paper gas sensors, highlighting the key components, code structure, and potential extensions.
