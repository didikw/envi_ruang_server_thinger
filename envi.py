#!/usr/bin/python3

import json
import requests as requ
import time

#bot_token ='000000000:XXXXXXXXXXX-ZZZZZZZZZZZZZZZZZZZZZZZ'
#bot_chatID ='-888888888'

req = requ.get('http://servere.com:80/v2/users/username/devices/devicename/device', headers={'Authorization': 'Bearer bearersecret'})
#print(req.text)
d=json.loads(req.text)
envi=d['out']['celsius']
while True :
  if envi > 27.5 :
   url = 'https://api.telegram.org/bot000000000:XXXXXXXXXXX-ZZZZZZZZZZZZZZZZZZZZZZZ/sendMessage?chat_id=-888888888&text=Suhu Ruang Server : ' + str(envi)
   requ.post(url).json()
   time.sleep(60*60)
