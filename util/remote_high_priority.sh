#!/bin/bash

usage() { echo "Usage: $0 [-c <string>]" 1>&2; exit 1; }

while getopts ":c:" o; do
  case "${o}" in
      c)
          c=${OPTARG}
          ;;
      *)
          usage
          ;;
  esac
done

shift $((OPTIND-1))

if [ -z "${c}" ]; then
    usage
fi

echo "Command received: $c"
echo "Connecting to dev.internal..."
ssh caleb@dev.internal "timeout 5s cat < /dev/ttyACM0 && sleep 2s; echo $c > /dev/ttyACM0" 1>&2
echo "Command executed on dev.internal."

# End of file
