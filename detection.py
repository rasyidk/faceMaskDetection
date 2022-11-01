import  cv2
from firebase import firebase
import vlc

mouth_cascade = cv2.CascadeClassifier('haarcascade_mcs_mouth.xml')
nose_cascade = cv2.CascadeClassifier('haarcascade_mcs_nose.xml')
firebase = firebase.FirebaseApplication('https://mask-162b2.firebaseio.com/', None)
cap = cv2.VideoCapture(0)
ds_factor = 1.4

while True:
    _, frame = cap.read()

    frame = cv2.resize(frame, None, fx=ds_factor, fy=ds_factor, interpolation=cv2.INTER_AREA)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    val = 1

    mouth_rects = mouth_cascade.detectMultiScale(gray, 1.7, 11)
    nose_rects = nose_cascade.detectMultiScale(gray, 1.3, 5)
    for (x,y,w,h) in nose_rects:
        cv2.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 3)
        val = 0
        break

    for (x,y,w,h) in mouth_rects:
        y = int(y - 0.15*h)
        cv2.rectangle(frame, (x,y), (x+w,y+h), (255,255,255), 3)
        val = 0
        break


    if val == 1:
        p = vlc.MediaPlayer("silahkanmasuk.mp3")
        p.play()

    elif val == 0:
        p = vlc.MediaPlayer("mohonpakaimasker.mp3")
        p.play()

    firebase.put('/', 'val', val)
    cv2.imshow("cam",frame)
    key = cv2.waitKey(1)
    if key == 27:
        break

