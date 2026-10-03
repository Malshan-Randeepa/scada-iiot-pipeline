# Alarming and Historian Design

## Clean Process Tags

Raw MQTT payloads are converted into Float tags in the `default` Tag Provider:

```text
[default]ESP01_Temperature
[default]ESP02_Temperature
```

Example:

```text
toFloat({[MQTT Engine].../ESP01/temp})
```

The exact raw MQTT Engine path may vary depending on MQTT Engine namespace configuration.

## Tag Historian

The clean Float tags are historized to SQLite.

Lab configuration:

```text
Sample Mode: Periodic
Sample Rate: 1 second
```

The Vision Easy Chart is used in historical mode to visualize the stored process data.

## Alarm Configuration

The demonstration thresholds are intentionally set near the simulated process range:

| Alarm | Threshold | Priority |
|---|---:|---|
| High Temperature | 36 °C | High |
| Critical Temperature | 39 °C | Critical |

Because the simulated temperature typically varies within the 20–40 °C range, these thresholds allow alarm behavior to be demonstrated frequently.

## Alarm Presentation

The Vision dashboard contains:

- Alarm Status Table for current alarm conditions
- Alarm Journal Table for historical alarm events
- alarm-driven visual indication on the temperature display

## Alarm Journal

Alarm events are stored using a database-backed Alarm Journal profile connected to SQLite.

This allows cleared alarm events to remain available for review after the process returns to normal.

## Production Considerations

For a real process:

- choose alarm limits from process engineering requirements
- configure deadband to prevent chattering
- configure on/off delays where appropriate
- define acknowledgment philosophy
- document alarm priorities consistently
- test communication-loss alarms
- define retention policy for alarm history
