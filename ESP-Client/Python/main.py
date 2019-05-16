import time, network
from umqtt.simple import MQTTClient

data = 'Some data from ESP'

ssid = 'ssid'
WiFiPassword = 'password'

broker = 'postman.cloudmqtt.com'
port = 18697
user = 'vfwrxgsq'
password = 'tYTP8C1e_IeK'
clientId = 'ESP_ID'

# подключаемся в качестве станции
connection = network.WLAN(network.STA_IF) # AP_IF - точка доступа
connection.active(True)
connection.connect(ssid, WiFiPassword)

print('Connecting to WiFi ')

while not connection.isconnected():
    pass
    
print('Connected to Wifi\n')

# подключение к брокеру
client = MQTTClient(clientId, broker, port, user, password)
client.connect()

def callback(topic, msg):
   print((topic, msg))

def sendData():
    client.publish('data/fromMicroPython', str(data))

def getData():
    client.set_callback(callback) 
    client.subscribe(topic='data/fromAndroid') 
    #if True:
        # ожидаем сообщение
        #client.wait_msg()
    #else:
        # проверяем есть ли ожидающее сообщение от брокера
       # client.check_msg()
       
timer = 0
while True:
    if(timer == 3):
        # через каждые 4 цикла публикуем 
        sendData()
        timer = 0
        
    getData()
    time.sleep_ms(100)
    timer += 1
