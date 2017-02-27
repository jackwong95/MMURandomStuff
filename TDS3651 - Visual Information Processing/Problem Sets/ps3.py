import cv2
import numpy as np

'''
class for each bounding box
where each bounding box counts number of cars passing by,
every time when a bounding box detected a car 
it will be disabled until a fixed number of frames passed 
'''
class BoundingBox:
    
    #global count for cars
    cars = 0
    
    def __init__(self, x, y, width, height, ratio, resetTick):
        self.count = -1
        self.resetTick = resetTick
        self.ratio = ratio
        self.x = x
        self.y = y
        self.xExt = x + width
        self.yExt = y + height    
        
    def tick(self, img):
        
        #extent(content) of the bounding box
        extent = np.sum(img[self.y:self.yExt, self.x:self.xExt]/255)/((self.yExt-self.y)*(self.xExt-self.x))
        if extent > self.ratio and self.count == -1:#not self.flag:
            #add car count
            BoundingBox.cars = BoundingBox.cars + 1
            #start the tick
            self.count = 0
            
        #if detected a car, start counting how many frames passed
        if self.count != -1:
            self.count = self.count + 1
            #should i reset the frames passed now?
            if self.count == self.resetTick:
                self.count = -1
            
    #draw the bounding rectangle
    def draw(self, mask, color):
        mask = cv2.rectangle(mask, (self.x, self.y), (self.xExt, self.yExt), (255, 255, 255), 4)
        #if the frame is still within the bound then make the border green
        if self.count != -1:
            color = cv2.rectangle(color, (self.x, self.y), (self.xExt, self.yExt), (0, 255, 0), 4)
        else:
            color = cv2.rectangle(color, (self.x, self.y), (self.xExt, self.yExt), (0, 0, 255), 4)
        return (mask, color)


vid = cv2.VideoCapture('traffic.avi')
length = int(vid.get(cv2.CAP_PROP_FRAME_COUNT))

# ~~~ PRE PROCESSING ~~~
#get the first frame
ret, frame = vid.read()
w, h, c = frame.shape
videoFrames = np.zeros((length, w, h, c))
background = np.zeros((w, h, c), dtype = np.uint8)
vid.set(cv2.CAP_PROP_POS_FRAMES,0);

#store all of frames into numpy array
for i in range (length):
    ret,frame = vid.read()
    videoFrames[i, :, :, :] = frame

#apply median filter on each pixel
for chan in range(c):
    for row in range(h):
        for col in range(w):
            background[col, row, chan] = np.median(videoFrames[:, col, row, chan])

#cv2.imshow("background", background)
            
# ~~~ CAR COUNTING ~~~
#initialize
vid.set(cv2.CAP_PROP_POS_FRAMES,0)
#create 3 bounding boxes    
boxes = [BoundingBox(0, 110, 40, 10, 0.6, 4), 
         BoundingBox(45, 110, 40, 10, 0.5, 4), 
         BoundingBox(100, 100, 50, 15, 0.2, 4)]


for i in range (length - 1):
    ret, frame = vid.read()
    
    bgs = cv2.subtract(background, frame)
    bgs = cv2.cvtColor(bgs, cv2.COLOR_BGR2GRAY)
    
    ret, thresh = cv2.threshold(bgs, 50, 255, cv2.THRESH_BINARY)
    
    #custom closing with different kernel sizes!
    #reduce noise using erosion
    shadow = cv2.morphologyEx(thresh, cv2.MORPH_ERODE, cv2.getStructuringElement(cv2.MORPH_RECT, (2, 2)))
    #highlight the shadow using custom rect shape
    shadow = cv2.morphologyEx(shadow, cv2.MORPH_DILATE, cv2.getStructuringElement(cv2.MORPH_RECT, (4, 5)))
    
    #to display the bounding rectangles
    mask = np.zeros((w, h, 3), dtype = np.uint8)
    color = np.zeros((w, h, 3), dtype = np.uint8)
    
    for box in boxes:
        box.tick(shadow)
        mask,color = box.draw(mask, color)
    
    #inverse the mask
    frameWithBoundingBox = cv2.subtract(frame, mask)
    #color the frame with different color bounding box
    frameWithBoundingBox = cv2.add(frameWithBoundingBox, color)

    k = cv2.waitKey(60) & 0xff
    if k == 27:
        break
    
    # show the current frame
    cv2.imshow('frame', frame)
    # show the threshold and closing frame
    cv2.imshow('clean frame', shadow)
    # show the reduced noise and closed image
    cv2.imshow("frame with bounding box", frameWithBoundingBox)  
    
cv2.destroyAllWindows()
vid.release()

print("Number of cars : ", BoundingBox.cars)