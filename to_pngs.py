from PIL import Image, ImageDraw
import gzip
import numpy as np
file_content=None;
with gzip.open('mandelbrot.bin', 'rb') as f:
    file_content = f.read()
data=np.frombuffer(file_content, dtype=np.uint8).reshape(5,3840,-1)
from matplotlib import cm
for i in range(data.shape[0]):
    #cdata=np.dstack((data[i,:,:], data[i,:,:],data[i,:,:]))
    #print(cdata.shape)
    #print(data[i,:,:])
    #cdata[:,:,0]=data[i,:,:]
    # print(cdata)
    # cdata[:,:,1]=data[i,:,:]
    # cdata[:,:,2]=data[i,:,:]

    #img = Image.fromarray(np.uint8(cm.twilight_shifted(data[i].T/np.max(data[i]))*255))
    cdata=np.array(data[i], dtype=float)
    cdata=cdata-np.min(cdata)
    cdata=cdata/np.max(cdata)
    print(np.max(cdata))
    img = Image.fromarray(np.uint8(cm.magma_r(cdata.T)*255))
    #img = Image.fromarray(cdata,'RGB')
    img.save(f"output{i:>03}.png", 'PNG')

