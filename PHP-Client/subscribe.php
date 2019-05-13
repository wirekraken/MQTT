<?php

require_once 'Lib/phpMQTT.php';
$config = require_once 'config.php';

use bluerhinos\phpMQTT; 

$host = $config['host'];
$port = $config['port'];
$username = $config['username'];
$password = $config['password'];
$client_id = 'PHP_subscriber';

$mqtt = new phpMQTT($host, $port, $client_id);

if(!$mqtt->connect()){
	echo 'Failed to connect to broker ';
    exit(1);
}
else{
	echo 'Connecting to the broker is successfull ';
}

$topics['data/fromAndroid'] = array('qos' => 0, 'function' => 'procmsg');
$mqtt->subscribe($topics, 0);

while($mqtt->proc()){}

$mqtt->close();
function procmsg($topic, $value){
    $time = time();
    print $topic . ' ' . $value . "\n";
}

