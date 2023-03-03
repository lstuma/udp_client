# udp_client
Python UDP Client

## How to use

### Connecting to server
```Python
import udp_client as udp
socket = udp.open()
```

### Sending packet
```Python
udp.send("Hello Server!", socket, '127.0.0.1', 7777)
```

### Receiving Packets
```Python
print(udp.receive(socket))
```

### Closing connection
```Python
udp.close(socket)
```
