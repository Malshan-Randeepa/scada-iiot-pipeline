# Security Notes

This repository is an educational / portfolio SCADA and IIoT prototype.

## Do not commit

- Wi-Fi SSIDs or passwords
- MQTT passwords
- Mosquitto password files
- API tokens
- database credentials
- SQLite runtime databases
- Ignition Gateway backups (`.gwbk`)
- private certificates or keys

Use the provided `secrets.h.example` files and create local `secrets.h` files that are ignored by Git.

## Deployment Scope

The example broker configuration uses MQTT over TCP for a trusted lab network. Do not expose port 1883 directly to the public Internet.

For industrial deployment, use:

- MQTT over TLS
- strong unique credentials
- least-privilege ACLs
- network segmentation / firewalling
- secure certificate and secret storage
- SCADA role-based access control
- audited configuration changes
- backup and disaster-recovery procedures

## If a credential is accidentally pushed

Treat the credential as compromised. Rotate or revoke it first, then remove it from Git history if necessary.
