import cv2
import numpy as np

vid = cv2.VideoCapture('Hello.mp4')

if not vid.isOpened():
    print('Error!')

ballX = 0
ballY = 0
size = 150

fix = 0


def process(prev, frame):
    return cv2.subtract(frame, prev)


lastFrame = vid.read()
while vid.isOpened():

    ret, fr = vid.read()
    if ret is True:

        kik = process(lastFrame, fr)

        cv2.imshow('Frame', kik)
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break
        lastFrame = fr
    else:
        break

vid.release()

cv2.destroyAllWindows()




