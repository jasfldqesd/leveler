# ESP32 + MPU6050 Camper Leveler System Outline

## Problem Statement

The RV needs a two-axis leveling system. The system will measure rotation about two axes and display the current leveling state to a cellular device using an internal web server UI.

## Hardware

The hardware will consist of:

* ESP32
* MPU6050 IMU
* Buck converter
* 12V power from the RV fuse bus
* Case or enclosure mounted to the camper

The RV 12V supply will feed the buck converter, which will step the voltage down to 5V for the electronics.

## Software

The software will:

* Connect via Wi-Fi
* Host the web server
* Read input data from the MPU6050 IMU
* Update the web UI with input data
* Convert radians to degrees or linear units, such as inches
* Measure rotation about the Z axis
* Measure rotation about the Y axis

## 1. System Overview

A local, Wi-Fi-enabled camper leveling tool that:

* Uses an MPU6050 IMU to measure tilt
* Hosts a web interface on an ESP32 in Access Point (AP) mode
* Provides real-time leveling data to a phone browser
* Supports calibration and configuration via web UI

## 2. Hardware Components

### 2.1 Controller

* ESP32
* Wi-Fi Access Point
* Web server
* Main control logic

### 2.2 Sensor

* MPU6050 accelerometer and gyro
* I2C interface
* Primary data: accelerometer for tilt

### 2.3 Power System

* 12V camper supply
* Inline fuse, approximately 1A
* Buck converter, 12V to 5V or 3.3V
* Optional power switch

### 2.4 Mechanical

* 3D printed enclosure
* Rigid mounting location on the frame or floor
* Secure mounting method, such as screws, VHB tape, or bracket

### 2.5 Wiring

* SDA, I2C data
* SCL, I2C clock
* VCC
* GND

## 3. Firmware Architecture

### 3.1 Startup / Initialization

1. Boot ESP32
2. Load stored settings, including offsets and configuration
3. Initialize MPU6050
4. Validate sensor communication
5. Start Wi-Fi AP mode
6. Start web server
7. Enter runtime loop

## 4. Coordinate Frames and Sensor Mapping

### 4.1 MPU Coordinate Frame

The MPU6050 coordinate frame is defined by the physical mounting orientation of the sensor inside the enclosure.

This frame is used as the raw measurement frame for:

* accelX
* accelY
* accelZ

The exact physical orientation of the MPU shall be documented based on how the board is mounted in the camper.

### 4.2 RV Coordinate Frame

A separate RV coordinate frame is defined for user-facing interpretation:

* RV front-to-back axis
* RV side-to-side axis
* RV vertical axis

The RV frame is the frame used for leveling calculations and UI output.

### 4.3 Sensor-to-RV Mapping

The software shall map the MPU6050 coordinate frame to the RV coordinate frame so that:

* The correct raw sensor data is used based on the actual mounting orientation
* The displayed leveling output corresponds to camper directions rather than raw board directions

This mapping layer shall handle:

* Axis swaps if required by mounting orientation
* Sign inversion if required by mounting orientation
* Normalization of outputs into RV leveling terms

### 4.4 User-Facing Leveling Axes

The user interface shall display leveling state in RV terms:

* Side-to-side tilt
* Front-to-back tilt

The user interface shall not expose raw MPU axes during normal use.

### 4.5 Sign Convention

A fixed sign convention shall be defined and preserved in code. Example:

* Positive side-to-side value = right side low
* Negative side-to-side value = left side low
* Positive front-to-back value = front high
* Negative front-to-back value = front low

This sign convention shall be validated during testing.

## 5. Sensor Processing

### 5.1 Data Acquisition

* Read raw accelerometer values
* Validate data

### 5.2 Filtering

Use a moving average or low-pass filter. The goal is stable output with minimal jitter.

### 5.3 Tilt Calculation

* Calculate tilt angles from gravity vector
* Calculate RV side-to-side tilt
* Calculate RV front-to-back tilt
* Apply the sensor-to-RV mapping layer before display and user interpretation

## 6. Calibration System

### 6.1 Purpose

Define "level" regardless of mounting orientation.

### 6.2 Procedure

1. User levels camper manually
2. User triggers calibration
3. Store current roll and pitch as offsets

### 6.3 Correction Logic

```text
corrected_roll = measured_roll - roll_offset
corrected_pitch = measured_pitch - pitch_offset
```

## 7. Leveling Logic

### 7.1 Outputs

* Roll angle
* Pitch angle
* Direction indicators

### 7.2 Direction Detection

* Left side low / right side low
* Front low / front high

### 7.3 Tolerance Band

Define "level" range, for example +/-0.2 degrees.

### 7.4 States

* Not level
* Near level
* Level
* Sensor fault

## 8. Web Server Structure

### 8.1 Routes

* `/` -> user page
* `/data` -> JSON data endpoint
* `/calibrate` -> save offsets
* `/admin` -> admin page
* `/update` -> OTA, future

## 9. Data Interface

### 9.1 JSON Example

```json
{
  "roll": 1.2,
  "pitch": -0.6,
  "rollText": "Left side low",
  "pitchText": "Front low",
  "level": false
}
```

## 10. Web UI Design

### 10.1 User Page

* Large roll and pitch display
* Direction text
* Level status indicator
* Optional calibrate button

### 10.2 Admin Page

* Raw sensor values
* Corrected values
* Calibration offsets
* Reboot control
* OTA update access

## 11. Persistent Storage

### 11.1 Stored Values

* Roll offset
* Pitch offset
* Tolerance setting
* Optional configuration values

### 11.2 Storage Method

* ESP32 Preferences (NVS)

## 12. Runtime Loop

1. Read IMU
2. Filter data
3. Compute tilt
4. Apply calibration offsets
5. Determine direction and state
6. Update data endpoints
7. Handle web requests

## 13. Fault Handling

### 13.1 Fault Types

* IMU communication failure
* Invalid sensor readings
* Calibration error
* Wi-Fi failure

### 13.2 Behavior

* Maintain safe operation
* Display fault status on UI
* Log or expose error in admin page

## 14. Minimum Viable Product (MVP)

### Includes

* ESP32 AP mode
* MPU6050 tilt reading
* Basic filtering
* Calibration function
* Simple HTML UI
* JSON data endpoint

### Excludes

* Cloud features
* Remote access
* Mobile apps
* Complex UI frameworks

## 15. Future Enhancements

* Inches-to-raise calculation
* Color-coded UI
* Driver mode with large text
* OTA updates
* Hitch height memory
* Captive portal
* Configurable parameters via UI

## 16. Development Phases

### Phase 1

* Sensor read and serial output

### Phase 2

* Web UI and data endpoint

### Phase 3

* Calibration and offsets

### Phase 4

* Packaging, enclosure, and power integration

### Phase 5

* Refinement and usability improvements
