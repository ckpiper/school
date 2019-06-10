#This plots the error bounds and forward bounds
using Plots

function main()

	colors = ["red", "blue", "green", "orange", "black", "purple", "turquoise", "yellow", "brown", "grey", "silver"]

	# fDemo = open("../data/newtonFormEval.txt");
	# fDemoC = open("../data/newtonFormEvalC.txt");
	# uBound = 1
	# lBound = -1
	# numberPoints = 501

	# dx = (uBound-lBound)/(numberPoints-1)
	# xx = collect(lBound:dx:uBound) 
	# exact = Array{Float64}(numberPoints+1)
	# interPol = Array{Float64}(numberPoints)
	# interPolC = Array{Float64}(numberPoints)

	# i = 1
	# for ln in eachline(fDemo)
	# 	interPol[i] = parse(Float64, ln)
	# 	i = i + 1
	# end
	# i = 1
	# for ln in eachline(fDemoC)
	# 	interPolC[i] = parse(Float64, ln)
	# 	i = i + 1
	# end

	# pl = plot(xx, interPol, color = colors[5], 
	# 	label = string(colors[5], " = Demo"), 	#label is for each line being added, and it gets added to the legend as such
	# 	xlabel="x", ylabel="y",							#xlabel labels the x-axis similarly for ylabel
	# 	title = "Demo", 								#title puts the title on the graph
	# 	ylims=(-20,8))
	# plot!(xx, interPolC, color = colors[1], label=string(colors[1], " = Demo C"))

	# display(pl)

	# close(fDemo)


	# f1 = open("../data/newtonFormEval.txt");
	# f2 = open("../data/piecewisePolynomialEval.txt");
	# f3 = open("../data/bernsteinExperiment.txt");
	f4 = open("../data/splinePolynomialEval.txt");
	f5 = open("../data/exactEval.txt");
	f6 = open("../data/bSplinePolynomialEval.txt");

	uBound = 5
	lBound = 0.1
	numberPoints = 101
	dx = (uBound-lBound)/(numberPoints-1)
	xx = collect(lBound:dx:uBound) 

	exact = Array{Float64}(numberPoints)
	# bern = Array{Float64}(numberPoints+1)
	# piece = Array{Float64}(numberPoints)
	spline = Array{Float64}(numberPoints)
	bSpline = Array{Float64}(numberPoints)
	# newton = Array{Float64}(numberPoints)

	# i = 1
	# for ln in eachline(f1)
	# 	newton[i] = parse(Float64, ln)
	# 	i = i + 1
	# end
	# i = 1
	# for ln in eachline(f2)
	# 	piece[i] = parse(Float64, ln)
	# 	i = i + 1
	# end
	# i = 1
	# for ln in eachline(f3)
	# 	bern[i] = parse(Float64, ln)
	# 	i = i + 1
	# end
	i = 1
	for ln in eachline(f4)
		spline[i] = parse(Float64, ln)
		i = i + 1
	end
	i = 1
	for ln in eachline(f5)
		exact[i] = parse(Float64, ln)
		i = i + 1
	end
	i = 1
	for ln in eachline(f6)
		bSpline[i] = parse(Float64, ln)
		i = i + 1
	end

	pl = plot(xx, exact, color = colors[5], 
		label = string(colors[5], " =  Exact"), 	#label is for each line being added, and it gets added to the legend as such
		xlabel="x", ylabel="y",							#xlabel labels the x-axis similarly for ylabel
		title="1/x + x From [0.1,5] with 7 Mesh") 								#title puts the title on the graph
		#ylims=(0.5,1))
	# plot!(xx, bern, color = colors[1], label=string(colors[1], " = Bern_15"))
	plot!(xx, spline, color = colors[2], label=string(colors[2], " = Spline"))
	# plot!(xx, bSpline, color =colors[3], label=string(colors[3], " = B-Spline"))
	# plot!(xx, piece, color = colors[4], label=string(colors[4], " = Piece"))
	# plot!(xx, newton, color = colors[5], label=string(colors[5], " = Newton"))
	display(pl)


	# close(f1)
	# close(f2)
	# close(f3)
	close(f4)
	close(f5)
	close(f6)

end

main()
