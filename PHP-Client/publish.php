<?php

require_once 'Lib/phpMQTT.php';
$config = require_once 'config.php';

use bluerhinos\phpMQTT; 

$host = $config['host'];
$port = $config['port'];
$username = $config['username'];
$password = $config['password'];
$client_id = 'PHP_publisher';

$message = 'Some data from PHP';

$mqtt = new phpMQTT($host, $port, $client_id);

if($mqtt->connect(true, NULL, $username, $password)){
	echo 'Connecting to the broker is successfull ';

  	$mqtt->publish('data/fromPHP', $message, 0);
  	$mqtt->close();
}
else{
  	echo 'Failed to connect to broker ';
}
