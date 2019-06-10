
from numpy import loadtxt
from matplotlib import pyplot as plt
import matplotlib.image as mpimg
from PIL import Image

# source = loadtxt("../data/source.txt")
blurred = loadtxt("../data/blurredDemo.txt")
focused = loadtxt("../data/focusedDemo.txt")
compressed = loadtxt("../data/compressedDemo.txt")


# plt.imshow(source)
# title_obj = plt.title('Source File') #get the title property handler
# plt.getp(title_obj, 'text')            #print out the 'text' property for title
# plt.setp(title_obj, color='black') 
# plt.show()

plt.imshow(blurred, cmap = 'gray')
title_obj = plt.title('Blurred File') #get the title property handler
plt.getp(title_obj, 'text')            #print out the 'text' property for title
plt.setp(title_obj, color='black') 
plt.show()


plt.imshow(focused, cmap = 'gray')
title_obj = plt.title('Focused File') #get the title property handler
plt.getp(title_obj, 'text')            #print out the 'text' property for title
plt.setp(title_obj, color='black') 
plt.show()

plt.imshow(compressed, cmap = 'gray')
title_obj = plt.title('Compressed File') #get the title property handler
plt.getp(title_obj, 'text')            #print out the 'text' property for title
plt.setp(title_obj, color='black') 
plt.show()
