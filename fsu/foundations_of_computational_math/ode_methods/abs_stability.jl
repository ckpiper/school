using Plots


function main()
	
	dgam = pi/500
	gamma = collect(0:dgam:2*pi)

	bashBeta = [[0.0, 1], [0, 3/2.0, -1/2.0], [0, 23/12.0, -16/12.0, 5/12.0], [0, 55/24.0, -59/24.0, 37/24.0, -9/24.0]]
	moultBeta = [[1, 0], [1/2.0, 1/2.0], [5/12.0, 8/12.0, -1/12.0], [9/24.0, 19.0/24.0, -5/24.0, 1/24.0], [251/720.0, 646/720.0, -264/720.0, 106/720.0, -19/720.0], [475/1440.0, 1427/1440.0, -798/1440.0, 482/1440.0, -173/1440.0, 27/1440.0]]
	bdfbeta = [1, 2/3.0, 6/11.0, 12/25.0, 60/137.0]
	bdfalpha = [[1, -1], [1, -4/3.0, 1/3.0], [1, -18/11.0, 9/11.0, -2/11.0], [1, -48/25.0, 36/25.0, -16/25.0, 3/25.0], [1, -300/137.0, 300/137.0, -200/137.0, 75/137.0, -12/137.0]]
	


	uu = linearOne(0.0, gamma);
	# uu = adamsBashford(1, bashBeta[1], gamma)
	# uu = adamsMoulton(1, moultBeta[1], gamma)
	uu = backDiffForm(1, bdfbeta[1], bdfalpha[1], gamma)

	reals = real(uu)
	imags = imag(uu)

	colors = ["red", "blue", "green", "purple", "black", "orange", "turquoise", "grey", "silver", "brown", "yellow"]
	pl = plot(reals, imags, color = colors[1], 
		label = string(colors[1], ", ", "k = ", 1), 	#label is for each line being added, and it gets added to the legend as such
		xlabel="Real", ylabel="Imaginary",							#xlabel labels the x-axis similarly for ylabel
		title="BDFs")				#title puts the title on the graph
		# ylims=(-5,5))								#ylims sets the yaxis limits
		# yticks=0:0.05:0.25)

	# i = 2
	# for theta in 0.1:0.1:1 
	# 	uu = linearOne(theta, gamma)
	# 	reals = real(uu)
	# 	imags = imag(uu)
	# 	plot!(reals, imags, color = colors[i], label = string(colors[i], ", ", "theta = ", theta))
	# 	i = i + 1
	# end

	for k in 2:5
		# uu = adamsBashford(k, bashBeta[k], gamma)
		# uu = adamsMoulton(k, moultBeta[k], gamma)
		uu = backDiffForm(k, bdfbeta[k], bdfalpha[k], gamma)
		reals = real(uu)
		imags = imag(uu)
		plot!(reals, imags, color = colors[k], label = string(colors[k], ", ", "k = ", k))
	end

	display(pl)

end

#This is for determining boundary of the linear One step methods 
function linearOne(theta::Float64, gamma::Vector{Float64})

	uu = (exp(im.*gamma)-1)./(theta.*exp(im.*gamma) + 1 - theta)
	return uu

end


function adamsBashford(k::Int64, beta::Array{Float64}, gamma::Vector{Float64})

	top = (exp(im*k.*gamma) - exp(im*(k-1).*gamma))

	#k+1 because there are k+1 betas and alphas
	k = k+1  		
	bottom = 0

	#Sums up the sigma for boundary 
	for j in 1:k
		bottom = bottom + beta[j].*exp(im*(k-1-(j-1)).*gamma)
	end

	uu = (top./bottom)
	return uu

end


function adamsMoulton(k::Int64, beta::Array{Float64}, gamma::Vector{Float64})

	#Past k==1 the k needs to go down one because the fact that Moultons has 2 k==1 screws up the form
	if (k > 1)
		k = k-1
	end 

	top = (exp(im*k.*gamma) - exp(im*(k-1).*gamma))

	#k+1 because there are k+1 betas and alphas
	k = k+1		
	bottom = 0

	#Sums up the sigma for boundary 
	for j in 1:k
		bottom = bottom + beta[j].*exp(im*(k-1-(j-1)).*gamma)
	end

	uu = (top./bottom)
	return uu

end


function backDiffForm(k::Int64, beta::Float64, alpha::Array{Float64}, gamma::Vector{Float64})

	bottom = beta.*exp(im*k.*gamma)

	#k+1 because there are k+1 betas and alphas
	k = k+1		
	top = 0

	#Sums up the sigma for boundary 
	for j in 1:k
		top = top + alpha[j].*exp(im*(k-1-(j-1)).*gamma)
	end

	uu = (top./bottom)
	return uu

end


main()
