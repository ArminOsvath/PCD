import cv2

# citire
src = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')
# culoare -> grey
src = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
# functia de egalizare
dst = cv2.equalizeHist(src)

cv2.imwrite("/home/dj/VSC/C_Cpp/Project/images/equalizeHistogram.jpg", dst)
