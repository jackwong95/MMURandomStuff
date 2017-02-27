"""
coinCounting.py

YOUR WORKING FUNCTION

"""
import numpy as np
import cv2
import math
import os

# you are allowed to import other Python packages above
##########################
#convert the standard [0,179], [0,254], [0,254]
def toStandardHSV(H, S, V):
    H = (H/360 * 179)
    S = (S/100 * 254)
    V = (V/100 * 254)
    return (H,S,V)
        
#given a list of input image and location of template, find the number of matches
def countCoins(inList, templateDir):
    #coin is the image to be used for template matching
    coin = None

    #if there is only one image in the list then make coin the image to be template matched
    if(len(inList) == 1):
        coin = inList[0]

    elif(len(inList) > 1):
    	#else convert the list into a tuple and horizontally stack them side by side
        coin = tuple(inList)
        coin = np.concatenate((coin), axis = 1)

    #get the current directory
    cwd = os.getcwd()

    #count of the coin that are matched
    count = 0

    #absolute path to the coin's template
    coinWD = cwd+templateDir
	 
    #if there is a coin to be template matched
    if coin is not None:
        #convert the coin into gray scale
        coin = cv2.cvtColor(coin, cv2.COLOR_BGR2GRAY)

        #list all of templates
        for templateName in os.listdir(coinWD):
            
            #get each of their absolute path to image
            fullPath = coinWD+templateName

            #read template as gray scale image
            temp = cv2.imread(fullPath, 0)
            
            #template match them 
            res = cv2.matchTemplate(coin,temp,cv2.TM_CCOEFF_NORMED)

            #get only the matched that are accurate
            loc = np.where(res >= 0.99)

            #for each of those coins, count them
            for pt in zip(*loc[::-1]):
                count = count + 1

    return count

def coinCount(coinMat, i):
    # Inputs
    # coinMat: 4-D numpy array of row*col*3*numImages, 
    #          numImage denote number of images in coin set (10 in this case)
    # i: coin set image number (1, 2, ... 10)
    # Output
    # ans: Total value of the coins in the image, in float type
    #
    #########################################################################
    # ADD YOUR CODE BELOW THIS LINE
    
    #read images
    img = coinMat[:,:,:,i]
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    b, g, r = cv2.split(img)

    #get all edges from all channels
    bEdge = cv2.Canny(b, 220, 80)
    gEdge = cv2.Canny(g, 220, 80)
    rEdge = cv2.Canny(r, 220, 80)

    #combine all edges from canny 
    combinedEdge = cv2.bitwise_or(bEdge, rEdge)
    combinedEdge = cv2.bitwise_or(combinedEdge, gEdge)
    
    #close all the small edges of the coins
    rectKernel = cv2.getStructuringElement(cv2.MORPH_RECT,(3,3))
    combinedEdge = cv2.morphologyEx(combinedEdge,cv2.MORPH_CLOSE,rectKernel,iterations=1)
      
    #initialization for flood fill
    floodFill = combinedEdge.copy()
    h, w = combinedEdge.shape
    mask = np.zeros((h+2, w+2), np.uint8)
    
    #flood fill from 0,0 and then inverse the image so the white values will be the coin
    cv2.floodFill(floodFill, mask, (0,0), 255)
    invFloodFill = cv2.bitwise_not(floodFill)
    
    #combine them and perform erosion so that the circle's edges wont be so close to each other
    combinedCoin = cv2.bitwise_or(combinedEdge, invFloodFill)
    combinedCoin = cv2.erode(combinedCoin, rectKernel)
    #cv2.imwrite("in.png", combinedCoin)
    
    #fine tune simple blob detector's parameter to detect separated circles
    params = cv2.SimpleBlobDetector_Params()
    
    params.filterByArea = True
    #default value of simple blob detector for min and max area
    params.minArea = 5;
    params.maxArea = 50000;    
    
    params.filterByConvexity = True;
    params.minConvexity = 0.9;
    params.maxConvexity = 1.0;
    
    params.filterByCircularity = False;
    params.filterByInertia = False;
    params.filterByColor = False;
    
    #bitwise not the combined coin, because simple blob detector uses white as background
    coinMask =cv2.bitwise_not(combinedCoin)
    
    #apply the parameter to the combined coin
    detector = cv2.SimpleBlobDetector_create(params)
    keypoints = detector.detect(coinMask)
    
    #after you get the points, inverse the combine coin back to the original 
    coinMask = cv2.bitwise_not(coinMask)

    #segments contain subset of the original images which contains only the exact 
    segments = []

    #for each keypoints obtained from simple blob detector
    for keyPoint in keypoints:
        x = keyPoint.pt[0]
        y = keyPoint.pt[1]

        #find radius of the circle from center of the circles
        radius = int(x)
        while coinMask[int(y),radius] != 0:
            radius = radius + 1
        radius = radius - x

        #subset the image 
        sub = img[int(y-radius):int(y+radius),int(x-radius):int(x+radius)]
        
        #for the mask of the coins, empty the detected(segmented) coins to 255
        #so the coins that are close to each other will be segmented out later
        coinMask[math.ceil(y-radius):math.ceil(y+radius),math.ceil(x-radius):math.ceil(x+radius)] = 0

        #copy from the original image
        segments.append(sub.copy())

    #start applying watershed
    ellipseKernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5))

    #remove small noises from mask of coin image 
    mask = cv2.morphologyEx(coinMask,cv2.MORPH_OPEN,ellipseKernel, iterations = 2)
    
    #dilate until all neighbour coins overlap each other, so we can make sure that it is a boundary region
    sure_bg = cv2.dilate(mask,ellipseKernel,iterations=3)

    #erode until all coins are no longer connected to each other so we can be sure it is coin
    sure_fg = cv2.erode(mask, ellipseKernel, iterations = 8)
    
    #get the regions that overlap each other "unknown region" of coins
    unknown = cv2.subtract(sure_bg,sure_fg)
    
    #get the connected components for each coins that are "eroded"    
    ret, markers = cv2.connectedComponents(sure_fg)
    
    #increment the marker by one so the first marker starts with 1, because 0 is for the unknown areas
    markers = markers + 1
    
    #for all that are not labelled mark it with 0
    markers[unknown==255] = 0

    #apply watershed algorithm to get the markers
    markers = cv2.watershed(img,markers)
    
    #store all of the labels (each isolated circles)
    labels = {}

    #for each of different labels (meaning each label = each circle) 
    #save them inside a list of tuples containing the row and the column of all that type of label(circle)
    rows, cols = markers.shape
    for r in range(0, rows):
        for c in range(0, cols):
            label = markers[r,c]
            if(label > 1):
                if label not in labels:
                    labels[label] = []
                labels[label].append((r,c))        

    #get the radius and then segment out the coins like the blob detector
    if len(labels) is not 0:
        
        for label in labels:
            points = labels[label]

            #initialize coordinates
            r, c = points[0]
            minX = c
            maxX = c
            minY = r
            maxY = r
            for p in points:
                r, c = p
                minX = min(minX, c)
                maxX = max(maxX, c)
                minY = min(minY, r)
                maxY = max(maxY, r)
            
            #calculate the radius of the label
            radiusX = (maxX - minX)/2
            radiusY = (maxY - minY)/2
            
            #take the smallest estimated radius
            radius = min(radiusX, radiusY)
            centerX = minX + radiusX
            centerY = minY + radiusY

            #segment out the coin
            sub = img[int(centerY-radius):int(centerY+radius),int(centerX-radius):int(centerX+radius)]
            segments.insert(0, sub.copy())

    #pre process the segments by drawing a circle equivilent of the size of each segment right at the center
    #until the end, so we only the coin
    #temporary list that holds the background removed segments
    segmentNoBG = []

    #gold and silver segment list 
    goldColorSegment = []
    silverColorSegment = []

    for segment in segments:
        #the mask for the segment
        mask = np.zeros(segment.shape, np.uint8)
        rMask, cMask, dMask = mask.shape

        #take the min of radius to remove more background 
        radius = min(cMask/2, rMask/2)
        cv2.circle(mask,(int(cMask/2),int(rMask/2)), int(radius), (255,255,255), -1)
        
        #apply mask to the segment
        segment = cv2.bitwise_and(mask, segment)
        segmentNoBG.append(segment)

        #median blur for reducing exposed light and then convert to HSV
        blur = cv2.medianBlur(segment, 3)
        blur = cv2.cvtColor(segment.copy(), cv2.COLOR_BGR2HSV)
        
        #convert the opencv's HSV value to standard HSV value
        low_h_gold, low_s_gold, low_v_gold = toStandardHSV(30, 35, 20)
        high_h_gold, high_s_gold, high_v_gold = toStandardHSV(80, 100, 100)

        #define the lower and upper bound of gold coins
        hsv_min_gold = (low_h_gold,low_s_gold,low_v_gold)
        hsv_max_gold = (high_h_gold,high_s_gold,high_v_gold)

        #create a for coins that are in range, gold coins
        goldMask = cv2.inRange(blur,hsv_min_gold,hsv_max_gold);
        
        #repeat the same p rocess as above but for silver coins
        low_h_silver, low_s_silver, low_v_silver = toStandardHSV(0, 0, 10) 
        high_h_silver, high_s_silver, high_v_silver = toStandardHSV(360, 51, 100)

        hsv_min_silver = (low_h_silver,low_s_silver, low_v_silver)
        hsv_max_silver = (high_h_silver,high_s_silver,high_v_silver)
        silverMask = cv2.inRange(blur,hsv_min_silver,hsv_max_silver)
        
        #flatten and count all of 255 (meaning the mask's concentration of gold or silver)
        silverCount = silverMask.flatten()
        silverCount = (silverCount == 255).sum()
        goldCount = goldMask.flatten()
        goldCount = (goldCount == 255).sum()
        
        rCoin, cCoin, dCoin = segment.shape
        
        #add some paddings in between of mats for template matching to avoid range error (some template height and width are bigger than the current image)
        segment = cv2.copyMakeBorder(segment, 0,200-rCoin, 0, 10, cv2.BORDER_CONSTANT, (0,0,0))

        #separate them accordingly based on which have higher value of silver or gold mask
        if goldCount > silverCount:
        		goldColorSegment.append(segment)
        else:
        		silverColorSegment.append(segment)

    #template matching and get the value
    #dircetory specified is relative and not absolute path
    gold50SenCount = countCoins(goldColorSegment, "/gold coin template/50 sen/")
    gold20SenCount = countCoins(goldColorSegment, "/gold coin template/20 sen/")

    silver50SenCount = countCoins(silverColorSegment, "/silver coin template/50 sen/")
    silver20SenCount = countCoins(silverColorSegment, "/silver coin template/20 sen/")
    silver10SenCount = countCoins(silverColorSegment, "/silver coin template/10 sen/")
    silver5SenCount = countCoins(silverColorSegment, "/silver coin template/5 sen/")    

    #calculate them
    ans = (gold50SenCount + silver50SenCount) * 0.5
    ans = ans + ((gold20SenCount + silver20SenCount) * 0.2)
    ans = ans + (silver10SenCount * 0.1)
    ans = ans + (silver5SenCount * 0.05)
    
    # END OF YOUR CODE
    #########################################################################
    return round(ans, 2)
    
