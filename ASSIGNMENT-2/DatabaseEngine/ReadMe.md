# Introduction
client A have user input type client<br>
clients B,C,D,E has the loop input type clients<br>marks.txt is the test file

# MY results

*Trail 1*<br>
Sending same data multiple times<br>



|  Sno |  Sending time(in us) |  Service Time(in us) |  
|---|---|---|
| 1 |    74|  174 | 
|  2 |   65 |  116 |  
|   3|    61| 76  | 
| 4 |    74|  127 | 
|  5 |   48 |  86 |  
|   6|    72| 92 | 


*Trail2*<br>
Changing the type of data sent<br>

|type| Sending time(in us) |  Service Time(in us) |  
|---|---|---|
| Incorrect  |    58|  84  | 
|  Data not found |   62 |  160  | 
| Input incomplete | 51 | 66 |
|   Sucessful(small file) |   41| 117  | 
| Sucessful(Big file) | 52 |456 |

*Trail3*<br>
multiclient( Sending small file with loop input of big file)


|  no. of clients |  Sending time(in us)  |  Service Time(in us) |  
|---|---|---|
| 1 |    70|  189  | 
|  2 |   11 |  37 |  
|   3|    14| 49  | 
|  4 |   21 |  74 |  
|   5|    28| 109 | 
