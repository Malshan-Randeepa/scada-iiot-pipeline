# Setup Guide

## Prerequisites

- Windows 10/11
- Eclipse Mosquitto 2.x
- Ignition 8.3 with Vision Module
- Cirrus Link MQTT Engine
- Arduino IDE
- ESP8266 board support
- PubSubClient library
- two ESP8266 boards
- local SQLite database connection in Ignition

## 1. Clone the repository

```bash
git clone https://github.com/Malshan-Randeepa/scada-iiot-pipeline.git
cd scada-iiot-pipeline
```

## 2. Configure local firmware secrets

For ESP01, copy:

```text
firmware/ESP01_Edge_Node/secrets.h.example
```

to:

```text
firmware/ESP01_Edge_Node/secrets.h
```

Repeat for ESP02.

Edit the local `secrets.h` files with:

- Wi-Fi SSID
- Wi-Fi password
- Mosquitto host IP
- MQTT username
- MQTT password

Do not commit `secrets.h`.

## 3. Configure Mosquitto

Create the local password file with `mosquitto_passwd`.

Copy `broker/mosquitto.conf.example` to your local Mosquitto configuration and update the file paths.

Copy `broker/aclfile.example` to the ACL path configured in Mosquitto.

Start the broker:

```bat
mosquitto -c "C:\Program Files\mosquitto\mosquitto.conf" -v
```

## 4. Flash ESP01 and ESP02

Open each Arduino sketch, select the correct ESP8266 board and COM port, then upload.

Open Serial Monitor at `115200` baud and verify:

- Wi-Fi connected
- MQTT connected
- telemetry published every second
- command topic subscribed

## 5. Configure MQTT Engine

Create an MQTT Engine server connection to the Mosquitto broker.

Recommended account:

```text
ignition_scada
```

Verify the server reports **Connected**.

## 6. Import Ignition project resources

Import the Vision project `.zip` from:

```text
ignition/project-export/
```

## 7. Import clean tags

Import:

```text
ignition/tags/default-tags.json
```

into the `default` Tag Provider.

Verify:

```text
[default]ESP01_Temperature
[default]ESP02_Temperature
```

have Good quality and Float values.

## 8. Configure historian

Create or verify the SQLite database connection.

Enable Tag History on the clean temperature tags.

Example lab configuration:

```text
History Provider: Sample_SQLite_Database
Sample Mode: Periodic
Sample Rate: 1 second
```

## 9. Configure Alarm Journal

Create a database-backed Alarm Journal profile using the SQLite datasource.

Verify High/Critical alarm events are recorded.

## 10. Verify Vision dashboard

Check:

- ESP01 and ESP02 live values
- gauges and digital displays
- historical Easy Chart
- Alarm Status Table
- Alarm Journal Table
- LED ON/OFF command
- LED status feedback

## 11. Acceptance test

Run the test matrix in `TESTING.md`.
