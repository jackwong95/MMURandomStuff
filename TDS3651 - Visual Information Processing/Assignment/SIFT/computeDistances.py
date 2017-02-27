from scipy.spatial import distance

def computeDistances(fv):
    
    # Cosine similarity measure
    D = distance.squareform(distance.pdist(fv, 'cosine') )
    
    return D