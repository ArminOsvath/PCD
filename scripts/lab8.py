import cv2

# citire
src = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')
# culoare -> grey
src = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
# functia de egalizare
dst = cv2.equalizeHist(src)

cv2.imshow('Source image', src)
cv2.imwrite("L8_GREY.jpg", src)
# afisare poza
cv2.imshow('Equalized Image', dst)
cv2.imwrite("L8_EqualizationHist.jpg", dst)
cv2.waitKey()
