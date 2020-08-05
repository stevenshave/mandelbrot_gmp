from PIL import Image, ImageDraw
import gzip
import numpy as np
from matplotlib import cm

file_content=None;
with gzip.open('budahbrot.bin', 'rb') as f:
    file_content = f.read()
data=np.frombuffer(file_content, dtype=np.uint64).reshape(1024,768)
print("max=",np.max(data))
cdata=np.array(data, dtype=float)
cdata=cdata-np.min(cdata)
cdata=cdata/100000
np.clip(cdata,0,255)
img = Image.fromarray(np.uint8((cdata)*255),'L')

img.save('budah.png', 'PNG')