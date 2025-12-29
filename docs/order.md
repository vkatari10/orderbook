# Order Object

## `.qty`

Represents the quantity required, wanted, or currently filled. This is the only field that will be mutated and changed depending on the TIF of the order. 

| TIF | `.qty` Meaning | 
|-----|--------------|
| DAY | number of shares to fill, if decreased then remaining numbers to fill | 
| FOK | number of shares required to fill | 
| IOC | max number of shares to try to fill, filled qty will be shown in trade obj | 

## `.status`

The `.status` field will give info about the current status of an order regarding if it is active or not. 

| Code | Meaning | Eligible to cancel? | 
|------|---------|---------------------|
| 0 | Cancelled, no longer active | N/A |
| 1 | Alive, no shares filled, active | YES | 
| 2 | Partially filled, active | YES | 
| 3 | Filled, no longer active | NO | 
| 4 | Dead/Rejected, could not fill shares, no longer active | NO | 