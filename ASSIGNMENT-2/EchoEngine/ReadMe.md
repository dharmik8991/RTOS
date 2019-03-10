# Introduction
client A has the user input type client<br>
clients B,C,D,E have loop input type clients<br>

# MY results

*Trail 1*<br>
Sending same data multiple times<br>



|  Sno |  Sending time(in us) |  Service Time(in us) |  
|---|---|---|
| 1 |    59|   125 | 
|  2 |   57|  105 |  
|   3|    60| 83  | 
| 4 |    58|  96  | 
|  5 |   71 |  99 |   


*Trail2*<br>
Changing the type of data sent<br>

|type| Sending time(in us) |  Service Time(in us) |  
|---|---|---|
| lower |    42|  55 | 
|  upper |   73 |  121  |  
|   character|   62| 57  | 

*Trail3*<br>
multiclient


|  no. of clients |  Sending time(in us)  |  Service Time(in us) |  
|---|---|---|
| 1 |    66|  96  | 
|  2 |   18 |  27 |  
|   3|    28| 76 | 
|  4 |   25 |  122 |  
|   5|    19| 200 | 
