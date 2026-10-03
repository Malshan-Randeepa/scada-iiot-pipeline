# Test Matrix

Use this document as evidence that the system functions end to end.

| ID | Test | Expected Result | Status |
|---|---|---|---|
| T01 | ESP01 telemetry | Ignition receives changing ESP01 temperature | Pass |
| T02 | ESP02 telemetry | Ignition receives changing ESP02 temperature | Pass |
| T03 | Clean tag conversion | Temperature values appear as Float | Pass |
| T04 | Historian | Temperature records are written to SQLite | Pass |
| T05 | Historical trend | Easy Chart retrieves stored history | Pass |
| T06 | High alarm | Alarm activates at configured High threshold | Pass |
| T07 | Critical alarm | Alarm activates at configured Critical threshold | Pass |
| T08 | Alarm journal | Alarm events remain available after clearing | Pass |
| T09 | ESP01 LED command | Vision command changes ESP01 onboard LED | Pass |
| T10 | ESP02 LED command | Vision command changes ESP02 onboard LED | Pass |
| T11 | LED feedback | Vision reflects device-published LED state | Pass |
| T12 | Broker restart | Nodes reconnect after broker restart | Recommended verification |
| T13 | Node disconnect | SCADA identifies missing node / stale data | Future improvement |
| T14 | Invalid command payload | Device ignores unsupported LED command | Recommended verification |

## Test Evidence

Store screenshots in:

```text
docs/images/
```

Recommended evidence files:

```text
dashboard-overview.png
historical-trend.png
alarm-status.png
alarm-journal.png
mqtt-control.png
hardware-nodes.jpg
```
