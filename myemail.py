from time import time
import RPi.GPIO as GPIO         ## Import GPIO library
import smtplib
GPIO.setmode(GPIO.BCM)          ## Use board physixal pin numbering
GPIO.setwarnings(False)
intrusion = 25
GPIO.setup(intrusion, GPIO.IN, pull_up_down=GPIO.PUD_UP)
smtpUser = 'smartagriculture2018a@gmail.com'
smtpPass = 'qwert12345$#'
toAdd = 'smartagriculture2018@gmail.com'
fromAdd = smtpUser
subject = 'WELCOME TO THE SMART AND ADVANCED AGRICULTURE MONITORING USING IOT AND RASPBERRY PI'
header = 'To: ' + toAdd + '\n' + 'From: ' + fromAdd + '\n' + 'subject: ' + subject
body =  'THIS SMART AGRICULTURE SYSTEM HAS BEEN DEVELOPED BY THE STUDENTS OF BGSBU RAJOURI, DEPTT. OF COMPUTER SCIENCE AND ENGINEERING"\n" GROUP MEMBERS"\n" 1. MOAZAM FARHAN BANDAY(03-CSE-14) "\n" 2. AQLEEM MAKHDOOMI(31-CSE-14)"\n" 3. ZAHID ASLAM SHORA(34-CSE-14)"\n" 4. UMAR FAROOQ(45-CSE-14)'
print header + '\n' + body
s = smtplib.SMTP('smtp.gmail.com',587)
s.ehlo()
s.starttls()
s.ehlo()
s.login(smtpUser,smtpPass)
s.sendmail(fromAdd, toAdd, header + '\n\n' + body)
s.quit()
count1 = 1
count2 = 1
while True:
        if GPIO.input(intrusion) == True:
                count2 =1
                count1+=1
                if count1 == 2:
                        #print('hello how r u')
                        smtpUser = 'smartagriculture2018a@gmail.com'
                        smtpPass = 'qwert12345$#'
                        toAdd = 'smartagriculture2018@gmail.com'
                        fromAdd = smtpUser
                        subject = 'INTRUSION DETECTED IN THE FIELD'
                        header = 'To: ' + toAdd + '\n' + 'From: ' + fromAdd + '\n' + 'subject: ' + subject
                        body =  'INTRUSION DETECTED, CHECK OUT THE LATEST FEEDS AT http://192.168.43.107:8081'
                        print header + '\n' + body
                        s = smtplib.SMTP('smtp.gmail.com',587)
                        s.ehlo()
                        s.starttls()
                        s.ehlo()
                        s.login(smtpUser,smtpPass)
                        s.sendmail(fromAdd, toAdd, header + '\n\n' + body)
                        s.quit()

         
                
        else:
                count1 =1
                count2+=1
                if count2 == 2:
              
                        smtpUser = 'smartagriculture2018a@gmail.com'
                        smtpPass = 'qwert12345$#'
                        toAdd = 'smartagriculture2018@gmail.com'
                        fromAdd = smtpUser
                        subject = 'NO INTRUSION DETECTED IN THE FIELD'
                        header = 'To: ' + toAdd + '\n' + 'From: ' + fromAdd + '\n' + 'subject: ' + subject
                        body =  'NO INTRUSION DETECTED, CHECK OUT THE LATEST FEEDS AT http://192.168.43.107:8081'
                        print header + '\n' + body
                        s = smtplib.SMTP('smtp.gmail.com',587)
                        s.ehlo()
                        s.starttls()
                        s.ehlo()
                        s.login(smtpUser,smtpPass)
                        s.sendmail(fromAdd, toAdd, header + '\n\n' + body)
                        s.quit()
                                        

GPIO.Cleanup()
