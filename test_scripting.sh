#!/bin/bash

echo "Testing simple_shell"
echo "Executing ls"
./simple_shell << EOF
ls
exit
EOF

echo "Executing /bin/ls"
./simple_shell << EOF
/bin/ls
exit
EOF

echo "Executing ls -l /tmp"
./simple_shell << EOF
ls -l /tmp
exit
EOF