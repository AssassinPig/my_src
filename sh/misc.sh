#1 /bin/bash

var=123545
echo ${#var}

echo $SHELL

if [ $UID -ne 0 ]; then
  echo Non root user. please run as root.
else
  echo "Root user"
fi
