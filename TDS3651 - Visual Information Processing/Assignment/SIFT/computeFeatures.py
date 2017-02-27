import numpy as np
import cv2
import pickle
from cyvlfeat import sift as cysift
from scipy.cluster.vq import vq

def computeFeatures(img):
    
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
    
    # Truncate all sides by 5% since they tend to be background
    pca = pca[round(pca.shape[0]*0.05):round(pca.shape[0]*0.95),
                    round(pca.shape[1]*0.05):round(pca.shape[1]*0.95)]
    
    # Extract SIFT features and descriptors
    (frame, desc) = cysift.sift(pca, peak_thresh = 10,
                          edge_thresh = 20, compute_descriptor = True)
    
    # CLAHE
    clahe = cv2.createCLAHE(clipLimit = 4.0, tileGridSize = (8,8))
    pca = clahe.apply(pca)
    
    # Load codebook
    codebook = pickle.load(open("codebook.pkl", "rb"))
    
    # Construct visual word histogram
    code, distortion = vq(desc, codebook)
    featvect, bins = np.histogram(code, codebook.shape[0], normed=True)
    
    return featvect