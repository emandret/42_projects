#!/bin/bash
export LC_ALL=C
make || exit 1
while [ 1 ];
	  do
min=1
max=100000
DIGIT_LEN=`jot -r 1 $min $max`
STRING=`cat /dev/urandom | head -c $DIGIT_LEN`
LEN=`echo -n "$STRING" | wc -c`
LAST_STRING_FILENAME=last_string.txt
echo -n "$STRING" > $LAST_STRING_FILENAME
MY_HASH="`./ft_ssl md5 -q -s "$STRING"`" && MD5_HASH="`echo -n "$STRING" | md5 -q`" &&
# MY_HASH="`./ft_ssl sha256 -q -s "$STRING"`" && MD5_HASH="`echo -n "$STRING" | openssl sha -sha256`" &&
	if [ "$MY_HASH" = "$MD5_HASH" ];
	then
		echo "string_len = $LEN"
		echo "my: $MY_HASH"
		echo "os: $MD5_HASH"
		echo "OK"
	else
		echo "string_len = $LEN"
		echo "my: $MY_HASH"
		echo "os: $MD5_HASH"
		echo FAILURE; exit 1;
	fi;
done;

