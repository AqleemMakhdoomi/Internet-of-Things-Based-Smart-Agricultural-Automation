from time import time           ## import the time library
import RPi.GPIO as GPIO         ## Import GPIO library
GPIO.setmode(GPIO.BCM)          ## Use board physixal pin numbering
GPIO.setwarnings(False)
button1 = 6
button2 = 7
button3 = 8
button4 = 9
led1 = 2
led2 = 3
led3 = 4
led4 = 5
GPIO.setup(led1, GPIO.OUT)      ## Setup GPIO Pin 2 to OUT
GPIO.setup(led2, GPIO.OUT)      ## Setup GPIO Pin 3 to OUT
GPIO.setup(led3, GPIO.OUT)      ## Setup GPIO Pin 4 to OUT
GPIO.setup(led4, GPIO.OUT)      ## Setup GPIO Pin 5 to OUT

GPIO.setup(button1, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(button2, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(button3, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(button4, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.output(led1,False)
GPIO.output(led2,False)
GPIO.output(led3,False)
GPIO.output(led4,False)

while True:
        if GPIO.input(button1)== True:
                GPIO.output(led1,True)  ## Turn on Led
        
        else:
                GPIO.output(led1,False) ## Turn off Led

        if GPIO.input(button2)== True:
                GPIO.output(led2,True)  ## Turn on Led
        
        else:
                GPIO.output(led2,False) ## Turn off Led

        if GPIO.input(button3)== True:
                GPIO.output(led3,True)  ## Turn on Led
        
        else:
                GPIO.output(led3,False) ## Turn off Led

        if GPIO.input(button4)== True:
                GPIO.output(led4,True)  ## Turn on Led
        
        else:
                GPIO.output(led4,False) ## Turn off Led


GPIO.Cleanup()
