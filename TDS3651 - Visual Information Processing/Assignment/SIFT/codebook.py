import os
import cv2
import random
import numpy as np
import pickle
from cyvlfeat import sift as cysift
from scipy.cluster.vq import kmeans

# Database path
dbpath = os.getcwd() + '/../fooddb'

# Labels
labels = ('AK','BL','CD','CL','DR','MG','NL','PG','RC','ST')

# Sample database to reduce computation time
n = []
for i in range(10):
    temp = list(range(100))
    temp = [j + (i * 100)  for j in temp]
    random.shuffle(temp)
    n = n + temp[0:20]
    
print('Extracting SIFT features...')
feat = list()

for idx in n:
    
    # Read image
    img = cv2.imread( os.path.join(dbpath, str(idx) + ".jpg") )
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    
    # Reshape for PCA
    copy = img.reshape(-1, 3).copy()
    
    # PCA
    mean, eigenvectors = cv2.PCACompute(copy, np.array([]), maxComponents = 3)
    pca = cv2.PCAProject(copy, mean, eigenvectors)
    pca = pca.reshape(img.shape)
    
    # Extract first component
    pca = pca[:,:,0]
    pca = (pca - np.min(pca))/(np.max(pca) - np.min(pca)) * 255
    pca = cv2.convertScaleAbs(pca)
    
    pca = pca[round(pca.shape[0]*0.05):round(pca.shape[0]*0.95),
                    round(pca.shape[1]*0.05):round(pca.shape[1]*0.95)]
    
    # CLAHE
    clahe = cv2.createCLAHE(clipLimit = 4.0, tileGridSize = (8,8))
    pca = clahe.apply(pca)
    
    # Extract SIFT features and descriptors
    (frame, descriptor) = cysift.sift(pca, peak_thresh = 5,
                          edge_thresh = 8, compute_descriptor = True)
    
    # Append descriptors to global descriptors
    feat.append((frame, descriptor))

# Vertical stack descriptors
descriptors = [item[1] for item in feat]
descriptors = np.vstack(descriptors)

# Clean up
del temp
del img
del copy
del mean
del eigenvectors
del pca
del clahe
del idx
del frame
del descriptor
del feat

# Clustering
print('Clustering SIFT descriptors...')

k = 68
descriptors = np.float32(descriptors)

# Codebook
codebook, distortion = kmeans(descriptors, k)

# Pickle codebook
pickle.dump(codebook, open("codebook.pkl", "wb"))
print("Codebook pickled")
