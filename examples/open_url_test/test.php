<?php
//This is a working example to open an url with the Cactus Rev 2. 
//You can find the tutorial on http://derpade.de/tutorial-cactus-rev-2-esp8266-flashen
//@author Patrick Hausmann <privat@patrick-designs.de>

file_put_content("test.txt", var_export($_SERVER, true));

if (file_exists("test.txt")) echo file_get_content("test.txt");

?>