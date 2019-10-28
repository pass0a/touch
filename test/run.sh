#!/bin/bash
export LD_LIBRARY_PATH=/usr/local/app/bin/pack:$LD_LIBRARY_PATH
chmod 777 /usr/local/app/bin/pack/passoa
/usr/local/app/bin/pack/passoa ./touch
