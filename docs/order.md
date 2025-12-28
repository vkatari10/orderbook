# Order Object

## Alive Status

The `.alive` field will give info about the current status of an order regarding if it is active or not. 

| Code | Meaning | Eligible to cancel? | 
|------|---------|---------------------|
| 0 | Cancelled, no longer active | N/A |
| 1 | Alive, no shares filled, active | YES | 
| 2 | Partially filled, active | YES | 
| 3 | Filled, no longer active | NO | 