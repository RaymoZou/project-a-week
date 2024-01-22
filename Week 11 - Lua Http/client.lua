local socket = require("socket")
local port = 3001
local client = socket.connect("*", port)
client:send("testing\n")
client:close()
