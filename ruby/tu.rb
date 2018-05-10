
@machine = IO.readlines(ARGV[0]);
@machineIndex = 0
@tape = ARGV[1].dup

def runState(state,cur)

	return 0 if state == "halt!"

	tok = state.split(":")
	
	if tok[0] == "right"
		@machineIndex += 1
	elsif tok[0] == "left"
		@machineIndex -= 1
		if machineIndex < 0
			puts "lower bounds reached"
			return  -1
		end
	else
		puts "unrecognized command"
		return -1
	end

	tok = tok[1].split(" ")

	i = 0;

	loop do
		if tok[i] == @tape[@machineIndex]
			i += 1
			@tape[@machineIndex] = tok[i]
			i += 1
			return tok[i].to_i
		else
			i += 4
		end
		break if i > tok.length
	end

	return cur
end

def runMachine
	nextState = 1;
	loop do
		nextState = runState(@machine[nextState-1],nextState)
		break if nextState <= 0
	end
end

puts "Initial Tape : " + @tape
runMachine
puts "Final Tape : " + @tape