# tcp_client
Python TCP Client

## How to use

### Connecting to server
´´´
import tcp_client as tcp
socket = tcp.connect('127.0.0.1', 7777)
´´´

### Sending packet
```
tcp.send("Hello Server!", socket)
```

### Receiving Packets
```
print(tcp.receive(socket))
```

### Closing connection
```
tcp.close(socket)
```