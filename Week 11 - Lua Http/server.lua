local socket = require("socket")
local port = 3001
-- bind to all local interfaces on given port
local server = socket.bind("*", port)
print("Listening on port: " .. port)

while true do
	local client = server:accept()
	local data = client:receive()
	print(data)
	client:close()
end
