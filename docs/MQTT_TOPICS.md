# MQTT Topic Contract

The topic structure separates telemetry, command, and feedback traffic.

## Topic Table

| Node | Topic | Publisher | Subscriber | Payload |
|---|---|---|---|---|
| ESP01 | `EE2120/ESP01/temp` | ESP01 | Ignition | Decimal temperature text |
| ESP01 | `EE2120/ESP01/LED/cmd` | Ignition | ESP01 | `1` or `0` |
| ESP01 | `EE2120/ESP01/LED/status` | ESP01 | Ignition | `1` or `0` |
| ESP02 | `EE2120/ESP02/temp` | ESP02 | Ignition | Decimal temperature text |
| ESP02 | `EE2120/ESP02/LED/cmd` | Ignition | ESP02 | `1` or `0` |
| ESP02 | `EE2120/ESP02/LED/status` | ESP02 | Ignition | `1` or `0` |

## Access Model

### ESP01

```text
WRITE  EE2120/ESP01/temp
WRITE  EE2120/ESP01/LED/status
READ   EE2120/ESP01/LED/cmd
```

### ESP02

```text
WRITE  EE2120/ESP02/temp
WRITE  EE2120/ESP02/LED/status
READ   EE2120/ESP02/LED/cmd
```

### Ignition

```text
READ   EE2120/+/temp
READ   EE2120/+/LED/status
WRITE  EE2120/+/LED/cmd
```

## Payload Notes

Temperature is currently transmitted as a plain-text numeric value for simplicity.

LED commands and status use:

```text
1 = ON
0 = OFF
```

## Recommended future extension

Add node availability topics using MQTT Last Will and Testament:

```text
EE2120/ESP01/status
EE2120/ESP02/status
```

with retained `online` / `offline` state.
