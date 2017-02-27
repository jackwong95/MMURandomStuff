import pickle
import numpy as np
import matplotlib.pyplot as plt
import os
from SIFT import computeDistances as sift
from RGB import computeDistances as rgb

# Food database information
dbSize = 1000
retrieves = [i for i in range(0, 1000, 10)]
nPerCat = 100
nC = 10
labels = ('AK','BL','CD','CL','DR','MG','NL','PG','RC','ST')

# Database path
dbpath = os.getcwd() + "/fooddb/"

# Function to return a tuple of precisions and recalls.
#
# Input: pickle file name
# Output: a tuple of a list of precision and a list of recall
#
def get_results(picklefile, func):

    fv = pickle.load(open(picklefile, "rb"))
    
    D = func(fv)
    avg_prec = np.zeros(dbSize)
    
    precisions = []
    recalls = []
    
    for retrive in retrieves:
        for c in range(nC): 
          for i in range(nPerCat):
              idx = (c*nPerCat) + i;
        
              # access distances of all images from query image, sort them asc
              nearest_idx = np.argsort(D[idx, :]);
        
              # quick way of finding category label for top K retrieved images
              retrievedCats = np.uint8(np.floor((nearest_idx[1:retrive+1])/nPerCat));
         
              # find matches
              hits = (retrievedCats == np.floor(idx/nPerCat))
              
              # calculate average precision of the ranked matches
              if np.sum(hits) != 0:
                  avg_prec[idx] = np.sum(hits*np.cumsum(hits)/(np.arange(retrive)+1)) / np.sum(hits)
              else:
                  avg_prec[idx] = 0.0
              
        mean_avg_prec = np.mean(avg_prec)
        recall = np.sum(hits) / nPerCat
        
        precisions = precisions + [mean_avg_prec]
        recalls = recalls + [recall]
        
    return (precisions, recalls)
    
# Get the benchmark precision and recall
precisions, recalls = get_results("RGB/feat.pkl", rgb.computeDistances)

# Get the SIFT method precision and recall
precisions_sift, recalls_sift = get_results("SIFT/feat.pkl", sift.computeDistances)

        
plt.clf()
plt.plot(recalls, precisions, lw=2, color='navy', label='RGB Color Histogram')
plt.plot(recalls_sift, precisions_sift, lw=2, color='red', label='SIFT')
plt.legend(loc="upper right")
plt.xlabel('Recall')
plt.ylabel('Precision')
plt.ylim([0.0, 1.05])
plt.xlim([0.0, 1.0])
plt.title('Precision-Recall')
plt.savefig("Precision Recall.png")
# plt.show()
# plt.close()