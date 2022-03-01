import zmq

context = zmq.Context()

# Socket to talk to server
print "Connecting to server..."
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

dist = 0.3


for request in range(10):
    print "Sending request ", request, "..."
    socket.send(str(dist))

    # Get the reply.
    message = socket.recv()
    print "Received reply ", request, "[", message, "]"a
