local randomNum = math.random(0, 5)
io.write("Guess the number between 0 and 5\n")
local guess = io.read("n")
if randomNum == guess then
	print("Good job!")
else
	print("Nope, the number was " .. randomNum)
end
