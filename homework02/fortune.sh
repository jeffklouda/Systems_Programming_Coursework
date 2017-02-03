#!/bin/sh

COWSAY="/afs/nd.edu/user15/pbui/pub/bin/cowsay"
QUESTION=

signal_exit () {
    echo ""
    echo "Leaving so soon?" | $COWSAY
    exit 1
}

echo "Hello $USER, what is your question?" | $COWSAY

while [ true ]

trap signal_exit INT HUP TERM

do
    if [ -z "$QUESTION" ] ; then
        read -p "Question? " QUESTION
    else
        echo ""
        shuf << EOF | head -n 1 | $COWSAY
            It is certain
            It is decidedly so
            Without a doubt
            Yes, definitely
            You may rely on it
            As I see it, yes
            Most likely
            Outlook good
            Yes
            Signs point to yes
            Reply hazy try again
            Ask again later
            Better not tell you now
            Cannot predict now
            Concentrate and ask again
            Don\'t count on it
            My reply is no
            My sources say no
            Outlook not so good
            Very doubtful
EOF
        exit 0
    fi
done
exit 0
