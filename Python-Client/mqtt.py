import paho.mqtt.client as mqtt
from time import sleep

broker_name = 'pi'
broker_password = '123'
broker_ip = '192.168.43.244'
broker_port = 1883

def on_connect(client, userdata, flags, rc):
    print('Connected with result code ' + str(rc))
    client.subscribe('#')

def on_message(client, userdata, msg):
    print(msg.topic + ' ' + str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set(broker_name, password=broker_password)

client.connect(broker_ip, broker_port)

# client.loop_forever()

send_data = 'hello world'

while True:
    client.publish('fromPython', send_data)
    print('Sent : ' + send_data)
    sleep(0.3)