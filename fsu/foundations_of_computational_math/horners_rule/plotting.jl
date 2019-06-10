#This plots the error bounds and forward bounds
using Plots

function main()

	colors = ["red", "blue", "green", "orange", "black", "purple", "turquoise", "yellow", "brown", "grey", "silver"]
	#f = open("../data/dataP2a.txt");
	#f = open("../data/dataP2b.txt");
	#f = open("../data/dataP2c.txt");
	#f = open("../data/dataDouble.txt");
	#f = open("../data/dataP3c1.txt");
	#f = open("../data/dataP3c2.txt");
	#f = open("../data/dataP3c3.txt");

	# lBound = 1.9       #Problem 2
	# uBound = 2.1	   #Problem 2
	#lBound = -4.1      #Problem 3
	#uBound = -3.9	   #Problem 3
	# lBound = 14.9      #Problem 3
	# uBound = 15.1	   #Problem 3
	# lBound = 48      #Problem 3
	# uBound = 52	   #Problem 3


	f = open("../data/data.txt");
	uBound = 0
	lBound = 1
	numberPoints = 500


	dx = (uBound-lBound)/numberPoints 			
	xx = collect(lBound:dx:uBound) 				#This gives a vector from lBound->uBound by dx steps
	exact = Array{Float32}(numberPoints+1)
	horner = Array{Float32}(numberPoints+1)
	forUpBound = Array{Float32}(numberPoints+1)
	forLowBound = Array{Float32}(numberPoints+1)
	runUpBound = Array{Float32}(numberPoints+1)
	runLowBound = Array{Float32}(numberPoints+1)

	count = 1
	i = 1
	#The data is in the file by evaluations at x.
	#So lines with 1 mod 4 are exact values at x_i, lines 2 mod 4 are horner values at x_i,
	#lines 3 mod 4 are forward error bounds at x_i, and lines 0 mod 4 are run error bounds at x_i
	for ln in eachline(f) 
	    #print("$(length(ln)), $ln")
	    if (count % 4 == 1)
	    	exact[i] = parse(Float64, ln)
		elseif (count % 4 == 2)
			horner[i] = parse(Float32, ln)
		elseif (count % 4 == 3)
			forUpBound[i] = exact[i] + parse(Float32, ln)
			forLowBound[i] = exact[i] - parse(Float32, ln)
		elseif (count % 4 == 0)
			runUpBound[i] = exact[i] + parse(Float32, ln)
			runLowBound[i] = exact[i] - parse(Float32, ln)
			i = i + 1
		end 
		count = count + 1
	end

	close(f)



	pl = plot(xx, exact, color = colors[1], 
		label = string(colors[1], " =  Exact"), 	#label is for each line being added, and it gets added to the legend as such
		xlabel="x", ylabel="u",							#xlabel labels the x-axis similarly for ylabel
		title="Exact, Horner's, Both Error Bounds") 					#title puts the title on the graph
	plot!(xx, horner, color = colors[2], label=string(colors[2], " = Horner"))
	plot!(xx, forUpBound, color = colors[3], label=string(colors[3], " = Forward HighBound"))
	plot!(xx, forLowBound, color = colors[3], label=string(colors[3], " = Forward LowBound"))
	plot!(xx, runUpBound, color = colors[4], label=string(colors[4], " = Run HighBound"))
	plot!(xx, runLowBound, color = colors[4], label=string(colors[4], " = Run LowBound"))
	display(pl)


	# pl = plot(xx, exact, color = colors[1], 
	# 	label = string(colors[1], " =  Exact"), 	#label is for each line being added, and it gets added to the legend as such
	# 	xlabel="x", ylabel="u",							#xlabel labels the x-axis similarly for ylabel
	# 	title="Double Precision with Run Bounds P2a") 					#title puts the title on the graph
	#plot!(xx, horner, color = colors[2], label=string(colors[2], " = Horner"))
	# plot!(xx, runUpBound, color = colors[4], label=string(colors[4], " = Run HighBound"))
	# plot!(xx, runLowBound, color = colors[4], label=string(colors[4], " = Run LowBound"))
	#display(pl)


	# pl = plot(xx, exact, color = colors[1], 
	# 	label = string(colors[1], " =  Exact"), 	#label is for each line being added, and it gets added to the legend as such
	# 	xlabel="x", ylabel="u",							#xlabel labels the x-axis similarly for ylabel
	# 	title="Single Precision with Both Bounds P2b") 					#title puts the title on the graph
	# plot!(xx, horner, color = colors[2], label=string(colors[2], " = Horner"))
	# plot!(xx, forUpBound, color = colors[3], label=string(colors[3], " = Forward HighBound"))
	# plot!(xx, forLowBound, color = colors[3], label=string(colors[3], " = Forward LowBound"))
	# plot!(xx, runUpBound, color = colors[4], label=string(colors[4], " = Run HighBound"))
	# plot!(xx, runLowBound, color = colors[4], label=string(colors[4], " = Run LowBound"))
	# display(pl)


	# pl = plot(xx, exact, color = colors[1], 
	# 	label = string(colors[1], " =  Exact"), 	#label is for each line being added, and it gets added to the legend as such
	# 	xlabel="x", ylabel="u",							#xlabel labels the x-axis similarly for ylabel
	# 	title="Single Precision with Run Bounds P2b") 					#title puts the title on the graph
	# plot!(xx, horner, color = colors[2], label=string(colors[2], " = Horner"))
	# plot!(xx, runUpBound, color = colors[4], label=string(colors[4], " = Run HighBound"))
	# plot!(xx, runLowBound, color = colors[4], label=string(colors[4], " = Run LowBound"))
	# display(pl)

end 


main()
