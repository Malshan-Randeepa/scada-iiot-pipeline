# Industrialization Roadmap

This project demonstrates a scalable SCADA / IIoT pattern, but additional engineering is required before real industrial deployment.

## Current Prototype

- two ESP8266 edge nodes
- Wi-Fi transport
- MQTT broker on a local Windows host
- MQTT username/password authentication
- SQLite historian
- simulated temperature signals
- single Ignition Gateway
- single MQTT broker

## Recommended Production Upgrades

### Communications

- MQTT over TLS
- certificate management
- network segmentation
- firewall rules
- broker redundancy
- MQTT Last Will and Testament
- node heartbeat / availability tags
- reconnect backoff and watchdog logic

### Edge Devices

- real industrial sensors
- input validation
- hardware watchdog
- persistent configuration
- device identity management
- firmware version reporting
- timestamp synchronization

### SCADA

- communication-loss alarms
- role-based access control
- audit logging
- alarm rationalization
- alarm shelving policy
- backups and disaster recovery
- redundancy where required

### Data Layer

SQLite is appropriate for a small lab/demo system. A larger deployment should use a production database with appropriate backup, monitoring, retention, and concurrency characteristics.

### Change Management

- versioned releases
- documented configuration changes
- staged test environment
- acceptance-test checklist
- rollback plan
